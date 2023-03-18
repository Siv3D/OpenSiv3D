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
# include <Siv3D/TextureFormat.hpp>

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

	static void ConstructT(int32 value, BindType* self)
	{
		new(self) BindType(ToEnum<TexturePixelFormat>(static_cast<uint8>(value)));
	}

	static bool Equals(const BindType& other, const BindType& value)
	{
		return (value == other);
	}

	void RegisterTextureFormat(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "TextureFormat";

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TextureFormat &in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(TexturePixelFormat)", asFUNCTION(ConstructT), asCALL_CDECL_OBJLAST); assert(r >= 0);

			//value()
			//name()
			r = engine->RegisterObjectMethod(TypeName, "int32 DXGIFormat() const", asMETHODPR(BindType, DXGIFormat, () const, int32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "int32 GLInternalFormat() const", asMETHODPR(BindType, GLInternalFormat, () const, int32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "int32 GLFormat() const", asMETHODPR(BindType, GLFormat, () const, int32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "int32 GLType() const", asMETHODPR(BindType, GLType, () const, int32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "uint32 pixelSize() const", asMETHODPR(BindType, pixelSize, () const, uint32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "uint32 num_channels() const", asMETHODPR(BindType, num_channels, () const, uint32), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isSRGB() const", asMETHODPR(BindType, isSRGB, () const, bool), asCALL_THISCALL); assert(r >= 0);

			//
			// ==
			//
			r = engine->RegisterObjectMethod(TypeName, "bool opEquals(const TextureFormat& in) const", asFUNCTION(Equals), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
			{
				r = engine->RegisterGlobalProperty("const TexturePixelFormat Unknown", (void*)&TextureFormat::Unknown); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const TexturePixelFormat R8G8B8A8_Unorm", (void*)&TextureFormat::R8G8B8A8_Unorm); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const TexturePixelFormat R8G8B8A8_Unorm_SRGB", (void*)&TextureFormat::R8G8B8A8_Unorm_SRGB); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const TexturePixelFormat R16G16_Float", (void*)&TextureFormat::R16G16_Float); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const TexturePixelFormat R32_Float", (void*)&TextureFormat::R32_Float); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const TexturePixelFormat R10G10B10A2_Unorm", (void*)&TextureFormat::R10G10B10A2_Unorm); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const TexturePixelFormat R11G11B10_UFloat", (void*)&TextureFormat::R11G11B10_UFloat); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const TexturePixelFormat R16G16B16A16_Float", (void*)&TextureFormat::R16G16B16A16_Float); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const TexturePixelFormat R32G32_Float", (void*)&TextureFormat::R32G32_Float); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const TexturePixelFormat R32G32B32A32_Float", (void*)&TextureFormat::R32G32B32A32_Float); assert(r >= 0);
			}
			r = engine->SetDefaultNamespace(""); assert(r >= 0);
		}
	}
}
