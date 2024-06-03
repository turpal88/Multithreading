#include <accumulate_function.h>
#include <for_each_parallel.h>
#include <windows.h>
#include <vector>
#include <cstdlib>

#pragma execution_character_set("utf-8")
const int VEC_SIZE = 24;
int main(){
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);

    //std::vector<int> vec1;
	std::vector<int> vec;
	for (int i = 0; i < VEC_SIZE; i++) vec.push_back(static_cast<int>(std::rand() / (RAND_MAX / 30)));
	std::cout << "Исходный контейнер: ";
	for (auto& t : vec) std::cout << t << " ";
	std::cout << "\n";
	ForEach_Parallel<std::vector<int>::iterator, int> fep;
	std::cout << "Суммы пар элементов: ";
	fep.make_accumulate_element(vec.begin(), vec.end(), accumulate_function<std::vector<int>::iterator, int>, vec.begin(), vec.end());
	//std::vector<int> vec{1, 5, 8, 9, 15, 4, 89, 7, 96, 2, 31, 32, 78, 11, 15, 65, 23};
system("pause");
return 0;	
}