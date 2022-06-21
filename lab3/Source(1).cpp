#include <Windows.h>
#include <iostream>
#include <ctime>
#include <process.h>
#include <string>
#include <sstream>
using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma

HANDLE work, SumElement;
DWORD IDwork, IDs;
CRITICAL_SECTION cs;
CRITICAL_SECTION cs2;
HANDLE hOutEvent;
double mean;
int length;
int k;
int* arr;
char* temp;
int num;

DWORD WINAPI Work(LPVOID)
{
	EnterCriticalSection(&cs); 
	int time;
	cout << "¬ведите врем€ паузы";
	cin >> time;
	num = 0;
	temp=new char[length];
	for (int i = 0; i<length; i++) {
		if (arr[i]<= 9) {
			temp[num] = arr[i] + '0';
			Sleep(time);
			num++;
		}
	}
	for (int i = num; i < length; i++) {
		temp[i] = ' ';
	}
	LeaveCriticalSection(&cs);
	return 0;
}

DWORD WINAPI Sum(LPVOID) {
	EnterCriticalSection(&cs2);
	double sum = 0;
	int i = 0, m = 0;
	for(int i = 0; i < k; i++){
		char c = temp[i];
		sum += c-48;
	}
	mean = sum / k;
	SetEvent(hOutEvent);
	LeaveCriticalSection(&cs2);
	return 0;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	// инициализируем критическую секцию
	InitializeCriticalSection(&cs);
	InitializeCriticalSection(&cs2);
	work = CreateThread(NULL, 0, Work, NULL, CREATE_SUSPENDED, &IDwork);
	if (work == NULL) return GetLastError();
	SumElement = CreateThread(NULL, 0, Sum, NULL, CREATE_SUSPENDED, &IDs);
	if (SumElement == NULL) return GetLastError();
	cout << "¬ведите размер массива";
	cin >> length;
	arr = new int[length];
	cout << "¬ведите элементы массива";
	for (int i = 0; i < length; i++) {
		cin >> arr[i];
	}
	EnterCriticalSection(&cs2);
	cout << "¬ведите число k";
	cin >> k;
	ResumeThread(work);
	ResumeThread(SumElement);
	Sleep(10);
	EnterCriticalSection(&cs);
	for (int i = 0; i < length; i++) {
		cout << temp[i] << " ";
	}
	hOutEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hOutEvent == NULL)
		return GetLastError();
	LeaveCriticalSection(&cs);
	LeaveCriticalSection(&cs2);
	WaitForSingleObject(hOutEvent, INFINITE);
	cout << endl << "—реднее арифметическое первых " << k << " элементов:\n";
	cout << mean;
	return 0;
}