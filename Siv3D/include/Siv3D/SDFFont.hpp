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
# include "Fwd.hpp"
# include "Font.hpp"

namespace s3d
{
	struct GlyphF
	{
		TextureRegion texture;

		char32 codePoint = U'\0';

		Vec2 offset = Vec2(0, 0);

		Vec2 padding = Vec2(0, 0);

		double bearingY = 0;

		double xAdvance = 0;

		double yAdvance = 0;

		int32 index = 0;
	};

	class SDFFont
	{
	protected:

		struct Tag {};

		using SDFFontHandle = AssetHandle<Tag>;

		std::shared_ptr<SDFFontHandle> m_handle;

		friend SDFFontHandle::AssetHandle();

		friend SDFFontHandle::AssetHandle(const IDWrapperType id) noexcept;

		friend SDFFontHandle::~AssetHandle();

	public:

		using IDType = SDFFontHandle::IDWrapperType;

		SDFFont();

		explicit SDFFont(int32 baseSize, Typeface typeface = Typeface::Default, FontStyle style = FontStyle::Default);

		SDFFont(int32 baseSize, const FilePath& path, FontStyle style = FontStyle::Default);

		SDFFont(const std::pair<FilePath, FilePath>& prerenderedFiles, int32 baseSize, Typeface typeface = Typeface::Default, FontStyle style = FontStyle::Default);

		SDFFont(const std::pair<FilePath, FilePath>& prerenderedFiles, int32 baseSize, const FilePath& path, FontStyle style = FontStyle::Default);

		virtual ~SDFFont();

		void release();

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const;

		[[nodiscard]] IDType id() const;

		[[nodiscard]] bool operator ==(const SDFFont& font) const;

		[[nodiscard]] bool operator !=(const SDFFont& font) const;

		[[nodiscard]] const String& familyName() const;

		[[nodiscard]] const String& styleName() const;

		[[nodiscard]] int32 baseSize() const;

		[[nodiscard]] double ascent() const;

		[[nodiscard]] double descent() const;

		[[nodiscard]] double height() const;

		[[nodiscard]] double pixelRange() const;

		const SDFFont& preload(StringView text) const;

		bool saveGlyphs(FilePathView imagePath, FilePathView jsonPath) const;

		[[nodiscard]] GlyphF getGlyph(char32 codePoint) const;

		[[nodiscard]] Array<GlyphF> getGlyphs(StringView text) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		[[nodiscard]] SDFDrawableText operator()(const String& text) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		[[nodiscard]] SDFDrawableText operator()(String&& text) const;

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
		[[nodiscard]] inline SDFDrawableText operator()(const Args& ... args) const;

		[[nodiscard]] const Texture& getTexture() const;
	};

	using SDFFontID = SDFFont::IDType;

	class GlyphFIterator
	{
	private:

		SDFFont m_font;

		String::const_iterator m_iterator;

		int32 m_index = 0;

	public:

		GlyphFIterator() = default;

		GlyphFIterator(const GlyphFIterator&) = default;

		GlyphFIterator(const SDFFont& font, String::const_iterator it, int32 index);

		GlyphFIterator& operator =(const GlyphFIterator&) = default;

		GlyphFIterator& operator ++();

		[[nodiscard]] GlyphF operator *() const;

		[[nodiscard]] bool operator ==(const GlyphFIterator& other) const;

		[[nodiscard]] bool operator !=(const GlyphFIterator& other) const;
	};

	struct SDFDrawableText
	{
		SDFFont font;

		String text;

		SDFDrawableText() = default;

		SDFDrawableText(const SDFFont& _font, const String & _text);

		SDFDrawableText(const SDFFont& _font, String && _text);

		[[nodiscard]] GlyphFIterator begin() const;

		[[nodiscard]] GlyphFIterator end() const;

		[[nodiscard]] RectF boundingRect(double fontSize, double x, double y) const;

		[[nodiscard]] RectF boundingRect(double fontSize, const Vec2& pos = Vec2(0, 0)) const;

		[[nodiscard]] RectF boundingRect(double fontSize, Arg::topLeft_<Vec2> topLeft) const;

		[[nodiscard]] RectF boundingRect(double fontSize, Arg::topRight_<Vec2> topRight) const;

