#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	wstring child_name(L"C:/Users/sveta/Desktop/c++/lab 2 oc/Debug/Child.exe");
	LPWSTR name = &child_name[0];
	string line = "";
	cout << "¬ведите размер массива: " << endl;
	int length;
	cin >> length;
	int* array = new int[length];
	line += to_string(length);
	for (int i = 0; i < length; i++) {
		cin >> array[i];
		line += " "+to_string(array[i]);
	}
	wstring c(line.begin(), line.end());
	LPWSTR command_line = &c[0];
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	LPWSTR child_ = (LPWSTR)L"CHILD PROCESS";
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.lpTitle = child_;
	boolean check=CreateProcess(name, command_line, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);
	if (!check){
		_cputs("process not created");
		return 0;
	}
	_cputs("The new process is created.\n");
	// ждем завершени€ созданного прцессаCloseHandle(piF.hThread);
	WaitForSingleObject(piApp.hProcess, INFINITE);
	// закрываем дескрипторы этого процесса в текущем процессе
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	ExitProcess(0);
	return 0;
}