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
# include <Siv3D/TexturePixelFormat.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterTexturePixelFormat(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "TexturePixelFormat";
			r = engine->RegisterEnumValue(TypeName, "Unknown", static_cast<int32>(TexturePixelFormat::Unknown)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "R8G8B8A8_Unorm", static_cast<int32>(TexturePixelFormat::R8G8B8A8_Unorm)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "R8G8B8A8_Unorm_SRGB", static_cast<int32>(TexturePixelFormat::R8G8B8A8_Unorm_SRGB)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "R16G16_Float", static_cast<int32>(TexturePixelFormat::R16G16_Float)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "R32_Float", static_cast<int32>(TexturePixelFormat::R32_Float)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "R10G10B10A2_Unorm", static_cast<int32>(TexturePixelFormat::R10G10B10A2_Unorm)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "R11G11B10_UFloat", static_cast<int32>(TexturePixelFormat::R11G11B10_UFloat)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "R16G16B16A16_Float", static_cast<int32>(TexturePixelFormat::R16G16B16A16_Float)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "R32G32_Float", static_cast<int32>(TexturePixelFormat::R32G32_Float)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "R32G32B32A32_Float", static_cast<int32>(TexturePixelFormat::R32G32B32A32_Float)); assert(r >= 0);
		}
	}
}
