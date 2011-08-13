#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "cycle.h"

void *thread_func(void *) {
	pthread_exit(NULL);
}

double test_threads() {
	const int Iterations = 10000;
	pthread_t thread;
	int status;
	
	unsigned long long start = getticks();
	for(int i=0; i < Iterations; i++) {
		pthread_create(&thread, NULL, thread_func, NULL);
		pthread_join(thread, (void **)&status);
	}
	unsigned long long end = getticks();
	return double(end-start)/Iterations;
}

double test_procs() {
	const int Iterations = 10000;
	pid_t pid;
	int status;
	
	unsigned long long start = getticks();
	for(int i=0; i < Iterations; i++) {
		pid = fork();
		if(pid == 0) {
			exit(0);
		}
		else {
			waitpid(pid, &status, 0);
		}
	}
	unsigned long long end = getticks();
	return double(end-start)/Iterations;
}

int main() {
	using namespace std;
	
	cout.flags(ios::fixed | ios::showpoint);
	cout.precision(2);
	
	double thread_time = test_threads();
	cout << "Threads: " << thread_time << endl;
	
	double proc_time = test_procs();
	cout << "Processes" << proc_time << endl;
	
	return 0;
}
