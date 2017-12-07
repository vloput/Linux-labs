#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

int points;

void player_1(int sig)
{
    points += rand() % 30;
    printf("Player 1: %i\n", points);
}

void player_2(int sig)
{
    points -= rand() % 30;
    printf("Player 2: %i\n", points);
}

int main(void)
{
    srand(time(0));

    int i = 0;
    points = 0;
    
    while(i++ < 4)
    {
        signal(SIGALRM, player_1);
        raise(SIGALRM);
	    signal(SIGALRM, player_2);
	    raise(SIGALRM);
        puts("");

        sleep(1);
    }

    if(points > 0)
    {
        printf("Player 1 won!\n");
    }
    else if (points < 0)
    {
        printf("Player 2 won!\n");
    }
    else
    {
        printf("Nobody won...\n");
    }

    return 0;
}