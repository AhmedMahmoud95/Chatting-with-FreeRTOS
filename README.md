# Chatting-with-FreeRTOS
This project shows a simple application of FreeRTOS to manage system tasks.
The shown project is a chatting application where 2 microcontrollers can sen messages to each other.
Each MCU has an LCD, a Keypad, a push button, and 2 LEDs. The same .hex file is attached to both boards.
If board A wishes to send a message to board B, the message is entered using the jeypad attached to it and the input is shown on the first line of the LCD. Once the message is complete, we press the push button.
At this moment, the message is send through UART, the message appears on the second line on the reciever LCD, LED1 on the sender becomes ON for 200 ms and LED2 on the receiver becomes ON for a 1000ms.
The message dissapears from the sender and receiver LCDs after 2000ms from pressing the push button. 
