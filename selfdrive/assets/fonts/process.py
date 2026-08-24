#!/usr/bin/env python3
from pathlib import Path
from io import BytesIO
import json

import pyray as rl

FONT_DIR = Path(__file__).resolve().parent
SELFDRIVE_DIR = FONT_DIR.parents[1]
TRANSLATIONS_DIR = SELFDRIVE_DIR / "ui" / "translations"
LANGUAGES_FILE = TRANSLATIONS_DIR / "languages.json"

GLYPH_PADDING = 6
EXTRA_CHARS = "–‑✓×°§•X⚙✕◀▶✔⌫⇧␣○●↳çêüñ–‑✓×°§•€£¥"
UNIFONT_LANGUAGES = {"th", "zh-CHT", "zh-CHS", "ko", "ja"}
# BluePilot: these known Noto Sans SC gaps are rendered by Unifont or the
# existing color-emoji renderer, so they do not belong in the CJK atlas.
SIMPLIFIED_CHINESE_EXTERNAL_GLYPHS = set("↳⌫⚙✔✕🔥")
SIMPLIFIED_CHINESE_WEIGHTS = {
  "NotoSansSC-Medium": 500,
  "NotoSansSC-Bold": 700,
}
# End BluePilot


def _languages():
  if not LANGUAGES_FILE.exists():
    return {}
  with LANGUAGES_FILE.open(encoding="utf-8") as f:
    return json.load(f)


def _char_sets():
  base = set(map(chr, range(32, 127))) | set(EXTRA_CHARS)
  unifont = set(base)
  # BluePilot: keep the Noto Sans SC atlas limited to Simplified Chinese UI
  # text so it remains practical on the original comma 3 GPU.
  simplified_chinese = set(base)
  # End BluePilot

  for language, code in _languages().items():
    unifont.update(language)
    po_path = TRANSLATIONS_DIR / f"app_{code}.po"
    try:
      chars = set(po_path.read_text(encoding="utf-8"))
    except FileNotFoundError:
      continue
    (unifont if code in UNIFONT_LANGUAGES else base).update(chars)

    # BluePilot: include the language display name and the zh-CHS catalog.
    if code == "zh-CHS":
      simplified_chinese.update(language)
      simplified_chinese.update(c for c in chars if ord(c) >= 32)
    # End BluePilot

  # BluePilot: keep known external-fallback glyphs out of the generated atlas.
  simplified_chinese.difference_update(SIMPLIFIED_CHINESE_EXTERNAL_GLYPHS)
  # End BluePilot

  return (tuple(sorted(ord(c) for c in base)),
          tuple(sorted(ord(c) for c in unifont)),
          tuple(sorted(ord(c) for c in simplified_chinese)))


def _glyph_metrics(glyphs, rects, glyph_count: int):
  entries = []
  min_offset_y, max_extent = None, 0
  for idx in range(glyph_count):
    glyph = glyphs[idx]
    rect = rects[idx]
    width = int(round(rect.width))
    height = int(round(rect.height))
    offset_y = int(round(glyph.offsetY))
    min_offset_y = offset_y if min_offset_y is None else min(min_offset_y, offset_y)
    max_extent = max(max_extent, offset_y + height)
    entries.append({
      "id": glyph.value,
      "x": int(round(rect.x)),
      "y": int(round(rect.y)),
      "width": width,
      "height": height,
      "xoffset": int(round(glyph.offsetX)),
      "yoffset": offset_y,
      "xadvance": int(round(glyph.advanceX)),
    })

  if min_offset_y is None:
    raise RuntimeError("No glyphs were generated")

  line_height = int(round(max_extent - min_offset_y))
  base = int(round(max_extent))
  return entries, line_height, base


def _write_bmfont(path: Path, font_size: int, face: str, atlas_name: str, line_height: int, base: int, atlas_size, entries):
  # TODO: why doesn't raylib calculate these metrics correctly?
  if line_height != font_size:
    print("using font size for line height", atlas_name)
    line_height = font_size
  lines = [
    f"info face=\"{face}\" size=-{font_size} bold=0 italic=0 charset=\"\" unicode=1 stretchH=100 smooth=0 aa=1 padding=0,0,0,0 spacing=0,0 outline=0",
    f"common lineHeight={line_height} base={base} scaleW={atlas_size[0]} scaleH={atlas_size[1]} pages=1 packed=0 alphaChnl=0 redChnl=4 greenChnl=4 blueChnl=4",
    f"page id=0 file=\"{atlas_name}\"",
    f"chars count={len(entries)}",
  ]
  for entry in entries:
    lines.append(
      ("char id={id:<4} x={x:<5} y={y:<5} width={width:<5} height={height:<5} " +
       "xoffset={xoffset:<5} yoffset={yoffset:<5} xadvance={xadvance:<5} page=0  chnl=15").format(**entry)
    )
  path.write_text("\n".join(lines) + "\n")


