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
# include <iostream>
# include "Fwd.hpp"
# include "Format.hpp"

namespace s3d
{
	/// <summary>
	/// カラー
	/// </summary>
	/// <remarks>
	/// R,G,B,A それぞれを 8bit の整数で色を表現します。
	/// </remarks>
	struct Color
	{
		/// <summary>
		/// 赤 | Red
		/// </summary>
		uint32 r : 8;

		/// <summary>
		/// 緑 | Green
		/// </summary>
		uint32 g : 8;

		/// <summary>
		/// 青 | Blue
		/// </summary>
		uint32 b : 8;

		/// <summary>
		/// アルファ | Alpha
		/// </summary>
		uint32 a : 8;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Color() = default;

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="color">
		/// コピーする色
		/// </param>
		constexpr Color(const Color& color) noexcept = default;

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="_r">
		/// 赤 [0, 255]
		/// </param>
		/// <param name="_g">
		/// 緑 [0, 255]
		/// </param>
		/// <param name="_b">
		/// 青 [0, 255]
		/// </param>
		/// <param name="_a">
		/// アルファ [0, 255]
		/// </param>
		constexpr Color(uint32 _r, uint32 _g, uint32 _b, uint32 _a = 255) noexcept
			: r(_r)
			, g(_g)
			, b(_b)
			, a(_a) {}

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="rgb">
		/// グレースケール [0, 255]
		/// </param>
		/// <param name="_a">
		/// アルファ [0, 255]
		/// </param>
		explicit constexpr Color(uint32 rgb, uint32 _a = 255) noexcept
			: r(rgb)
			, g(rgb)
			, b(rgb)
			, a(_a) {}

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="rgb">
		/// 赤・緑・青
		/// </param>
		/// <param name="_a">
		/// アルファ [0, 255]
		/// </param>
		constexpr Color(const Color& rgb, uint32 _a) noexcept
			: r(rgb.r)
			, g(rgb.g)
			, b(rgb.b)
			, a(_a) {}

		/// <summary>
		/// 色をコピーします。
		/// </summary>
		/// <param name="color">
		/// コピーする色
		/// </param>
		constexpr Color(const ColorF& color) noexcept;

		/// <summary>
		/// 色をコピーします。
		/// </summary>
		/// <param name="hsv">
		/// コピーする色
		/// </param>
		Color(const HSV& hsv) noexcept;

		/// <summary>
		/// 色をカラーコードから作成します。
		/// </summary>
		/// <param name="code">
		/// "#FFF" または "#FFFFFF" のように # から始まるカラーコード
		/// </param>
		explicit Color(StringView code) noexcept;

		/// <summary>
		/// 新しい色を代入します。
		/// </summary>
		/// <param name="color">
		/// 新しい色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Color& operator =(const Color& color) noexcept = default;

		/// <summary>
		/// 新しい色を代入します。
		/// </summary>
		/// <param name="color">
		/// 新しい色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Color& operator =(const ColorF& color) noexcept;

		/// <summary>
		/// 新しい色を代入します。
		/// </summary>
		/// <param name="hsv">
		/// 新しい色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Color& operator =(const HSV& hsv) noexcept;

		/// <summary>
		/// 反転させた色を返します。
		/// </summary>
		/// <returns>
		/// 反転した色
		/// </returns>
		constexpr Color operator ~() const noexcept
		{
			return{ static_cast<uint8>(~r), static_cast<uint8>(~g), static_cast<uint8>(~b), a };
		}

		/// <summary>
		/// 色が等しいかを調べます。
		/// </summary>
		/// <param name="color">
		/// 比較対象の色
		/// </param>
		/// <returns>
		/// 等しければ true, それ以外の場合は false
		/// </returns>
		bool operator ==(const Color& color) const noexcept
		{
			return asUint32() == color.asUint32();
		}

		/// <summary>
		/// 色が等しくないかを調べます。
		/// </summary>
		/// <param name="color">
		/// 比較対象の色
		/// </param>
		/// <returns>
		/// 等しくなければ true, それ以外の場合は false
		/// </returns>
		bool operator !=(const Color& color) const noexcept
		{
			return !(*this == color);
		}

