#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

time_t curtime;
struct tm* loctime;

void sigalrm_handler_1(int sig)
{
    curtime = time(0);
    loctime = localtime(&curtime);
    puts("First handler:");
    fputs(asctime(loctime), stdout);
}

void sigalrm_handler_2(int sig)
{
    curtime = time(0);
    loctime = localtime(&curtime);
    puts("Second handler:");
    fputs(asctime(loctime), stdout);
}

int main(void)
{
    int i = 0;
    
    while(i++ < 4)
    {
        signal(SIGALRM, sigalrm_handler_1);
        raise(SIGALRM);
	    signal(SIGALRM, sigalrm_handler_2);
	    raise(SIGALRM);
        puts("");

        sleep(1);
    }

    return 0;
}