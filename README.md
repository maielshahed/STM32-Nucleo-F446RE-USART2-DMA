🔧 Project Description (STM32 Nucleo-F446RE + USART2 + DMA)
This code controls an LED on the STM32 Nucleo-F446RE board using commands sent over USART2 (UART). It uses DMA in circular mode to receive data efficiently without CPU overhead.

⚙️ Features:
Receives '1' to turn the LED ON and '0' to turn it OFF.

Uses DMA for continuous, non-blocking UART reception.

Sends back confirmation messages over UART.

🔄 Workflow:
Configure system clock and initialize SysTick.

Enable GPIOA, USART2, and DMA1.

Set up the following GPIO pins:

PA2 → USART2 TX

PA3 → USART2 RX

PA5 → LED output

Initialize USART2 with 9600 baud rate.

Send an initial message to the UART terminal.

Configure DMA1 Stream5 to receive USART2 data into rx_buffer.

In the main loop:

Continuously check for new data in the buffer.

Toggle the LED according to received characters.

🧪 How to Use:
Using a serial terminal (e.g., PuTTY or TeraTerm):

Send 1 → LED turns ON.

Send 0 → LED turns OFF.

