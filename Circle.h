#pragma once
#include "GeometricObject.h"

namespace jm
{
	class Circle : public GeometricObject
	{
	private:
		float radius = 0.0f;

	public:
		Circle()
			:GeometricObject(Colors::red, { 0.0f, 0.0f }, 0.0f)
		{}

		~Circle()
		{
			std::cout << "Circle destructor" << std::endl;
		}

		Circle(const RGB& _color, const vec2& _pos, const float& _rot, const float&_radius)
			: GeometricObject(_color, _pos, _rot), radius(_radius)
		{}

		void drawGeometry() const override
		{
			drawFilledCircle(GeometricObject::color, radius);
		}
	};
}