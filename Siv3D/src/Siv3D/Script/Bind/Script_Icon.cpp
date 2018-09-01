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
# include <Siv3D/Icon.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"
# include "Script_Image.hpp"

namespace s3d
{
	using namespace AngelScript;

	using BindType = Icon;

	static void Construct(const Icon& c, BindType* self)
	{
		new(self) BindType(c);
	}

	static void ConstructUI(uint32 code, int32 size, BindType* self)
	{
		new(self) BindType(code, size);
	}

	static RefWrapper<Image>* IconLoadImage(uint32 code, int32 size)
	{
		return new RefWrapper<Image>(Icon::LoadImage(code, size));
	}

	void RegisterIcon(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Icon";

		int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "uint32 code", asOFFSET(BindType, code)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "int32 size", asOFFSET(BindType, size)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const Icon &in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(uint32 code, int32 size)", asFUNCTION(ConstructUI), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->SetDefaultNamespace("Icon"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Image@ LoadImage(uint32 code, int32 size)", asFUNCTION(IconLoadImage), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
