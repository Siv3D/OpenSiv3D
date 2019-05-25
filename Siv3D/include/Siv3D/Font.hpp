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

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "AssetHandle.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Color.hpp"
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "TextureRegion.hpp"
# include "NamedParameter.hpp"
# include "OutlineGlyph.hpp"

namespace s3d
{
	enum class Typeface
	{
		Thin,

		Light,

		Regular,

		Medium,

		Bold,

		Heavy,

		Black,

		Default = Regular,
	};

	/// <summary>
	///	フォントスタイルのフラグ
	/// </summary>
	enum class FontStyle : uint32
	{
		Default = 0x0,

		Bold = 0x01,

		Italic = 0x02,

		BoldItalic = Bold | Italic,

		Bitmap = 0x04,

		BoldBitmap = Bold | Bitmap,

		ItalicBitmap = Italic | Bitmap,

		BoldItalicBitmap = Bold | Italic | Bitmap,
	};

	struct Glyph
	{
		TextureRegion texture;

		char32 codePoint = U'\0';

		Point offset = Point(0, 0);

		int32 bearingY = 0;

		int32 xAdvance = 0;

		int32 yAdvance = 0;

		int32 index = 0;
	};
	
	class Font
	{
	protected:

		struct Tag {};

		using FontHandle = AssetHandle<Tag>;

		std::shared_ptr<FontHandle> m_handle;
		
		friend FontHandle::AssetHandle();
		
		friend FontHandle::AssetHandle(const IDWrapperType id) noexcept;
		
		friend FontHandle::~AssetHandle();

	public:

		using IDType = FontHandle::IDWrapperType;

		Font();

		explicit Font(int32 fontSize, Typeface typeface = Typeface::Default, FontStyle style = FontStyle::Default);

		Font(int32 fontSize, const FilePath& path, FontStyle style = FontStyle::Default);

		virtual ~Font();

		void release();

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const;

		[[nodiscard]] IDType id() const;

		[[nodiscard]] bool operator ==(const Font& font) const;

		[[nodiscard]] bool operator !=(const Font& font) const;

		[[nodiscard]] const String& familyName() const;

		[[nodiscard]] const String& styleName() const;

		[[nodiscard]] int32 fontSize() const;

		[[nodiscard]] int32 ascent() const;

		[[nodiscard]] int32 descent() const;

		[[nodiscard]] int32 height() const;

		[[nodiscard]] Glyph getGlyph(char32 codePoint) const;

		[[nodiscard]] Array<Glyph> getGlyphs(const String& text) const;

		[[nodiscard]] Array<Glyph> getVerticalGlyphs(const String& text) const;

		[[nodiscard]] OutlineGlyph getOutlineGlyph(char32 codePoint) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		[[nodiscard]] DrawableText operator()(const String& text) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		[[nodiscard]] DrawableText operator()(String&& text) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="args">
		/// 文字列に変換するデータ
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		template <class ... Args>
		[[nodiscard]] inline DrawableText operator()(const Args& ... args) const;

		[[nodiscard]] const Texture& getTexture() const;
	};

	class GlyphIterator
	{
	private:

		Font m_font;

		String::const_iterator m_iterator;

		int32 m_index = 0;

	public:

		GlyphIterator() = default;

		GlyphIterator(const GlyphIterator&) = default;

		GlyphIterator(const Font& font, String::const_iterator it, int32 index);

		GlyphIterator& operator =(const GlyphIterator&) = default;

		GlyphIterator& operator ++();

		[[nodiscard]] Glyph operator *() const;

		[[nodiscard]] bool operator ==(const GlyphIterator& other) const;
		
		[[nodiscard]] bool operator !=(const GlyphIterator& other) const;
	};

	using FontID = Font::IDType;

	struct DrawableText
	{
		Font font;

		String text;

		DrawableText() = default;

		DrawableText(const Font& _font, const String& _text);

		DrawableText(const Font& _font, String&& _text);

		[[nodiscard]] GlyphIterator begin() const;

		[[nodiscard]] GlyphIterator end() const;

		[[nodiscard]] RectF boundingRect(double x, double y) const;

		[[nodiscard]] RectF boundingRect(const Vec2& pos = Vec2(0, 0)) const;

		[[nodiscard]] RectF boundingRect(Arg::topLeft_<Vec2> topLeft) const;

