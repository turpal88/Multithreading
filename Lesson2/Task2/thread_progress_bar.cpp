#include <thread>
#include<mutex>
#include <chrono>
#include <system_error>
#include <iostream>
#include "windows.h"
#include <vector>
#include <random>
#include <condition_variable>

std::mutex m;

int plus_one_more_line = 0; //прибавляем 1 к последней напечатанной строке, чтобы в конце текст программы не налазил друг на друга
void gotoxy(int x, int y, _In_ WORD color = FOREGROUND_GREEN)
{
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//template<typename T>

void print_thread_table_columns() {
	gotoxy(0, 0);
	std::cout << "Номер потока по порядку";
	gotoxy(30, 0);
	std::cout << "Идентификатор потока";
	gotoxy(60, 0);
	std::cout << "Прогресс-бар";
	gotoxy(90, 0);
	std::cout << "Время выполнения";
	

}
void print_thread_num(const int& n) {
	gotoxy(0, n + 2);
	std::cout << n + 1;
}

void put_blue_red_symbol(int& factor, int thread_num, int rand_temp, int i) {
	
	if (rand_temp == i) {
		
		throw std::exception("\nБыло брошено исключение в потоке с id = ");
	}
	else gotoxy(factor + 60, thread_num + 2, FOREGROUND_BLUE);
	SetConsoleOutputCP(866);
	std::cout << static_cast<char>(219);
	SetConsoleOutputCP(1251);
	factor++;
	
}

void test_func(int count_size, std::chrono::duration<double>& elapsed_time, int thread_num, int threads_count) {
	std::unique_lock<std::mutex> lk_u(m);
	int step = count_size / 20; //берем шаг в 20 символов - максимум сколько можно отрисовать в консоли в линии для для одного потока, для этого считаем step - на какой итерации рисовать символ
	int factor = 1;
	
	gotoxy(30, thread_num + 2);

	std::cout << std::this_thread::get_id();
	lk_u.unlock();
	std::random_device random_device; // Источник энтропии.
	std::mt19937 generator(random_device()); // Генератор случайных чисел.
	// (Здесь берется одно инициализирующее значение, можно брать больше)

	

	

	int temp = 0;
	auto start = std::chrono::steady_clock::now();
	
	for (int i = 0; i < count_size; i++) {
		temp++;
		auto end = std::chrono::steady_clock::now();
		elapsed_time += (end - start);
		
		if (i >= step * factor) {
			std::lock_guard<std::mutex> lock(m);
			std::uniform_int_distribution<> distribution(step, step * factor); // Равномерное распределение [10, 20]
			int rand_temp = distribution(generator); // Случайное число.
			try {
				
				put_blue_red_symbol(factor, thread_num, rand_temp, i);
			}
			catch (std::exception& e) {
				plus_one_more_line++;
				gotoxy(0, threads_count + plus_one_more_line, FOREGROUND_RED);
				std::cout << e.what() << std::this_thread::get_id() << std::endl;
				gotoxy(factor + 60, thread_num + 2, FOREGROUND_RED);
				SetConsoleOutputCP(866);
				std::cout << static_cast<char>(219);
				SetConsoleOutputCP(1251);
				factor++;
				
			}
			gotoxy(90, thread_num + 2);
			std::cout << elapsed_time.count();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		
	} 
	
	

}
void thread_init(std::vector<std::thread>& thread_vec, const int& threads_count, const int& count_size, std::vector<std::chrono::duration<double>>& thread_work_time_vec) {
	
	print_thread_table_columns();
	for (int i = 0; i < threads_count; i++) print_thread_num(i);
	for (int i = 0; i < threads_count; i++) thread_vec.push_back(std::thread(test_func, count_size, std::ref(thread_work_time_vec.at(i)), i, threads_count));
	


	//print_thread_num(i);
		
	
	
}




int main(){
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	const int threads_count = 10; //количество потоков
	const int count_size = 100; //длина расчета
	std::vector<std::thread> thread_vec;
	std::vector<std::chrono::duration<double>> thread_work_time_vec(threads_count);
	for (std::chrono::duration<double>& n : thread_work_time_vec) n = std::chrono::seconds(0);
	
	thread_init(thread_vec, threads_count, count_size, thread_work_time_vec);
	
	
	try {
		for (std::thread& n : thread_vec) n.join();
	}
	catch (const std::system_error& e) {
		std::cout << "\n";
		std::cout << e.code() << "\n";
		std::cout << e.what() << "\n";
	}
	gotoxy(0, threads_count + plus_one_more_line + 2);
	
	return 0;
}