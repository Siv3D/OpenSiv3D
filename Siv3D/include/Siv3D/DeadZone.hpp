//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// デッドゾーンの計算方式
	/// </summary>
	enum class DeadZoneType
	{
		/// <summary>
		/// デッドゾーンなし
		/// </summary>
		None,

		/// <summary>
		/// 軸独立
		/// </summary>
		Independent,

		/// <summary>
		/// 円形
		/// </summary>
		Circular
	};

	/// <summary>
	/// デッドゾーンの定義
	/// </summary>
	struct DeadZone
	{
		/// <summary>
		/// デッドゾーンの大きさ
		/// </summary>
		double size = 0.0;

		/// <summary>
		/// 飽和地点
		/// </summary>
		double maxValue = 1.0;

		/// <summary>
		/// デッドゾーンの計算方式
		/// </summary>
		DeadZoneType type = DeadZoneType::None;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		constexpr DeadZone() = default;

		/// <summary>
		/// デッドゾーンを定義します。
		/// </summary>
		/// <param name="_size">
		/// デッドゾーンの大きさ
		/// </param>
		/// <param name="_maxValue">
		/// 飽和地点
		/// </param>
		/// <param name="_type">
		/// デッドゾーンの計算方式
		/// </param>
		constexpr DeadZone(double _size, double _maxValue, DeadZoneType _type)
			: size(_size)
			, maxValue(_maxValue)
			, type(_type) {}

		/// <summary>
		/// デッドゾーン無し
		/// </summary>
		/// <remarks>
		/// { 0.0, 1.0, DeadZoneType::None }
		/// </remarks>
		static constexpr DeadZone Disabled()
		{
			return DeadZone{ 0.0, 1.0, DeadZoneType::None };
		}
	};
}
