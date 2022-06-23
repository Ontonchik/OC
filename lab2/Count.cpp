#include <iostream>
#include <conio.h>
#include <windows.h>

void fibonachi(long long a, long long b) {
	Sleep(100);
	std::cout << a <<"\n";
	fibonachi(a + b, a);
}

int main() {
	const long long zero = 0ll;
	const long long one = 1ll;
	fibonachi(zero,one);
	std::cin.get();
}
