//#include "export.h"
#include <iostream>
#include <future>


template<class T>
class SelectionSort{
	private:
	int min;
	std::promise<T> selection_sort_promise;
	std::future<T> selection_sort_future;
	//void set(std::vector<T>& vec);
	//void get(std::vector<T>& vec);
	
	void print_vec(std::vector<T>& vec, int temp_mark){
		if(temp_mark == 0) std::cout << "Исходный массив: ";
		else if(temp_mark == 1) std::cout << "Отсортированный массив: ";
		
		for(auto& t : vec) std::cout << t << " ";
		std::cout << "\n";
		
	}
	
	void sorting_procedure(std::vector<T>& vec){
		if(vec.size() == 0) selection_sort_promise.set_exception(std::make_exception_ptr(std::logic_error("Размер массива равен 0\n")));
		//print_vec(vec, 0);
		for(int i = 0; i < vec.size() - 1; ++i){
			
			min = i;
			for(int j = i + 1; j < vec.size(); ++j){
				//if(min == j) continue;
				if(vec.at(j) < vec.at(min)) min = j;
					//std::swap(vec.at(j), vec.at(i));
					
				
				
			}
			if(min == i) continue;
			std::swap(vec.at(i), vec.at(min));
			
		}
		selection_sort_promise.set_value(1);
		//print_vec(vec, 1);
		
	}
	
	public:
	SelectionSort(SelectionSort const&) = delete;
	SelectionSort& operator=(SelectionSort const&) = delete;
	SelectionSort(){
		selection_sort_future = selection_sort_promise.get_future();
	}
	
	
	void make_selection_sort(std::vector<T>& vec){
		print_vec(vec, 0);
		
		std::thread th(&SelectionSort::sorting_procedure, this, std::ref(vec));
		try{
			selection_sort_future.get();
			print_vec(vec, 1);
			
		}
		catch(std::exception& e){
			
			std::cout << e.what();
		}
		
		
		th.join();
	}
	
	
	
	
	
};