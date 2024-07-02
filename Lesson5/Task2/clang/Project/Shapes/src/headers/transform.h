#pragma once
#include"shape.h"
class API_SHAPES transform
{
public:
	transform(Shape* sh);
	

	Shape* shift(int m, int n, int k);
	Shape* scaleX(int a);
	Shape* scaleY(int d);
	Shape* scaleZ(int e);
	Shape* scale(int s);

private:
	Shape* shape;
};