def _font_data(font_path: Path, variable_weight: int | None = None) -> bytes:
  data = font_path.read_bytes()
  if variable_weight is None:
    return data

  # Raylib does not expose variable-font axes and loads Noto Sans SC at the
  # source font's 100-weight default. Materialize a static instance before
  # passing it to Raylib so Chinese text has a predictable, readable weight.
  from fontTools.ttLib import TTFont
  from fontTools.varLib.instancer import instantiateVariableFont

  font = TTFont(BytesIO(data))
  instantiateVariableFont(font, {"wght": variable_weight}, inplace=True, optimize=True)
  output = BytesIO()
  font.save(output)
  font.close()
  return output.getvalue()


def _process_font(font_path: Path, codepoints: tuple[int, ...], output_stem: str | None = None,
                  variable_weight: int | None = None):
  output_stem = output_stem or font_path.stem
  weight_label = f" at weight {variable_weight}" if variable_weight is not None else ""
  print(f"Processing {font_path.name}{weight_label} as {output_stem}...")

  font_size = {
    "unifont.otf": 16,  # unifont is only 16x8 or 16x16 pixels per glyph
    # BluePilot: UI text is normally 40-75 px. Generate CJK glyphs near their
    # display size to avoid the blocky scaling visible with 16 px Unifont.
    "NotoSansSC-VF.ttf": 80,
    # End BluePilot
  }.get(font_path.name, 200)

  data = _font_data(font_path, variable_weight)
  file_buf = rl.ffi.new("unsigned char[]", data)
  cp_buffer = rl.ffi.new("int[]", codepoints)
  cp_ptr = rl.ffi.cast("int *", cp_buffer)
  glyph_count = rl.ffi.new("int *", len(codepoints))
  glyphs = rl.load_font_data(
    rl.ffi.cast("unsigned char *", file_buf), len(data), font_size, cp_ptr, len(codepoints),
    rl.FontType.FONT_DEFAULT, glyph_count
  )
  if glyphs == rl.ffi.NULL:
    raise RuntimeError("raylib failed to load font data")

  # BluePilot: make missing translation glyphs visible during the build
  # instead of silently producing empty boxes on the device.
  loaded_codepoints = {glyphs[idx].value for idx in range(glyph_count[0])}
  missing_codepoints = sorted(set(codepoints) - loaded_codepoints)
  if missing_codepoints:
    printable = ", ".join(f"U+{cp:04X}" for cp in missing_codepoints)
    print(f"warning: {font_path.name} is missing {len(missing_codepoints)} glyphs: {printable}")
  # End BluePilot

  rects_ptr = rl.ffi.new("Rectangle **")
  image = rl.gen_image_font_atlas(glyphs, rects_ptr, glyph_count[0], font_size, GLYPH_PADDING, 0)
  if image.width == 0 or image.height == 0:
    raise RuntimeError("raylib returned an empty atlas")

  rects = rects_ptr[0]
  atlas_name = f"{output_stem}.png"
  atlas_path = FONT_DIR / atlas_name
  entries, line_height, base = _glyph_metrics(glyphs, rects, glyph_count[0])

  if not rl.export_image(image, atlas_path.as_posix()):
    raise RuntimeError("Failed to export atlas image")

  _write_bmfont(FONT_DIR / f"{output_stem}.fnt", font_size, output_stem, atlas_name, line_height, base, (image.width, image.height), entries)


def main():
  base_cp, unifont_cp, simplified_chinese_cp = _char_sets()
  fonts = sorted(FONT_DIR.glob("*.ttf")) + sorted(FONT_DIR.glob("*.otf"))
  for font in fonts:
    if "emoji" in font.name.lower():
      continue
    # BluePilot: generate a dedicated compact Simplified Chinese atlas.
    if font.stem.lower().startswith("notosanssc"):
      glyphs = simplified_chinese_cp
      for output_stem, variable_weight in SIMPLIFIED_CHINESE_WEIGHTS.items():
        _process_font(font, glyphs, output_stem, variable_weight)
      continue
    else:
      glyphs = unifont_cp if font.stem.lower().startswith("unifont") else base_cp
    # End BluePilot
    _process_font(font, glyphs)
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
