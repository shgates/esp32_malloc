# ESP32 Memory Allocation

This is an ESP32 code project developed as part of my RTOS (Real-Time Operating Systems) Embedded Systems course. The main objective of this project is to explore memory allocation and concurrent programming concepts on the ESP32 platform. 

## Overview

In this project, we have implemented a system that listens for incoming messages from a serial interface (e.g., UART) and stores them in the heap memory. The received messages are then made available for another task to process. This project serves as an educational example for understanding memory management and multitasking on the ESP32 microcontroller.

## Features

- Listens for incoming messages from a serial interface.
- Allocates memory on the heap to store received messages.
- Uses FreeRTOS to manage concurrent tasks.
- Demonstrates proper memory allocation and deallocation techniques.
- Provides a basic example of task synchronization using semaphores.

## Prerequisites

Before running this code, ensure that you have the following tools and libraries installed:

- [Arduino IDE with ESP32 support](https://www.arduino.cc/en/software)
- [FreeRTOS for ESP32](https://github.com/espressif/arduino-esp32)
- ESP32 development board

## Usage

1. Clone this repository to your local machine.

```bash
git clone https://github.com/your-username/esp32-memory-allocation.git
```

## How It Works
The __xTaskListenAndSend__ task continuously listens for incoming characters on the serial interface. When it receives a complete line (terminated by a '\n'), it allocates memory on the heap and stores the message there. The task then signals the xTaskReceiveMessage task to process the message.

The __xTaskReceiveMessage__ task waits for a signal from xTaskListenAndSend. Once a message is available, it retrieves and processes the message, demonstrating proper memory management.


Feel free to explore, modify, and expand upon this project for your own learning and experimentation.
