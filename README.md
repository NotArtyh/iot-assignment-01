# Assignment #01 - Turn on the Sequence! (TOS)

![circuit-diagram](./circuit-diagram.png)

## Setup and Build

The project has been tested and has native support for the following `i2c` displays:

- LCD - `1602 lcd`
- OLED - `sh1106 oled`

Any display using the i2c protocol and supported by the `LiquidCrystal_I2C.h` library for LCDs or the `U8g2lib.h` for the OLEDs (virtually any oled display with any protocol is supported with this library) should work with minimal editing of the respective display module.

To switch between the OLED and LCD configuration, set the `-D USE_OLED` build flag in the `platformio.ini` (or configure a platformio env with the corresonding flag)

## Project Architecture

The project has been developed with a modular and flexible system in mind. Every hardware component and system function has been separated in its respective module to ensure separation of scope and purpose. Each component hides its internal implementation, only exposing abstract methods via its
correpsonding header, ensuring safety and proper separation, while also alowing for a modular programming style to be followed. All of this has been done while still using the C paradime, creating language wrappers around the arduino and library methods that use a C++ syntax.

The fsm acts as the core for the whole project with a _super loop_ -type implementation, handling the routing and implementation of states that define the game. Each state simply calls the exposed
methods that handle the needed component function without having to implement anything internally.
The game module implements the game logic, handling the tracking of the user sequence, score and
win/lose validations; the fsm is still responsible for timings and managing the game difficulty.

During development different libraries had to be tested for handling the OLED display. This was made necessary by the heavy use of the internal SRAM for the display buffer, which showed to be a changellenge for the 2kb available to the arduino uno. The `U8g2lib.h` has been chosen as a popular alternative to the initially used `Adafruit_SH1106.h`, which ended up being too cumbersome and wasteful for the available memory. The library supports a wide range of displays, while also providing a useful `u8x8` character only mode, which doesn't require a display buffer to be kept in ram. This then escalated in an attempt to optimize the code, and its memory usage, as much as reasonably possible. (A lot of improvements could still be had, while it is known to us where and which parts would need improvements, the underlying super loop style implementation is prone to more memory usage than a event driven one, but still, it could be improved further).
