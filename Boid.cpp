#include "Boid.hpp"
#include <raylib.h>
#include <cmath>

namespace EnttBoids {
	
	Boid::Boid(float x, float y, RulesFactor& rulesFactor)
		: m_location{x, y}
		, m_maxForce{0.2}
		, m_maxSpeed{5}
		, m_rulesFactor{ &rulesFactor }
	{
		m_velocity = Vector2{ static_cast<float>(GetRandomValue(-100, 100)) / 100.f, static_cast<float>(GetRandomValue(-100, 100)) / 100.f };
		m_velocity.SetMagnitude((float)GetRandomValue(2, 4));
	}

	Boid::Boid(float x, float y, bool predatorCheck, RulesFactor& rulesFactor)
		: m_location{x, y}
		, m_bPredator{predatorCheck}
		, m_maxForce{ 0.2 }
		, m_rulesFactor{ &rulesFactor }
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
		: m_rulesFactor{other.m_rulesFactor}
	{
		m_location = other.m_location;
		m_velocity = other.m_velocity;
		m_accelaration = other.m_accelaration;
		m_maxForce = other.m_maxForce;
		m_maxSpeed = other.m_maxSpeed;
		m_rulesFactor = other.m_rulesFactor;
	}

	Boid& Boid::operator=(const Boid&& other) noexcept
	{
		if (this != &other)
		{
			m_location = other.m_location;
			m_velocity = other.m_velocity;
			m_accelaration = other.m_accelaration;
			m_maxForce = other.m_maxForce;
			m_maxSpeed = other.m_maxSpeed;
			m_rulesFactor = other.m_rulesFactor;
		}
		
		return *this;
	}

	Boid& Boid::operator=(const Boid& other) noexcept
	{
		if (this != &other)
		{
			m_location = other.m_location;
			m_velocity = other.m_velocity;
			m_accelaration = other.m_accelaration;
			m_maxForce = other.m_maxForce;
			m_maxSpeed = other.m_maxSpeed;
			m_rulesFactor = other.m_rulesFactor;
		}
		
		return *this;

	}

	void Boid::Run(const std::array<Boid, Settings::TotalBoids>& Boids , const float DeltaTime)
	{
		Flock(Boids);
		Update(DeltaTime);
	}

	void Boid::LimitLocation(const Vector2<int> Bounds)
	{
		if (m_location.x < 0)
		{
			m_location.x = Bounds.x;
		}
		else if (m_location.x > Bounds.x)
		{
			m_location.x = 0;
		}

		if (m_location.y < 0)
		{
			m_location.y = Bounds.y;
		}
		else if (m_location.y > Bounds.y)
		{
			m_location.y = 0;
		}
	}

	void Boid::Update(const float DeltaTime)
	{
		m_velocity += (m_accelaration * DeltaTime);
		m_location += (m_velocity * DeltaTime);
		m_velocity.Limit(m_maxSpeed);

		// Reset Acceleration
		m_accelaration *= 0;
	}

	void Boid::Flock(const std::array<Boid, Settings::TotalBoids>& Boids )
	{
		Vector2 Sep = Separation(Boids);
		Vector2 Coh = Cohesion(Boids);
		Vector2 Aln = Alignment(Boids);

		Sep *= m_rulesFactor->separation;
		Coh *= m_rulesFactor->cohesion;
		Aln *= m_rulesFactor->alignment;

		m_accelaration += Aln;
		m_accelaration += Sep;
		m_accelaration += Coh;
		
	}
	
	Vector2<float> Boid::Separation(const std::array<Boid, Settings::TotalBoids>& Boids )
	{
		Vector2<float> Steer{};
		int count{};

		for (int i{ 0 }; i < Boids.size(); ++i) {
			double d = m_location.Distance(Boids[i].m_location);
			
			if (this != &(Boids[i]) && d < Settings::perceptionRadius)
			{
				Vector2<float> Diff{};
				Diff = m_location - Boids[i].GetLocationRef();
				Diff.Normalize();
				Diff /= std::fmax((d * d), 0.0000000001f); // let's prevent from division by zero!!!
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

	Vector2<float> Boid::Alignment(const std::array<Boid, Settings::TotalBoids>& Boids )
	{
		Vector2<float> Steer{};
		int count{};

		for (int i{}; i < Boids.size(); ++i)
		{
			const Vector2<float>& BoidLocation = Boids[i].GetLocationRef();
			const Vector2<float>& BoidVelocity = Boids[i].GetVelocityRef();
			float distance = m_location.Distance(BoidLocation);
			if (this != &(Boids[i]) && distance < Settings::perceptionRadius)
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

	Vector2<float> Boid::Cohesion(const std::array<Boid, Settings::TotalBoids>& Boids )
	{
		Vector2<float> Steer{};
		int count{};

		for (int i{}; i < Boids.size(); ++i) 
		{
			const Vector2<float>& BoidLocation = Boids[i].GetLocationRef();
			float distance = m_location.Distance(BoidLocation);
			if (this != &(Boids[i]) && distance < Settings::perceptionRadius)
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
