## __NEAI_AnomalyDetection Example Description__

Main function is to show how to use the "N" version of ISPU device programmed with the library generated from NEAI Studio and send data from a Nucleo board
to any connected PC terminal application.

The example of the Anomaly Detection library has been generated and integrated into the example. If the user wants to use his own library generated from NEAI Studio, he can replace the ispu_neai.h file in the Inc directory and possibly adapt other code in the Src directory to support this library.

After connection has been established:

  - the user can view the library learning during normal device behaviour
  - the user can view if any anomaly from the device normal behaviour has been detected
  - the user can view the acceleration data of ISPU buffer when the anomaly has been detected


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
    NUCLEO-U575ZI-Q RevC boards with ISM330ISN and LSM6DSO16ISN devices and can
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
