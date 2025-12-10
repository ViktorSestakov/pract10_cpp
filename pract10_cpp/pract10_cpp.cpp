#include <iostream>
#include <Windows.h>
#include <math.h>

using namespace std;

void Inkrement(DWORD ID) {
	int a = 0;
	while (true) {
		a++;
		cout << a << " " << ID << endl;
		Sleep(1000);
	}
}

void Fibonachi(DWORD ID) {
	long long f1 = 0, f2 = 1;
	int iter = 0;
	while (true) {
		int tmp = f1 + f2;
		f1 = f2;
		f2 = tmp;

		iter++;
		cout << iter << " " << ID << endl;
		Sleep(1000);
	}
}

void Kvadraty(DWORD ID) {
	int num = 0, result = 0;
	while (true) {
		result = pow(num, 2);
		num++;

		cout << num << " " << ID << endl;
		Sleep(1000);
	}
}

int main()
{
	setlocale(LC_ALL, "Ru");

	HANDLE IThread, FThread, KThread;
	DWORD IDI = 1, IDF = 2, IDK = 3;

	if (!SetThreadPriority(IThread, THREAD_PRIORITY_NORMAL)) {
		cout << "Failed to set priority to IThread" << endl;
		return GetLastError();
	}
	if (!SetThreadPriority(FThread, THREAD_PRIORITY_BELOW_NORMAL)) {
		cout << "Failed to set priority to FThread" << endl;
		return GetLastError();
	}
	if (!SetThreadPriority(KThread, THREAD_PRIORITY_LOWEST)) {
		cout << "Failed to set priority to KThread" << endl;
		return GetLastError();
	}

	IThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Inkrement, (void*)IDI, 0, &IDI);
	FThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Fibonachi, (void*)IDF, 0, &IDF);
	KThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Kvadraty, (void*)IDK, 0, &IDK);

	if (IThread == 0 || FThread == 0 || KThread == 0)
		return GetLastError();

	WaitForSingleObject(IThread, INFINITE);
	WaitForSingleObject(FThread, INFINITE);
	WaitForSingleObject(KThread, INFINITE);

	int vvod = 0;

	while (true) {
		cin >> vvod;

		switch (vvod)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}
	}
}