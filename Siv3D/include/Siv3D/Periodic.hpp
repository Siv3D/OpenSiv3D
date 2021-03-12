//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
		/// @brief サインカーブに従って、周期的に [0.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時刻（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Sine0_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief サインカーブに従って、周期的に [0.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時刻（秒）
		/// @return [0.0, 1.0] の範囲の値
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
