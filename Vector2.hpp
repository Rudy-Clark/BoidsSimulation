#pragma once

#include <iostream>
#include <assert.h>
#include <math.h>
#include <iomanip>
#include "raylib.h"

namespace EnttBoids {
	template<typename T>
	struct Vector2 {
		T x{};
		T y{};

		Vector2() = default;

		explicit Vector2(T in_x, T in_y) noexcept
			: x(in_x)
			, y(in_y)
		{};

		Vector2(const Vector2<T>& other) noexcept {
			x = other.x;
			y = other.y;
		}

		Vector2(const Vector2<T>&& other) noexcept {
			x = other.x;
			y = other.y;
		}

		static double Magnitude(const Vector2<T>& v) {
			return std::sqrt((v.x * v.x) + (v.y * v.y));
		}

		double Magnitude() const {
			return std::sqrt((x * x) + (y * y));
		}

		void Normalize() {
			double tempMagnitude = Magnitude();
			if (tempMagnitude == 0) return;

			x /= tempMagnitude;
			y /= tempMagnitude;
		}

		void SetMagnitude(T scale) {
			Normalize();
			x *= scale;
			y *= scale;
		}

		void Limit(double max) {
			double size = Magnitude();
			if (size > max) {
				Normalize();
				x = static_cast<double>(x) * max;
				y = static_cast<double>(y) * max;
			}
		}

		double Distance(const Vector2<T>& v) {
			T dx = x - v.x;
			T dy = y - v.y;
			double dist = Vector2::Magnitude(Vector2{ dx, dy });

			return dist;
		}

		double DotProduct(const Vector2<T>& v) const {
			return (x * v.x) + (y * v.y);
		}

		double AngleBetween(const Vector2& other) const {
			double dot = DotProduct(other);
			double magn1 = this->Magnitude();
			double magn2 = other.Magnitude();
			double amt = dot / (magn1 * magn2);
			if (amt < -1.0) 
			{
				return PI;
			}
			else if (amt >= 1.0) 
			{
				return 0;
			}

			return std::acos(amt);
		}

		// OPERATOR OVERLOADING
		Vector2<T>& operator = (const Vector2<T>& other) noexcept {
			x = other.x;
			y = other.y;
			return *this;
		}

		// Adding operators and params
		Vector2<T> operator + (const Vector2<T>& other) noexcept {
			return Vector2<T>( x + other.x, y + other.y );
		}

		Vector2<T>& operator += (const Vector2<T>& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2<T> operator + (T scalar) noexcept {
			return Vector2<T>(x + scalar, y + scalar);
		}

		Vector2<T>& operator += (T scalar) {
			x += scalar;
			y += scalar;
			return *this;
		}
		
		// Subtraction
		Vector2<T> operator - (const Vector2<T>& other) noexcept {
			return Vector2<T>(x - other.x, y - other.y);
		}

		Vector2<T>& operator -= (const Vector2<T>& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vector2<T> operator - (T scalar) noexcept {
			return Vector2<T>(x - scalar, y - scalar);
		}

		Vector2<T>& operator -= (T scalar) {
			x -= scalar;
			y -= scalar;
			return *this;
		}

		// Dot Product
		double operator * (const Vector2<T>& other) noexcept {
			return (static_cast<double>(x) * static_cast<double>(other.x)) + (static_cast<double>(y) * static_cast<double>(other.y));
		}

		Vector2<T> operator * (T scalar) const noexcept {
			return Vector2(x * scalar, y * scalar);
		}

		Vector2<T>& operator *= (T scalar) noexcept {
			x *= scalar;
			y *= scalar;
			return *this;
		}

		// Division
		Vector2<T> operator / (const Vector2<T>& other) {
			assert(other.x != 0 && other.y != 0 && "Division By Zero!!!");
			return Vector2(x / other.x, y / other.y);
		}

		Vector2<T> operator / (T scalar) {
			assert(scalar != 0 && "Division By Zero!!!");
			return Vector2(x / scalar, y / scalar);
		}

		Vector2<T>& operator /= (const Vector2<T>& other) {
			assert(other.x != 0 && other.y != 0 && "Division By Zero!!!");
			x /= other.x;
			y /= other.y;

			return *this;
		}

		Vector2<T>& operator /= (T scalar) {
			assert(scalar != 0 && "Division By Zero!!!");
			x /= scalar;
			y /= scalar;

			return *this;
		}

	};

	// For debug purposes
	template<typename T>
	std::ostream& operator <<(std::ostream& out, const Vector2<T>& other) {
		out << std::setprecision(10);
		out << "Vector2(" << other.x << ", " << other.y << ")" << '\n';

		return out;
	}
}