		/// <summary>
		/// 色を変更します。
		/// </summary>
		/// <param name="_r">
		/// 赤 [0, 255]
		/// </param>
		/// <param name="_g">
		/// 緑 [0, 255]
		/// </param>
		/// <param name="_b">
		/// 青 [0, 255]
		/// </param>
		/// <param name="_a">
		/// アルファ [0, 255]
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Color& set(const uint32 _r, const uint32 _g, const uint32 _b, const uint32 _a = 255) noexcept
		{
			r = _r;
			g = _g;
			b = _b;
			a = _a;
			return *this;
		}

		/// <summary>
		/// RGB の値を変更します。
		/// </summary>
		/// <param name="rgb">
		/// 新しい色のグレースケール [0, 255]
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Color& setRGB(uint32 rgb) noexcept
		{
			r = g = b = rgb;
			return *this;
		}

		/// <summary>
		/// アルファ値を変更します。
		/// </summary>
		/// <param name="_a">
		/// 新しいアルファ値 [0, 255]
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr Color& setA(const uint32 _a) noexcept
		{
			a = _a;
			return *this;
		}

		/// <summary>
		/// グレースケール値 [0, 255] を計算します。
		/// </summary>
		/// <returns>
		/// グレースケール値
		/// </returns>
		constexpr uint8 grayscale_0_255() const noexcept
		{
			return static_cast<uint8>(0.299*r + 0.587*g + 0.114*b);
		}

		/// <summary>
		/// グレースケール値 [0.0, 1.0] を計算します。
		/// </summary>
		/// <returns>
		/// グレースケール値
		/// </returns>
		constexpr double grayscale() const noexcept
		{
			return (0.299 / 255.0 * r) + (0.587 / 255.0 * g) + (0.114 / 255.0 * b);
		}

		uint32 asUint32() const noexcept
		{
			return *static_cast<const uint32*>(static_cast<const void*>(this));
		}

		constexpr Color lerp(const Color& other, const double f) const noexcept
		{
			return{ static_cast<uint32>(int32(r) + (int32(other.r) - int32(r)) * f),
					static_cast<uint32>(int32(g) + (int32(other.g) - int32(g)) * f),
					static_cast<uint32>(int32(b) + (int32(other.b) - int32(b)) * f),
					static_cast<uint32>(int32(a) + (int32(other.a) - int32(a)) * f) };
		}

		/// <summary>
		/// ガンマを適用した値を返します。
		/// </summary>
		/// <param name="gamma">
		/// ガンマ値
		/// </param>
		/// <returns>
		/// ガンマを適用した値
		/// </returns>
		Color gamma(double gamma) const noexcept;

		String toHex() const;
	};

	/// <summary>
	/// カラー
	/// </summary>
	/// <remarks>
	/// R,G,B,A それぞれを 64bit 浮動小数点数で表現します。
	/// </remarks>
	struct ColorF
	{
		/// <summary>
		/// 赤 | Red
		/// </summary>
		double r;

		/// <summary>
		/// 緑 | Green
		/// </summary>
		double g;

		/// <summary>
		/// 青 | Blue
		/// </summary>
		double b;

		/// <summary>
		/// アルファ | Alpha
		/// </summary>
		double a;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		ColorF() = default;

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="color">
		/// コピーする色
		/// </param>
		constexpr ColorF(const ColorF& color) noexcept = default;

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="rgb">
		/// グレースケール [0.0, 1.0]
		/// </param>
		/// <param name="_a">
		/// アルファ [0.0, 1.0]
		/// </param>
		explicit constexpr ColorF(double rgb, double _a = 1.0) noexcept
			: r(rgb)
			, g(rgb)
			, b(rgb)
			, a(_a) {}

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="_r">
		/// 赤 [0.0, 1.0]
		/// </param>
		/// <param name="_g">
		/// 緑 [0.0, 1.0]
		/// </param>
		/// <param name="_b">
		/// 青 [0.0, 1.0]
		/// </param>
		/// <param name="_a">
		/// アルファ [0.0, 1.0]
		/// </param>
		constexpr ColorF(double _r, double _g, double _b, double _a = 1.0) noexcept
			: r(_r)
			, g(_g)
			, b(_b)
			, a(_a) {}

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="color">
		/// 赤・緑・青
		/// </param>
		/// <param name="_a">
		/// アルファ [0.0, 1.0]
		/// </param>
		constexpr ColorF(const ColorF& color, double _a) noexcept
			: r(color.r)
			, g(color.g)
			, b(color.b)
			, a(_a) {}

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="rgb">
		/// 赤・緑・青
		/// </param>
		/// <param name="_a">
		/// アルファ [0.0, 1.0]
		/// </param>
		explicit ColorF(const Vec3& rgb, double _a = 1.0) noexcept;

