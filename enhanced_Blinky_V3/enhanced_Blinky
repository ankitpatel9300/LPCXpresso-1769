#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED_ON  0
#define LED_OFF 1

//Global variables
uint8_t RED_LED = 0;
uint8_t GREEN_LED = 1;
uint8_t BLUE_LED = 2;
volatile unsigned int period = 1;

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LEDs state is off */
	Board_LED_Set(0, LED_OFF);
	Board_LED_Set(1, LED_OFF);
	Board_LED_Set(2, LED_OFF);
}

/* LED toggle thread */
static void vLED_ToggleTask(void *pvParameters)
{
	portTickType xLastWakeTime = xTaskGetTickCount();
	const portTickType xDelay125ms = portTICK_RATE_MS * 125;
	uint8_t LED_Number = *(uint8_t*) pvParameters;

	while (1)
	{

		if (LED_Number == 0)
		{
			Board_LED_Set(LED_Number, LED_ON);       // LED on for 0.125 Second
			vTaskDelayUntil(&xLastWakeTime, xDelay125ms * period);
			Board_LED_Set(LED_Number, LED_OFF);      // LED off for 0.250 Second
			vTaskDelayUntil(&xLastWakeTime, xDelay125ms * 5 * period);
		}
		if (LED_Number == 1)
		{
			vTaskDelayUntil(&xLastWakeTime, xDelay125ms * 2 * period);
			Board_LED_Set(LED_Number, LED_ON);       // LED on for 0.125 Second
			vTaskDelayUntil(&xLastWakeTime, xDelay125ms * period);
			Board_LED_Set(LED_Number, LED_OFF);      // LED off for 0.250 Second
			vTaskDelayUntil(&xLastWakeTime, xDelay125ms * 3 * period);
		}
		if (LED_Number == 2)
		{

			vTaskDelayUntil(&xLastWakeTime, xDelay125ms * 4 * period);
			Board_LED_Set(LED_Number, LED_ON);       // LED on for 0.125 Second
			vTaskDelayUntil(&xLastWakeTime, xDelay125ms * period);
			Board_LED_Set(LED_Number, LED_OFF);      // LED off for 0.250 Second
			vTaskDelayUntil(&xLastWakeTime, xDelay125ms * period);
		}
	}
}

static void vButton_StatusTASK(void *pvParameters)
{

	portTickType xLastWakeTime = xTaskGetTickCount();
	const portTickType xButtonDelay_ms = portTICK_RATE_MS * 125;

	while (1)
	{

		vTaskDelayUntil(&xLastWakeTime, xButtonDelay_ms * period);

		if (UP_Button_GetStatus() == 0X01)
		{
			period += 1;

		}
		else if (DOWN_Button_GetStatus() == 0X01)
		{
			period -= 1;
		}
		vTaskDelayUntil(&xLastWakeTime, xButtonDelay_ms * 4 * period);
	}

}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

int main(void)
{
	prvSetupHardware();

	/* RED toggle thread */
	xTaskCreate(vLED_ToggleTask, (signed char* ) "vTaskLed1",
			configMINIMAL_STACK_SIZE, (void* )&RED_LED,
			(tskIDLE_PRIORITY + 4UL), (xTaskHandle *) NULL);

	/* GREEN toggle thread */
	xTaskCreate(vLED_ToggleTask, (signed char* ) "vTaskLed2",
			configMINIMAL_STACK_SIZE, (void* )&GREEN_LED,
			(tskIDLE_PRIORITY + 3UL), (xTaskHandle *) NULL);
	/* BLUE toggle thread */
	xTaskCreate(vLED_ToggleTask, (signed char* ) "vTaskLed3",
			configMINIMAL_STACK_SIZE, (void* )&BLUE_LED,
			(tskIDLE_PRIORITY + 2UL), (xTaskHandle *) NULL);
	/* BUTTON Status check  thread */
	xTaskCreate(vButton_StatusTASK, (signed char* ) "vTaskButton",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
