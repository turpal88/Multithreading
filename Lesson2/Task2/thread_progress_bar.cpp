#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#pragma execution_character_set("utf-8")
#include <windows.h>
#include <algorithm>
#include <mutex>
#include <functional>


const int THREAD_COUNT = 10;
const int CALC_SIZE = 10000;
const int EXCEPTION_I = 600;

using namespace std::chrono_literals;

//#define ENABLE_EXCEPTION

std::mutex m;


class ProgressBar {
private:
	
	int calc_size;
	bool is_main_thread_info_printed;
	int current_thread_num;
	
public:
	
	ProgressBar(int calc_size) :  calc_size(calc_size) {
		
		is_main_thread_info_printed = false;
		
	}
	
	

	void gotoxy(int x, int y, UINT16 symbol_color)
	{
		COORD cd;
		cd.X = x;
		cd.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), symbol_color);
	}

	void print_thread_info() {
		this->gotoxy(1, 0, 0x0002);
		std::cout << "Номер потока";
		this->gotoxy(20, 0, 0x0002);
		std::cout << "id потока";
		this->gotoxy(50, 0, 0x0002);
		std::cout << "Прогресс-бар";
		this->gotoxy(80, 0, 0x0002);
		std::cout << "Время работы";
		this->gotoxy(0, 0, 0x0002);
	}


	void print_progress_bar() {
	
		SetConsoleOutputCP(866);
		std::cout << static_cast<char>(219);
		SetConsoleOutputCP(CP_UTF8);
	}
	

	void digit_calc(int current_thread_num) {
		
		if (!this->is_main_thread_info_printed) {
			{
				this->current_thread_num = current_thread_num;
				{
					std::lock_guard<std::mutex> lk(m);
				this->gotoxy(1, current_thread_num + 1, 0x0002);
				
				std::cout << current_thread_num + 1;
				std::this_thread::sleep_for(50ms);
				}
				
				{
					std::lock_guard<std::mutex> lk(m);
			    this->gotoxy(20, current_thread_num + 1, 0x0002);
				
					std::cout << std::this_thread::get_id();
					std::this_thread::sleep_for(50ms);
				}
				
				
				
				
				
				
				is_main_thread_info_printed = true;
			}
			
		}
		
		
		unsigned long long res{ 0 };
		int intermediate_res{ 0 };
		
		int initial_print_bar_position = 50;
		int initial_print_time_position = 80;
		
		std::chrono::duration<double, std::milli> elapsed_time{ 0ms };

		
		
		
		

		
		while (true) {
			
			try {
				//current_print_bar_thread_num = 0;
				for (int i = intermediate_res; i < calc_size; ++i) {
					auto start = std::chrono::steady_clock::now();
#ifndef ENABLE_EXCEPTION
					if (i % EXCEPTION_I == 0) {
#endif 
						auto end = std::chrono::steady_clock::now();
						elapsed_time += (end - start);
#ifdef ENABLE_EXCEPTION
						if (i % EXCEPTION_I == 0 && i != EXCEPTION_I * 4) {
#endif
						
						
							{
								std::lock_guard<std::mutex> lk(m);
								this->gotoxy(initial_print_bar_position, current_thread_num + 1, 0x0003);
								print_progress_bar();
								std::this_thread::sleep_for(50ms);
							}
							
								
								++initial_print_bar_position;

								{
									std::lock_guard<std::mutex> lk(m);
									this->gotoxy(initial_print_time_position, current_thread_num + 1, 0x0002);
									std::cout << elapsed_time.count();
									std::this_thread::sleep_for(50ms);
								}
								
							}
							
#ifdef ENABLE_EXCEPTION
					if (i == EXCEPTION_I*4) {
						intermediate_res = ++i;
						throw std::out_of_range("Попалась исключительная i");
					}
#endif

					res += i % 2;
					
				}
				break;
			}
			catch (std::out_of_range& e) {
				
				auto start = std::chrono::steady_clock::now();
				{
					std::lock_guard<std::mutex> lk(m);
					this->gotoxy(initial_print_bar_position, current_thread_num + 1, 0x0004);
					print_progress_bar();
					std::this_thread::sleep_for(50ms);
				}
						
						++initial_print_bar_position;
				auto end = std::chrono::steady_clock::now();
				elapsed_time += (end - start);
				
				{
					std::lock_guard<std::mutex> lk(m);
					this->gotoxy(initial_print_time_position, current_thread_num + 1, 0x0002);
					std::cout << elapsed_time.count();
					std::this_thread::sleep_for(50ms);
				}
				
			}
		}
		
		return;
		
	}



};




class Thread {
private:
	std::vector<std::thread> th_v;
	
	std::vector<ProgressBar> pb;
	
	int thread_count;
	int calc_size;
public:
	
	Thread(int thread_count, int calc_size) :thread_count(thread_count), calc_size(calc_size) {
		
		for (int i = 0; i < thread_count; i++) pb.push_back(ProgressBar(calc_size));
		pb.at(0).print_thread_info();
		
	}
	void make_count() {
		for (int i = 0; i < thread_count; i++) {
			
			th_v.push_back(std::thread(&ProgressBar::digit_calc, &pb.at(i), i));
			//if (th_v.at(i).joinable()) th_v.at(i).join();
		}
		for (int i = 0; i < thread_count; ++i) {
			if (th_v.at(i).joinable()) th_v.at(i).join();
		}
		
	}
	void put_cursor_down() {
		pb.at(0).gotoxy(0, thread_count+2, 0x0002);
	}
	

};

/*0x0001 - синий*/
/*0x0002 - зеленый*/
/*0x0003 - голубой*/
/*0x0004 - красный*/

int main() {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	

	Thread th(THREAD_COUNT, CALC_SIZE);
	th.make_count();
	th.put_cursor_down();
	

	return 0;
}