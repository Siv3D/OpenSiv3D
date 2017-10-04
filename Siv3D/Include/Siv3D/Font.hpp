//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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

		char32_t codePoint = U'\0';

		Point offset = Point(0, 0);

		int32 bearingY = 0;

		int32 xAdvance = 0;

		Glyph()
		{
			texture.uvRect = FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
			
			texture.size.set(0.0f, 0.0f);
		}
	};
	
	class Font
	{
	protected:

		class Handle {};

		using FontHandle = AssetHandle<Handle>;
		
		friend FontHandle::~AssetHandle();

		std::shared_ptr<FontHandle> m_handle;

	public:

		using IDType = FontHandle::IDType;

		static constexpr IDType NullHandleID = FontHandle::NullID;

		Font();

		explicit Font(int32 fontSize, Typeface typeface = Typeface::Default, FontStyle style = FontStyle::Default);

		Font(int32 fontSize, const FilePath& path, FontStyle style = FontStyle::Default);

		~Font();

		void release();

		bool isEmpty() const;

		explicit operator bool() const
		{
			return !isEmpty();
		}

		IDType id() const;

		bool operator ==(const Font& font) const;

		bool operator !=(const Font& font) const;

		const String& familyName() const;

		const String& styleName() const;

		int32 fontSize() const;

		int32 ascent() const;

		int32 descent() const;

		int32 height() const;

		Glyph getGlyph(char32_t codePoint) const;

		Array<Glyph> getGlyphs(const String& text) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		DrawableText operator()(const String& text) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		DrawableText operator()(String&& text) const;

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
		inline DrawableText operator()(const Args& ... args) const;
	};

	class GlyphIterator
	{
	private:

		Font font;

		U32String::const_iterator textIterator;

	public:

		GlyphIterator() = default;

		GlyphIterator(const GlyphIterator&) = default;

		GlyphIterator(const Font& _font, U32String::const_iterator _it)
			: font(_font)
			, textIterator(_it) {}

		GlyphIterator& operator =(const GlyphIterator&) = default;

		GlyphIterator& operator ++()
		{
			++textIterator;

			return *this;
		}

		Glyph operator *() const
		{
			return font.getGlyph(*textIterator);
		}

		bool operator ==(const GlyphIterator& other) const
		{
			return textIterator == other.textIterator;
		}
		
		bool operator !=(const GlyphIterator& other) const
		{
			return textIterator != other.textIterator;
		}
	};

	struct DrawableText
	{
		Font font;

		U32String codePoints;

		DrawableText(const Font& _font, const String& text)
			: font(_font)

		# if defined(SIV3D_TARGET_WINDOWS)

			, codePoints(text.toUTF32()) {}

		# else

			, codePoints(text) {}

		# endif	

		DrawableText(const Font& _font, String&& text)
			: font(_font)

		# if defined(SIV3D_TARGET_WINDOWS)

			, codePoints(text.toUTF32()) {}

		# else

			, codePoints(std::move(text)) {}

		# endif	

		GlyphIterator begin() const
		{
			return GlyphIterator(font, codePoints.begin());
		}

		GlyphIterator end() const
		{
			return GlyphIterator(font, codePoints.end());
		}

		RectF boundingRect(double x, double y) const
		{
			return boundingRect(Vec2(x, y));
		}

		RectF boundingRect(const Vec2& pos = Vec2(0, 0)) const;

		RectF boundingRect(Arg::topLeft_<Vec2> topLeft) const
		{
			return boundingRect(*topLeft);
		}

		RectF boundingRect(Arg::topRight_<Vec2> topRight) const
		{
			return boundingRect(topRight->movedBy(-region().w, 0));
		}

		RectF boundingRect(Arg::bottomLeft_<Vec2> bottomLeft) const
		{
			return boundingRect(bottomLeft->movedBy(0, -region().h));
		}

		RectF boundingRect(Arg::bottomRight_<Vec2> bottomRight) const
		{
			return boundingRect(bottomRight->movedBy(-region().size));
		}

		RectF boundingRect(Arg::topCenter_<Vec2> topCenter) const
		{
			return boundingRect(topCenter->movedBy(-region().w * 0.5, 0));
		}

		RectF boundingRect(Arg::bottomCenter_<Vec2> bottomCenter) const
		{
			return boundingRect(bottomCenter->movedBy(-region().w * 0.5, -region().h));
		}

		RectF boundingRect(Arg::leftCenter_<Vec2> leftCenter) const
		{
			return boundingRect(leftCenter->movedBy(0, -region().h * 0.5));
		}

		RectF boundingRect(Arg::rightCenter_<Vec2> rightCenter) const
		{
			return boundingRect(rightCenter->movedBy(-region().w, -region().h * 0.5));
		}

		RectF boundingRect(Arg::center_<Vec2> center) const
		{
			return boundingRectAt(*center);
		}

		RectF boundingRectAt(double x, double y) const
		{
			return boundingRectAt(Vec2(x, y));
		}

		RectF boundingRectAt(const Vec2& pos = Vec2(0, 0)) const
		{
			const RectF rect = boundingRect();

			return rect.movedBy(pos - rect.center());
		}

		RectF region(double x, double y) const
		{
			return region(Vec2(x, y));
		}

		RectF region(const Vec2& pos = Vec2(0, 0)) const;

		RectF region(Arg::topLeft_<Vec2> topLeft) const
		{
			return region(*topLeft);
		}

		RectF region(Arg::topRight_<Vec2> topRight) const
		{
			return region(topRight->movedBy(-region().w, 0));
		}

		RectF region(Arg::bottomLeft_<Vec2> bottomLeft) const
		{
			return region(bottomLeft->movedBy(0, -region().h));
		}

		RectF region(Arg::bottomRight_<Vec2> bottomRight) const
		{
			return region(bottomRight->movedBy(-region().size));
		}

		RectF region(Arg::topCenter_<Vec2> topCenter) const
		{
			return region(topCenter->movedBy(-region().w * 0.5, 0));
		}

		RectF region(Arg::bottomCenter_<Vec2> bottomCenter) const
		{
			return region(bottomCenter->movedBy(-region().w * 0.5, -region().h));
		}

		RectF region(Arg::leftCenter_<Vec2> leftCenter) const
		{
			return region(leftCenter->movedBy(0, -region().h * 0.5));
		}

		RectF region(Arg::rightCenter_<Vec2> rightCenter) const
		{
			return region(rightCenter->movedBy(-region().w, -region().h * 0.5));
		}

		RectF region(Arg::center_<Vec2> center) const
		{
			return regionAt(*center);
		}

		RectF regionAt(double x, double y) const
		{
			return regionAt(Vec2(x, y));
		}

		RectF regionAt(const Vec2& pos = Vec2(0, 0)) const
		{
			const RectF rect = region();

			return rect.movedBy(pos - rect.center());
		}

		Array<int32> getXAdvances() const;

		RectF draw(double x, double y, const ColorF& color = Palette::White) const
		{
			return draw(Vec2(x, y), color);
		}

		RectF draw(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;

		RectF draw(Arg::topLeft_<Vec2> topLeft, const ColorF& color = Palette::White) const
		{
			return draw(*topLeft, color);
		}

		RectF draw(Arg::topRight_<Vec2> topRight, const ColorF& color = Palette::White) const
		{
			return draw(topRight->movedBy(-region().w, 0), color);
		}

		RectF draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color = Palette::White) const
		{
			return draw(bottomLeft->movedBy(0, -region().h), color);
		}

		RectF draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF& color = Palette::White) const
		{
			return draw(bottomRight->movedBy(-region().size), color);
		}

		RectF draw(Arg::topCenter_<Vec2> topCenter, const ColorF& color = Palette::White) const
		{
			return draw(topCenter->movedBy(-region().w * 0.5, 0), color);
		}

		RectF draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color = Palette::White) const
		{
			return draw(bottomCenter->movedBy(-region().w * 0.5, -region().h), color);
		}

		RectF draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF& color = Palette::White) const
		{
			return draw(leftCenter->movedBy(0, -region().h * 0.5), color);
		}

		RectF draw(Arg::rightCenter_<Vec2> rightCenter, const ColorF& color = Palette::White) const
		{
			return draw(rightCenter->movedBy(-region().w, -region().h * 0.5), color);
		}

		RectF draw(Arg::center_<Vec2> center, const ColorF& color = Palette::White) const
		{
			return drawAt(*center, color);
		}

		RectF drawAt(double x, double y, const ColorF& color = Palette::White) const
		{				
			return drawAt(Vec2(x, y), color);
		}

		RectF drawAt(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const
		{
			return draw(pos - region().center(), color);
		}

		RectF drawBase(double x, double y, const ColorF& color = Palette::White) const
		{
			return drawBase(Vec2(x, y), color);
		}

		RectF drawBase(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const
		{
			return draw(pos.movedBy(0, -font.ascent()), color);
		}

		RectF drawBase(Arg::left_<Vec2> left, const ColorF& color = Palette::White) const
		{
			return drawBase(*left, color);
		}

		RectF drawBase(Arg::right_<Vec2> right, const ColorF& color = Palette::White) const
		{
			return drawBase(right->movedBy(-region().w, 0), color);
		}

		RectF drawBase(Arg::center_<Vec2> center, const ColorF& color = Palette::White) const
		{
			return drawBase(center->movedBy(-region().w * 0.5, 0), color);
		}

		RectF drawBaseAt(double x, double y, const ColorF& color = Palette::White) const
		{
			return drawBaseAt(Vec2(x, y), color);
		}

		RectF drawBaseAt(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const
		{
			return drawBase(pos - region().center(), color);
		}

		bool draw(const RectF& area, const ColorF& color = Palette::White) const;
	};

	inline DrawableText Font::operator()(const String& text) const
	{
		return{ *this, text };
	}

	inline DrawableText Font::operator()(String&& text) const
	{
		return{ *this, std::move(text) };
	}

	template <class ... Args>
	inline DrawableText Font::operator()(const Args& ... args) const
	{
		return DrawableText(*this, Format(args...));
	}
}
