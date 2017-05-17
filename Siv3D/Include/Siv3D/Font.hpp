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
# include "String.hpp"
# include "Color.hpp"
# include "PointVector.hpp"
# include "Rectangle.hpp"

namespace s3d
{
	class Font
	{
	protected:

		class Handle {};

		using FontHandle = AssetHandle<Handle>;

		std::shared_ptr<FontHandle> m_handle;

	public:

		using IDType = FontHandle::IDType;

		static constexpr IDType NullHandleID = FontHandle::NullID;

		Font();

		Font(const FilePath& path, int32 fontSize);

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
		/// <param name="args">
		/// 文字列に変換するデータ
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		template <class ... Args>
		inline DrawableText operator()(const Args& ... args) const;
	};

	struct DrawableText
	{
		Font font;

		String text;

		DrawableText(const Font& _font, const String& _text)
			: font(_font)
			, text(_text) {}

		DrawableText(const Font& _font, String&& _text)
			: font(_font)
			, text(std::move(_text)) {}

		RectF draw(double x, double y, const ColorF& color = Palette::White) const
		{
			return draw(Vec2(x, y), color);
		}

		RectF draw(const Vec2& pos, const ColorF& color = Palette::White) const;
	};

	inline DrawableText Font::operator()(const String& text) const
	{
		return{ *this, text };
	}

	template <class ... Args>
	inline DrawableText Font::operator()(const Args& ... args) const
	{
		return DrawableText(*this, Format(args...));
	}
}
