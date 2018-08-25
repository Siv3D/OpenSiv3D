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
# include <Siv3D/Circular.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ValueType = LineStyle;

	static void ConstructDefault(ValueType* self)
	{
		new(self) ValueType();
	}

	static void Construct(const LineStyle& style, ValueType* self)
	{
		new(self) ValueType(style);
	}

	static void ConstructL(const LineStyle::Parameters& params, ValueType* self)
	{
		new(self) ValueType(params);
	}

	static void ConstructLS(const LineStyle::Parameters& style, LineStyle::Parameters* self)
	{
		new(self) LineStyle::Parameters(style);
	}

# if defined(SIV3D_TARGET_WINDOWS)

	static LineStyle ConvToLineStyle(const LineStyle::Parameters& params)
	{
		return LineStyle(params);
	}

# else

	static void Offset_Generic(asIScriptGeneric* gen)
	{
		const LineStyle::Parameters* a = static_cast<const LineStyle::Parameters*>(gen->GetObject());
		const double* b = static_cast<const double*>(gen->GetAddressOfArg(0));
		auto ret_val = a->offset(*b);
		gen->SetReturnObject(&ret_val);
	}

	static void ConvToLineStyle_Generic(asIScriptGeneric* gen)
	{
		const LineStyle::Parameters* a = static_cast<const LineStyle::Parameters*>(gen->GetObject());
		auto ret_val = LineStyle(*a);
		gen->SetReturnObject(&ret_val);
	}

# endif

	void RegisterLineStyle(asIScriptEngine* engine)
	{
		{
			constexpr char TypeName[] = "LineStyle";

			int32 r = 0;
			r = engine->RegisterObjectProperty(TypeName, "double dotOffset", asOFFSET(LineStyle, dotOffset)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "bool hasCap", asOFFSET(LineStyle, hasCap)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "bool isRound", asOFFSET(LineStyle, isRound)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "bool isDotted", asOFFSET(LineStyle, isDotted)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "bool hasAlignedDot", asOFFSET(LineStyle, hasAlignedDot)); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructDefault), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineStyle& in)", asFUNCTION(Construct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineStyleParameters& in)", asFUNCTION(ConstructL), asCALL_CDECL_OBJLAST); assert(r >= 0);
		}

		{
			constexpr char TypeName[] = "LineStyleParameters";

			int32 r = 0;
			r = engine->RegisterObjectProperty(TypeName, "double dotOffset", asOFFSET(LineStyle, dotOffset)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "bool hasCap", asOFFSET(LineStyle, hasCap)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "bool isRound", asOFFSET(LineStyle, isRound)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "bool isDotted", asOFFSET(LineStyle, isDotted)); assert(r >= 0);
			r = engine->RegisterObjectProperty(TypeName, "bool hasAlignedDot", asOFFSET(LineStyle, hasAlignedDot)); assert(r >= 0);

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const LineStyleParameters& in)", asFUNCTION(ConstructLS), asCALL_CDECL_OBJLAST); assert(r >= 0);

			//r = engine->RegisterObjectMethod(TypeName, "LineStyleParameters opCall(double) const", asMETHOD(LineStyle::Parameters, offset), asCALL_THISCALL); assert(r >= 0); // AngelScript のバグ?
			
		# if defined(SIV3D_TARGET_WINDOWS)

			r = engine->RegisterObjectMethod(TypeName, "LineStyleParameters offset(double) const", asMETHOD(LineStyle::Parameters, offset), asCALL_THISCALL); assert(r >= 0);

		# else

			r = engine->RegisterObjectMethod(TypeName, "LineStyleParameters offset(double) const", asFUNCTION(Offset_Generic), asCALL_GENERIC); assert(r >= 0);

		# endif

			r = engine->SetDefaultNamespace("LineStyle"); assert(r >= 0);
			{
				r = engine->RegisterGlobalProperty("const LineStyleParameters SquareCap", (void*)&LineStyle::SquareCap); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const LineStyleParameters RoundCap", (void*)&LineStyle::RoundCap); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const LineStyleParameters NoCap", (void*)&LineStyle::NoCap); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const LineStyleParameters SquareDot", (void*)&LineStyle::SquareDot); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const LineStyleParameters RoundDot", (void*)&LineStyle::RoundDot); assert(r >= 0);
				r = engine->RegisterGlobalProperty("const LineStyleParameters Default", (void*)&LineStyle::Default); assert(r >= 0);
			}
			r = engine->SetDefaultNamespace(""); assert(r >= 0);

		# if defined(SIV3D_TARGET_WINDOWS)

			r = engine->RegisterObjectMethod(TypeName, "LineStyle opImplConv() const", asFUNCTION(ConvToLineStyle), asCALL_CDECL_OBJLAST); assert(r >= 0);

		# else

			r = engine->RegisterObjectMethod(TypeName, "LineStyle opImplConv() const", asFUNCTION(ConvToLineStyle_Generic), asCALL_GENERIC); assert(r >= 0);

		# endif
		}
	}
}
