#include "Flock.hpp"
#include <raylib.h>

namespace EnttBoids {
	Flock::Flock()
		: m_rulesFactor{1.f, 1.f, 1.5f}
	{
		for (int i{}; i < Settings::TotalBoids; ++i) {
			m_boids[i] = Boid(GetRandomValue(0, Settings::screenWidth), GetRandomValue(0, Settings::screenHeight), m_rulesFactor);
		}
	}

	void Flock::Flocking(const float DeltaTime)
	{
		for (int i{ 0 }; i < m_boids.size(); ++i) {
			m_boids[i].Run(m_boids, DeltaTime);
			m_boids[i].LimitLocation(Vector2{ Settings::screenWidth, Settings::screenHeight });
		}
	}

	void Flock::ForEachBoid(std::function<void(const Vector2<float>& Pos, const Vector2<float>& Vel)> f)
	{
		for (int i{ 0 }; i < m_boids.size(); ++i)
		{
			f(m_boids[i].GetLocationRef(), m_boids[i].GetVelocityRef());
		}
	}

	float* Flock::GetAlignmentPtr()
	{
		return &m_rulesFactor.alignment;
	}
	
	float* Flock::GetSeparationPtr()
	{
		return &m_rulesFactor.separation;
	}
	
	float* Flock::GetCohesionPtr()
	{
		return &m_rulesFactor.cohesion;
	}
}

