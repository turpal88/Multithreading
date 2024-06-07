

//#include <cstdlib>
#include <mutex>

#include <windows.h>
#include <iostream>

#include <chrono>
#pragma execution_character_set("utf-8")

using namespace std::chrono_literals;
std::mutex m;


template<typename T>
struct MultiplyFunction {
private:
	std::mutex _m;
public:
	//T result;
	MultiplyFunction() {
		//m = new std::mutex;
		//result = 0;
	}

	MultiplyFunction(const MultiplyFunction&) {
		//m = new std::mutex;
		//result = 0;
	}

	
	void operator()(T it) {
		std::lock_guard<std::mutex> lk(_m);
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);
		//if (begin != (end - 1)) result = *begin + *(end - 1); else result = *begin;
		//std::cout << "Новый элемент равен = " << result << "\n";
		it *= 3;
		std::cout << it << " ";
		//result = *it;
		std::this_thread::sleep_for(300ms);
		//return result;
	}
	//~MultiplyFunction() {
	//	delete m;
	//}

};



template<typename T>
void multiply_function(T it) {
	//T result{ 0 };
	std::lock_guard<std::mutex> lk(m);
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);
	it *= 3;
	std::cout << it << " ";
	//result = *it;
	//std::cout << "Сумма элементов равна = " << result << "\n";
	std::this_thread::sleep_for(300ms);
	//return result;
}
