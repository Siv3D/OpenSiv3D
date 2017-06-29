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
	class Texture
	{
	protected:

		class Handle {};

		using TextureHandle = AssetHandle<Handle>;
		
		friend TextureHandle::~AssetHandle();

		std::shared_ptr<TextureHandle> m_handle;

		struct BackBuffer {};

		explicit Texture(BackBuffer);

	public:

		using IDType = TextureHandle::IDType;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Texture();

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
