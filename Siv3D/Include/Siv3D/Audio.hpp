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
# include "Wave.hpp"

namespace s3d
{
	class Audio
	{
	protected:

		class Handle {};

		using AudioHandle = AssetHandle<Handle>;

		friend AudioHandle::~AssetHandle();

		std::shared_ptr<AudioHandle> m_handle;

	public:

		using IDType = AudioHandle::IDType;

		static constexpr IDType NullHandleID = AudioHandle::NullID;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Audio();

		explicit Audio(const Wave& wave);

		explicit Audio(const FilePath& path);

		//explicit Audio(IReader&& reader);

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Audio();

		/// <summary>
		/// オーディオをリリースします。
		/// </summary>
		/// <remarks>
		/// プログラムのほかの場所で同じオーディオが使われていない場合、オーディオのメモリを解放します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		/// <summary>
		/// オーディオが空かどうかを示します。
		/// </summary>
		bool isEmpty() const;

		/// <summary>
		/// オーディオが空ではないかを返します。
		/// </summary>
		/// <returns>
		/// オーディオが空ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const
		{
			return !isEmpty();
		}

		/// <summary>
		/// オーディオハンドルの ID を示します。
		/// </summary>
		IDType id() const;

		/// <summary>
		/// 2 つの Audio が同じかどうかを返します。
		/// </summary>
		/// <param name="audio">
		/// 比較する Audio
		/// </param>
		/// <returns>
		/// 2 つの Audio が同じ場合 true, それ以外の場合は false
		/// </returns>
		bool operator ==(const Audio& audio) const;

		/// <summary>
		/// 2 つの Audio が異なるかどうかを返します。
		/// </summary>
		/// <param name="audio">
		/// 比較する Audio
		/// </param>
		/// <returns>
		/// 2 つの Audio が異なる場合 true, それ以外の場合は false
		/// </returns>
		bool operator !=(const Audio& audio) const;
	};
}
