#include <windows.h>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#pragma execution_character_set("utf-8")

#define UNIQUE_LOCK
//#define LOCK_GUARD
//#define SCOPED_LOCK

class Data {
private:
	int obj_num;
	std::mutex m;
	int data_field_1;
	double data_field_2;
	unsigned long data_field_3;
public:
	Data(int data_filed_1, double data_field_2, unsigned long data_field_3, int obj_num) :data_field_1(data_filed_1), data_field_2(data_field_2), data_field_3(data_field_3), obj_num(obj_num) {}
	//Data(const Data& other_data) {
	//}

	Data& operator=(const Data& other_data) = delete;
	std::mutex* get_mutex() {
		return &this->m;
	}

	int* get_data_field_1() {
		return &this->data_field_1;
	}

	double* get_data_field_2() {
		return &this->data_field_2;
	}
	unsigned long* get_data_field_3() {
		return &this->data_field_3;
	}

	void put_data_field_1(int data_field_1) {
		this->data_field_1 = data_field_1;
	}
	void put_data_field_2(double data_field_2) {
		this->data_field_2 = data_field_2;
	}

	void put_data_field_3(unsigned long data_field_3) {
		this->data_field_3 = data_field_3;
	}

	int get_obj_num() {
		return this->obj_num;
	}

	void print_data() {

		std::cout << "Я объект номер " << obj_num << ". Мои поля:" << std::endl;
		std::cout << "data_field_1 = " << data_field_1 << " ";
		std::cout << "data_field_2 = " << data_field_2 << " ";
		std::cout << "data_field_3 = " << data_field_3 << std::endl;
	}
};

void swap(std::shared_ptr<Data> data_1, std::shared_ptr<Data> data_2) {
	std::cout << "Замена объекта " << data_1->get_obj_num() << " с объектом " << data_2->get_obj_num() << "...\n";
#ifdef UNIQUE_LOCK
	std::unique_lock<std::mutex> lk1(*data_1->get_mutex(), std::defer_lock);
	std::unique_lock<std::mutex> lk2(*data_2->get_mutex(), std::defer_lock);
	std::lock(lk1, lk2);
#endif
#ifdef LOCK_GUARD
	std::lock(*data_1->get_mutex(), *data_2->get_mutex());
	std::lock_guard<std::mutex> lk1(*data_1->get_mutex(), std::adopt_lock);
	std::lock_guard<std::mutex> lk2(*data_2->get_mutex(), std::adopt_lock);
#endif
#ifdef SCOPED_LOCK
	std::scoped_lock(*data_1->get_mutex(), *data_2->get_mutex());
#endif
	int temp_int_1, temp_int_2;
	double temp_double_1, temp_double_2;
	unsigned long temp_ul_1, temp_ul_2;
	temp_int_1 = *data_1->get_data_field_1(); temp_int_2 = *data_2->get_data_field_1();
	temp_double_1 = *data_1->get_data_field_2(); temp_double_2 = *data_2->get_data_field_2();
	temp_ul_1 = *data_1->get_data_field_3(); temp_ul_2 = *data_2->get_data_field_3();

	data_1->put_data_field_1(temp_int_2);
	data_1->put_data_field_2(temp_double_2);
	data_1->put_data_field_3(temp_ul_2);

	data_2->put_data_field_1(temp_int_1);
	data_2->put_data_field_2(temp_double_1);
	data_2->put_data_field_3(temp_ul_1);

	std::cout << "Данные объектов " << data_1->get_obj_num() << " и " << data_2->get_obj_num() << " заменены между собой\n";
}

int main() {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0003);
	const unsigned int th_count = std::thread::hardware_concurrency();
	std::vector<std::shared_ptr<Data>> data_vector;
	std::vector<std::thread> th_v;
	try {
		if (th_count > std::thread::hardware_concurrency()) throw std::out_of_range("Многовато потоков для данной машины");
		if (th_count < 1) throw std::out_of_range("Где потоки?");
		for (unsigned int i = 0; i < th_count; ++i) data_vector.push_back(std::make_shared<Data>(5 * i, 7.6 * i, 15231 * i, i));
		for (auto& n : data_vector) {
			n->print_data();
			std::cout << "\n\n";
		}
		th_v.push_back(std::thread(swap, data_vector.at(0), data_vector.at(5)));
		th_v.push_back(std::thread(swap, data_vector.at(5), data_vector.at(1)));
		th_v.push_back(std::thread(swap, data_vector.at(1), data_vector.at(8)));
		/*
		for (unsigned int i = 0; i < th_count - 1; ++i) {
			th_v.push_back(std::thread(swap, data_vector.at(i), data_vector.at(i + 1)));
		} 
		*/
		/*
		for (auto& n : data_vector) {
			n->print_data();
			std::cout << "\n\n";
		}
		*/
		

		for (auto& n : th_v) {
			if (n.joinable()) n.join();
		}
		std::cout << "\n\n";
		data_vector.at(0)->print_data();
		data_vector.at(1)->print_data();
		data_vector.at(5)->print_data();
		data_vector.at(8)->print_data();
		
	}
	catch (std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}
	


	return 0;
}

