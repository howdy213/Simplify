#include"Print.h"
#include<iostream>
void PrintTestTitle(int num) {
	std::cout << "\n--------------------test_" << num << "--------------------\n";
}
void Repeat(int num, char c) {
	for (int n = 1; n <= num; n++)printf("%c", c);
}
