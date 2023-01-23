thread is simply a single stream within a process, may be used to run seperate section of code .

unlike the process, threads are not independent they share the ressources held
by the process(pc, code section, data section,fds, signals) and can communicate with each other easily, but each thread has its own pc and stack space register set.

threading is mainly used to improve the application performance by using parallelism which means multiple threads working simultaneously of diff tasks

to create thread use the func pthread_create that takes 4 args the pointer to p_thread_id var and atts, and function that the thread will run and the args of this func, on success the func assigns the p_thread_id the id of the created thread and returns 0, otherwise an errno will be returned
fail : {
	"attr is invalid";
	"excceeded thread creation number"
}

pthread_join(thread_id, NULL), suspends the execution of the main calling thread until it terminates, on success returns 0;

after threads creation we can not know which thread will enter first its unknown its the OS job and it does it like randomlly sometimes the thread firstly created enter second...


mutex (mutual exclusion) is a cooperative way used between threads to agree that
only one thread can access the data and run a code at a time, used to accomplish the threads sync when they reach critical section of code .for example avoid confusions like wanting a var to be changed inside a thread then passed to second thread but the second thread access it first, race condition...

when a thread mutex a section of obj this mutex will be only accessible and unlockable by that thread and all other threads inside that process wont have the access to that obj data,
to start a mutex mechanism we use pthread_mutex_init, pthread_mutex_lock
the mutex can be unlocked by two ways int pthread_mutex_unlock(pthread_mutex_t *mutex), int pthread_mutex_destroy(pthread_mutex_t *mutex) the first unlock the mutex and give the ability again to mutex for ex if another thread asked to mutex before assign that object the latter destroyes that mutex and 
pthread_mutex_destory will fail if mutex is still locked

gettimeofday (struct timeval val) : stores in the val.tv_sec th num of seconds spent since 
jan 1 1970, the val.tv_usec is a microsecond value 

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

data_objects->tcount = data_objects->tcount_tmp;
	while(data_objects->tcount)
	{
		data_objects->philo[x].pid = pc;
		data_objects->philo[x].iseating = 0;
		data_objects->philo[x].issleeping = 0;
		data_objects->philo[x].isthinking = 0;
		data_objects->philo[x].timetodie = atoi(av[2]);
		data_objects->philo[x].timetoeat = atoi(av[3]);
		data_objects->philo[x].timetosleep = atoi(av[4]);
		if (x == data_objects->tcount_tmp - 1)
		{
			data_objects->philo[x].access.f1 = data_objects->philo[x].pid;
			data_objects->philo[x].access.f2 = 1;
		}
		else
		{
			data_objects->philo[x].access.f1 = data_objects->philo[x].pid;
			data_objects->philo[x].access.f2 = data_objects->philo[x].access.f1 + 1;
		}
		x++;
		pc++;
		data_objects->tcount--;
	}
	x = 0;
	// data_objects->tcount  = data_objects->tcount_tmp;
	// while(data_objects->tcount--)
	// 	data_objects->frep[x++] = 1;
	i = 0;
	data_objects->tcount  = data_objects->tcount_tmp;
	//while(data_objects->philo[x].pid)
	//{
	//	printf("%d", data_objects->philo[x].pid);
	//	x++;
	//}
