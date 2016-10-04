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
# include "Fwd.hpp"
# include "Array.hpp"
# include "Color.hpp"
# include "PointVector.hpp"
# include "Grid.hpp"

namespace s3d
{
	/// <summary>
	/// 画像
	/// </summary>
	/// <remarks>
	/// メモリ上に確保される画像データです。
	/// ピクセル単位のアクセスや、変形、エフェクト処理を適用できます。
	/// イメージを描画する場合は Texture に変換する必要があります。
	/// </remarks>
	class Image
	{
	private:

		Array<Color> m_data;

		uint32 m_width = 0;

		uint32 m_height = 0;

		static constexpr bool IsValidSize(size_t width, size_t height)
		{
			return width <= MaxSize && height <= MaxSize;
		}

	public:

		using iterator					= Array<Color>::iterator;
		using const_iterator			= Array<Color>::const_iterator;
		using reverse_iterator			= Array<Color>::reverse_iterator;
		using const_reverse_iterator	= Array<Color>::const_reverse_iterator;

		/// <summary>
		/// 画像の最大サイズ
		/// </summary>
		static constexpr int32 MaxSize = 8192;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Image() = default;

		/// <summary>
		/// 画像を別の画像からコピーして作成します。
		/// </summary>
		/// <param name="image">
		/// コピーする画像
		/// </param>
		Image(const Image& image) = default;

		/// <summary>
		/// 画像を別の画像からムーブして作成します。
		/// </summary>
		/// <param name="image">
		/// ムーブする画像
		/// </param>
		Image(Image&& image) noexcept
			: m_data(std::move(image.m_data))
			, m_width(image.m_width)
			, m_height(image.m_height)
		{
			image.m_width = image.m_height = 0;
		}

		/// <summary>
		/// 指定したサイズの画像を作成します。
		/// </summary>
		/// <param name="size">
		/// 画像のサイズ（ピクセル）
		/// </param>
		explicit Image(const Size& size)
			: Image(size.x, size.y) {}

		/// <summary>
		/// 指定した色、サイズで塗りつぶされた画像を作成します。
		/// </summary>
		/// <param name="size">
		/// 画像のサイズ（ピクセル）
		/// </param>
		/// <param name="color">
		/// 塗りつぶしの色
		/// </param>
		Image(const Size& size, const Color& color)
			: Image(size.x, size.y, color) {}

		//Image(const Size& size, std::function<Color(Point)> generator)
		//	: Image(size.x, size.y, generator) {}

		/// <summary>
		/// 指定したサイズの画像を作成します。
		/// </summary>
		/// <param name="width">
		/// 画像の幅（ピクセル）
		/// </param>
		/// <param name="height">
		/// 画像の高さ（ピクセル）
		/// </param>
		Image(size_t width, size_t height)
			: m_data(IsValidSize(width, height) ? width*height : 0)
			, m_width(IsValidSize(width, height) ? static_cast<uint32>(width) : 0)
			, m_height(IsValidSize(width, height) ? static_cast<uint32>(height) : 0) {}

		//Image(uint32 width, uint32 height, std::function<Color(Point)> generator);

		/// <summary>
		/// 指定した色、サイズで塗りつぶされた画像を作成します。
		/// </summary>
		/// <param name="width">
		/// 画像の幅（ピクセル）
		/// </param>
		/// <param name="height">
		/// 画像の高さ（ピクセル）
		/// </param>
		/// <param name="color">
		/// 塗りつぶしの色
		/// </param>
		Image(size_t width, size_t height, const Color& color)
			: m_data(IsValidSize(width, height) ? width * height : 0, color)
			, m_width(IsValidSize(width, height) ? static_cast<uint32>(width) : 0)
			, m_height(IsValidSize(width, height) ? static_cast<uint32>(height) : 0) {}

		/// <summary>
		/// 画像ファイルから画像を作成します。
		/// </summary>
		/// <param name="path">
		/// 画像ファイルのパス
		/// </param>
		//explicit Image(const FilePath& path);

		/// <summary>
		/// Reader から画像を作成します。
		/// </summary>
		/// <param name="reader">
		/// Reader
		/// </param>
		/// <param name="format">
		/// 画像のフォーマット
		/// </param>
		//explicit Image(IReader&& reader, ImageFormat format = ImageFormat::Unspecified);

		/// <summary>
		/// 2 つの画像ファイルから画像を作成します。
		/// </summary>
		/// <param name="rgb">
		/// RGB を読み込む画像ファイルのパス
		/// </param>
		/// <param name="alpha">
		/// アルファ値を読み込む画像ファイルのパス
		/// </param>
		//Image(const FilePath& rgb, const FilePath& alpha);

