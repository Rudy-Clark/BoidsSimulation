#pragma once

#include <array>
#include "Vector2.hpp"
#include "Settings.hpp"

namespace EnttBoids {
	class Boid
	{
	public:
		Boid() = default;
		Boid(float x, float y);
		Boid(float x, float y, bool predatorCheck);

		Boid(const Boid&& other) noexcept;
		Boid& operator = (const Boid&& other) noexcept;
		Boid(const Boid& other) = delete;
		Boid& operator = (const Boid& other) = delete;

		inline Vector2<float> GetAccelaration() const { return m_accelaration; };
		inline Vector2<float> GetVelocity() const { return m_velocity; };
		inline Vector2<float> GetLocation() const { return m_location; };

		inline void SetLocation(const Vector2<float>& location) { m_location = location; };

		void Run(const std::array<Boid, Settings::TotalBoids>& Boids, const float DeltaTime);
		
	private:
		void Update(const float DeltaTime);
		void Flock(const std::array<Boid, Settings::TotalBoids>& Boids);

		// Min rules for boids simulation
		Vector2<float> Separation(const std::array<Boid, Settings::TotalBoids>& Boids);
		Vector2<float> Alignment(const std::array<Boid, Settings::TotalBoids>& Boids);
		Vector2<float> Cohesion(const std::array<Boid, Settings::TotalBoids>& Boids);

		bool m_bPredator{};
		Vector2<float> m_accelaration{};
		Vector2<float> m_velocity{};
		Vector2<float> m_location{};

		float m_maxSpeed{};
		float m_maxForce{};
	};
}
