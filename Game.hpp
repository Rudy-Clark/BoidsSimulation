#pragma once

#include "Flock.hpp"
#include "Settings.hpp"
#include "Vector2.hpp"
#include "RulesFactor.hpp"

namespace EnttBoids {
	class Game
	{
	public:
		Game(const int screenWidth, const int screenHeight, const int fps);

		void Run();

	private:
		void Tick(const float DeltaTime);
		void Update(const float DeltaTime);
		void Render();
		void UI();

		const Vector2<int> m_windowSize;
		Flock m_flock{};
	};
}


