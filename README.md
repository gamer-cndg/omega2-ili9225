# Onion Omega2 ILI9225 Library

### Description
This library enables the Omega2(+) to control a ILI9225 based display via SPI. It contains many graphics-drawing and display-drawing functions. Due to the current state of the OnionIoT provided bit-banged SPI driver ([which has multiple issues](https://github.com/OnionIoT/spi-gpio-driver/issues)), drawing is extremely slow (1-2 FPS). Thus, this library is rather suited for displaying simple user interfaces, simple graphics or static pictures. 

### Hardware Wireup
You will need:
* an Onion Omega2 or Omega2+, preferably with the extension dock
* an ILI9225 display (e.g., [on ebay](https://www.ebay.com/itm/2-2-inch-LCD-2-2-SPI-TFT-LCD-Display-Module-ILI9225-with-SD-Socket-for-Arduino/162145341921))
* breadboard and wires

You can connect the wires (MOSI, SCLK, CS, RST, RS, LED) to any free GPIO pin you have. This library uses the [spio-gpio-driver](https://github.com/OnionIoT/spi-gpio-driver/) from OmegaIoT, which is able to bit-bang SPI on any given pin. The other signals RST (reset), RS (also called register select, data/command or D/C) and LED (backlight control) can also be connected to any GPIO. The library takes an initialization object in which you can define which pins to use. 

### Library Usage

Your first call should be to `ILI9225_Init()` with a pin configuration object (see example code). You can then use any of the functions to draw text, shapes or pixels into the framebuffer. At last, you have to transfer the local framebuffer to the display by calling `ILI9225_CopyFramebuffer()`.  

The following library functions are available:
* drawing text with different fonts, sizes and colors
* drawing shapes (lines, circles, triangles) either filled or outlined with a color
* changing the orientation of the display (portrait / landscape)
* turning the display on and off (either by LED GPIO pin or SPI commands)
* modfying the internal framebuffer directly, or drawing from an external frame buffer
* executing a graphics demo


### Compilation

This project was designed for cross-compliation. Compile your toolchain according to https://docs.onion.io/omega2-docs/cross-compiling.html, **change the paths** in the `Makefile` (`TOOLCHAIN_ROOT_DIR`) and do a `make all`. Optionally, `make upload` will attempt to use `sshpass` with `scp` to transfer the compiled binary to your Omega Onion2 system. Simply change the IP address and the password if you whish to use this feature.

For a successful compilation, you need the `omega_includes` and `omega_libraries` folder somewhere on your computer. You can download them at [todo](https://todo.com/). This folder basically includes the `libonionspi`, `liboniondebug` and `libugpio` library and include files. Change the path in the `Makefile` accordingly.

After executing `make all`, the library file `libili9225.so` and a executable file `displayTest` will be created. If you wish to to use the dynamic library in your own project, you have to:
1. set the include path to where the `ILI9225.h` is (`-I somedir`)
2. set the library path to where the `libili9225.so` and the dependency `libonionspi.so`, `liboniondebug.so` and `libugpio.so` is (`-L somelibdir`)
3. set the linker flags to link your executable against the prementioned dependencies (`-lili9225 -lonionspi -loniondebug -lugpio`) 

See the Makefile of this project to see how a userspace program may be compiled and linked against this library.

### Testing the compiled binaries

1. Install the SPI library by typing `opkg update && opkg install libonionspi`. If you already have that library, skip this step.
2. Transfer the `libili9225.so` file from this repository to the `/usr/lib/` folder on your Omega2, e.g. by using `ssh` or `scp`. 
3. Make sure the wiring is that which is described in the `main.c`. 
4. Transfer the `displayTest` file (ELF) to some directory on your Omega2, e.g. `/root/` and run it!

### Credits
* Maximilian Gerhardt, library porter
* Nkawu, [ported library to AVR Arduino](https://github.com/Nkawu/TFT_22_ILI9225)
* 4D Systems, [original library](https://github.com/4dsystems/screen_4D_22_library)
 
![hardware setup](https://github.com/gamer-cndg/omega2-ili9225/raw/master/display.jpg)
