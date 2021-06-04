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
# include "Optional.hpp"
# include "PointVector.hpp"
# include "String.hpp"
# include "2DShapes.hpp"
# include "Array.hpp"

namespace s3d
{
	/// @brief モニターの情報
	struct Monitor
	{
		/// @brief ディスプレイの名前
		String name;

		/// @brief ディスプレイ ID
		String id;

		/// @brief 内部的に使われているディスプレイの名前
		String displayDeviceName;

		/// @brief ディスプレイ全体の位置とサイズ
		Rect displayRect = Rect{ 0 };

		/// @brief タスクバーなどを除いた利用可能な領域の位置とサイズ
		Rect workArea = Rect{ 0 };
		
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
		Array<Monitor> EnumerateMonitors();

		/// @brief ウィンドウが配置されているモニターのインデックスを取得します。
		/// @return ウィンドウが配置されているモニターのインデックス
		[[nodiscard]]
		size_t GetCurrentMonitorIndex();

		/// @brief ウィンドウが配置されているモニターの情報を取得します。
		/// @return ウィンドウが配置されているモニターの情報
		[[nodiscard]]
		Monitor GetCurrentMonitor();
	}
}
