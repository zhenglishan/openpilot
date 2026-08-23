# Comma 3 support

BluePilot calls the original Comma 3 `tici` (device-tree model may also be
`comma three`). This port is pinned to the C3-compatible **AGNOS 18.4** image;
AGNOS 18.5 rejects the original C3 board firmware during early boot. The C3
uses its internal STM32F4 DOS panda over USB. C3X/C4 keep the upstream
STM32H7/SPI path.

The launcher defers EC25 modem USB enumeration until pandad has connected to
the DOS panda. Native and Python dependencies otherwise use BP7's normal
locked build environment.
