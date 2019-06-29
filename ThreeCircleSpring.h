#pragma once
#include "Game2D.h"
#include "RigidCircle.h"

namespace jm
{
	class ThreeCirclesSpring : public Game2D
	{
	public:
		RigidCircle rb0, rb1, rb2;

		ThreeCirclesSpring()
			: Game2D("This is a Three Circles Spring System", 900, 650, false)
		{
			reset();
		}

		void reset()
		{
			// initial pos, vel, color, radius...

			rb0.pos = vec2(0.0f, 0.5f);
			rb0.vel = vec2(0.0f, 0.0f);
			rb0.color = Colors::gold;
			rb0.radius = 0.05f;
			rb0.mass = 1.0f;

			rb1.pos = vec2(0.5f, 0.5f);
			rb1.vel = vec2(0.0f, 0.0f);
			rb1.color = Colors::skyblue;
			rb1.radius = 0.05f;
			rb0.mass = rb0.mass * std::pow(rb1.radius / rb0.radius, 2.0f);

			rb2.pos = vec2(0.5f, 0.3f);
			rb2.vel = vec2(0.0f, 0.0f);
			rb2.color = Colors::skyblue;
			rb2.radius = 0.05f;
			rb2.mass = rb1.mass * std::pow(rb2.radius / rb1.radius, 2.0f);
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
			const auto dt = getTimeStep() * 0.02f;
			const vec2 gravity = vec2(0.0f, -9.8f);
			const float epsilon = 0.5f;

			// update
			{
				// coefficients
				const float coeff_k = 50.0f;   // stiffness coef : spring force
				const float coeff_d = 50.0f;	// damping coef
				const float L0 = 0.5f;


				const auto distance0 = (rb1.pos - rb0.pos).getMagnitude();
				const auto normal_vector0 = (rb1.pos - rb0.pos) / distance0;   // πÊ«‚ ∫§≈Õ

				const auto distance1 = (rb2.pos - rb1.pos).getMagnitude();
				const auto normal_vector1 = (rb2.pos - rb1.pos) / distance1;

				// compute spring force

				const auto spring_force0 = normal_vector0 * -coeff_k * (distance0 - L0);
				const auto spring_force1 = normal_vector1 * -coeff_k * (distance1 - L0);
				
				const auto damping_force0 = normal_vector0 * -coeff_d * (rb1.vel - rb0.vel).getDotProduct(normal_vector0);
				const auto damping_force1 = normal_vector1 * -coeff_d * (rb2.vel - rb1.vel).getDotProduct(normal_vector1);

				const auto accel0 = gravity + spring_force0 / rb1.mass + damping_force0 / rb1.mass;
				const auto accel1 = gravity 
					+ spring_force0 / rb1.mass + damping_force0 / rb1.mass
					+ spring_force1 / rb2.mass + damping_force1 / rb2.mass;


				rb1.vel += accel0 * dt;
				rb1.pos += rb1.vel * dt;
				rb2.vel += accel1 * dt;
				rb2.pos += rb2.vel * dt;
			}

			// rendering
			drawWall();

			setLineWidth(0.2f);
			drawLine(Colors::red, rb0.pos, Colors::red, rb1.pos);
			drawLine(Colors::red, rb1.pos, Colors::red, rb2.pos);

			rb0.draw();
			rb1.draw();
			rb2.draw();

			// reset button
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
			if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_2)) reset();
		}




	};
}