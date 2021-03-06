#include "global.h"

#include "battery.h"
#include "time2.h"
#include "cpu.h"
#include "ram.h"
#include "io.h"

struct sigaction sig_handler;
int running = 1;
int ticks   = 0;

void handler(int signal)
{
    switch(signal)
    {
	
    case SIGSTOP:
    {
	running = 0;
	break;
    }
    
    case SIGCONT: break;
	
    }
}

int main(void)
{    
    // signal handler
    sig_handler.sa_handler = handler;
    sig_handler.sa_flags   = SA_RESTART;
    sigfillset(&sig_handler.sa_mask);
    sigaction(SIGSTOP, &sig_handler, NULL);
    sigaction(SIGCONT, &sig_handler, NULL);    

    // tick time
    struct timespec time;
    time.tv_sec  = 0;
    time.tv_nsec = 150000000;    
    
    printf("{\"version\":1}");
    
    line_begin();
    while(running)
    {
	line_begin();
	
	// BEGIN

	time_print(NOT_LAST, ticks);
	ram_print(NOT_LAST, ticks);
	cpu_print(NOT_LAST, ticks);
	battery_print(LAST, ticks);

	// END

	line_end(NOT_LAST);	
	fflush(stdout);
	
	ticks++;
	nanosleep(&time, NULL);
    }
    line_end(LAST);
	
    return 0;
}
