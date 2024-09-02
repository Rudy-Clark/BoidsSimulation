#pragma once

#include <array>
#include <functional>
#include "Boid.hpp"
#include "Settings.hpp"
#include "RulesFactor.hpp"

namespace EnttBoids {
	class Flock
	{
	public:
		Flock();
		
		void Flocking(const float DeltaTime);

		void ForEachBoid(std::function<void(const Vector2<float>& Loc, const Vector2<float>& Vel)>f);

		float* GetAlignmentPtr();
		float* GetSeparationPtr();
		float* GetCohesionPtr();
		inline const RulesFactor& GetRulesFactorRef() const { return m_rulesFactor; };

	private:
		std::array<Boid, Settings::TotalBoids> m_boids;
		int m_boidsIterCount{0};
		RulesFactor m_rulesFactor{};
	};
}
