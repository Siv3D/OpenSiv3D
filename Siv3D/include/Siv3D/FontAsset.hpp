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
# include "Asset.hpp"
# include "Font.hpp"
# include "FontAssetData.hpp"
# include "HashTable.hpp"

namespace s3d
{
	class FontAsset : public Font
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit FontAsset(AssetNameView name);

		static bool Register(AssetNameView name, int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		static bool Register(AssetNameView name, int32 fontSize, FilePathView path, size_t faceIndex, FontStyle style = FontStyle::Default);
		
		static bool Register(AssetNameView name, int32 fontSize, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default);
		
		static bool Register(AssetNameView name, FontMethod fontMethod, int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);
		
		static bool Register(AssetNameView name, FontMethod fontMethod, int32 fontSize, FilePathView path, size_t faceIndex, FontStyle style = FontStyle::Default);

		static bool Register(AssetNameView name, FontMethod fontMethod, int32 fontSize, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default);
	
		static bool Register(AssetNameView name, std::unique_ptr<FontAssetData>&& data);


		static bool Register(const AssetNameAndTags& nameAndTags, int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		static bool Register(const AssetNameAndTags& nameAndTags, int32 fontSize, FilePathView path, size_t faceIndex, FontStyle style = FontStyle::Default);

		static bool Register(const AssetNameAndTags& nameAndTags, int32 fontSize, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default);

		static bool Register(const AssetNameAndTags& nameAndTags, FontMethod fontMethod, int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		static bool Register(const AssetNameAndTags& nameAndTags, FontMethod fontMethod, int32 fontSize, FilePathView path, size_t faceIndex, FontStyle style = FontStyle::Default);

		static bool Register(const AssetNameAndTags& nameAndTags, FontMethod fontMethod, int32 fontSize, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default);


		[[nodiscard]]
		static bool IsRegistered(AssetNameView name);

		static bool Load(AssetNameView name, const String& preloadText = U"");

		static void LoadAsync(AssetNameView name, const String& preloadText = U"");

		/// @brief 指定したフォントアセットのロードが完了するまで待機します。
		/// @param name フォントアセット名
		static void Wait(AssetNameView name);

		/// @brief 指定したフォントアセットのロード処理が（成否にかかわらず）完了しているかを返します。
		/// @param name フォントアセット名
		/// @return ロード処理が（成否にかかわらず）完了している場合 true, それ以外の場合は false
		[[nodiscard]]
		static bool IsReady(AssetNameView name);

		/// @brief 指定したフォントアセットについて、ロードしたデータをメモリ上から削除します。登録状態は維持されます。
		/// @param name フォントアセット名
		static void Release(AssetNameView name);

		/// @brief すべてのフォントアセットについて、ロードしたデータをメモリ上から削除します。登録状態は維持されます。
		static void ReleaseAll();

		/// @brief 指定したフォントアセットについて、ロードしたデータをメモリ上から削除し、登録も解除します。
		/// @param name フォントアセット名
		static void Unregister(AssetNameView name);

		/// @brief すべてのフォントアセットについて、ロードしたデータをメモリ上から削除し、登録も解除します。
		static void UnregisterAll();

		/// @brief 登録されているフォントアセットの情報一覧を取得します。
		/// @return 登録されているフォントアセットの情報一覧
		[[nodiscard]]
		static HashTable<AssetName, AssetInfo> Enumerate();
	};
}
