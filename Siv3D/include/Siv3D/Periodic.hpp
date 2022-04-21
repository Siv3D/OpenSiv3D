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
# include "PointVector.hpp"
# include "Duration.hpp"
# include "Scene.hpp"
# include "Math.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	//
	// [Sine0_1]
	// 
	// 1.0 | **      **      **      **
	//     |*  *    *  *    *  *    *
	// 0.5 *    *  *    *  *    *  *
	//     |    *  *    *  *    *  *
	// 0.0 |     **      **      **
	//     ----------------------------
	//     0       1       2       3
	//
	// [Square0_1]
	// 
	// 1.0 ****    ****    ****    ****
	//     |
	// 0.5 |
	//     |  
	// 0.0 |   ****    ****    ****   
	//     ----------------------------
	//     0       1       2       3
	//
	// [Triangle0_1]
	// 
	// 1.0 |   *       *       *       
	//     |  * *     * *     * *     *
	// 0.5 | *   *   *   *   *   *   *
	//     |*     * *     * *     * *
	// 0.0 *       *       *       *
	//     ----------------------------
	//     0       1       2       3
	//
	// [Sawtooth0_1]
	// 
	// 1.0 |       -       -       -
	//     |     *       *       *
	// 0.5 |   *       *       *       *
	//     | *       *       *       *
	// 0.0 *       +       +       +
	//     ----------------------------
	//     0       1       2       3
	//
	// [Jump0_1]
	// 
	// 1.0 |  -^-     -^-     -^-     -
	//     | *   *   *   *   *   *   *
	// 0.5 |*     * *     * *     * *
	//     |*     * *     * *     * *
	// 0.0 *       *       *       *
	//     ----------------------------
	//     0       1       2       3
	//
	// 
	// 
	// [Sine1_1]
	// 
	// 1.0 | **      **      **      **
	//     |*  *    *  *    *  *    *
	// 0.0 *    *  *    *  *    *  *
	//     |    *  *    *  *    *  *
	//-1.0 |     **      **      **
	//     ----------------------------
	//     0       1       2       3
	//
	// [Square1_1]
	// 
	// 1.0 ****    ****    ****    ****
	//     |
	// 0.5 |
	//     |  
	//-1.0 |   ****    ****    ****   
	//     ----------------------------
	//     0       1       2       3
	//
	// [Triangle1_1]
	// 
	// 1.0 |   *       *       *       
	//     |  * *     * *     * *     *
	// 0.0 | *   *   *   *   *   *   *
	//     |*     * *     * *     * *
	//-1.0 *       *       *       *
	//     ----------------------------
	//     0       1       2       3
	//
	// [Sawtooth1_1]
	// 
	// 1.0 |       -       -       -
	//     |     *       *       *
	// 0.0 |   *       *       *       *
	//     | *       *       *       *
	//-1.0 *       +       +       +
	//     ----------------------------
	//     0       1       2       3
	//
	// [Jump1_1]
	// 
	// 1.0 |  -^-     -^-     -^-     -
	//     | *   *   *   *   *   *   *
	// 0.0 |*     * *     * *     * *
	//     |*     * *     * *     * *
	//-1.0 *       *       *       *
	//     ----------------------------
	//     0       1       2       3
	//

	namespace Periodic
	{
		/// @brief サインカーブに従って、周期的に [0.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時間（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Sine0_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief サインカーブに従って、周期的に [0.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時間（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Sine0_1(const Duration& period, double t = Scene::Time()) noexcept;

		/// @brief 矩形波に従って、周期的に [0.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時間（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]	
		inline double Square0_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief 矩形波に従って、周期的に [0.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時間（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Square0_1(const Duration& period, double t = Scene::Time()) noexcept;

		/// @brief 三角波に従って、周期的に [0.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時間（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Triangle0_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief 三角波に従って、周期的に [0.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時間（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Triangle0_1(const Duration& period, double t = Scene::Time()) noexcept;

		/// @brief のこぎり波に従って、周期的に [0.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時間（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Sawtooth0_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief のこぎり波に従って、周期的に [0.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時間（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Sawtooth0_1(const Duration& period, double t = Scene::Time()) noexcept;

		/// @brief ジャンプする運動に従って、周期的に [0.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時間（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Jump0_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief ジャンプする運動に従って、周期的に [0.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時間（秒）
		/// @return [0.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Jump0_1(const Duration& period, double t = Scene::Time()) noexcept;


		/// @brief サインカーブに従って、周期的に [-1.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時間（秒）
		/// @return [-1.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Sine1_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief サインカーブに従って、周期的に [-1.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時間（秒）
		/// @return [-1.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Sine1_1(const Duration& period, double t = Scene::Time()) noexcept;

		/// @brief 矩形波に従って、周期的に [-1.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時間（秒）
		/// @return [-1.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Square1_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief 矩形波に従って、周期的に [-1.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時間（秒）
		/// @return [-1.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Square1_1(const Duration& period, double t = Scene::Time()) noexcept;

		/// @brief 三角波に従って、周期的に [-1.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時間（秒）
		/// @return [-1.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Triangle1_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief 三角波に従って、周期的に [-1.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時間（秒）
		/// @return [-1.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Triangle1_1(const Duration& period, double t = Scene::Time()) noexcept;

		/// @brief のこぎり波に従って、周期的に [-1.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時間（秒）
		/// @return [-1.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Sawtooth1_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief のこぎり波に従って、周期的に [-1.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時間（秒）
		/// @return [-1.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Sawtooth1_1(const Duration& period, double t = Scene::Time()) noexcept;

		/// @brief ジャンプする運動に従って、周期的に [-1.0, 1.0] の値を返します。
		/// @param periodSec 周期（秒）
		/// @param t 経過時間（秒）
		/// @return [-1.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Jump1_1(double periodSec, double t = Scene::Time()) noexcept;

		/// @brief ジャンプする運動に従って、周期的に [-1.0, 1.0] の値を返します。
		/// @param period 周期
		/// @param t 経過時間（秒）
		/// @return [-1.0, 1.0] の範囲の値
		[[nodiscard]]
		inline double Jump1_1(const Duration& period, double t = Scene::Time()) noexcept;
	}
}

# include "detail/Periodic.ipp"
