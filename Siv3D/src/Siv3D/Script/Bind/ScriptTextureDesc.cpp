//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/TextureDesc.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterTextureDesc(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "TextureDesc";
			r = engine->RegisterEnumValue(TypeName, "Unmipped", static_cast<int32>(TextureDesc::Unmipped)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "UnmippedSRGB", static_cast<int32>(TextureDesc::UnmippedSRGB)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Mipped", static_cast<int32>(TextureDesc::Mipped)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "MippedSRGB", static_cast<int32>(TextureDesc::MippedSRGB)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "SDF", static_cast<int32>(TextureDesc::SDF)); assert(r >= 0);
		}
	}
}
