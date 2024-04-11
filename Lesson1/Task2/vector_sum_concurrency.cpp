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
	int begin_index, int end_index) {
	
	
	
	for (int i = begin_index; i < end_index; i++) vec3.push_back(vec1.at(i) + vec2.at(i));
	
	std::this_thread::sleep_for(1s);
	
}


int main() {
	std::vector<int> el_number = {1000, 10000, 100000, 1000000};
	std::vector<int> thread_numbers = {1,2,4,8,16};
	std::vector<std::thread> threads;
	//std::vector<std::vector<std::thread>> threads_vector;
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
	

	
	
	
	
	
	for (int i = 0; i < thread_numbers.size(); i++) {
		gotoxy(0, 4 + i);
		std::cout << thread_numbers[i] << " потоков";

		for (int j = 0; j < el_number.size(); j++) {
			gotoxy((j * print_x_interval) + print_x_interval / 2, 3);
			std::cout << el_number[j];
			gotoxy((j * print_x_interval) + print_x_interval / 2, 4 + i);

			vec1.clear(); vec2.clear(); vec3.clear();
			
			for (int k = 0; k < el_number.at(j); k++) {
				vec1.push_back(rand() % 7);
				vec2.push_back(rand() % 7);
			}

			int begin_index = 0;
			int end_index = el_number.at(j)/thread_numbers[i];
			fp_ms = 0ms;
			auto start = std::chrono::steady_clock::now();
			for (int l = begin_index; l <= el_number.at(j) - el_number.at(j) / thread_numbers[i]; l+= end_index) {
				threads.push_back(std::thread(vector_sum, std::ref(vec1), std::ref(vec2), std::ref(vec3),
					l, l+end_index));
				
				
			}
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double, std::milli> fp_ms = end - start;
			for (auto& el : threads) {
				if (el.joinable()) el.join();
			}
			threads.clear();
			std::cout << fp_ms.count();
			
		}
	}
	
	gotoxy(0, thread_numbers.size() + 4);
	

	return 0;
}