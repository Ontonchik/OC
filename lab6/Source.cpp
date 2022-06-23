#include <windows.h>
#include <conio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;
	HANDLE hNamedPipe;
	DWORD dwBytesRead;
	DWORD dwBytesWrite;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.lpSecurityDescriptor = &sd;
	hNamedPipe = CreateNamedPipe(L"\\\\.\\pipe\\demo_pipe", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 0, 0, INFINITE, &sa);
	
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Creation of the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		std::cout << "Press any char to finish server: ";
		_getch();
		return 0;
	}
	std::cout << "The server is waiting for connection with a client." << std::endl;

	if (!ConnectNamedPipe(hNamedPipe, (LPOVERLAPPED)NULL))
	{
		std::cerr << "The connection failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		CloseHandle(hNamedPipe);
		std::cout << "Press any char to finish the server: ";
		_getch();
		return 0;
	}
	int n;
	std::cout << "Введите размер массива" << std::endl;
	std::cin >> n;
	char* s = new char[n];
	std::cout << "Введите массив" << std::endl;
	std::cin >> s;
	DWORD dwBytesWritten;

	if (!WriteFile(hNamedPipe, &n, sizeof(n), &dwBytesWritten, (LPOVERLAPPED)NULL))
	{
		std::cerr << "Data writing to the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		CloseHandle(hNamedPipe);
		std::cout << "Press any char to finish the server: ";
		_getch();
		return 0;
	}

	for (int i = 0; i < n; i++)
	{
		if (!WriteFile(hNamedPipe, &s[i], sizeof(s), &dwBytesWritten, (LPOVERLAPPED)NULL))
		{
			std::cerr << "Data writing to the named pipe failed." << std::endl
				<< "The last error code: " << GetLastError() << std::endl;
			CloseHandle(hNamedPipe);
			std::cout << "Press any char to finish the server: ";
			_getch();
			return 0;
		}
	}

	int i = 0;
	std::cout << "Server отправил : " << n << " " << s << std::endl;
	int k = 0;
	char* nData = new char[n];

	while (true) {
		k++;
		DWORD dwBytesRead;
		if (!ReadFile(hNamedPipe, &nData[i], sizeof(nData), &dwBytesRead, (LPOVERLAPPED)NULL))
		{
			CloseHandle(hNamedPipe);
			std::cout << "\nВсе лексемы были получены" << std::endl;
			_getch();
			return 0;
		}
		std::cout << "" << nData[i];
		i++;
	}
	std::cout << std::endl;

	if (k == 0) {
		std::cout << "Ничего не было получено" << std::endl;
	}
	else {
		std::cout << "Все лексемы были получены" << std::endl;
	}

	CloseHandle(hNamedPipe);
	std::cout << "Press any key to exit.\n";
	_getch();
	return 0;
}
