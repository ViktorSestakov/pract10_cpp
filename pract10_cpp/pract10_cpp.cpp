#include <iostream>
#include <Windows.h>
#include <math.h>
#include <time.h>

using namespace std;

int iter[3]{0,0,0};
bool iter_kon = false;


void Inkrement() {
	int a = 0;
	while (true) {
		a++;

		if (!iter_kon) {
			iter[0]++;
		}
	}
}

void Fibonachi() {
	long long f1 = 0, f2 = 1;
	while (true) {
		long long tmp = f1 + f2;
		f1 = f2;
		f2 = tmp;

		if (!iter_kon) {
			iter[1]++;
		}
	}
}

void Kvadraty() {
	int num = 0, result = 0;
	while (true) {
		result = pow(num, 2);
		num++;

		if (!iter_kon) {
			iter[2]++;
		}
	}
}

HANDLE threads[3];
DWORD ids[3];

void Seeker(HANDLE thread, DWORD id) {
	SuspendThread(thread);
	if (id == ids[0]) {
		cout << iter[0] << endl;
		iter[0] = 0;
	}
	else if (id == ids[1]) {
		cout << iter[1] << endl;
		iter[1] = 0;
	}
	else if (id == ids[2]) {
		cout << iter[2] << endl;
		iter[2] = 0;
	}
	ResumeThread(thread);
}

int main()
{
	setlocale(LC_ALL, "Ru");

	threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Inkrement, NULL, 0, &ids[0]);
	threads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Fibonachi, NULL, 0, &ids[1]);
	threads[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Kvadraty, NULL, 0, &ids[2]);

	if (!SetThreadPriority(threads[0], THREAD_PRIORITY_NORMAL)) {
		cout << "Failed to set priority to IThread" << endl;
		return GetLastError();
	}
	if (!SetThreadPriority(threads[1], THREAD_PRIORITY_BELOW_NORMAL)) {
		cout << "Failed to set priority to FThread" << endl;
		return GetLastError();
	}
	if (!SetThreadPriority(threads[2], THREAD_PRIORITY_LOWEST)) {
		cout << "Failed to set priority to KThread" << endl;
		return GetLastError();
	}

	if (threads[0] == 0 || threads[1] == 0 || threads[2] == 0)
		return GetLastError();

	Sleep(1000);
	Seeker(threads[0], ids[0]);
	Seeker(threads[1], ids[1]);
	Seeker(threads[2], ids[2]);
	iter_kon = true;

	TerminateThread(threads[0], 0);
	TerminateThread(threads[1], 0);
	TerminateThread(threads[2], 0);

	WaitForSingleObject(threads[0], INFINITE);
	WaitForSingleObject(threads[1], INFINITE);
	WaitForSingleObject(threads[2], INFINITE);
}
