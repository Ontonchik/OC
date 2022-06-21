#include <windows.h>
#include <iostream>
using namespace std;

void setSTP(STARTUPINFO* stp) {
	ZeroMemory(stp, sizeof(STARTUPINFO));
	stp->cb = sizeof(STARTUPINFO);
	stp->lpTitle = (LPWSTR)L"Hello world!";
	//stp->dwFlags = STARTF_USEPOSITION | STARTF_USECOUNTCHARS | STARTF_USEFILLATTRIBUTE;
	//stp->dwX = 300;
	//stp->dwY = 200;
	//stp->dwXSize = 800;
	//stp->dwYSize = 600;
	//stp->dwFillAttribute = BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE;
}

int main() {
	int n;
	cin >> n;
	string st("Child.exe");
	for (int i = 0;i < n;++i) {
		char c;
		cin >> c;
		st.append(' ' + string(1, c));
	}
	wstring q(st.length(), L' ');
	for (int i = 0;i < st.length();++i)
		q[i] = wchar_t(st[i]);

	STARTUPINFO stp;
	PROCESS_INFORMATION pi;
	setSTP(&stp);
	
	CreateProcess(NULL, &q[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &stp, &pi);//������ Child.exe

	WaitForSingleObject(pi.hProcess,INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);


	//////////��� ������///////////

	
	cout << "Setting priority:\n" << GetPriorityClass(GetCurrentProcess()) << " -> ";
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS); //��������� ����������
	cout << GetPriorityClass(GetCurrentProcess()) << '\n';

	Sleep(1000);
	ZeroMemory(&stp, sizeof(STARTUPINFO));
	stp.cb = sizeof(STARTUPINFO);
	CreateProcess(L"Count.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &stp, &pi);//������ Count.exe

	Sleep(6000);
	TerminateProcess(pi.hProcess, 0);//���������� ������ �������� Count

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);


	ExitProcess(0); //���������� ������ �������� Parent
}