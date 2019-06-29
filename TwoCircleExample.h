#pragma once
#include "Game2D.h"
#include "RigidCircle.h"

namespace jm
{
	class TwoCircleExample : public Game2D
	{
	public:
		RigidCircle rb0, rb1;

	public:
		TwoCircleExample()
			: Game2D("This is a rigid circle example", 900, 650, false)
		{
			reset();
		}

		void reset()
		{
			// Initial position and velocity
			rb0.pos = vec2(-0.8f, 0.3f);
			rb0.vel = vec2(5.0f, 0.0f);
			rb0.color = Colors::hotpink;
			rb0.radius = 0.1f;
			rb0.mass = 1.0f;

			rb1.pos = vec2(0.8f, 0.3f);
			rb1.vel = vec2(-5.0f, 0.0f);
			rb1.color = Colors::yellow;
			rb1.radius = 0.15f;
			rb1.mass = rb0.mass * std::pow(rb1.radius / rb0.radius, 2.0f);
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
			const float epsilon = 1.0f;
		
			// physics update
			rb0.update(dt);
			rb1.update(dt);

			// check collision between two circles
			const auto distance = (rb1.pos - rb0.pos).getMagnitude();
			const auto normal_vector = -(rb1.pos - rb0.pos) / distance;
			const auto rel_vel = rb0.vel - rb1.vel;

			if (distance <= rb0.radius + rb1.radius)
			{
				if (rel_vel.getDotProduct(normal_vector) < 0.0f) // two cirlces approching
				{
					// compuste impulse
					const auto impulse = normal_vector * -(1.0f + epsilon) * rel_vel.getDotProduct(normal_vector) / ((1.0f / rb0.mass) + (1.0f / rb1.mass));

					// update velocities of two bodies;
					rb0.vel += impulse / rb0.mass;
					rb1.vel -= impulse / rb1.mass;

				}
			}

			// rendering
			drawWall();
			rb0.draw();
			rb1.draw();

			// reset button
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
			if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_2)) reset();
		}
	};
}