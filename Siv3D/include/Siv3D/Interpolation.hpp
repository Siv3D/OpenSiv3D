//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <type_traits>
# include "PointVector.hpp"
# include "Math.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"

namespace s3d
{
	namespace detail
	{
		template <class, class = std::void_t<>>
		struct HasLerp : std::false_type {};

		template <class Type>
		struct HasLerp<Type, std::void_t<decltype(std::declval<Type&>().lerp(std::declval<const Type&>(), 0.0))>> : std::true_type {};

		template <class Type> constexpr bool HasLerp_v = HasLerp<Type>::value;
	}

	namespace Math
	{
		/// <summary>
		/// 線形補間した結果を返します。
		/// </summary>
		template <class T, class U, class V>
		[[nodiscard]] inline constexpr auto Lerp(const T& v1, const U& v2, V f) noexcept
		{
			if constexpr(detail::HasLerp_v<T>)
			{
				return v1.lerp(v2, f);
			}
			else
			{
				return v1 + (v2 - v1) * f;
			}
		}

		[[nodiscard]] float Damp(float a, float b, float r, float dt);
		[[nodiscard]] double Damp(double a, double b, double r, double dt);

		[[nodiscard]] Float2 Damp(const Float2& a, const Float2& b, float r, float dt);
		[[nodiscard]] Vec2 Damp(const Vec2& a, const Vec2& b, double r, double dt);

		[[nodiscard]] Float3 Damp(const Float3& a, const Float3& b, float r, float dt);
		[[nodiscard]] Vec3 Damp(const Vec3& a, const Vec3& b, double r, double dt);

		[[nodiscard]] Float4 Damp(const Float4& a, const Float4& b, float r, float dt);
		[[nodiscard]] Vec4 Damp(const Vec4& a, const Vec4& b, double r, double dt);

		[[nodiscard]] float SmoothDamp(float from, float to, float& velocity, float smoothTime, float deltaTime, const Optional<float>& maxSpeed = unspecified);
		[[nodiscard]] double SmoothDamp(double from, double to, double& velocity, double smoothTime, double deltaTime, const Optional<double>& maxSpeed = unspecified);

		[[nodiscard]] Float2 SmoothDamp(const Float2& from, Float2 to, Float2& velocity, float smoothTime, float deltaTime, const Optional<float>& maxSpeed = unspecified);
		[[nodiscard]] Vec2 SmoothDamp(const Vec2& from, Vec2 to, Vec2& velocity, double smoothTime, double deltaTime, const Optional<double>& maxSpeed = unspecified);

		[[nodiscard]] Float3 SmoothDamp(const Float3& from, Float3 to, Float3& velocity, float smoothTime, float deltaTime, const Optional<float>& maxSpeed = unspecified);
		[[nodiscard]] Vec3 SmoothDamp(const Vec3& from, Vec3 to, Vec3& velocity, double smoothTime, double deltaTime, const Optional<double>& maxSpeed = unspecified);

		[[nodiscard]] Float4 SmoothDamp(const Float4& from, Float4 to, Float4& velocity, float smoothTime, float deltaTime, const Optional<float>& maxSpeed = unspecified);
		[[nodiscard]] Vec4 SmoothDamp(const Vec4& from, Vec4 to, Vec4& velocity, double smoothTime, double deltaTime, const Optional<double>& maxSpeed = unspecified);

		[[nodiscard]] inline constexpr double InvLerp(double a, double b, double value) noexcept
		{
			return (value - a) / (b - a);
		}
	}
}
