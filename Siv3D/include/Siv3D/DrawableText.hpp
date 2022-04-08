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
# include "String.hpp"
# include "Font.hpp"
# include "Format.hpp"
# include "TextStyle.hpp"

namespace s3d
{
	struct DrawableText
	{
		Font font;

		String text;

		Array<GlyphCluster> clusters;

		SIV3D_NODISCARD_CXX20
		DrawableText() = default;

		SIV3D_NODISCARD_CXX20
		DrawableText(const Font& _font, const String& _text);

		SIV3D_NODISCARD_CXX20
		DrawableText(const Font& _font, String&& _text);

		[[nodiscard]]
		Array<double> getXAdvances() const;

		[[nodiscard]]
		Array<double> getXAdvances(double size) const;

		/// @brief テキストが描画される領域を返します。
		/// @param x 描画する左上の X 座標
		/// @param y 描画する左上の Y 座標
		/// @return テキストが描画される領域
		[[nodiscard]]
		RectF region(double x, double y) const;

		/// @brief テキストが描画される領域を返します。
		/// @param pos 描画する左上の座標
		/// @return テキストが描画される領域
		[[nodiscard]]
		RectF region(Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF region(Arg::topLeft_<Vec2> topLeft) const;

		[[nodiscard]]
		RectF region(Arg::topCenter_<Vec2> topCenter) const;

		[[nodiscard]]
		RectF region(Arg::topRight_<Vec2> topRight) const;

		[[nodiscard]]
		RectF region(Arg::rightCenter_<Vec2> rightCenter) const;

		[[nodiscard]]
		RectF region(Arg::bottomRight_<Vec2> bottomRight) const;

		[[nodiscard]]
		RectF region(Arg::bottomCenter_<Vec2> bottomCenter) const;

		[[nodiscard]]
		RectF region(Arg::bottomLeft_<Vec2> bottomLeft) const;

		[[nodiscard]]
		RectF region(Arg::leftCenter_<Vec2> leftCenter) const;

		[[nodiscard]]
		RectF region(Arg::center_<Vec2> center) const;

		[[nodiscard]]
		RectF region(double size, double x, double y) const;

		[[nodiscard]]
		RectF region(double size, Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF region(double size, Arg::topLeft_<Vec2> topLeft) const;

		[[nodiscard]]
		RectF region(double size, Arg::topCenter_<Vec2> topCenter) const;

		[[nodiscard]]
		RectF region(double size, Arg::topRight_<Vec2> topRight) const;

		[[nodiscard]]
		RectF region(double size, Arg::rightCenter_<Vec2> rightCenter) const;

		[[nodiscard]]
		RectF region(double size, Arg::bottomRight_<Vec2> bottomRight) const;

		[[nodiscard]]
		RectF region(double size, Arg::bottomCenter_<Vec2> bottomCenter) const;

		[[nodiscard]]
		RectF region(double size, Arg::bottomLeft_<Vec2> bottomLeft) const;

		[[nodiscard]]
		RectF region(double size, Arg::leftCenter_<Vec2> leftCenter) const;

		[[nodiscard]]
		RectF region(double size, Arg::center_<Vec2> center) const;

		[[nodiscard]]
		RectF regionBase(double x, double y) const;

		[[nodiscard]]
		RectF regionBase(Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionBase(Arg::left_<Vec2> left) const;

		[[nodiscard]]
		RectF regionBase(Arg::center_<Vec2> center) const;

		[[nodiscard]]
		RectF regionBase(Arg::right_<Vec2> right) const;

		[[nodiscard]]
		RectF regionBase(double size, double x, double y) const;

		[[nodiscard]]
		RectF regionBase(double size, Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionBase(double size, Arg::left_<Vec2> left) const;

		[[nodiscard]]
		RectF regionBase(double size, Arg::center_<Vec2> center) const;

		[[nodiscard]]
		RectF regionBase(double size, Arg::right_<Vec2> right) const;

		[[nodiscard]]
		RectF regionAt(double x, double y) const;

		[[nodiscard]]
		RectF regionAt(Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionAt(double size, double x, double y) const;

		[[nodiscard]]
		RectF regionAt(double size, Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionBaseAt(double x, double y) const;

		[[nodiscard]]
		RectF regionBaseAt(Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionBaseAt(double size, double x, double y) const;

		[[nodiscard]]
		RectF regionBaseAt(double size, Vec2 pos = Vec2{ 0, 0 }) const;

		RectF draw(double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF draw(Arg::topLeft_<Vec2> topLeft, const ColorF& color = Palette::White) const;

		RectF draw(Arg::topCenter_<Vec2> topCenter, const ColorF& color = Palette::White) const;

		RectF draw(Arg::topRight_<Vec2> topRight, const ColorF& color = Palette::White) const;

		RectF draw(Arg::rightCenter_<Vec2> rightCenter, const ColorF& color = Palette::White) const;

		RectF draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF& color = Palette::White) const;

		RectF draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color = Palette::White) const;

		RectF draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color = Palette::White) const;

		RectF draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF& color = Palette::White) const;

		RectF draw(Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		bool draw(const RectF& area, const ColorF& color = Palette::White) const;

		RectF draw(double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(double size, const Vec2& pos, const ColorF& color = Palette::White) const;

		RectF draw(double size, Arg::topLeft_<Vec2> topLeft, const ColorF& color = Palette::White) const;

		RectF draw(double size, Arg::topCenter_<Vec2> topCenter, const ColorF& color = Palette::White) const;

		RectF draw(double size, Arg::topRight_<Vec2> topRight, const ColorF& color = Palette::White) const;

		RectF draw(double size, Arg::rightCenter_<Vec2> rightCenter, const ColorF& color = Palette::White) const;

		RectF draw(double size, Arg::bottomRight_<Vec2> bottomRight, const ColorF& color = Palette::White) const;

		RectF draw(double size, Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color = Palette::White) const;

		RectF draw(double size, Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color = Palette::White) const;

		RectF draw(double size, Arg::leftCenter_<Vec2> leftCenter, const ColorF& color = Palette::White) const;

		RectF draw(double size, Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		bool draw(double size, const RectF& area, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, Arg::topLeft_<Vec2> topLeft, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, Arg::topCenter_<Vec2> topCenter, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, Arg::topRight_<Vec2> topRight, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, Arg::rightCenter_<Vec2> rightCenter, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, Arg::bottomRight_<Vec2> bottomRight, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, Arg::leftCenter_<Vec2> leftCenter, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		bool draw(const TextStyle& textStyle, const RectF& area, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, const Vec2& pos, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, Arg::topLeft_<Vec2> topLeft, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, Arg::topCenter_<Vec2> topCenter, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, Arg::topRight_<Vec2> topRight, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, Arg::rightCenter_<Vec2> rightCenter, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, Arg::bottomRight_<Vec2> bottomRight, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, Arg::leftCenter_<Vec2> leftCenter, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, Arg::center_<Vec2> center, const ColorF & color = Palette::White) const;

		bool draw(const TextStyle& textStyle, double size, const RectF& area, const ColorF& color = Palette::White) const;

		RectF drawBase(double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBase(const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF drawBase(Arg::left_<Vec2> left, const ColorF& color = Palette::White) const;

		RectF drawBase(Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		RectF drawBase(Arg::right_<Vec2> right, const ColorF& color = Palette::White) const;

		RectF drawBase(double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBase(double size, const Vec2& pos, const ColorF& color = Palette::White) const;

		RectF drawBase(double size, Arg::left_<Vec2> left, const ColorF& color = Palette::White) const;

		RectF drawBase(double size, Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		RectF drawBase(double size, Arg::right_<Vec2> right, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, Arg::left_<Vec2> left, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, Arg::right_<Vec2> right, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, double size, const Vec2& pos, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, double size, Arg::left_<Vec2> left, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, double size, Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, double size, Arg::right_<Vec2> right, const ColorF& color = Palette::White) const;

		/// @brief 中心位置を指定してテキストを描画します。
		/// @param x 描画する中心の X 座標
		/// @param y 描画する中心の Y 座標
		/// @param color テキストの色
		/// @return テキストが描画された領域
		RectF drawAt(double x, double y, const ColorF& color = Palette::White) const;

		/// @brief 中心位置を指定してテキストを描画します。
		/// @param pos 描画する中心の座標
		/// @param color テキストの色
		/// @return テキストが描画された領域
		RectF drawAt(const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		/// @brief 中心位置を指定してテキストを描画します。
		/// @param size テキストのサイズ
		/// @param x 描画する中心の X 座標
		/// @param y 描画する中心の Y 座標
		/// @param color テキストの色
		/// @return テキストが描画された領域
		RectF drawAt(double size, double x, double y, const ColorF& color = Palette::White) const;

		/// @brief 中心位置を指定してテキストを描画します。
		/// @param size テキストのサイズ
		/// @param pos 描画する中心の座標
		/// @param color テキストの色
		/// @return テキストが描画された領域
		RectF drawAt(double size, const Vec2& pos, const ColorF& color = Palette::White) const;

		/// @brief 中心位置を指定してテキストを描画します。
		/// @param textStyle テキストのスタイル
		/// @param x 描画する中心の X 座標
		/// @param y 描画する中心の Y 座標
		/// @param color テキストの色
		/// @return テキストが描画された領域
		RectF drawAt(const TextStyle & textStyle, double x, double y, const ColorF & color = Palette::White) const;

		/// @brief 中心位置を指定してテキストを描画します。
		/// @param textStyle テキストのスタイル
		/// @param pos 描画する中心の座標
		/// @param color テキストの色
		/// @return テキストが描画された領域
		RectF drawAt(const TextStyle & textStyle, const Vec2 & pos = Vec2{ 0, 0 }, const ColorF & color = Palette::White) const;

		/// @brief 中心位置を指定してテキストを描画します。
		/// @param textStyle テキストのスタイル
		/// @param size テキストのサイズ
		/// @param x 描画する中心の X 座標
		/// @param y 描画する中心の Y 座標
		/// @param color テキストの色
		/// @return テキストが描画された領域
		RectF drawAt(const TextStyle & textStyle, double size, double x, double y, const ColorF & color = Palette::White) const;

		/// @brief 中心位置を指定してテキストを描画します。
		/// @param textStyle テキストのスタイル
		/// @param size テキストのサイズ
		/// @param pos 描画する中心の座標
		/// @param color テキストの色
		/// @return テキストが描画された領域
		RectF drawAt(const TextStyle & textStyle, double size, const Vec2 & pos, const ColorF & color = Palette::White) const;

		RectF drawBaseAt(double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(double size, const Vec2& pos, const ColorF& color = Palette::White) const;
		
		RectF drawBaseAt(const TextStyle& textStyle, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(const TextStyle& textStyle, const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(const TextStyle& textStyle, double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(const TextStyle& textStyle, double size, const Vec2& pos, const ColorF& color = Palette::White) const;


		void paint(Image& dst, double x, double y, const Color& color = Palette::White) const;

		void paint(Image& dst, const Vec2& pos, const Color& color = Palette::White) const;

		void stamp(Image& dst, double x, double y, const Color& color = Palette::White) const;

		void stamp(Image& dst, const Vec2& pos, const Color& color = Palette::White) const;

		void overwrite(Image& dst, double x, double y) const;

		void overwrite(Image& dst, const Vec2& pos) const;


		void paintAt(Image& dst, double x, double y, const Color& color = Palette::White) const;

		void paintAt(Image& dst, const Vec2& pos, const Color& color = Palette::White) const;

		void stampAt(Image& dst, double x, double y, const Color& color = Palette::White) const;

		void stampAt(Image& dst, const Vec2& pos, const Color& color = Palette::White) const;

		void overwriteAt(Image& dst, double x, double y) const;

		void overwriteAt(Image& dst, const Vec2& pos) const;
	};

	template <class ... Args>
	inline DrawableText Font::operator ()(const Args& ... args) const
	{
		return DrawableText(*this, Format(args...));
	}
}
