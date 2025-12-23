#include <iostream>
#include <Windows.h>
#include <math.h>
#include <time.h>

using namespace std;

volatile long long iter[4]{0,0,0,0};

void Inkrement() {
	int a = 0;
	while (true) {
		a++;

		iter[0]++;
	}
}

void Fibonachi() {
	long long f1 = 0, f2 = 1;
	while (true) {
		long long tmp = f1 + f2;
		f1 = f2;
		f2 = tmp;

		iter[1]++;
	}
}

void Kvadraty() {
	double num = 0, result = 0;
	while (true) {
		result = pow(num, 2);
		num++;

		iter[2]++;
	}
}

void Nagruzchik() {
	int a = 0;
	while (true) {
		a++;

		iter[3]++;
	}
}

HANDLE threads[4];
DWORD ids[4];

void Seeker(HANDLE thread, DWORD id) {
	SuspendThread(thread);
	if (id == ids[0]) {
		cout << iter[0];
		iter[0] = 0;
	}
	else if (id == ids[1]) {
		cout << iter[1];
		iter[1] = 0;
	}
	else if (id == ids[2]) {
		cout << iter[2];
		iter[2] = 0;
	}
	ResumeThread(thread);
}

void menu_vibor() {
	int vibor;
	bool konec = false;

	while (!konec) {
		cin >> vibor;

		switch (vibor)
		{
		case 1:
			if (!SetThreadPriority(threads[0], THREAD_PRIORITY_LOWEST)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			break;
		case 2:
			if (!SetThreadPriority(threads[1], THREAD_PRIORITY_LOWEST)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			break;
		case 3:
			if (!SetThreadPriority(threads[2], THREAD_PRIORITY_LOWEST)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			break;
		case 4:
			if (!SetThreadPriority(threads[0], THREAD_PRIORITY_NORMAL)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			break;
		case 5:
			if (!SetThreadPriority(threads[1], THREAD_PRIORITY_NORMAL)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			break;
		case 6:
			if (!SetThreadPriority(threads[2], THREAD_PRIORITY_NORMAL)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			break;
		case 7:
			if (!SetThreadPriority(threads[0], THREAD_PRIORITY_ABOVE_NORMAL)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			break;
		case 8:
			if (!SetThreadPriority(threads[1], THREAD_PRIORITY_ABOVE_NORMAL)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			break;
		case 9:
			if (!SetThreadPriority(threads[2], THREAD_PRIORITY_ABOVE_NORMAL)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			break;
		case 0:
			threads[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Nagruzchik, NULL, 0, &ids[3]);
			if (!SetThreadPriority(threads[3], THREAD_PRIORITY_HIGHEST)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			if (!SetThreadPriorityBoost(threads[3], FALSE)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
			break;
		case 10:
			if (!TerminateThread(threads[0], 0)) cout << GetLastError() << endl;
			if (!TerminateThread(threads[1], 0)) cout << GetLastError() << endl;
			if (!TerminateThread(threads[2], 0)) cout << GetLastError() << endl;
			if (!TerminateThread(threads[3], 0)) cout << GetLastError() << endl;
			system("cls");
			konec = true;
			break;
		default:
			cout << "Не правильно выбран пункт!" << endl;
			break;
		}
	}
}

void menu() {
	HANDLE thread;

	thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)menu_vibor, NULL, 0, NULL);

	while (true) {
		Sleep(1000);
		system("cls");

		if (iter[3] > (iter[2] + iter[1] + iter[0])) {
			if (!SetThreadPriority(threads[3], THREAD_PRIORITY_NORMAL)) {
				cout << "Failed to set priority to Thread" << endl;
				cout << GetLastError() << endl;
			}
		}

		cout << "Кол-во итераций в секундну" << endl;
		cout << "Поток 1 - инкремент: ";
		Seeker(threads[0], ids[0]);
		cout << " | Приоритет = " << GetThreadPriority(threads[0]) << endl;
		iter[0] = 0;
		cout << "Поток 2 - последовательность фибоначчи: ";
		Seeker(threads[1], ids[1]);
		cout << " | Приоритет = " << GetThreadPriority(threads[1]) << endl;
		iter[1] = 0;
		cout << "Поток 3 - последовательность квадратов: ";
		Seeker(threads[2], ids[2]);
		cout << " | Приоритет = " << GetThreadPriority(threads[2]) << endl;
		iter[2] = 0;

		cout << endl;
		if (GetThreadPriority(threads[3]) == 2 || GetThreadPriority(threads[3]) == 0) {
			cout << "Нагрузчик | Приоритет = " << GetThreadPriority(threads[3]) << endl;
			iter[3] = 0;
		}
		else {
			cout << "Нагрузчик | Приоритет = неактивен" << endl;
			iter[3] = 0;
		}
		cout << endl;

		cout << "Меню:" << endl;
		cout << "1. Сменить приоритет потока 1 - минимальный" << endl;
		cout << "2. Сменить приоритет потока 2 - минимальный" << endl;
		cout << "3. Сменить приоритет потока 3 - минимальный" << endl;
		cout << endl;
		cout << "4. Сменить приоритет потока 1 - нормальный" << endl;
		cout << "5. Сменить приоритет потока 2 - нормальный" << endl;
		cout << "6. Сменить приоритет потока 3 - нормальный" << endl;
		cout << endl;
		cout << "7. Сменить приоритет потока 1 - выше нормального" << endl;
		cout << "8. Сменить приоритет потока 2 - выше нормального" << endl;
		cout << "9. Сменить приоритет потока 3 - выше нормального" << endl;
		cout << endl;
		cout << "0. Запустить нагрузчик" << endl;
		cout << "10. Выйти из программы" << endl;
		cout << endl;
		cout << "Введите номер пункта: ";
	}
}

int main()
{
	setlocale(LC_ALL, "Ru");

	threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Inkrement, NULL, 0, &ids[0]);
	threads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Fibonachi, NULL, 0, &ids[1]);
	threads[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Kvadraty, NULL, 0, &ids[2]);

	if (threads[0] == 0 || threads[1] == 0 || threads[2] == 0) {
		return GetLastError();
	} else {
		if (!SetThreadPriority(threads[0], THREAD_PRIORITY_NORMAL)) {
			cout << "Failed to set priority to Thread-1" << endl;
			return GetLastError();
		}
		if (!SetThreadPriority(threads[1], THREAD_PRIORITY_BELOW_NORMAL)) {
			cout << "Failed to set priority to Thread-2" << endl;
			return GetLastError();
		}
		if (!SetThreadPriority(threads[2], THREAD_PRIORITY_ABOVE_NORMAL)) {
			cout << "Failed to set priority to Thread-3" << endl;
			return GetLastError();
		}
	}

	HANDLE thread;

	thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)menu, NULL, 0, NULL);

	WaitForSingleObject(threads[0], INFINITE);
	WaitForSingleObject(threads[1], INFINITE);
	WaitForSingleObject(threads[2], INFINITE);
	WaitForSingleObject(threads[3], INFINITE);

	return 0;
}
