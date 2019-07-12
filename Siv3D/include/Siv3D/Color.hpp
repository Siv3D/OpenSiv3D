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
		[[nodiscard]] constexpr Color operator ~() const noexcept
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
		[[nodiscard]] bool operator ==(const Color& color) const noexcept
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
		[[nodiscard]] bool operator !=(const Color& color) const noexcept
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

		constexpr Color& set(const Color& color) noexcept
		{
			return *this = color;
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

		constexpr Color& setRGB(uint32 _r, uint32 _g, uint32 _b) noexcept
		{
			r = _r;
			g = _g;
			b = _b;
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
		[[nodiscard]] constexpr uint8 grayscale0_255() const noexcept
		{
			return static_cast<uint8>(0.299*r + 0.587*g + 0.114*b);
		}

		/// <summary>
		/// グレースケール値 [0.0, 1.0] を計算します。
		/// </summary>
		/// <returns>
		/// グレースケール値
		/// </returns>
		[[nodiscard]] constexpr double grayscale() const noexcept
		{
			return (0.299 / 255.0 * r) + (0.587 / 255.0 * g) + (0.114 / 255.0 * b);
		}

		[[nodiscard]] uint32 asUint32() const noexcept
		{
			return *static_cast<const uint32*>(static_cast<const void*>(this));
		}

		[[nodiscard]] constexpr Color lerp(const Color& other, const double f) const noexcept
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
		[[nodiscard]] Color gamma(double gamma) const noexcept;

		[[nodiscard]] String toHex() const;

		[[nodiscard]] size_t hash() const noexcept;
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
		/// 色を作成します。
		/// </summary>
		/// <param name="rgba">
		/// 赤・緑・青・アルファ [0.0, 1.0]
		/// </param>
		explicit ColorF(const Vec4& rgba) noexcept;

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
		[[nodiscard]] constexpr ColorF operator +(const ColorF& color) const noexcept
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
		[[nodiscard]] constexpr ColorF operator -(const ColorF& color) const noexcept
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
		[[nodiscard]] constexpr ColorF operator *(const double s) const noexcept
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
		[[nodiscard]] constexpr ColorF operator *(const ColorF& color) const noexcept
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
		/// 色が等しいかを調べます。
		/// </summary>
		/// <param name="color">
		/// 比較対象の色
		/// </param>
		/// <returns>
		/// 等しければ true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool operator ==(const ColorF& color) const noexcept
		{
			return (r == color.r) && (g == color.g) && (b == color.b) && (a == color.a);
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
		[[nodiscard]] bool operator !=(const ColorF& color) const noexcept
		{
			return (r != color.r) || (g != color.g) || (b != color.b) || (a != color.a);
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

		constexpr ColorF& set(const ColorF& color) noexcept
		{
			return *this = color;
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

		constexpr ColorF& setRGB(const double _r, const double _g, const double _b) noexcept
		{
			r = _r;
			g = _g;
			b = _b;
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
		[[nodiscard]] constexpr Color toColor() const noexcept
		{
			return Color(r >= 1.0 ? 255 : r <= 0.0 ? 0 : static_cast<uint8>(r * 255.0 + 0.5)
					   , g >= 1.0 ? 255 : g <= 0.0 ? 0 : static_cast<uint8>(g * 255.0 + 0.5)
					   , b >= 1.0 ? 255 : b <= 0.0 ? 0 : static_cast<uint8>(b * 255.0 + 0.5)
					   , a >= 1.0 ? 255 : a <= 0.0 ? 0 : static_cast<uint8>(a * 255.0 + 0.5));
		}

		[[nodiscard]] Float4 toFloat4() const;

		[[nodiscard]] Vec4 toVec4() const;

		/// <summary>
		/// ガンマを適用した値を返します。
		/// </summary>
		/// <param name="gamma">
		/// ガンマ値
		/// </param>
		/// <returns>
		/// ガンマを適用した値
		/// </returns>
		[[nodiscard]] ColorF gamma(double gamma) const noexcept;

		/// <summary>
		/// グレースケール値 [0.0, 1.0] を計算します。
		/// </summary>
		/// <returns>
		/// グレースケール値
		/// </returns>
		[[nodiscard]] constexpr double grayscale() const noexcept
		{
			return 0.299 * r + 0.587 * g + 0.114 * b;
		}

		[[nodiscard]] constexpr ColorF lerp(const ColorF& other, const double f) const noexcept
		{
			return{ r + (other.r - r) * f,
					g + (other.g - g) * f,
					b + (other.b - b) * f,
					a + (other.a - a) * f };
		}

		/// <summary>
		/// Vec2(r, g)
		/// </summary>
		[[nodiscard]] Vec2 rg() const noexcept;

		/// <summary>
		/// Vec2(g, b)
		/// </summary>
		[[nodiscard]] Vec2 gb() const noexcept;

		/// <summary>
		/// Vec2(b, a)
		/// </summary>
		[[nodiscard]] Vec2 ba() const noexcept;

		/// <summary>
		/// Vec3(r, g, b)
		/// </summary>
		[[nodiscard]] Vec3 rgb() const noexcept;

		/// <summary>
		/// Vec3(g, b, a)
		/// </summary>
		[[nodiscard]] Vec3 gba() const noexcept;

		/// <summary>
		/// Vec3(b, g, r)
		/// </summary>
		[[nodiscard]] Vec3 bgr() const noexcept;

		/// <summary>
		/// Vec4(r, g, b, a)
		/// </summary>
		[[nodiscard]] Vec4 rgba() const noexcept;

		/// <summary>
		/// Vec4(a, r, g, b)
		/// </summary>
		[[nodiscard]] Vec4 argb() const noexcept;

		/// <summary>
		/// Vec4(a, b, g, r)
		/// </summary>
		[[nodiscard]] Vec4 abgr() const noexcept;

		[[nodiscard]] size_t hash() const noexcept;
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
	[[nodiscard]] inline constexpr ColorF operator *(const double s, const ColorF& color) noexcept
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
	[[nodiscard]] inline constexpr Color Alpha(const uint32 alpha) noexcept
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
	[[nodiscard]] inline constexpr ColorF AlphaF(const double alpha) noexcept
	{
		return ColorF(1.0, alpha);
	}

	/// <summary>
	/// ColorF(1.0, 1.0, 1.0, 1.0 - transparency) を返します。
	/// </summary>
	/// <param name="transparency">
	/// 透明度 [0.0, 1.0]
	/// </param>
	/// <returns>
	/// ColorF(1.0, 1.0, 1.0, 1.0 - transparency)
	/// </returns>
	[[nodiscard]] inline constexpr ColorF Transparency(const double transparency) noexcept
	{
		return ColorF(1.0, 1.0 - transparency);
	}

	[[nodiscard]] inline constexpr Color ToColor(const float rgb) noexcept
	{
		return Color((rgb >= 1.0f ? 255 : rgb <= 0.0f ? 0 : static_cast<uint8>(rgb * 255.0f + 0.5f)));
	}

	[[nodiscard]] inline constexpr Color ToColor(const double rgb) noexcept
	{
		return Color(rgb >= 1.0 ? 255 : rgb <= 0.0 ? 0 : static_cast<uint8>(rgb * 255.0 + 0.5));
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

# include "ColorPalette.hpp"

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Color& value);

	void Formatter(FormatData& formatData, const ColorF& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Color& value)
	{
		return output << CharType('(')
			<< value.r << CharType(',') << CharType(' ')
			<< value.g << CharType(',') << CharType(' ')
			<< value.b << CharType(',') << CharType(' ')
			<< value.a << CharType(')');
	}

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const ColorF& value)
	{
		return output << CharType('(')
			<< value.r << CharType(',') << CharType(' ')
			<< value.g << CharType(',') << CharType(' ')
			<< value.b << CharType(',') << CharType(' ')
			<< value.a << CharType(')');
	}

	std::istream& operator >>(std::istream& input, Color& value);
	std::wistream& operator >>(std::wistream& input, Color& value);

	std::istream& operator >>(std::istream& input, ColorF& value);
	std::wistream& operator >>(std::wistream& input, ColorF& value);
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::Color>
	{
		[[nodiscard]] size_t operator ()(const s3d::Color& value) const noexcept
		{
			return value.hash();
		}
	};

	template <>
	struct hash<s3d::ColorF>
	{
		[[nodiscard]] size_t operator ()(const s3d::ColorF& value) const noexcept
		{
			return value.hash();
		}
	};
}

//////////////////////////////////////////////////
//
//	fmt
//
//////////////////////////////////////////////////

namespace fmt_s3d
{
	template <>
	struct formatter<s3d::Color, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Color& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.r, value.g, value.b, value.a);
		}
	};

	template <>
	struct formatter<s3d::ColorF, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::ColorF& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.r, value.g, value.b, value.a);
		}
	};
}
