//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <iostream>
# include "Fwd.hpp"

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
		/// L"#FFF" または L"#FFFFFF" のように # から始まるカラーコード
		/// </param>
		explicit Color(const StringView& code) noexcept;

		/// <summary>
		/// 新しい色を代入します。
		/// </summary>
		/// <param name="color">
		/// 新しい色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Color& operator =(const Color& color) noexcept = default;

		/// <summary>
		/// 新しい色を代入します。
		/// </summary>
		/// <param name="color">
		/// 新しい色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 Color& operator =(const ColorF& color) noexcept;

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
		S3D_CONSTEXPR_CPP14 Color& set(uint32 _r, uint32 _g, uint32 _b, uint32 _a = 255) noexcept
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
		S3D_CONSTEXPR_CPP14 Color& setRGB(uint32 rgb) noexcept
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
		S3D_CONSTEXPR_CPP14 Color& setA(uint32 _a) noexcept
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

		constexpr Color lerp(const Color& other, double f) const noexcept
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
	};

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
		return os	<< CharType('(')
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

		is	>> unused
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
		/// L"#FFF" または L"#FFFFFF" のように # から始まるカラーコード
		/// </param>
		explicit ColorF(const StringView& code) noexcept
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
		S3D_CONSTEXPR_CPP14 ColorF& operator =(const ColorF& color) noexcept = default;

		/// <summary>
		/// 新しい色を代入します。
		/// </summary>
		/// <param name="color">
		/// 新しい色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		S3D_CONSTEXPR_CPP14 ColorF& operator =(const Color& color) noexcept
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
		S3D_CONSTEXPR_CPP14 ColorF& operator +=(const ColorF& color) noexcept
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
		S3D_CONSTEXPR_CPP14 ColorF& operator -=(const ColorF& color) noexcept
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
		constexpr ColorF operator *(double s) const noexcept
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
		S3D_CONSTEXPR_CPP14 ColorF& operator *=(double s) noexcept
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
		S3D_CONSTEXPR_CPP14 ColorF& operator *=(const ColorF& color) noexcept
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
		S3D_CONSTEXPR_CPP14 ColorF& set(double _r, double _g, double _b, double _a = 1.0) noexcept
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
		S3D_CONSTEXPR_CPP14 ColorF& setRGB(double rgb) noexcept
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
		S3D_CONSTEXPR_CPP14 ColorF& setA(double _a) noexcept
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

		constexpr ColorF lerp(const ColorF& other, double f) const noexcept
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
	inline constexpr ColorF operator *(double s, const ColorF& color)
	{
		return{ s * color.r, s * color.g, s * color.b, color.a };
	}

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
		return os	<< CharType('(')
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
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, ColorF& color)
	{
		CharType unused;

		is	>> unused
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

	/// <summary>
	/// Color(255, 255, 255, alpha) を返します。
	/// </summary>
	/// <param name="alpha">
	/// アルファ値
	/// </param>
	/// <returns>
	/// Color(255, 255, 255, alpha)
	/// </returns>
	inline constexpr Color Alpha(uint32 alpha)
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
	inline constexpr ColorF AlphaF(double alpha)
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
	inline S3D_CONSTEXPR_CPP14 Color& Color::operator =(const ColorF& color) noexcept
	{
		return *this = color.toColor();
	}

	/// <summary>
	/// カラーパレット
	/// </summary>
	namespace Palette
	{
		constexpr Color Black{ 0,0,0 };
		constexpr Color Dimgray{ 105,105,105 };
		constexpr Color Gray{ 128,128,128 };
		constexpr Color Darkgray{ 169,169,169 };
		constexpr Color Silver{ 192,192,192 };
		constexpr Color Lightgrey{ 211,211,211 };
		constexpr Color Gainsboro{ 220,220,220 };
		constexpr Color Whitesmoke{ 245,245,245 };
		constexpr Color White{ 255,255,255 };
		constexpr Color Snow{ 255,250,250 };
		constexpr Color Ghostwhite{ 248,248,255 };
		constexpr Color Floralwhite{ 255,250,240 };
		constexpr Color Linen{ 250,240,230 };
		constexpr Color Antiquewhite{ 250,235,215 };
		constexpr Color Papayawhip{ 255,239,213 };
		constexpr Color Blanchedalmond{ 255,235,205 };
		constexpr Color Bisque{ 255,228,196 };
		constexpr Color Moccasin{ 255,228,181 };
		constexpr Color Navajowhite{ 255,222,173 };
		constexpr Color Peachpuff{ 255,218,185 };
		constexpr Color Mistyrose{ 255,228,225 };
		constexpr Color Lavenderblush{ 255,240,245 };
		constexpr Color Seashell{ 255,245,238 };
		constexpr Color Oldlace{ 253,245,230 };
		constexpr Color Ivory{ 255,255,240 };
		constexpr Color Honeydew{ 240,255,240 };
		constexpr Color Mintcream{ 245,255,250 };
		constexpr Color Azure{ 240,255,255 };
		constexpr Color Aliceblue{ 240,248,255 };
		constexpr Color Lavender{ 230,230,250 };
		constexpr Color Lightsteelblue{ 176,196,222 };
		constexpr Color Lightslategray{ 119,136,153 };
		constexpr Color Slategray{ 112,128,144 };
		constexpr Color Steelblue{ 70,130,180 };
		constexpr Color Royalblue{ 65,105,225 };
		constexpr Color Midnightblue{ 25,25,112 };
		constexpr Color Navy{ 0,0,128 };
		constexpr Color Darkblue{ 0,0,139 };
		constexpr Color Mediumblue{ 0,0,205 };
		constexpr Color Blue{ 0,0,255 };
		constexpr Color Dodgerblue{ 30,144,255 };
		constexpr Color Cornflowerblue{ 100,149,237 };
		constexpr Color Deepskyblue{ 0,191,255 };
		constexpr Color Lightskyblue{ 135,206,250 };
		constexpr Color Skyblue{ 135,206,235 };
		constexpr Color Lightblue{ 173,216,230 };
		constexpr Color Powderblue{ 176,224,230 };
		constexpr Color Paleturquoise{ 175,238,238 };
		constexpr Color Lightcyan{ 224,255,255 };
		constexpr Color Cyan{ 0,255,255 };
		constexpr Color Aqua{ 0,255,255 };
		constexpr Color Turquoise{ 64,224,208 };
		constexpr Color Mediumturquoise{ 72,209,204 };
		constexpr Color Darkturquoise{ 0,206,209 };
		constexpr Color Lightseagreen{ 32,178,170 };
		constexpr Color Cadetblue{ 95,158,160 };
		constexpr Color Darkcyan{ 0,139,139 };
		constexpr Color Teal{ 0,128,128 };
		constexpr Color Darkslategray{ 47,79,79 };
		constexpr Color Darkgreen{ 0,100,0 };
		constexpr Color Green{ 0,128,0 };
		constexpr Color Forestgreen{ 34,139,34 };
		constexpr Color Seagreen{ 46,139,87 };
		constexpr Color Mediumseagreen{ 60,179,113 };
		constexpr Color Mediumaquamarine{ 102,205,170 };
		constexpr Color Darkseagreen{ 143,188,143 };
		constexpr Color Aquamarine{ 127,255,212 };
		constexpr Color Palegreen{ 152,251,152 };
		constexpr Color Lightgreen{ 144,238,144 };
		constexpr Color Springgreen{ 0,255,127 };
		constexpr Color Mediumspringgreen{ 0,250,154 };
		constexpr Color Lawngreen{ 124,252,0 };
		constexpr Color Chartreuse{ 127,255,0 };
		constexpr Color Greenyellow{ 173,255,47 };
		constexpr Color Lime{ 0,255,0 };
		constexpr Color Limegreen{ 50,205,50 };
		constexpr Color Yellowgreen{ 154,205,50 };
		constexpr Color Darkolivegreen{ 85,107,47 };
		constexpr Color Olivedrab{ 107,142,35 };
		constexpr Color Olive{ 128,128,0 };
		constexpr Color Darkkhaki{ 189,183,107 };
		constexpr Color Palegoldenrod{ 238,232,170 };
		constexpr Color Cornsilk{ 255,248,220 };
		constexpr Color Beige{ 245,245,220 };
		constexpr Color Lightyellow{ 255,255,224 };
		constexpr Color Lightgoldenrodyellow{ 250,250,210 };
		constexpr Color Lemonchiffon{ 255,250,205 };
		constexpr Color Wheat{ 245,222,179 };
		constexpr Color Burlywood{ 222,184,135 };
		constexpr Color Tan{ 210,180,140 };
		constexpr Color Khaki{ 240,230,140 };
		constexpr Color Yellow{ 255,255,0 };
		constexpr Color Gold{ 255,215,0 };
		constexpr Color Orange{ 255,165,0 };
		constexpr Color Sandybrown{ 244,164,96 };
		constexpr Color Darkorange{ 255,140,0 };
		constexpr Color Goldenrod{ 218,165,32 };
		constexpr Color Peru{ 205,133,63 };
		constexpr Color Darkgoldenrod{ 184,134,11 };
		constexpr Color Chocolate{ 210,105,30 };
		constexpr Color Sienna{ 160,82,45 };
		constexpr Color Saddlebrown{ 139,69,19 };
		constexpr Color Maroon{ 128,0,0 };
		constexpr Color Darkred{ 139,0,0 };
		constexpr Color Brown{ 165,42,42 };
		constexpr Color Firebrick{ 178,34,34 };
		constexpr Color Indianred{ 205,92,92 };
		constexpr Color Rosybrown{ 188,143,143 };
		constexpr Color Darksalmon{ 233,150,122 };
		constexpr Color Lightcoral{ 240,128,128 };
		constexpr Color Salmon{ 250,128,114 };
		constexpr Color Lightsalmon{ 255,160,122 };
		constexpr Color Coral{ 255,127,80 };
		constexpr Color Tomato{ 255,99,71 };
		constexpr Color Orangered{ 255,69,0 };
		constexpr Color Red{ 255,0,0 };
		constexpr Color Crimson{ 220,20,60 };
		constexpr Color Mediumvioletred{ 199,21,133 };
		constexpr Color Deeppink{ 255,20,147 };
		constexpr Color Hotpink{ 255,105,180 };
		constexpr Color Palevioletred{ 219,112,147 };
		constexpr Color Pink{ 255,192,203 };
		constexpr Color Lightpink{ 255,182,193 };
		constexpr Color Thistle{ 216,191,216 };
		constexpr Color Magenta{ 255,0,255 };
		constexpr Color Fuchsia{ 255,0,255 };
		constexpr Color Violet{ 238,130,238 };
		constexpr Color Plum{ 221,160,221 };
		constexpr Color Orchid{ 218,112,214 };
		constexpr Color Mediumorchid{ 186,85,211 };
		constexpr Color Darkorchid{ 153,50,204 };
		constexpr Color Darkviolet{ 148,0,211 };
		constexpr Color Darkmagenta{ 139,0,139 };
		constexpr Color Purple{ 128,0,128 };
		constexpr Color Indigo{ 75,0,130 };
		constexpr Color Darkslateblue{ 72,61,139 };
		constexpr Color Blueviolet{ 138,43,226 };
		constexpr Color Mediumpurple{ 147,112,219 };
		constexpr Color Slateblue{ 106,90,205 };
		constexpr Color Mediumslateblue{ 123,104,238 };
	};
}

namespace std
{
	template <>
	struct hash<s3d::Color>
	{
		size_t operator ()(const s3d::Color& keyVal) const
		{
			return hash<s3d::uint32>()(*((s3d::uint32*)&keyVal));
		}
	};
}
