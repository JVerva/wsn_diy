#include "contiki.h"
#include "dev/light-sensor.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  static int state = 0;
  static int val = 0;
  static int thresh = 100;

  PROCESS_BEGIN();
  SENSORS_ACTIVATE(light_sensor);
  while(1) {
    //range between 0-4095
    val = light_sensor.value(LIGHT_SENSOR_TOTAL_SOLAR);
    if (val < thresh && state == 0){
      printf("button pressed\n");
      state = 1;
    }else if (val >= thresh && state == 1){
      printf("button released\n");
      state = 0;
    }
    PROCESS_PAUSE();
  }
  SENSORS_DEACTIVATE(light_sensor);
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/