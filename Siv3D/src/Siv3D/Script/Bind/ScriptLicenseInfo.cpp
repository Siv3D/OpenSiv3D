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
# include <Siv3D/LicenseInfo.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = LicenseInfo;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void Destruct(BindType* self)
	{
		self->~LicenseInfo();
	}

	void RegisterLicenseInfo(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "LicenseInfo";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "String title", asOFFSET(BindType, title)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "String copyright", asOFFSET(BindType, copyright)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "String text", asOFFSET(BindType, text)); assert(r >= 0);

		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
	}
}
