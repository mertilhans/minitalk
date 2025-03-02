#include <unistd.h>
#include <signal.h>

static void ft_putnbr(int n)
{
    if (n > 9)
        ft_putnbr(n / 10);
    write(1, &"0123456789"[n % 10], 1);
}

void handle_signal(int sig)
{
	static unsigned char msg = 0; 
    static int count = 0;  

    if (sig == SIGUSR1)
        msg |= (1 << (7 - count));  
    count++;

    if (count == 8)
    {
        write(1, &msg, 1); 
        msg = 0;  
        count = 0;  
    }
}

int main(void)
{
	int pid;
	pid = getpid();
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	ft_putnbr(pid);
	write(STDOUT_FILENO , "\n" ,1);
	while(1337)
		pause();
	return 0;
}
