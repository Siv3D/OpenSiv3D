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
# include "Array.hpp"
# include "AssetHandle.hpp"
# include "Rectangle.hpp"
# include "Image.hpp"

namespace s3d
{
	/// <summary>
	/// テクスチャの設定
	/// </summary>
	enum class TextureDesc
	{
		/// <summary>
		/// ミップマップなし
		/// </summary>
		Unmipped,

		/// <summary>
		/// ミップマップなし、sRGB
		/// </summary>
		UnmippedSRGB,

		/// <summary>
		/// ミップマップあり
		/// </summary>
		Mipped,

		/// <summary>
		/// ミップマップあり、sRGB
		/// </summary>
		MippedSRGB,

		/// <summary>
		/// Signed Distance Field
		/// </summary>
		SDF,

		/// <summary>
		/// 3D 用のテクスチャのデフォルト [ミップマップあり、sRGB]
		/// </summary>
		For3D = MippedSRGB,
	};

	class Texture
	{
	protected:

		class Handle {};

		using TextureHandle = AssetHandle<Handle>;
		
		friend TextureHandle::~AssetHandle();

		std::shared_ptr<TextureHandle> m_handle;

		struct BackBuffer {};

		struct Dynamic {};

		struct Render {};

		explicit Texture(BackBuffer);

		Texture(Dynamic, uint32 width, uint32 height, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc);

		Texture(Dynamic, uint32 width, uint32 height, const ColorF& color, TextureFormat format, TextureDesc desc);

		Texture(Render, const Size& size, uint32 multisampleCount);

	public:

		using IDType = TextureHandle::IDType;

		static constexpr IDType NullHandleID = TextureHandle::NullID;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Texture();

		/// <summary>
		/// 画像からテクスチャを作成します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// 画像が空の場合、空のテクスチャを作成します。
		/// </remarks>
		explicit Texture(const Image& image, TextureDesc desc = TextureDesc::Unmipped);


		Texture(const Image& image, const Array<Image>& mipmaps, TextureDesc desc = TextureDesc::Mipped);

		/// <summary>
		/// 画像ファイルからテクスチャを作成します。
		/// </summary>
		/// <param name="path">
		/// 画像ファイルのパス
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		explicit Texture(const FilePath& path, TextureDesc desc = TextureDesc::Unmipped);

		explicit Texture(IReader&& reader, TextureDesc desc = TextureDesc::Unmipped);

		/// <summary>
		/// 2 つの画像ファイルからテクスチャを作成します。
		/// </summary>
		/// <param name="rgb">
		/// RGB を読み込む画像ファイルのパス
		/// </param>
		/// <param name="alpha">
		/// アルファ値を読み込む画像ファイルのパス
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// alpha の画像の R 成分を、テクスチャのアルファ値に設定します。
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		Texture(const FilePath& rgb, const FilePath& alpha, TextureDesc desc = TextureDesc::Unmipped);

		/// <summary>
		/// 画像ファイルからアルファ値を作成し、テクスチャを作成します。
		/// </summary>
		/// <param name="rgb">
		/// RGB 成分の色
		/// </param>
		/// <param name="alpha">
		/// アルファ値を読み込む画像ファイルのパス
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// alpha の画像の R 成分を、テクスチャのアルファ値に設定します。
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		Texture(const Color& rgb, const FilePath& alpha, TextureDesc desc = TextureDesc::Unmipped);

		explicit Texture(const Emoji& emoji, TextureDesc desc = TextureDesc::Unmipped);

		explicit Texture(const Icon& icon, TextureDesc desc = TextureDesc::Unmipped);

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Texture();

		/// <summary>
		/// テクスチャをリリースします。
		/// </summary>
		/// <remarks>
		/// プログラムのほかの場所で同じテクスチャが使われていない場合、テクスチャのメモリを解放します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		/// <summary>
		/// テクスチャが空かどうかを示します。
		/// </summary>
		bool isEmpty() const;

		/// <summary>
		/// テクスチャが空ではないかを返します。
		/// </summary>
		/// <returns>
		/// テクスチャが空ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const
		{
			return !isEmpty();
		}

		/// <summary>
		/// テクスチャハンドルの ID を示します。
		/// </summary>
		IDType id() const;

		/// <summary>
		/// 2 つの Texture が同じかどうかを返します。
		/// </summary>
		/// <param name="texture">
		/// 比較する Texture
		/// </param>
		/// <returns>
		/// 2 つの Texture が同じ場合 true, それ以外の場合は false
		/// </returns>
		bool operator ==(const Texture& texture) const;

		/// <summary>
		/// 2 つの Texture が異なるかどうかを返します。
		/// </summary>
		/// <param name="texture">
		/// 比較する Texture
		/// </param>
		/// <returns>
		/// 2 つの Texture が異なる場合 true, それ以外の場合は false
		/// </returns>
		bool operator !=(const Texture& texture) const;

		int32 width() const;

		int32 height() const;

		Size size() const;

		TextureDesc getDesc() const;

		bool isMipped() const;

		bool isSDF() const;

		Rect region(int32 x, int32 y) const
		{
			return{ x, y, size() };
		}

