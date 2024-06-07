#include <algorithm>
#include <windows.h>
//#include <cstdlib>
#include <mutex>

#include <chrono>

using namespace std::chrono_literals;
std::mutex m;


template<typename RandomIt, typename T>
struct AccumulateFunction {
private:
	std::mutex* m;
public:
	T result;
	AccumulateFunction() {
		m = new std::mutex;
		result = 0;
	}
	
	T operator()(RandomIt begin, RandomIt end) {
		std::lock_guard<std::mutex> lk(*m);
		std::for_each(begin, end, [&result](T t) {
			result += t;
			});
		std::this_thread::sleep_for(300ms);
		return result;
	}
	~AccumulateFunction() {
		delete m;
	}

};



template<typename RandomIt, typename T>
T accumulate_function(RandomIt begin, RandomIt end) {
	T result{ 0 };
	std::lock_guard<std::mutex> lk(m);
	std::for_each(begin, end, [&result](T t) {
		result += t;
		});
	std::this_thread::sleep_for(300ms);
	return result;
}
