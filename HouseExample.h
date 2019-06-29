#pragma once
#include "Game2D.h"
#include "RandomNumberGenerator.h"

namespace jm
{
	class House
	{
	private:
		RGB roof_color;
		vec2 pos;
		float angle = 0.0f;

	public:
		House()
			: roof_color(Colors::red), pos({ 0.0f, 0.0f }), angle(0.0f)
		{}

		House(const RGB& _roof_color, const vec2& _pos, const float& _angle)
			: roof_color(_roof_color), pos(_pos), angle(_angle)
		{}

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				rotate(angle);

				// body
				drawFilledBox(Colors::yellow, 0.2f, 0.2f);

				// roof
				drawFilledTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
				drawWiredTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });

				// window
				drawFilledBox(Colors::skyblue, 0.1f, 0.1f);
				drawWiredBox(Colors::gray, 0.1f, 0.1f);
				drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
				drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });
			}
			endTransformation();
		}

		void setPos(const vec2& _pos) { pos = _pos; }
		void setRoofColor(const RGB& c) { roof_color = c; }
		void setAngle(const float& f) { angle = f; }
		
	};

	
	class HouseExample : public Game2D
	{
	public:
		RandomNumberGenerator rnd;
		House houses[100];

		HouseExample()
		{

			for (int i = 0; i < 100; ++i)
			{
				houses[i].setPos(vec2(-1.5f + 0.1f * float(i), rnd.getFloat(-1.0f, 1.0f)));
				houses[i].setRoofColor(getRandomColor());
				houses[i].setAngle(rnd.getFloat(0.0f, 360.0f));
			}
		}

		const RGB& getRandomColor()
		{
			return RGB(rnd.getFloat(0.0f, 1.0f), rnd.getFloat(0.0f, 1.0f), rnd.getFloat(0.0f, 1.0f));
		}

		void update() override
		{
			for (int i = 0; i < 100; ++i)
				houses[i].draw();
		}
	};
}