#include <stdio.h>

int main(void)
{
	for (int i = 0; i < 100; i++){
		printf("NEW OUTPUT\n");
		system("./philo 4 100 100 100");
	}
}