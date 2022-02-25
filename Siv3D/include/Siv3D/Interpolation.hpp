//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cmath>
# include "Common.hpp"
# include "PointVector.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"
# include "Scene.hpp"

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
		/// @brief 線形補間した結果を返します。
		/// @tparam T 
		/// @tparam U 
		/// @tparam V 
		/// @param v1 
		/// @param v2 
		/// @param f 
		/// @return 線形補間した結果
		template <class T, class U, class V>
		[[nodiscard]]
		inline constexpr auto Lerp(const T& v1, const U& v2, V f) noexcept;

		[[nodiscard]]
		inline constexpr double InvLerp(double a, double b, double value) noexcept;

		template <class T, class U>
		[[nodiscard]]
		inline constexpr auto Map(double value, double a, double b, const T& v1, const U& v2) noexcept;

		template <class T, class U, class V>
		[[nodiscard]]
		inline auto LerpAngle(T from, U to, V t) noexcept;

		[[nodiscard]]
		inline double Eerp(double a, double b, double t) noexcept;

		[[nodiscard]]
		float Damp(float a, float b, float r, float dt);
		
		[[nodiscard]]
		double Damp(double a, double b, double r, double dt);

		[[nodiscard]]
		Float2 Damp(const Float2& a, const Float2& b, float r, float dt);

		[[nodiscard]]
		Vec2 Damp(const Vec2& a, const Vec2& b, double r, double dt);

		[[nodiscard]]
		Float3 Damp(const Float3& a, const Float3& b, float r, float dt);

		[[nodiscard]]
		Vec3 Damp(const Vec3& a, const Vec3& b, double r, double dt);

		[[nodiscard]]
		Float4 Damp(const Float4& a, const Float4& b, float r, float dt);

		[[nodiscard]]
		Vec4 Damp(const Vec4& a, const Vec4& b, double r, double dt);

		/// @brief 目標地点に向かってスムーズに移動させます。
		/// @param from 現在地
		/// @param to 目標地点
		/// @param velocity 現在の速度
		/// @param smoothTime 平滑化時間（最大速度で目標に向かうときに期待される所要時間）。動く目標を追いかけるときの遅延時間で、小さいと目標に早く到達する
		/// @param maxSpeed 最大速度。無制限の場合は unspecified
		/// @param deltaTime 前回からの経過時間。デフォルトでは Scene::DeltaTime()
		/// @return 新しい現在地
		[[nodiscard]]
		float SmoothDamp(float from, float to, float& velocity, float smoothTime, const Optional<float>& maxSpeed = unspecified, float deltaTime = static_cast<float>(Scene::DeltaTime()));

		/// @brief 目標地点に向かってスムーズに移動させます。
		/// @param from 現在地
		/// @param to 目標地点
		/// @param velocity 現在の速度
		/// @param smoothTime 平滑化時間（最大速度で目標に向かうときに期待される所要時間）。動く目標を追いかけるときの遅延時間で、小さいと目標に早く到達する
		/// @param maxSpeed 最大速度。無制限の場合は unspecified
		/// @param deltaTime 前回からの経過時間。デフォルトでは Scene::DeltaTime()
		/// @return 新しい現在地	
		[[nodiscard]]
		double SmoothDamp(double from, double to, double& velocity, double smoothTime, const Optional<double>& maxSpeed = unspecified, double deltaTime = Scene::DeltaTime());

		/// @brief 目標地点に向かってスムーズに移動させます。
		/// @param from 現在地
		/// @param to 目標地点
		/// @param velocity 現在の速度
		/// @param smoothTime 平滑化時間（最大速度で目標に向かうときに期待される所要時間）。動く目標を追いかけるときの遅延時間で、小さいと目標に早く到達する
		/// @param maxSpeed 最大速度。無制限の場合は unspecified
		/// @param deltaTime 前回からの経過時間。デフォルトでは Scene::DeltaTime()
		/// @return 新しい現在地
		[[nodiscard]]
		Float2 SmoothDamp(const Float2& from, const Float2& to, Float2& velocity, float smoothTime, const Optional<float>& maxSpeed = unspecified, float deltaTime = static_cast<float>(Scene::DeltaTime()));

		/// @brief 目標地点に向かってスムーズに移動させます。
		/// @param from 現在地
		/// @param to 目標地点
		/// @param velocity 現在の速度
		/// @param smoothTime 平滑化時間（最大速度で目標に向かうときに期待される所要時間）。動く目標を追いかけるときの遅延時間で、小さいと目標に早く到達する
		/// @param maxSpeed 最大速度。無制限の場合は unspecified
		/// @param deltaTime 前回からの経過時間。デフォルトでは Scene::DeltaTime()
		/// @return 新しい現在地
		[[nodiscard]]
		Vec2 SmoothDamp(const Vec2& from, const Vec2& to, Vec2& velocity, double smoothTime, const Optional<double>& maxSpeed = unspecified, double deltaTime = Scene::DeltaTime());

		/// @brief 目標地点に向かってスムーズに移動させます。
		/// @param from 現在地
		/// @param to 目標地点
		/// @param velocity 現在の速度
		/// @param smoothTime 平滑化時間（最大速度で目標に向かうときに期待される所要時間）。動く目標を追いかけるときの遅延時間で、小さいと目標に早く到達する
		/// @param deltaTime 前回からの経過時間
		/// @param maxSpeed 最大速度。無制限の場合は unspecified
		/// @return 新しい現在地
		[[nodiscard]]
		Float3 SmoothDamp(const Float3& from, const Float3& to, Float3& velocity, float smoothTime, const Optional<float>& maxSpeed = unspecified, float deltaTime = static_cast<float>(Scene::DeltaTime()));

		/// @brief 目標地点に向かってスムーズに移動させます。
		/// @param from 現在地
		/// @param to 目標地点
		/// @param velocity 現在の速度
		/// @param smoothTime 平滑化時間（最大速度で目標に向かうときに期待される所要時間）。動く目標を追いかけるときの遅延時間で、小さいと目標に早く到達する
		/// @param maxSpeed 最大速度。無制限の場合は unspecified
		/// @param deltaTime 前回からの経過時間。デフォルトでは Scene::DeltaTime()
		/// @return 新しい現在地
		[[nodiscard]]
		Vec3 SmoothDamp(const Vec3& from, const Vec3& to, Vec3& velocity, double smoothTime, const Optional<double>& maxSpeed = unspecified, double deltaTime = Scene::DeltaTime());

		/// @brief 目標地点に向かってスムーズに移動させます。
		/// @param from 現在地
		/// @param to 目標地点
		/// @param velocity 現在の速度
		/// @param smoothTime 平滑化時間（最大速度で目標に向かうときに期待される所要時間）。動く目標を追いかけるときの遅延時間で、小さいと目標に早く到達する
		/// @param maxSpeed 最大速度。無制限の場合は unspecified
		/// @param deltaTime 前回からの経過時間。デフォルトでは Scene::DeltaTime()
		/// @return 新しい現在地
		[[nodiscard]]
		Float4 SmoothDamp(const Float4& from, const Float4& to, Float4& velocity, float smoothTime, const Optional<float>& maxSpeed = unspecified, float deltaTime = static_cast<float>(Scene::DeltaTime()));

		/// @brief 目標地点に向かってスムーズに移動させます。
		/// @param from 現在地
		/// @param to 目標地点
		/// @param velocity 現在の速度
		/// @param smoothTime 平滑化時間（最大速度で目標に向かうときに期待される所要時間）。動く目標を追いかけるときの遅延時間で、小さいと目標に早く到達する
		/// @param maxSpeed 最大速度。無制限の場合は unspecified
		/// @param deltaTime 前回からの経過時間。デフォルトでは Scene::DeltaTime()
		/// @return 新しい現在地
		[[nodiscard]]
		Vec4 SmoothDamp(const Vec4& from, const Vec4& to, Vec4& velocity, double smoothTime, const Optional<double>& maxSpeed = unspecified, double deltaTime = Scene::DeltaTime());
	}
}

# include "detail/Interpolation.ipp"
