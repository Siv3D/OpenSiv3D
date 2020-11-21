//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "Duration.hpp"
# include "Scene.hpp"
# include "Math.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	namespace Periodic
	{
		[[nodiscard]]
		inline double Sine0_1(double periodSec, double t = Scene::Time()) noexcept;

		[[nodiscard]]
		inline double Sine0_1(const Duration& period, double t = Scene::Time()) noexcept;

		[[nodiscard]]
		inline double Square0_1(double periodSec, double t = Scene::Time()) noexcept;

		[[nodiscard]]
		inline double Square0_1(const Duration& period, double t = Scene::Time()) noexcept;

		[[nodiscard]]
		inline double Triangle0_1(double periodSec, double t = Scene::Time()) noexcept;

		[[nodiscard]]
		inline double Triangle0_1(const Duration& period, double t = Scene::Time()) noexcept;

		[[nodiscard]]
		inline double Sawtooth0_1(double periodSec, double t = Scene::Time()) noexcept;

		[[nodiscard]]
		inline double Sawtooth0_1(const Duration& period, double t = Scene::Time()) noexcept;

		[[nodiscard]]
		inline double Jump0_1(double periodSec, double t = Scene::Time()) noexcept;

		[[nodiscard]]
		inline double Jump0_1(const Duration& period, double t = Scene::Time()) noexcept;
	}
}

# include "detail/Periodic.ipp"
