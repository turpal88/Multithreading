#include <iostream>
#include <vector>
#include <thread>
#include <functional>

#include <export.h>
#include <safe_queue.h>

using namespace std::chrono_literals;

class thread_pool{
	private:
	int core_count;
	std::vector<std::thread> thread_vector;
	safe_queue<std::function<void(void)>> safe_q;
	std::mutex tp_mutex;
	public:
	API_THREAD_POOL thread_pool();
	void API_THREAD_POOL work();
	void API_THREAD_POOL submit(std::vector<std::function<void(void)>>& f_vector);
	//API_THREAD_POOL ~thread_pool();
	API_THREAD_POOL void join_threads();
	
};