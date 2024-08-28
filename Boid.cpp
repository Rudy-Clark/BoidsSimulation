#include "Boid.hpp"
#include <raylib.h>

namespace EnttBoids {
	Boid::Boid(float x, float y)
		: m_location{x, y}
		, m_maxForce{0.2}
		, m_maxSpeed{5}
	{
		m_velocity = Vector2{ static_cast<float>(GetRandomValue(-100, 100)) / 100.f, static_cast<float>(GetRandomValue(-100, 100)) / 100.f };
		m_velocity.SetMagnitude((float)GetRandomValue(2, 4));
	}

	Boid::Boid(float x, float y, bool predatorCheck)
		: m_location{x, y}
		, m_bPredator{predatorCheck}
		, m_maxForce{ 0.2 }
	{
		if (predatorCheck) 
		{
			m_velocity = Vector2{ static_cast<float>(GetRandomValue(-100, 100)) / 100.f, static_cast<float>(GetRandomValue(-100, 100)) / 100.f };
			m_velocity.SetMagnitude((float)GetRandomValue(2, 4));
			m_maxSpeed = 5;
		}
		else
		{
			m_velocity = Vector2{ static_cast<float>(GetRandomValue(-100, 100)) / 100.f, static_cast<float>(GetRandomValue(-100, 100)) / 100.f };
			m_velocity.SetMagnitude((float)GetRandomValue(2, 4));
			m_maxSpeed = 5;
		}
	}

	Boid::Boid(const Boid&& other) noexcept
	{
		m_location = other.m_location;
		m_velocity = other.m_velocity;
		m_accelaration = other.m_accelaration;
		m_maxForce = other.m_maxForce;
		m_maxSpeed = other.m_maxSpeed;
	}

	Boid& Boid::operator=(const Boid&& other) noexcept
	{
		m_location = other.m_location;
		m_velocity = other.m_velocity;
		m_accelaration = other.m_accelaration;
		m_maxForce = other.m_maxForce;
		m_maxSpeed = other.m_maxSpeed;

		return *this;
	}

	void Boid::Run(const Boid* const Boids, const int size, const float DeltaTime)
	{
		Flock(Boids, size);
		Update(DeltaTime);
	}

	void Boid::Update(const float DeltaTime)
	{
		m_velocity += (m_accelaration * DeltaTime);
		m_location += (m_velocity * DeltaTime);
		m_velocity.Limit(m_maxSpeed);

		// Reset Acceleration
		m_accelaration *= 0;
	}

	void Boid::Flock(const Boid* const Boids, const int size)
	{
		Vector2 Sep = Separation(Boids, size);
		Vector2 Coh = Cohesion(Boids, size);
		Vector2 Aln = Alignment(Boids, size);

		Sep *= 1.5;
		Coh *= 1.0;
		Aln *= 1.0;

		m_accelaration += Aln;
		m_accelaration += Sep;
		m_accelaration += Coh;
		
	}
	
	Vector2<float> Boid::Separation(const Boid* const Boids, const int size)
	{
		float desiredSeparation{ 50 };
		Vector2<float> Steer{};
		int count{};

		for (int i{ 0 }; i < size; ++i) {
			double d = m_location.Distance(Boids[i].m_location);
			
			if (this != &(Boids[i]) && d > 0 && d < desiredSeparation)
			{
				Vector2<float> Diff{};
				Diff = m_location - Boids[i].GetLocation();
				Diff.Normalize();
				Diff /= (d * d);
				Steer += Diff;
				++count;
			}
		}

		if (count > 0)
		{
			Steer /= static_cast<float>(count);
			Steer.SetMagnitude(m_maxSpeed);
			Steer -= m_velocity;
			Steer.Limit(m_maxForce);
		}

		return Steer;
	}

	Vector2<float> Boid::Alignment(const Boid* const Boids, const int size)
	{
		float perceptionRadius{ 50 };
		Vector2<float> Steer{};
		int count{};

		for (int i{}; i < size; ++i)
		{
			Vector2 BoidLocation = Boids[i].GetLocation();
			Vector2 BoidVelocity = Boids[i].GetVelocity();
			float distance = m_location.Distance(BoidLocation);
			if (this != &(Boids[i]) && distance < perceptionRadius)
			{
				Steer += BoidVelocity;
				++count;
			}
		}

		if (count > 0) {
			Steer /= static_cast<float>(count);
			Steer.Normalize();
			Steer.SetMagnitude(m_maxSpeed);
			Steer -= m_velocity;
			Steer.Limit(m_maxForce);
		}

		return Steer;
	}

	Vector2<float> Boid::Cohesion(const Boid* const Boids, const int size)
	{
		float neighborDist{ 50 };

		Vector2<float> Steer{};
		int count{};

		for (int i{}; i < size; ++i) 
		{
			Vector2 BoidLocation = Boids[i].GetLocation();
			float distance = m_location.Distance(BoidLocation);
			if (this != &(Boids[i]) && distance < neighborDist)
			{
				Steer += BoidLocation;
				++count;
			}
		}

		if (count > 0)
		{
			Steer /= static_cast<float>(count);
			Steer -= m_location;
			Steer.SetMagnitude(m_maxSpeed);
			Steer -= m_velocity;
			Steer.Limit(m_maxForce);
		}
			

		return Steer;
	}
}
