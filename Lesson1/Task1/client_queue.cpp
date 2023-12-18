#include <thread>
#include <chrono>
#include <iostream>
#include "windows.h"
#define MAX_CLIENT_COUNT 10

void make_clock_count(std::chrono::time_point<std::chrono::steady_clock>& start, std::chrono::duration<double>& elapsed_seconds) {
	//std::chrono::duration<double> elapsed_seconds{ 0.0 };
	
	
	auto end{ std::chrono::steady_clock::now() };
	elapsed_seconds = end - start;
	
	
	
	
}

void virtual_client(int& current_client_count) {
	if (current_client_count < MAX_CLIENT_COUNT) {
		current_client_count++;
		std::cout << "+1 Клиент. Клиентов в очереди - " + std::to_string(current_client_count) + "\n";
	}
	
	
}
void virtual_operationist(int& current_client_count) {
	if (current_client_count > 0) {
		current_client_count--;
		std::cout << "-1 Клиент. Клиентов в очереди - " + std::to_string(current_client_count) + "\n";
	}
	
	
}
int main() {
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	int current_client_count = 0;
	bool is_client_increasing_enough = true;
	while (true) {
		auto start{ std::chrono::steady_clock::now() };
		std::chrono::duration<double> elapsed_seconds{ 0.0 };
		while (elapsed_seconds.count() < 2.0) {
			make_clock_count(start, elapsed_seconds);
			if (elapsed_seconds.count() == 1.0 && is_client_increasing_enough){
				std::thread thread1(virtual_client, std::ref(current_client_count));
				thread1.join();
				
			}
			if (elapsed_seconds.count() == 2.0) {
				if (is_client_increasing_enough) {
					std::thread thread1(virtual_client, std::ref(current_client_count));
					thread1.join();
				}
				
				if (current_client_count == MAX_CLIENT_COUNT) is_client_increasing_enough = false;
				
				std::thread thread2(virtual_operationist, std::ref(current_client_count));
				thread2.join();
				break;
			}
		}


		if (current_client_count == 0) {
			std::cout << "Обход очереди закончен\n";
			break;
		}
		
	}
	return 0;
}