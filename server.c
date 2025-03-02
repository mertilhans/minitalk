#include <unistd.h>
#include <signal.h>

static int counter = 0;

static void ft_putnbr(int n)
{
    if (n > 9)
        ft_putnbr(n / 10);
    write(1, &"0123456789"[n % 10], 1);
}

void handle_signal(int sig, siginfo_t *info, void *ucontext)
{
    static unsigned char msg = 0;
    static int count = 0;

    (void)ucontext; 

    if (sig == SIGUSR1)
        msg |= (1 << (7 - count));  
    count++;
    if (count == 8)
    {
        write(1, &msg, 1); 
        msg = 0;  
        count = 0;  
    }
    kill(info->si_pid, SIGUSR1);
}

int main(void)
{
    int pid;
    pid = getpid();
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    ft_putnbr(pid);
    write(STDOUT_FILENO , "\n" ,1);
    while (1)
        pause(); 

    return 0;
}