#define _USE_MATH_DEFINES
#include"shape.h"



Shape::Shape(int _x1, int _y1) {
	_x.push_back(_x1);
	_y.push_back(_y1);
}


void Shape::set_x(int _x_coord, int index) {
	_x.at(index) = _x_coord;
}
void Shape::set_y(int _y_coord, int index) {
	_y.at(index) = _y_coord;;
}

int Shape::get_x(int index) {
	return _x.at(index);
}

int Shape::get_y(int index) {
	return _y.at(index);
}

int Shape::get_x_size() {
	return x_size;
}
int Shape::get_y_size() {
	return y_size;
}


int Shape::get_z(int index) { return 0; }
void Shape::set_z(int _z_coord, int index) {}
int Shape::get_z_size() { return 0; }

Line::Line(int _x1, int _y1, int _x2, int _y2) : Shape(_x1, _y1){
	_x.push_back(_x2);
	_y.push_back(_y2);
	x_size = 2;
	y_size = 2;
	// считаем площадь фигуры
	square = 0;
	// считаем объем фигуры
	volume = 0;
}




Square::Square(int _x1, int _y1, int _x2, int _y2, int _x3, int _y3, int _x4, int _y4) : Shape(_x1, _y1) {
	_x.push_back(_x2); _y.push_back(_y2);
	_x.push_back(_x3); _y.push_back(_y3);
	_x.push_back(_x4); _y.push_back(_y4);
	x_size = 4;
	y_size = 4;
	// считаем площадь фигуры
	square = abs(_x.at(0) - _x.at(1)) * abs(_y.at(0) - _y.at(1));
	// считаем объем фигуры
	volume = 0;

}



Cube::Cube(int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8) : Shape(_x1, _y1) {
	_z.push_back(_z1);
	_x.push_back(_x2); _y.push_back(_y2); _z.push_back(_z2);
	_x.push_back(_x3); _y.push_back(_y3); _z.push_back(_z3);
	_x.push_back(_x4); _y.push_back(_y4); _z.push_back(_z4);
	_x.push_back(_x5); _y.push_back(_y5); _z.push_back(_z5);
	_x.push_back(_x6); _y.push_back(_y6); _z.push_back(_z6);
	_x.push_back(_x7); _y.push_back(_y7); _z.push_back(_z7);
	_x.push_back(_x8); _y.push_back(_y8); _z.push_back(_z8);
	x_size = 8;
	y_size = 8;
	z_size = 8;
	// считаем площадь фигуры
	square = 2 * abs(_x.at(0) - _x.at(1)) * abs(_y.at(0) - _y.at(1)) + 2 * abs(_x.at(0) - _x.at(1)) * abs(_z.at(0) - _z.at(1)) + 2 * abs(_y.at(0) - _y.at(1)) * abs(_z.at(0) - _z.at(1));
	// считаем объем фигуры
	volume = abs(_x.at(0) - _x.at(1)) * abs(_y.at(0) - _y.at(1)) * abs(_z.at(0) - _z.at(1));
	
}

void Cube::set_z(int _z_coord, int index) {
	_z.at(index) = _z_coord;
}

int Cube::get_z(int index) {
	return _z.at(index);
}

int Cube::get_z_size() {
	return z_size;
}

Circle::Circle(int _x1, int _y1, double R) : Shape(_x1, _y1) {
	R = R;
	// считаем площадь фигуры
	square = M_PI * R * R;
	// считаем объем фигуры
	volume = 0;
}



Cylinder::Cylinder(int _x1, int _y1, double R, double H) : Circle(_x1, _y1, R) {
	H = H;
	// считаем площадь фигуры
	square = M_PI * R * R + 2 * R * H;
	// считаем объем фигуры
	volume = M_PI * R * R * H;
}







