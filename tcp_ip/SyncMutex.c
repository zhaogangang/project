#include <stdio.h>
#include <Windows.h>
#include <process.h>

#define NUM_THREAD 50
unsigned WINAPI threadInc(void *arg);
unsigned WINAPI threadDes(void *arg);

long long num = 0;
HANDLE hMutex;

int main(int argc, char *argv[])
{
	HANDLE tHandles[NUM_THREAD];

	hMutex = CreateMutex(NULL, FALSE, NULL);
	for (int i = 0; i < NUM_THREAD; ++i) {
		if (i & 1)
			tHandles[i] = (HANDLE)_beginthreadex(NULL, 0, threadInc, NULL, 0, NULL);
		else
			tHandles[i] = (HANDLE)_beginthreadex(NULL, 0, threadDes, NULL, 0, NULL);
	}
	WaitForMultipleObjects(NUM_THREAD, tHandles, TRUE, INFINITE);
	CloseHandle(hMutex);
	printf("result: %lld \n", num);
	system("pause");
	return 0;
}

unsigned WINAPI threadInc(void *arg) {
	WaitForSingleObject(hMutex, INFINITE);
	for (int i = 0; i < 5000000; ++i)
		num += 1;
	ReleaseMutex(hMutex);
	return 0;
}
unsigned WINAPI threadDes(void *arg) {
	WaitForSingleObject(hMutex, INFINITE);
	for (int i = 0; i < 5000000; ++i)
		num -= 1;
	ReleaseMutex(hMutex);
	return 0;
}

	
