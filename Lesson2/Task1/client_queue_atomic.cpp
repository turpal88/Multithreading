#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#pragma execution_character_set("utf-8")
#include <windows.h>
#include <atomic>


#define MAX_CLIENT_COUNT 10
using namespace std::chrono_literals;
std::atomic<int> client_count{ 0 };
int old_client_count{ 0 };


void client() {
	
	int client_client_count{ 0 };
	
	while (client_client_count < MAX_CLIENT_COUNT) {
		std::this_thread::sleep_for(1s);
		old_client_count = client_count.fetch_add(1, std::memory_order_release);
			
			client_client_count = client_count.load(std::memory_order_acquire);
			std::cout << "+1 клиент в очереди. Кол-во клиентов = " << client_client_count << std::endl;
	}
	return;

	



}

void operationist() {
	
	int operationist_client_count{ 0 };
	while (old_client_count == 0);

	while (old_client_count > 0) {
		std::this_thread::sleep_for(1s);
		client_count.fetch_sub(1, std::memory_order_release);
		operationist_client_count = client_count.load(std::memory_order_acquire);
		std::cout << "-1 клиент в очереди. Кол-во клиентов = " << operationist_client_count << std::endl;
		while (!client_count.compare_exchange_weak(old_client_count, operationist_client_count, std::memory_order_release));
		
		
	}
	return;
	






	



}

int main() {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	

	std::thread th1(client);
	std::thread th2(operationist);

	th1.join();
	th2.join();

	return 0;
}