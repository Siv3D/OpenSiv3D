//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = RefWrapper<Image>;

	BindType* DefaultConstruct()
	{
		return new BindType();
	}

	BindType* CopyConstruct(const BindType& image)
	{
		return new BindType(image);
	}

	BindType* Image_FactoryII(int32 w, int32 h)
	{
		return new BindType(w, h);
	}

	BindType* Image_FactoryIIC(int32 w, int32 h, const Color& color)
	{
		return new BindType(w, h, color);
	}

	BindType* Image_FactoryPC(const Point& size, const Color& color)
	{
		return new BindType(size, color);
	}

	BindType* ConstructF(const FilePath& path)
	{
		return new BindType(path);
	}

	void RegisterImage(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Image";

		int32 r = 0;

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f()", asFUNCTION(DefaultConstruct), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const Image& in)", asFUNCTION(CopyConstruct), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(int32 w, int32 h)", asFUNCTION(Image_FactoryII), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(int32 w, int32 h, const Color& in)", asFUNCTION(Image_FactoryIIC), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const Point& in, const Color& in)", asFUNCTION(Image_FactoryPC), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Image@ f(const String& in)", asFUNCTION(ConstructF), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_ADDREF, "void f()", asMETHOD(BindType, AddRef), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_RELEASE, "void f()", asMETHOD(BindType, Release), asCALL_THISCALL); assert(r >= 0);
	
		
		
		r = engine->RegisterObjectMethod(TypeName, "int32 width() const", asMETHOD(BindType, width), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "int32 height() const", asMETHOD(BindType, height), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "Polygon alphaToPolygon(uint32 threshold = 160, bool allowHoles = true) const", asMETHOD(BindType, alphaToPolygon), asCALL_THISCALL); assert(r >= 0);

	}
}
