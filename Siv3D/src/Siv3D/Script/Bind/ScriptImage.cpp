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
# include <Siv3D/Image.hpp>
# include <Siv3D/Icon.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = Image;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const BindType& image, BindType* self)
	{
		new(self) BindType(image);
	}

	static void Image_FactoryI(size_t size, BindType* self)
	{
		new(self) BindType(size);
	}

	static void Image_FactoryIC(size_t size, const Color& color, BindType* self)
	{
		new(self) BindType(size, color);
	}

	static void Image_FactoryP(const Point& size, BindType* self)
	{
		new(self) BindType(size);
	}

	static void Image_FactoryPC(const Point& size, const Color& color, BindType* self)
	{
		new(self) BindType(size, color);
	}

	static void Image_FactoryII(size_t w, size_t h, BindType* self)
	{
		new(self) BindType(w, h);
	}

	static void Image_FactoryIIC(size_t w, size_t h, const Color& color, BindType* self)
	{
		new(self) BindType(w, h, color);
	}

	static void ConstructF(const FilePath& path, BindType* self)
	{
		new(self) BindType(path);
	}

	static void ConstructFF(const FilePath& rgb, const FilePath& alpha, BindType* self)
	{
		new(self) BindType(rgb, alpha);
	}

	static void ConstructCF(const ColorF& rgb, const FilePath& alpha, BindType* self)
	{
		new(self) BindType(rgb, alpha);
	}

	static void ConstructEm(const Emoji& emoji, BindType* self)
	{
		new(self) BindType(emoji);
	}

	static void ConstructIcI(const Icon& icon, int32 size, BindType* self)
	{
		new(self) BindType(icon, size);
	}

	static void Destruct(BindType* self)
	{
		self->~Image();
	}

	static Color* OpIndexUU(size_t x, size_t y, BindType* image)
	{
		const size_t index = y * image->width() + x;

		if (index >= image->num_pixels())
		{
			asIScriptContext* ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Image::operator[]: Index out of bounds");
			return nullptr;
		}

		return (image->data() + index);
	}

	static const Color* OpIndexUUC(size_t x, size_t y, const BindType* image)
	{
		const size_t index = y * image->width() + x;

		if (index >= image->num_pixels())
		{
			asIScriptContext* ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Image::operator[]: Index out of bounds");
			return nullptr;
		}

		return (image->data() + index);
	}

	static Color* OpIndexP(const Point& pos, BindType* image)
	{
		const size_t index = pos.y * image->width() + pos.x;

		if (index >= image->num_pixels())
		{
			asIScriptContext* ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Image::operator[]: Index out of bounds");
			return nullptr;
		}

		return (image->data() + index);
	}

	static const Color* OpIndexPC(const Point& pos, const BindType* image)
	{
		const size_t index = pos.y * image->width() + pos.x;

		if (index >= image->num_pixels())
		{
			asIScriptContext* ctx = asGetActiveContext();
			if (ctx)
				ctx->SetException("Image::operator[]: Index out of bounds");
			return nullptr;
		}

		return (image->data() + index);
	}

	static bool ConvToBool(const BindType& image)
	{
		return static_cast<bool>(image);
	}

	void RegisterImage(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Image";

		int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Image& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(size_t size)", asFUNCTION(Image_FactoryI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(size_t size, const Color& in)", asFUNCTION(Image_FactoryIC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in)", asFUNCTION(Image_FactoryP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Point& in, const Color& in)", asFUNCTION(Image_FactoryPC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(size_t w, size_t h)", asFUNCTION(Image_FactoryII), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(size_t w, size_t h, const Color& in)", asFUNCTION(Image_FactoryIIC), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in)", asFUNCTION(ConstructF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, const String& in)", asFUNCTION(ConstructFF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Color& in, const String& in)", asFUNCTION(ConstructCF), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Emoji& in)", asFUNCTION(ConstructEm), asCALL_CDECL_OBJLAST); assert(r >= 0);
		//r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Icon& in, int32)", asFUNCTION(ConstructIcI), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

	}
}
