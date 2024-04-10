#include <thread>
#include <vector>
#include <windows.h>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#pragma execution_character_set("utf-8")

using namespace std::chrono_literals;

void gotoxy(int x, int y)
{
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

void vector_sum(std::vector<int>& vec1, std::vector<int>& vec2, std::vector<int>& vec3, 
	int begin_index, int end_index, std::chrono::duration<double, std::milli>& fp_ms) {
	auto start = std::chrono::steady_clock::now();
	
	for (int i = begin_index; i < end_index; i++) vec3.push_back(vec1.at(i) + vec2.at(i));
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	fp_ms += duration;
	std::this_thread::sleep_for(1s);
	
}


int main() {
	std::vector<int> el_number = {1000, 10000, 100000, 1000000};
	std::vector<int> thread_numbers = {1,2,4,8,16};
	std::vector<std::thread> threads;
	std::vector<std::vector<std::thread>> threads_vector;
	std::chrono::duration<double, std::milli> fp_ms{0s};
	std::vector<int> vec1, vec2, vec3;
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	
	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetClientRect(hWnd, &rc);
	int w = rc.right/10; // ширина рабочей области
	int h = rc.bottom/10;// высота рабочей области

	


	std::cout << "Количество аппаратных ядер = " << std::thread::hardware_concurrency() << std::endl;

	
	int print_x_interval = w / el_number.size();
	//int el_number_index = 0;

	
	//int x_coord = (el_number_index * print_x_interval) + print_x_interval / 2;

	
	
	
	
	
	for (int i = 0; i < thread_numbers.size(); i++) {
		gotoxy(0, 4 + i);
		std::cout << thread_numbers[i] << " потоков";

		for (int j = 0; j < el_number.size(); j++) {
			gotoxy((j * print_x_interval) + print_x_interval / 2, 3);
			std::cout << el_number[j];
			gotoxy((j * print_x_interval) + print_x_interval / 2, 4 + i);

			vec1.clear(); vec2.clear(); vec3.clear();
			fp_ms = 0ms;
			for (int k = 0; k < el_number.at(j); k++) {
				vec1.push_back(rand() % 7);
				vec2.push_back(rand() % 7);
			}

			int begin_index = 0;
			int end_index = el_number.at(j)/thread_numbers[i];

			for (int l = begin_index; l <= el_number.at(j) - el_number.at(j) / thread_numbers[i]; l+= end_index) {
				threads.push_back(std::thread(vector_sum, std::ref(vec1), std::ref(vec2), std::ref(vec3),
					l, l+end_index, std::ref(fp_ms)));
				
				
			}
			

			for (auto& el : threads) {
				if (el.joinable()) el.join();
			}
			threads.clear();
			std::cout << fp_ms.count();
			//if (i == 0 && j == 0) std::cout << fp_ms.count();
			//std::cout << "!";
		}
	}
	
	gotoxy(0, thread_numbers.size() + 4);
	/*
	std::for_each(el_number.begin(), el_number.end(), [&](int& n) {
		int thread_numbers_index = 0;
		int x_coord = (el_number_index * print_x_interval) + print_x_interval/2;
		gotoxy(x_coord, 3);
		std::cout << n;
		vec1.clear();
		vec2.clear();
		vec3.clear();
		for (int i = 0; i < n; i++) {
			vec1.push_back(rand() % 7);
			vec2.push_back(rand() % 7);
		}

		while (thread_numbers_index < thread_numbers.size()) {
			
			 //auto start = std::chrono::steady_clock::now();
			for (int j = 0; j < thread_numbers[thread_numbers_index]; j++) {
				int begin_index = j * n / thread_numbers[thread_numbers_index];
		        int end_index = (j + 1) * n / thread_numbers[thread_numbers_index];
				
				threads.push_back(std::thread(vector_sum, std::ref(vec1), std::ref(vec2), std::ref(vec3),
					std::ref(begin_index), std::ref(end_index)));
			}
			//auto end = std::chrono::steady_clock::now();
			gotoxy(x_coord, 4 + thread_numbers_index);
			//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			std::cout << (char)34;
			threads_vector.push_back(std::move(threads));
			threads.clear();
			
			++thread_numbers_index;

		}
		++el_number_index;

		});
		
	for (auto& threads_vector_el : threads_vector) {
		for (auto& threads_el : threads_vector_el) {
			if (threads_el.joinable()) threads_el.join();
		}
	}
		*/

	return 0;
}