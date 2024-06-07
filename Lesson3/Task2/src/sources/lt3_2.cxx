#include <vector>
#include <windows.h>
#include <iostream>
#include <for_each_parallel.h>
#include <multiply_function.h>

const int VEC_SIZE = 24;

#define USING_SIMPLE_FUNCTION



int main(){
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);

	std::vector<int> vec;
	for (int i = 0; i < VEC_SIZE; i++) vec.push_back(static_cast<int>(std::rand() / (RAND_MAX / 100)));
	std::cout << "Исходный контейнер: ";
	for (auto& t : vec) std::cout << t << " ";
	std::cout << "\n";
	

#ifdef USING_SIMPLE_FUNCTION
     parallel_for_each(vec.begin(), vec.end(), multiply_function<std::vector<int>::iterator>);
#else

	MultiplyFunction<std::vector<int>::iterator, int> af;
	//AccumulateFunction<std::vector<int>::iterator, int>* ref_af = &af;
	parallel_for_each(vec.begin(), vec.end(), af);
#endif

	std::cout << "Новый контейнер: " << "\n";
	for (auto& t : vec) std::cout << t << " ";
	std::cout << "\n";
	

    
system("pause");
return 0;	
}