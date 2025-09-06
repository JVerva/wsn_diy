#include <contiki.h>
#include <stdio.h>

/*---------------------------------------------------------------------------*/
PROCESS(fixed_point_arithmetic_process, "fixed_point_arithmetic process");
AUTOSTART_PROCESSES(&fixed_point_arithmetic_process);
/*---------------------------------------------------------------------------*/

void print_fixed_point(uint16_t x) {
    uint16_t integer_part = x >> 4;
    uint16_t fractional_part = x & 0x0F;
    printf("%u.%u\n", integer_part, fractional_part * 625);
}

PROCESS_THREAD(fixed_point_arithmetic_process, ev, data) {
    uint16_t a = 0x0025; //2.3 in Q12.4
    uint16_t b = 0x007D; //7.8 in Q12.4

    uint16_t c[256];

    PROCESS_BEGIN();

    for (uint16_t i=0; i<256; i++) {
        uint16_t i_fp = i << 4; //i in Q12.4
        c[i]=((a+i_fp)*b) >> 4; //(a+i)*b in Q24.8, convert to Q12.4
        printf("%hu\n", c[i]);
    }

    PROCESS_END();

};