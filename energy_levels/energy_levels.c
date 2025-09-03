
#include "sys/energest.h"
#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(energy_levels_process, "energy_levels process");
AUTOSTART_PROCESSES(&energy_levels_process);
/*---------------------------------------------------------------------------*/

static unsigned long to_seconds(uint64_t t) {
  return (unsigned long)(t / ENERGEST_SECOND);
}

PROCESS_THREAD(energy_levels_process, ev, data) {
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 2);
  while(1) {
    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

    /* Update all energest times. */
    energest_flush();
    /* Print out all energest times. */
    printf("\nEnergest:\n");
    printf(" CPU          %4lus LPM      %4lus DEEP LPM     %4lus TOTAL     %4lus\n",
           to_seconds(energest_type_time(ENERGEST_TYPE_CPU)),
           to_seconds(energest_type_time(ENERGEST_TYPE_LPM)),
           to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM)),
           to_seconds(ENERGEST_GET_TOTAL_TIME()));

    /* Reset timer. */
    etimer_reset(&timer);
  }

  PROCESS_END();

}
/*---------------------------------------------------------------------------*/