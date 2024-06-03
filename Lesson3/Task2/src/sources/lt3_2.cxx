//#include <accumulate_function.h>
//#include <for_each_parallel.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <future>
#include <chrono>
#include <iterator>

#pragma execution_character_set("utf-8")

using namespace std::chrono_literals;
const int VEC_SIZE = 24;

void gotoxy(int x, int y)
{
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);

}

template<class T>
std::vector<std::future<T>> future_vector;
template<class T>
std::vector<T> temp_vector;

template<class It, class T>
T accumulate_function(It begin, It end) {

	return std::accumulate(begin, end, 0);
}

template<class It, class T>

T make_accumulate_element(It begin, It end, T(*f)(It, It), It, It) {
	int d = std::distance(begin, end);
	
	if (d == 2) return f(begin, end);
	else {
		//int j = (d/2 <= core_count)? 1 : (d/2)/core_count; //1 2 3 4 5
		//int k = (d/2 <= core_count)? d%2 : (d/2)%core_count; //begin+ 1 3 5 7 9
									// begin+ 

		//bool is_remainder_more_0 = (k > 0)? true : false;
		//int p = (is_remainder_more_0)? 1 : 0;
		//std::future<T> ft;
		for (int i = 0; i < 12; ++i) {
			//if(k == 0 && is_remainder_more_0) p = 0;
			future_vector<T>.push_back(std::move(std::async(std::launch::async, make_accumulate_element<std::vector<T>::iterator, T>, begin, begin + 1, f, begin, begin + 1)));
			
				//ft = std::async(std::launch::async, make_accumulate_element<It, T>, begin, begin + 1, f, begin, begin + 1);
		
			
				
			
			
			//future_vector.push_back(std::async(std::launch::async, &ForEach_Parallel::make_accumulate_element, this, begin, begin + 1 + 2 * j + 2 * p, f, begin, begin + 1 + 2 * j + 2 * p));
			
			if ((begin + 2) <= end - 2) begin += 2; else break;
			//if((begin + 2 + 2 * j + 2 * p) < end - 1) begin += 2 + 2 * j + 2 * p; else break;
			//if(is_remainder_more_0 && p != 0) --k;


		}
		
			//temp_vector<T>.push_back(ft.get());
		
		
			
		
		
	}
	T sum = 0;
	for (int i = 0; i < future_vector<T>.size(); ++i) {
		gotoxy(21 + 2 * i, 1);
		T temp = future_vector<T>.at(i).get();
		std::cout << temp;
		std::this_thread::sleep_for(10ms);
		sum += temp;

	}
	return sum;
}


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
	//ForEach_Parallel<std::vector<int>::iterator, int> fep;
	std::cout << "Суммы пар элементов: ";
	
		make_accumulate_element(vec.begin(), vec.end(), accumulate_function<std::vector<int>::iterator, int>, vec.begin(), vec.end());
	
	
		
	
	
	//fep.make_accumulate_element(vec.begin(), vec.end(), accumulate_function<std::vector<int>::iterator, int>, vec.begin(), vec.end());
	//std::vector<int> vec{1, 5, 8, 9, 15, 4, 89, 7, 96, 2, 31, 32, 78, 11, 15, 65, 23};
system("pause");
return 0;	
}