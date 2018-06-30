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

# include <Siv3D/SimpleGUI.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/FontAsset.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/RoundRect.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]] Font GetSimpleGUIFont()
		{
			static bool initialized = false;

			if (!initialized)
			{
				FontAsset::Register(U"Siv3D.SimpleGUI", 20, Typeface::Medium);

				initialized = true;
			}

			return FontAsset(U"Siv3D.SimpleGUI");
		}

		constexpr int32 CheckBoxSize = 24;
		constexpr int32 CheckBoxPadding = 8;
	}

	namespace SimpleGUI
	{
		RectF ButtonRegion(const String& label, const Vec2& pos, const Optional<int32>& _width)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(font(label).region().w + 40);

			return RectF(pos, width, 36);
		}

		RectF ButtonRegionAt(const String& label, const Vec2& center, const Optional<int32>& _width)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(font(label).region().w + 40);

			return RectF(Arg::center = center, width, 36);
		}

		bool Button(const String& label, const Vec2& pos, const Optional<int32>& _width, const bool enabled)
		{
			const Vec2 center = ButtonRegion(label, pos, _width).center();

			return ButtonAt(label, center, _width, enabled);
		}

		bool ButtonAt(const String& label, const Vec2& center, const Optional<int32>& _width, const bool enabled)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(font(label).region().w + 40);

			const RectF rect(Arg::center = center, width, 36);

			const bool mouseOver = enabled && rect.mouseOver();
			const bool pushed = mouseOver && Cursor::OnClientRect() && MouseL.down();

			if (enabled)
			{
				rect.rounded(4.4)
					.draw(mouseOver ? ColorF(0.92, 0.96, 1.0) : ColorF(1.0))
					.drawFrame(1, 0, ColorF(0.67, pushed ? 0.0 : 1.0));

				font(label).drawAt(center.asPoint(), ColorF(0.2));
			}
			else
			{
				rect.rounded(4.4)
					.draw(ColorF(0.92))
					.drawFrame(1, 0, ColorF(0.67));

				font(label).drawAt(center.asPoint(), ColorF(0.67));
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
				font(label).draw(Arg::leftCenter = region.leftCenter().movedBy(8, 0), ColorF(0.2));

				baseRoundRect.draw(ColorF(0.33));
				fillRoundRect.draw(ColorF(0.35, 0.7, 1.0));

				smallRect.rounded(4.2)
					.draw(mouseOver ? ColorF(0.92, 0.96, 1.0) : ColorF(1.0))
					.drawFrame(0.5, 0.5, ColorF(0.33));
			}
			else
			{
				font(label).draw(Arg::leftCenter = region.leftCenter().movedBy(8, 0), ColorF(0.67));

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

		RectF CheckBoxRegion(const String& label, const Vec2& pos, const Optional<int32>& _width)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(detail::CheckBoxPadding * 3 + detail::CheckBoxSize + font(label).region().w);

			return RectF(pos, width, 36);
		}

		RectF CheckBoxRegionAt(const String& label, const Vec2& center, const Optional<int32>& _width)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(detail::CheckBoxPadding * 3 + detail::CheckBoxSize + font(label).region().w);

			return RectF(Arg::center = center, width, 36);
		}

		bool CheckBox(bool& checked, const String& label, const Vec2& pos, const Optional<int32>& _width, const bool enabled)
		{
			const Vec2 center = CheckBoxRegion(label, pos, _width).center();

			return CheckBoxAt(checked, label, center, _width, enabled);
		}

		bool CheckBoxAt(bool& checked, const String& label, const Vec2& center, const Optional<int32>& _width, const bool enabled)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = _width.value_or(detail::CheckBoxPadding * 3 + detail::CheckBoxSize + font(label).region().w);
			const RectF region(Arg::center = center, width, 36);
			const RectF checkBox(Arg::leftCenter(region.x + 8, center.y), detail::CheckBoxSize);
			const Vec2 labelPos(region.x + detail::CheckBoxPadding * 2 + detail::CheckBoxSize, center.y);
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

				font(label).draw(Arg::leftCenter = labelPos, ColorF(0.2));
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

				font(label).draw(Arg::leftCenter = labelPos, ColorF(0.67));
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
	}
}
