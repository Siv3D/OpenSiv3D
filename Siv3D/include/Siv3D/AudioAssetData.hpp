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
# include "AsyncTask.hpp"

namespace s3d
{
	struct AudioAssetData : IAsset
	{
		FilePath path;

		Optional<AudioLoopTiming> loopTiming;

		bool streaming = false;

		Audio audio;

		std::function<bool(AudioAssetData&, const String&)> onLoad = DefaultLoad;

		std::function<void(AudioAssetData&)> onRelease = DefaultRelease;

		SIV3D_NODISCARD_CXX20
		AudioAssetData();

		//SIV3D_NODISCARD_CXX20
		//AudioAssetData(AudioMethod _fontMethod, int32 _fontSize, FilePathView _path, size_t _faceIndex, AudioStyle _style, const Array<AssetTag>& tags = {});

		//SIV3D_NODISCARD_CXX20
		//AudioAssetData(AudioMethod _fontMethod, int32 _fontSize, Typeface _typeface, AudioStyle _tyle, const Array<AssetTag>& tags = {});

		bool load(const String& hint) override;

		void loadAsync(const String& hint) override;

		void wait() override;

		void release() override;

		static bool DefaultLoad(AudioAssetData& asset, const String& hint);

		static void DefaultRelease(AudioAssetData& asset);

	private:

		AsyncTask<void> m_task;
	};
}
