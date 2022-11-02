## __DataLogExtended Example Description__

Main function is to show how to use ISPU device to send data from a Nucleo board
using UART to a connected PC with the Unicleo-GUI Utility.

To run the application, it is needed to install and launch the Unicleo-GUI on the PC.
The Unicleo-GUI is available on [Unicleo-GUI](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/sensor-software-development-tools/unicleo-gui.html).

After connection has been established:

  - the user can view data from ISPU sensor
  - the user can upload predefined json/ucf pairs of files to ISPU device
  - the user can also visualize this data as graphs


### __Keywords__

  - ISPU
  - I2C
  - VCOM


### __Directory contents__

  - Binary - contains binary file to be directly downloaded to corresponding HW
  - EWARM - contains project files for IAR toolchain
  - Inc - contains header files
  - MDK-ARM - contains project files for Keil µVision toolchain
  - Src - contains source files
  - STM32CubeIDE - contains project files for STM32CubeIDE toolchain


### __Hardware and Software environment__

  - This example runs on STM32 Nucleo board with ISPU sensor.
  - This example has been tested with STMicroelectronics NUCLEO-F401RE RevC and
    NUCLEO-L476RG RevC boards with ISM330IS and LSM6DSO16IS devices and can
    be easily tailored to any other supported device and development board.


### __How to use it?__

In order to make the program work, you must do the following:

  - WARNING: before opening the project with any toolchain be sure your folder
    installation path is not too in-depth since the toolchain may report errors
    after building
  - Open your preferred toolchain
  - Rebuild all files and load your image into target memory
  - Run the example
  - Alternatively, you can download the pre-built binary in "Binary"
    folder included in the distributed package
