## 1 - Introduction

This is a template for validating on target (that is, on the ISPU) the code generated by [ST Edge AI Core](https://www.st.com/en/development-tools/stedgeai-core.html), a tool that can be used to convert neural network models into implementations optimized for the ISPU.

The *ispu* folder of the template may be copied by itself (no dependencies other than the CLI toolchain or IDE environment that must be installed) and used to build the application running the model on the ISPU to perform the validation.


## 2 - Host board firmware

Validation on target with ST Edge AI Core requires flashing the firmware on the host board, which acts as a bridge between the user's PC and the ISPU. The firmware for the user's specific hardware setup can be found in the *host_firmware/nucleo_ispu_stedgeai_validate* folder of ST's GitHub repository for ISPU ([https://github.com/STMicroelectronics/st-mems-ispu](https://github.com/STMicroelectronics/st-mems-ispu)).

For information on the supported hardware and how to set it up, refer to the readme file of the firmware.


## 3 - Model implementation generation and build

The validation template project is structured so that ST Edge AI Core can automatically populate it with the necessary files in the right places. In order to achieve that, run the following command:

```shell
stedgeai generate --target ispu --no-workspace --no-report -m <nn_model_file> --output <ispu_folder>
```

where `nn_model_file` is the file containing the model of the neural network to convert and `ispu_folder` is a copy of the *ispu* folder of this template. Of course, additional options can be added to the `generate` command above as needed.

The validation application can then be built just like any other ISPU project using the Makefile or the Eclipse project. Note that no modification to the project source files is required.


## 4 - Validation run

Once the validation application has been built, in order to perform the validation on target, run the following command:

```shell
stedgeai validate --target ispu -m <nn_model_file> --target ispu --mode target --ucf <path_to_ucf>
```

where `nn_model_file` is the file containing the model of the neural network to validate and `path_to_ucf` is the path to the UCF just generated with the build of the validation application. If additional options to modify the converted model were specified in the `generate` command, they should be specified again here.

Note 1: By default, the UCF file is generated as *ispu/make/bin/ispu.ucf* if using the Makefile and as *ispu/eclipse/release/ispu.ucf* if using the Eclipse project.

Note 2: By default, the validation is performed with the ISPU clock configured at 5 MHz. To validate with the ISPU clock at 10 MHz, it is sufficient to modify the clock configuration in *ispu/conf.txt*.

------

**More Information: [http://www.st.com](http://st.com/MEMS)**

**Copyright © 2024 STMicroelectronics**