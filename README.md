# X-CUBE-ISPU Firmware Package

![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/x-cube-ispu.svg?color=brightgreen)

The X-CUBE-ISPU is an expansion software package for STM32Cube. This software is gathering Temperature, Humidity, Pressure and Motion sensor drivers for the HTS221, LPS22HH, LIS2MDL, IIS2MDC, ISM330IS, LSM6DSO16IS, SHT40-AD1B, LPS22DF, STTS22H devices, running on STM32. It is built on top of STM32Cube software technology that ease portability across different STM32 microcontrollers.

**X-CUBE-ISPU software features**:

- Complete software to build applications using the following sensors:

  - temperature and humidity sensors: SHT40-AD1B for X-NUCLEO-IKS4A1, HTS221 for X-NUCLEO-IKS01A3
  - pressure sensor: LPS22DF for X-NUCLEO-IKS4A1, LPS22HH for XNUCLEO-IKS01A3
  - temperature sensors: STTS22H for X-NUCLEO-IKS4A1
  - motion sensors: ISM330IS for DIL24 adapter board, LSM6DSO16IS for DIL24 adapter board and onboard for X-NUCLEO-IKS4A1, LIS2MDL for X-NUCLEO-IKS01A3 and X-NUCLEO-IKS4A1, IIS2MDC for X-NUCLEO-IKS02A1

- Several examples of json/ucf pair of files in Ispu folder to show the innovative hardware/software features of ISPU sensors

- Sample applications to upload json/ucf pair of files to ISPU device and transmit real time ISPU, inertial and environmental sensors data to a PC

- Sample applications to use library generated from NEAI Studio and send data to a PC terminal application

- Compatible with the MEMS Studio graphical user interface to display sensors data and configure outputs

- Sample implementation available on X-NUCLEO-IKS4A1, X-NUCLEO-IKS01A3 or X-NUCLEO-IKS02A1 expansion boards connected to a NUCLEO-F401RE or NUCLEO-U575ZI-Q development board with ISPU device onboard or in DIL24 adapter board and on CUSTOM boards with ISPU sensor only

- Easy portability across different MCU families, thanks to STM32Cube architecture and STM32CubeMX tool

- Free, user-friendly license terms

[![The X-CUBE-ISPU package contents](_htmresc/X-CUBE-ISPU_components_2022.png)]()

Here is the list of references to user documents:

- [X-NUCLEO-IKS4A1 SCHEMATIC](https://www.st.com/resource/en/schematic_pack/x-nucleo-iks4a1_schematic.pdf)
- [X-NUCLEO-IKS01A3 SCHEMATIC](https://www.st.com/resource/en/schematic_pack/x-nucleo-iks01a3_schematic.pdf)
- [X-NUCLEO-IKS02A1 SCHEMATIC](https://www.st.com/resource/en/schematic_pack/x-nucleo-iks02a1_schematic.pdf)
- [UM3239 Getting started with the X-NUCLEO-IKS4A1 motion MEMS and environmental sensor expansion board for STM32 Nucleo](https://www.st.com/resource/en/user_manual/um3239-getting-started-with-the-xnucleoiks4a1-motion-mems-and-environmental-sensor-expansion-board-for-stm32-nucleo-stmicroelectronics.pdf)
- [UM2559 Getting started with the X-NUCLEO-IKS01A3 motion MEMS and environmental sensor expansion board for STM32 Nucleo](https://www.st.com/resource/en/user_manual/um2559-getting-started-with-the-xnucleoiks01a3-motion-mems-and-environmental-sensor-expansion-board-for-stm32-nucleo-stmicroelectronics.pdf)
- [UM2633 Getting started with the X-NUCLEO-IKS02A1 industrial motion MEMS sensor expansion board for STM32 Nucleo](https://www.st.com/resource/en/user_manual/um2633-getting-started-with-the-xnucleoiks02a1-industrial-motion-mems-sensor-expansion-board-for-stm32-nucleo-stmicroelectronics.pdf)
