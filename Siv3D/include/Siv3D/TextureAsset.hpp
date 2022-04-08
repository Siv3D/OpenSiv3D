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
# include "Texture.hpp"
# include "TextureAssetData.hpp"
# include "HashTable.hpp"

namespace s3d
{
	class TextureAsset : public Texture
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit TextureAsset(AssetNameView name);

		/// @brief テクスチャアセットを登録します。
		/// @param name テクスチャアセットの登録名
		/// @param path 登録するテクスチャのファイルパス
		/// @param desc テクスチャの設定
		static bool Register(AssetNameView name, FilePathView path, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(AssetNameView name, FilePathView rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(AssetNameView name, const Color& rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(AssetNameView name, const Emoji& emoji, TextureDesc desc = TextureDesc::Mipped);

		static bool Register(AssetNameView name, const Icon& icon, int32 size, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(AssetNameView name, std::unique_ptr<TextureAssetData>&& data);


		static bool Register(const AssetNameAndTags& nameAndTags, FilePathView path, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(const AssetNameAndTags& nameAndTags, FilePathView rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(const AssetNameAndTags& nameAndTags, const Color& rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		static bool Register(const AssetNameAndTags& nameAndTags, const Emoji& emoji, TextureDesc desc = TextureDesc::Mipped);

		static bool Register(const AssetNameAndTags& nameAndTags, const Icon& icon, int32 size, TextureDesc desc = TextureDesc::Unmipped);


		/// @brief 指定したテクスチャアセットが登録されているかを返します。
		/// @param name テクスチャアセット名
		/// @return 登録されている場合 true, それ以外の場合は false
		[[nodiscard]]
		static bool IsRegistered(AssetNameView name);

		/// @brief 指定したテクスチャアセットを直ちにロードします。
		/// @param name テクスチャアセット名
		/// @remark この関数はロード処理が終了するまで制御を返しません。
		/// @return ロードに成功した場合 true, それ以外の場合は false
		static bool Load(AssetNameView name);

		/// @brief 指定したテクスチャアセットの非同期ロードを開始します。
		/// @param name テクスチャアセット名
		static void LoadAsync(AssetNameView name);

		/// @brief 指定したテクスチャアセットのロードが完了するまで待機します。
		/// @param name テクスチャアセット名
		static void Wait(AssetNameView name);

		/// @brief 指定したテクスチャアセットのロード処理が（成否にかかわらず）完了しているかを返します。
		/// @param name テクスチャアセット名
		/// @return ロード処理が（成否にかかわらず）完了している場合 true, それ以外の場合は false
		[[nodiscard]]
		static bool IsReady(AssetNameView name);

		/// @brief 指定したテクスチャアセットについて、ロードしたデータをメモリ上から削除します。登録状態は維持されます。
		/// @param name テクスチャアセット名
		static void Release(AssetNameView name);

		/// @brief すべてのテクスチャアセットについて、ロードしたデータをメモリ上から削除します。登録状態は維持されます。
		static void ReleaseAll();

		/// @brief 指定したテクスチャアセットについて、ロードしたデータをメモリ上から削除し、登録も解除します。
		/// @param name テクスチャアセット名
		static void Unregister(AssetNameView name);

		/// @brief すべてのテクスチャアセットについて、ロードしたデータをメモリ上から削除し、登録も解除します。
		static void UnregisterAll();

		/// @brief 登録されているテクスチャアセットの情報一覧を取得します。
		/// @return 登録されているテクスチャアセットの情報一覧
		[[nodiscard]]
		static HashTable<AssetName, AssetInfo> Enumerate();
	};
}
