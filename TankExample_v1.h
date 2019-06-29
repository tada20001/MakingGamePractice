#pragma once
#include "Game2D.h"
#include <vector>
// command pattern

namespace jm
{
	class Mybullet;

	class Actor
	{
	public:
		virtual void moveUp(const float& dt) = 0;
		virtual void moveDown(const float& dt) = 0;
		virtual void moveRight(const float& dt) = 0;
		virtual void moveLeft(const float& dt) = 0;
	};

	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(Actor& actor, const float& dt) = 0;
	};

	class UpCommand : public Command
	{
	public:
		virtual void execute(Actor& actor, const float& dt) override
		{
			actor.moveUp(dt);
		}
	};

	class DownCommand : public Command
	{
	public:
		virtual void execute(Actor& actor, const float& dt) override
		{
			actor.moveDown(dt);
		}
	};

	class LeftCommand : public Command
	{
	public:
		virtual void execute(Actor& actor, const float& dt) override
		{
			actor.moveLeft(dt);
		}
	};

	class RightCommand : public Command
	{
	public:
		virtual void execute(Actor& actor, const float& dt) override
		{
			actor.moveRight(dt);
		}
	};


	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);

	public:
		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
			endTransformation();
		}

		void update(const float& dt)
		{
			center = center + velocity * dt;
		}
	};



	class MyTank : public Actor
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);

	public:
		
		void moveUp(const float& dt) override
		{
			center.y += 0.2f * dt;
		}

		void moveDown(const float& dt) override
		{
			center.y -= 0.2f * dt;
		}

		void moveLeft(const float& dt) override
		{
			center.x -= 0.2f * dt;
		}
		
		void moveRight(const float& dt) override
		{
			center.x += 0.2f * dt;
		}

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(-0.02f, 0.1f);
				drawFilledBox(Colors::blue, 0.15f, 0.09f); // turret
				translate(0.15f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
			}
			endTransformation();
		}
	};

	

	class InputHandler   // 명령의 실제 수행 클래스
	{
	public:
		Command* button_up = nullptr;
		Command* button_down = nullptr;
		Command* button_left = nullptr;
		Command* button_right = nullptr;

		std::map<int, Command*> key_command_map;

		InputHandler()
		{
			button_up = new UpCommand;
			button_down = new DownCommand;
			button_left = new LeftCommand;
			button_right = new RightCommand;

			key_command_map.insert(std::pair<int, Command*>(265, button_up));
			key_command_map.insert(std::pair<int, Command*>(264, button_down));
			key_command_map.insert(std::pair<int, Command*>(263, button_left));
			key_command_map.insert(std::pair<int, Command*>(262, button_right));
			

		}

		~InputHandler()
		{
			if (button_up != nullptr) delete button_up;
			if (button_down != nullptr) delete button_down;
			if (button_left != nullptr) delete button_left;
			if (button_right != nullptr) delete button_right;
			
		}

		void handleInput(Game2D& game, Actor& actor, const float& dt)
		{
			/*if (game.isKeyPressed(GLFW_KEY_UP)) button_up->execute(actor, dt);
			if (game.isKeyPressed(GLFW_KEY_DOWN)) button_down->execute(actor, dt);
			if (game.isKeyPressed(GLFW_KEY_LEFT)) button_left->execute(actor, dt);
			if (game.isKeyPressed(GLFW_KEY_RIGHT)) button_right->execute(actor, dt);*/

			for (auto& m : key_command_map)
			{
				if (game.isKeyPressed(m.first)) m.second->execute(actor, dt);
			}
		}

	};

	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		//MyBullet* bullet = nullptr;   // 총알이 발사할 때면 존재하기 때문에 포인터로 만듦
		
		InputHandler input_handler;

		std::vector<MyBullet*> bullets;
		int m_number = 0;

	public:
		TankExample()
			: Game2D("This is a Tank example canvas!", 900, 650, false)
		{
			// key mapping
			input_handler.key_command_map[GLFW_KEY_UP] = new UpCommand;
			input_handler.key_command_map[GLFW_KEY_DOWN] = new DownCommand;
			input_handler.key_command_map[GLFW_KEY_LEFT] = new LeftCommand;
			input_handler.key_command_map[GLFW_KEY_RIGHT] = new RightCommand;
		}

		TankExample(const int& num)
		{
			m_number = num;
		}

		~TankExample()
		{
			//if (bullet != nullptr) delete bullet;
			for (auto& bullet : bullets)
				if (bullet != nullptr) delete bullet;
			bullets.clear();
		}

		void update() override
		{
			// move tank
			/*if (isKeyPressed(GLFW_KEY_LEFT))	tank.center.x -= 0.1f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_RIGHT))	tank.center.x += 0.1f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.1f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.1f * getTimeStep();*/

			input_handler.handleInput(*this, tank, getTimeStep());

			// shoot a cannon ball
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE))
			{
				for (int i = 0; i < m_number; ++i)
				{
					//if (bullet != nullptr) delete bullet;
					MyBullet* bullet = new MyBullet;
					bullet->center = tank.center;
					bullet->center.x += 0.2f;
					bullet->center.y += 0.1f;
					bullet->velocity = vec2(1.0f, 0.0f);

					bullets.push_back(bullet);
				}
			}

			for (auto& bullet : bullets)
			{
				if (bullet != nullptr) bullet->update(getTimeStep() * 0.1f);
			}

			// rendering
			tank.draw();

			for (auto& bullet : bullets)
			{
				if (bullet != nullptr) bullet->draw();
			}
		}
	};
}