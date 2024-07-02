#include "transform.h"


transform::transform(Shape* sh) {
	shape = sh;
}



Shape* transform::shift(int m, int n, int k)
{
	for (int i = 0; i < shape->get_x_size(); i++) shape->set_x((shape->get_x(i) + m), i);
	for (int i = 0; i < shape->get_y_size(); i++) shape->set_y((shape->get_y(i) + n), i);
	if(shape->get_z_size() > 0) for (int i = 0; i < shape->get_z_size(); i++) shape->set_z((shape->get_z(i) + k), i);

	
	return shape;
}

Shape* transform::scaleX(int a)
{
	for (int i = 0; i < shape->get_x_size(); i++) shape->set_x((shape->get_x(i) * a), i);
	
	return shape;
}

Shape* transform::scaleY(int d)
{
	for (int i = 0; i < shape->get_y_size(); i++) shape->set_y((shape->get_y(i) * d), i);
	
	return shape;
}

Shape* transform::scaleZ(int e)
{
	if (shape->get_z_size() > 0) for (int i = 0; i < shape->get_z_size(); i++) shape->set_z((shape->get_z(i) * e), i);
	
	return shape;
}

Shape* transform::scale(int s)
{
	for (int i = 0; i < shape->get_x_size(); i++) shape->set_x((shape->get_x(i) / s), i);
	for (int i = 0; i < shape->get_y_size(); i++) shape->set_y((shape->get_y(i) / s), i);
	if (shape->get_z_size() > 0) for (int i = 0; i < shape->get_z_size(); i++) shape->set_z((shape->get_z(i) / s), i);

	
	return shape;
}