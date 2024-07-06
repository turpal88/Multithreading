#include <iostream>
#include <chrono>
#ifdef _WIN32
#include <windows.h>
#endif

#include <thread_pool.h>




const int COUNT_NUM = 10;
const int ADDED_FUNC_NUM = 5;
std::mutex main_mtx;
void test_func(int i){
	std::lock_guard<std::mutex> lk(main_mtx);
	std::cout << "Я функция номер " << i << ", выполняюсь в потоке с id = " << std::this_thread::get_id() << std::endl; 
}


int main(){
	
#ifdef _WIN32	
SetConsoleCP(CP_UTF8);
SetConsoleOutputCP(CP_UTF8);
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);
#endif

int j = COUNT_NUM;
std::vector<std::function<void(void)>> test_vec;

thread_pool tp;

//std::function<void(void)> temp_obj = test_func;
int i = 0;
int k = 1;
while(j > 0){
	
	for (; i < ADDED_FUNC_NUM * k; ++i) {
		test_vec.push_back([i]() {test_func(i); });
		std::cout << "Функция номер " << i << " добавлена в очередь потоком с id = " << std::this_thread::get_id() << std::endl;
	}
	
	std::this_thread::sleep_for(1s);
	tp.submit(test_vec);
	test_vec.clear();
	--j;
	++k;
}





tp.join_threads();


#ifdef _WIN32
system("pause");
#endif

return 0;	
}