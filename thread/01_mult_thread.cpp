#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* cameraThread(void* arg)
{
	printf("camera thread start!!\n\n");
	while (true) {
		printf("camera thread is excuting!!\n");
		sleep(3);
	}

	return nullptr;
}

void* robotThread(void* arg)
{
	printf("robot thread start!!\n\n");
	while (true) {
		printf("robot  thread is excuting!!\n");
		sleep(3);
	}

	return nullptr;
}

int main()
{
	pthread_t camera;
	pthread_t robot;

	pthread_create(&camera, nullptr, cameraThread, nullptr);
	printf("already created cameraThread!!\n");
	pthread_create(&robot, nullptr, robotThread, nullptr);
	printf("already created robotThread\n");

	pthread_join(camera, nullptr);
	pthread_join(robot, nullptr);

	return 0;
}
