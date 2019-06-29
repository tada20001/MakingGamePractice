#pragma once
#include "Game2D.h"
#include "RigidCircle.h"

namespace jm
{
	class SpringSystem : public Game2D
	{
	public:

		RigidCircle rb0, rb1;

	public:
		SpringSystem()
			: Game2D("This is a Mass Spring System Example", 900, 650, false)
		{
			reset();
		}

		void reset()
		{
			// initial pos, vel, L0

			rb0.pos = vec2(0.0f, 0.5f);
			rb0.vel = vec2(0.0f, 0.0f);
			rb0.color = Colors::hotpink;
			rb0.radius = 0.03f;
			rb0.mass = 1.0f;

			rb1.pos = vec2(0.5f, 0.5f);
			rb1.vel = vec2(0.0f, 0.0f);
			rb1.color = Colors::yellow;
			rb1.radius = 0.03f;
			rb0.mass = rb0.mass * std::pow(rb1.radius / rb0.radius, 2.0f);
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
			const float dt = getTimeStep() * 0.02f;
			const float epsilon = 0.5f;

			//// physics update
			//rb0.update(dt);
			//rb1.update(dt);

			// coefficients
			const vec2 gravity = vec2(0.0f, -9.8f);
			const float L0 = 0.5f;
			const float coeff_k = 50.0f;   // stiffness coef : spring force
			const float coeff_d = 10.0f;	// damping coef

			// update rb1(Note: rb0 is fixed)
			{
				const auto distance = (rb1.pos - rb0.pos).getMagnitude();
				const auto normal_vector = (rb1.pos - rb0.pos) / distance;

				// compute stiffness force(spring force)
				const auto spring_force = normal_vector * -coeff_k * (distance - L0);

				// compute damping force
				const auto damping_force = normal_vector * -coeff_d * (rb1.vel - rb0.vel).getDotProduct(normal_vector);

				const auto accel = gravity + spring_force / rb1.mass + damping_force / rb1.mass;

				rb1.vel += accel * dt;
				rb1.pos += rb1.vel * dt;
			}

			// rendering
			setLineWidth(3.0f);
			drawLine(Colors::red, rb0.pos, Colors::red, rb1.pos);
			drawWall();
			rb0.draw();
			rb1.draw();


			// reset button
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
			if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_2)) reset();

		}


	};
}