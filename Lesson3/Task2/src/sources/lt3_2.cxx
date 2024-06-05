
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <future>
#include <chrono>
#include <algorithm>
#include <mutex>
//#include <iterator>

#pragma execution_character_set("utf-8")

using namespace std::chrono_literals;
const int VEC_SIZE = 24;
std::mutex m;

void gotoxy(int x, int y)
{
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);

}


template <typename RandomIt, typename T>
T parallel_for_each(RandomIt beg, RandomIt end, T(*f)(RandomIt, RandomIt))
{
	int len = end - beg;
	
	
	if (len < 3)
		return f(beg, end);

	RandomIt mid = beg + len / 2;
	std::future<T> handle = std::async(std::launch::async,
		parallel_for_each<RandomIt, T>, mid, end, f);
	T sum = parallel_for_each(beg, mid, f);
	return sum + handle.get();
}

template<typename RandomIt, typename T>
T accumulate_function(RandomIt begin, RandomIt end) {
	static int i = 1;
	T sum = 0;
	std::lock_guard<std::mutex> lk(m);
	std::for_each(begin, end, [&sum](T t) {
		sum += t;
		});
	gotoxy(21, i);
	std::cout << "Сумма значений ";
	if ((end - begin) < 2) std::cout << *begin << " = " << sum;
	else std::cout << *begin << " + " << *(end - 1) << " = " << sum;
	++i;
	std::this_thread::sleep_for(500ms);
	return sum;
}


int main(){
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);

	std::vector<int> vec;
	for (int i = 0; i < VEC_SIZE; i++) vec.push_back(static_cast<int>(std::rand() / (RAND_MAX / 100)));
	std::cout << "Исходный контейнер: ";
	for (auto& t : vec) std::cout << t << " ";
	std::cout << "\n";
	std::cout << "Суммы пар элементов: ";
	
	int result = parallel_for_each(vec.begin(), vec.end(), accumulate_function<std::vector<int>::iterator, int>);
	std::cout << "\n";
	std::cout << "The sum is " << result << '\n';

    
system("pause");
return 0;	
}