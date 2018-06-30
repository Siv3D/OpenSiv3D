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
# include "Unspecified.hpp"

namespace s3d
{
	namespace SimpleGUI
	{
		[[nodiscard]] RectF ButtonRegion(const String& label, const Vec2& pos, const Optional<int32>& width = unspecified);

		[[nodiscard]] RectF ButtonRegionAt(const String& label, const Vec2& center, const Optional<int32>& width = unspecified);

		[[nodiscard]] bool Button(const String& label, const Vec2& pos, const Optional<int32>& width = unspecified, bool enabled = true);

		[[nodiscard]] bool ButtonAt(const String& label, const Vec2& center, const Optional<int32>& width = unspecified, bool enabled = true);

		[[nodiscard]] RectF SliderRegion(const Vec2& pos, double labelWidth = 80.0, double sliderWidth = 120.0);

		[[nodiscard]] RectF SliderRegionAt(const Vec2& center, double labelWidth = 80.0, double sliderWidth = 120.0);

		bool Slider(double& value, const Vec2& pos, double sliderWidth = 120.0, bool enabled = true);

		bool Slider(double& value, double min, double max, const Vec2& pos, double sliderWidth = 120.0, bool enabled = true);

		bool Slider(const String& label, double& value, const Vec2& pos, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		bool Slider(const String& label, double& value, double min, double max, const Vec2& pos, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(double& value, const Vec2& center, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(double& value, double min, double max, const Vec2& center, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(const String& label, double& value, const Vec2& center, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(const String& label, double& value, double min, double max, const Vec2& center, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		[[nodiscard]] RectF VerticalSliderRegion(const Vec2& pos, double sliderHeight = 120.0);

		[[nodiscard]] RectF VerticalSliderRegionAt(const Vec2& center, double sliderHeight = 120.0);

		bool VerticalSlider(double& value, const Vec2& pos, double sliderHeight = 120.0, bool enabled = true);

		bool VerticalSlider(double& value, double min, double max, const Vec2& pos, double sliderHeight = 120.0, bool enabled = true);

		bool VerticalSliderAt(double& value, const Vec2& center, double sliderHeight = 120.0, bool enabled = true);

		bool VerticalSliderAt(double& value, double min, double max, const Vec2& center, double sliderHeight = 120.0, bool enabled = true);

		[[nodiscard]] RectF CheckBoxRegion(const String& label, const Vec2& pos, const Optional<int32>& width = unspecified);

		[[nodiscard]] RectF CheckBoxRegionAt(const String& label, const Vec2& center, const Optional<int32>& width = unspecified);

		bool CheckBox(bool& checked, const String& label, const Vec2& pos, const Optional<int32>& width = unspecified, bool enabled = true);

		bool CheckBoxAt(bool& checked, const String& label, const Vec2& center, const Optional<int32>& width = unspecified, bool enabled = true);
	}
}
