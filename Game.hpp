#pragma once

#include "Flock.hpp"
#include "Settings.hpp"
#include "Vector2.hpp"

namespace EnttBoids {
	class Game
	{
	public:
		Game(const int screenWidth, const int screenHeight, const char* title, const int fps);

		~Game() noexcept;

		void Run();

	private:
		void Tick(const float DeltaTime);
		void Update(const float DeltaTime);
		void Render();

		const Vector2<int> m_windowDimension;
		Flock m_flock;

	};
}


