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
	namespace Typeface
	{
		const String Default = L"engine/font/umeplus/umeplus-p-gothic.ttf";

		const String Thin = L"engine/font/mplus/mplus-1p-thin.ttf";

		const String Light = L"engine/font/mplus/mplus-1p-light.ttf";
		
		const String Regular = L"engine/font/mplus/mplus-1p-regular.ttf";
		
		const String Medium = L"engine/font/mplus/mplus-1p-medium.ttf";

		const String Bold = L"engine/font/mplus/mplus-1p-bold.ttf";
		
		const String Heavy = L"engine/font/mplus/mplus-1p-heavy.ttf";

		const String Black = L"engine/font/mplus/mplus-1p-black.ttf";
	}

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

		Font(int32 fontSize, const FilePath& path = Typeface::Default, FontStyle style = FontStyle::Default);

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

		RectF draw(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;
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
