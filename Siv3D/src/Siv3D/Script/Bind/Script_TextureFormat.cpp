//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/TextureFormat.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = TextureFormat;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const TextureFormat& format, BindType* self)
	{
		new(self) BindType(format);
	}

	static void ConstructT(TextureFormatValue value, BindType* self)
	{
		new(self) BindType(value);
	}

	void RegisterTextureFormat(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "TextureFormat";

		int32 r = 0;

		r = engine->RegisterEnumValue("TextureFormatValue", "Unknown", static_cast<int32>(TextureFormatValue::Unknown)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormatValue", "R8G8B8A8_Unorm", static_cast<int32>(TextureFormatValue::R8G8B8A8_Unorm)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormatValue", "R8G8B8A8_Unorm_SRGB", static_cast<int32>(TextureFormatValue::R8G8B8A8_Unorm_SRGB)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormatValue", "R16G16_Float", static_cast<int32>(TextureFormatValue::R16G16_Float)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormatValue", "R32_Float", static_cast<int32>(TextureFormatValue::R32_Float)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormatValue", "R10G10B10A2_Unorm", static_cast<int32>(TextureFormatValue::R10G10B10A2_Unorm)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormatValue", "R11G11B10_UFloat", static_cast<int32>(TextureFormatValue::R11G11B10_UFloat)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormatValue", "R16G16B16A16_Float", static_cast<int32>(TextureFormatValue::R16G16B16A16_Float)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormatValue", "R32G32_Float", static_cast<int32>(TextureFormatValue::R32G32_Float)); assert(r >= 0);
		r = engine->RegisterEnumValue("TextureFormatValue", "R32G32B32A32_Float", static_cast<int32>(TextureFormatValue::R32G32B32A32_Float)); assert(r >= 0);



		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TextureFormat &in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(TextureFormatValue value)", asFUNCTION(ConstructT), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const TextureFormat& in) const", asMETHOD(BindType, operator==), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const TextureFormatValue Unknown", (void*)& TextureFormat::Unknown); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const TextureFormatValue R8G8B8A8_Unorm", (void*)& TextureFormat::R8G8B8A8_Unorm); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const TextureFormatValue R8G8B8A8_Unorm_SRGB", (void*)& TextureFormat::R8G8B8A8_Unorm_SRGB); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const TextureFormatValue R16G16_Float", (void*)& TextureFormat::R16G16_Float); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const TextureFormatValue R32_Float", (void*)& TextureFormat::R32_Float); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const TextureFormatValue R10G10B10A2_Unorm", (void*)& TextureFormat::R10G10B10A2_Unorm); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const TextureFormatValue R11G11B10_UFloat", (void*)& TextureFormat::R11G11B10_UFloat); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const TextureFormatValue R16G16B16A16_Float", (void*)& TextureFormat::R16G16B16A16_Float); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const TextureFormatValue R32G32_Float", (void*)& TextureFormat::R32G32_Float); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const TextureFormatValue R32G32B32A32_Float", (void*)& TextureFormat::R32G32B32A32_Float); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
