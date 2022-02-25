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
# include "Common.hpp"
# include "Easing.hpp"
# include "Scene.hpp"

namespace s3d
{
	class Transition
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit constexpr Transition(const Duration& inDuration = SecondsF(0.2), const Duration& outDuration = SecondsF(0.1), double initialValue = 0.0) noexcept;

		constexpr void update(bool in, double deltaSec = Scene::DeltaTime());

		[[nodiscard]]
		constexpr double value() const noexcept;

		[[nodiscard]]
		constexpr bool isZero() const noexcept;

		[[nodiscard]]
		constexpr bool isOne() const noexcept;

		[[nodiscard]]
		constexpr double easeIn(double easingFunction(double) = Easing::Quart) const;

		[[nodiscard]]
		constexpr double easeOut(double easingFunction(double) = Easing::Quart) const;

		[[nodiscard]]
		constexpr double easeInOut(double easingFunction(double) = Easing::Quart) const;

	private:

		double m_inDuration = 0.0;

		double m_outDuration = 0.0;

		double m_value = 0.0;
	};
}

# include "detail/Transition.ipp"
