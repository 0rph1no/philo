#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/time.h>

typedef struct locks
{
	int i;
	pthread_mutex_t *fork;
	int tcount;
}locks;

pthread_mutex_t mutex;

typedef struct philo
{
	int ttd;
	int id;
	int tte;
	int tts;
	int left;
	int right;
	long long lm;
	long long start;
	locks *lock;
}philo;

long long get_real_time()
{
	struct timeval current;
	long long ret;
	ret = 0;
	gettimeofday(&current, NULL);
	ret+=(current.tv_sec * 1000);
	ret+=(current.tv_usec / 1000);
	return ret;
}

typedef struct threads
{
	int i;
	pthread_t *id;
}threads;

void *doprint(void *data)
{
	philo *philosopher = (philo *)data;
	philosopher->start = get_real_time();
	//printf("{%d--%d---%d}\n", philosopher->id,philosopher->left,philosopher->right);
	if (philosopher->id % 2 == 0)
		usleep(100);
	while(1)
	{
		pthread_mutex_lock(&philosopher->lock->fork[philosopher->right]);
		printf("Philos %d has picked a fork\n", philosopher->id);
		pthread_mutex_lock(&philosopher->lock->fork[philosopher->left]);
		printf("Philos %d has picked another fork\n", philosopher->id);
		printf("Philos %d is eating\n", philosopher->id);
		usleep(philosopher->tte);
		philosopher->lm = get_real_time();
		printf("time to die counted : %lld\n", philosopher->lm);
		printf("Philos %d is sleeping\n", philosopher->id);
		printf("Philos %d is thinking\n", philosopher->id);
		pthread_mutex_unlock(&philosopher->lock->fork[philosopher->left]);
		pthread_mutex_unlock(&philosopher->lock->fork[philosopher->right]);
		usleep(100);

	}
	return NULL;
	//eating(philosopher->id);
	//sleeping(philosopher->id);
	//thinking(philosopher->id);

}


void handle_all(char **av, int count, philo *philosopher, locks *lock)
{
	threads *thread;
	int i;
	
	thread = malloc(sizeof(threads));
	thread->id = malloc(sizeof(pthread_t) * count);
	i = 0;
	while(i < count)
	{
		pthread_mutex_init(&philosopher->lock->fork[i], NULL);
		i++;
	}
	i = 0;
	while(i < count)
	{
		philosopher[i].id = i + 1;
		philosopher[i].lm = 0;
		philosopher[i].lock = philosopher->lock;
		philosopher[i].ttd = atoi(av[2]);
		philosopher[i].tte = atoi(av[3]);
		philosopher[i].tts = atoi(av[4]);
		philosopher[i].right = philosopher[i].id;
		if (i == count - 1)
			philosopher[i].left = 1;
		else
			philosopher[i].left = philosopher[i].id + 1;
		i++;
	}
	i = 0;
	while(i < count)
	{
		pthread_create(&thread->id[i], NULL, doprint, &philosopher[i]);
		i++;
	}
	//printf("fsfsd\n");
	i = 0;
	while(i < count)
	{
		pthread_join(thread->id[i], NULL);
		i++;
	}
	i = 0;
	while(i < count)
	{
		pthread_mutex_destroy(&philosopher->lock->fork[i]);
		i++;
	}
}

int main(int ac, char **av)
{
	struct timeval current;
	//printf("time elapsed since the beg of this earth %lld\n", rt);
	locks *lock;
	int count = atoi(av[1]);
	philo *philosopher;
	philosopher = (philo *)malloc(sizeof(philo) * count);
	//lock = malloc(sizeof(locks));
	philosopher->lock = (locks *)malloc(sizeof(locks));
	philosopher->lock->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (count + 1));
	if (philosopher->lock->fork==NULL)
		perror("malloc");
	
	handle_all(av, count, philosopher, lock);
}