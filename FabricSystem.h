#pragma once
#include "Game2D.h"
#include "RigidCircle.h"

namespace jm
{
	class FabricSystem : public Game2D
	{
	public:
		RigidCircle rg[16];
		const float L0 = 0.5f;
		const float coeff_k = 300.0f;
		const float coeff_d = 300.0f;
		const vec2 gravity = vec2(0.0f, -9.8f);
	
	public:
		FabricSystem()
			: Game2D("This is a Fabric System", 900, 650, false)
		{
			reset();
		}

		void reset()
		{
			for (int i = 0; i < 16; ++i)
			{
				if (i < 4) rg[i].pos = vec2(-0.45f + 0.3f * (float)i, 0.8f);   // first row
				else if( i < 8) rg[i].pos = vec2(-0.45f + 0.3f * (float)(i - 4), 0.5f);  // second row
				else if (i < 12) rg[i].pos = vec2(-0.45f + 0.3f * (float)(i - 8), 0.2f);  // thrid row
				else rg[i].pos = vec2(-0.45f + 0.3f * (float)(i - 12), -0.1f);  //4th row

				rg[i].vel = vec2(0.0f, 0.0f);
				
				if (i == 0 || i == 3) rg[i].color = Colors::gold;
				else rg[i].color = Colors::skyblue;

				rg[i].radius = 0.05f;
				rg[i].mass = 1.0f;
			}
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

		vec2 calculateSpringforce(const RigidCircle& rb1, const RigidCircle& rb2)
		{
			const float distance = (rb1.pos - rb2.pos).getMagnitude();
			const vec2 normal = (rb1.pos - rb2.pos) / distance;
			const vec2 spring_force = normal * -coeff_k * (distance - L0);
			
			return spring_force / rb1.mass;
		}

		vec2 calculateDampingforce(const RigidCircle& rb1, const RigidCircle& rb2)
		{
			const float distance = (rb1.pos - rb2.pos).getMagnitude();
			const vec2 normal = (rb1.pos - rb2.pos) / distance;
			const vec2 damping_force = normal * -coeff_d * (rb1.vel - rb2.vel).getDotProduct(normal);

			return damping_force / rb1.mass;
		}

		void update()
		{
			const float dt = getTimeStep() * 0.01f;
			// coefficients
			
			vec2 accel[16];

			// compute spring force and damping forces, accel

			for (int i = 0; i < 16; ++i)
			{
				if (i == 0 || i == 3)
				{
					accel[i] = vec2(0.0f, 0.0f);
				}

				else if (i == 1 || i == 2)
				{
					// case : with (i-1), (i+1), (i+3), (i+4), (i+5)
					accel[i] = gravity
						+ (calculateSpringforce(rg[i], rg[i - 1]) + calculateDampingforce(rg[i], rg[i - 1]))
						+ (calculateSpringforce(rg[i], rg[i + 1]) + calculateDampingforce(rg[i], rg[i + 1]))
						+ (calculateSpringforce(rg[i], rg[i + 3]) + calculateDampingforce(rg[i], rg[i + 3]))
						+ (calculateSpringforce(rg[i], rg[i + 4]) + calculateDampingforce(rg[i], rg[i + 4]))
						+ (calculateSpringforce(rg[i], rg[i + 5]) + calculateDampingforce(rg[i], rg[i + 5]));
				}
					
				else if (i == 5 || i == 6 || i == 9 || i == 10)
				{
					// case : with (i - 1) (i+1), (i+3)(i-3) (i+4) (i-4) (i+5)(i-5)
					accel[i] = gravity
						+ (calculateSpringforce(rg[i], rg[i - 1]) + calculateDampingforce(rg[i], rg[i - 1]))
						+ (calculateSpringforce(rg[i], rg[i + 1]) + calculateDampingforce(rg[i], rg[i + 1]))
						+ (calculateSpringforce(rg[i], rg[i + 3]) + calculateDampingforce(rg[i], rg[i + 3]))
						+ (calculateSpringforce(rg[i], rg[i - 3]) + calculateDampingforce(rg[i], rg[i - 3]))
						+ (calculateSpringforce(rg[i], rg[i + 4]) + calculateDampingforce(rg[i], rg[i + 4]))
						+ (calculateSpringforce(rg[i], rg[i - 4]) + calculateDampingforce(rg[i], rg[i - 4]))
						+ (calculateSpringforce(rg[i], rg[i + 5]) + calculateDampingforce(rg[i], rg[i + 5]))
						+ (calculateSpringforce(rg[i], rg[i - 5]) + calculateDampingforce(rg[i], rg[i - 5]));
				}
				else if (i == 13 || i == 14)
				{
					// case : with (i - 1) (i+1), (i-3)  (i-4) (i-5)

					accel[i] = gravity
						+ (calculateSpringforce(rg[i], rg[i - 1]) + calculateDampingforce(rg[i], rg[i - 1]))
						+ (calculateSpringforce(rg[i], rg[i + 1]) + calculateDampingforce(rg[i], rg[i + 1]))
						+ (calculateSpringforce(rg[i], rg[i - 3]) + calculateDampingforce(rg[i], rg[i - 3]))
						+ (calculateSpringforce(rg[i], rg[i - 4]) + calculateDampingforce(rg[i], rg[i - 4]))
						+ (calculateSpringforce(rg[i], rg[i - 5]) + calculateDampingforce(rg[i], rg[i - 5]));
				}
				else if (i == 4 || i == 8)
				{
					// case : with (i+1), (i-4) (i+4) (i-3) (i+ 5)

					accel[i] = gravity
						+ (calculateSpringforce(rg[i], rg[i + 1]) + calculateDampingforce(rg[i], rg[i + 1]))
						+ (calculateSpringforce(rg[i], rg[i - 3]) + calculateDampingforce(rg[i], rg[i - 3]))
						+ (calculateSpringforce(rg[i], rg[i - 4]) + calculateDampingforce(rg[i], rg[i - 4]))
						+ (calculateSpringforce(rg[i], rg[i + 4]) + calculateDampingforce(rg[i], rg[i + 4]))
						+ (calculateSpringforce(rg[i], rg[i + 5]) + calculateDampingforce(rg[i], rg[i + 5]));
				}
				else if (i == 7 || i == 11)
				{
					// case : with (i-1), (i-4) (i+4) (i+3) (i- 5)

					accel[i] = gravity
						+ (calculateSpringforce(rg[i], rg[i - 1]) + calculateDampingforce(rg[i], rg[i - 1]))
						+ (calculateSpringforce(rg[i], rg[i + 3]) + calculateDampingforce(rg[i], rg[i + 3]))
						+ (calculateSpringforce(rg[i], rg[i - 4]) + calculateDampingforce(rg[i], rg[i - 4]))
						+ (calculateSpringforce(rg[i], rg[i + 4]) + calculateDampingforce(rg[i], rg[i + 4]))
						+ (calculateSpringforce(rg[i], rg[i - 5]) + calculateDampingforce(rg[i], rg[i - 5]));
				}
				else if (i == 12)
				{
					// case : with (i+1), (i-4) (i-3)

					accel[i] = gravity
						+ (calculateSpringforce(rg[i], rg[i + 1]) + calculateDampingforce(rg[i], rg[i + 1]))
						+ (calculateSpringforce(rg[i], rg[i - 3]) + calculateDampingforce(rg[i], rg[i - 3]))
						+ (calculateSpringforce(rg[i], rg[i - 4]) + calculateDampingforce(rg[i], rg[i - 4]));
				}
				else
				{
					// case : with (i-1), (i-4) (i-5)
					accel[i] = gravity
						+ (calculateSpringforce(rg[i], rg[i - 1]) + calculateDampingforce(rg[i], rg[i - 1]))
						+ (calculateSpringforce(rg[i], rg[i - 5]) + calculateDampingforce(rg[i], rg[i - 5]))
						+ (calculateSpringforce(rg[i], rg[i - 4]) + calculateDampingforce(rg[i], rg[i - 4]));
				}
			}

			// physics update
			for (int i = 0; i < 16; ++i)
			{
				rg[i].vel += accel[i] * dt;
				rg[i].pos += rg[i].vel * dt;
			}

			// rendering
			setLineWidth(1.0f);
			for (int i = 0; i < 16; ++i)
			{
				//edge lines
				{
					// column lines
					if (i % 4 == 0 && i <= 8) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 4].pos);
					if (i % 4 == 1 && i <= 9) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 4].pos);
					if (i % 4 == 2 && i <= 10) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 4].pos);
					if (i % 4 == 3 && i <= 11) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 4].pos);

					// row lines
					if (i < 3) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 1].pos);
					else if(i > 3 && i < 7) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 1].pos);
					//else if (i > 7 && i < 11) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 1].pos);
					else if(i > 11 && i < 15) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 1].pos);

					// diagonal lines
					if(i % 5 == 0 && i != 15) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 5].pos);
					if(i % 5 == 1 && i != 11)drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 5].pos);
					if (i == 2) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 5].pos);
					if (i % 5 == 3 && i >= 8 && i != 13)drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 5].pos);
					if (i % 5 == 4 && i >= 4 && i != 14)drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 5].pos);

					if(i % 3 == 0 && i < 12 && i!= 0) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 3].pos);
					if (i % 3 == 1 && i < 13 && i!= 4) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 3].pos);
					if (i % 3 == 2 && i < 14) drawLine(Colors::green, rg[i].pos, Colors::green, rg[i + 3].pos);
				}

			}

			drawWall();
			for (int i = 0; i < 16; ++i)
				rg[i].draw();
		}
	};

}