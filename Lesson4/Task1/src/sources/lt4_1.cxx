
#include <windows.h>
#include <transform.h>

int main() {
	
SetConsoleCP(CP_UTF8);
SetConsoleOutputCP(CP_UTF8);
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0002);

Line ln(1, 2, 3, 4);
Shape* shape_ptr = &ln;
transform tf(shape_ptr);
auto r = tf.shift(1, 2, 3);

system("pause");

	return 0;
}