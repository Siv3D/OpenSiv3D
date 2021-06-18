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
# include "Audio.hpp"
# include "AudioAssetData.hpp"
# include "HashTable.hpp"

namespace s3d
{
	class AudioAsset : public Audio
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit AudioAsset(AssetNameView name);

		//static bool Register(const AssetName& name, int32 fontSize, FilePathView path, AudioStyle style = AudioStyle::Default);

		//static bool Register(const AssetName& name, int32 fontSize, FilePathView path, size_t faceIndex, AudioStyle style = AudioStyle::Default);
		//
		//static bool Register(const AssetName& name, int32 fontSize, Typeface typeface = Typeface::Regular, AudioStyle style = AudioStyle::Default);
		//
		//static bool Register(const AssetName& name, AudioMethod fontMethod, int32 fontSize, FilePathView path, AudioStyle style = AudioStyle::Default);
		//
		//static bool Register(const AssetName& name, AudioMethod fontMethod, int32 fontSize, FilePathView path, size_t faceIndex, AudioStyle style = AudioStyle::Default);

		//static bool Register(const AssetName& name, AudioMethod fontMethod, int32 fontSize, Typeface typeface = Typeface::Regular, AudioStyle style = AudioStyle::Default);
	
		static bool Register(const AssetName& name, std::unique_ptr<AudioAssetData>&& data);


		//static bool Register(const AssetNameAndTags& nameAndTags, int32 fontSize, FilePathView path, AudioStyle style = AudioStyle::Default);

		//static bool Register(const AssetNameAndTags& nameAndTags, int32 fontSize, FilePathView path, size_t faceIndex, AudioStyle style = AudioStyle::Default);

		//static bool Register(const AssetNameAndTags& nameAndTags, int32 fontSize, Typeface typeface = Typeface::Regular, AudioStyle style = AudioStyle::Default);

		//static bool Register(const AssetNameAndTags& nameAndTags, AudioMethod fontMethod, int32 fontSize, FilePathView path, AudioStyle style = AudioStyle::Default);

		//static bool Register(const AssetNameAndTags& nameAndTags, AudioMethod fontMethod, int32 fontSize, FilePathView path, size_t faceIndex, AudioStyle style = AudioStyle::Default);

		//static bool Register(const AssetNameAndTags& nameAndTags, AudioMethod fontMethod, int32 fontSize, Typeface typeface = Typeface::Regular, AudioStyle style = AudioStyle::Default);


		[[nodiscard]]
		static bool IsRegistered(AssetNameView name);

		static bool Load(AssetNameView name);

		static void LoadAsync(AssetNameView name);

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

