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

# include <Siv3D/SimpleGUI.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/CursorStyle.hpp>
# include <Siv3D/TexturedCircle.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/TextInput.hpp>
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Indexed.hpp>
# include <Siv3D/Clipboard.hpp>
# include <Siv3D/ScopedCustomShader2D.hpp>
# include <Siv3D/GUI/IGUI.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline const Font& GetSimpleGUIFont() noexcept
		{
			return SIV3D_ENGINE(GUI)->getDefaultFont();
		}
	}

	namespace SimpleGUI
	{
		constexpr int32 CellSize = 40;
		constexpr int32 UnitSize = 36;
		constexpr ColorF BackgroundColor{ 1.0 };
		constexpr ColorF DisabledBackgroundColor{ 0.92 };
		constexpr ColorF ButtonMouseOverColor{ 0.9, 0.95, 1.0 };
		constexpr ColorF ActiveTextColor{ 0.11 };
		constexpr ColorF DisabledTextColor{ 0.67 };
		constexpr ColorF FrameColor{ 0.67 };
		constexpr ColorF SliderBaseColor{ 0.33 };
		constexpr ColorF SliderFillColor{ 0.35, 0.7, 1.0 };
		constexpr ColorF SliderDisabledBaseColor{ 0.75 };
		constexpr ColorF SliderDisabledFillColor{ 0.75, 0.85, 1.0 };
		constexpr ColorF CheckBoxFillColor{ SliderFillColor };
		constexpr ColorF CheckBoxHighlightedFillColor{ 0.45, 0.8, 1.0 };
		constexpr ColorF CheckBoxBaseColor{ 0.67 };
		constexpr ColorF CheckBoxDisabledBaseColor{ SliderDisabledBaseColor };
		constexpr ColorF CheckBoxDisabledFillColor{ SliderDisabledFillColor };
		constexpr ColorF CheckBoxMouseOverColor{ ButtonMouseOverColor };
		constexpr ColorF RadioButtonFillColor{ SliderFillColor };
		constexpr ColorF RadioButtonBaseColor{ 0.5 };
		constexpr ColorF RadioButtonDisabledBaseColor{ 0.75 };
		constexpr int32 FontYOffset = -1;
		constexpr double RoundSize = 4.8;
		constexpr double SliderBarRoundSize = 2.0;
		constexpr double SliderMinLength = 40.0;
		constexpr int32 CheckBoxSize	= 24;
		constexpr int32 CheckBoxPadding	= 8;
		constexpr int32 RadioButtonSize		= 19;
		constexpr int32 RadioButtonPadding	= 8;
		constexpr int32 TextBoxHeight		= 36;
		constexpr Size ColorPickerSize{ 160, 116 };

		[[nodiscard]]
		inline constexpr ColorF GetTextColor(bool enabled) noexcept
		{
			return (enabled ? ActiveTextColor : DisabledTextColor);
		}

		static void DrawCheck(const Vec2& center)
		{
			Quad{ 2.5, 13.5, 6, 11, 9.5, 14.5, 9.5, 20.5 }.movedBy(-12, -12).movedBy(center).draw();
			Quad{ 9.5, 20.5, 9.5, 14.5, 17.75, 3.75, 20.5, 6.5 }.movedBy(-12, -12).movedBy(center).draw();
		}

		RectF HeadlineRegion(const String& text, const Vec2& pos, const Optional<double>& _width)
		{
			const Font& font = detail::GetSimpleGUIFont();
			const double width = _width.value_or_eval([&](){ return Math::Ceil(font(text).region().w + 20); });
			return{ pos, width, CellSize };
		}

		void Headline(const String& text, const Vec2& pos, const Optional<double>& _width, const bool enabled)
		{
			const Font& font = detail::GetSimpleGUIFont();
			const RectF region = HeadlineRegion(text, pos, _width);
			region.draw(BackgroundColor);

			const auto dtext = font(text);
			const double labelWidth = Math::Ceil(dtext.region().w);
			const Vec2 labelPos{ (region.x + (region.w - labelWidth) / 2.0), (region.center().y - font.height() / 2.0 + FontYOffset) };
			dtext.draw(labelPos, GetTextColor(enabled));
		}

		RectF ButtonRegion(const String& label, const Vec2& pos, const Optional<double>& _width)
		{
			const Font& font = detail::GetSimpleGUIFont();
			const double width = _width.value_or_eval([&](){ return Math::Ceil(font(label).region().w + 40); });
			return{ pos, width, UnitSize };
		}

		RectF ButtonRegionAt(const String& label, const Vec2& center, const Optional<double>& _width)
		{
			const Font& font = detail::GetSimpleGUIFont();
			const double width = _width.value_or_eval([&](){ return Math::Ceil(font(label).region().w + 40); });
			return{ Arg::center = center, width, UnitSize };
		}

		bool Button(const String& label, const Vec2& pos, const Optional<double>& _width, const bool enabled)
		{
			const Vec2 center = ButtonRegion(label, pos, _width).center();
			return ButtonAt(label, center, _width, enabled);
		}

		bool ButtonAt(const String& label, const Vec2& center, const Optional<double>& _width, const bool enabled)
		{
			const Font& font = detail::GetSimpleGUIFont();
			const auto dtext = font(label);

			const double labelWidth = Math::Ceil(dtext.region().w);
			const double width = _width.value_or_eval([&](){ return (labelWidth + 40); });

			const RectF rect{ Arg::center = center, width, UnitSize };
			const Vec2 labelPos{ (rect.x + (width - labelWidth) / 2.0), (center.y - font.height() / 2.0 + FontYOffset) };

			const bool mouseOver = (enabled && rect.mouseOver());
			const bool pushed = (mouseOver && Cursor::OnClientRect() && MouseL.down());
			const RoundRect rrect = rect.rounded(RoundSize);

			if (enabled)
			{
				rrect.draw(mouseOver ? ButtonMouseOverColor : BackgroundColor);
			}
			else
			{
				rrect.draw(DisabledBackgroundColor);
			}

			if (not pushed)
			{
				rrect.drawFrame(1, 0, FrameColor);
			}

			dtext.draw(labelPos, GetTextColor(enabled));

			if (mouseOver)
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			return pushed;
		}

		RectF SliderRegion(const Vec2& pos, double labelWidth, double sliderWidth)
		{
			labelWidth	= Max(labelWidth, 0.0);
			sliderWidth	= Max(sliderWidth, SliderMinLength);
			const double width = (labelWidth + sliderWidth);
			return{ pos, width, UnitSize };
		}

		RectF SliderRegionAt(const Vec2& center, double labelWidth, double sliderWidth)
		{
			labelWidth	= Max(labelWidth, 0.0);
			sliderWidth	= Max(sliderWidth, SliderMinLength);
			const double width = (labelWidth + sliderWidth);
			return{ Arg::center = center, width, UnitSize };
		}

		bool Slider(double& value, const Vec2& pos, const double sliderWidth, const bool enabled)
		{
			return Slider(String{}, value, 0.0, 1.0, pos, 0.0, sliderWidth, enabled);
		}

		bool Slider(double& value, const double min, const double max, const Vec2& pos, const double sliderWidth, const bool enabled)
		{
			return Slider(String{}, value, min, max, pos, 0.0, sliderWidth, enabled);
		}

		bool Slider(const String& label, double& value, const Vec2& pos, const double labelWidth, const double sliderWidth, const bool enabled)
		{
			return Slider(label, value, 0.0, 1.0, pos, labelWidth, sliderWidth, enabled);
		}

		bool Slider(const String& label, double& value, const double min, const double max, const Vec2& pos, const double labelWidth, const double sliderWidth, const bool enabled)
		{
			const Vec2 center = SliderRegion(pos, labelWidth, sliderWidth).center();
			return SliderAt(label, value, min, max, center, labelWidth, sliderWidth, enabled);
		}

		bool SliderAt(double& value, const Vec2& center, const double sliderWidth, const bool enabled)
		{
			return SliderAt(String{}, value, 0.0, 1.0, center, 0.0, sliderWidth, enabled);
		}

		bool SliderAt(double& value, const double min, const double max, const Vec2& center, const double sliderWidth, const bool enabled)
		{
			return SliderAt(String{}, value, min, max, center, 0.0, sliderWidth, enabled);
		}

		bool SliderAt(const String& label, double& value, const Vec2& center, const double labelWidth, const double sliderWidth, const bool enabled)
		{
			return SliderAt(label, value, 0.0, 1.0, center, labelWidth, sliderWidth, enabled);
		}

		bool SliderAt(const String& label, double& value, double min, double max, const Vec2& center, const double _labelWidth, const double _sliderWidth, const bool enabled)
		{
			const Font& font = detail::GetSimpleGUIFont();

			const double labelWidth		= Max(_labelWidth, 0.0);
			const double sliderWidth	= Max(_sliderWidth, SliderMinLength);
			const double width			= (labelWidth + sliderWidth);
			const RectF region{ Arg::center = center, width, UnitSize };
			const Vec2 labelPos{ (region.x + 8), (center.y - font.height() / 2.0 + FontYOffset) };

			const double sliderRegionX0	= (region.x + labelWidth + 8);
			const double sliderRegionX1	= (region.x + region.w - 8);
			const double sliderRegionW	= (sliderRegionX1 - sliderRegionX0);

			const double actualSliderRegionX0	= (sliderRegionX0 + 8);
			const double actualSliderRegionX1	= (sliderRegionX1 - 8);
			const double actualSliderRegionW	= (actualSliderRegionX1 - actualSliderRegionX0);

			const RectF sliderRect{ Arg::leftCenter(sliderRegionX0, center.y), sliderRegionW, 6 };
			const RoundRect baseRoundRect = sliderRect.rounded(SliderBarRoundSize);

			const double previousValue = value;
			const auto [min_, max_] = std::minmax(min, max);
			value = Clamp(value, min_, max_);

			const double fill = ((value - min) / (max - min));
			const RectF fillRect{ sliderRect.pos, sliderRect.w * fill, sliderRect.h };
			const RoundRect fillRoundRect = fillRect.rounded(SliderBarRoundSize);

			const RectF smallRect{ Arg::center(actualSliderRegionX0 + actualSliderRegionW * fill, center.y), 16, 24 };
			const RoundRect smallRoundRect = smallRect.rounded(4.2);
			const bool mouseOver = (enabled && smallRect.mouseOver());

			region.draw(BackgroundColor);

			if (enabled)
			{
				baseRoundRect.draw(SliderBaseColor);
				fillRoundRect.draw(SliderFillColor);
				smallRoundRect
					.draw(mouseOver ? ButtonMouseOverColor : BackgroundColor)
					.drawFrame(1, ColorF{ 0.33 });
			}
			else
			{
				baseRoundRect.draw(SliderDisabledBaseColor);
				fillRoundRect.draw(SliderDisabledFillColor);
				smallRoundRect
					.draw(DisabledBackgroundColor)
					.drawFrame(1, ColorF{ 0.67 });
			}

			font(label).draw(labelPos, GetTextColor(enabled));

			const RectF sliderRectExtended = sliderRect.stretched(4, 12);

			if (enabled && Cursor::OnClientRect() && (sliderRectExtended.mouseOver() || smallRect.mouseOver()))
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			if (enabled && Cursor::OnClientRect() && sliderRectExtended.leftPressed())
			{
				const double pos = (Cursor::PosF().x - actualSliderRegionX0);
				const double posN = Math::Saturate(pos / actualSliderRegionW);
				value = (min + posN * (max - min));
			}

			return (value != previousValue);
		}

		RectF VerticalSliderRegion(const Vec2& pos, double sliderHeight)
		{
			sliderHeight = Max(sliderHeight, SliderMinLength);
			return{ pos, UnitSize, sliderHeight };
		}

		RectF VerticalSliderRegionAt(const Vec2& center, double sliderHeight)
		{
			sliderHeight = Max(sliderHeight, SliderMinLength);
			return{ Arg::center = center, UnitSize, sliderHeight };
		}

		bool VerticalSlider(double& value, const Vec2& pos, const double sliderHeight, const bool enabled)
		{
			return VerticalSlider(value, 0.0, 1.0, pos, sliderHeight, enabled);
		}

		bool VerticalSlider(double& value, const double min, const double max, const Vec2& pos, const double sliderHeight, const bool enabled)
		{
			const Vec2 center = VerticalSliderRegion(pos, sliderHeight).center();
			return VerticalSliderAt(value, min, max, center, sliderHeight, enabled);
		}

		bool VerticalSliderAt(double& value, const Vec2& center, const double sliderHeight, const bool enabled)
		{
			return VerticalSliderAt(value, 0.0, 1.0, center, sliderHeight, enabled);
		}

		bool VerticalSliderAt(double& value, double min, double max, const Vec2& center, const double _sliderHeight, const bool enabled)
		{
			const double sliderWidth = Max(_sliderHeight, SliderMinLength);
			const double height = sliderWidth;
			const RectF region{ Arg::center = center, 36, height };

			const double sliderRegionY0	= (region.y + 8);
			const double sliderRegionY1	= (region.y + region.h - 8);
			const double sliderRegionH	= (sliderRegionY1 - sliderRegionY0);

			const double actualSliderRegionY0	= (sliderRegionY0 + 8);
			const double actualSliderRegionY1	= (sliderRegionY1 - 8);
			const double actualSliderRegionH	= (actualSliderRegionY1 - actualSliderRegionY0);

			const RectF sliderRect{ Arg::topCenter(center.x, sliderRegionY0), 6, sliderRegionH };
			const RoundRect baseRoundRect = sliderRect.rounded(2);

			const double previousValue = value;
			const auto [min_, max_] = std::minmax(min, max);
			value = Clamp(value, min_, max_);

			const double fill = ((value - min) / (max - min));
			const RectF fillRect{ Arg::bottomLeft = sliderRect.bl(), sliderRect.w, (sliderRect.h * fill) };
			const RoundRect fillRoundRect = fillRect.rounded(2);

			const RectF smallRect{ Arg::center(center.x, actualSliderRegionY1 - actualSliderRegionH * fill), 24, 16 };
			const RoundRect smallRoundRect = smallRect.rounded(4.2);
			const bool mouseOver = (enabled && smallRect.mouseOver());

			region.draw(BackgroundColor);

			if (enabled)
			{
				baseRoundRect.draw(SliderBaseColor);
				fillRoundRect.draw(SliderFillColor);
				smallRoundRect
					.draw(mouseOver ? ButtonMouseOverColor : BackgroundColor)
					.drawFrame(1, ColorF(0.33));
			}
			else
			{
				baseRoundRect.draw(SliderDisabledBaseColor);
				fillRoundRect.draw(SliderDisabledFillColor);
				smallRoundRect
					.draw(DisabledBackgroundColor)
					.drawFrame(1, ColorF(0.67));
			}

			const RectF sliderRectExtended = sliderRect.stretched(12, 4);

			if (enabled && Cursor::OnClientRect() && (sliderRectExtended.mouseOver() || smallRect.mouseOver()))
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			if (enabled && Cursor::OnClientRect() && sliderRectExtended.leftPressed())
			{
				const double pos	= (actualSliderRegionY1 - Cursor::PosF().y);
				const double posN	= Math::Saturate(pos / actualSliderRegionH);
				value = (min + posN * (max - min));
			}

			return (value != previousValue);
		}

		RectF CheckBoxRegion(const String& label, const Vec2& pos, const Optional<double>& _width)
		{
			const Font& font = detail::GetSimpleGUIFont();
			const double width = _width.value_or_eval([&](){ return Math::Ceil(CheckBoxPadding * 3 + CheckBoxSize + font(label).region().w); });
			return{ pos, width, UnitSize };
		}

		RectF CheckBoxRegionAt(const String& label, const Vec2& center, const Optional<double>& _width)
		{
			const Font& font = detail::GetSimpleGUIFont();
			const double width = _width.value_or_eval([&](){ return Math::Ceil(CheckBoxPadding * 3 + CheckBoxSize + font(label).region().w); });
			return{ Arg::center = center, width, UnitSize };
		}

		bool CheckBox(bool& checked, const String& label, const Vec2& pos, const Optional<double>& _width, const bool enabled)
		{
			const Vec2 center = CheckBoxRegion(label, pos, _width).center();
			return CheckBoxAt(checked, label, center, _width, enabled);
		}

		bool CheckBoxAt(bool& checked, const String& label, const Vec2& center, const Optional<double>& _width, const bool enabled)
		{
			const Font& font = detail::GetSimpleGUIFont();
			const DrawableText dtext = font(label);

			const double width = _width.value_or_eval([&](){ return Math::Ceil(CheckBoxPadding * 3 + CheckBoxSize + dtext.region().w); });
			const RectF region{ Arg::center = center, width, UnitSize };
			const RectF checkBox{ Arg::leftCenter(region.x + 8, center.y), CheckBoxSize };
			const RoundRect roundCheckBox = checkBox.rounded(3.2);
			const Vec2 labelPos{ (region.x + CheckBoxPadding * 2 + CheckBoxSize), (center.y - font.height() / 2.0 + FontYOffset) };
			const bool mouseOver = (enabled && checkBox.mouseOver());

			region.draw(BackgroundColor);

			if (checked)
			{
				if (enabled)
				{
					roundCheckBox.draw(mouseOver ? CheckBoxHighlightedFillColor : CheckBoxFillColor);
				}
				else
				{
					roundCheckBox.draw(CheckBoxDisabledFillColor);
				}

				DrawCheck(checkBox.center());
			}
			else
			{
				const RoundRect innerRoundRect = checkBox.stretched(-1.25).rounded(3.2);

				if (enabled)
				{
					roundCheckBox.draw(CheckBoxBaseColor);
					innerRoundRect.draw(mouseOver ? CheckBoxMouseOverColor : ColorF{ 0.95 });
				}
				else
				{
					roundCheckBox.draw(CheckBoxDisabledBaseColor);
					innerRoundRect.draw(ColorF{ 0.8 });
				}
			}

			dtext.draw(labelPos, GetTextColor(enabled));

			if (enabled && Cursor::OnClientRect() && checkBox.mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			const bool previousValue = checked;

			if (enabled && Cursor::OnClientRect() && checkBox.leftClicked())
			{
				checked = !checked;
			}

			return (checked != previousValue);
		}

		RectF RadioButtonsRegion(const Array<String>& options, const Vec2& pos, const Optional<double>& _width)
		{
			const Font& font = detail::GetSimpleGUIFont();
			double width = 0.0;

			if (_width)
			{
				width = *_width;
			}
			else
			{
				for (const auto& option : options)
				{
					width = Max<double>(width, RadioButtonPadding * 3 + RadioButtonSize + font(option).region().w);
				}

				width = Math::Ceil(width);
			}

			return{ pos, width, Max<double>(0.0, static_cast<double>(options.size() * CellSize - (CellSize - UnitSize))) };
		}

		RectF RadioButtonsRegionAt(const Array<String>& options, const Vec2& center, const Optional<double>& _width)
		{
			const Font& font = detail::GetSimpleGUIFont();
			double width = 0.0;

			if (_width)
			{
				width = *_width;
			}
			else
			{
				for (const auto& option : options)
				{
					width = Max<double>(width, RadioButtonPadding * 3 + RadioButtonSize + font(option).region().w);
				}

				width = Math::Ceil(width);
			}

			return{ Arg::center = center, width, Max<double>(0.0, static_cast<double>(options.size() * CellSize - (CellSize - UnitSize))) };
		}

		bool RadioButtons(size_t& index, const Array<String>& options, const Vec2& pos, const Optional<double>& _width, const bool enabled)
		{
			const Vec2 center = RadioButtonsRegion(options, pos, _width).center();
			return RadioButtonsAt(index, options, center, _width, enabled);
		}

		bool RadioButtonsAt(size_t& index, const Array<String>& options, const Vec2& center, const Optional<double>& _width, bool enabled)
		{
			const Font& font = detail::GetSimpleGUIFont();
			const RectF region = RadioButtonsRegionAt(options, center, _width);
			const bool onClient = Cursor::OnClientRect();

			bool hasChanged = false;
			const int32 labelPosX = static_cast<int32>(region.x + RadioButtonPadding * 2 + RadioButtonSize);
			const double baseY = (center.y - (options.size() * CellSize - (CellSize - UnitSize)) / 2.0 + 18);

			region.draw(BackgroundColor);
			{
				const ColorF checkedCircleColor = (enabled ? RadioButtonFillColor : RadioButtonDisabledBaseColor);
				const ColorF uncheckedCircleColor = (enabled ? RadioButtonBaseColor : RadioButtonDisabledBaseColor);

				for (size_t row = 0; row < options.size(); ++row)
				{
					const RectF radioButtonBox{ Arg::leftCenter(region.x + RadioButtonPadding, baseY + row * CellSize), RadioButtonSize };
					const Circle radioButton{ radioButtonBox.center(), RadioButtonSize / 2.0 };
					const bool mouseOver = (enabled && radioButtonBox.mouseOver());
					const bool checked = (index == row);

					if (checked)
					{
						radioButton.drawFrame(2, 0.5, checkedCircleColor);
						radioButton.stretched(-5).draw(checkedCircleColor);
					}
					else
					{
						radioButton.drawFrame(2, 0.5, uncheckedCircleColor);
					}

					if (mouseOver && onClient)
					{
						Cursor::RequestStyle(CursorStyle::Hand);
					}

					if (enabled && onClient && radioButtonBox.leftClicked())
					{
						if (index != row)
						{
							index = row;
							hasChanged = true;
						}
					}
				}
			}

			{
				const int32 fontHeight = font.height();
				const ColorF textColor = GetTextColor(enabled);
				size_t row = 0;

				for (const auto& option : options)
				{
					const RectF radioButtonBox{ Arg::leftCenter(region.x + RadioButtonPadding, baseY + row * CellSize), RadioButtonSize };
					const Circle radioButton{ radioButtonBox.center(), RadioButtonSize / 2.0 };
					const Vec2 labelPos{ labelPosX, (radioButton.y - fontHeight / 2.0 + FontYOffset - 0.5) };

					font(option).draw(labelPos, textColor);
					++row;
				}
			}

			return hasChanged;
		}

		RectF HorizontalRadioButtonsRegion(const Array<String>& options, const Vec2& pos, const Optional<double>& _itemWidth)
		{
			const Font& font = detail::GetSimpleGUIFont();

			double itemWidth = 0.0;
			{
				if (_itemWidth)
				{
					itemWidth = *_itemWidth;
				}
				else
				{
					for (const auto& option : options)
					{
						itemWidth = Max<double>(itemWidth, RadioButtonPadding * 3 + RadioButtonSize + font(option).region().w);
					}

					itemWidth = Math::Ceil(itemWidth);
				}
			}

			const double width = (itemWidth * options.size());
			return{ pos, width, UnitSize };
		}

		RectF HorizontalRadioButtonsRegionAt(const Array<String>& options, const Vec2& center, const Optional<double>& _itemWidth)
		{
			const Font& font = detail::GetSimpleGUIFont();

			double itemWidth = 0.0;
			{
				if (_itemWidth)
				{
					itemWidth = *_itemWidth;
				}
				else
				{
					for (const auto& option : options)
					{
						itemWidth = Max<double>(itemWidth, RadioButtonPadding * 3 + RadioButtonSize + font(option).region().w);
					}

					itemWidth = Math::Ceil(itemWidth);
				}
			}

			const double width = (itemWidth * options.size());
			return{ Arg::center = center, width, UnitSize };
		}

		bool HorizontalRadioButtons(size_t& index, const Array<String>& options, const Vec2& pos, const Optional<double>& _itemWidth, const bool enabled)
		{
			const Vec2 center = HorizontalRadioButtonsRegion(options, pos, _itemWidth).center();
			return HorizontalRadioButtonsAt(index, options, center, _itemWidth, enabled);
		}

		bool HorizontalRadioButtonsAt(size_t& index, const Array<String>& options, const Vec2& center, const Optional<double>& _itemWidth, bool enabled)
		{
			const Font& font = detail::GetSimpleGUIFont();

			double itemWidth = 0.0;
			{
				if (_itemWidth)
				{
					itemWidth = *_itemWidth;
				}
				else
				{
					for (const auto& option : options)
					{
						itemWidth = Max<double>(itemWidth, RadioButtonPadding * 3 + RadioButtonSize + font(option).region().w);
					}

					itemWidth = Math::Ceil(itemWidth);
				}
			}

			const double width = (itemWidth * options.size());
			const RectF region{ Arg::center = center, width, UnitSize };
			const bool onClient = Cursor::OnClientRect();

			bool hasChanged = false;
			const double baseY = (center.y - UnitSize / 2 + 18);
			const int32 fontHeight = font.height();

			region.draw(BackgroundColor);
			{
				const ColorF checkedCircleColor = (enabled ? RadioButtonFillColor : RadioButtonDisabledBaseColor);
				const ColorF uncheckedCircleColor = (enabled ? RadioButtonBaseColor : RadioButtonDisabledBaseColor);

				for (size_t itemIndex = 0; itemIndex < options.size(); ++itemIndex)
				{
					const double posX = (region.x + itemWidth * itemIndex);
					const RectF radioButtonBox{ Arg::leftCenter(posX + RadioButtonPadding, baseY), RadioButtonSize };
					const Circle radioButton{ radioButtonBox.center(), (RadioButtonSize / 2.0) };
					const Vec2 labelPos{ (posX + RadioButtonPadding * 2 + RadioButtonSize), (radioButton.y - fontHeight / 2.0 + FontYOffset - 0.5) };
					const bool mouseOver = (enabled && radioButtonBox.mouseOver());
					const bool checked = (index == itemIndex);

					if (checked)
					{
						radioButton.drawFrame(2, 0.5, checkedCircleColor);
						radioButton.stretched(-5).draw(checkedCircleColor);
					}
					else
					{
						radioButton.drawFrame(2, 0.5, uncheckedCircleColor);
					}

					if (mouseOver && onClient)
					{
						Cursor::RequestStyle(CursorStyle::Hand);
					}

					if (enabled && onClient && radioButtonBox.leftClicked())
					{
						if (index != itemIndex)
						{
							index = itemIndex;
							hasChanged = true;
						}
					}
				}
			}

			{
				const ColorF textColor = GetTextColor(enabled);
				size_t itemIndex = 0;

				for (const auto& option : options)
				{
					const double posX = (region.x + itemWidth * itemIndex);
					const RectF radioButtonBox{ Arg::leftCenter(posX + RadioButtonPadding, baseY), RadioButtonSize };
					const Circle radioButton{ radioButtonBox.center(), (RadioButtonSize / 2.0) };
					const Vec2 labelPos{ (posX + RadioButtonPadding * 2 + RadioButtonSize), (radioButton.y - fontHeight / 2.0 + FontYOffset - 0.5) };

					font(option).draw(labelPos, textColor);
					++itemIndex;
				}
			}

			return hasChanged;
		}

		RectF TextBoxRegion(const Vec2& pos, double width)
		{
			width = Max(width, 40.0);

			return{ pos, width, TextBoxHeight };
		}

		RectF TextBoxRegionAt(const Vec2& center, double width)
		{
			width = Max(width, 40.0);

			return{ Arg::center = center, width, TextBoxHeight };
		}

		bool TextBox(TextEditState& text, const Vec2& pos, double width, const Optional<size_t>& maxChars, const bool enabled)
		{
			width = Max(width, 40.0);

			return TextBoxAt(text, pos + Vec2{ width * 0.5, 18.0 }, width, maxChars, enabled);
		}

		bool TextBoxAt(TextEditState& text, const Vec2& center, const double _width, const Optional<size_t>& maxChars, const bool enabled)
		{
			const Font& font = detail::GetSimpleGUIFont();
			const double width = Max(_width, 40.0);
			const RectF region{ Arg::center = center, width, TextBoxHeight };
			const Vec2 textPos{ (region.x + 8), (center.y - font.height() / 2 + FontYOffset - 0.5) };
			const ColorF textColor = GetTextColor(enabled);

			text.cursorPos = Min(text.cursorPos, text.text.size());

			if (enabled)
			{
				if (text.active)
				{
					region
						.draw()
						.drawFrame(0.0, 1.5, ColorF(0.35, 0.7, 1.0, 0.75))
						.drawFrame(2.5, 0.0, ColorF(0.35, 0.7, 1.0));
				}
				else
				{
					region
						.draw()
						.drawFrame(2.0, 0.0, ColorF(0.5));
				}

				if (text.active)
				{
					const String textHeader = text.text.substr(0, text.cursorPos);
					const String textTail = text.text.substr(text.cursorPos, String::npos);
					const String editingText = TextInput::GetEditingText();

				# if SIV3D_PLATFORM(WINDOWS)

					const auto[editingCursorIndex, editingTargetlength] = Platform::Windows::TextInput::GetCursorIndex();
					const bool hasEditingTarget = (editingTargetlength > 0);

				# else

					const int32 editingCursorIndex = -1, editingTargetlength = 0;
					const bool hasEditingTarget = false;

				# endif

					const double fontHeight = font.height();
					Vec2 pos = textPos;
					double cursorPosX = 0.0;

					{
						double begX = 0.0, begY = 0.0, endX = 0.0;
						{
							ScopedCustomShader2D shader{ Font::GetPixelShader(font.method()) };

							for (auto glyph : font.getGlyphs(textHeader))
							{
								glyph.texture.draw(pos + glyph.getOffset(), textColor);
								pos.x += glyph.xAdvance;
							}

							begX = pos.x;
							begY = 0;
							endX = pos.x;

							for (auto&& [i, glyph] : Indexed(font.getGlyphs(editingText)))
							{
								const int32 currentCharIndex = static_cast<int32>(i);

								if (currentCharIndex == editingCursorIndex)
								{
									begX = pos.x;
									begY = pos.y + fontHeight;
								}
								else if (hasEditingTarget && (currentCharIndex == (editingCursorIndex + editingTargetlength - 1)))
								{
									endX = pos.x + glyph.xAdvance;
								}

								glyph.texture.draw(pos + glyph.getOffset(), textColor);
								pos.x += glyph.xAdvance;
							}

							cursorPosX = pos.x;

							for (auto glyph : font.getGlyphs(textTail))
							{
								glyph.texture.draw(pos + glyph.getOffset(), textColor);
								pos.x += glyph.xAdvance;
							}
						}

						if (hasEditingTarget)
						{
							Line(begX, begY, endX, begY).movedBy(0, -2).draw(2, textColor);
						}
					}

					const bool showCursor = (text.cursorStopwatch.ms() % 1200 < 600)
						|| (text.leftPressStopwatch.isRunning() && text.leftPressStopwatch < SecondsF(0.5))
						|| (text.rightPressStopwatch.isRunning() && text.rightPressStopwatch < SecondsF(0.5));

					if (showCursor)
					{
						const RectF cursor(Arg::leftCenter(Vec2(cursorPosX, center.y).asPoint()), 1, 26);
						cursor.draw(textColor);
					}
				}
				else
				{
					font(text.text).draw(textPos, textColor);
				}
			}
			else
			{
				region
					.draw(ColorF(0.9))
					.drawFrame(2.0, 0.0, ColorF(0.67));

				font(text.text).draw(textPos, textColor);
			}

			if (enabled && Cursor::OnClientRect() && region.mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::IBeam);
			}

			if (MouseL.down())
			{
				if (enabled && Cursor::OnClientRect() && region.mouseOver())
				{
					text.active = true;
					const double posX = Cursor::PosF().x - (region.x + 8);

					size_t index = 0;
					double pos = 0.0;

					for (const auto& advance : font(text.text).getXAdvances())
					{
						if (posX <= (pos + (advance / 2)))
						{
							break;
						}

						pos += advance;
						++index;
					}

					text.cursorPos = index;
					text.cursorStopwatch.restart();
					text.leftPressStopwatch.reset();
					text.rightPressStopwatch.reset();

				# if SIV3D_PLATFORM(WEB)
					Platform::Web::TextInput::RequestEnableIME();		
				# endif
				}
				else
				{
					text.active = false;

				# if SIV3D_PLATFORM(WEB)
					Platform::Web::TextInput::RequestDisableIME();		
				# endif
				}
			}

			const String previousText = text.text;

			if (text.active)
			{
				text.cursorPos = TextInput::UpdateText(text.text, text.cursorPos, TextInputMode::AllowBackSpaceDelete);

				if (TextInput::GetEditingText().isEmpty()
					&&
				# if SIV3D_PLATFORM(MACOS)

					((KeyCommand + KeyV).down() || (KeyControl + KeyV).down())

				# else

					(KeyControl + KeyV).down()

				# endif
					)
				{

				# if SIV3D_PLATFORM(WEB)

					if (!text.pendingClipboardText.valid())
					{
						text.pendingClipboardText = Platform::Web::Clipboard::GetText();
					}

				# else

					if (String paste; Clipboard::GetText(paste))
					{
						text.text.insert(text.cursorPos, paste);
						text.cursorPos += paste.size();
					}

				# endif

				}

			# if SIV3D_PLATFORM(WEB)

				if (text.pendingClipboardText.valid() && text.pendingClipboardText.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
				{
					String paste = text.pendingClipboardText.get();

					text.text.insert(text.cursorPos, paste);
					text.cursorPos += paste.size();
				}

			# endif

				if (maxChars && (text.text.size() > *maxChars))
				{
					text.text.resize(*maxChars);
					text.cursorPos = Min(text.cursorPos, *maxChars);
				}

				if (text.text != previousText)
				{
					text.cursorStopwatch.restart();
				}

				if (const String raw = TextInput::GetRawInput(); raw.includes(U'\r') || raw.includes(U'\t'))
				{
					text.active = false;

				# if SIV3D_PLATFORM(WEB)					
					Platform::Web::TextInput::RequestDisableIME();					
				# endif
				}

				if ((0 < text.cursorPos) && (KeyLeft.down() || (KeyLeft.pressedDuration() > SecondsF(0.33) && text.leftPressStopwatch > SecondsF(0.06))))
				{
					--text.cursorPos;
					text.leftPressStopwatch.restart();
				}

				if ((text.cursorPos < text.text.size()) && (KeyRight.down() || (KeyRight.pressedDuration() > SecondsF(0.33) && text.rightPressStopwatch > SecondsF(0.06))))
				{
					++text.cursorPos;
					text.rightPressStopwatch.restart();
				}
			}

			return (text.text != previousText);
		}

		RectF ColorPickerRegion(const Vec2& pos)
		{
			return{ pos, ColorPickerSize };
		}

		RectF ColorPickerRegionAt(const Vec2& center)
		{
			return{ Arg::center = center, ColorPickerSize };
		}

		bool ColorPicker(HSV& hsv, const Vec2& pos, const bool enabled)
		{
			const Vec2 center = ColorPickerRegion(pos).center();
			return ColorPickerAt(hsv, center, enabled);
		}

		bool ColorPickerAt(HSV& hsv, const Vec2& center, const bool enabled)
		{
			const HSV previousHSV = hsv;

			const RectF region = ColorPickerRegionAt(center);
			constexpr int32 circleSize = (ColorPickerSize.y - 18);
			const Vec2 circleCenter = center.movedBy(-26 + 4, 0);
			const Circle circle{ circleCenter, (circleSize / 2) };
			const Circle touchCircle = circle.stretched((116 - circleSize) / 2);
			const RectF touchRect{ Arg::center = circleCenter, (circleSize + 8) };
			const bool mouseLPressed = MouseL.pressed();
			const bool onCircle = (touchRect.mouseOver() || touchCircle.mouseOver());
			const bool onCircleUpdate = (enabled && onCircle && mouseLPressed);

			if (onCircleUpdate)
			{
				const Vec2 pos = Cursor::PosF();
				const Vec2 dir = (pos - circleCenter);
				const Circular cir{ dir };
				const double h = Math::Fmod(Math::ToDegrees(cir.theta) + 360.0, 360.0);
				const double s = Min((Min(cir.r, circleSize / 2.0) / ((circleSize - 1) / 2.0)), 1.0);
				hsv.h = h;
				hsv.s = s;
			}

			const RectF valueBox{ Arg::center = center.movedBy(56, 0), 24, 96 };
			const Vec2 valueBoxBase = valueBox.pos;
			const RectF touchValueBox = valueBox.stretched(8, 8, 8, 4);
			const bool onValueBox = touchValueBox.mouseOver();
			const bool onValueBoxUpdate = (enabled && onValueBox && mouseLPressed);

			if (onValueBoxUpdate)
			{
				const Vec2 pos = Cursor::PosF();
				const double y = (pos.y - valueBox.y);
				const double v = Math::Saturate(1.0 - (y / (valueBox.h - 1)));
				hsv.v = v;
			}

			if (enabled && (onCircle || onValueBox))
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			// Background
			{
				region.draw(BackgroundColor);
				RectF{ Arg::center = center, 148, 104 }.rounded(2.2).draw(ColorF(enabled ? 0.66 : 0.75));
			}

			// HS Circle
			{
				circle(SIV3D_ENGINE(GUI)->getColorPickerTexture()).draw();

				if (not enabled)
				{
					circle.stretched(1).draw(ColorF{ 1.0, 0.5 });
				}

				const double r = (hsv.s * ((circleSize - 1) / 2.0));
				const double theta = Math::ToRadians(hsv.h);
				const Vec2 dir = Circular{ r, theta }.fastToVec2();
				const ColorF color = HSV{ hsv.h, hsv.s, 1.0 };
				const Circle smallCircle{ circleCenter + dir, 5 };

				if (enabled)
				{
					smallCircle
						.draw(color)
						.stretched(onCircleUpdate ? 1 : 0)
						.drawFrame(2, HSV{ 0.0, 0.0, hsv.s });
				}
				else
				{
					smallCircle
						.draw(color)
						.draw(ColorF{ 1.0, 0.5 })
						.drawFrame(2, ColorF{ 0.75 });
				}
			}

			// V box
			{
				valueBox.draw(Arg::top = HSV{ hsv.h, hsv.s, 1.0 }, Arg::bottom = HSV{ hsv.h, hsv.s, 0.0 });

				if (not enabled)
				{
					valueBox.draw(ColorF{ 1.0, 0.5 });
				}

				const double y = (1.0 - hsv.v) * valueBox.h;
				const ColorF triangleColor{ enabled ? 0.2 : 0.5 };
				Triangle{ valueBoxBase.movedBy(-6, y), 10, 90_deg }.draw(triangleColor);
				Triangle{ valueBoxBase.movedBy(valueBox.w + 6, y), 10, 270_deg }.draw(triangleColor);
			}

			// Preview
			if (onValueBoxUpdate)
			{
				RectF{ Arg::center = circleCenter, 36 }.draw(HSV{ hsv, 1.0 });
			}

			return (previousHSV.toColorF() != hsv.toColorF());
		}
	}
}
