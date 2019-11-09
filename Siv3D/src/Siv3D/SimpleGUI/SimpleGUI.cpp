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

# include <Siv3D/SimpleGUI.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/HSV.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/TexturedCircle.hpp>
# include <Siv3D/Triangle.hpp>
# include <Siv3D/RoundRect.hpp>
# include <Siv3D/KeyConjunction.hpp>
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/TextInput.hpp>
# include <Siv3D/Clipboard.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3DEngine.hpp>
# include <GUI/IGUI.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]] const Font& GetSimpleGUIFont()
		{
			return Siv3DEngine::Get<ISiv3DGUI>()->getDefaultGUIFont();
		}

		constexpr int32 CheckBoxSize = 24;
		constexpr int32 CheckBoxPadding = 8;
		constexpr int32 RadioButtonSize = 19;
		constexpr int32 RadioButtonPadding = 8;
		constexpr int32 TextBoxHeight = 36;
		constexpr Size  ColorPickerSize(160, 116);
	}

	TextEditState::TextEditState(const String& defaultText)
		: text(defaultText)
		, cursorPos(defaultText.size())
	{
	
	}

	void TextEditState::clear()
	{
		text.clear();
		cursorPos = 0;
		leftPressStopwatch.reset();
		rightPressStopwatch.reset();
		cursorStopwatch.reset();
	}

	namespace SimpleGUI
	{
		RectF ButtonRegion(const String& label, const Vec2& pos, const Optional<double>& _width)
		{
			const Font& font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(font(label).region().w + 40);

			return RectF(pos, width, 36);
		}

		RectF ButtonRegionAt(const String& label, const Vec2& center, const Optional<double>& _width)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(font(label).region().w + 40);

			return RectF(Arg::center = center, width, 36);
		}

		bool Button(const String& label, const Vec2& pos, const Optional<double>& _width, const bool enabled)
		{
			const Vec2 center = ButtonRegion(label, pos, _width).center();

			return ButtonAt(label, center, _width, enabled);
		}

		bool ButtonAt(const String& label, const Vec2& center, const Optional<double>& _width, const bool enabled)
		{
			const Font font = detail::GetSimpleGUIFont();

			const int32 labelWidth = font(label).region().w;
			const double width = _width.value_or(labelWidth + 40);

			const RectF rect(Arg::center = center, width, 36);
			const Vec2 labelPos(static_cast<int32>(rect.x + (width - labelWidth) / 2), center.y - font.height() / 2);

			const bool mouseOver = enabled && rect.mouseOver();
			const bool pushed = mouseOver && Cursor::OnClientRect() && MouseL.down();

			if (enabled)
			{
				rect.rounded(4.8)
					.draw(mouseOver ? ColorF(0.92, 0.96, 1.0) : ColorF(1.0))
					.drawFrame(1, 0, ColorF(0.67, pushed ? 0.0 : 1.0));

				font(label).draw(labelPos, ColorF(0.2));
			}
			else
			{
				rect.rounded(4.8)
					.draw(ColorF(0.92))
					.drawFrame(1, 0, ColorF(0.67));

				font(label).draw(labelPos, ColorF(0.67));
			}

			if (mouseOver)
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			return pushed;
		}

		RectF SliderRegion(const Vec2& pos, double labelWidth, double sliderWidth)
		{
			labelWidth = std::max(labelWidth, 0.0);

			sliderWidth = std::max(sliderWidth, 20.0);

			const double width = labelWidth + sliderWidth;

			return RectF(pos, width, 36);
		}

		RectF SliderRegionAt(const Vec2& center, double labelWidth, double sliderWidth)
		{
			labelWidth = std::max(labelWidth, 0.0);

			sliderWidth = std::max(sliderWidth, 20.0);

			const double width = labelWidth + sliderWidth;

			return RectF(Arg::center = center, width, 36);
		}

		bool Slider(double& value, const Vec2& pos, const double sliderWidth, const bool enabled)
		{
			return Slider(String(), value, 0.0, 1.0, pos, 0.0, sliderWidth, enabled);
		}

		bool Slider(double& value, const double min, const double max, const Vec2& pos, const double sliderWidth, const bool enabled)
		{
			return Slider(String(), value, min, max, pos, 0.0, sliderWidth, enabled);
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
			return SliderAt(String(), value, 0.0, 1.0, center, 0.0, sliderWidth, enabled);
		}

		bool SliderAt(double& value, const double min, const double max, const Vec2& center, const double sliderWidth, const bool enabled)
		{
			return SliderAt(String(), value, min, max, center, 0.0, sliderWidth, enabled);
		}

		bool SliderAt(const String& label, double& value, const Vec2& center, const double labelWidth, const double sliderWidth, const bool enabled)
		{
			return SliderAt(label, value, 0.0, 1.0, center, labelWidth, sliderWidth, enabled);
		}

		bool SliderAt(const String& label, double& value, double min, double max, const Vec2& center, const double _labelWidth, const double _sliderWidth, const bool enabled)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double labelWidth = std::max(_labelWidth, 0.0);
			const double sliderWidth = std::max(_sliderWidth, 40.0);
			const double width = labelWidth + sliderWidth;
			const RectF region(Arg::center = center, width, 36);
			const Vec2 labelPos(region.x + 8, center.y - font.height() / 2);

			const double sliderRegionX0 = region.x + labelWidth + 8;
			const double sliderRegionX1 = region.x + region.w - 8;
			const double sliderRegionW = (sliderRegionX1 - sliderRegionX0);

			const double actualSliderRegionX0 = sliderRegionX0 + 8;
			const double actualSliderRegionX1 = sliderRegionX1 - 8;
			const double actualSliderRegionW = (actualSliderRegionX1 - actualSliderRegionX0);

			const RectF sliderRect = RectF(Arg::leftCenter(sliderRegionX0, center.y), sliderRegionW, 6);
			const RoundRect baseRoundRect = sliderRect.rounded(2);

			const double previousValue = value;
			const auto[min_, max_] = std::minmax(min, max);
			value = Clamp(value, min_, max_);

			const double fill = (value - min) / (max - min);
			const RectF fillRect(sliderRect.pos, sliderRect.w * fill, sliderRect.h);
			const RoundRect fillRoundRect = fillRect.rounded(2);

			const RectF smallRect(Arg::center(actualSliderRegionX0 + actualSliderRegionW * fill, center.y), 16, 24);
			const bool mouseOver = enabled && smallRect.mouseOver();

			region.draw(ColorF(1.0));

			if (enabled)
			{
				font(label).draw(labelPos, ColorF(0.2));

				baseRoundRect.draw(ColorF(0.33));
				fillRoundRect.draw(ColorF(0.35, 0.7, 1.0));

				smallRect.rounded(4.2)
					.draw(mouseOver ? ColorF(0.92, 0.96, 1.0) : ColorF(1.0))
					.drawFrame(0.5, 0.5, ColorF(0.33));
			}
			else
			{
				font(label).draw(labelPos, ColorF(0.67));

				baseRoundRect.draw(ColorF(0.75));
				fillRoundRect.draw(ColorF(0.75, 0.85, 1.0));

				smallRect.rounded(4.2)
					.draw(ColorF(0.92))
					.drawFrame(0.5, 0.5, ColorF(0.67));
			}

			const RectF sliderRectExtended = sliderRect.stretched(4, 12);

			if (enabled && Cursor::OnClientRect() && (sliderRectExtended.mouseOver() || smallRect.mouseOver()))
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			if (enabled && Cursor::OnClientRect() && sliderRectExtended.leftPressed())
			{
				const double pos = Cursor::PosF().x - actualSliderRegionX0;
				const double posN = Math::Saturate(pos / actualSliderRegionW);
				value = min + posN * (max - min);
			}

			return (value != previousValue);
		}

		RectF VerticalSliderRegion(const Vec2& pos, double sliderHeight)
		{
			sliderHeight = std::max(sliderHeight, 20.0);

			return RectF(pos, 36, sliderHeight);
		}

		RectF VerticalSliderRegionAt(const Vec2& center, double sliderHeight)
		{
			sliderHeight = std::max(sliderHeight, 20.0);

			return RectF(Arg::center = center, 36, sliderHeight);
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
			const double sliderWidth = std::max(_sliderHeight, 40.0);
			const double height = sliderWidth;
			const RectF region(Arg::center = center, 36, height);

			const double sliderRegionY0 = region.y + 8;
			const double sliderRegionY1 = region.y + region.h - 8;
			const double sliderRegionH = (sliderRegionY1 - sliderRegionY0);

			const double actualSliderRegionY0 = sliderRegionY0 + 8;
			const double actualSliderRegionY1 = sliderRegionY1 - 8;
			const double actualSliderRegionH = (actualSliderRegionY1 - actualSliderRegionY0);

			const RectF sliderRect = RectF(Arg::topCenter(center.x, sliderRegionY0), 6, sliderRegionH);
			const RoundRect baseRoundRect = sliderRect.rounded(2);

			const double previousValue = value;
			const auto[min_, max_] = std::minmax(min, max);
			value = Clamp(value, min_, max_);

			const double fill = (value - min) / (max - min);
			const RectF fillRect(Arg::bottomLeft = sliderRect.bl(), sliderRect.w, sliderRect.h * fill);
			const RoundRect fillRoundRect = fillRect.rounded(2);

			const RectF smallRect(Arg::center(center.x, actualSliderRegionY1 - actualSliderRegionH * fill), 24, 16);
			const bool mouseOver = enabled && smallRect.mouseOver();

			region.draw(ColorF(1.0));

			if (enabled)
			{
				baseRoundRect.draw(ColorF(0.33));
				fillRoundRect.draw(ColorF(0.35, 0.7, 1.0));

				smallRect.rounded(4.2)
					.draw(mouseOver ? ColorF(0.92, 0.96, 1.0) : ColorF(1.0))
					.drawFrame(0.5, 0.5, ColorF(0.33));
			}
			else
			{
				baseRoundRect.draw(ColorF(0.75));
				fillRoundRect.draw(ColorF(0.75, 0.85, 1.0));

				smallRect.rounded(4.2)
					.draw(ColorF(0.92))
					.drawFrame(0.5, 0.5, ColorF(0.67));
			}

			const RectF sliderRectExtended = sliderRect.stretched(12, 4);

			if (enabled && Cursor::OnClientRect() && (sliderRectExtended.mouseOver() || smallRect.mouseOver()))
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			if (enabled && Cursor::OnClientRect() && sliderRectExtended.leftPressed())
			{
				const double pos = actualSliderRegionY1 - Cursor::PosF().y;
				const double posN = Math::Saturate(pos / actualSliderRegionH);
				value = min + posN * (max - min);
			}

			return (value != previousValue);
		}

		RectF CheckBoxRegion(const String& label, const Vec2& pos, const Optional<double>& _width)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(detail::CheckBoxPadding * 3 + detail::CheckBoxSize + font(label).region().w);

			return RectF(pos, width, 36);
		}

		RectF CheckBoxRegionAt(const String& label, const Vec2& center, const Optional<double>& _width)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(detail::CheckBoxPadding * 3 + detail::CheckBoxSize + font(label).region().w);

			return RectF(Arg::center = center, width, 36);
		}

		bool CheckBox(bool& checked, const String& label, const Vec2& pos, const Optional<double>& _width, const bool enabled)
		{
			const Vec2 center = CheckBoxRegion(label, pos, _width).center();

			return CheckBoxAt(checked, label, center, _width, enabled);
		}

		bool CheckBoxAt(bool& checked, const String& label, const Vec2& center, const Optional<double>& _width, const bool enabled)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(detail::CheckBoxPadding * 3 + detail::CheckBoxSize + font(label).region().w);
			const RectF region(Arg::center = center, width, 36);
			const RectF checkBox(Arg::leftCenter(region.x + 8, center.y), detail::CheckBoxSize);
			const Vec2 labelPos(static_cast<int32>(region.x + detail::CheckBoxPadding * 2 + detail::CheckBoxSize), center.y - font.height() / 2);
			const bool mouseOver = enabled && checkBox.mouseOver();

			region.draw(ColorF(1.0));

			if (enabled)
			{
				if (checked)
				{
					checkBox.rounded(3.2).draw(mouseOver ? ColorF(0.45, 0.8, 1.0) : ColorF(0.35, 0.7, 1.0));

					font(U"✔").drawAt(checkBox.center());
				}
				else
				{
					checkBox.rounded(3.2).draw(ColorF(0.67));

					checkBox.stretched(-1.25).rounded(3.2).draw(mouseOver ? ColorF(0.92, 0.96, 1.0) : ColorF(0.95));
				}

				font(label).draw(labelPos, ColorF(0.2));
			}
			else
			{
				if (checked)
				{
					checkBox.rounded(3.2).draw(ColorF(0.75, 0.85, 1.0));

					font(U"✔").drawAt(checkBox.center());
				}
				else
				{
					checkBox.rounded(3.2).draw(ColorF(0.75));

					checkBox.stretched(-1.25).rounded(3.2).draw(ColorF(0.8));
				}

				font(label).draw(labelPos, ColorF(0.67));
			}

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
			const Font font = detail::GetSimpleGUIFont();

			double width = 0.0;

			if (_width)
			{
				width = _width.value();
			}
			else
			{
				for (const auto& option : options)
				{
					width = std::max<double>(width, detail::RadioButtonPadding * 3 + detail::RadioButtonSize + font(option).region().w);
				}
			}

			return RectF(pos, width, std::max(0.0, options.size() * 40 - 4.0));
		}

		RectF RadioButtonsRegionAt(const Array<String>& options, const Vec2& center, const Optional<double>& _width)
		{
			const Font font = detail::GetSimpleGUIFont();

			double width = 0.0;

			if (_width)
			{
				width = _width.value();
			}
			else
			{
				for (const auto& option : options)
				{
					width = std::max<double>(width, detail::RadioButtonPadding * 3 + detail::RadioButtonSize + font(option).region().w);
				}
			}

			return RectF(Arg::center = center, width, std::max(0.0, options.size() * 40 - 4.0));
		}

		bool RadioButtons(size_t& index, const Array<String>& options, const Vec2& pos, const Optional<double>& _width, const bool enabled)
		{
			const Vec2 center = RadioButtonsRegion(options, pos, _width).center();

			return RadioButtonsAt(index, options, center, _width, enabled);
		}

		bool RadioButtonsAt(size_t& index, const Array<String>& options, const Vec2& center, const Optional<double>& _width, bool enabled)
		{
			const Font font = detail::GetSimpleGUIFont();

			const RectF region = RadioButtonsRegionAt(options, center, _width);

			region.draw();

			bool hasChanged = false;
			size_t row = 0;
			const int32 labelPosX = static_cast<int32>(region.x + detail::RadioButtonPadding * 2 + detail::RadioButtonSize);		
			const double baseY = center.y - (static_cast<double>(options.size()) * 40 - 4) / 2 + 18;

			for (const auto& option : options)
			{
				const RectF radioButtonBox(Arg::leftCenter(region.x + detail::RadioButtonPadding, baseY + row * 40), detail::RadioButtonSize);
				const Circle radioButton(radioButtonBox.center(), detail::RadioButtonSize / 2.0);
				const Vec2 labelPos(labelPosX, radioButton.y - font.height() / 2 - 1);
				const bool mouseOver = enabled && radioButtonBox.mouseOver();
				const bool checked = (index == row);

				if (enabled)
				{
					if (checked)
					{
						radioButton.drawFrame(2, 0.5, ColorF(0.35, 0.7, 1.0));

						radioButton.stretched(-5).draw(ColorF(0.35, 0.7, 1.0));
					}
					else
					{
						radioButton.drawFrame(2, 0.5, ColorF(0.5));
					}

					font(option).draw(labelPos, ColorF(0.2));
				}
				else
				{
					if (checked)
					{
						radioButton.drawFrame(2, 0.5, ColorF(0.75));

						radioButton.stretched(-5).draw(ColorF(0.75));
					}
					else
					{
						radioButton.drawFrame(2, 0.5, ColorF(0.75));
					}

					font(option).draw(labelPos, ColorF(0.67));
				}

				if (mouseOver && Cursor::OnClientRect())
				{
					Cursor::RequestStyle(CursorStyle::Hand);
				}

				if (enabled && Cursor::OnClientRect() && radioButtonBox.leftClicked())
				{
					if (index != row)
					{
						index = row;

						hasChanged = true;
					}
				}

				++row;
			}

			return hasChanged;
		}

		RectF TextBoxRegion(const Vec2& pos, double width)
		{
			width = std::max(width, 40.0);

			return RectF(pos, width, detail::TextBoxHeight);
		}

		RectF TextBoxRegionAt(const Vec2& center, double width)
		{
			width = std::max(width, 40.0);

			return RectF(Arg::center = center, width, detail::TextBoxHeight);
		}

		bool TextBox(TextEditState& text, const Vec2& pos, double width, const Optional<size_t>& maxChars, const bool enabled)
		{
			width = std::max(width, 40.0);

			return TextBoxAt(text, pos + Vec2(width * 0.5, 18.0), width, maxChars, enabled);
		}

		bool TextBoxAt(TextEditState& text, const Vec2& center, const double _width, const Optional<size_t>& maxChars, const bool enabled)
		{
			const Font font = detail::GetSimpleGUIFont();
			const double width = std::max(_width, 40.0);
			const RectF region(Arg::center = center, width, detail::TextBoxHeight);
			const Vec2 textPos(region.x + 8, center.y - font.height() / 2);

			text.cursorPos = std::min(text.cursorPos, text.text.size());

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

					for (auto glyph : font(textHeader))
					{
						glyph.texture.draw(pos + glyph.offset, ColorF(0.2));
						pos.x += glyph.xAdvance;
					}

					double begX = pos.x, begY = 0, endX = pos.x;

					for (auto glyph : font(editingText))
					{
						if (glyph.index == editingCursorIndex)
						{
							begX = pos.x;
							begY = pos.y + fontHeight;
						}
						else if (hasEditingTarget && glyph.index == editingCursorIndex + editingTargetlength - 1)
						{
							endX = pos.x + glyph.xAdvance;
						}

						glyph.texture.draw(pos + glyph.offset, ColorF(0.2));
						pos.x += glyph.xAdvance;
					}

					if (hasEditingTarget)
					{
						Line(begX, begY, endX, begY).movedBy(0, -2).draw(2, ColorF(0.2));
					}

					const double cursorPosX = pos.x;

					for (auto glyph : font(textTail))
					{
						glyph.texture.draw(pos + glyph.offset, ColorF(0.2));
						pos.x += glyph.xAdvance;
					}

					const bool showCursor = (text.cursorStopwatch.ms() % 1200 < 600)
						|| (text.leftPressStopwatch.isRunning() && text.leftPressStopwatch < SecondsF(0.5))
						|| (text.rightPressStopwatch.isRunning() && text.rightPressStopwatch < SecondsF(0.5));

					if (showCursor)
					{
						const RectF cursor(Arg::leftCenter(Vec2(cursorPosX, center.y).asPoint()), 1, 26);
						cursor.draw(ColorF(0.2));
					}
				}
				else
				{
					font(text.text).draw(textPos, ColorF(0.2));
				}
			}
			else
			{
				region
					.draw(ColorF(0.9))
					.drawFrame(2.0, 0.0, ColorF(0.67));

				font(text.text).draw(textPos, ColorF(0.67));
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
				}
				else
				{
					text.active = false;
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
					if (String paste; Clipboard::GetText(paste))
					{
						text.text.insert(text.cursorPos, paste);
						text.cursorPos += paste.size();
					}
				}

				if (maxChars && text.text.size() > maxChars.value())
				{
					text.text.resize(maxChars.value());
					text.cursorPos = std::min(text.cursorPos, maxChars.value());
				}

				if (text.text != previousText)
				{
					text.cursorStopwatch.restart();
				}

				if (const String raw = TextInput::GetRawInput(); raw.includes(U'\r') || raw.includes(U'\t'))
				{
					text.active = false;
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
			return RectF(pos, detail::ColorPickerSize);
		}

		RectF ColorPickerRegionAt(const Vec2& center)
		{
			return RectF(Arg::center = center, detail::ColorPickerSize);
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
			constexpr int32 circleSize = (detail::ColorPickerSize.y - 18);
			const Vec2 circleCenter = center.movedBy(-26 + 4, 0);
			const Circle circle(circleCenter, circleSize / 2);
			const Circle touchCircle = circle.stretched((116 - circleSize) / 2);
			const RectF touchRect(Arg::center = circleCenter, circleSize + 8);
			const bool onCircle = (touchRect.mouseOver() || touchCircle.mouseOver());
			const bool onCircleUpdate = enabled && onCircle && MouseL.pressed();

			if (onCircleUpdate)
			{
				const Vec2 pos = Cursor::PosF();
				const Vec2 dir = (pos - circleCenter);
				const Circular cir(dir);
				const double h = Math::Fmod(Math::ToDegrees(cir.theta) + 360.0, 360.0);
				const double s = std::min((std::min(cir.r, circleSize / 2.0) / ((circleSize - 1) / 2.0)), 1.0);
				hsv.h = h;
				hsv.s = s;
			}

			const RectF valueBox(Arg::center = center.movedBy(56, 0), 24, 96);
			const Vec2 valueBoxBase = valueBox.pos;
			const RectF touchValueBox = valueBox.stretched(8, 8, 8, 4);
			const bool onValueBox = touchValueBox.mouseOver();
			const bool onValueBoxUpdate = enabled && onValueBox && MouseL.pressed();

			if (onValueBoxUpdate)
			{
				const Vec2 pos = Cursor::PosF();
				const double y = pos.y - valueBox.y;
				const double v = Saturate(1.0 - (y / (valueBox.h - 1)));
				hsv.v = v;
			}

			if (enabled && (onCircle || onValueBox))
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			// Background
			{
				region.draw();
				RectF(Arg::center = center, 148, 104).rounded(2.2).draw(ColorF(enabled ? 0.66 : 0.75));
			}

			// HS Circle
			{
				circle(Siv3DEngine::Get<ISiv3DGUI>()->getColorPickerTexture()).draw();

				if (!enabled)
				{
					circle.stretched(1).draw(ColorF(1.0, 0.5));
				}

				const double r = hsv.s * ((circleSize - 1) / 2.0);
				const double theta = ToRadians(hsv.h);
				const Circular cir(r, theta);
				const Vec2 dir = cir.toVec2();
				const ColorF color = HSV(hsv.h, hsv.s, 1.0);

				if (enabled)
				{
					Circle(circleCenter + dir, 5)
						.draw(color)
						.stretched(onCircleUpdate ? 1 : 0)
						.drawFrame(1.0, 1.0, HSV(0.0, 0.0, hsv.s));
				}
				else
				{
					Circle(circleCenter + dir, 5)
						.draw(color)
						.draw(ColorF(1.0, 0.5))
						.drawFrame(1.0, 1.0, ColorF(0.75));
				}
			}

			// V box
			{
				valueBox.draw(Arg::top = HSV(hsv.h, hsv.s, 1.0), Arg::bottom = HSV(hsv.h, hsv.s, 0.0));

				if (!enabled)
				{
					valueBox.draw(ColorF(1.0, 0.5));
				}

				const double y = (1.0 - hsv.v) * valueBox.h;
				const ColorF triangleColor(enabled ? 0.2 : 0.5);
				Triangle(valueBoxBase.movedBy(-6, y), 10, 90_deg).draw(triangleColor);
				Triangle(valueBoxBase.movedBy(valueBox.w + 6, y), 10, 270_deg).draw(triangleColor);
			}

			// Preview
			if (onValueBoxUpdate)
			{
				RectF(Arg::center = circleCenter, 36).draw(HSV(hsv, 1.0));
			}

			return (previousHSV.toColorF() != hsv.toColorF());
		}
	}
}
