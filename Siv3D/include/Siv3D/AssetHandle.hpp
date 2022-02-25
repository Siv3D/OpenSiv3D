//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "AssetIDWrapper.hpp"

namespace s3d
{
	/// @brief アセットハンドル
	/// @tparam AssetType アセットのタグ
	template <class AssetType>
	class AssetHandle
	{
	public:

		/// @brief アセット ID ラッパー型
		using AssetIDWrapperType = AssetIDWrapper<AssetHandle>;

		/// @brief アセット ID 型
		using IDType = typename AssetIDWrapperType::IDType;

		SIV3D_NODISCARD_CXX20
		AssetHandle();

		SIV3D_NODISCARD_CXX20
		explicit AssetHandle(std::shared_ptr<AssetIDWrapperType>&& id);

		/// @brief アセットの内部管理 ID を返します。
		/// @remark アセットが作成されるときに割り当てられる（同じ種類のアセット内で）一意の値です。
		/// @return アセットの内部管理 ID
		[[nodiscard]]
		IDType id() const noexcept;

		/// @brief アセットが空であるかを返します。
		/// @return アセットが空の場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief アセットが空でないかを返します。
		/// @return アセットが空でない場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 2 つのアセットが同じオブジェクトであるかを返します。
		/// @param other 比較するオブジェクト 
		/// @return 2 つのアセットが同じオブジェクトである場合 true, それ以外の場合は false
		[[nodiscard]]
		bool operator ==(const AssetHandle& other) const noexcept;

		/// @brief 2 つのアセットが異なるオブジェクトであるかを返します。
		/// @param other 比較するオブジェクト 
		/// @return 2 つのアセットが異なるオブジェクトである場合 true, それ以外の場合は false
		[[nodiscard]]
		bool operator !=(const AssetHandle& other) const noexcept;

		/// @brief このハンドルが管理するアセットを解放します。
		/// @remark 解放されたアセットは空になります。
		void release();

	protected:

		std::shared_ptr<AssetIDWrapperType> m_handle;
	};
}

# include "detail/AssetHandle.ipp"
