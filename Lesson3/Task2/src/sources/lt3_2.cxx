#include <vector>
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
	std::cout << "Модифицированные значения: ";
	
#ifdef USING_SIMPLE_FUNCTION
	void(*_multiply_function)(int) = multiply_function<int>;
     parallel_for_each(vec.begin(), vec.end(), _multiply_function);
#else

	MultiplyFunction<int> af;
	//AccumulateFunction<int>* ref_af = &af;
	MultiplyFunction<int>* ft = &af;
	parallel_for_each(vec.begin(), vec.end(), &MultiplyFunction<int>{});
#endif

	
	//std::cout << "Новый контейнер: ";
	//for (auto& t : vec) std::cout << t << " ";
	std::cout << "\n";
	

    
system("pause");
return 0;	
}