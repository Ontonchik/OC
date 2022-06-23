#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>

int main() {
	setlocale(LC_ALL, "RUS");
	std::string line = "Child.exe ";
	std::cout << "Введите размер массива: " << std::endl;
	int length;
	std::cin >> length;
	int* array = new int[length];
	line += std::to_string(length);
	for (int i = 0; i < length; i++) {
		std::cin >> array[i];
		line += " "+ std::to_string(array[i]);
	}
	std::wstring c(line.begin(), line.end());
	LPWSTR command_line = &c[0];
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	LPWSTR child_ = (LPWSTR)L"CHILD PROCESS";
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.lpTitle = child_;
	boolean check=CreateProcess(NULL, command_line, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);
	if (!check){
		_cputs("process not created");
		return 0;
	}
	_cputs("The new process is created.\n");
	// ждем завершения созданного прцессаCloseHandle(piF.hThread);
	WaitForSingleObject(piApp.hProcess, INFINITE);
	// закрываем дескрипторы этого процесса в текущем процессе
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	line = "Count.exe";
	std::wstring str(line.begin(), line.end());
	command_line = &str[0];
	boolean check2=CreateProcess(NULL, command_line, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);
	if (check2) {
		std::cout << "New process has created";
	}
	SetPriorityClass(piApp.hProcess, HIGH_PRIORITY_CLASS);
	Sleep(3000);
	TerminateProcess(piApp.hProcess, 0);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	ExitProcess(0);
}
