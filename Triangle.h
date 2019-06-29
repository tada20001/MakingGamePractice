#pragma once
#include "GeometricObject.h"
namespace jm
{
	class Triangle : public GeometricObject
	{
	private:
		
		float edge_length = 0.0f;

	public:
		Triangle()
			:GeometricObject(Colors::red, {0.0f, 0.0f}, 0.0f)
		{}

		~Triangle()
		{
			std::cout << "Triangle destructor" << std::endl;
		}

		Triangle(const RGB& _color, const vec2& _pos, const float& _rot, const float& _edge_length)
			: GeometricObject(_color, _pos, _rot)
		{
			edge_length = _edge_length;
		}
		
		void drawGeometry() const override
		{
			drawFilledTriangle(GeometricObject::color, edge_length);
		}

	};
}