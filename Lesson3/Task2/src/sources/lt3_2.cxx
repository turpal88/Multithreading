#include <vector>
#include <iostream>
#include <for_each_parallel.h>
#include <accumulate_function.h>

const int VEC_SIZE = 24;

#define USING_SIMPLE_FUNCTION



int main(){
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);

	std::vector<int> vec;
	for (int i = 0; i < VEC_SIZE; i++) vec.push_back(static_cast<int>(std::rand() / (RAND_MAX / 100)));
	std::cout << "�������� ���������: ";
	for (auto& t : vec) std::cout << t << " ";
	std::cout << "\n";
	std::cout << "����� ��� ���������: " << "\n";
	

#ifdef USING_SIMPLE_FUNCTION
     parallel_for_each(vec.begin(), vec.end(), accumulate_function<std::vector<int>::iterator, int>);
#else

	AccumulateFunction<std::vector<int>::iterator, int> af;
	//AccumulateFunction<std::vector<int>::iterator, int>* ref_af = &af;
	parallel_for_each(vec.begin(), vec.end(), af);
#endif

	std::cout << "\n";
	

    
system("pause");
return 0;	
}