#pragma once
#include "Game2D.h"

namespace jm
{
	class MouseExample : public Game2D
	{
	public:
		void update() override
		{
			const vec2 mouse_pos = getCursorPos();

			if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			{
				translate(mouse_pos);
				drawFilledCircle(Colors::gold, 0.1f);
			}
			if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
			{
				translate(mouse_pos);
				drawFilledCircle(Colors::red, 0.1f);
			}

		}
	};

}