		[[nodiscard]] RectF boundingRect(double fontSize, Arg::bottomLeft_<Vec2> bottomLeft) const;

		[[nodiscard]] RectF boundingRect(double fontSize, Arg::bottomRight_<Vec2> bottomRight) const;

		[[nodiscard]] RectF boundingRect(double fontSize, Arg::topCenter_<Vec2> topCenter) const;

		[[nodiscard]] RectF boundingRect(double fontSize, Arg::bottomCenter_<Vec2> bottomCenter) const;

		[[nodiscard]] RectF boundingRect(double fontSize, Arg::leftCenter_<Vec2> leftCenter) const;

		[[nodiscard]] RectF boundingRect(double fontSize, Arg::rightCenter_<Vec2> rightCenter) const;

		[[nodiscard]] RectF boundingRect(double fontSize, Arg::center_<Vec2> center) const;

		[[nodiscard]] RectF boundingRectAt(double fontSize, double x, double y) const;

		[[nodiscard]] RectF boundingRectAt(double fontSize, const Vec2& pos = Vec2(0, 0)) const;

		[[nodiscard]] RectF region(double fontSize, double x, double y) const;

		[[nodiscard]] Rect region(double fontSize, const Point& pos = Point(0, 0)) const;

		[[nodiscard]] RectF region(double fontSize, const Vec2& pos) const;

		[[nodiscard]] RectF region(double fontSize, Arg::topLeft_<Vec2> topLeft) const;

		[[nodiscard]] RectF region(double fontSize, Arg::topRight_<Vec2> topRight) const;

		[[nodiscard]] RectF region(double fontSize, Arg::bottomLeft_<Vec2> bottomLeft) const;

		[[nodiscard]] RectF region(double fontSize, Arg::bottomRight_<Vec2> bottomRight) const;

		[[nodiscard]] RectF region(double fontSize, Arg::topCenter_<Vec2> topCenter) const;

		[[nodiscard]] RectF region(double fontSize, Arg::bottomCenter_<Vec2> bottomCenter) const;

		[[nodiscard]] RectF region(double fontSize, Arg::leftCenter_<Vec2> leftCenter) const;

		[[nodiscard]] RectF region(double fontSize, Arg::rightCenter_<Vec2> rightCenter) const;

		[[nodiscard]] RectF region(double fontSize, Arg::center_<Vec2> center) const;

		[[nodiscard]] RectF regionAt(double fontSize, double x, double y) const;

		[[nodiscard]] RectF regionAt(double fontSize, const Vec2& pos = Vec2(0, 0)) const;

		[[nodiscard]] Array<double> getXAdvances(double fontSize) const;

		RectF draw(double fontSize, double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(double fontSize, const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;

		RectF draw(double fontSize, Arg::topLeft_<Vec2> topLeft, const ColorF& color = Palette::White) const;

		RectF draw(double fontSize, Arg::topRight_<Vec2> topRight, const ColorF& color = Palette::White) const;

		RectF draw(double fontSize, Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color = Palette::White) const;

		RectF draw(double fontSize, Arg::bottomRight_<Vec2> bottomRight, const ColorF& color = Palette::White) const;

		RectF draw(double fontSize, Arg::topCenter_<Vec2> topCenter, const ColorF& color = Palette::White) const;

		RectF draw(double fontSize, Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color = Palette::White) const;

		RectF draw(double fontSize, Arg::leftCenter_<Vec2> leftCenter, const ColorF& color = Palette::White) const;

		RectF draw(double fontSize, Arg::rightCenter_<Vec2> rightCenter, const ColorF& color = Palette::White) const;

		RectF draw(double fontSize, Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		RectF drawAt(double fontSize, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawAt(double fontSize, const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;

		RectF drawBase(double fontSize, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBase(double fontSize, const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;

		RectF drawBase(double fontSize, Arg::left_<Vec2> left, const ColorF& color = Palette::White) const;

		RectF drawBase(double fontSize, Arg::right_<Vec2> right, const ColorF& color = Palette::White) const;

		RectF drawBase(double fontSize, Arg::center_<Vec2> center, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(double fontSize, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(double fontSize, const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;
	};

	template <class ... Args>
	inline SDFDrawableText SDFFont::operator()(const Args& ... args) const
	{
		return SDFDrawableText(*this, Format(args...));
	}
}
