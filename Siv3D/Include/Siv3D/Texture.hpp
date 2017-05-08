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

		struct Render {};

		explicit Texture(BackBuffer);

		Texture(Render, const Size& size, uint32 multisampleCount);

	public:

		using IDType = TextureHandle::IDType;

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
	};
}
