//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "Color.hpp"
# include "NamedParameter.hpp"
# include "PointVector.hpp"
# include "Grid.hpp"
# include "ImageFormat.hpp"

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

		static Image Generate(const size_t width, const size_t height, std::function<Color(void)> generator);

		template <class Fty>
		static Image Generate(const size_t width, const size_t height, Fty generator)
		{
			Image new_image(width, height);

			if (!new_image.isEmpty())
			{
				Color* pDst = new_image[0];

				for (uint32 y = 0; y < height; ++y)
				{
					for (uint32 x = 0; x < width; ++x)
					{
						(*pDst++) = generator({ x, y });
					}
				}
			}

			return new_image;
		}

		static Image Generate0_1(const size_t width, const size_t height, std::function<Color(Vec2)> generator);

		static constexpr bool IsValidSize(const size_t width, const size_t height)
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

		Image(const Size& size, Arg::generator_<std::function<Color(void)>> generator)
			: Image(size.x, size.y, generator) {}

		Image(const Size& size, Arg::generator_<std::function<Color(Point)>> generator)
			: Image(size.x, size.y, generator) {}

		Image(const Size& size, Arg::generator_<std::function<Color(Vec2)>> generator)
			: Image(size.x, size.y, generator) {}

		Image(const Size& size, Arg::generator0_1_<std::function<Color(Vec2)>> generator)
			: Image(size.x, size.y, generator) {}

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
			: m_data(IsValidSize(width, height) ? width * height : 0)
			, m_width(IsValidSize(width, height) ? static_cast<uint32>(width) : 0)
			, m_height(IsValidSize(width, height) ? static_cast<uint32>(height) : 0) {}

		Image(uint32 width, uint32 height, Arg::generator_<std::function<Color(void)>> generator)
			: Image(Generate(width, height, *generator)) {}

		Image(uint32 width, uint32 height, Arg::generator_<std::function<Color(Point)>> generator)
			: Image(Generate(width, height, *generator)) {}

		Image(uint32 width, uint32 height, Arg::generator_<std::function<Color(Vec2)>> generator)
			: Image(Generate(width, height, *generator)) {}

		Image(uint32 width, uint32 height, Arg::generator0_1_<std::function<Color(Vec2)>> generator)
			: Image(Generate0_1(width, height, *generator)) {}

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
		explicit Image(const FilePath& path);

		/// <summary>
		/// Reader から画像を作成します。
		/// </summary>
		/// <param name="reader">
		/// Reader
		/// </param>
		/// <param name="format">
		/// 画像のフォーマット
		/// </param>
		explicit Image(IReader&& reader, ImageFormat format = ImageFormat::Unspecified);

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

		explicit Image(const Grid<Color>& grid);

		explicit Image(const Grid<ColorF>& grid);

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
		/// 新しい画像を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい画像
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Image& operator =(const Image& image) = default;

		/// <summary>
		/// 新しい画像を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい画像
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Image& operator =(Image&& image) = default;

		Image& assign(const Image& image)
		{
			return operator =(image);
		}

		Image& assign(Image&& image)
		{
			return operator =(std::move(image));
		}

		/// <summary>
		/// 画像の幅（ピクセル）
		/// </summary>
		int32 width() const noexcept
		{
			return m_width;
		}

		/// <summary>
		/// 画像の高さ（ピクセル）
		/// </summary>
		int32 height() const noexcept
		{
			return m_height;
		}

		/// <summary>
		/// 画像の幅と高さ（ピクセル）
		/// </summary>
		Size size() const noexcept
		{
			return{ m_width, m_height };
		}

		/// <summary>
		/// 画像の各行のデータサイズ
		/// </summary>
		uint32 stride() const noexcept
		{
			return m_width * sizeof(Color);
		}

		/// <summary>
		/// 画像のピクセル数
		/// </summary>
		uint32 num_pixels() const noexcept
		{
			return m_width * m_height;
		}

		/// <summary>
		/// 画像のデータサイズ
		/// </summary>
		uint32 memorySize() const
		{
			return stride() * m_height;
		}

		/// <summary>
		/// 画像が空かどうかを示します。
		/// </summary>
		bool isEmpty() const
		{
			return m_data.empty();
		}

		/// <summary>
		/// 画像の不要なメモリ消費を削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void shrink_to_fit()
		{
			m_data.shrink_to_fit();
		}

		/// <summary>
		/// 画像を消去し、空の画像にします。
		/// </summary>
		/// <remarks>
		/// メモリを解放したい場合は shrink_to_fit() を呼びます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void clear()
		{
			m_data.clear();

			m_width = m_height = 0;
		}

		void release()
		{
			clear();

			shrink_to_fit();
		}

		/// <summary>
		/// 画像を指定した色で塗りつぶします。
		/// </summary>
		/// <param name="color">
		/// 塗りつぶしの色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void fill(const Color& color)
		{
			for (auto& pixel : m_data)
			{
				pixel = color;
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







		void resize(size_t width, size_t height);


		bool save(const FilePath& path, ImageFormat format = ImageFormat::Unspecified) const;
	};
}
