#include "time2.h"

void time_print(enum print_type type, int ticks)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    blk_begin();

    prop_begin(PROP_FULL_TEXT);
    printf("\"TIME %02d:%02d:%02d %02d.%02d.%02d\"", tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    prop_end(LAST);

    blk_end(type);
}


