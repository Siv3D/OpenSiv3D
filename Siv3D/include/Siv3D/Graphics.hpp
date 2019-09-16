//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Rectangle.hpp"
# include "Array.hpp"

namespace s3d
{
	struct DisplayMode
	{
		Size size;

		double refreshRateHz;
	};

	struct DisplayOutput
	{
		String name;

		Rect displayRect;

		Array<DisplayMode> displayModes;
	};

	namespace Graphics
	{
		// 現在のフレームのクリアをスキップ
		void SkipClearScreen();

		[[nodiscard]] Array<DisplayOutput> EnumOutputs();

		// フルスクリーンとして使用できる解像度を取得
		[[nodiscard]] Array<Size> GetFullscreenResolutions(double minRefreshRate = 49.0);

		// フレームレートの上限を変更
		// none にするとモニターに合わせる
		void SetTargetFrameRateHz(const Optional<double>& targetFrameRateHz);

		[[nodiscard]] Optional<double> GetTargetFrameRateHz();

		[[nodiscard]] double GetDisplayRefreshRateHz();

		[[nodiscard]] double GetDPIScaling();
	}
}
