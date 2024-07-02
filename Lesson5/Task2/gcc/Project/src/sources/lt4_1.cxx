
#ifdef _WIN32
#include <windows.h>
#endif
#include <transform.h>
#include <iostream>

int main() {

#ifdef _WIN32	
SetConsoleCP(CP_UTF8);
SetConsoleOutputCP(CP_UTF8);
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);
#endif
Line ln(1, 2, 3, 4);
Shape* shape_ptr = &ln;
transform tf(shape_ptr);
auto r = tf.shift(1, 2, 3);

#ifdef _WIN32
system("pause");
#endif
std::cout << "Programm has been started succesfully" << std::endl;
	return 0;
}