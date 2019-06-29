#pragma once
#include "Game2D.h"


namespace jm
{
	class GeometricObject
	{
	protected:
		RGB color = Colors::red;
		vec2 pos = { 0.0f, 0.0f };
		float rot = { 0.0f };

	public:
	/*	GeometricObject()
		{}*/

		GeometricObject(const RGB& _color, const vec2& _pos, const float& _rot)
			: color(_color), pos(_pos), rot(_rot)
		{}

		virtual ~GeometricObject()
		{
		}

		virtual void drawGeometry() const = 0;

		void draw()
		{
			beginTransformation();
			{
				translate(pos);

				rotate(rot);

				drawGeometry();
			}
			endTransformation();
		}

		void setColor(const RGB& _color) { color = _color; }
		void setPos(const vec2& _pos) { pos = _pos; }
		void setRot(const float& _rot) { rot = _rot; }

		static GeometricObject* makeTriangle(const RGB& _color, const vec2& _pos, const float& _rot, const float& _edge_length);
		static GeometricObject* makeBox(const RGB& _color, const vec2& _pos, const float& _rot, const float& _width, const float& _height);
		static GeometricObject* makeCircle(const RGB& _color, const vec2& _pos, const float& _rot, const float& _radius);
		static GeometricObject* makeStar(const RGB& _color, const vec2& _pos, const float& _rot, const float& _outer_radius, const float& _inner_radius);

	};
}