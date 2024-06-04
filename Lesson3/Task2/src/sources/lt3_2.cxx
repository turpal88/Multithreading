//#include <accumulate_function.h>
//#include <for_each_parallel.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <future>
#include <chrono>
#include <algorithm>
//#include <iterator>

#pragma execution_character_set("utf-8")

using namespace std::chrono_literals;
const int VEC_SIZE = 240;

void gotoxy(int x, int y)
{
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);

}

/*
template<class T>
struct Sum
{
	T sum{ 0 };
	void operator()(T n) { sum += n; }
	
	Sum<T>& operator+(const Sum<T>& rh) { this->sum += rh.sum; return this; }
	Sum<T>& operator=(const Sum<T>& rh) { this->sum = rh.sum; return this; }
};
*/

/*
template<class It, class T>
Sum<T> accumulate_function(It begin, It end) {
	Sum<T> s = std::for_each(begin, end, Sum<T>());
	return s;
}
*/

/*
template<class It, class T>

Sum<T> make_parallel_for_each(It begin, It end, Sum<T> (*f)(It, It)) {

	int len = end - begin;
	if (len < 10) {
	Sum<T> s = std::for_each(begin, end, f);
	return s;
	} 

	It mid = begin + len / 2;
	std::future<Sum<T>> first_half = std::async(std::launch::async, make_parallel_for_each<It, T>, begin, mid, f);
	Sum<T> s = make_parallel_for_each<It, Sum<T>>(mid, end, f);

	Sum<T> final_sum = s + first_half.get();
	return final_sum;
	

}
*/


template <typename RandomIt, typename Func, typename T>
T parallel_for_each(RandomIt beg, RandomIt end, Func f)
{
	RandomIt len = end - beg;
	if (len < 10)
		return f(begin, end);

	RandomIt mid = beg + len / 2;
	T handle = std::async(std::launch::async,
		parallel_for_each<RandomIt, Func>, mid, end, f);
	T sum = parallel_for_each(beg, mid, f);
	return sum + handle.get();
}

template<typename RandomIt, typename T>
T accumulate_function(RandomIt begin, RandomIt end) {
	T sum = 0;
	std::for_each(begin, end, [&sum](RandomIt t) {
		sum += t;
		});
}

int main(){
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);


	std::vector<int> v(10000, 1);
	std::cout << "The sum is " << parallel_for_each(v.begin(), v.end(), accumulate_function) << '\n';

    //std::vector<int> vec1;
	//std::vector<int> vec;
	
	//for (int i = 0; i < VEC_SIZE; i++) vec.push_back(static_cast<int>(std::rand() / (RAND_MAX / 30)));
	
	//auto s = make_parallel_for_each<std::vector<int>::iterator, int>(vec.begin(), vec.end(), _accumulate_function);
	//std::cout << "Исходный контейнер: ";
	//for (auto& t : vec) std::cout << t << " ";
	//std::cout << "\n";
	//ForEach_Parallel<std::vector<int>::iterator, int> fep;
	//std::cout << "Суммы пар элементов: ";
	
		//make_accumulate_element(vec.begin(), vec.end(), accumulate_function<std::vector<int>::iterator, int>, vec.begin(), vec.end());
	
	
		
	
	
	//fep.make_accumulate_element(vec.begin(), vec.end(), accumulate_function<std::vector<int>::iterator, int>, vec.begin(), vec.end());
	//std::vector<int> vec{1, 5, 8, 9, 15, 4, 89, 7, 96, 2, 31, 32, 78, 11, 15, 65, 23};
system("pause");
return 0;	
}