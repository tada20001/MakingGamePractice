#include "GeometricObject.h"
#include "Triangle.h"
#include "Box.h"
#include "Circle.h"
#include "Star.h"

namespace jm
{
	GeometricObject* GeometricObject::makeTriangle(const RGB& _color, const vec2& _pos, const float& _rot, const float& _edge_length)
	{
		return new Triangle(_color, _pos, _rot, _edge_length);
	}

	GeometricObject* GeometricObject::makeBox(const RGB& _color, const vec2& _pos, const float& _rot, const float& _width, const float& _height)
	{
		return new Box(_color, _pos, _rot, _width, _height);
	}

	GeometricObject* GeometricObject::makeCircle(const RGB& _color, const vec2& _pos, const float& _rot, const float& _radius)
	{
		return new Circle(_color, _pos, _rot, _radius);
	}

	GeometricObject* GeometricObject::makeStar(const RGB& _color, const vec2& _pos, const float& _rot, const float& _outer_radius, const float& _inner_radius)
	{
		return new Star(_color, _pos, _rot, _outer_radius, _inner_radius);
	}
}

