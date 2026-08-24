import pyray as rl
from openpilot.system.ui.lib.scroll_panel import GuiScrollPanel
from openpilot.system.ui.widgets import Widget

ITEM_SPACING = 40
LINE_COLOR = rl.GRAY
LINE_PADDING = 40


class LineSeparator(Widget):
  def __init__(self, height: int = 1):
    super().__init__()
    self._rect = rl.Rectangle(0, 0, 0, height)

  def set_parent_rect(self, parent_rect: rl.Rectangle) -> None:
    super().set_parent_rect(parent_rect)
    self._rect.width = parent_rect.width

  def _render(self, _):
    rl.draw_line(int(self._rect.x) + LINE_PADDING, int(self._rect.y),
                 int(self._rect.x + self._rect.width) - LINE_PADDING, int(self._rect.y),
                 LINE_COLOR)


class Scroller(Widget):
  def __init__(self, items: list[Widget], spacing: int = ITEM_SPACING, line_separator: bool = False, pad_end: bool = True):
    super().__init__()
    self._items: list[Widget] = []
    self._spacing = spacing
    self._line_separator = LineSeparator() if line_separator else None
    self._pad_end = pad_end

    # BluePilot: track content geometry so expanding/collapsing settings cannot leave
    # the scroll position outside the new content bounds.
    self._layout_signature: tuple[tuple[int, float], ...] | None = None
    # End BluePilot

    self.scroll_panel = GuiScrollPanel()

    for item in items:
      self.add_widget(item)

  def add_widget(self, item: Widget) -> None:
    self._items.append(item)
    item.set_touch_valid_callback(self.scroll_panel.is_touch_valid)

  def _render(self, _):
    # TODO: don't draw items that are not in the viewport
    visible_items = [item for item in self._items if item.is_visible]

    # BluePilot: visibility and item heights can change while a settings section or
    # description is expanded. Clamp immediately to the new bounds instead of letting
    # the old offset bounce back over several frames.
    layout_signature = tuple((id(item), float(item.rect.height)) for item in visible_items)
    layout_changed = layout_signature != self._layout_signature
    self._layout_signature = layout_signature
    # End BluePilot

    # Add line separator between items
    if self._line_separator is not None:
      l = len(visible_items)
      for i in range(1, len(visible_items)):
        visible_items.insert(l - i, self._line_separator)

    content_height = sum(item.rect.height for item in visible_items) + self._spacing * (len(visible_items))
    if not self._pad_end:
      content_height -= self._spacing

    # BluePilot: a collapsed section can become shorter than the viewport or current
    # offset. Resetting through set_offset also stops obsolete scroll inertia.
    if layout_changed:
      max_scroll_distance = max(0.0, content_height - self._rect.height)
      clamped_offset = max(-max_scroll_distance, min(0.0, self.scroll_panel.offset))
      self.scroll_panel.set_offset(clamped_offset)
    # End BluePilot
    scroll = self.scroll_panel.update(self._rect, rl.Rectangle(0, 0, self._rect.width, content_height))

    rl.begin_scissor_mode(int(self._rect.x), int(self._rect.y),
                          int(self._rect.width), int(self._rect.height))

    cur_height = 0
    for idx, item in enumerate(visible_items):
      if not item.is_visible:
        continue

      # Nicely lay out items vertically
      x = self._rect.x
      y = self._rect.y + cur_height + self._spacing * (idx != 0)

      # Consider scroll
      y += scroll

      # Update item state
      item.set_position(x, y)
      item.set_parent_rect(self._rect)
      item.render()

      # BluePilot: rendering a ListItem can expand its description and change its
      # height. Use that new height for the next row to prevent one-frame overlap.
      cur_height += item.rect.height + self._spacing * (idx != 0)
      # End BluePilot

    rl.end_scissor_mode()

  def show_event(self):
    super().show_event()
    # Reset to top
    self.scroll_panel.set_offset(0)
    self._layout_signature = None
    for item in self._items:
      item.show_event()

  def hide_event(self):
    super().hide_event()
    for item in self._items:
      item.hide_event()
