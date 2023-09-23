//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
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
	namespace SimpleGUI
	{
		namespace detail
		{
			static void TextAreaDraw(const TextAreaEditState& text, const Font& font, const int32 fontHeight, const RectF& region,
				const RectF& textRenderRegion, const double textRenderRegionBottomY,
				double textCursorLineX, const double textCursorLineY0, const double textCursorLineY1,
				const String& editingText, const Vec2& editingTextPos, const double maxScroll, const bool enabled);
		}

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
		constexpr int32 ListBoxFrameThickness = 1;
		constexpr int32 ScrollBarWidth = 18;
		constexpr ColorF ListBoxSelectedColor{ 0.2, 0.4, 0.8 };
		constexpr ColorF ListBoxSelectedDisabledColor{ 0.75, 0.85, 1.0 };
		constexpr double MinTextBoxWidth = 40.0;
		constexpr double MinTextAreaHeight = 36.0;
		constexpr double TextAreaScrollBarWidth = 3.0;
		constexpr double TextAreaScrollBarMinHeight = 16.0;
		constexpr ColorF TextAreaEditingTextBackgroundColor{ 0.8 };
		constexpr ColorF TextAreaScrollBarColor{ 0.67 };
		constexpr ColorF CandidateWindowColor{ 0.98 };
		constexpr ColorF CandidateWindowFrameColor{ 0.75 };
		constexpr ColorF CandidateSelectedBackgroundColor{ 0.55, 0.85, 1.0 };
		constexpr ColorF CandidateTextColor{ 0.11 };
		constexpr ColorF CandidateMinimapColor{ 0.67 };
		constexpr double CandidateMargin = 4.0;
		constexpr double CandidatePadding = 12.0;
		constexpr double CandidateMinimapWidth = 20.0;

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

		const Font& GetFont() noexcept
		{
			return SIV3D_ENGINE(GUI)->getDefaultFont();
		}

		RectF HeadlineRegion(const StringView text, const Vec2& pos, const Optional<double>& _width)
		{
			const Font& font = GetFont();
			const double width = _width.value_or_eval([&](){ return Math::Ceil(font(text).region().w + 20); });
			return{ pos, width, CellSize };
		}

		void Headline(const StringView text, const Vec2& pos, const Optional<double>& _width, const bool enabled)
		{
			const Font& font = GetFont();
			const RectF region = HeadlineRegion(text, pos, _width);
			region.draw(BackgroundColor);

			const auto dtext = font(text);
			const double labelWidth = Math::Ceil(dtext.region().w);
			const Vec2 labelPos{ (region.x + (region.w - labelWidth) / 2.0), (region.center().y - font.height() / 2.0 + FontYOffset) };
			dtext.draw(labelPos, GetTextColor(enabled));
		}

		RectF ButtonRegion(const StringView label, const Vec2& pos, const Optional<double>& _width)
		{
			const Font& font = GetFont();
			const double width = _width.value_or_eval([&](){ return Math::Ceil(font(label).region().w + 40); });
			return{ pos, width, UnitSize };
		}

		RectF ButtonRegionAt(const StringView label, const Vec2& center, const Optional<double>& _width)
		{
			const Font& font = GetFont();
			const double width = _width.value_or_eval([&](){ return Math::Ceil(font(label).region().w + 40); });
			return{ Arg::center = center, width, UnitSize };
		}

		bool Button(const StringView label, const Vec2& pos, const Optional<double>& _width, const bool enabled)
		{
			const Vec2 center = ButtonRegion(label, pos, _width).center();
			return ButtonAt(label, center, _width, enabled);
		}

		bool ButtonAt(const StringView label, const Vec2& center, const Optional<double>& _width, const bool enabled)
		{
			const Font& font = GetFont();
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
			return Slider(StringView{}, value, 0.0, 1.0, pos, 0.0, sliderWidth, enabled);
		}

		bool Slider(double& value, const double min, const double max, const Vec2& pos, const double sliderWidth, const bool enabled)
		{
			return Slider(StringView{}, value, min, max, pos, 0.0, sliderWidth, enabled);
		}

		bool Slider(const StringView label, double& value, const Vec2& pos, const double labelWidth, const double sliderWidth, const bool enabled)
		{
			return Slider(label, value, 0.0, 1.0, pos, labelWidth, sliderWidth, enabled);
		}

		bool Slider(const StringView label, double& value, const double min, const double max, const Vec2& pos, const double labelWidth, const double sliderWidth, const bool enabled)
		{
			const Vec2 center = SliderRegion(pos, labelWidth, sliderWidth).center();
			return SliderAt(label, value, min, max, center, labelWidth, sliderWidth, enabled);
		}

		bool SliderAt(double& value, const Vec2& center, const double sliderWidth, const bool enabled)
		{
			return SliderAt(StringView{}, value, 0.0, 1.0, center, 0.0, sliderWidth, enabled);
		}

		bool SliderAt(double& value, const double min, const double max, const Vec2& center, const double sliderWidth, const bool enabled)
		{
			return SliderAt(StringView{}, value, min, max, center, 0.0, sliderWidth, enabled);
		}

		bool SliderAt(const StringView label, double& value, const Vec2& center, const double labelWidth, const double sliderWidth, const bool enabled)
		{
			return SliderAt(label, value, 0.0, 1.0, center, labelWidth, sliderWidth, enabled);
		}

		bool SliderAt(const StringView label, double& value, double min, double max, const Vec2& center, const double _labelWidth, const double _sliderWidth, const bool enabled)
		{
			const Font& font = GetFont();

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

		RectF CheckBoxRegion(const StringView label, const Vec2& pos, const Optional<double>& _width)
		{
			const Font& font = GetFont();
			const double width = _width.value_or_eval([&](){ return Math::Ceil(CheckBoxPadding * 3 + CheckBoxSize + font(label).region().w); });
			return{ pos, width, UnitSize };
		}

		RectF CheckBoxRegionAt(const StringView label, const Vec2& center, const Optional<double>& _width)
		{
			const Font& font = GetFont();
			const double width = _width.value_or_eval([&](){ return Math::Ceil(CheckBoxPadding * 3 + CheckBoxSize + font(label).region().w); });
			return{ Arg::center = center, width, UnitSize };
		}

		bool CheckBox(bool& checked, const StringView label, const Vec2& pos, const Optional<double>& _width, const bool enabled)
		{
			const Vec2 center = CheckBoxRegion(label, pos, _width).center();
			return CheckBoxAt(checked, label, center, _width, enabled);
		}

		bool CheckBoxAt(bool& checked, const StringView label, const Vec2& center, const Optional<double>& _width, const bool enabled)
		{
			const Font& font = GetFont();
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
			const Font& font = GetFont();
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
			const Font& font = GetFont();
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
			const Font& font = GetFont();
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
			const Font& font = GetFont();

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
			const Font& font = GetFont();

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
			const Font& font = GetFont();

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
			width = Max(width, MinTextBoxWidth);

			return{ pos, width, TextBoxHeight };
		}

		RectF TextBoxRegionAt(const Vec2& center, double width)
		{
			width = Max(width, MinTextBoxWidth);

			return{ Arg::center = center, width, TextBoxHeight };
		}

		bool TextBox(TextEditState& text, const Vec2& pos, double width, const Optional<size_t>& maxChars, const bool enabled)
		{
			width = Max(width, MinTextBoxWidth);

			return TextBoxAt(text, pos + Vec2{ width * 0.5, 18.0 }, width, maxChars, enabled);
		}

		bool TextBoxAt(TextEditState& text, const Vec2& center, const double _width, const Optional<size_t>& maxChars, const bool enabled)
		{
			text.cursorPos = Min(text.cursorPos, text.text.size());
			text.tabKey = false;
			text.enterKey = false;

			const Font& font = SimpleGUI::GetFont();
			const int32 fontHeight = font.height();

			const String previousText = text.text;
			const String editingText = ((text.active && enabled) ? TextInput::GetEditingText() : U"");

			// テキストを更新する
			{
				if (text.active && enabled)
				{
					// text.text を更新する
					text.cursorPos = TextInput::UpdateText(text.text, text.cursorPos, TextInputMode::AllowBackSpaceDelete);

				# if not SIV3D_PLATFORM(WEB)

					// ショートカットキーによるペースト
					if ((not editingText) &&
					# if SIV3D_PLATFORM(MACOS)
						((KeyCommand + KeyV).down() || (KeyControl + KeyV).down())
					# else
						(KeyControl + KeyV).down()
					# endif
						)
					{
						if (String paste; Clipboard::GetText(paste))
						{
							paste.remove_if([](char32 ch) { return (ch < 0x20) || (ch == U'\x7F'); });
							text.text.insert(text.cursorPos, paste);
							text.cursorPos += paste.size();
						}
					}

				# endif
				}

				// 最大字数を超えていたら削る
				if (maxChars && (*maxChars < text.text.size()))
				{
					text.text.resize(*maxChars);
					text.cursorPos = Min(text.cursorPos, *maxChars);
				}

				// 文字列に変更があったかを調べる
				text.textChanged = (text.text != previousText);

				// 文字列に変更があれば
				if (text.textChanged)
				{
					// カーソル点滅をリセットする
					text.cursorStopwatch.restart();
				}
			}

			// テキストボックス
			const double width = Max(_width, MinTextBoxWidth);
			const RectF region{ Arg::center = center, Max(width, MinTextBoxWidth), TextBoxHeight };

			// マウスカーソルを IBeam にする
			if (enabled && Cursor::OnClientRect() && region.mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::IBeam);
			}

			// 入力カーソルのアクティブ / 非アクティブを切り替える
			if (MouseL.down() && (TextInput::GetEditingText().isEmpty()))
			{
				if (enabled && Cursor::OnClientRect() && region.mouseOver())
				{
					text.active = true;
					text.resetStopwatches();

					// カーソルの位置を計算する
					{
						const double posX = (Cursor::PosF().x - (region.x + 8));
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
					}
				}
				else
				{
					text.active = false;
				}
			}

			// テキストカーソルを更新する
			if (text.text)
			{
				if (text.active && enabled && (not editingText))
				{
					// キーでテキストカーソルを移動させる
					// 一定時間押下すると、テキストカーソルが高速に移動

					// テキストカーソルを先頭へ移動させる
					if ((KeyControl + KeyHome).down()) // [ctrl] + [home]: 全体の先頭へ
					{
						text.cursorPos = 0;
						text.cursorStopwatch.restart();
					}
					else if (
					# if SIV3D_PLATFORM(MACOS)
						((KeyControl + KeyA).down() || KeyHome.down())
					# else
						KeyHome.down()
					# endif
						) // [home]: 行頭へ
					{
						text.cursorPos = 0;
						text.cursorStopwatch.restart();
					}

					// テキストカーソルを末尾へ移動させる
					if ((KeyControl + KeyEnd).down()) // [ctrl] + [end]: 全体の末尾へ
					{
						text.cursorPos = text.text.size();
						text.cursorStopwatch.restart();
					}
					else if (
					# if SIV3D_PLATFORM(MACOS)
						((KeyControl + KeyE).down() || KeyEnd.down())
					# else
						KeyEnd.down()
					# endif
						) // [end]: 行末へ
					{
						text.cursorPos = text.text.size();
						text.cursorStopwatch.restart();
					}

					// [←] キー
					if ((0 < text.cursorPos)
						&& (KeyLeft.down() || ((SecondsF{ 0.33 } < KeyLeft.pressedDuration()) && (SecondsF{ 0.06 } < text.leftPressStopwatch))))
					{
						--text.cursorPos;
						text.leftPressStopwatch.restart();
					}

					// [→] キー
					if ((text.cursorPos < text.text.size())
						&& (KeyRight.down() || ((SecondsF{ 0.33 } < KeyRight.pressedDuration()) && (SecondsF{ 0.06 } < text.rightPressStopwatch))))
					{
						++text.cursorPos;
						text.rightPressStopwatch.restart();
					}
				}
			}

			if (text.active && enabled && (not editingText))
			{
				// [tab][enter] キーで入力カーソルを非アクティブに
				{
					const String raw = TextInput::GetRawInput();
					text.tabKey = raw.contains(U'\t');
					text.enterKey = raw.contains(U'\r');

					if (text.tabKey || text.enterKey)
					{
						text.active = false;
					}
				}
			}

			// 描画
			{
				const Vec2 textPos{ (region.x + 8), (center.y - font.height() / 2 + FontYOffset - 0.5) };

				if (enabled)
				{
					if (text.active)
					{
						region
							.draw()
							.drawFrame(0.0, 1.5, ColorF{ 0.35, 0.7, 1.0, 0.75 })
							.drawFrame(2.5, 0.0, ColorF{ 0.35, 0.7, 1.0 });
					}
					else
					{
						region
							.draw()
							.drawFrame(2.0, 0.0, ColorF{ 0.5 });
					}
				}
				else
				{
					region
						.draw(ColorF{ 0.9 })
						.drawFrame(2.0, 0.0, ColorF{ 0.67 });
				}

				{
					const ColorF textColor = GetTextColor(enabled);
					const auto& pixelShader = Font::GetPixelShader(font.method());
					
					double cursorPosX = textPos.x;
					Vec2 editingTextPos = textPos;

					// テキストの描画
					{
						const ScopedCustomShader2D shader{ pixelShader };
						Vec2 penPos = textPos;
						const Array<Glyph> glyphs = font.getGlyphs(text.text);

						for (auto&& [index, glyph] : Indexed(glyphs))
						{
							const double xAdvance = glyph.xAdvance;
							const Vec2 glyphPos = (penPos + glyph.getOffset());

							glyph.texture.draw(glyphPos, textColor);		
							penPos.x += xAdvance;

							// テキストカーソルの位置の計算を計算する
							if (text.active && (text.cursorPos == (index + 1)))
							{
								cursorPosX = penPos.x;
								editingTextPos = penPos;
							}
						}
					}

					if (editingText)
					{
						// 変換テキストとその領域の取得
						const Array<Glyph> editingGlyphs = font.getGlyphs(editingText);
						Array<Vec2> editingGlyphPositions(editingGlyphs.size());
						{
							Vec2 penPos = editingTextPos;

							for (size_t i = 0; i < editingGlyphs.size(); ++i)
							{
								const auto& glyph = editingGlyphs[i];
								editingGlyphPositions[i] = (penPos + glyph.getOffset());
								penPos.x += glyph.xAdvance;
							}
						}

						// 変換テキスト背景の描画
						if (editingGlyphs)
						{
							const auto& firstGlyph = editingGlyphs.front();
							const auto& lastGlyph = editingGlyphs.back();
							const Vec2 pos = (editingGlyphPositions.front() - firstGlyph.getOffset());
							const double w = ((editingGlyphPositions.back().x - lastGlyph.getOffset().x + lastGlyph.xAdvance) - pos.x);
							RectF{ pos, w, fontHeight }.draw(TextAreaEditingTextBackgroundColor);

							// 変換テキストの選択範囲の描画
							{
							# if SIV3D_PLATFORM(WINDOWS)

								const std::pair<int32, int32> editingTarget = Platform::Windows::TextInput::GetCursorIndex();

							# elif SIV3D_PLATFORM(WEB)

								const std::pair<int32, int32> editingTarget = Platform::Web::TextInput::GetCandicateCursorIndex();

							# else

								const std::pair<int32, int32> editingTarget{ -1, 0 };

							# endif

								if (editingTarget.second && ((editingTarget.first + editingTarget.second) <= editingGlyphPositions.size()))
								{
									const int32 firstIndex = editingTarget.first;
									const int32 lastIndex = (editingTarget.first + editingTarget.second - 1);
									const double x0 = editingGlyphPositions[firstIndex].x;
									const double x1 = editingGlyphPositions[lastIndex].x + editingGlyphs[lastIndex].xAdvance;
									RectF{ x0, (pos.y + fontHeight - 2), (x1 - x0), 2 }.draw(ActiveTextColor);
								}
							}
						}

						// 変換テキストの描画
						{
							const ScopedCustomShader2D shader{ pixelShader };

							for (size_t i = 0; i < editingGlyphs.size(); ++i)
							{
								const auto& glyph = editingGlyphs[i];
								glyph.texture.draw(editingGlyphPositions[i], textColor);
							}
						}
					}

					// テキスト入力カーソルの描画
					if (text.active && enabled)
					{
						const bool showCursor = (text.cursorStopwatch.ms() % 1200 < 600)
							|| (text.leftPressStopwatch.isRunning() && (text.leftPressStopwatch < SecondsF{ 0.5 }))
							|| (text.rightPressStopwatch.isRunning() && (text.rightPressStopwatch < SecondsF{ 0.5 }));

						if (showCursor)
						{
							const RectF cursor(Arg::leftCenter(Vec2{ cursorPosX, region.center().y }.asPoint()), 1, 26);
							cursor.draw(Palette::Black);
						}
					}
				}
			}

		# if SIV3D_PLATFORM(WEB)

			Platform::Web::TextInput::SetFocusToTextInput(text.active);		
				
			if (text.active && not editingText)
			{
				if (text.lastCursorPos != text.cursorPos)
				{
					Platform::Web::TextInput::SyncronizeText(text.text);
					Platform::Web::TextInput::SetCursorIndex(text.cursorPos);		
				}
				else if (auto currentCursorPos = Platform::Web::TextInput::GetCursorIndex(); text.lastCursorPos != currentCursorPos)
				{
					text.cursorPos = currentCursorPos;
					text.cursorStopwatch.restart();
				}

				text.lastCursorPos = text.cursorPos;
			}

		# endif

			return text.textChanged;
		}

		RectF TextAreaRegion(const Vec2& pos, const SizeF& size)
		{
			return{ pos, Max(size.x, MinTextBoxWidth), Max(size.y, MinTextAreaHeight) };
		}

		RectF TextAreaRegionAt(const Vec2& center, const SizeF& size)
		{
			return{ Arg::center = center, Max(size.x, MinTextBoxWidth), Max(size.y, MinTextAreaHeight) };
		}

		bool TextArea(TextAreaEditState& text, const Vec2& pos, const SizeF& size, const size_t maxChars, const bool enabled)
		{
			const double width = Max(size.x, MinTextBoxWidth);
			const double height = Max(size.y, MinTextAreaHeight);
			return TextAreaAt(text, pos.movedBy((width * 0.5), (height * 0.5)), SizeF{ width, height }, maxChars, enabled);
		}

		bool TextAreaAt(TextAreaEditState& text, const Vec2& center, const SizeF& size, const size_t maxChars, const bool enabled)
		{
			text.cursorPos = Min(text.cursorPos, text.text.size());

			const Font& font = SimpleGUI::GetFont();
			const int32 fontHeight = font.height();

			const String previousText = text.text;
			const String editingText = ((text.active && enabled) ? TextInput::GetEditingText() : U"");

			// テキストを更新する
			{
				if (text.active && enabled)
				{
					// text.text を更新する
					text.cursorPos = TextInput::UpdateText(text.text, text.cursorPos, TextInputMode::AllowEnterTabBackSpaceDelete);

				# if not SIV3D_PLATFORM(WEB)

					// ショートカットキーによるペースト
					if ((not editingText) &&
					# if SIV3D_PLATFORM(MACOS)
						((KeyCommand + KeyV).down() || (KeyControl + KeyV).down())
					# else
						(KeyControl + KeyV).down()
					# endif
						)
					{
						if (String paste; Clipboard::GetText(paste))
						{
							text.text.insert(text.cursorPos, paste);
							text.cursorPos += paste.size();
						}
					}

				# endif
				}

				// 最大字数を超えていたら削る
				if (maxChars < text.text.size())
				{
					text.text.resize(maxChars);
					text.cursorPos = Min(text.cursorPos, maxChars);
				}

				// 文字列に変更があったかを調べる
				text.textChanged = (text.text != previousText);

				// 文字列に変更があれば
				if (text.textChanged)
				{
					// カーソル点滅をリセットする
					text.cursorStopwatch.restart();

					// グリフを再構築する
					text.rebuildGlyphs();
				}
			}

			// テキストエリア
			const RectF region{ Arg::center = center, Max(size.x, MinTextBoxWidth), Max(size.y, MinTextAreaHeight) };

			// 入力カーソルのアクティブ / 非アクティブを切り替える
			if (MouseL.down() && (TextInput::GetEditingText().isEmpty()))
			{
				if (Cursor::OnClientRect() && region.mouseOver())
				{
					text.active = true;
					text.resetStopwatches();
				}
				else
				{
					text.active = false;
				}
			}

			const RectF textRenderRegion = region.stretched(-2, -(6 + TextAreaScrollBarWidth), -2, -8);
			const double textRenderRegionRightX = textRenderRegion.rightX();
			const double textRenderRegionBottomY = textRenderRegion.bottomY();

			double textCursorLineX = 0.0, textCursorLineY0 = 0.0, textCursorLineY1 = 0.0;
			if (text.active && (text.cursorPos == 0))
			{
				textCursorLineX = textRenderRegion.x;
				textCursorLineY0 = (textRenderRegion.y + text.scrollY);
				textCursorLineY1 = (textCursorLineY0 + fontHeight);
			}

			Vec2 editingTextPos = textRenderRegion.pos;
			double newScrollY = Min(text.scrollY + (region.mouseOver() ? (Mouse::Wheel() * -fontHeight * 0.5) : 0.0), 0.0);
			double scrollOffset = 0.0;
			uint16 maxRow = 0;
			{
				text.glyphPositions.clear();
				text.clipInfos.clear();

				Vec2 penPos = textRenderRegion.pos;
				uint16 row = 0;
				uint16 column = 1;

				// 入力した文字列の各文字と、位置と描画領域を記録する。
				for (auto&& [index, glyph] : Indexed(text.glyphs))
				{
					// 改行文字であるか
					bool isLF = false;

					// 改行が発生したか
					bool isLineBreak = false;

					// 改行の場合、描画位置を下にずらす
					if (glyph.codePoint == U'\n')
					{
						isLF = true;
						penPos.x = textRenderRegion.x;
						penPos.y += fontHeight;
						column = 0;
						maxRow = ++row;
					}

					const double xAdvance = glyph.xAdvance;

					Vec2 glyphPos = penPos.movedBy(0, text.scrollY);
					{
						// テキストがテキスト描画領域右端からはみ出る場合、テキストを枠内に収めるようにテキストを折り返す
						if (textRenderRegionRightX < (glyphPos.x + xAdvance))
						{
							penPos.x = textRenderRegion.x;
							penPos.y += fontHeight;
							isLineBreak = true;
							column = 1;
							maxRow = ++row;
						}

						// テキストの描画位置のオフセットを決定する
						if ((index + 1) == text.cursorPos)
						{
							const double d1 = ((penPos.y + fontHeight + newScrollY) - textRenderRegionBottomY);
							const double d2 = (textRenderRegion.y - (penPos.y + newScrollY));

							if (0.0 < d1)
							{
								scrollOffset = -d1;
							}
							else if (0.0 < d2)
							{
								scrollOffset = d2;
							}
						}

						glyphPos = (penPos + glyph.getOffset() + Vec2{ 0, text.scrollY });
					}

					// グリフのクリップ領域（描画矩形）を決める
					RectF clipRect{ 0 };
					{
						// x 方向のクリップを決める
						if (InRange(glyphPos.x, (textRenderRegion.x - xAdvance), textRenderRegion.x))
						{
							clipRect.x = textRenderRegion.x;
							clipRect.w = ((glyphPos.x + xAdvance - textRenderRegion.x) - glyph.getOffset().x);
						}
						else if (InRange(glyphPos.x, textRenderRegion.x, (textRenderRegionRightX - xAdvance)))
						{
							clipRect.x = glyphPos.x;
							clipRect.w = (xAdvance - glyph.getOffset().x);
						}
						else if (InRange(glyphPos.x, (textRenderRegionRightX - xAdvance), textRenderRegionRightX))
						{
							clipRect.x = glyphPos.x;
							clipRect.w = ((textRenderRegionRightX - glyphPos.x) - glyph.getOffset().x);
						}

						// y 方向のクリップを決める
						if (InRange(glyphPos.y, (textRenderRegion.y - fontHeight), textRenderRegion.y))
						{
							clipRect.y = textRenderRegion.y;
							clipRect.h = (glyphPos.y + fontHeight - textRenderRegion.y);
						}
						else if (InRange(glyphPos.y, textRenderRegion.y, (textRenderRegion.y + size.y - fontHeight)))
						{
							clipRect.y = glyphPos.y;
							clipRect.h = fontHeight;
						}
						else if (InRange(glyphPos.y, (textRenderRegionBottomY - fontHeight), textRenderRegionBottomY))
						{
							clipRect.y = glyphPos.y;
							clipRect.h = (textRenderRegionBottomY - glyphPos.y);
						}
					}

					// テキストエリアの範囲内にある文字のみ描画対象に加える。
					if (InRange(glyphPos.x, (textRenderRegion.x - xAdvance), textRenderRegionRightX)
							&& InRange(glyphPos.y, (textRenderRegion.y - glyph.yAdvance), (textRenderRegionBottomY + fontHeight - glyph.yAdvance)))
					{
						if (isLF)
						{
							if (text.clipInfos)
							{
								text.clipInfos.back().isEndOfLine = true;
							}

							text.clipInfos.push_back({ glyphPos, RectF::Empty(), static_cast<uint32>(index), false, false });
						}
						else
						{
							const bool isEndOfText = (index == (text.glyphs.size() - 1));

							if (isLineBreak && text.clipInfos)
							{
								text.clipInfos.back().isEndOfLine = true;
							}

							text.clipInfos.push_back({ glyphPos, clipRect, static_cast<uint32>(index), isEndOfText, false });
						}
					}

					{
						text.glyphPositions.emplace_back(row, column);
						++column;
					}

					// テキストカーソルの位置の計算を計算する
					if (text.active && (text.cursorPos == (index + 1)))
					{
						double yBegin = 0.0, yEnd = 0.0;

						if ((penPos.y + text.scrollY) < textRenderRegion.y)
						{
							yBegin = textRenderRegion.y;
						}
						else
						{
							yBegin = (penPos.y + text.scrollY);
						}

						if (textRenderRegionBottomY < (penPos.y + fontHeight + text.scrollY))
						{
							yEnd = textRenderRegionBottomY;
						}
						else
						{
							yEnd = (penPos.y + fontHeight + text.scrollY);
						}

						if ((textRenderRegionRightX < (glyphPos.x + xAdvance))
							|| ((glyphPos.x + xAdvance) < textRenderRegion.x))
						{
							yBegin = 0.0;
							yEnd = 0.0;
						}

						textCursorLineX = (glyphPos.x + (isLF ? 0 : clipRect.w));
						textCursorLineY0 = yBegin;
						textCursorLineY1 = yEnd;

						editingTextPos = Vec2{ (glyphPos.x + (isLF ? 0 : clipRect.w)), (penPos.y + text.scrollY) };
					}

					if (isLF)
					{
						continue;
					}

					penPos.x += xAdvance;
				}

				// テキストカーソルの位置の計算を計算する
				if (text.active && (text.cursorPos == 0))
				{
					double yBegin = 0.0, yEnd = 0.0;

					if ((textRenderRegion.y + text.scrollY) < textRenderRegion.y)
					{
						yBegin = textRenderRegion.y;
					}
					else
					{
						yBegin = (textRenderRegion.y + text.scrollY);
					}

					if (textRenderRegionBottomY < (textRenderRegion.y + fontHeight + text.scrollY))
					{
						yEnd = textRenderRegionBottomY;
					}
					else
					{
						yEnd = (textRenderRegion.y + fontHeight + text.scrollY);
					}

					textCursorLineX = textRenderRegion.x;
					textCursorLineY0 = yBegin;
					textCursorLineY1 = yEnd;

					editingTextPos = Vec2{ textRenderRegion.x, (textRenderRegion.y + text.scrollY) };
				}
			}

			// テキストカーソルを更新する
			if (text.glyphPositions)
			{
				if (text.refreshScroll)
				{
					if (text.cursorPos == 0)
					{
						newScrollY = 0.0;
					}
					else
					{
						newScrollY = (text.scrollY + scrollOffset);
					}

					text.refreshScroll = false;
				}

				text.refreshScroll |= (text.textChanged || editingText);

				if (text.active && enabled && (not editingText))
				{
					// キーでテキストカーソルを移動させる
					// 一定時間押下すると、テキストカーソルが高速に移動

					// テキストカーソルを先頭へ移動させる
					if ((KeyControl + KeyHome).down()) // [ctrl] + [home]: 全体の先頭へ
					{
						text.cursorPos = 0;
						text.cursorStopwatch.restart();
						text.refreshScroll = true;
					}
					else if (
					# if SIV3D_PLATFORM(MACOS)
						((KeyControl + KeyA).down() || KeyHome.down())
					# else
						KeyHome.down()
					# endif
						) // [home]: 行頭へ
					{
						for (int32 i = (static_cast<int32>(text.cursorPos) - 1); 0 <= i; --i)
						{
							if (text.glyphs[i].codePoint == '\n')
							{
								text.cursorPos = (i + 1);
								text.cursorStopwatch.restart();
								text.refreshScroll = true;
								break;
							}
							else if (i == 0)
							{
								text.cursorPos = 0;
								text.cursorStopwatch.restart();
								text.refreshScroll = true;
								break;
							}
						}
					}

					// テキストカーソルを末尾へ移動させる
					if ((KeyControl + KeyEnd).down()) // [ctrl] + [end]: 全体の末尾へ
					{
						text.cursorPos = text.text.size();
						text.cursorStopwatch.restart();
						text.refreshScroll = true;
					}
					else if (
					# if SIV3D_PLATFORM(MACOS)
						((KeyControl + KeyE).down() || KeyEnd.down())
					# else
						KeyEnd.down()
					# endif
						) // [end]: 行末へ
					{
						for (size_t i = text.cursorPos; i <= text.text.size(); ++i)
						{
							if (i == text.text.size())
							{
								text.cursorPos = text.text.size();
								text.cursorStopwatch.restart();
								text.refreshScroll = true;
								break;
							}
							else if (text.glyphs[i].codePoint == '\n')
							{
								text.cursorPos = i;
								text.cursorStopwatch.restart();
								text.refreshScroll = true;
								break;
							}
						}
					}

					// [←] キー
					if ((0 < text.cursorPos)
						&& (KeyLeft.down() || ((SecondsF{ 0.33 } < KeyLeft.pressedDuration()) && (SecondsF{ 0.06 } < text.leftPressStopwatch))))
					{
						--text.cursorPos;
						text.leftPressStopwatch.restart();
						text.refreshScroll = true;
					}

					// [→] キー
					if ((text.cursorPos < text.text.size())
						&& (KeyRight.down() || ((SecondsF{ 0.33 } < KeyRight.pressedDuration()) && (SecondsF{ 0.06 } < text.rightPressStopwatch))))
					{
						++text.cursorPos;
						text.rightPressStopwatch.restart();
						text.refreshScroll = true;
					}

					// [↑] キーでテキストカーソルを上に移動させる
					if (KeyUp.down() || ((SecondsF{ 0.33 } < KeyUp.pressedDuration()) && (SecondsF{ 0.06 } < text.upPressStopwatch)))
					{
						const int32 currentRow = (text.cursorPos ? text.glyphPositions[text.cursorPos - 1].first : 0);
						const int32 currentColumn = (text.cursorPos ? text.glyphPositions[text.cursorPos - 1].second : 0);

						if (0 < currentRow)
						{
							for (int32 i = (static_cast<int32>(text.cursorPos) - 1); 0 <= i; --i)
							{
								if (i == 0)
								{
									text.cursorPos = 0;
									break;
								}

								const auto& glyphPosition = text.glyphPositions[i - 1];
								const int32 row = glyphPosition.first;
								const int32 column = glyphPosition.second;

								if (row < currentRow)
								{
									if ((row + 1) < currentRow)
									{
										text.cursorPos = (i + 1);
										break;
									}

									if (column <= currentColumn)
									{
										text.cursorPos = i;
										break;
									}
								}
							}
						}

						text.upPressStopwatch.restart();
						text.refreshScroll = true;
					}

					// [↓] キーでテキストカーソルを下に移動させる
					if (KeyDown.down() || ((SecondsF{ 0.33 } < KeyDown.pressedDuration()) && (SecondsF{ 0.06 } < text.downPressStopwatch)))
					{
						const int32 maxCursorIndex = static_cast<int32>(text.glyphPositions.size());
						const int32 currentRow = (text.cursorPos ? text.glyphPositions[text.cursorPos - 1].first : 0);
						const int32 currentColumn = (text.cursorPos ? text.glyphPositions[text.cursorPos - 1].second : 0);

						if (currentRow < (text.glyphPositions.back().first))
						{
							for (int32 i = (static_cast<int32>(text.cursorPos) + 1); i <= maxCursorIndex; ++i)
							{
								const auto& glyphPosition = text.glyphPositions[i - 1];
								const int32 row = glyphPosition.first;
								const int32 column = glyphPosition.second;

								if (currentRow < row)
								{
									if ((currentRow + 1) < row)
									{
										text.cursorPos = (i - 1);
										break;
									}

									if (currentColumn <= column)
									{
										text.cursorPos = i;
										break;
									}
								}

								if (i == maxCursorIndex)
								{
									text.cursorPos = maxCursorIndex;
									break;
								}
							}
						}

						text.downPressStopwatch.restart();
						text.refreshScroll = true;
					}
				}
			}

			// テキストエリアクリックでテキストカーソルを移動させる
			if (const Vec2 cursorPos = Cursor::PosF();
				enabled && textRenderRegion.intersects(cursorPos) && MouseL.down())
			{
				if (text.clipInfos)
				{
					text.cursorPos = text.clipInfos.front().index;
				}
			
				// 最後の行の文字をマーク
				if (1 <= text.clipInfos.size())
				{
					auto it = text.clipInfos.rbegin();

					it->isLastLine = true;
					it->isEndOfLine = true;

					++it;

					for (; it != text.clipInfos.rend(); ++it)
					{
						if (it->isEndOfLine)
						{
							break;
						}

						it->isLastLine = true;
					}
				}

				// カーソルの移動先を求める
				for (const auto& clipInfo : text.clipInfos)
				{
					const auto& glyph = text.glyphs[clipInfo.index];

					const Vec2 penPos = (clipInfo.pos - glyph.getOffset());

					RectF rect{ penPos, glyph.xAdvance, fontHeight };

					if (clipInfo.isEndOfLine)
					{
						rect.w = (textRenderRegionRightX - rect.x);
					}

					if (clipInfo.isLastLine)
					{
						rect.h = (textRenderRegionBottomY - rect.y);
					}

					if (rect.intersects(cursorPos))
					{
						text.cursorPos = (clipInfo.index + ((glyph.xAdvance / 2) <= (cursorPos.x - penPos.x)));
						text.cursorStopwatch.restart();
						break;
					}
				}
			}

			const double maxScroll = Min(-((maxRow + 1.5) * fontHeight - region.h), 0.0);
			text.scrollY = Clamp(newScrollY, maxScroll, 0.0);

			//描画
			detail::TextAreaDraw(text, font, fontHeight, region, textRenderRegion, textRenderRegionBottomY,
									textCursorLineX, textCursorLineY0, textCursorLineY1,
									editingText, editingTextPos, maxScroll, enabled);
	
			return text.textChanged;
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

		RectF ListBoxRegion(const Vec2& pos, const double width, const double height)
		{
			const Font& font = SimpleGUI::GetFont();
			const RectF rect{ pos, Max(width, 40.0), Max<double>(height, font.height() + (ListBoxFrameThickness * 2)) };
			return rect;
		}

		RectF ListBoxRegionAt(const Vec2& center, const double width, const double height)
		{
			const Font& font = SimpleGUI::GetFont();
			const RectF rect{ Arg::center(center), Max(width, 40.0), Max<double>(height, font.height() + (ListBoxFrameThickness * 2)) };
			return rect;
		}

		bool ListBox(ListBoxState& state, const Vec2& pos, const double width, const double height, const bool enabled)
		{
			const Font& font = SimpleGUI::GetFont();
			const RectF rect{ pos, Max(width, 40.0), Max<double>(height, font.height() + (ListBoxFrameThickness * 2)) };
			return ListBoxAt(state, rect.center(), width, height, enabled);
		}

		bool ListBoxAt(ListBoxState& state, const Vec2& center, const double width, const double height, const bool enabled)
		{
			const Optional<size_t> oldState = state.selectedItemIndex;

			const Font& font = SimpleGUI::GetFont();
			const int32 maxLines = (static_cast<int32>(height) - (ListBoxFrameThickness * 2)) / font.height();
			const bool hasScrollBar = (maxLines < static_cast<int32>(state.items.size()));
			const RectF rect{ Arg::center(center), Max(width, 40.0), Max<double>(height, font.height() + (ListBoxFrameThickness * 2)) };
			const Vec2 pos = rect.pos;

			const int32 fontHeight = font.height();
			const int32 lines = Min(static_cast<int32>(state.items.size()), maxLines);
			const int32 itemWidth = static_cast<int32>(rect.w - (ListBoxFrameThickness * 2) - (hasScrollBar ? ScrollBarWidth : 0));

			if (state.items.isEmpty())
			{
				state.selectedItemIndex.reset();
			}
			else if (state.items.size() <= state.selectedItemIndex)
			{
				state.selectedItemIndex = (state.items.size() - 1);
			}

			// update
			{
				if (enabled)
				{
					for (int32 i = 0; i < lines; ++i)
					{
						const size_t itemIndex = (state.scroll + i);
						const RectF itemRect(pos.x + ListBoxFrameThickness, pos.y + ListBoxFrameThickness + (fontHeight * i), itemWidth, fontHeight);

						if (itemRect.leftClicked())
						{
							state.active = true;
							state.selectedItemIndex = itemIndex;
						}
					}
				}
				
				if ((not enabled) || (MouseL.down() && not rect.mouseOver()))
				{
					state.active = false;
				}

				if (state.active && state.selectedItemIndex)
				{
					if ((0 < *state.selectedItemIndex) &&
						(KeyUp.down() || ((SecondsF{ 0.33 } < KeyUp.pressedDuration()) && (SecondsF{ 0.06 } < state.upPressStopwatch))))
					{
						--(*state.selectedItemIndex);
						state.upPressStopwatch.restart();

						if (hasScrollBar  && (static_cast<int32>(*state.selectedItemIndex) < state.scroll))
						{
							state.scroll = Max(state.scroll - 1, 0);
						}
					}
					else if (((*state.selectedItemIndex + 1) < state.items.size()) &&
						(KeyDown.down() || ((SecondsF{ 0.33 } < KeyDown.pressedDuration()) && (SecondsF{ 0.06 } < state.downPressStopwatch))))
					{
						++(*state.selectedItemIndex);
						state.downPressStopwatch.restart();

						if (hasScrollBar && (maxLines <= (static_cast<int32>(*state.selectedItemIndex) - state.scroll)))
						{
							state.scroll = Min(state.scroll + 1, static_cast<int32>(state.items.size()) - maxLines);
						}
					}
				}

				if (hasScrollBar)
				{
					const RectF scrollBarArea(pos.x + rect.w - (ListBoxFrameThickness + ScrollBarWidth), pos.y + ListBoxFrameThickness, ScrollBarWidth, rect.h - (ListBoxFrameThickness * 2));
					const RectF upButton(scrollBarArea.pos, ScrollBarWidth, ScrollBarWidth);
					const RectF downButton(scrollBarArea.x, scrollBarArea.y + scrollBarArea.h - ScrollBarWidth, ScrollBarWidth, ScrollBarWidth);

					if (upButton.leftClicked())
					{
						state.scroll = Max(state.scroll - 1, 0);
					}

					if (downButton.leftClicked())
					{
						state.scroll = Min(state.scroll + 1, static_cast<int32>(state.items.size()) - maxLines);
					}

					state.scroll = Min(state.scroll, static_cast<int32>(state.items.size()) - maxLines);

					const RectF innerScrollBarArea = scrollBarArea.stretched(0, -ScrollBarWidth);
					const double scrollBarHeight = (innerScrollBarArea.h * (static_cast<double>(maxLines) / state.items.size()));
					const int32 scrollBarOffset = static_cast<int32>((innerScrollBarArea.h - scrollBarHeight) * (static_cast<double>(state.scroll) / (state.items.size() - maxLines)));
					const RectF scrollBar(innerScrollBarArea.pos.movedBy(0, (scrollBarOffset - 3.0)), innerScrollBarArea.w, (scrollBarHeight + 6.0));

					if (state.scrollBarGrabbed && MouseL.up())
					{
						state.scrollBarGrabbed.reset();
					}

					if ((rect.mouseOver() && Mouse::Wheel()) || state.scrollBarGrabbed)
					{
						if (rect.mouseOver() && Mouse::Wheel())
						{
							state.wheel += Mouse::Wheel();
						}

						if (state.scrollBarGrabbed)
						{
							const double ih = static_cast<double>(innerScrollBarArea.h) / state.items.size();
							state.wheel = state.scrollBarGrabbed->second + ((Cursor::Pos().y - state.scrollBarGrabbed->first) / ih);
						}

						const double maxWheel = static_cast<int32>(state.items.size()) - maxLines;
						state.wheel = Clamp(state.wheel, 0.0, maxWheel);
						state.scroll = static_cast<int32>(state.wheel);
					}
					else
					{
						state.wheel = state.scroll;
					}

					if (scrollBar.leftClicked())
					{
						state.scrollBarGrabbed = std::pair{ Cursor::Pos().y, state.wheel };
					}
				}
				else
				{
					state.scrollBarGrabbed.reset();
					state.scroll = 0;
					state.wheel = 0.0;
				}
			}

			// draw
			{
				constexpr int32 PaddingLeft = 8;
				constexpr int32 PaddingRight = 8;

				rect
					.draw()
					.drawFrame(1, 0, ColorF{ 0.5 });

				const int32 textMaxWidth = itemWidth - (PaddingLeft + PaddingRight);
				const ColorF textColor = GetTextColor(enabled);

				for (int32 i = 0; i < lines; ++i)
				{
					const size_t itemIndex = (state.scroll + i);
					const bool selected = (itemIndex == state.selectedItemIndex);
					const RectF itemRect(pos.x + ListBoxFrameThickness, pos.y + ListBoxFrameThickness + (fontHeight * i), itemWidth, fontHeight);
					const RectF textRect(itemRect.pos.movedBy(PaddingLeft, 0), textMaxWidth, itemRect.h);
					const String& text = state.items[itemIndex];

					if (selected)
					{
						const ColorF selectedItemBackgroundColor = 
							enabled ? ListBoxSelectedColor : ListBoxSelectedDisabledColor;

						itemRect
							.stretched(-1, 0, 0, -1)
							.draw(selectedItemBackgroundColor);

						font(text).draw(textRect, ColorF{ 1.0 });
					}
					else
					{
						font(text).draw(textRect, textColor);
					}
				}

				if (hasScrollBar)
				{
					const RectF scrollBarArea(pos.x + rect.w - (ListBoxFrameThickness + ScrollBarWidth), pos.y + ListBoxFrameThickness, ScrollBarWidth, rect.h - (ListBoxFrameThickness * 2));
					const RectF upButton(scrollBarArea.pos, ScrollBarWidth, ScrollBarWidth);
					const RectF downButton(scrollBarArea.x, scrollBarArea.y + scrollBarArea.h - ScrollBarWidth, ScrollBarWidth, ScrollBarWidth);

					scrollBarArea.draw(ColorF(0.85));

					{
						const bool pressed = ((not state.scrollBarGrabbed) && upButton.leftPressed());
						const Vec2 c = upButton.center();

						if (pressed)
						{
							upButton
								.stretched(-1)
								.draw(ColorF{ 0.33 });
						}

						Triangle{ c.movedBy(0, -ScrollBarWidth * 0.22),
							c.movedBy(ScrollBarWidth * 0.25, ScrollBarWidth * 0.08),
							c.movedBy(-ScrollBarWidth * 0.25, ScrollBarWidth * 0.08) }
						.draw(pressed ? ColorF{ 0.85 } : ColorF{ 0.33 });
					}

					{
						const bool pressed = ((not state.scrollBarGrabbed) && downButton.leftPressed());
						const Vec2 c = downButton.center();

						if (pressed)
						{
							downButton
								.stretched(-1)
								.draw(ColorF{ 0.33 });
						}

						Triangle{ c.movedBy(0, ScrollBarWidth * 0.22),
							c.movedBy(-ScrollBarWidth * 0.25, -ScrollBarWidth * 0.08),
							c.movedBy(ScrollBarWidth * 0.25, -ScrollBarWidth * 0.08) }
						.draw(pressed ? ColorF{ 0.85 } : ColorF{ 0.33 });
					}

					const RectF innerScrollBarArea = scrollBarArea.stretched(0, -ScrollBarWidth);
					const double scrollBarHeight = (innerScrollBarArea.h * (static_cast<double>(maxLines) / state.items.size()));
					const int32 scrollBarOffset = static_cast<int32>((innerScrollBarArea.h - scrollBarHeight) * (static_cast<double>(state.scroll) / (state.items.size() - maxLines)));
					const RectF scrollBar(innerScrollBarArea.pos.movedBy(0, (scrollBarOffset - 3.0)), innerScrollBarArea.w, (scrollBarHeight + 6.0));

					scrollBar
						.stretched(-1, 0)
						.draw(state.scrollBarGrabbed ? ColorF{ 0.33 } : ColorF{ 0.67 });
				}
			}

			return (oldState != state.selectedItemIndex);
		}

		RectF IMECandidateWindowRegion(const Vec2& pos)
		{
		# if SIV3D_PLATFORM(WINDOWS)

			const auto& cadidateState = Platform::Windows::TextInput::GetCandidateState();

			if (not cadidateState.candidates)
			{
				return{ pos, 0 };
			}

			const Font& font = GetFont();

			const double boxWidth = [&font, &cadidateState]()
				{
					double boxWidth = 0.0;

					for (const auto& canditate : cadidateState.candidates)
					{
						boxWidth = Max<double>(boxWidth, font(canditate).region().w);
					}

					return boxWidth;
				}() + (CandidatePadding * 2 + CandidateMinimapWidth);

				const double candidateItemHeight = (font.height() + CandidateMargin);

				return{ pos, boxWidth, (candidateItemHeight * cadidateState.candidates.size()) };

		# else

			return{ pos, 0 };

		# endif
		}

		void IMECandidateWindow([[maybe_unused]] const Vec2& pos)
		{
		# if SIV3D_PLATFORM(WINDOWS)

			const auto& cadidateState = Platform::Windows::TextInput::GetCandidateState();

			if (not cadidateState.candidates)
			{
				return;
			}

			const Font& font = GetFont();

			const double boxWidth = [&font, &cadidateState]()
				{
					double boxWidth = 0.0;

					for (const auto& canditate : cadidateState.candidates)
					{
						boxWidth = Max<double>(boxWidth, font(canditate).region().w);
					}

					return boxWidth;
				}() + (CandidatePadding * 2 + CandidateMinimapWidth);

			const double candidateItemHeight = (font.height() + CandidateMargin);

			RectF{ pos, boxWidth, (candidateItemHeight * cadidateState.candidates.size()) }
				.drawShadow(Vec2{ 0, 2 }, 8)
				.draw(CandidateWindowColor)
				.drawFrame(1, 0, CandidateWindowFrameColor);

			{
				int32 currentIndex = cadidateState.pageStartIndex;

				for (const auto& candidate : cadidateState.candidates)
				{
					const bool selected = (currentIndex == cadidateState.selectedIndex);

					const Vec2 itemPos{ pos.x, (pos.y + (currentIndex - cadidateState.pageStartIndex) * candidateItemHeight) };

					if (selected)
					{
						RectF{ itemPos, (boxWidth - CandidateMinimapWidth), candidateItemHeight }
							.stretched(-1, 0)
							.draw(CandidateSelectedBackgroundColor);
					}

					if (candidate)
					{
						font(candidate).draw(itemPos.movedBy(CandidatePadding, (CandidateMargin * 0.5 - 1.0)), CandidateTextColor);
					}

					++currentIndex;
				}
			}

			// minimap
			{
				if (cadidateState.pageStartIndex != 0)
				{
					const Vec2 scrollPos{ (pos.x + boxWidth - CandidateMinimapWidth * 0.5 - 1), (pos.y + 0 * candidateItemHeight + 11) };
					scrollPos.asCircle(3.5).draw(CandidateMinimapColor);
					scrollPos.movedBy(0, 8).asCircle(2.8).draw(CandidateMinimapColor);
					scrollPos.movedBy(0, 15).asCircle(2.25).draw(CandidateMinimapColor);
				}

				if ((cadidateState.pageStartIndex + cadidateState.pageSize) != cadidateState.count)
				{
					const Vec2 scrollPos{ (pos.x + boxWidth - CandidateMinimapWidth * 0.5 - 1), (pos.y + cadidateState.pageSize * candidateItemHeight - 9) };
					scrollPos.asCircle(3.5).draw(CandidateMinimapColor);
					scrollPos.movedBy(0, -8).asCircle(2.8).draw(CandidateMinimapColor);
					scrollPos.movedBy(0, -15).asCircle(2.25).draw(CandidateMinimapColor);
				}
			}

		# endif
		}

		namespace detail
		{
			static void TextAreaDraw(const TextAreaEditState& text, const Font& font, const int32 fontHeight, const RectF& region,
				const RectF& textRenderRegion, const double textRenderRegionBottomY,
				const double textCursorLineX, const double textCursorLineY0, const double textCursorLineY1,
				const String& editingText, const Vec2& editingTextPos, const double maxScroll, const bool enabled)
			{
				// テキストエリアの描画
				if (enabled)
				{
					if (text.active)
					{
						region
							.draw()
							.drawFrame(0.0, 1.5, ColorF{ 0.35, 0.7, 1.0, 0.75 })
							.drawFrame(2.5, 0.0, ColorF{ 0.35, 0.7, 1.0 });
					}
					else
					{
						region
							.draw()
							.drawFrame(2.0, 0.0, ColorF{ 0.5 });
					}
				}
				else
				{
					region
						.draw(ColorF{ 0.9 })
						.drawFrame(2.0, 0.0, ColorF{ 0.67 });
				}

				// テキスト入力カーソルの描画
				if (text.active && enabled)
				{
					const bool showCursor = (text.cursorStopwatch.ms() % 1200 < 600)
						|| (text.leftPressStopwatch.isRunning() && (text.leftPressStopwatch < SecondsF{ 0.5 }))
						|| (text.rightPressStopwatch.isRunning() && (text.rightPressStopwatch < SecondsF{ 0.5 }))
						|| (text.upPressStopwatch.isRunning() && (text.upPressStopwatch < SecondsF{ 0.5 }))
						|| (text.downPressStopwatch.isRunning() && (text.downPressStopwatch < SecondsF{ 0.5 }));

					if (showCursor)
					{
						if ((textCursorLineY0 < textRenderRegionBottomY)
							&& (textRenderRegion.y < textCursorLineY1))
						{
							const double x = (Math::Ceil(textCursorLineX) - 0.5);
							Line{ x, textCursorLineY0, x, textCursorLineY1 }.stretched(-2).draw(1, Palette::Black);
						}
					}
				}

				{
					const ColorF textColor = GetTextColor(enabled);
					const auto& pixelShader = Font::GetPixelShader(font.method());

					// テキストの描画
					{
						const ScopedCustomShader2D shader{ pixelShader };

						for (const auto& clipInfo : text.clipInfos)
						{
							const auto& glyph = text.glyphs[clipInfo.index];

							if ((glyph.codePoint == U'\t') || (glyph.codePoint == U'\n'))
							{
								continue;
							}

							glyph.texture.drawClipped(clipInfo.pos, clipInfo.clipRect, textColor);
						}
					}

					if (editingText)
					{
						// 変換テキストとその領域の取得
						const Array<Glyph> editingGlyphs = font.getGlyphs(editingText);
						Array<Vec2> editingGlyphPositions(editingGlyphs.size());
						{
							Vec2 penPos = editingTextPos;

							for (size_t i = 0; i < editingGlyphs.size(); ++i)
							{
								const auto& glyph = editingGlyphs[i];
								editingGlyphPositions[i] = (penPos + glyph.getOffset());
								penPos.x += glyph.xAdvance;
							}
						}

						// 変換テキスト背景の描画
						if (editingGlyphs)
						{
							const auto& firstGlyph = editingGlyphs.front();
							const auto& lastGlyph = editingGlyphs.back();
							const Vec2 pos = (editingGlyphPositions.front() - firstGlyph.getOffset());
							const double w = ((editingGlyphPositions.back().x - lastGlyph.getOffset().x + lastGlyph.xAdvance) - pos.x);
							RectF{ pos, w, fontHeight }.draw(TextAreaEditingTextBackgroundColor);

							// 変換テキストの選択範囲の描画
							{
							# if SIV3D_PLATFORM(WINDOWS)

								const std::pair<int32, int32> editingTarget = Platform::Windows::TextInput::GetCursorIndex();

							# elif SIV3D_PLATFORM(WEB)

								const std::pair<int32, int32> editingTarget = Platform::Web::TextInput::GetCandicateCursorIndex();

							# else

								const std::pair<int32, int32> editingTarget{ -1, 0 };

							# endif

								if (editingTarget.second && ((editingTarget.first + editingTarget.second) <= editingGlyphPositions.size()))
								{
									const int32 firstIndex = editingTarget.first;
									const int32 lastIndex = (editingTarget.first + editingTarget.second - 1);
									const double x0 = editingGlyphPositions[firstIndex].x;
									const double x1 = editingGlyphPositions[lastIndex].x + editingGlyphs[lastIndex].xAdvance;
									RectF{ x0, (pos.y + fontHeight - 2), (x1 - x0), 2 }.draw(ActiveTextColor);
								}
							}
						}

						// 変換テキストの描画
						{
							const ScopedCustomShader2D shader{ pixelShader };

							for (size_t i = 0; i < editingGlyphs.size(); ++i)
							{
								const auto& glyph = editingGlyphs[i];
								glyph.texture.draw(editingGlyphPositions[i], textColor);
							}
						}
					}
				}

				// スクロールバーの描画
				if (maxScroll)
				{
					const RectF scrollRegion = RectF{ textRenderRegion.tr().movedBy(2, 0), TextAreaScrollBarWidth, textRenderRegion.h }.stretched(0, -2);
					const double scrollBarHeight = Max(((scrollRegion.h / (scrollRegion.h - maxScroll)) * scrollRegion.h), TextAreaScrollBarMinHeight);
					const double scrollBaroffset = ((scrollRegion.h - scrollBarHeight) * (text.scrollY / maxScroll));
					RectF{ scrollRegion.pos.x, (scrollRegion.pos.y + scrollBaroffset), scrollRegion.w, scrollBarHeight }.rounded(TextAreaScrollBarWidth * 0.5).draw(TextAreaScrollBarColor);
				}
			}
		}
	}
}