		[[nodiscard]] RectF boundingRect(Arg::topRight_<Vec2> topRight) const;

		[[nodiscard]] RectF boundingRect(Arg::bottomLeft_<Vec2> bottomLeft) const;

		[[nodiscard]] RectF boundingRect(Arg::bottomRight_<Vec2> bottomRight) const;

		[[nodiscard]] RectF boundingRect(Arg::topCenter_<Vec2> topCenter) const;

		[[nodiscard]] RectF boundingRect(Arg::bottomCenter_<Vec2> bottomCenter) const;

		[[nodiscard]] RectF boundingRect(Arg::leftCenter_<Vec2> leftCenter) const;

		[[nodiscard]] RectF boundingRect(Arg::rightCenter_<Vec2> rightCenter) const;

		[[nodiscard]] RectF boundingRect(Arg::center_<Vec2> center) const;

		[[nodiscard]] RectF boundingRectAt(double x, double y) const;

		[[nodiscard]] RectF boundingRectAt(const Vec2& pos = Vec2(0, 0)) const;

		[[nodiscard]] RectF region(double x, double y) const;

		[[nodiscard]] Rect region(const Point& pos = Point(0, 0)) const;

		[[nodiscard]] RectF region(const Vec2& pos) const;

		[[nodiscard]] RectF region(Arg::topLeft_<Vec2> topLeft) const;

		[[nodiscard]] RectF region(Arg::topRight_<Vec2> topRight) const;

		[[nodiscard]] RectF region(Arg::bottomLeft_<Vec2> bottomLeft) const;

		[[nodiscard]] RectF region(Arg::bottomRight_<Vec2> bottomRight) const;

		[[nodiscard]] RectF region(Arg::topCenter_<Vec2> topCenter) const;

		[[nodiscard]] RectF region(Arg::bottomCenter_<Vec2> bottomCenter) const;

		[[nodiscard]] RectF region(Arg::leftCenter_<Vec2> leftCenter) const;

		[[nodiscard]] RectF region(Arg::rightCenter_<Vec2> rightCenter) const;

		[[nodiscard]] RectF region(Arg::center_<Vec2> center) const;

		[[nodiscard]] RectF regionAt(double x, double y) const;

		[[nodiscard]] RectF regionAt(const Vec2& pos = Vec2(0, 0)) const;

		[[nodiscard]] Array<int32> getXAdvances() const;

		RectF draw(double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;

		RectF draw(Arg::topLeft_<Vec2> topLeft, const ColorF& color = Palette::White) const;

		RectF draw(Arg::topRight_<Vec2> topRight, const ColorF& color = Palette::White) const;

		RectF draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color = Palette::White) const;

		RectF draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF& color = Palette::White) const;

		RectF draw(Arg::topCenter_<Vec2> topCenter, const ColorF& color = Palette::White) const;

		RectF draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color = Palette::White) const;

		RectF draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF& color = Palette::White) const;

		RectF draw(Arg::rightCenter_<Vec2> rightCenter, const ColorF& color = Palette::White) const;

		RectF draw(Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		RectF drawAt(double x, double y, const ColorF& color = Palette::White) const;

		RectF drawAt(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;

		RectF drawBase(double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBase(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;

		RectF drawBase(Arg::left_<Vec2> left, const ColorF& color = Palette::White) const;

		RectF drawBase(Arg::right_<Vec2> right, const ColorF& color = Palette::White) const;

		RectF drawBase(Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;

		bool draw(const RectF& area, const ColorF& color = Palette::White) const;

		Rect paint(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		Rect paint(Image& dst, const Point& pos = Point(0, 0), const Color& color = Palette::White) const;

		RectF paintAt(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		RectF paintAt(Image& dst, const Point& pos = Point(0, 0), const Color& color = Palette::White) const;

		Rect overwrite(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		Rect overwrite(Image& dst, const Point& pos = Point(0, 0), const Color& color = Palette::White) const;

		RectF overwriteAt(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		RectF overwriteAt(Image& dst, const Point& pos = Point(0, 0), const Color& color = Palette::White) const;
	};

	template <class ... Args>
	inline DrawableText Font::operator()(const Args& ... args) const
	{
		return DrawableText(*this, Format(args...));
	}
}
