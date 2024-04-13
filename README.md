# stm32-cellular-iot

Buildstorm Cellular IoT seamlessly integrates STM32 microcontrollers with Quectel and SIMCOM modems, enabling robust cellular connectivity for IoT applications. This integration offers developers flexibility in hardware selection and streamlines development through a unified environment. With scalability and comprehensive documentation, Buildstorm accelerates time-to-market for IoT projects of all sizes.

The firmware is hosted on the STM32 and communicates with the GSM modem using AT commands. This solution has been built and thoroughly tested on the STM32F407, and it can be easily ported to any other STM32 controllers with a simple configuration change using the STM32 cube IDE.

The software architecture is based on the FreeRTOS kernel, running two tasks: the system task and the application task. The system task handles cellular IoT integration, modem communication, over-the-air (OTA) updates, and logging, while the application task is fully available for user-specific applications and functionalities.

Supported Platforms:
1. [AWS IoT](https://github.com/BuildStormTechnologies/stm32-cellular-iot/tree/stm32-aws-cellular-iot)
2. [Thingsboard IoT](https://github.com/BuildStormTechnologies/stm32-cellular-iot/tree/stm32-thingsboard-cellular-iot)
3. [Kaa IoT](https://github.com/BuildStormTechnologies/stm32-cellular-iot/tree/stm32-kaa-cellular-iot)

Supported Modems:
1. Quectel M95, M66
2. Quectel BG95, BG96, EC200U
3. Simcom SIM7600, A7670E, A7670C, A7670S 
