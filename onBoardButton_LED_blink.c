#include "board.h"

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LEDs state is off */
	Board_LED_Set(0, true);  //RED   LED OFF
	Board_LED_Set(1, true);  //GREEN LED OFF
	Board_LED_Set(2, true);  //BLUE  LED OFF

}

int main()  {

	prvSetupHardware();
	int i=0;

	while(1) {
	bool button_state = false ;
	bool LedState = false;

	if(Buttons_GetStatus()==0x01) {
	  button_state=true ;
	}

	    if(button_state){

			Board_LED_Set(i, LedState); }
			else {
			LedState = (bool) !LedState;
			Board_LED_Set(i, LedState);
			if(i != 2) { i++ ; }
			else { i=0 ; }

			   			       }
	    }

	return 0 ;
}
