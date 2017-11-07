#include "mcal_uart.h"
#include "ring_buff.h"


#define HAL_CRITICAL_SECTION


//TODO: It should be only pointer to real implementation
//TODO: Add CRITICAL_SECTION, it should also point to real implementation.
void HAL_UART_IRQHandler(void) {

	// Example condition
	/* Check are data received, clear irq flags etc */
	/*FIXME removed in this stage of implementation
	if (USART2->SR & USART_SR_RXNE)
	{
		RB_PutByte(uint8_t c);
	}
	*/
}

