#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#pragma execution_character_set("utf-8")
#include <windows.h>


#define MAX_CLIENT_COUNT 10
using namespace std::chrono_literals;
//int client_count;
std::vector<std::thread> queue_threads;

void client(int& client_count) {
	bool increasing_flag = 0;
	while (true) {
		if (client_count < MAX_CLIENT_COUNT){
			increasing_flag = true;
		std::cout << "+1 клиент в очереди. Кол-во клиентов = " << ++client_count << std::endl;
	}
		
		if (client_count == MAX_CLIENT_COUNT && increasing_flag) break; else std::this_thread::sleep_for(1s);
			
		
	}
	
	
	

}

void operationist(int& client_count) {
	bool decreasing_flag = 0;
	while (true) {
		if (client_count > 0) {
			decreasing_flag = true;
			std::cout << "-1 клиент в очереди. Кол-во клиентов = " << --client_count << std::endl;
			
		}
		if (client_count == 0 && decreasing_flag) break; else std::this_thread::sleep_for(2s);
			
		
			
		
		
		
	}
	
	
	
}

int main() {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	int client_count = 0;// MAX_CLIENT_COUNT;
	
	std::thread th1(client, std::ref(client_count));
	std::thread th2(operationist, std::ref(client_count));

	th1.join();
	th2.join();

	return 0;
}