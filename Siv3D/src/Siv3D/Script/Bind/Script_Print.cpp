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
# include <Siv3D/Print.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	String FormatBase(const void** args, const int* types, size_t num_args);

	using namespace AngelScript;

	using BindType = uint8;

	struct PrintBufferWrapeer : detail::PrintBuffer
	{
		int32 refCount = 0;

		PrintBufferWrapeer()
		{
			AddRef();
		}

		PrintBufferWrapeer(const String& str)
		{
			AddRef();
			formatData->string.assign(str);
		}

		PrintBufferWrapeer(String&& str)
		{
			AddRef();
			formatData->string.assign(std::move(str));
		}

		PrintBufferWrapeer* write(const String& str)
		{
			detail::PrintBuffer::operator<<(str);
			return this;
		}

		PrintBufferWrapeer* write_T1(const void *ref1, int typeID1)
		{
			detail::PrintBuffer::operator<<(FormatBase(&ref1, &typeID1, 1));
			return this;
		}

		static PrintBufferWrapeer* Create()
		{
			return new PrintBufferWrapeer();
		}

		static PrintBufferWrapeer* Create(const String& text)
		{
			return new PrintBufferWrapeer(text);
		}

		static PrintBufferWrapeer* Create(String&& text)
		{
			return new PrintBufferWrapeer(std::move(text));
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

	static PrintBufferWrapeer* PrintShl(const String& text, BindType*)
	{
		return PrintBufferWrapeer::Create(text);
	}

	static PrintBufferWrapeer* PrintShl_T1(const void *ref1, int typeID1, BindType*)
	{
		return PrintBufferWrapeer::Create(FormatBase(&ref1, &typeID1, 1));
	}

	void RegisterPrint(asIScriptEngine *engine)
	{
		static const uint8 PrintImplDummy = 0;
		const char PrintBufferTypeName[] = "PrintBuffer";
		const char PrintTypeName[] = "Print_impl";
		
		int32 r = 0;	
		r = engine->RegisterObjectBehaviour(PrintBufferTypeName, asBEHAVE_FACTORY, "PrintBuffer@ f()", asFUNCTIONPR(PrintBufferWrapeer::Create, (), PrintBufferWrapeer*), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(PrintBufferTypeName, asBEHAVE_ADDREF, "void f()", asMETHOD(PrintBufferWrapeer, AddRef), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(PrintBufferTypeName, asBEHAVE_RELEASE, "void f()", asMETHOD(PrintBufferWrapeer, Release), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(PrintBufferTypeName, "PrintBuffer& opShl(const String&in text)", asMETHOD(PrintBufferWrapeer, write), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(PrintBufferTypeName, "PrintBuffer& opShl(const ?&in)", asMETHOD(PrintBufferWrapeer, write_T1), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(PrintTypeName, "PrintBuffer@ opShl(const String&in text) const", asFUNCTION(PrintShl), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(PrintTypeName, "PrintBuffer@ opShl(const ?&in) const", asFUNCTION(PrintShl_T1), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Print_impl Print", (void*)&PrintImplDummy); assert(r >= 0);

		engine->RegisterGlobalFunction("void ClearPrint()", asFUNCTION(ClearPrint), asCALL_CDECL); assert(r >= 0);
	}
}