		/// <summary>
		/// 色をコピーします。
		/// </summary>
		/// <param name="color">
		/// コピーする色
		/// </param>
		constexpr ColorF(const Color& color) noexcept
			: r(color.r / 255.0)
			, g(color.g / 255.0)
			, b(color.b / 255.0)
			, a(color.a / 255.0) {}

		/// <summary>
		/// 色をコピーします。
		/// </summary>
		/// <param name="hsv">
		/// コピーする色
		/// </param>
		ColorF(const HSV& hsv) noexcept;

		/// <summary>
		/// 色をカラーコードから作成します。
		/// </summary>
		/// <param name="code">
		/// "#FFF" または "#FFFFFF" のように # から始まるカラーコード
		/// </param>
		explicit ColorF(StringView code) noexcept
			: ColorF(Color(code)) {}

		/// <summary>
		/// 新しい色を代入します。
		/// </summary>
		/// <param name="color">
		/// 新しい色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr ColorF& operator =(const ColorF& color) noexcept = default;

		/// <summary>
		/// 新しい色を代入します。
		/// </summary>
		/// <param name="color">
		/// 新しい色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr ColorF& operator =(const Color& color) noexcept
		{
			r = color.r / 255.0;
			g = color.g / 255.0;
			b = color.b / 255.0;
			a = color.a / 255.0;
			return *this;
		}

		/// <summary>
		/// 新しい色を代入します。
		/// </summary>
		/// <param name="hsv">
		/// 新しい色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		ColorF& operator =(const HSV& hsv) noexcept;

		/// <summary>
		/// 色の成分を加算します
		/// </summary>
		/// <param name="color">
		/// 加算する値
		/// </param>
		/// <returns>
		/// 加算した色
		/// </returns>
		constexpr ColorF operator +(const ColorF& color) const noexcept
		{
			return{ r + color.r, g + color.g, b + color.b, a };
		}

		/// <summary>
		/// 色の成分を加算します
		/// </summary>
		/// <param name="color">
		/// 加算する値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr ColorF& operator +=(const ColorF& color) noexcept
		{
			r += color.r;
			g += color.g;
			b += color.b;
			return *this;
		}

		/// <summary>
		/// 色の成分を減算します
		/// </summary>
		/// <param name="color">
		/// 減算する値
		/// </param>
		/// <returns>
		/// 減算した色
		/// </returns>
		constexpr ColorF operator -(const ColorF& color) const noexcept
		{
			return{ r - color.r, g - color.g, b - color.b, a };
		}

		/// <summary>
		/// 色の成分を減算します
		/// </summary>
		/// <param name="color">
		/// 減算する値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr ColorF& operator -=(const ColorF& color) noexcept
		{
			r -= color.r;
			g -= color.g;
			b -= color.b;
			return *this;
		}

		/// <summary>
		/// 色の成分を乗算します
		/// </summary>
		/// <param name="s">
		/// 乗算する値
		/// </param>
		/// <returns>
		/// 乗算した結果
		/// </returns>
		constexpr ColorF operator *(const double s) const noexcept
		{
			return{ r * s, g * s, b * s, a };
		}

		/// <summary>
		/// 色の成分を乗算します
		/// </summary>
		/// <param name="s">
		/// 乗算する値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr ColorF& operator *=(const double s) noexcept
		{
			r *= s;
			g *= s;
			b *= s;
			return *this;
		}

		/// <summary>
		/// 色の成分を乗算します
		/// </summary>
		/// <param name="color">
		/// 乗算する値
		/// </param>
		/// <returns>
		/// 乗算した色
		/// </returns>
		constexpr ColorF operator *(const ColorF& color) const noexcept
		{
			return{ r * color.r, g * color.g, b * color.b, a * color.a };
		}

		/// <summary>
		/// 色の成分を乗算します
		/// </summary>
		/// <param name="color">
		/// 乗算する値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr ColorF& operator *=(const ColorF& color) noexcept
		{
			r *= color.r;
			g *= color.g;
			b *= color.b;
			a *= color.a;
			return *this;
		}

