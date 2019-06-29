#pragma once
#include "Game2D.h"
#include "RandomNumberGenerator.h"
#include <vector>

namespace jm
{
	class RigidCircle
	{
	public:
		vec2 pos;
		vec2 vel;
		float radius = 0.1f;
		RGB color = Colors::hotpink;
		float mass = 1.0f;

	public:
		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledCircle(color, radius - 1e-3);
				setLineWidth(2.0f);
				drawWiredCircle(Colors::black, radius);
			}
			endTransformation();
		}

		void update(const float& dt)
		{
			static const vec2 gravity = vec2(0.0f, -9.8f);  // 중력가속도
			static const float coef_res = 0.3f;		
			// coefficient restitution 반발계수 : 공의 진행하는 방향이 뒤집히게 하는 힘
			// 벽이 딱딱하면 많이 튕겨나오고 벽이 물렁물렁하면 힘이 흡수
			static const float coef_friction = 0.999f;   // 마찰 계수


			// numerical integration
			vel = vel + gravity * dt;
			pos = pos + vel * dt;

			// wall collision, friction
			if (1.0f - pos.x <= radius)  // right wall collision check
			{
				pos.x = 1.0f - radius;			// stop

				if(vel.x >= 0.0f)
					vel.x = vel.x * (-coef_res);
			}

			if (-(-1.0f - pos.y)  <= radius)   // floor
			{
				pos.y = -1.0f + radius;		// stop

				if (vel.y <= 0.0f)
					vel.y = vel.y * (-coef_res);

				vel.x = vel.x * coef_friction;   // apply friction
			}

			if (-(-1.0f - pos.x) <= radius)     // left wall
			{
				pos.x = -1.0f + radius;		//stop

				if (vel.x <= 0.0f)
					vel.x *= -coef_res;
			}
		}

		void setColor(const RGB& _color)
		{
			color = _color;
		}

		void setMass(const float& _mass)
		{
			mass = _mass;
		}
	};

	class CircleExample : public Game2D
	{
	public:

		RigidCircle rb0;

		CircleExample()
			: Game2D("This is a rigid circle example", 900, 650, false)
		{
			rb0.mass = 1.0f;
			rb0.color = Colors::hotpink;
			rb0.radius = 0.1f;

			reset();
		}

		void reset()
		{
			// initial position and velocity
			rb0.pos = vec2(-0.8f, 0.3f);
			rb0.vel = vec2(10.0f, 0.0f);     // 10m/s
		}

		void drawWall()
		{
			beginTransformation();
			{
				setLineWidth(5.0f);
				drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { 1.0f, -1.0f });
				drawLine(Colors::blue, { 1.0f, -1.0f }, Colors::blue, { 1.0f, 1.0f });
				drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { -1.0f, 1.0f });
			}
			endTransformation();
		}

		void update() override
		{

			// physics update
			rb0.update(getTimeStep() * 0.02f);

			// rendering
			drawWall();

			rb0.draw();

			// reset button
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
			if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_2)) reset();
		}
	};


	
}