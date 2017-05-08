#include "cpu.h"

float total_prev, total_idle_prev = 0.0f;

void cpu_print(enum print_type type, int ticks)
{
    long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;

    FILE* file = fopen("/proc/stat", "r");
    if(file == NULL) goto cpu_print_error;
    if(fscanf(file, "cpu  %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld\n"
	      , &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice) != 10)
	goto cpu_print_error;
    fclose(file);

    long total = user + nice + system + idle + iowait + irq + softirq + steal;
    long total_idle = idle + iowait;

    long total_diff = total - total_prev;
    long total_idle_diff = total_idle - total_idle_prev;

    float cpu_usage = ((float)(total_diff - total_idle_diff)/(float)total_diff) * 100.0f;
    
    total_prev = total;
    total_idle_prev = total_idle;
    
    blk_begin();

    if(cpu_usage > 90)
    {
	prop_begin(PROP_COLOR);
	printf("\"%s\"", color_string(COLOR_RED));
	prop_end(NOT_LAST);
    }
    
    prop_begin(PROP_FULL_TEXT);
    printf("\"CPU %6.2f%%\"", cpu_usage);
    prop_end(LAST);
    blk_end(type);

    return;
    
cpu_print_error:;

    blk_begin();
    
    prop_begin(PROP_FULL_TEXT);
    printf("\"CPU ???.??%%\"");
    prop_end(LAST);

    blk_end(type);
}
