#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include "windows.h"
const int MAX_CLIENT_COUNT = 10;



void func5(std::atomic<int>& current_client_count, std::atomic<bool>& is_client_action_started, std::atomic<bool>& is_client_increasing_enough)
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if (current_client_count.load() < MAX_CLIENT_COUNT) {
			current_client_count.store(++current_client_count);
			if (!is_client_action_started.load()) is_client_action_started.store(true);
			std::cout << "+1 клиент. Клиентов в очереди - " + std::to_string(current_client_count.load()) + "\n";
		}
		if (current_client_count.load() == MAX_CLIENT_COUNT) {
			
			is_client_increasing_enough.store(true);
			break;
		} 
	}
	
	
}
void func6(std::atomic<int>& current_client_count, std::atomic<bool>& is_client_action_started, std::atomic<bool>& is_client_increasing_enough)
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		if (current_client_count.load() > 0 && is_client_action_started.load() || is_client_increasing_enough.load() == true) {
			
			current_client_count.store(--current_client_count);
				std::cout << "-1 клиент. Клиентов в очереди - " + std::to_string(current_client_count.load()) + "\n";
			
		}


		if (current_client_count.load() == 0 && is_client_action_started.load() && is_client_increasing_enough.load() == true) {
			std::cout << "Обход клиентов завершен\n";
			break;
		}
	}
	
	
}



int main() {
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	std::atomic<int> current_client_count = 0;
	std::atomic<bool> is_client_operationist_actions_finished = false;
	std::atomic<bool> is_client_action_started = false;
	std::atomic<bool> is_client_increasing_enough = false;
	std::thread t3(func5, std::ref(current_client_count), std::ref(is_client_action_started), std::ref(is_client_increasing_enough));
	std::thread t4(func6, std::ref(current_client_count), std::ref(is_client_action_started), std::ref(is_client_increasing_enough));
	
		t3.join();
		t4.join();
	
	
	return 0;
}