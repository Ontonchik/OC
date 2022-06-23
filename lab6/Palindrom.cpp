#include <windows.h>
#include <conio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	HANDLE hNamedPipe;
	char machineName[80];
	TCHAR pipeName[80];
	DWORD dwBytesWritten;
	std::cout << "Enter a name of the server machine: ";
	std::cin >> machineName;
	wsprintf(pipeName, L" ", machineName);


	hNamedPipe = CreateFile(L"\\\\.\\pipe\\demo_pipe", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Connection with the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		cout << "Press any char to finish the client: ";
		_getch();
		return 0;
	}
	cout << "В ожидание получения размерности массива" << std::endl;
	int n;
	DWORD dwBytesRead;

	if (!ReadFile(hNamedPipe, &n, sizeof(n), &dwBytesRead, (LPOVERLAPPED)NULL))
	{
		std::cerr << "Data reading from the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		CloseHandle(hNamedPipe);
		std::cout << "Press any char to finish the server: ";
		_getch();
		return 0;
	}
	char* s = new char[n];
	DWORD dwBytesRead2;
	for (int i = 0; i < n; i++)
	{
		if (!ReadFile(hNamedPipe, &s[i], sizeof(s), &dwBytesRead2, (LPOVERLAPPED)NULL))
		{
			std::cerr << "Data reading from the named pipe failed." << std::endl
				<< "The last error code: " << GetLastError() << std::endl;
			CloseHandle(hNamedPipe);
			cout << "Press any char to finish the server: ";
			_getch();
			return 0;
		}
	}

	system("cls");
	std::cout << "Polindrom получил размер массива: " << n << std::endl;

	char x;
	std::cout << "Введите разделитель" << std::endl;
	std::cin >> x;
	std::cout << "Полученный разделитель " << x << std::endl;

	int k = 0;
	bool key = true;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == x)
		{
			for (int j = 0; j < (i - k) / 2; j++)
			{
				if (s[k + j] != s[i - j - 1])
				{
					key = false;
					break;
				}
			}

			if (key)
			{
				for (int j = k; j < i; j++)
				{
					std::cout << s[j];
					DWORD dwBytesWritten;
					if (!WriteFile(hNamedPipe, &s[j], sizeof(s), &dwBytesWritten, (LPOVERLAPPED)NULL))
					{
						std::cerr << "Writing to the named pipe failed: " << std::endl
							<< "The last error code: " << GetLastError() << std::endl;
						std::cout << "Press any char to finish the client: ";
						_getch();
						CloseHandle(hNamedPipe);
						return 0;
					}
				}

				DWORD dwBytesWritten;
				if (!WriteFile(hNamedPipe, &s[i], sizeof(s), &dwBytesWritten, (LPOVERLAPPED)NULL))
				{
					std::cerr << "Writing to the named pipe failed: " << std::endl
						<< "The last error code: " << GetLastError() << std::endl;
					std::cout << "Press any char to finish the client: ";
					_getch();
					CloseHandle(hNamedPipe);
					return 0;
				}
			}
			k = i + 1;
			key = true;
		}

	}
	CloseHandle(hNamedPipe);
	std::cout << "\nВсе найденные полиндромы были отправлены\n";
	std::cout << "Press any key to exit.\n";
	_getch();
	return 0;
}
