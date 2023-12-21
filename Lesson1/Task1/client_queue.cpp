#include <thread>
#include <chrono>
#include <iostream>
#include "windows.h"
const int MAX_CLIENT_COUNT = 10;



void func5(int& current_client_count, bool& is_client_action_started, bool& is_client_increasing_enough)
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if (current_client_count < MAX_CLIENT_COUNT) {
			current_client_count++;
			if (!is_client_action_started) is_client_action_started = true;
			std::cout << "+1 клиент. Клиентов в очереди - " + std::to_string(current_client_count) + "\n";
		}
		if (current_client_count == MAX_CLIENT_COUNT) {
			
			is_client_increasing_enough = true;
			break;
		} 
	}
	
	
}
void func6(int& current_client_count, bool& is_client_action_started, bool& is_client_increasing_enough)
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		if (current_client_count > 0 && is_client_action_started || is_client_increasing_enough == true) {
			
				current_client_count--;
				std::cout << "-1 клиент. Клиентов в очереди - " + std::to_string(current_client_count) + "\n";
			
		}


		if (current_client_count == 0 && is_client_action_started && is_client_increasing_enough == true) {
			std::cout << "Обход клиентов завершен\n";
			break;
		}
	}
	
	
}



int main() {
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	int current_client_count = 0;
	bool is_client_operationist_actions_finished = false;
	bool is_client_action_started = false;
	bool is_client_increasing_enough = false;
	std::thread t3(func5, std::ref(current_client_count), std::ref(is_client_action_started), std::ref(is_client_increasing_enough));
	std::thread t4(func6, std::ref(current_client_count), std::ref(is_client_action_started), std::ref(is_client_increasing_enough));
	
		t3.join();
		t4.join();
	
	
	return 0;
}