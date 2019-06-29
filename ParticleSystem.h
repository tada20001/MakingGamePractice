#pragma once
#include "Game2D.h"
#include "PrimitivesGallery.h"
#include "RandomNumberGenerator.h"

#include <vector>

namespace jm
{
	using namespace std;

	static const vec2 gravity = vec2(0.0f, -9.8f);

	class Particle
	{
	public:
		vec2 pos = { 0.0f, 0.0f };
		vec2 vel = { 0.0f, 0.0f };
		RGB color = Colors::red;
		float rot = 0.0f;
		float angular_velocity = 0.0f;

		float age = 0.0f;
		float life = 5.0f;

		void update(const float& dt)
		{
			const auto acc = gravity;  // assume GA only

			vel += acc * dt;
			pos += vel * dt;
			rot += angular_velocity * dt;

			// update age
			age += dt;
		}
	};

	class ParticleSystem
	{
	public:
		vector<Particle> particles;

		RandomNumberGenerator rnd;

		ParticleSystem()
		{
			reset();
		}

		void reset()
		{
			particles.clear();

			// initial pos, vel
			for (int i = 0; i < 1000; ++i)
			{
				Particle new_particle;
				new_particle.pos = vec2(0.0f, 0.5f) + getRandomUnitVector() * rnd.getFloat(0.001f, 0.03f);
				new_particle.vel = getRandomUnitVector() * rnd.getFloat(0.01f, 2.0f);
				new_particle.color = getRandomColor();
				new_particle.age = 0.0f;
				new_particle.life = rnd.getFloat(0.1f, 1.0f);
				new_particle.rot = rnd.getFloat(0.0f, 360.0f);
				new_particle.angular_velocity = rnd.getFloat(-1.0f, 1.0f) * 360.0f * 4.0f;

				particles.push_back(new_particle);
			}
		}

		vec2 getRandomUnitVector()
		{
			const float theta = rnd.getFloat(0.0f, 3.141592f * 2.0f);  // 0.0~2pi (0~360)

			return vec2(cos(theta), -sin(theta));
		}

		RGB getRandomColor()
		{
			return RGB(rnd.getFloat(0.0f, 1.0f), rnd.getFloat(0.0f, 1.0f), rnd.getFloat(0.0f, 1.0f));
		}

		void update(const float& dt)
		{
			for (auto& particle : particles)
				particle.update(dt);
		}

		void draw()
		{
			for (const auto& particle : particles)
			{
				if (particle.age > particle.life) continue;

				const float alpha = 1.0f - particle.age / particle.life;
				const RGB blended_color =
				{
					particle.color.r * alpha + 1.0f * (1.0f - alpha),
					particle.color.g * alpha + 1.0f * (1.0f - alpha),
					particle.color.b * alpha + 1.0f * (1.0f - alpha),
				};

				//drawPoint(particle.color, particle.pos, 5.0f);
				beginTransformation();
				translate(particle.pos);
				rotate(particle.rot);
				drawFilledStar(blended_color, 0.03f, 0.015f);
				endTransformation();
			}

		}
	};

	class ParticleExample : public Game2D
	{
	public:
		ParticleSystem ps;

		ParticleExample()
			: Game2D("This is a Particle Example", 900, 650, false)
		{
			reset();
		}

		void reset()
		{
			ps.reset();
		}

		void update() override
		{
			// update
			ps.update(getTimeStep() * 0.5f);

			ps.draw();

			// reset button
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
		}
	};
}