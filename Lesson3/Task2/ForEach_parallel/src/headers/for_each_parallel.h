//#include "export.h"
#include <iostream>
#include <future>
#include <thread>
#include <windows.h>
#include <chrono>

using namespace std::chrono_literals;


template<class It, class T>
class ForEach_Parallel{
	private:
	int core_count;
	//It begin;
	//It end;
	std::vector<std::future<T>> future_vector;
	//void get_it(It begin, It end){
	//	this->begin = begin;
	//	this->end = end;
		
	//}
	void gotoxy(int x, int y)
	{
		COORD cd;
		cd.X = x;
		cd.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);

	}

	public:
	ForEach_Parallel(){
		core_count = std::thread::hardware_concurrency();
		
	}
	
	ForEach_Parallel(ForEach_Parallel const&) = delete;
	ForEach_Parallel& operator=(ForEach_Parallel const&) = delete;

	


	T make_accumulate_element(It begin, It end, T(*f)(It, It), It, It){
		//this->get_it(begin, end);
		int d = std::distance(begin, end); 
		//std::unique_ptr<It> temp_iterator = begin;
		if(d == 2) return f(begin, end);
		//else if(d/2 <= core_count){
			
		//		for(int i = 0; i < d/2; ++i){
		//			if(i == (d/2 - 1) && d%2 != 0) {
		//			std::future<T> ft = std::async(std::launch::async, make_accumulate_element<It>, begin, begin + 1 + d%2, &f);
		//			future_vector.push_back(std::move(ft));
		//			}
				    
		//		else {
		//			std::future<T> ft = std::async(std::launch::async, make_accumulate_element<It>, begin, begin + 1, &f);
		//			future_vector.push_back(std::move(ft));
		//			begin += 2;
					
		//		}
					
		//		}
		//		T sum;
		//		for(int i = 0; i < future_vector.size(); ++i) sum += future_vector.at(i).get();
		//		return sum;
				
			
			
		//}
		else{
			//int j = (d/2 <= core_count)? 1 : (d/2)/core_count; //1 2 3 4 5
			//int k = (d/2 <= core_count)? d%2 : (d/2)%core_count; //begin+ 1 3 5 7 9
										// begin+ 
			
			//bool is_remainder_more_0 = (k > 0)? true : false;
			//int p = (is_remainder_more_0)? 1 : 0;
			for(int i = 0; i < core_count; ++i){
				//if(k == 0 && is_remainder_more_0) p = 0;
				future_vector.push_back(std::async(std::launch::async, &ForEach_Parallel::make_accumulate_element, this, begin, begin + 1, f, begin, begin + 1));
				//future_vector.push_back(std::async(std::launch::async, &ForEach_Parallel::make_accumulate_element, this, begin, begin + 1 + 2 * j + 2 * p, f, begin, begin + 1 + 2 * j + 2 * p));
				if ((begin + 2) <= end - 2) begin += 2; else break;
					//if((begin + 2 + 2 * j + 2 * p) < end - 1) begin += 2 + 2 * j + 2 * p; else break;
					//if(is_remainder_more_0 && p != 0) --k;
				
				
			}
			
		}
		T sum;
		for (int i = 0; i < future_vector.size(); ++i) {
			gotoxy(21 + 2*i, 1);
			T temp = future_vector.at(i).get();
			std::cout << temp;
			std::this_thread::sleep_for(500ms);
			sum += temp;
			
		} 
		return sum;
		
	}
	
	
	
};