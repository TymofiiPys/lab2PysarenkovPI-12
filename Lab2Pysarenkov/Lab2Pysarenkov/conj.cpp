#include <iostream>
#include <string>
#include <clocale>
#include <stdio.h>
#include "conj.h"
#include <fstream>

void bfunc::NodeList::readFromConsole(int N) {
	head = nullptr;
	tail = nullptr;
	std::string names = "";
	int i;
	for (i = 0; i < N; i++) {
		if (i < 3)
			names += char(120 + i); //x, y, z
		else
			names += char(94 + i); //a, b, c, d...
	}
	std::cout << "Назви змінних: ";
	for (i = 0; i < N; i++) {
		std::cout << names[i];
		if (i < N - 1)
			std::cout << ", ";
		else
			std::cout << ".\n";
	}
	std::cout << "Введіть елементарні диз'юнкції за правилами:\n";
	std::cout << "1. Змінні записувати через нижнє підкреслювання (_)\n";
	std::cout << "2. Для запису заперечення змінної поставте перед нею літеру N.\n";
	std::cout << "3. Для припинення запису КНФ введіть end.\n";
	std::cout << "Приклад вводу ЕД: x_Ny_z\n";
	for (;;) {
		std::string ed;
		std::cin >> ed;
		if (ed == "end")
		{
			break;
		}
		else {
			Node* node = new Node(ed);
			if (head == nullptr) {
				head = node;
				tail = node;
			}
			else {
				tail->next = node;
				tail = node;
			}
		}
	}
	std::cout << "Записана функція має вигляд: ";
	Node* iter = head;
	int edamnt = 0;
	while (iter != nullptr) {
		std::cout << "(";
		std::string ed;
		ed = iter->ed;
		int edl = ed.length();
		for (int i = 0; i < edl; i++) {
			if (ed[i] == 'N')
				std::cout << "¬";
			else if (ed[i] == '_')
				std::cout << " V ";
			else
				std::cout << ed[i];
		}
		if (iter != tail) {
			std::cout << ") & ";
		}
		else {
			std::cout << ")\n";
		}
		edamnt++;
		iter = iter->next;
	}
	solve(names, N, edamnt);
}

void bfunc::NodeList::readFromFile() {
	head = nullptr;
	tail = nullptr;
	std::ifstream fo("input.txt");
	if (fo) {
		int N, i;
		std::string buf;
		std::string Ns, names = "";
		std::getline(fo, Ns);
		N = std::stoi(Ns);
		for (i = 0; i < N; i++) {
			if (i < 3)
				names += char(120 + i); //x, y, z
			else
				names += char(94 + i); //a, b, c, d...
		}
		while (!fo.eof()) {
			std::string ed;
			std::getline(fo, ed);
			Node* node = new Node(ed);
			if (head == nullptr) {
				head = node;
				tail = node;
			}
			else {
				tail->next = node;
				tail = node;
			}
		}
		std::cout << "Записана функція має вигляд: ";
		Node* iter = head;
		int edamnt = 0;
		while (iter != nullptr) {
			std::cout << "(";
			std::string ed;
			ed = iter->ed;
			int edl = ed.length();
			for (int i = 0; i < edl; i++) {
				if (ed[i] == 'N')
					std::cout << "¬";
				else if (ed[i] == '_')
					std::cout << " V ";
				else
					std::cout << ed[i];
			}
			if (iter != tail) {
				std::cout << ") & ";
			}
			else {
				std::cout << ")\n";
			}
			edamnt++;
			iter = iter->next;
		}
		solve(names, N, edamnt);
	}
	else {
		std::cout << "Файл не знайдено. Перевірте розташування та ім'я файлу (input.txt)";
	}
}

void bfunc::NodeList::solve(std::string names, int N, int edamnt) {
	std::string fline = "", l, ed;
	int valamnt = 1;
	for (int i = 0; i < N; i++) {
		std::cout << names[i] << '\t';
		if (i < N - 1) {
			fline += names[i];
			fline += ",";
		}
		else {
			fline += names[i];
		}
		valamnt *= 2;
	}
	std::cout << "f(" << fline << ")\n";
	int v = valamnt, *vars, j, *edv, k, fvalue;
	for (int i = 0; i < valamnt; i++)
	{
		vars = new int[N]; //Значення кожної з N змінних
		edv = new int[edamnt]; //Значення кожної з edamnt елементарних диз'юнкцій
		fvalue = 1;//Значення функції
		Node* iter = head;
		for (k = 0; k < edamnt; k++) {
			edv[k] = 0;
		}
		l = "";
		int x = i;
		do
		{
			l = std::to_string(x % 2) + l;
			x /= 2;
		} while (x != 0); //В таблиці потрібно записати функції для 2^N наборів. Тобто, якщо змінних 3, то набори наступні:
		//(0,0,0), (0,0,1), (0,1,0), (0,1,1), (1,0,0), (1,0,1), (1,1,0), (1,1,1). Якщо записати значення змінних на i-му рядку в рядок,
		//то цей рядок покаже число i, записане у двійковому вигляді.
		int il = l.length();
		if (il < N)
		{
			for (k = 0; k < N - il; k++) {
				l = '0' + l;
			}
		}
		for (j = 0; j < N; j++) {
			std::string x = "";
			x += l[j];
			vars[j] = std::stoi(x);
			std::cout << vars[j] << '\t';
		}
		k = 0;
		while (iter != nullptr) {
			ed = iter->ed;
			int edl = ed.length();
			int c = 0;
			bool NOT = false;
			for (j = 0; j < edl; j++) {
				if (std::to_string(ed[j]) == std::to_string(names[c])) {
					if (vars[c] == 1)//Якщо хоча б одна із змінних, або її заперечення, дорівнює 1, то і вся ЕД дорівнює 1
					{
						edv[k] = 1;
						if (NOT) {
							NOT = false;
							if (vars[c] == 1)
								vars[c] = 0;
							else
								vars[c] = 1;
						}
						break;
					}
					else {
						if (NOT) {
							NOT = false;
							if (vars[c] == 1)
								vars[c] = 0;
							else
								vars[c] = 1;
						}
					}
					c++;
				}
				else if (ed[j] == 'N') {
					NOT = true;
					if (vars[c] == 1)
						vars[c] = 0;
					else
						vars[c] = 1;
				}
			}
			if (edv[k] == 0) {
				fvalue = 0;
				break;
			}
			iter = iter->next;
			k++;
		}
		std::cout << fvalue << "\n";
	}
}

bfunc::NodeList::Node::Node(std::string ed)
{
	this->ed = ed;
	this->next = nullptr;
}