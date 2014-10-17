typedef struct{
	pthread_t thread_tid;
	long thread_count;
}Thread;

Thread* tptr;

#define MAXNCLI 32
int clifd[MAXNCLI], iget, iput;
pthread_mutex_t clifd_mutex;
pthread_cond_t clifd_cond;