		/// <summary>
		/// 色を変更します。
		/// </summary>
		/// <param name="_r">
		/// 赤 [0.0, 1.0]
		/// </param>
		/// <param name="_g">
		/// 緑 [0.0, 1.0]
		/// </param>
		/// <param name="_b">
		/// 青 [0.0, 1.0]
		/// </param>
		/// <param name="_a">
		/// アルファ [0.0, 1.0]
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr ColorF& set(const double _r, const double _g, const double _b, const double _a = 1.0) noexcept
		{
			r = _r;
			g = _g;
			b = _b;
			a = _a;
			return *this;
		}

		/// <summary>
		/// RGB の値を変更します。
		/// </summary>
		/// <param name="rgb">
		/// 新しい色のグレースケール [0.0, 1.0]
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr ColorF& setRGB(const double rgb) noexcept
		{
			r = g = b = rgb;
			return *this;
		}

		/// <summary>
		/// アルファ値を変更します。
		/// </summary>
		/// <param name="_a">
		/// 新しいアルファ値 [0.0, 1.0]
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		constexpr ColorF& setA(const double _a) noexcept
		{
			a = _a;
			return *this;
		}
		
		/// <summary>
		/// Color 型に変換した値を返します。
		/// </summary>
		/// <remarks>
		/// 各成分は [0.0, 1.0] にクランプして変換されます。
		/// </remarks>
		/// <returns>
		/// 変換した値
		/// </returns>
		constexpr Color toColor() const noexcept
		{
			return Color(r >= 1.0 ? 255 : r <= 0.0 ? 0 : static_cast<uint8>(r * 255.0 + 0.5)
					   , g >= 1.0 ? 255 : g <= 0.0 ? 0 : static_cast<uint8>(g * 255.0 + 0.5)
					   , b >= 1.0 ? 255 : b <= 0.0 ? 0 : static_cast<uint8>(b * 255.0 + 0.5)
					   , a >= 1.0 ? 255 : a <= 0.0 ? 0 : static_cast<uint8>(a * 255.0 + 0.5));
		}

		Float4 toFloat4() const;

		Vec4 toVec4() const;

		/// <summary>
		/// ガンマを適用した値を返します。
		/// </summary>
		/// <param name="gamma">
		/// ガンマ値
		/// </param>
		/// <returns>
		/// ガンマを適用した値
		/// </returns>
		ColorF gamma(double gamma) const noexcept;

		/// <summary>
		/// グレースケール値 [0.0, 1.0] を計算します。
		/// </summary>
		/// <returns>
		/// グレースケール値
		/// </returns>
		constexpr double grayscale() const noexcept
		{
			return 0.299 * r + 0.587 * g + 0.114 * b;
		}

		constexpr ColorF lerp(const ColorF& other, const double f) const noexcept
		{
			return{ r + (other.r - r) * f,
					g + (other.g - g) * f,
					b + (other.b - b) * f,
					a + (other.a - a) * f };
		}

		/// <summary>
		/// Vec2(r, g)
		/// </summary>
		Vec2 rg() const noexcept;

		/// <summary>
		/// Vec2(g, b)
		/// </summary>
		Vec2 gb() const noexcept;

		/// <summary>
		/// Vec2(b, a)
		/// </summary>
		Vec2 ba() const noexcept;

		/// <summary>
		/// Vec3(r, g, b)
		/// </summary>
		Vec3 rgb() const noexcept;

		/// <summary>
		/// Vec3(g, b, a)
		/// </summary>
		Vec3 gba() const noexcept;

		/// <summary>
		/// Vec3(b, g, r)
		/// </summary>
		Vec3 bgr() const noexcept;

		/// <summary>
		/// Vec4(r, g, b, a)
		/// </summary>
		Vec4 rgba() const noexcept;

		/// <summary>
		/// Vec4(a, r, g, b)
		/// </summary>
		Vec4 argb() const noexcept;

		/// <summary>
		/// Vec4(a, b, g, r)
		/// </summary>
		Vec4 abgr() const noexcept;
	};

