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
# include "LicenseInfo.hpp"
# include "Array.hpp"

namespace s3d
{
	namespace LicenseManager
	{
		/// @brief ライセンス情報一覧の先頭にアプリケーションのライセンスを追加します。
		/// @param applicationName アプリケーションの名前
		/// @param license ライセンス情報
		void SetApplicationLicense(const String& applicationName, const LicenseInfo& license);

		/// @brief ライセンス情報の一覧に新しい要素を追加します。
		/// @param license ライセンス情報
		void AddLicense(const LicenseInfo& license);

		/// @brief ライセンス情報一覧を返します。
		/// @return ライセンス情報一覧
		[[nodiscard]]
		const Array<LicenseInfo>& EnumLicenses();

		/// @brief [F1] キーでライセンス情報を表示する挙動を有効にします（デフォルトでは有効）。
		void EnableDefaultTrigger();

		/// @brief [F1] キーでライセンス情報を表示する挙動を無効化します。
		void DisableDefaultTrigger();

		/// @brief ライセンス情報を Web ブラウザで表示します。
		void ShowInBrowser();
	}
}
