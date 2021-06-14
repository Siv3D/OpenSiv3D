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

namespace s3d
{
	class FontAsset : public Font
	{
	public:

		explicit FontAsset(AssetNameView name);

		static bool Register(const AssetName& name, int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		static bool Register(const AssetName& name, int32 fontSize, FilePathView path, size_t faceIndex, FontStyle style = FontStyle::Default);
		
		static bool Register(const AssetName& name, int32 fontSize, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default);
		
		static bool Register(const AssetName& name, FontMethod fontMethod, int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);
		
		static bool Register(const AssetName& name, FontMethod fontMethod, int32 fontSize, FilePathView path, size_t faceIndex, FontStyle style = FontStyle::Default);

		static bool Register(const AssetName& name, FontMethod fontMethod, int32 fontSize, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default);
	
		static bool Register(const AssetName& name, std::unique_ptr<FontAssetData>&& data);

		[[nodiscard]]
		static bool IsRegistered(AssetNameView name);
	};
}
