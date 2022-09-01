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
# include "Optional.hpp"
# include "PointVector.hpp"
# include "String.hpp"
# include "2DShapes.hpp"
# include "Array.hpp"

namespace s3d
{
	/// @brief モニターの情報
	struct MonitorInfo
	{
		/// @brief ディスプレイの名前
		String name;

		/// @brief ディスプレイ ID
		String id;

		/// @brief 内部的に使われているディスプレイの名前
		String displayDeviceName;

		/// @brief ディスプレイ全体の位置とサイズ
		Rect displayRect = Rect::Empty();

		/// @brief タスクバーなどを除いた利用可能な領域の位置とサイズ
		Rect workArea = Rect::Empty();

		/// @brief フルスクリーン時の解像度
		Size fullscreenResolution = Size{ 0, 0 };

		/// @brief メインディスプレイであるか
		bool isPrimary = false;

		/// @brief 物理的なサイズ (mm)
		Optional<Size> sizeMillimeter;

		/// @brief UI の拡大倍率
		Optional<double> scaling;

		/// @brief リフレッシュレート
		Optional<double> refreshRate;

		/// @brief モニターの情報を文字列に変換します。
		/// @return モニターの情報
		[[nodiscard]]
		String format() const;
	};

	namespace System
	{
		/// @brief 使用可能なモニターの一覧を取得します。
		/// @return 使用可能なモニターの一覧
		[[nodiscard]]
		Array<MonitorInfo> EnumerateMonitors();
	}
}
