//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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

		static void Wait(AssetNameView name);

		[[nodiscard]]
		static bool IsReady(AssetNameView name);

		static void Release(AssetNameView name);

		static void ReleaseAll();

		static void Unregister(AssetNameView name);

		static void UnregisterAll();

		[[nodiscard]]
		static HashTable<AssetName, AssetInfo> Enumerate();
	};
}
