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
	}

	namespace SimpleGUI
	{
		RectF ButtonRegion(const String& label, const Vec2& pos, const Optional<int32>& minimumWidth)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = minimumWidth.value_or(font(label).region().w + 40);

			return RectF(pos, width, 36);
		}

		RectF ButtonRegionAt(const String& label, const Vec2& center, const Optional<int32>& minimumWidth)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = minimumWidth.value_or(font(label).region().w + 40);

			return RectF(Arg::center = center, width, 36);
		}

		bool Button(const String& label, const Vec2& pos, const Optional<int32>& minimumWidth, const bool enabled)
		{
			const Vec2 center = ButtonRegion(label, pos, minimumWidth).center();

			return ButtonAt(label, center, minimumWidth, enabled);
		}

		bool ButtonAt(const String& label, const Vec2& center, const Optional<int32>& minimumWidth, const bool enabled)
		{
			const Font font = detail::GetSimpleGUIFont();

			const double width = minimumWidth.value_or(font(label).region().w + 40);

			const RectF rect(Arg::center = center, width, 36);

			const bool mouseOver = enabled && rect.mouseOver();
			const bool pushed = mouseOver && Cursor::OnClientRect() && MouseL.down();

			if (enabled)
			{
				rect.rounded(3.2)
					.draw(mouseOver ? ColorF(0.92, 0.96, 1.0) : ColorF(1.0))
					.drawFrame(1, 0, ColorF(0.67, pushed ? 0.0 : 1.0));

				font(label).drawAt(center.asPoint(), ColorF(0.25));
			}
			else
			{
				rect.rounded(3.2)
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

		bool Slider(const String& label, double& value, const Vec2& pos, const double labelWidth, const double sliderWidth, const bool enabled)
		{
			return Slider(label, value, 0.0, 1.0, pos, labelWidth, sliderWidth, enabled);
		}

		bool Slider(const String& label, double& value, double min, double max, const Vec2& pos, const double labelWidth, const double sliderWidth, const bool enabled)
		{
			const Vec2 center = SliderRegion(pos, labelWidth, sliderWidth).center();

			return SliderAt(label, value, min, max, center, labelWidth, sliderWidth, enabled);
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

			const double fill = (value - min) / (max - min);
			const RectF fillRect(sliderRect.pos, sliderRect.w * fill, sliderRect.h);
			const RoundRect fillRoundRect = fillRect.rounded(2);

			const RectF smallRect(Arg::center(actualSliderRegionX0 + actualSliderRegionW * fill, center.y), 16, 24);
			const bool mouseOver = enabled && smallRect.mouseOver();

			region.draw(ColorF(1.0));

			if (enabled)
			{
				font(label).draw(Arg::leftCenter = region.leftCenter().movedBy(8, 0), ColorF(0.25));

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

			const RectF sliderRectExtended = sliderRect.stretched(4, 10);

			if (enabled && Cursor::OnClientRect() && (sliderRectExtended.mouseOver() || smallRect.mouseOver()))
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			const double previousValue = value;
			value = Clamp(value, min, max);

			if (enabled && Cursor::OnClientRect() && sliderRectExtended.leftPressed())
			{
				const double pos = Cursor::PosF().x - actualSliderRegionX0;
				const double posN = Math::Saturate(pos / actualSliderRegionW);
				value = min + posN * (max - min);
			}

			return (value != previousValue);
		}
	}
}
