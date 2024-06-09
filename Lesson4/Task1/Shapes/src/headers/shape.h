#pragma once
#include <export.h>
#include<string>
#include<cmath>
#include <vector>

class API_SHAPES Shape {
private:
	//int type;
	
protected:
	//int _x1, _y1;
	std::vector<int> _x;
	std::vector<int> _y;
	int x_size;
	int y_size;
	double volume;
	double square;
	
	Shape(int _x1, int _y1);
public:
	//Shape() = delete;
	void set_x(int _x_coord, int index);
	void set_y(int _y_coord, int index);
	virtual void set_z(int _y_coord, int index);
	int get_x(int index);
	int get_y(int index);
	virtual int get_z(int index);
	int get_x_size();
	int get_y_size();
	virtual int get_z_size();
	//int getType() { return type; }

};

class API_SHAPES Line : public Shape {
private:
	
	//std::vector<int> _x;
	//std::vector<int> _y;
public:
	
	Line(int _x1, int _y1, int _x2, int _y2);
};

class API_SHAPES Square : public Shape {
private:
	
	//int _x2, _y2, _x3, _y3, _x4, _y4;
public:
	
	Square(int _x1, int _y1, int _x2, int _y2, int _x3, int _y3, int _x4, int _y4);

};

class API_SHAPES Cube : public Shape {
private:
	std::vector<int> _z;
	int z_size;
	//int _x2, _y2, _z1, _z2, _x3, _y3, _z3, _x4, _y4, _z4, _x5, _y5, _z5, _x6, _y6, _z6, _x7, _y7, _z7, _x8, _y8, _z8;
public:
	int get_z(int index) override;
	void set_z(int _z_coord, int index) override;
	int get_z_size() override;

	Cube(int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8);

};

class API_SHAPES Circle : public Shape {
//private:
//	double R;
protected:
	double R;
//	int _x1, _y1;
public:
	
	Circle(int _x1, int _y1, double R);

};

class API_SHAPES Cylinder : public Circle {
private:
	double H;
public:
	
	Cylinder(int _x1, int _y1, double R, double H);


};
