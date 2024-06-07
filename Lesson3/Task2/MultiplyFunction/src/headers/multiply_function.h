

//#include <cstdlib>
#include <mutex>

#include <windows.h>
#include <chrono>

using namespace std::chrono_literals;
std::mutex m;


template<typename RandomIt>
struct MultiplyFunction {
private:
	std::mutex* m;
public:
	//T result;
	MultiplyFunction() {
		m = new std::mutex;
		//result = 0;
	}
	
	void operator()(RandomIt it) {
		std::lock_guard<std::mutex> lk(*m);
		//if (begin != (end - 1)) result = *begin + *(end - 1); else result = *begin;
		//std::cout << "Новый элемент равен = " << result << "\n";
		*it *= 3;
		//result = *it;
		std::this_thread::sleep_for(300ms);
		//return result;
	}
	~MultiplyFunction() {
		delete m;
	}

};



template<typename RandomIt>
void multiply_function(RandomIt it) {
	//T result{ 0 };
	std::lock_guard<std::mutex> lk(m);
	*it *= 3;
	//result = *it;
	//std::cout << "Сумма элементов равна = " << result << "\n";
	std::this_thread::sleep_for(300ms);
	//return result;
}
