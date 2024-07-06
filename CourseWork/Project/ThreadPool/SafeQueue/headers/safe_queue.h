#include <queue>
#include <mutex>
#include <condition_variable>
//#include <export_interface.h>

template<typename Func>
class safe_queue{
	private:
	std::queue<Func> sf;
	std::mutex m;
	std::condition_variable cv;
	bool ready_1;
	//bool ready_2;
	public:
		
	safe_queue(){
		ready_1 = false;
		//ready_2{false};
		
	}
	
	~safe_queue(){
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [&](){return sf.empty();});
		cv.notify_all();
		
	}
	
	void push(Func func){
		std::unique_lock<std::mutex> lk(m);
		//cv.wait(lk, [this](){return ready_1;});
		sf.push(func);
		//ready_1 = true;
		lk.unlock();
		cv.notify_all();
		
	}
	Func pop(){
		
		
			std::unique_lock<std::mutex> lk(m);
			cv.wait(lk, [this](){return !sf.empty();});
			Func temp = std::move(sf.front());
		    sf.pop();
			//ready_2 = true;
			//lk.unlock();
			//cv.notify_one();
			return temp;
		
		
		
		
	}
	
	
};