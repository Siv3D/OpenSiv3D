//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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
		/// <summary>
		/// ディスプレイの名前
		/// </summary>
		String name;
	
		/// <summary>
		/// ディスプレイ ID
		/// </summary>
		String id;
		
		/// <summary>
		/// 内部的に使われているディスプレイの名前
		/// </summary>
		String displayDeviceName;
		
		/// <summary>
		/// ディスプレイ全体の位置とサイズ
		/// </summary>
		Rect displayRect;

		/// <summary>
		/// タスクバーなどを除いた利用可能な領域の位置とサイズ
		/// </summary>
		Rect workArea;

		/// <summary>
		/// メインディスプレイかどうか
		/// </summary>
		bool isPrimary;
	};

	namespace System
	{
		/// <summary>
		/// 使用可能なモニターの一覧を取得します。
		/// </summary>
		[[nodiscard]] Array<Monitor> EnumerateActiveMonitors();

		/// <summary>
		/// ウィンドウが配置されているモニターのインデックスを取得します。
		/// </summary>
		[[nodiscard]] size_t GetCurrentMonitorIndex();
	}

	namespace DisplayResolution
	{
		inline constexpr Size VGA_640x480(640, 480);

		inline constexpr Size SVGA_800x600(800, 600);

		inline constexpr Size XGA_1024x768(1024, 768);

		inline constexpr Size HD_1280x720(1280, 720);

		inline constexpr Size HD_1366x768(1366, 768);
		
		inline constexpr Size FHD_1920x1080(1920, 1080);
		
		inline constexpr Size WQHD_2560x1440(2560, 1440);
		
		inline constexpr Size UHD_3840x2160(3840, 2160);
		
		inline constexpr Size UHD_7680x4320(7680, 4320);
	}
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Monitor& value);
}