		Rect region(const Point& pos = Point(0, 0)) const
		{
			return region(pos.x, pos.y);
		}

		RectF region(double x, double y) const
		{
			return{ x, y, size() };
		}

		RectF region(const Vec2& pos) const
		{
			return region(pos.x, pos.y);
		}

		RectF regionAt(double x, double y) const
		{
			const Size s = size();
			return{ x - s.x * 0.5, y - s.y * 0.5, s };
		}

		RectF regionAt(const Vec2& pos) const
		{
			return regionAt(pos.x, pos.y);
		}

		/// <summary>
		/// テクスチャを描きます。
		/// </summary>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw(const ColorF& diffuse = Palette::White) const
		{
			return draw(0.0, 0.0, diffuse);
		}

		/// <summary>
		/// 指定した位置にテクスチャを描きます。
		/// </summary>
		/// <param name="x">
		/// 描画開始位置の X 座標
		/// </param>
		/// <param name="y">
		/// 描画開始位置の Y 座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		/// <summary>
		/// 指定した位置にテクスチャを描きます。
		/// </summary>
		/// <param name="pos">
		/// 描画開始位置
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw(const Vec2& pos, const ColorF& diffuse = Palette::White) const
		{
			return draw(pos.x, pos.y, diffuse);
		}

		RectF draw(Arg::topLeft_<Vec2> topLeft, const ColorF& diffuse = Palette::White) const
		{
			return draw(topLeft->x, topLeft->y, diffuse);
		}

		RectF draw(Arg::topRight_<Vec2> topRight, const ColorF& diffuse = Palette::White) const
		{
			return draw(topRight->x - width(), topRight->y, diffuse);
		}

		RectF draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& diffuse = Palette::White) const
		{
			return draw(bottomLeft->x, bottomLeft->y - height(), diffuse);
		}

		RectF draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF& diffuse = Palette::White) const
		{
			return draw(bottomRight->x - width(), bottomRight->y - height(), diffuse);
		}

		RectF draw(Arg::topCenter_<Vec2> topCenter, const ColorF& diffuse = Palette::White) const
		{
			return draw(topCenter->x - width() * 0.5, topCenter->y, diffuse);
		}

		RectF draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& diffuse = Palette::White) const
		{
			return draw(bottomCenter->x - width() * 0.5, bottomCenter->y - height(), diffuse);
		}

		RectF draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF& diffuse = Palette::White) const
		{
			return draw(leftCenter->x, leftCenter->y - height() * 0.5, diffuse);
		}

		RectF draw(Arg::rightCenter_<Vec2>rightCenter, const ColorF& diffuse = Palette::White) const
		{
			return draw(rightCenter->x - width(), rightCenter->y - height() * 0.5, diffuse);
		}

		RectF draw(Arg::center_<Vec2> center, const ColorF& diffuse = Palette::White) const
		{
			return drawAt(center->x, center->y, diffuse);
		}

		/// <summary>
		/// 中心位置を指定してテクスチャを描きます。
		/// </summary>
		/// <param name="x">
		/// 中心位置の X 座標
		/// </param>
		/// <param name="y">
		/// 中心位置の X 座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		/// <summary>
		/// 中心位置を指定してテクスチャを描きます。
		/// </summary>
		/// <param name="pos">
		/// 中心位置の座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const
		{
			return drawAt(pos.x, pos.y, diffuse);
		}

		TextureRegion operator ()(double x, double y, double w, double h) const;

		TextureRegion operator ()(const Vec2& xy, double w, double h) const;

		TextureRegion operator ()(double x, double y, double size) const;

		TextureRegion operator ()(double x, double y, const Vec2& size) const;

		TextureRegion operator ()(const Vec2& xy, const Vec2& size) const;

		/// <summary>
		/// テクスチャ内の範囲を表す TextureRegion を返します。
		/// </summary>
		/// <param name="rect">
		/// 範囲（ピクセル）
		/// </param>
		/// <returns>
		/// テクスチャの範囲を表す TextureRegion
		/// </returns>
		TextureRegion operator ()(const RectF& rect) const;

		TextureRegion uv(double u, double v, double w, double h) const;

		TextureRegion uv(const RectF& rect) const;

		TextureRegion mirror() const;

		TextureRegion mirror(bool doMirror) const;

		TextureRegion flip() const;

		TextureRegion flip(bool doFlip) const;

		TextureRegion scale(double s) const;

		TextureRegion scale(double xs, double ys) const;

		TextureRegion scale(const Vec2& s) const;

		TextureRegion resize(double size) const;

		TextureRegion resize(double width, double height) const;

		TextureRegion resize(const Vec2& size) const;

		TextureRegion repeat(double xRepeat, double yRepeat) const;

		TextureRegion repeat(const Vec2& _repeat) const;

		TextureRegion map(double width, double height) const;

		TextureRegion map(const Vec2& size) const;

		TexturedQuad rotate(double angle) const;

		TexturedQuad rotateAt(double x, double y, double angle) const;

		TexturedQuad rotateAt(const Vec2& pos, double angle) const;
	};
}
