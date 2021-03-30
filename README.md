# Mks-Robin-Nano-Marlin2.0-Firmware
## Features
This branch uses [Mks-Robin-Nano-Marlin2.0-Firmware](https://github.com/makerbase-mks/Mks-Robin-Nano-Marlin2.0-Firmware.git) firmware for MKS Robin Nano V2 and V3 motherboards, in order to change the standard layout, to use LVGL version 7 with as few images as possible, using thema material, or others available in LVGL.

• If possible, make the selection of layouts available in the settings menu.

• Use the standard language defined in marlin, and their respective translations (I don't see the need for the option in the menu to change the language).

• Use ESP3D as a wifi support.

- References used for development:
https://docs.lvgl.io/latest/en/html/index.html

- "Symbol" pattern
https://docs.lvgl.io/latest/en/html/overview/font.html?highlight=font%20image

 [Marlin2.0.x](https://github.com/MarlinFirmware/Marlin), added the [LVGL v7](https://github.com/lvgl/lvgl.git), supporting colourful GUI and touch screen. It is developed on PlatformIO, we hope more and more developers will participate the development of this repository.

![](https://github.com/ThiagoAboo/Mks-Robin-Nano-Marlin2.0-Firmware/blob/LVGL7-material-theme/Images/MKS_Robin_Nano_light.jpg)

![](https://github.com/ThiagoAboo/Mks-Robin-Nano-Marlin2.0-Firmware/blob/LVGL7-material-theme/Images/MKS_Robin_Nano_dark.jpg)

(https://github.com/ThiagoAboo/Mks-Robin-Nano-Marlin2.0-Firmware/blob/LVGL7-material-theme/Images/MKS_Robin_Nano_v2.mp4)

## Build
As the firmware is based on Marlin2.0.x which is built on the core of PlatformIO, the buid compiling steps are the same as Marlin2.0.x. You can directly using [PlatformIO Shell Commands](https://docs.platformio.org/en/latest/core/installation.html#piocore-install-shell-commands), or using IDEs contain built-in PlatformIO Core(CLI), for example, [VSCode](https://docs.platformio.org/en/latest/integration/ide/vscode.html#ide-vscode) and [Atom](https://docs.platformio.org/en/latest/integration/ide/atom.html). VSCode is recommended.

## About the gcode file preview
The images should be added to gcode file when slicing, and MKS has developed the [plugin for Cura](https://github.com/makerbase-mks/mks-wifi-plugin) to make it.

## Firmware Can be run on Robin Nano V1.x / V2.x boards and V3.x boards
## MKS Robin Nano V1.x build and update firmware

1. Build config:
     
- platformio.ini: 
     
     default_envs = mks_robin_nano35    
- Configuation.h:  
     #define SERIAL_PORT 3  
     #define MKS_ROBIN_TFT35  
     #define MOTHERBOARD BOARD_MKS_ROBIN_NANO  
     #define TFT_LVGL_7_UI  
     #define TOUCH_SCREEN  

2. Update firmware:
   
- Enter the `.pio\build\mks_robin_nano35` directory, copy the `Robin_nano35.bin` to the sd card
- Insert SD card to the motherboard, and you can see the update interface after power on.   

## MKS Robin Nano V2.x build and update firmware

1. Build config:
     
- platformio.ini: 
     
     default_envs = mks_robin_nano35    
- Configuation.h:   
     #define SERIAL_PORT 3  
     #define MKS_TS35_V2_0  
     #define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V2     
     #define TFT_LVGL_7_UI  
     #define TOUCH_SCREEN  

2. Update firmware:
   
- Enter the `.pio\build\mks_robin_nano35` directory, copy the `Robin_nano35.bin` to the sd card
- Insert SD card is to the motherboard, and you can see the update interface after power on.   

## MKS Robin Nano V3.x build and update firmware

1. Build config:
     
- platformio.ini: 
     
     default_envs = mks_robin_nano_v3_usb_flash_drive_msc
- Configuation.h:   
     #define SERIAL_PORT -1  
     #define MKS_TS35_V2_0  
     #define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V3     
     #define TFT_LVGL_7_UI  
     #define TOUCH_SCREEN

- Configuation_adv.h:    
     Now you can either use the TF card or USB disk, use TF card:   
    // #define USB_FLASH_DRIVE_SUPPORT  
    Use USB disk:  
     #define USB_FLASH_DRIVE_SUPPORT  

2. Update firmware:
   
- Enter the `.pio\build\mks_robin_nano35` directory, copy the `Robin_nano_v3.bin` to the sd card or usb disk
- Insert sdcard or usb disk to the motherboard, and you can see the update interface after power on.  

## For more function configuration, please refer to Robin nano series Wiki
- [MKS Robin Nano V1.x Wiki](https://github.com/makerbase-mks/MKS-Robin-Nano-V1.X/wiki). 
- [MKS Robin Nano V2.x Wiki](https://github.com/makerbase-mks/MKS-Robin-Nano-V2.X/wiki). 
- [MKS Robin Nano V3.x Wiki](https://github.com/makerbase-mks/MKS-Robin-Nano-V3.X/wiki).

## More information about the Robin Nano V1.X
Please refer to [MKS Robin Nano github](https://github.com/makerbase-mks/MKS-Robin-Nano-V1.X).

##  More information about the Robin Nano V2.X
Please refer to [MKS Robin Nano V2 github](https://github.com/makerbase-mks/MKS-Robin-Nano-V2).

##  More information about the Robin Nano V3.X
Please refer to [MKS Robin Nano V3 github](https://github.com/makerbase-mks/MKS-Robin-Nano-V3.X).

