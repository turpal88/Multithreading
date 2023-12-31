#include <thread>
#include<mutex>
#include <chrono>
//#include <system_error>
#include <iostream>
#include "windows.h"
#include <vector>
//#include <random>

class Data {
public:
	int value;
	std::string s;
	Data(int value, std::string s) :value(value), s(s) {}

	std::mutex m;

};

void swap_lock(Data& a, Data& b) {
	std::lock(a.m, b.m);
	std::lock_guard<std::mutex> lk1(a.m, std::adopt_lock);
	std::lock_guard<std::mutex> lk2(b.m, std::adopt_lock);
	int temp_value;
	std::string temp_s;
	temp_value = a.value;
	a.value = b.value;
	b.value = temp_value;

	temp_s = a.s;
	a.s = b.s;
	b.s = temp_s;
	std::cout << "\nЯ функция swap_lock и я виртуозно поменяла два объекта которые мне передали местами\nСмотрите что получилось:\n";
	std::cout << "Объект а: value = " << a.value << ", s = " << a.s << "\n";
	std::cout << "Объект b: value = " << b.value << ", s = " << b.s << "\n";
}

void swap_scoped_lock(Data& a, Data& b) {
	std::scoped_lock(a.m, b.m);
	int temp_value;
	std::string temp_s;
	temp_value = a.value;
	a.value = b.value;
	b.value = temp_value;

	temp_s = a.s;
	a.s = b.s;
	b.s = temp_s;
	std::cout << "\nЯ функция swap_scoped_lock и я виртуозно поменяла два объекта которые мне передали местами\nСмотрите что получилось:\n";
	std::cout << "Объект а: value = " << a.value << ", s = " << a.s << "\n";
	std::cout << "Объект b: value = " << b.value << ", s = " << b.s << "\n";
}
void swap_unique_lock(Data& a, Data& b) {
	
	std::unique_lock<std::mutex> lk1(a.m, std::defer_lock);
	std::unique_lock<std::mutex> lk2(b.m, std::defer_lock);
	std::lock(lk1, lk2);
	int temp_value;
	std::string temp_s;
	temp_value = a.value;
	a.value = b.value;
	b.value = temp_value;

	temp_s = a.s;
	a.s = b.s;
	b.s = temp_s;
	std::cout << "\nЯ функция swap_unique_lock и я виртуозно поменяла два объекта которые мне передали местами\nСмотрите что получилось:\n";
	std::cout << "Объект а: value = " << a.value << ", s = " << a.s << "\n";
	std::cout << "Объект b: value = " << b.value << ", s = " << b.s << "\n";
	
}
int main() {
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	Data a(5, "пять");
	Data b(10, "десять");
	std::cout << "Объект а: value = " << a.value << ", s = " << a.s << "\n";
	std::cout << "Объект b: value = " << b.value << ", s = " << b.s << "\n";
	std::vector<std::thread> thread_vec(3);
	thread_vec.at(0) = std::thread(swap_lock, std::ref(a), std::ref(b));
	thread_vec.at(1) = std::thread(swap_scoped_lock, std::ref(a), std::ref(b));
	thread_vec.at(2) = std::thread(swap_unique_lock, std::ref(a), std::ref(b));
	
	
	for (auto& n : thread_vec) n.join();
	return 0;
}