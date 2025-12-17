#include <iostream>
#include <Windows.h>
#include <math.h>
#include <time.h>

using namespace std;

int iter[3]{0,0,0};

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

HANDLE threads[4];
DWORD ids[4];

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

void change_priority(HANDLE thread) {
	int vibor;

	cout << "Выберите приоритет: " << endl;
	cout << "1. Низший" << endl;
	cout << "2. Ниже нормального" << endl;
	cout << "3. Нормальный" << endl;
	cout << "4. Выше нормального" << endl;
	cout << "5. Высший" << endl;
	cout << "Выберите пункт: ";

	cin >> vibor;

	switch (vibor)
	{
	case 1:
		if (!SetThreadPriority(thread, THREAD_PRIORITY_LOWEST)) {
			cout << "Failed to set priority to Thread" << endl;
			cout << GetLastError() << endl;
		}
		system("cls");
		break;
	case 2:
		if (!SetThreadPriority(thread, THREAD_PRIORITY_BELOW_NORMAL)) {
			cout << "Failed to set priority to Thread" << endl;
			cout << GetLastError() << endl;
		}
		system("cls");
		break;
	case 3:
		if (!SetThreadPriority(thread, THREAD_PRIORITY_NORMAL)) {
			cout << "Failed to set priority to Thread" << endl;
			cout << GetLastError() << endl;
		}
		system("cls");
		break;
	case 4:
		if (!SetThreadPriority(thread, THREAD_PRIORITY_ABOVE_NORMAL)) {
			cout << "Failed to set priority to Thread" << endl;
			cout << GetLastError() << endl;
		}
		system("cls");
		break;
	case 5:
		if (!SetThreadPriority(thread, THREAD_PRIORITY_HIGHEST)) {
			cout << "Failed to set priority to Thread" << endl;
			cout << GetLastError() << endl;
		}
		system("cls");
		break;
	default:
		cout << "Не правильно выбран пункт!" << endl;
		break;
	}

	cout << "Приоритет изменен!" << endl;
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "Ru");

	threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Inkrement, NULL, 0, &ids[0]);
	threads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Fibonachi, NULL, 0, &ids[1]);
	threads[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Kvadraty, NULL, 0, &ids[2]);
	threads[3] = CreateThread(NULL, 0, NULL, NULL, 0, &ids[3]); // доделать нагрузчик

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
		if (!SetThreadPriority(threads[3], THREAD_PRIORITY_LOWEST)) {
			cout << "Failed to set priority to Thread-4" << endl;
			return GetLastError();
		}
	}

	int vibor;
	bool konec = false;

	while (!konec) {
		cout << "Кол-во итераций в секундну" << endl;
		Sleep(1000);
		cout << "Поток 1 - инкремент: ";
		Seeker(threads[0], ids[0]);
		iter[0] = 0;
		cout << "Поток 2 - последовательность фибоначчи: ";
		Seeker(threads[1], ids[1]);
		iter[1] = 0;
		cout << "Поток 3 - последовательность квадратов: ";
		Seeker(threads[2], ids[2]);
		iter[2] = 0;
		cout << endl;

		cout << "Меню:" << endl;
		cout << "1. Сменить приоритет потока 1" << endl;
		cout << "2. Сменить приоритет потока 2" << endl;
		cout << "3. Сменить приоритет потока 3" << endl;
		cout << "4. Запустить нагрузчик" << endl;
		cout << "5. Выйти из программы" << endl;
		cout << endl;
		cout << "Введите номер пункта: ";

		cin >> vibor;

		switch (vibor)
		{
		case 1:
			change_priority(threads[0]);
			break;
		case 2:
			change_priority(threads[1]);
			break;
		case 3:
			change_priority(threads[2]);
			break;
		case 4:
			// вызов функции нагрузчика
			break;
		case 5:
			CloseHandle(threads[0]);
			CloseHandle(threads[1]);
			CloseHandle(threads[2]);
			system("cls");
			konec = true;
			break;
		default:
			cout << "Не правильно выбран пункт!" << endl;
			break;
		}
	}

	WaitForSingleObject(threads[0], INFINITE);
	WaitForSingleObject(threads[1], INFINITE);
	WaitForSingleObject(threads[2], INFINITE);

	return 0;
}
