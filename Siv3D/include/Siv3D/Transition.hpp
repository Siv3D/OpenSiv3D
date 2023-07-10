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

# pragma once
# include "Common.hpp"
# include "Easing.hpp"
# include "Scene.hpp"

namespace s3d
{
	class Transition
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit constexpr Transition(const Duration& inDuration = SecondsF{ 0.2 }, const Duration& outDuration = SecondsF{ 0.1 }, double initialValue = 0.0) noexcept;

		/// @brief トランジションの値を更新します。
		/// @param in トランジションの値を増加させる場合 true, 減少させる場合は false
		/// @param deltaSec 前回のフレームからの経過時間（秒）
		constexpr void update(bool in, double deltaSec = Scene::DeltaTime());

		/// @brief 現在のトランジションの値を返します。
		/// @return 現在のトランジションの値
		[[nodiscard]]
		constexpr double value() const noexcept;

		/// @brief トランジションの値が 0.0 であるかを返します。
		/// @return トランジションの値が 0.0 である場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool isZero() const noexcept;

		/// @brief トランジションの値が 1.0 であるかを返します。
		/// @return トランジションの値が 1.0 である場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool isOne() const noexcept;

		[[nodiscard]]
		constexpr double easeIn(double easingFunction(double) = Easing::Quart) const;

		[[nodiscard]]
		constexpr double easeOut(double easingFunction(double) = Easing::Quart) const;

		[[nodiscard]]
		constexpr double easeInOut(double easingFunction(double) = Easing::Quart) const;

		/// @brief トランジションの値をリセットします。
		/// @param initialValue リセット後のトランジションの値の初期値
		constexpr void reset(double initialValue = 0.0) noexcept;

	private:

		double m_inDuration = 0.0;

		double m_outDuration = 0.0;

		double m_value = 0.0;
	};
}

# include "detail/Transition.ipp"
