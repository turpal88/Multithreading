#include "selection_sort.h"
#include <windows.h>
#pragma execution_character_set("utf-8")

int main(){
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
    //std::vector<int> vec1;
	std::vector<int> vec1{91, 37, 55, 70, 93, 15, 78};
	SelectionSort<int> ss1;
	ss1.make_selection_sort(vec1);
system("pause");
return 0;	
}