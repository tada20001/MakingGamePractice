#pragma once
#include "RandomNumberGenerator.h"
#include "GeometricObject.h"
#include <memory>
#include <vector>

namespace jm
{
	class GeomericExample : public Game2D
	{
	private:

		//std::vector<std::shared_ptr<GeometricObject>> my_objs;
		std::vector<GeometricObject*> my_objs;

		RandomNumberGenerator rnd;

	public:
		GeomericExample()
			:Game2D("This is my digital canvas!", 900, 650, false)
		{
			init();
		}

		~GeomericExample()
		{
			for (const auto& obj : my_objs)
				delete obj;

			my_objs.clear();
		}

		void init()
		{
			for (int i = 0; i < 10; ++i)
			{
				my_objs.push_back(GeometricObject::makeTriangle(Colors::black, vec2{ -0.5f, 0.2f }, rnd.getFloat(0.0f, 360.0f), 0.25f));
				my_objs.push_back(GeometricObject::makeBox(Colors::black, vec2{ 0.0f, 0.5f }, rnd.getFloat(0.0f, 360.0f), 0.15f, 0.25f));
				my_objs.push_back(GeometricObject::makeCircle(Colors::olive, vec2{ 0.1f, 0.1f }, 0.0f, 0.2f));
				my_objs.push_back(GeometricObject::makeStar(Colors::red, vec2{ -0.5f, -0.5f }, rnd.getFloat(0.0f, 360.0f), 0.25f, 0.15f));
			}

			int count = 0;
			for (auto& obj : my_objs)
			{
				obj->setColor(getRandomColor());
				obj->setPos(vec2(-1.5f + 0.08f * (float)count, rnd.getFloat(-0.5f, 1.0f)));
				obj->setRot(rnd.getFloat(0.0f, 360.0f));
				++count;
			}

			/*my_cir[i] = Circle(getRandomColor(), vec2((-1.5f + 0.2f * (float)i), rnd.getFloat(-1.0f, 1.0f)), rnd.getFloat(0.0f, 360.0f), 0.15f);
			my_box[i] = Box(getRandomColor(), vec2((-1.5f + 0.2f * (float)i), rnd.getFloat(-1.0f, 1.0f)), rnd.getFloat(0.0f, 360.0f), 0.25f, 0.3f);*/


		}
		const RGB& getRandomColor()
		{
			return RGB(rnd.getFloat(0.0f, 1.0f), rnd.getFloat(0.0f, 1.0f), rnd.getFloat(0.0f, 1.0f));
		}

		const vec2& getRandomPos()
		{
			return vec2(rnd.getFloat(-1.0f, 1.0f), rnd.getFloat(-0.5f, 0.5f));
		}

		void update() override
		{


			for (const auto& obj : my_objs)
				obj->draw();

		}
	};

}