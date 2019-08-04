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
# include <Siv3D/NamedParameter.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	struct SamplingRate_v
	{
		uint32 value = 0;

		SamplingRate_v() = default;

		explicit SamplingRate_v(uint32 _value)
			: value(_value) {}
	};

	static void DefaultConstruct(SamplingRate_v* self)
	{
		new(self) SamplingRate_v();
	}

	static void CopyConstruct(const SamplingRate_v& other, SamplingRate_v* self)
	{
		new(self) SamplingRate_v(other);
	}

	static void ConstructU(uint32 value, SamplingRate_v* self)
	{
		new(self) SamplingRate_v(value);
	}

	static SamplingRate_v NamedParameterUint32(uint32 value, const uint8&)
	{
		return SamplingRate_v(value);
	}

	void RegisterNamedArg(asIScriptEngine *engine)
	{
		static constexpr uint8 namedArgDummy = 0;

		int32 r = 0;	

		r = engine->SetDefaultNamespace("Arg"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const samplingRate_ samplingRate", (void*)&namedArgDummy); assert(r >= 0);
			r = engine->RegisterObjectBehaviour("samplingRate_v", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour("samplingRate_v", asBEHAVE_CONSTRUCT, "void f(const samplingRate_v& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour("samplingRate_v", asBEHAVE_CONSTRUCT, "void f(uint32)", asFUNCTION(ConstructU), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod("samplingRate_", "Arg::samplingRate_v opAssign(uint32) const", asFUNCTION(NamedParameterUint32), asCALL_CDECL_OBJLAST); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);		

	}
}
