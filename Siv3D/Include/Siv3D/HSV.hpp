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
# include "Color.hpp"
# include "Utility.hpp"

namespace s3d
{
	/// <summary>
	/// HSV カラー
	/// </summary>
	/// <remarks>
	/// 色を 色相(H), 彩度(S), 明度(V), アルファで表現します。
	/// </remarks>
	struct HSV
	{
		/// <summary>
		/// 色相 |Hue [0.0, 360.0)
		/// </summary>
		double h;

		/// <summary>
		/// 彩度 | Saturation [0.0, 1.0]
		/// </summary>
		double s;

		/// <summary>
		/// 明度 | Value [0.0, 1.0]
		/// </summary>
		double v;

		/// <summary>
		/// アルファ | Alpha [0.0, 1.0]
		/// </summary>
		double a;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		HSV() = default;

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		constexpr HSV(const HSV&) noexcept = default;

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="_h">
		/// 色相 [0.0, 360.0)
		/// </param>
		/// <param name="_a">
		/// アルファ [0.0, 1.0]
		/// </param>
		explicit constexpr HSV(double _h, double _a = 1.0) noexcept
			: h(_h)
			, s(1.0)
			, v(1.0)
			, a(_a) {}

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="_h">
		/// 色相 [0.0, 360.0)
		/// </param>
		/// <param name="_s">
		/// 彩度 [0.0, 1.0]
		/// </param>
		/// <param name="_v">
		/// 明度 [0.0, 1.0]
		/// </param>
		/// <param name="_a">
		/// アルファ [0.0, 1.0]
		/// </param>
		constexpr HSV(double _h, double _s, double _v, double _a = 1.0) noexcept
			: h(_h)
			, s(_s)
			, v(_v)
			, a(_a) {}

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="color">
		/// RGB カラー
		/// </param>
		HSV(const Color& color) noexcept;

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="col">
		/// RGB カラー
		/// </param>
		HSV(const ColorF& col) noexcept;

		/// <summary>
		/// HSV の値を加算します。
		/// </summary>
		/// <param name="hsv">
		/// 加算する値
		/// </param>
		/// <returns>
		/// 加算した結果
		/// </returns>
		constexpr HSV operator +(const HSV& hsv) const noexcept
		{
			return{ h + hsv.h, Clamp(s + hsv.s, 0.0, 1.0), Clamp(v + hsv.v, 0.0, 1.0), a };
		}

		/// <summary>
		/// HSV の値を減算します。
		/// </summary>
		/// <param name="hsv">
		/// 減算する値
		/// </param>
		/// <returns>
		/// 減算した結果
		/// </returns>
		constexpr HSV operator -(const HSV& hsv) const noexcept
		{
			return{ h - hsv.h, Clamp(s - hsv.s, 0.0, 1.0), Clamp(v - hsv.v, 0.0, 1.0), a };
		}

		constexpr HSV lerp(const HSV& other, double f) const noexcept
		{
			return{ h + (other.h - h) * f,
					s + (other.s - s) * f,
					v + (other.v - v) * f,
					a + (other.a - a) * f };
		}

		/// <summary>
		/// RGB 値から HSV 値に変換します。
		/// </summary>
		/// <param name="r">
		/// R [0.0, 1.0]
		/// </param>
		/// <param name="g">
		/// G [0.0, 1.0]
		/// </param>
		/// <param name="b">
		/// B [0.0, 1.0]
		/// </param>
		/// <param name="_a">
		/// A [0.0, 1.0]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void convertFrom(double r, double g, double b, double a = 1.0) noexcept;

		/// <summary>
		/// Color 型に変換します。
		/// </summary>
		/// <returns>
		/// 変換した値
		/// </returns>
		Color toColor() const noexcept;

		/// <summary>
		/// Color 型に変換します。
		/// </summary>
		/// <param name="alpha">
		/// アルファ値 [0, 255]
		/// </param>
		/// <returns>
		/// 変換した値
		/// </returns>
		Color toColor(uint32 alpha) const noexcept
		{
			return toColor().setA(alpha);
		}

		/// <summary>
		/// ColorF 型に変換します。
		/// </summary>
		/// <returns>
		/// 変換した値
		/// </returns>
		ColorF toColorF() const noexcept;

		/// <summary>
		/// ColorF 型に変換します。
		/// </summary>
		/// <param name="alpha">
		/// アルファ値 [0.0, 1.0]
		/// </param>
		/// <returns>
		/// 変換した値
		/// </returns>
		ColorF toColorF(double alpha) const noexcept
		{
			return toColorF().setA(alpha);
		}
	};

	/// <summary>
	/// 出力ストリームに色を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="hsv">
	/// 色
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const HSV& hsv)
	{
		return os	<< CharType('(')
					<< hsv.h << CharType(',')
					<< hsv.s << CharType(',')
					<< hsv.v << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに色を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="hsv">
	/// 色
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, HSV& hsv)
	{
		CharType unused;

		return is	>> unused
					>> hsv.h >> unused
					>> hsv.s >> unused
					>> hsv.v >> unused;
	}

	/// <summary>
	/// 色相から Color を作成します。
	/// </summary>
	/// <param name="hue">
	/// 色相 [0.0, 360.0)
	/// </param>
	/// <returns>
	/// 作成したカラー
	/// </returns>
	Color HueToColor(double hue) noexcept;

	/// <summary>
	/// 色相から ColorF を作成します。
	/// </summary>
	/// <param name="hue">
	/// 色相 [0.0, 360.0)
	/// </param>
	/// <returns>
	/// 作成したカラー
	/// </returns>
	ColorF HueToColorF(double hue) noexcept;
}
