/**
  @page DataLogExtended example based on ISPU device and STM32 Nucleo Board

  @verbatim
  ******************************************************************************
  * @file    readme.txt
  * @author  MSD
  * @brief   This application contains an example which shows how to obtain data
  *          from ISPU sensor. The communication is done using an UART connection
  *          with PC and the Unicleo-GUI Utility.
  ******************************************************************************
  *
  * Copyright (c) 2022 STMicroelectronics. All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @endverbatim

@par Example Description

Main function is to show how to use ISPU device to send data from a Nucleo board
using UART to a connected PC with the Unicleo-GUI Utility.

To run the application, it is needed to install and launch the Unicleo-GUI on the PC.
The Unicleo-GUI is available on https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/sensor-software-development-tools/unicleo-gui.html

After connection has been established:
  - the user can view data from ISPU inertial sensor like Accelerometer and Gyroscope
  - the user can upload predefined json/ucf pairs of files to ISPU device
  - the user can also visualize this data as graphs

@par Keywords

ISPU, I2C, VCOM

@par Hardware and Software environment

  - This example runs on STM32 Nucleo device with ISPU sensor
  - This example has been tested with STMicroelectronics:
    - NUCLEO-F401RE RevC board
    - NUCLEO-L476RG RevC board

ADDITIONAL_COMP : ISM330IS https://www.st.com/en/mems-and-sensors/ism330is.html

@par How to use it?

This package contains projects for 3 IDEs: IAR, Keil µVision and STM32CubeIDE. In order to make the
program work, you must do the following:
  - WARNING: before opening the project with any toolchain be sure your folder
    installation path is not too in-depth since the toolchain may report errors
    after building.
  - Open STM32CubeIDE or alternatively the Keil uVision toolchain or the IAR toolchain.
  - Rebuild all files and load your image into target memory.
  - Run the example.
  - Alternatively, you can download the pre-built binaries in "Binary"
    folder included in the distributed package.

  * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
  */
