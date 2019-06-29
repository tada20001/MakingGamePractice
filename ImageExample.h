#pragma once
#include "Game2D.h"
#include "ImageObject.h"

namespace jm
{
	using namespace std;

	class ImageExamle : public Game2D
	{
	public:
		ImageObject house;
		ImageObject background;
		ImageObject sentence;

		ImageExamle()
			: Game2D("This is my digital canvas!", 1280, 960, false)  // Must initialize Game2D
		{
			house.init("./car.png", 255, 255, 255);   // white to transparent
			background.init("./Background_image.bmp");
			sentence.init("./sentence.png");
		}
		
		void update() override
		{
			beginTransformation();
			scale(1.5f, 1.5f);
			background.draw();
			endTransformation();

			beginTransformation();
			translate(-0.5f, 0.0f);
			drawFilledStar(Colors::gold, 0.2f, 0.1f);
			endTransformation();

			beginTransformation();
			translate(0.0f, 0.0f);
			scale(0.5f, 0.5f);
			sentence.draw();
			endTransformation();

			// moving car
			{
				static float x = -1.0f;

				beginTransformation();
				translate(x, 0.0f);
				scale(0.5f, 0.5f);
				house.draw();
				endTransformation();

				x += 0.01f;

				if (x > 1.0f) x = -1.0f;
			}

			beginTransformation();
			translate(0.5f, 0.0f);
			drawFilledStar(Colors::red, 0.2f, 0.1f);
			endTransformation();

			// background.draw();   // this hides everything
		}
	};
}