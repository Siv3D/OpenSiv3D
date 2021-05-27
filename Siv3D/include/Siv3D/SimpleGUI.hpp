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

# pragma once
# include "Common.hpp"
# include "Optional.hpp"
# include "2DShapes.hpp"
# include "Unspecified.hpp"
# include "TextEditState.hpp"

namespace s3d
{
	namespace SimpleGUI
	{
		[[nodiscard]]
		RectF HeadlineRegion(const String& text, const Vec2& pos, const Optional<double>& width = unspecified);

		void Headline(const String& text, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF ButtonRegion(const String& label, const Vec2& pos, const Optional<double>& width = unspecified);

		[[nodiscard]]
		RectF ButtonRegionAt(const String& label, const Vec2& center, const Optional<double>& width = unspecified);

		/// @brief ボタンを表示します。
		/// @param label ボタンに書かれるテキスト
		/// @param pos ボタンの左上の座標
		/// @param width ボタンの幅。`unspecified` の場合はテキストに合わせて自動で決定
		/// @param enabled ボタンの操作を有効にするか
		/// @return このボタンが押された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool Button(const String& label, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		/// @brief ボタンを表示します。
		/// @param label ボタンに書かれるテキスト
		/// @param center ボタンの中心の座標
		/// @param width ボタンの幅（ピクセル）。`unspecified` の場合はテキストに合わせて自動で決定
		/// @param enabled ボタンの操作を有効にするか
		/// @return このボタンが押された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool ButtonAt(const String& label, const Vec2& center, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF SliderRegion(const Vec2& pos, double labelWidth = 80.0, double sliderWidth = 120.0);

		[[nodiscard]]
		RectF SliderRegionAt(const Vec2& center, double labelWidth = 80.0, double sliderWidth = 120.0);

		/// @brief スライダーを表示します。（値の範囲は [0.0, 1.0]）
		/// @param value スライダーで操作する値
		/// @param pos スライダーの左上の座標
		/// @param sliderWidth スライダーの幅（ピクセル）
		/// @param enabled スライダーの操作を有効にするか
		/// @return スライダーが操作された場合 true, それ以外の場合は false
		bool Slider(double& value, const Vec2& pos, double sliderWidth = 120.0, bool enabled = true);

		/// @brief スライダーを表示します。
		/// @param value スライダーで操作する値
		/// @param min 値の最小値
		/// @param max 値の最大値
		/// @param pos スライダーの左上の座標
		/// @param sliderWidth スライダーの幅（ピクセル）
		/// @param enabled スライダーの操作を有効にするか
		/// @return スライダーが操作された場合 true, それ以外の場合は false
		bool Slider(double& value, double min, double max, const Vec2& pos, double sliderWidth = 120.0, bool enabled = true);

		/// @brief テキスト付きのスライダーを表示します。（値の範囲は [0.0, 1.0]）
		/// @param label スライダーの左に表示するテキスト
		/// @param value スライダーで操作する値
		/// @param pos スライダーの左上の座標
		/// @param labelWidth テキスト領域の幅（ピクセル）
		/// @param sliderWidth スライダーの幅（ピクセル）
		/// @param enabled スライダーの操作を有効にするか
		/// @return スライダーが操作された場合 true, それ以外の場合は false
		bool Slider(const String& label, double& value, const Vec2& pos, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		/// @brief テキスト付きのスライダーを表示します。
		/// @param label スライダーの左に表示するテキスト
		/// @param value スライダーで操作する値
		/// @param min 値の最小値
		/// @param max 値の最大値
		/// @param pos スライダーの左上の座標
		/// @param labelWidth テキスト領域の幅（ピクセル）
		/// @param sliderWidth ライダーの幅（ピクセル）
		/// @param enabled スライダーの操作を有効にするか
		/// @return スライダーが操作された場合 true, それ以外の場合は false
		bool Slider(const String& label, double& value, double min, double max, const Vec2& pos, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(double& value, const Vec2& center, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(double& value, double min, double max, const Vec2& center, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(const String& label, double& value, const Vec2& center, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(const String& label, double& value, double min, double max, const Vec2& center, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		[[nodiscard]]
		RectF VerticalSliderRegion(const Vec2& pos, double sliderHeight = 120.0);

		[[nodiscard]]
		RectF VerticalSliderRegionAt(const Vec2& center, double sliderHeight = 120.0);

		bool VerticalSlider(double& value, const Vec2& pos, double sliderHeight = 120.0, bool enabled = true);

		bool VerticalSlider(double& value, double min, double max, const Vec2& pos, double sliderHeight = 120.0, bool enabled = true);

		bool VerticalSliderAt(double& value, const Vec2& center, double sliderHeight = 120.0, bool enabled = true);

		bool VerticalSliderAt(double& value, double min, double max, const Vec2& center, double sliderHeight = 120.0, bool enabled = true);

		[[nodiscard]]
		RectF CheckBoxRegion(const String& label, const Vec2& pos, const Optional<double>& width = unspecified);

		[[nodiscard]]
		RectF CheckBoxRegionAt(const String& label, const Vec2& center, const Optional<double>& width = unspecified);

		/// @brief チェックボックスを表示します。
		/// @param checked チェックボックスで操作する bool 値
		/// @param label チェックボックスの右横に表示するテキスト
		/// @param pos チェックボックスの左上の座標
		/// @param width チェックボックス領域の幅（ピクセル）
		/// @param enabled チェックボックスの操作を有効にするか
		/// @return チェックボックスが操作された場合 true, それ以外の場合は false
		bool CheckBox(bool& checked, const String& label, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		bool CheckBoxAt(bool& checked, const String& label, const Vec2& center, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF RadioButtonsRegion(const Array<String>& options, const Vec2& pos, const Optional<double>& width = unspecified);

		[[nodiscard]]
		RectF RadioButtonsRegionAt(const Array<String>& options, const Vec2& center, const Optional<double>& width = unspecified);

		bool RadioButtons(size_t& index, const Array<String>& options, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		bool RadioButtonsAt(size_t& index, const Array<String>& options, const Vec2& center, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF HorizontalRadioButtonsRegion(const Array<String>& options, const Vec2& pos, const Optional<double>& itemWidth = unspecified);

		[[nodiscard]]
		RectF HorizontalRadioButtonsRegionAt(const Array<String>& options, const Vec2& center, const Optional<double>& itemWidth = unspecified);

		bool HorizontalRadioButtons(size_t& index, const Array<String>& options, const Vec2& pos, const Optional<double>& itemWidth = unspecified, bool enabled = true);

		bool HorizontalRadioButtonsAt(size_t& index, const Array<String>& options, const Vec2& center, const Optional<double>& itemWidth = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF TextBoxRegion(const Vec2& pos, double width = 200.0);

		[[nodiscard]]
		RectF TextBoxRegionAt(const Vec2& center, double width = 200.0);

		bool TextBox(TextEditState& text, const Vec2& pos, double width = 200.0, const Optional<size_t>& maxChars = unspecified, bool enabled = true);

		bool TextBoxAt(TextEditState& text, const Vec2& center, double width = 200.0, const Optional<size_t>& maxChars = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF ColorPickerRegion(const Vec2& pos);

		[[nodiscard]]
		RectF ColorPickerRegionAt(const Vec2& center);

		bool ColorPicker(HSV& hsv, const Vec2& pos, bool enabled = true);

		bool ColorPickerAt(HSV& hsv, const Vec2& center, bool enabled = true);
	}
}
