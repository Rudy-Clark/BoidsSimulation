#pragma once

#include <array>
#include <functional>
#include "Boid.hpp"
#include "Settings.hpp"

namespace EnttBoids {
	class Flock
	{
	public:
		Flock() = default;

		Boid& GetBoid(int index);

		void AddBoid(const Boid&& boid);

		Boid& operator [] (int index);

		void Flocking(const float DeltaTime);

		void ForEach(std::function<void(Boid&)>f);

	private:
		std::array<Boid, Settings::TotalBoids> m_boids;
		int m_boidsIterCount{0};
	};
}

