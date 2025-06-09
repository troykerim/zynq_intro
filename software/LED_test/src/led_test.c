#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"
#include "xil_printf.h"

/*Definitions*/
#define GPIO_DEVICE_ID XPAR_AXI_GPIO_0_DEVICE_ID  // GPIO device that LEDs are connected to
#define LED 0x9
#define LED_DELAY 10000000
#define LED_CHANNEL 1
#define printf xil_printf

XGpio Gpio;

int LEDOutputExample(void)
{
	volatile int Delay;
	int Status;
	int led = LED;
	Status = XGpio_Initialize(&Gpio, GPIO_DEVICE_ID);
	if(Status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	XGpio_SetDataDirection(&Gpio, LED_CHANNEL, 0x0);
	while(1)
	{
		XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, led);
		led = ~led;
		for(Delay = 0; Delay < LED_DELAY; Delay++);
	}
	return XST_SUCCESS;

}
int main(void)
{
	int Status;
	Status = LEDOutputExample();
	if(Status != XST_SUCCESS)
	{
		xil_printf("GPIO output to the LEDs failed!\r\n");
	}
	return 0;
}
