#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	string line = "Child.exe ";
	cout << "������� ������ �������: " << endl;
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
	boolean check=CreateProcess(NULL, command_line, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);
	if (!check){
		_cputs("process not created");
		return 0;
	}
	_cputs("The new process is created.\n");
	// ���� ���������� ���������� �������CloseHandle(piF.hThread);
	WaitForSingleObject(piApp.hProcess, INFINITE);
	// ��������� ����������� ����� �������� � ������� ��������
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	line = "Count.exe";
	wstring str(line.begin(), line.end());
	command_line = &str[0];
	boolean check2=CreateProcess(NULL, command_line, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);
	if (check2) {
		cout << "New process has created";
	}
	SetPriorityClass(piApp.hProcess, HIGH_PRIORITY_CLASS);
	Sleep(3000);
	TerminateProcess(piApp.hProcess, 0);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	ExitProcess(0);
}