	/// <summary>
	/// 色の成分を乗算します
	/// </summary>
	/// <param name="s">
	/// 乗算する値
	/// </param>
	/// <param name="color">
	/// 乗算する色
	/// </param>
	/// <returns>
	/// 乗算した結果
	/// </returns>
	inline constexpr ColorF operator *(const double s, const ColorF& color) noexcept
	{
		return{ s * color.r, s * color.g, s * color.b, color.a };
	}

	/// <summary>
	/// Color(255, 255, 255, alpha) を返します。
	/// </summary>
	/// <param name="alpha">
	/// アルファ値
	/// </param>
	/// <returns>
	/// Color(255, 255, 255, alpha)
	/// </returns>
	inline constexpr Color Alpha(const uint32 alpha) noexcept
	{
		return Color(255, alpha);
	}

	/// <summary>
	/// ColorF(1.0, 1.0, 1.0, alpha) を返します。
	/// </summary>
	/// <param name="alpha">
	/// アルファ値
	/// </param>
	/// <returns>
	/// ColorF(1.0, 1.0, 1.0, alpha)
	/// </returns>
	inline constexpr ColorF AlphaF(const double alpha) noexcept
	{
		return ColorF(1.0, alpha);
	}

	/// <summary>
	/// 色をコピーします。
	/// </summary>
	/// <param name="color">
	/// コピーする色
	/// </param>
	inline constexpr Color::Color(const ColorF& color) noexcept
		: r(color.r >= 1.0 ? 255 : color.r <= 0.0 ? 0 : static_cast<uint8>(color.r * 255.0 + 0.5))
		, g(color.g >= 1.0 ? 255 : color.g <= 0.0 ? 0 : static_cast<uint8>(color.g * 255.0 + 0.5))
		, b(color.b >= 1.0 ? 255 : color.b <= 0.0 ? 0 : static_cast<uint8>(color.b * 255.0 + 0.5))
		, a(color.a >= 1.0 ? 255 : color.a <= 0.0 ? 0 : static_cast<uint8>(color.a * 255.0 + 0.5)) {}

	/// <summary>
	/// 新しい色を代入します。
	/// </summary>
	/// <param name="color">
	/// 新しい色
	/// </param>
	/// <returns>
	/// *this
	/// </returns>
	inline constexpr Color& Color::operator =(const ColorF& color) noexcept
	{
		return *this = color.toColor();
	}
}

namespace std
{
	template <>
	struct hash<s3d::Color>
	{
		size_t operator()(const s3d::Color& keyVal) const
		{
			return hash<s3d::uint32>()(*((s3d::uint32*)&keyVal));
		}
	};
}

# include "ColorPalette.hpp"

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Color
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[x] istream
//	[x] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	void Formatter(FormatData& formatData, const Color& value);

	/// <summary>
	/// 出力ストリームに色を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="color">
	/// 色
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Color& color)
	{
		return os << CharType('(')
			<< color.r << CharType(',')
			<< color.g << CharType(',')
			<< color.b << CharType(',')
			<< color.a << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに色を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="color">
	/// 色
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Color& color)
	{
		uint32 cols[4];
		CharType unused;

		is >> unused
			>> cols[0] >> unused
			>> cols[1] >> unused
			>> cols[2] >> unused;

		if (unused == CharType(','))
		{
			is >> cols[3] >> unused;
		}
		else
		{
			cols[3] = 255;
		}

		color.r = cols[0];
		color.g = cols[1];
		color.b = cols[2];
		color.a = cols[3];

		return is;
	}
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting ColorF
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[x] istream
//	[x] wistream
//	[x] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	void Formatter(FormatData& formatData, const ColorF& value);

	/// <summary>
	/// 出力ストリームに色を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="color">
	/// 色
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const ColorF& color)
	{
		return os << CharType('(')
			<< color.r << CharType(',')
			<< color.g << CharType(',')
			<< color.b << CharType(',')
			<< color.a << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに色を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="color">
	/// 色
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, ColorF& color)
	{
		CharType unused;

		is >> unused
			>> color.r >> unused
			>> color.g >> unused
			>> color.b >> unused;

		if (unused == CharType(','))
		{
			is >> color.a >> unused;
		}
		else
		{
			color.a = 1.0;
		}

		return is;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::ColorF& color)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("},{") + tag + S3DSTR("})");

		f.writer().write(fmt, color.r, color.g, color.b, color.a);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
