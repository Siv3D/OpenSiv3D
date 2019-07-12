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
# include <Siv3D/Say.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	String FormatBase(const void** args, const int* types, size_t num_args);

	using namespace AngelScript;

	using BindType = uint8;

	struct SayBufferWrapeer : detail::SayBuffer
	{
		int32 refCount = 0;

		SayBufferWrapeer()
		{
			AddRef();
		}

		SayBufferWrapeer(const String& str)
		{
			AddRef();
			formatData->string.assign(str);
		}

		SayBufferWrapeer(String&& str)
		{
			AddRef();
			formatData->string.assign(std::move(str));
		}

		SayBufferWrapeer* write(const String& str)
		{
			detail::SayBuffer::operator<<(str);
			return this;
		}

		SayBufferWrapeer* write_T1(const void *ref1, int typeID1)
		{
			detail::SayBuffer::operator<<(FormatBase(&ref1, &typeID1, 1));
			return this;
		}

		static SayBufferWrapeer* Create()
		{
			return new SayBufferWrapeer();
		}

		static SayBufferWrapeer* Create(const String& text)
		{
			return new SayBufferWrapeer(text);
		}

		static SayBufferWrapeer* Create(String&& text)
		{
			return new SayBufferWrapeer(std::move(text));
		}

		void AddRef()
		{
			++refCount;
		}

		void Release()
		{
			if (--refCount == 0)
			{
				delete this;
			}
		}
	};

	static SayBufferWrapeer* SayShl(const String& text, BindType*)
	{
		return SayBufferWrapeer::Create(text);
	}

	static SayBufferWrapeer* SayShl_T1(const void *ref1, int typeID1, BindType*)
	{
		return SayBufferWrapeer::Create(FormatBase(&ref1, &typeID1, 1));
	}

	void RegisterSay(asIScriptEngine *engine)
	{
		static const uint8 SayImplDummy = 0;
		const char SayBufferTypeName[] = "SayBuffer";
		const char SayTypeName[] = "Say_impl";
		
		int32 r = 0;	
		r = engine->RegisterObjectBehaviour(SayBufferTypeName, asBEHAVE_FACTORY, "SayBuffer@ f()", asFUNCTIONPR(SayBufferWrapeer::Create, (), SayBufferWrapeer*), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(SayBufferTypeName, asBEHAVE_ADDREF, "void f()", asMETHOD(SayBufferWrapeer, AddRef), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(SayBufferTypeName, asBEHAVE_RELEASE, "void f()", asMETHOD(SayBufferWrapeer, Release), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(SayBufferTypeName, "SayBuffer& opShl(const String&in text)", asMETHOD(SayBufferWrapeer, write), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(SayBufferTypeName, "SayBuffer& opShl(const ?&in)", asMETHOD(SayBufferWrapeer, write_T1), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(SayTypeName, "SayBuffer@ opShl(const String&in text) const", asFUNCTION(SayShl), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(SayTypeName, "SayBuffer@ opShl(const ?&in) const", asFUNCTION(SayShl_T1), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Say_impl Say", (void*)&SayImplDummy); assert(r >= 0);
	}
}
