#include "board.h"
#include "FreeRTOS.h"
#include "task.h"


/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LEDs state is off */
	Board_LED_Set(0, true);
	Board_LED_Set(1, true);
	Board_LED_Set(2, true);
}

/* RED toggle thread */
static void vLEDTask1(void *pvParameters) {

        while (1) {
		const portTickType xDelay500ms = 500/portTICK_RATE_MS;
		Board_LED_Set(0,false);
		vTaskDelay(xDelay500ms);     // RED LED on for 0.5 Second
		Board_LED_Set(0,true);      //RED LED off for 1 Second
		vTaskDelay(xDelay500ms);
		vTaskDelay(xDelay500ms);
	}
}
/* GREEN toggle thread */
static void vLEDTask2(void *pvParameters) {
	    const portTickType xDelay500ms = 500/portTICK_RATE_MS;
	    vTaskDelay(xDelay500ms);
        while (1) {

		Board_LED_Set(1, false );
		vTaskDelay(xDelay500ms);      // GREEN LED on for 0.5 Second

		Board_LED_Set(1,true);       // GREEN LED off for 1 Second
		vTaskDelay(xDelay500ms);
		vTaskDelay(xDelay500ms);
	}
}
/* BLUE toggle thread */
static void vLEDTask3(void *pvParameters) {
	    const portTickType xDelay500ms = 500/portTICK_RATE_MS;
	    vTaskDelay(xDelay500ms);
	    vTaskDelay(xDelay500ms);
        while (1) {

		Board_LED_Set(2,false );
		vTaskDelay(xDelay500ms);     // BLUE LED on for 0.5 Second

		Board_LED_Set(2,true);      // BLUE LED off for 0.5 Second
		vTaskDelay(xDelay500ms);
		vTaskDelay(xDelay500ms);
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	prvSetupHardware();

	/* RED toggle thread */
	xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
				(xTaskHandle *) NULL);

	/* GREEN toggle thread */
	xTaskCreate(vLEDTask2, (signed char *) "vTaskLed2",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
				(xTaskHandle *) NULL);
	/* BLUE toggle thread */
		xTaskCreate(vLEDTask3, (signed char *) "vTaskLed3",
					configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
					(xTaskHandle *) NULL);

		/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
