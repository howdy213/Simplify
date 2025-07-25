#include"Print.h"
#include<iostream>
void PrintSetup(int num) {
	std::cout << "\n--------------------setup_" << num << "--------------------\n";
}
void Repeat(int num, char c) {
	for (int n = 1; n <= num; n++)printf("%c", c);
}