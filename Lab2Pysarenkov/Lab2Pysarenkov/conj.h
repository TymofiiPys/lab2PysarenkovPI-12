#pragma once
#include <string>

namespace bfunc {
	struct NodeList {
	private:
		struct Node {
			std::string ed;
			Node* next;
			Node(std::string ed);
		};
		Node* head = nullptr;
		Node* tail = nullptr;
	public:
		void readFromFile();
		void readFromConsole(int N);
		void solve(std::string names, int N, int edamnt);
	};
}