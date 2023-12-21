#include <thread>
#include <ratio>
#include <chrono>

#include <iostream>
#include "windows.h"
#include <vector>
#include <random>

void gotoxy(int x, int y)
{
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

//template<typename T>
void sum_vectors(std::vector<int>& vec1, std::vector<int>& vec2, std::vector<int>& vec3, const int& _thread_count_j, int k) {
	for (int i = k * vec1.size() / _thread_count_j; i < (k * vec1.size() / _thread_count_j + vec1.size() / _thread_count_j); i++) {
		vec3[i] = vec1[i] + vec2[i];
	}
	
	//std::vector<int>::const_iterator it_start_vec1 = vec1.begin() + k * vec1.size() / _thread_count_j;
	//std::vector<int>::const_iterator it_end_vec1 = it_start_vec1 + vec1.size() / _thread_count_j;
	//std::vector<int>::const_iterator it_start_vec2 = vec2.begin() + k * vec2.size() / _thread_count_j;
	//std::vector<int>::const_iterator it_end_vec2 = it_start_vec2 + vec2.size() / _thread_count_j;
	//std::vector<int>::const_iterator it_start_vec3 = vec3.begin() + k * vec3.size() / _thread_count_j;
	//std::vector<int>::const_iterator it_end_vec3 = it_start_vec3 + vec3.size() / _thread_count_j;
	//std::vector<int>::const_iterator it2 = it_start_vec2;
	//for (std::vector<int>::const_iterator it = it_start_vec1; it != it_end_vec1; ++it) {
	//	*it_start_vec3 = *it + *it_start_vec2;
		//vec3.insert(it, (*it + *it_start_vec2));
	//	++it_start_vec2;
	//	++it_start_vec3;
	//}
	//return vec3;
}
void test_func() {
	for (int i = 0; i < 10; i++) {
		std::cout << i << " ";
	}
	std::cout << "\n";
}

int main(){
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	
	
	const std::vector<int> _thread_count{1,2,4,8,16 };
	const std::vector<int> elements_count{1000, 10000, 100000, 1000000};
	std::vector<std::vector<std::chrono::duration<double>>> time_arr(elements_count.size());
	std::vector<std::vector<std::chrono::duration<double>>>::const_iterator time_arr_it = time_arr.begin();
	
	
	gotoxy(40, 0);
	std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency();
	//gotoxy(0, 2);
	int temp = 20;
	std::for_each(elements_count.begin(), elements_count.end(), [&temp](const int& n) {
		gotoxy(temp,2);
		std::cout << n;
		temp += 18;
		});
	
	for (int e = 0; e < elements_count.size(); e++) {
		std::vector<std::vector<std::thread>> _thread_arr(_thread_count.size());
		std::vector<int> vec1(elements_count[e]);
		std::vector<int> vec2(elements_count[e]);
		std::vector<int> vec3(elements_count[e]);

		std::mt19937 gen;
		std::mt19937 gen2;
		std::uniform_int_distribution<int> dis(0, 100);
		std::uniform_int_distribution<int> dis2(200, 300);
		auto rand_num([=]() mutable {return dis(gen); });
		auto rand_num2([=]() mutable {return dis2(gen2); });
		std::generate(vec1.begin(), vec1.end(), rand_num);
		
		std::generate(vec2.begin(), vec2.end(), rand_num2);




		
		for (int j = 0; j < _thread_arr.size(); j++) {
			auto start_time = std::chrono::steady_clock::now();
			for (int k = 0; k < _thread_count[j]; k++) {

				_thread_arr.at(j).push_back(std::thread(sum_vectors, std::ref(vec1), std::ref(vec2), std::ref(vec3), _thread_count[j], k));


			}
			
			auto end_time = std::chrono::steady_clock::now();
			
			time_arr.at(e).push_back(std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time));
		}
		for (auto& n : _thread_arr) {
			for (auto& m : n) m.join();
		}

		}
	
	
	temp = 4;
	

	std::for_each(_thread_count.begin(), _thread_count.end(), [&temp](const int& n) {
		gotoxy(5, temp);
		std::cout << n << " потоков";
		temp+=2;
		
		});
	
	int temp1 = 18;
	
	for (int i = 0; i < time_arr.size(); i++) {
		temp = 4;
		std::for_each(time_arr[i].begin(), time_arr[i].end(), [&temp, &temp1](const std::chrono::duration<double>& n) {
			gotoxy(temp1, temp);
			std::cout << n.count();
			temp += 2;
			});
		temp1 += 18;
	}

	
	
	return 0;
}