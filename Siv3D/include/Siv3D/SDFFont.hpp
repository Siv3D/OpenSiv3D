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

		[[nodiscard]] int32 ascent() const;

		[[nodiscard]] int32 descent() const;

		[[nodiscard]] int32 height() const;

		[[nodiscard]] Glyph getGlyph(char32 codePoint) const;

		[[nodiscard]] Array<Glyph> getGlyphs(StringView text) const;

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

	struct SDFDrawableText
	{
		SDFFont font;

		String text;
	};
}
