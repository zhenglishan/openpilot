# Comma 3 support

BluePilot calls the original Comma 3 `tici` (device-tree model may also be
`comma three`). During the AGNOS 18.5 validation, slot A runs **AGNOS 18.5**
while slot B remains on the known-good **AGNOS 18.4** recovery image. The
original C3 continues to use its internal STM32F4 DOS panda over USB. C3X/C4
keep the upstream STM32H7/SPI path.

The launcher defers EC25 modem USB enumeration until pandad has connected to
the DOS panda. Native and Python dependencies otherwise use BP7's normal
locked build environment.