		/// <summary>
		/// 画像ファイルからアルファ値を作成し、画像を作成します。
		/// </summary>
		/// <param name="rgb">
		/// RGB 成分の色
		/// </param>
		/// <param name="alpha">
		/// アルファ値を読み込む画像ファイルのパス
		/// </param>
		/// <remarks>
		/// alpha の画像の R 成分を、テクスチャのアルファ値に設定します。
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		//Image(const Color& rgb, const FilePath& alpha);

		explicit Image(const Grid<Color>& grid)
			: Image(grid.width(), grid.height())
		{
			if (m_data.empty())
			{
				return;
			}

			::memcpy(m_data.data(), grid.data(), grid.size_bytes());
		}

		explicit Image(const Grid<ColorF>& grid)
			: Image(grid.width(), grid.height())
		{
			if (m_data.empty())
			{
				return;
			}

			const ColorF* pSrc = grid.data();
			const ColorF* const pSrcEnd = pSrc + grid.size_elements();
			Color* pDst = &m_data[0];

			while (pSrc != pSrcEnd)
			{
				*pDst++ = *pSrc++;
			}
		}

		template <class Type, class Fty>
		explicit Image(const Grid<Type>& grid, Fty converter)
			: Image(grid.width(), grid.height())
		{
			if (m_data.empty())
			{
				return;
			}

			const Type* pSrc = grid.data();
			const Type* const pSrcEnd = pSrc + grid.size_elements();
			Color* pDst = &m_data[0];

			while (pSrc != pSrcEnd)
			{
				*pDst++ = converter(*pSrc++);
			}
		}

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <returns>
		/// image[y][x] で指定したピクセルにアクセスします。
		/// </returns>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		Color* operator[](uint32 y)
		{
			return &m_data[m_width * y];
		}

		Color& operator[](const Point& pos)
		{
			return m_data[m_width * pos.y + pos.x];
		}

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <returns>
		/// image[y][x] で指定したピクセルにアクセスします。
		/// </returns>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		const Color* operator[](uint32 y) const
		{
			return &m_data[m_width * y];
		}

		const Color& operator[](const Point& pos) const
		{
			return m_data[m_width * pos.y + pos.x];
		}

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		void* data()
		{
			return &m_data[0];
		}

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		const void* data() const
		{
			return &m_data[0];
		}

		/// <summary>
		/// 画像の先頭位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭位置のイテレータ
		/// </returns>
		iterator begin() noexcept { return m_data.begin(); }

		/// <summary>
		/// 画像の先頭位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭位置のイテレータ
		/// </returns>
		const_iterator begin() const noexcept { return m_data.begin(); }

		/// <summary>
		/// 画像の先頭位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭位置のイテレータ
		/// </returns>
		const_iterator cbegin() const noexcept { return m_data.cbegin(); }

		/// <summary>
		/// 画像の終了位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の終了位置のイテレータ
		/// </returns>
		iterator end() noexcept { return m_data.end(); }

		/// <summary>
		/// 画像の終了位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の終了位置のイテレータ
		/// </returns>
		const_iterator end() const noexcept { return m_data.end(); }

		/// <summary>
		/// 画像の終了位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の終了位置のイテレータ
		/// </returns>
		const_iterator cend() const noexcept { return m_data.cend(); }

		/// <summary>
		/// 画像の末尾へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の末尾へのリバースイテレータ
		/// </returns>
		reverse_iterator rbegin() noexcept { return m_data.rbegin(); }

		/// <summary>
		/// 画像の末尾へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の末尾へのリバースイテレータ
		/// </returns>
		const_reverse_iterator rbegin() const noexcept { return m_data.rbegin(); }

		/// <summary>
		/// 画像の末尾へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の末尾へのリバースイテレータ
		/// </returns>
		const_reverse_iterator crbegin() const noexcept { return m_data.crbegin(); }

		/// <summary>
		/// 画像の先頭の前へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭の前へのリバースイテレータ
		/// </returns>
		reverse_iterator rend() noexcept { return m_data.rend(); }

		/// <summary>
		/// 画像の先頭の前へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator rend() const noexcept { return m_data.rend(); }

		/// <summary>
		/// 画像の先頭の前へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator crend() const noexcept { return m_data.crend(); }







		bool _saveBMP(const FilePath&) const;
	};
}
