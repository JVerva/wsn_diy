
#include "contiki.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(counter_process, "Counter process");
AUTOSTART_PROCESSES(&counter_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(counter_process, ev, data)
{
  static struct etimer timer;
  static int i = 0;

  PROCESS_BEGIN();

  /* Setup a periodic timer that expires after 10 seconds. */
  etimer_set(&timer, CLOCK_SECOND * 2);
  while(1) {
    printf("counter: %d\n",i);
    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
    i++;
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/