#pragma once

#include <array>
#include "Vector2.hpp"
#include "Settings.hpp"
#include "RulesFactor.hpp"

namespace EnttBoids {
	class Boid
	{
	public:
		Boid() = default;
		Boid(float x, float y, RulesFactor& rulesFactor);
		Boid(float x, float y, bool predatorCheck, RulesFactor& rulesFactor);

		Boid(const Boid&& other) noexcept;
		Boid& operator = (const Boid&& other) noexcept;
		Boid(const Boid& other) = delete;
		Boid& operator = (const Boid& other) noexcept;

		inline const Vector2<float>& GetAccelarationRef() const { return m_accelaration; };
		inline const Vector2<float>& GetVelocityRef() const { return m_velocity; };
		inline const Vector2<float>& GetLocationRef() const { return m_location; };

		inline void SetLocation(const Vector2<float>& location) { m_location = location; };

		void Run(const std::array<Boid, Settings::TotalBoids>& Boids, const float DeltaTime);
		void LimitLocation(const Vector2<int> Bounds);

	private:
		void Update(const float DeltaTime);
		void Flock(const std::array<Boid, Settings::TotalBoids>& Boids);

		// Main rules for boids simulation
		Vector2<float> Separation(const std::array<Boid, Settings::TotalBoids>& Boids);
		Vector2<float> Alignment(const std::array<Boid, Settings::TotalBoids>& Boids);
		Vector2<float> Cohesion(const std::array<Boid, Settings::TotalBoids>& Boids);

		bool m_bPredator{};
		Vector2<float> m_accelaration{};
		Vector2<float> m_velocity{};
		Vector2<float> m_location{};

		float m_maxSpeed{};
		float m_maxForce{};

		RulesFactor* m_rulesFactor{};
	};
}
