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
# include "Array.hpp"
# include "String.hpp"
# include "Rectangle.hpp"

namespace s3d
{
	struct Monitor
	{
		/// <summary>ディスプレイの名前</summary>
		String name;
		String id;
		/// <summary>内部的に使われているディスプレイの名前</summary>
		String displayDeviceName;
		/// <summary>ディスプレイ全体の位置とサイズ</summary>
		Rect displayRect;
		/// <summary>タスクバーなどを除いた利用可能な領域の位置とサイズ</summary>
		Rect workArea;
		/// <summary>メインディスプレイかどうか</summary>
		bool isPrimary;
	};

	namespace System
	{
		/// <summary>
		/// 使用可能なモニターの一覧を取得します。
		/// </summary>
		Array<Monitor> EnumActiveMonitors();

		/// <summary>
		/// ウィンドウが配置されているモニターのインデックスを取得します。
		/// </summary>
		size_t GetCurrentMonitorIndex();
	}
}
