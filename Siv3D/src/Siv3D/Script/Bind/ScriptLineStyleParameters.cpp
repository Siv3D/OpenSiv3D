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
# include <Siv3D/LineStyle.hpp>

namespace s3d
{
	using namespace AngelScript;

	using ShapeType = LineStyle::Parameters;

	static void DefaultConstruct(ShapeType* self)
	{
		new(self) ShapeType();
	}

	static void CopyConstruct(const LineStyle::Parameters& other, ShapeType* self)
	{
		new(self) ShapeType(other);
	}

	static void Destruct(ShapeType* self)
	{
		self->~Parameters();
	}

	void RegisterLineStyleParameters(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "LineStyleParameters";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineStyleParameters& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "LineStyleParameters opCall(double) const", asMETHODPR(LineStyle::Parameters, offset, (double) const, LineStyle::Parameters), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "LineStyleParameters offset(double) const", asMETHODPR(LineStyle::Parameters, offset, (double) const, LineStyle::Parameters), asCALL_THISCALL); assert(r >= 0);
	}
}
