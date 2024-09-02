#pragma once

namespace EnttBoids {
	struct RulesFactor {
		float alignment{ 1.0f };
		float cohesion{ 1.0f };
		float separation{ 1.5f };

		static constexpr float min{ 0.0f };
		static constexpr float max{ 2.0f };

		RulesFactor() = default;

		RulesFactor(float align, float cohes, float separ)
			: alignment{ align }
			, cohesion{ cohes }
			, separation{ separ }
		{}

		RulesFactor(const RulesFactor& other) = delete;
		RulesFactor& operator = (const RulesFactor& other) = delete;

		RulesFactor(const RulesFactor&& other) noexcept {
			alignment = other.alignment;
			cohesion = other.cohesion;
			separation = other.separation;
		}

		RulesFactor& operator = (const RulesFactor&& other) noexcept {
			if (this != &other) {
				alignment = other.alignment;
				cohesion = other.cohesion;
				separation = other.separation;
			}

			return *this;
		}
	};
}
