#include <iostream>
#include <conio.h>
#include <windows.h>

int main(int arg, char* argv[]) {
	int size = atoi(argv[1]);
	int* mas = new int[size];
	int* flags = new int[size];
	for (int i = 0; i < size; i++) {
		mas[i] = atoi(argv[i + 2]);
		flags[i] = 1;
	}
	int* temp = new int[size];
	int tmp = 0;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (mas[i] == mas[j] && flags[i] % 2 == 1) {
				flags[i]++;
				flags[j]++;
				temp[tmp] = mas[i];
				tmp++;
				temp[tmp] = mas[i];
				tmp++;
				break;
			}
		}
	}
	for (int i = 0; i < tmp; i += 2) {
		std::cout << temp[i] << " ";
	}
	int medium;
	for (int i = 0; i < size; i++) {
		if (flags[i] == 1) {
			medium = mas[i];
			std::cout << mas[i] << " ";
			break;
		}
	}
	for (int i = tmp - 1; i >= 0; i -= 2) {
		std::cout << temp[i] << " ";
	}
	for (int j = 0; j < size; j++) {
		if (flags[j] == 1 && mas[j] != medium) {
			std::cout << mas[j] << " ";
		}
	}
	std::cin.get();
}
