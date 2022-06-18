//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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
# include "ListBoxState.hpp"

namespace s3d
{
	class Font;

	namespace SimpleGUI
	{
		[[nodiscard]]
		const Font& GetFont() noexcept;

		[[nodiscard]]
		RectF HeadlineRegion(StringView text, const Vec2& pos, const Optional<double>& width = unspecified);

		void Headline(StringView text, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF ButtonRegion(StringView label, const Vec2& pos, const Optional<double>& width = unspecified);

		[[nodiscard]]
		RectF ButtonRegionAt(StringView label, const Vec2& center, const Optional<double>& width = unspecified);

		/// @brief ボタンを表示します。
		/// @param label ボタンに書かれるテキスト
		/// @param pos ボタンの左上の座標
		/// @param width ボタンの幅。`unspecified` の場合はテキストに合わせて自動で決定
		/// @param enabled ボタンの操作を有効にするか
		/// @return このボタンが押された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool Button(StringView label, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		/// @brief ボタンを表示します。
		/// @param label ボタンに書かれるテキスト
		/// @param center ボタンの中心の座標
		/// @param width ボタンの幅（ピクセル）。`unspecified` の場合はテキストに合わせて自動で決定
		/// @param enabled ボタンの操作を有効にするか
		/// @return このボタンが押された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool ButtonAt(StringView label, const Vec2& center, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF SliderRegion(const Vec2& pos, double labelWidth = 80.0, double sliderWidth = 120.0);

		[[nodiscard]]
		RectF SliderRegionAt(const Vec2& center, double labelWidth = 80.0, double sliderWidth = 120.0);

		/// @brief スライダーを表示します。（値の範囲は [0.0, 1.0]）
		/// @param value スライダーで操作する値への参照
		/// @param pos スライダーの左上の座標
		/// @param sliderWidth スライダーの幅（ピクセル）
		/// @param enabled スライダーの操作を有効にするか
		/// @return スライダーが操作された場合 true, それ以外の場合は false
		bool Slider(double& value, const Vec2& pos, double sliderWidth = 120.0, bool enabled = true);

		/// @brief スライダーを表示します。
		/// @param value スライダーで操作する値への参照
		/// @param min 値の最小値
		/// @param max 値の最大値
		/// @param pos スライダーの左上の座標
		/// @param sliderWidth スライダーの幅（ピクセル）
		/// @param enabled スライダーの操作を有効にするか
		/// @return スライダーが操作された場合 true, それ以外の場合は false
		bool Slider(double& value, double min, double max, const Vec2& pos, double sliderWidth = 120.0, bool enabled = true);

		/// @brief テキスト付きのスライダーを表示します。（値の範囲は [0.0, 1.0]）
		/// @param label スライダーの左に表示するテキスト
		/// @param value スライダーで操作する値への参照
		/// @param pos スライダーの左上の座標
		/// @param labelWidth テキスト領域の幅（ピクセル）
		/// @param sliderWidth スライダーの幅（ピクセル）
		/// @param enabled スライダーの操作を有効にするか
		/// @return スライダーが操作された場合 true, それ以外の場合は false
		bool Slider(StringView label, double& value, const Vec2& pos, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		/// @brief テキスト付きのスライダーを表示します。
		/// @param label スライダーの左に表示するテキスト
		/// @param value スライダーで操作する値への参照
		/// @param min 値の最小値
		/// @param max 値の最大値
		/// @param pos スライダーの左上の座標
		/// @param labelWidth テキスト領域の幅（ピクセル）
		/// @param sliderWidth ライダーの幅（ピクセル）
		/// @param enabled スライダーの操作を有効にするか
		/// @return スライダーが操作された場合 true, それ以外の場合は false
		bool Slider(StringView label, double& value, double min, double max, const Vec2& pos, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(double& value, const Vec2& center, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(double& value, double min, double max, const Vec2& center, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(StringView label, double& value, const Vec2& center, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		bool SliderAt(StringView label, double& value, double min, double max, const Vec2& center, double labelWidth = 80.0, double sliderWidth = 120.0, bool enabled = true);

		[[nodiscard]]
		RectF VerticalSliderRegion(const Vec2& pos, double sliderHeight = 120.0);

		[[nodiscard]]
		RectF VerticalSliderRegionAt(const Vec2& center, double sliderHeight = 120.0);

		bool VerticalSlider(double& value, const Vec2& pos, double sliderHeight = 120.0, bool enabled = true);

		bool VerticalSlider(double& value, double min, double max, const Vec2& pos, double sliderHeight = 120.0, bool enabled = true);

		bool VerticalSliderAt(double& value, const Vec2& center, double sliderHeight = 120.0, bool enabled = true);

		bool VerticalSliderAt(double& value, double min, double max, const Vec2& center, double sliderHeight = 120.0, bool enabled = true);

		[[nodiscard]]
		RectF CheckBoxRegion(StringView label, const Vec2& pos, const Optional<double>& width = unspecified);

		[[nodiscard]]
		RectF CheckBoxRegionAt(StringView label, const Vec2& center, const Optional<double>& width = unspecified);

		/// @brief チェックボックスを表示します。
		/// @param checked チェックボックスで操作する bool 値への参照
		/// @param label チェックボックスの右横に表示するテキスト
		/// @param pos チェックボックスの左上の座標
		/// @param width チェックボックス領域の幅（ピクセル）
		/// @param enabled チェックボックスの操作を有効にするか
		/// @return チェックボックスが操作された場合 true, それ以外の場合は false
		bool CheckBox(bool& checked, StringView label, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		/// @brief チェックボックスを表示します。
		/// @param checked チェックボックスで操作する bool 値への参照
		/// @param label チェックボックスの右横に表示するテキスト
		/// @param center チェックボックスの中心座標
		/// @param width チェックボックス領域の幅（ピクセル）
		/// @param enabled チェックボックスの操作を有効にするか
		/// @return チェックボックスが操作された場合 true, それ以外の場合は false
		bool CheckBoxAt(bool& checked, StringView label, const Vec2& center, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF RadioButtonsRegion(const Array<String>& options, const Vec2& pos, const Optional<double>& width = unspecified);

		[[nodiscard]]
		RectF RadioButtonsRegionAt(const Array<String>& options, const Vec2& center, const Optional<double>& width = unspecified);

		/// @brief ラジオボタンを表示します。
		/// @param index ラジオボタンで選択されているアイテムのインデックス値への参照
		/// @param options ラジオボタンのアイテム
		/// @param pos ラジオボタンの左上の座標
		/// @param width ラジオボタンの領域の幅（ピクセル）
		/// @param enabled ラジオボタンの操作を有効にするか
		/// @return ラジオボタンが操作された場合 true, それ以外の場合は false
		bool RadioButtons(size_t& index, const Array<String>& options, const Vec2& pos, const Optional<double>& width = unspecified, bool enabled = true);

		/// @brief ラジオボタンを表示します。
		/// @param index ラジオボタンで選択されているアイテムのインデックス値への参照
		/// @param options ラジオボタンのアイテム
		/// @param center ラジオボタンの中心座標
		/// @param width ラジオボタンの領域の幅（ピクセル）
		/// @param enabled ラジオボタンの操作を有効にするか
		/// @return ラジオボタンが操作された場合 true, それ以外の場合は false
		bool RadioButtonsAt(size_t& index, const Array<String>& options, const Vec2& center, const Optional<double>& width = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF HorizontalRadioButtonsRegion(const Array<String>& options, const Vec2& pos, const Optional<double>& itemWidth = unspecified);

		[[nodiscard]]
		RectF HorizontalRadioButtonsRegionAt(const Array<String>& options, const Vec2& center, const Optional<double>& itemWidth = unspecified);

		/// @brief 水平ラジオボタンを表示します。
		/// @param index ラジオボタンで選択されているアイテムのインデックス値への参照
		/// @param options ラジオボタンのアイテム
		/// @param pos ラジオボタンの左上の座標
		/// @param itemWidth ラジオボタンの各アイテムの幅（ピクセル）
		/// @param enabled ラジオボタンの操作を有効にするか
		/// @return ラジオボタンが操作された場合 true, それ以外の場合は false
		bool HorizontalRadioButtons(size_t& index, const Array<String>& options, const Vec2& pos, const Optional<double>& itemWidth = unspecified, bool enabled = true);

		/// @brief 水平ラジオボタンを表示します。
		/// @param index ラジオボタンで選択されているアイテムのインデックス値への参照
		/// @param options ラジオボタンのアイテム
		/// @param center ラジオボタンの中心座標
		/// @param itemWidth ラジオボタンの各アイテムの幅（ピクセル）
		/// @param enabled ラジオボタンの操作を有効にするか
		/// @return ラジオボタンが操作された場合 true, それ以外の場合は false
		bool HorizontalRadioButtonsAt(size_t& index, const Array<String>& options, const Vec2& center, const Optional<double>& itemWidth = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF TextBoxRegion(const Vec2& pos, double width = 200.0);

		[[nodiscard]]
		RectF TextBoxRegionAt(const Vec2& center, double width = 200.0);

		/// @brief テキストボックスを表示します。
		/// @param text テキストボックスの状態への参照
		/// @param pos テキストボックスの左上の座標
		/// @param width テキストボックスの幅（ピクセル）
		/// @param maxChars 入力できる最大の文字数 (char32 の要素数）
		/// @param enabled テキストボックスの操作を有効にするか
		/// @return テキストが操作された場合 true, それ以外の場合は false
		bool TextBox(TextEditState& text, const Vec2& pos, double width = 200.0, const Optional<size_t>& maxChars = unspecified, bool enabled = true);

		/// @brief テキストボックスを表示します。
		/// @param text テキストボックスの状態への参照
		/// @param center テキストボックスの中心座標
		/// @param width テキストボックスの幅（ピクセル）
		/// @param maxChars 入力できる最大の文字数 (char32 の要素数）
		/// @param enabled テキストボックスの操作を有効にするか
		/// @return テキストが操作された場合 true, それ以外の場合は false
		bool TextBoxAt(TextEditState& text, const Vec2& center, double width = 200.0, const Optional<size_t>& maxChars = unspecified, bool enabled = true);

		[[nodiscard]]
		RectF ColorPickerRegion(const Vec2& pos);

		[[nodiscard]]
		RectF ColorPickerRegionAt(const Vec2& center);

		/// @brief カラーピッカーを表示します。
		/// @param hsv カラーピッカーで操作する色への参照
		/// @param pos カラーピッカーの左上の座標
		/// @param enabled カラーピッカーの操作を有効にするか
		/// @return カラーピッカーが操作された場合 true, それ以外の場合は false
		bool ColorPicker(HSV& hsv, const Vec2& pos, bool enabled = true);

		/// @brief カラーピッカーを表示します。
		/// @param hsv カラーピッカーで操作する色への参照
		/// @param center カラーピッカーの中心座標
		/// @param enabled カラーピッカーの操作を有効にするか
		/// @return カラーピッカーが操作された場合 true, それ以外の場合は false
		bool ColorPickerAt(HSV& hsv, const Vec2& center, bool enabled = true);

		[[nodiscard]]
		RectF ListBoxRegion(const Vec2& pos, double width = 160.0, double height = 156.0);
		
		[[nodiscard]]
		RectF ListBoxRegionAt(const Vec2& center, double width = 160.0, double height = 156.0);
		
		/// @brief リストボックスを表示します。
		/// @param state リストボックスの状態への参照
		/// @param pos リストボックスの左上の座標
		/// @param width リストボックスの幅（ピクセル）
		/// @param height リストボックスの高さ（ピクセル）
		/// @param enabled リストボックスの操作を有効にするか
		/// @return リストボックスが操作された場合 true, それ以外の場合は false
		bool ListBox(ListBoxState& state, const Vec2& pos, double width = 160.0, double height = 156.0, bool enabled = true);
		
		/// @brief リストボックスを表示します。
		/// @param state リストボックスの状態への参照
		/// @param center リストボックスの中心座標
		/// @param width リストボックスの幅（ピクセル）
		/// @param height リストボックスの高さ（ピクセル）
		/// @param enabled リストボックスの操作を有効にするか
		/// @return リストボックスが操作された場合 true, それ以外の場合は false
		bool ListBoxAt(ListBoxState& state, const Vec2& center, double width = 160.0, double height = 156.0, bool enabled = true);
	}
}
