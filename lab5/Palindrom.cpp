#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

bool isPalindrom(std::string x) {
	std::string copy(x);
	std::reverse(copy.begin(), copy.end());
	if (x._Equal(copy)) {
		return true;
	}
	else return false;
}

int main(int argc, char* argv[])
{
	HANDLE hWritePipe, hReadPipe;
	HANDLE hEnableRead, hEnableRead1;
	std::string lpszEnableRead = "EnableRead";
	std::wstring ler(lpszEnableRead.begin(), lpszEnableRead.end());
	LPWSTR lpszer = &ler[0];
	std::string lpszEnableRead1 = "EnableRead1";
	std::wstring ler1(lpszEnableRead1.begin(), lpszEnableRead1.end());
	LPWSTR lpszer1 = &ler1[0];
	hEnableRead = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpszer);
	hEnableRead1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpszer1);
	hWritePipe = (HANDLE)atoi(argv[0]);
	hReadPipe = (HANDLE)atoi(argv[1]);
	char sep;
	std::cout << "Input separator" << std::endl;
	std::cin >> sep;
	std::cout << "Waiting to start reading" << std::endl;
	WaitForSingleObject(hEnableRead, INFINITE);
	int size, new_size = 0, count = 0;
	DWORD dwBytesRead1;
	int start = 0;
	ReadFile(hReadPipe, &size, sizeof(size), &dwBytesRead1, NULL);
	std::cout << "Reading from pipe... " << size << std::endl;
	char* array = new char[size];
	std::string* arr = new std::string[size];
	std::string Data = "";
	for (int i = 0; i < size; i++)
	{
		DWORD dwBytesRead;
		char nData;
		ReadFile(hReadPipe, &nData, sizeof(nData), &dwBytesRead, NULL);
		std::cout << "Reading from pipe... " << nData << std::endl;
		if (nData != sep) {
			array[new_size] += nData;
			Data += nData;
			new_size++;
		}
		else {
			if (isPalindrom(Data)) {
				arr[count] = Data;
				count++;
			}
			Data = "";
		}
	}

	DWORD dwBytesWritten;
	WriteFile(hWritePipe, &count, sizeof(count), &dwBytesWritten, NULL);
	std::cout << "Writing into pipe... " << count << std::endl;
	std::string result = "";
	for (int i = 0; i < count; i++)
	{
		DWORD dwBytesWritten1;
		WriteFile(hWritePipe, &arr[i], sizeof(arr[i]), &dwBytesWritten1, NULL);
		std::cout << "Writing into pipe... " << arr[i] << std::endl;
		result += arr[i] + " ";
	}
	std::cout << "Result: " << result;
	std::cin >> size;
	SetEvent(hEnableRead1);
	
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hEnableRead);
	CloseHandle(hEnableRead1);
	return 0;
}