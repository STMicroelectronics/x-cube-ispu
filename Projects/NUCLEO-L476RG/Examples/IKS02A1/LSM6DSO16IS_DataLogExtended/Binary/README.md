## __Binary Folder Description__

In this folder, compiled image of the firmware is provided, in order to allow the user to test the application in a quick and easy way.


### __Keywords__

  - BIN


### __Directory contents__

  - \<Project\>.bin - binary file to be directly downloaded to corresponding HW


### __Hardware and Software environment__

  - Install [ST-LINK drivers](http://www.st.com/web/en/catalog/tools/FM146/CL1984/SC720/SS1450/PF251168)
  - On the Nucleo board put JP5 jumper in U5V position


### __How to use it?__

The binary is provided in .bin format and can be flashed into the micro-controller flash memory using the procedure described below:

  1. Plug the Nucleo Board to the host PC using a mini USB cable. If the ST-LINK driver is correctly installed, it will be recognized as an external memory device called "NUCLEO"
  2. Drag and drop or copy the binary file into the "NUCLEO" device you see in Computer
  3. Wait until flashing is complete.
