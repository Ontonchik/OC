#include <windows.h>
#include <iostream>

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
	std::cin >> n;
	std::string st("Child.exe");
	for (int i = 0; i < n; ++i) {
		char c;
		std::cin >> c;
		st.append(' ' + std::string(1, c));
	}
	std::wstring q(st.length(), L' ');
	for (int i = 0; i < st.length(); ++i)
		q[i] = wchar_t(st[i]);

	STARTUPINFO stp;
	PROCESS_INFORMATION pi;
	setSTP(&stp);

	CreateProcess(NULL, &q[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &stp, &pi);//Çàïóñê Child.exe

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);


	//////////Äîï çàäà÷à///////////


	std::cout << "Setting priority:\n" << GetPriorityClass(GetCurrentProcess()) << " -> ";
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS); //Óñòàíîâêà ïðèîðèòåòà
	std::cout << GetPriorityClass(GetCurrentProcess()) << '\n';

	Sleep(1000);
	ZeroMemory(&stp, sizeof(STARTUPINFO));
	stp.cb = sizeof(STARTUPINFO);
	CreateProcess(L"Count.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &stp, &pi);//Çàïóñê Count.exe

	Sleep(6000);
	TerminateProcess(pi.hProcess, 0);//Ïðåðûâàíèå ðàáîòû ïðîöåññà Count

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);


	ExitProcess(0); //çàâåðøåíèå ðàáîòû ïðîöåññà Parent
}
