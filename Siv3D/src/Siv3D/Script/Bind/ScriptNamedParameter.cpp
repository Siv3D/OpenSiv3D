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
# include <Siv3D/PointVector.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	using namespace AngelScript;

	struct ArgVec2
	{
		Vec2 value;
	};

	struct ArgPos
	{
		uint8 _unused = 0;

		ArgVec2 set(double x, double y) const noexcept
		{
			return ArgVec2{ Vec2{x, y} };
		}

		ArgVec2 set(Vec2 value) const noexcept
		{
			return ArgVec2{ value };
		}
	};

	static void ArgVec2_DefaultConstruct(ArgVec2* self)
	{
		new(self) ArgVec2{};
	}

	static void ArgVec2_CopyConstruct(const ArgVec2& ref, ArgVec2* self)
	{
		new(self) ArgVec2{ ref };
	}

	struct ArgUint32
	{
		uint32 value;
	};

	struct ArgSampleRate
	{
		uint8 _unused = 0;

		ArgUint32 set(uint32 value) const noexcept
		{
			return ArgUint32{ value };
		}
	};

	static void ArgUint32_DefaultConstruct(ArgUint32* self)
	{
		new(self) ArgUint32{};
	}

	static void ArgUint32_CopyConstruct(const ArgUint32& ref, ArgUint32* self)
	{
		new(self) ArgUint32{ ref };
	}

	void RegisterNamedParameter(asIScriptEngine* engine)
	{
		static constexpr ArgPos argPos;
		static constexpr ArgSampleRate argSampleRate;

		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Arg"); assert(r >= 0);
		{
			{
				r = engine->RegisterGlobalProperty("const topLeft_ topLeft", (void*)&argPos); assert(r >= 0);
				r = engine->RegisterObjectMethod("topLeft_", "topLeft_Vec2 opAssign(Vec2) const", asMETHODPR(ArgPos, set, (Vec2) const, ArgVec2), asCALL_THISCALL); assert(r >= 0);
				r = engine->RegisterObjectMethod("topLeft_", "topLeft_Vec2 opCall(double, double) const", asMETHODPR(ArgPos, set, (double, double) const, ArgVec2), asCALL_THISCALL); assert(r >= 0);
				r = engine->RegisterObjectMethod("topLeft_", "topLeft_Vec2 opCall(Vec2) const", asMETHODPR(ArgPos, set, (Vec2) const, ArgVec2), asCALL_THISCALL); assert(r >= 0);
				r = engine->RegisterObjectBehaviour("topLeft_Vec2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ArgVec2_DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectBehaviour("topLeft_Vec2", asBEHAVE_CONSTRUCT, "void f(const topLeft_Vec2 &in)", asFUNCTION(ArgVec2_CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			}

			{
				r = engine->RegisterGlobalProperty("const center_ center", (void*)&argPos); assert(r >= 0);
				r = engine->RegisterObjectMethod("center_", "center_Vec2 opAssign(Vec2) const", asMETHODPR(ArgPos, set, (Vec2) const, ArgVec2), asCALL_THISCALL); assert(r >= 0);
				r = engine->RegisterObjectMethod("center_", "center_Vec2 opCall(double, double) const", asMETHODPR(ArgPos, set, (double, double) const, ArgVec2), asCALL_THISCALL); assert(r >= 0);
				r = engine->RegisterObjectMethod("center_", "center_Vec2 opCall(Vec2) const", asMETHODPR(ArgPos, set, (Vec2) const, ArgVec2), asCALL_THISCALL); assert(r >= 0);
				r = engine->RegisterObjectBehaviour("center_Vec2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ArgVec2_DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectBehaviour("center_Vec2", asBEHAVE_CONSTRUCT, "void f(const center_Vec2 &in)", asFUNCTION(ArgVec2_CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			}

			{
				r = engine->RegisterGlobalProperty("const sampleRate_ sampleRate", (void*)&argSampleRate); assert(r >= 0);
				r = engine->RegisterObjectMethod("sampleRate_", "sampleRate_uint32 opAssign(uint32) const", asMETHODPR(ArgSampleRate, set, (uint32) const, ArgUint32), asCALL_THISCALL); assert(r >= 0);
				r = engine->RegisterObjectMethod("sampleRate_", "sampleRate_uint32 opCall(uint32) const", asMETHODPR(ArgSampleRate, set, (uint32) const, ArgUint32), asCALL_THISCALL); assert(r >= 0);
				r = engine->RegisterObjectBehaviour("sampleRate_uint32", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ArgUint32_DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
				r = engine->RegisterObjectBehaviour("sampleRate_uint32", asBEHAVE_CONSTRUCT, "void f(const sampleRate_uint32 &in)", asFUNCTION(ArgUint32_CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			}
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
