#pragma once
#include "Game2D.h"
#include "GeometricObject.h"

namespace jm
{
	class Star : public GeometricObject
	{
	private:
		float outer_radius, inner_radius;

	public:
		Star()
			: GeometricObject(Colors::red, {0.0f, 0.0f}, 0.0f)
		{}

		Star(const RGB& _color, const vec2& _pos, const float& _rot, const float& _outer_radius, const float& _inner_radius)
			: GeometricObject(_color, _pos, _rot), outer_radius(_outer_radius), inner_radius(_inner_radius)
		{}

		void drawGeometry() const override
		{
			drawFilledStar(color, outer_radius, inner_radius);
		}
	};
}