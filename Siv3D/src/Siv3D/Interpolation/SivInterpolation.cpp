//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Interpolation.hpp>
# include <Siv3D/Math.hpp>

namespace s3d
{
	namespace detail
	{
		template <class VectorType, class ValueType>
		VectorType Damp_impl(const VectorType& a, const VectorType& b, const ValueType r, const ValueType dt) noexcept
		{
			return Math::Lerp(a, b, static_cast<ValueType>(1) - Math::Exp(-r * dt));
		}

		template <class VectorType, class ValueType>
		VectorType SmoothDamp_impl(const VectorType& from, const VectorType& to, VectorType& velocity, const ValueType smoothTime, const ValueType deltaTime, const Optional<ValueType>& maxSpeed)
		{
			const ValueType omega = static_cast<ValueType>(2.0) / smoothTime;
			const ValueType x = (omega * deltaTime);
			const ValueType exp = static_cast<ValueType>(1.0) / (static_cast<ValueType>(1.0) + x + static_cast<ValueType>(0.48) * x * x + static_cast<ValueType>(0.235) * x * x * x);
			VectorType change = (from - to);

			// 速度を maxSpeed に制限
			if (maxSpeed)
			{
				const ValueType maxChange = (*maxSpeed * smoothTime);
				
				if constexpr (std::is_arithmetic_v<VectorType>)
				{
					change = Clamp(change, -maxChange, maxChange);
				}
				else
				{
					change = change.limitLength(maxChange);
				}
			}

			const VectorType temp = (velocity + omega * change) * deltaTime;
			velocity = (velocity - omega * temp) * exp;

			VectorType result = (from - change) + (change + temp) * exp;

			// 行き過ぎを防ぐ
			if constexpr (std::is_arithmetic_v<VectorType>)
			{
				if (((to - from) > 0) == (result > to))
				{
					result = to;
					velocity = (result - to) / deltaTime;
				}
			}
			else
			{
				if ((to - from).dot(result - to) > 0)
				{
					result = to;
					velocity = (result - to) / deltaTime;
				}
			}

			return result;
		}
	}

	namespace Math
	{
		Float2 MoveTowards(const Float2& current, const Float2& target, const float maxSpeed) noexcept
		{
			return (current + (target - current).limitLength(maxSpeed));
		}

		Vec2 MoveTowards(const Vec2& current, const Vec2& target, const double maxSpeed) noexcept
		{
			return (current + (target - current).limitLength(maxSpeed));
		}

		Float3 MoveTowards(const Float3& current, const Float3& target, const float maxSpeed) noexcept
		{
			return (current + (target - current).limitLength(maxSpeed));
		}

		Vec3 MoveTowards(const Vec3& current, const Vec3& target, const double maxSpeed) noexcept
		{
			return (current + (target - current).limitLength(maxSpeed));
		}

		Float4 MoveTowards(const Float4& current, const Float4& target, const float maxSpeed) noexcept
		{
			return (current + (target - current).limitLength(maxSpeed));
		}

		Vec4 MoveTowards(const Vec4& current, const Vec4& target, const double maxSpeed) noexcept
		{
			return (current + (target - current).limitLength(maxSpeed));
		}

		ColorF MoveTowards(const ColorF& current, const ColorF& target, const double maxSpeed) noexcept
		{
			return ColorF{ MoveTowards(current.toVec4(), target.toVec4(), maxSpeed) };
		}

		float Damp(const float a, const float b, const float r, const float dt)
		{
			return detail::Damp_impl(a, b, r, dt);
		}

		double Damp(const double a, const double b, const double r, const double dt)
		{
			return detail::Damp_impl(a, b, r, dt);
		}

		Float2 Damp(const Float2& a, const Float2& b, const float r, const float dt)
		{
			return detail::Damp_impl(a, b, r, dt);
		}

		Vec2 Damp(const Vec2& a, const Vec2& b, const double r, const double dt)
		{
			return detail::Damp_impl(a, b, r, dt);
		}

		Float3 Damp(const Float3& a, const Float3& b, const float r, const float dt)
		{
			return detail::Damp_impl(a, b, r, dt);
		}

		Vec3 Damp(const Vec3& a, const Vec3& b, const double r, const double dt)
		{
			return detail::Damp_impl(a, b, r, dt);
		}

		Float4 Damp(const Float4& a, const Float4& b, const float r, const float dt)
		{
			return detail::Damp_impl(a, b, r, dt);
		}

		Vec4 Damp(const Vec4& a, const Vec4& b, const double r, const double dt)
		{
			return detail::Damp_impl(a, b, r, dt);
		}

		ColorF Damp(const ColorF& a, const ColorF& b, double r, double dt)
		{
			return detail::Damp_impl(a, b, r, dt);
		}

		float SmoothDamp(const float current, const float target, float& velocity, const float smoothTime, const Optional<float>& maxSpeed, const float deltaTime)
		{
			return detail::SmoothDamp_impl(current, target, velocity, smoothTime, deltaTime, maxSpeed);
		}

		double SmoothDamp(const double current, const double target, double& velocity, const double smoothTime, const Optional<double>& maxSpeed, const double deltaTime)
		{
			return detail::SmoothDamp_impl(current, target, velocity, smoothTime, deltaTime, maxSpeed);
		}

		Float2 SmoothDamp(const Float2& current, const Float2& target, Float2& velocity, const float smoothTime, const Optional<float>& maxSpeed, const float deltaTime)
		{
			return detail::SmoothDamp_impl(current, target, velocity, smoothTime, deltaTime, maxSpeed);
		}

		Vec2 SmoothDamp(const Vec2& current, const Vec2& target, Vec2& velocity, const double smoothTime, const Optional<double>& maxSpeed, const double deltaTime)
		{
			return detail::SmoothDamp_impl(current, target, velocity, smoothTime, deltaTime, maxSpeed);
		}

		Float3 SmoothDamp(const Float3& current, const Float3& target, Float3& velocity, const float smoothTime, const Optional<float>& maxSpeed, const float deltaTime)
		{
			return detail::SmoothDamp_impl(current, target, velocity, smoothTime, deltaTime, maxSpeed);
		}

		Vec3 SmoothDamp(const Vec3& current, const Vec3& target, Vec3& velocity, const double smoothTime, const Optional<double>& maxSpeed, const double deltaTime)
		{
			return detail::SmoothDamp_impl(current, target, velocity, smoothTime, deltaTime, maxSpeed);
		}

		Float4 SmoothDamp(const Float4& current, const Float4& target, Float4& velocity, const float smoothTime, const Optional<float>& maxSpeed, const float deltaTime)
		{
			return detail::SmoothDamp_impl(current, target, velocity, smoothTime, deltaTime, maxSpeed);
		}

		Vec4 SmoothDamp(const Vec4& current, const Vec4& target, Vec4& velocity, const double smoothTime, const Optional<double>& maxSpeed, const double deltaTime)
		{
			return detail::SmoothDamp_impl(current, target, velocity, smoothTime, deltaTime, maxSpeed);
		}

		ColorF SmoothDamp(const ColorF& current, const ColorF& target, ColorF& velocity, const double smoothTime, const Optional<double>& maxSpeed, const double deltaTime)
		{
			Vec4 vel = velocity.toVec4();

			const Vec4 result = detail::SmoothDamp_impl(current.toVec4(), target.toVec4(), vel, smoothTime, deltaTime, maxSpeed);

			velocity = ColorF{ vel };

			return ColorF{ result };
		}
	}
}
