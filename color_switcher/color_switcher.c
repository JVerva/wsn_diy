#include "contiki.h"
#include "leds.h"
#include "dev/button-sensor.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  static int counter = 0;

  PROCESS_BEGIN();
  //Base state
  leds_off(LEDS_ALL);
  SENSORS_ACTIVATE(button_sensor);
  while(1) {
    PROCESS_WAIT_EVENT();
    if(ev == sensors_event && data == &button_sensor) {
        printf("button pressed\n");
        if(counter == 3){
            counter = 0;
        }else{
            counter++;
        }
        switch (counter)
        {
        case 1:
            leds_off(LEDS_ALL);
            leds_on(LEDS_RED);
            break;
        case 2:
            leds_off(LEDS_ALL);
            leds_on(LEDS_GREEN);
        case 3:
            leds_off(LEDS_ALL);
            leds_on(LEDS_BLUE);
        default:
            leds_off(LEDS_ALL);
            break;
        }
    }
  }
  SENSORS_DEACTIVATE(button_sensor);
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/