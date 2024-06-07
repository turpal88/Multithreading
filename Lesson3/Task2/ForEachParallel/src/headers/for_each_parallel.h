#include <future>
#include <iostream>
#include <windows.h>
/*
template <typename RandomIt, typename T>
void parallel_for_each(RandomIt beg, RandomIt end, T(*f)(RandomIt, RandomIt))
{
	T result = 0;
	int len = end - beg;
    
	if (len < 3) {
		result = f(beg, end);
        std::cout << "Сумма элементов равна = " << result << "\n";
	}
		

	RandomIt mid = beg + len / 2;
	std::future<void> handle = std::async(std::launch::async, parallel_for_each<RandomIt, T>, mid, end, f);
	parallel_for_each(beg, mid, f);
	handle.wait();
	return;
	//std::cout << "The sum is " << result_first_half + handle.get() << '\n';
}
*/

#pragma execution_character_set("utf-8")

template <typename RandomIt, typename Func>
void parallel_for_each(RandomIt beg, RandomIt end, Func func) {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);

	auto result = 0;
	int len = end - beg;
	if (len < 3) {
		result = func(beg, end);
		
		std::cout << "Сумма элементов равна = " << result << "\n";
		return;
	}
		

	RandomIt mid = beg + len / 2;
	std::future<void> handle = std::async(std::launch::async, parallel_for_each<RandomIt, Func>, mid, end, func);
	parallel_for_each(beg, mid, func);
	handle.wait();
	return;
	
	//std::cout << "The sum is " << result_first_half + handle.get() << '\n';
}

