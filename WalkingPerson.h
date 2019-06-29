#pragma once

#include "Game2D.h"
#include <random>
#include <ctime>
#include "RandomNumberGenerator.h"

namespace jm
{
	/*
	TODO:
	- add left arm and left leg
	- make a Person class and use it to draw many people.
	- make an Ironman and allow for him to shoot repulsor beam with his right hand
	*/

	class Person 
	{
	public:
		vec2 pos;

		void setPos(const vec2& _pos)
		{
			pos = _pos;
		}

		void update(const float & dt)
		{
			translate(pos);
			// gold face
			beginTransformation();
			translate(0.0f, 0.12f);
			drawFilledCircle(Colors::gold, 0.08f);
			translate(0.05f, 0.03f);
			drawFilledCircle(Colors::white, 0.01f); // while eye
			endTransformation();

			// yellow left arm
			beginTransformation();
			rotate(-sin(dt * 5.0f) * 30.0f);					// animation!
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::yellow, 0.05f, 0.18f);
			endTransformation();

			// green left leg
			beginTransformation();
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(-sinf(dt * 5.0f + 3.141592f) * 30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::green, 0.1f, 0.4f);
			endTransformation();

			// red body
			beginTransformation();
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::red, 0.13f, 0.2f);
			endTransformation();

			// yellow right arm
			beginTransformation();
			rotate(sin(dt * 5.0f) * 30.0f);					// animation!
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::yellow, 0.05f, 0.18f);
			endTransformation();

			// green right leg
			beginTransformation();
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(sinf(dt * 5.0f + 3.141592f) * 30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::green, 0.1f, 0.4f);
			endTransformation();

			// floor
			beginTransformation();
			translate(0.0f, -0.85f);
			drawLine(Colors::silver, vec2(-0.2f, 0.0f), Colors::olive, vec2(0.2f, 0.0f));
			endTransformation();
		}
	};

	class WalkingPerson : public Game2D
	{
		Person person;
		float time = 0.0f;

		int m_number = 0;
		std::vector<Person> persons;

		RandomNumberGenerator rnd;

	public:
		WalkingPerson()
			:Game2D("This is a WalkingPerson Example", 900, 650, false)
		{}

		WalkingPerson(const int& num)
		{
			m_number = num;

			reset();
		}

		~WalkingPerson()
		{}

		void reset()
		{
			for (int i = 0; i < m_number; ++i)
			{
				Person person;
				person.setPos(vec2(rnd.getFloat(-1.0f, 1.0f), rnd.getFloat(0.0f, 1.0f)));
				persons.push_back(person);
			}
		}

		void update() override
		{
			scale(0.3f, 0.3f);

			for (auto& person : persons)
			{
				person.update(time);
			}
			time += this->getTimeStep()* 0.1f;
		}
	};
}