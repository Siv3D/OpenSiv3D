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
# include "Common.hpp"
# include "IAddon.hpp"
# include "StringView.hpp"

namespace s3d
{
	/// @brief アドオン関連の機能
	namespace Addon
	{
		/// @brief アドオンを登録します。
		/// @param name アドオンの名前
		/// @param pAddon アドオン
		/// @param priority アドオンリスト内での処理の優先度。数値が大きいほど先に実行されます
		/// @return アドオンの登録に成功した場合 true, それ以外の場合は false
		bool Register(StringView name, std::unique_ptr<IAddon>&& pAddon, int32 priority = 0);

		/// @brief アドオンを登録します。
		/// @tparam AddonType アドオンクラス
		/// @param name アドオンの名前
		/// @param priority アドオンリスト内での処理の優先度。数値が大きいほど先に実行されます
		/// @return アドオンの登録に成功した場合 true, それ以外の場合は false
		template <class AddonType, std::enable_if_t<std::is_base_of_v<IAddon, AddonType>>* = nullptr>
		bool Register(StringView name, int32 priority = 0);

		/// @brief 指定した名前のアドオンの登録を解除します。
		/// @param name アドオンの名前
		void Unregister(StringView name);

		/// @brief すべてのアドオンを登録解除します。
		void UnregisterAll();

		/// @brief 指定した名前のアドオンが登録されているかを返します。
		/// @param name アドオンの名前
		/// @return アドオンが登録されている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsRegistered(StringView name);

		/// @brief アドオンへのポインタを取得します。
		/// @param name アドオンの名前
		/// @return アドオンが登録されている場合、アドオンへのポインタ。それ以外の場合は nullptr
		[[nodiscard]]
		IAddon* GetIAddon(StringView name);

		/// @brief アドオンへのポインタを取得します。
		/// @tparam AddonType アドオンクラス
		/// @param name アドオンの名前
		/// @return アドオンが登録されている場合、アドオンへのポインタ。それ以外の場合は nullptr
		template <class AddonType>
		[[nodiscard]]
		AddonType* GetAddon(StringView name);
	}
}

# include "detail/Addon.ipp"
