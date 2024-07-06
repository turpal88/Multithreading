#include <thread_pool.h>


thread_pool::thread_pool(){
	
	core_count = std::thread::hardware_concurrency();
	for(int i = 0; i < core_count; ++i) thread_vector.push_back(std::thread(&thread_pool::work, this));
}


/*
thread_pool::~thread_pool(){
	
	for(auto& t : thread_vector){
		
		if(t.joinable()) t.join();
	}
}
*/

void thread_pool::work(){
	//std::unique_lock<std::mutex> lk(tp_mutex);
	std::function<void(void)> temp_func = safe_q.pop();
	//auto k = [temp_func](){
	std::unique_lock<std::mutex> lk(tp_mutex);
		temp_func();
		lk.unlock();
		std::this_thread::sleep_for(0.5s);
//	};
	
} 

void thread_pool::submit(std::vector<std::function<void(void)>>& f_vector){
	for (int i = 0; i < f_vector.size(); ++i) 
	
	 safe_q.push(f_vector.at(i));
		
		
	
	
} 


void thread_pool::join_threads() {
	for (auto& t : thread_vector) {

		if (t.joinable()) t.join();
	}
}
