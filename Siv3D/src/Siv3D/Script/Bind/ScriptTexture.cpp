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

# include <Siv3D/Script.hpp>
# include <Siv3D/Texture.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Texture;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const Texture& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void Destruct(BindType* self)
	{
		self->~Texture();
	}

	//static void ConstructIT(const Image& image, TextureDesc desc, BindType* self)
	//{
	//	new(self) BindType(image, desc);
	//}

	//static void ConstructFT(const FilePath& path, TextureDesc desc, BindType* self)
	//{
	//	new(self) BindType(path, desc);
	//}

	//static void ConstructFFT(const FilePath& rgb, const FilePath& alpha, TextureDesc desc, BindType* self)
	//{
	//	new(self) BindType(rgb, alpha, desc);
	//}

	//static void ConstructCFT(const Color& rgb, const FilePath& alpha, TextureDesc desc, BindType* self)
	//{
	//	new(self) BindType(rgb, alpha, desc);
	//}

	//static void ConstructEmT(const Emoji& emoji, TextureDesc desc, BindType* self)
	//{
	//	new(self) BindType(emoji, desc);
	//}

	//static void ConstructIcT(const Icon& icon, TextureDesc desc, BindType* self)
	//{
	//	new(self) BindType(icon, desc);
	//}

	//static bool ConvToBool(const Texture& texture)
	//{
	//	return !texture.isEmpty();
	//}

	//static TextureRegion ConvToTextureRegion(const Texture& texture)
	//{
	//	return texture;
	//}

	void RegisterTexture(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Texture";

		int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Texture& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Image& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructIT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		////	Texture(const Image& image, const Array<Image>& mipmaps, TextureDesc desc = TextureDesc::Mipped);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		////explicit Texture(IReader&& reader, TextureDesc desc = TextureDesc::Unmipped);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructFFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, const String& in, TextureDesc = TextureDesc::Unmipped)", asFUNCTION(ConstructCFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Emoji& in, TextureDesc = TextureDesc::Mipped)", asFUNCTION(ConstructEmT), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Icon& in, TextureDesc = TextureDesc::Mipped)", asFUNCTION(ConstructIcT), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
