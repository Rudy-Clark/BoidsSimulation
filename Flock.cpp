#include "Flock.hpp"

namespace EnttBoids {
	Boid& Flock::GetBoid(int index)
	{
		return m_boids[index];
	}

	void Flock::AddBoid(const Boid&& boid)
	{
		m_boids[m_boidsIterCount % m_boids.size()] = std::move(boid);
		++m_boidsIterCount;
	}

	inline Boid& Flock::operator[](int index)
	{
		return m_boids[index];
	}

	void Flock::Flocking(const float DeltaTime)
	{
		for (int i{ 0 }; i < m_boids.size(); ++i) {
			m_boids[i].Run(m_boids, DeltaTime);
		}
	}

	void Flock::ForEach(std::function<void(Boid&)> f)
	{
		for (int i{ 0 }; i < m_boids.size(); ++i)
		{
			f(m_boids[i]);
		}
	}
}

