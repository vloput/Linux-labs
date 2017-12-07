#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int cash;
void client(int sig);
void account(int sig);

void client(int sig)
{
    printf("Bank, what about my account?\n");
    signal(SIGUSR1, account);
    raise(SIGUSR1);
}

void account(int sig)
{
    printf("You have $%i\n", cash);
    cash += cash*0.1;
    sleep(1);
    signal(SIGUSR2, client);
    raise(SIGUSR2);
}

int main(void)
{
    cash = 100;
    signal(SIGUSR2, client);
    raise(SIGUSR2);
    
    return 0;
}