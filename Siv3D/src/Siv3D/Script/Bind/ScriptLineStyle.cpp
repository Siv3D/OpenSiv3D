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

	using ShapeType = LineStyle;

	static void DefaultConstruct(ShapeType* self)
	{
		new(self) ShapeType();
	}

	static void CopyConstruct(const LineStyle& other, ShapeType* self)
	{
		new(self) ShapeType(other);
	}

	static void ConstructP(const LineStyle::Parameters& params, ShapeType* self)
	{
		new(self) ShapeType(params);
	}

	static void Destruct(ShapeType* self)
	{
		self->~LineStyle();
	}

	void RegisterLineStyle(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "LineStyle";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineStyle& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineStyleParameters& in)", asFUNCTION(ConstructP), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(TypeName, "bool hasSquareCap() const", asMETHODPR(LineStyle, hasSquareCap, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasRoundCap() const", asMETHODPR(LineStyle, hasRoundCap, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasNoCap() const", asMETHODPR(LineStyle, hasNoCap, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasSquareDot() const", asMETHODPR(LineStyle, hasSquareDot, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(TypeName, "bool hasRoundDot() const", asMETHODPR(LineStyle, hasRoundDot, () const noexcept, bool), asCALL_THISCALL); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const LineStyleParameters SquareCap", (void*)&LineStyle::SquareCap); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const LineStyleParameters RoundCap", (void*)&LineStyle::RoundCap); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const LineStyleParameters Uncapped", (void*)&LineStyle::Uncapped); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const LineStyleParameters SquareDot", (void*)&LineStyle::SquareDot); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const LineStyleParameters RoundDot", (void*)&LineStyle::RoundDot); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const LineStyleParameters Default", (void*)&LineStyle::Default); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
