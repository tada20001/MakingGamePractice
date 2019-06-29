#pragma once
#include "GeometricObject.h"

namespace jm
{
	class Box : public GeometricObject
	{
	private:
		
		float width = 0.0f;
		float height = 0.0f;

	public:
		Box()
			:GeometricObject(Colors::red, { 0.0f, 0.0f }, 0.0f)
		{}

		Box(const RGB& _color, const vec2& _pos, const float& _rot, const float& _width, const float& _height)
			: GeometricObject(_color, _pos, _rot), width(_width), height(_height)
		{}

		~Box()
		{
			std::cout << "Box destructor" << std::endl;
		}

		void drawGeometry() const override
		{
			drawFilledBox(GeometricObject::color, width, height);
		}
	};
}