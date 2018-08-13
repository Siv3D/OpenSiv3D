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
# include "Array.hpp"
# include "String.hpp"
# include "Stopwatch.hpp"

namespace s3d
{
	struct TextEditState
	{
		String text;

		size_t cursorPos = 0;

		bool active = false;

		Stopwatch leftPressStopwatch, rightPressStopwatch, cursorStopwatch;

		TextEditState() = default;

		explicit TextEditState(const String& defaultText)
			: text(defaultText)
			, cursorPos(defaultText.size()) {}
	};

	namespace SimpleGUI
	{
		[[nodiscard]] RectF ButtonRegion(const String& label, const Vec2& pos, const Optional<double>& width = unspecified);

		[[nodiscard]] RectF ButtonRegionAt(const String& label, const Vec2& center, const Optional<double>& width = unspecified);

		[[nodiscard]] bool Button(const String& label, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]] bool ButtonAt(const String& label, const Vec2& center, const Optional<double>& width = unspecified, bool enabled = true);

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

		[[nodiscard]] RectF CheckBoxRegion(const String& label, const Vec2& pos, const Optional<double>& width = unspecified);

		[[nodiscard]] RectF CheckBoxRegionAt(const String& label, const Vec2& center, const Optional<double>& width = unspecified);

		bool CheckBox(bool& checked, const String& label, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		bool CheckBoxAt(bool& checked, const String& label, const Vec2& center, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]] RectF RadioButtonsRegion(const Array<String>& options, const Vec2& pos, const Optional<double>& width = unspecified);

		[[nodiscard]] RectF RadioButtonsRegionAt(const Array<String>& options, const Vec2& center, const Optional<double>& width = unspecified);

		bool RadioButtons(size_t& index, const Array<String>& options, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		bool RadioButtonsAt(size_t& index, const Array<String>& options, const Vec2& center, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]] RectF TextBoxRegion(const Vec2& pos, double width = 200.0);

		[[nodiscard]] RectF TextBoxRegionAt(const Vec2& center, double width = 200.0);

		bool TextBox(TextEditState& text, const Vec2& pos, double width = 200.0, const Optional<size_t>& maxChars = unspecified, bool enabled = true);

		bool TextBoxAt(TextEditState& text, const Vec2& center, double width = 200.0, const Optional<size_t>& maxChars = unspecified, bool enabled = true);
	}
}
