#include <iostream>
#include <string>
#include <Windows.h>
#include "conj.h"
#include <conio.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bfunc::NodeList list;
	std::cout << "Кодування функції у вигляді кон'юктивної нормальної форми.\n\n";
	std::cout << "Натисніть 0, якщо бажаєте зчитати функцію з txt-файлу\n";
	std::cout << "Натисніть 1, якщо бажаєте ввести функцію вручну\n";
	char c = getchar();
	switch (c)
	{
	case '0':
		list.readFromFile();
		break;
	case '1':
		std::cout << "Введіть кількість змінних\n";
		int N;
		std::cin >> N;
		list.readFromConsole(N);
		break;
	}
	return 0;
}

