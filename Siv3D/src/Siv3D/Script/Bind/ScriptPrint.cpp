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
# include <Siv3D/Print.hpp>

namespace s3d
{
	String FormatBase(const void** args, const int* types, size_t num_args);

	using namespace AngelScript;

	using BindType = uint8;

	struct PrintBufferWrapper : detail::PrintBuffer
	{
		int32 refCount = 0;

		PrintBufferWrapper()
		{
			AddRef();
		}

		PrintBufferWrapper(const String& str)
		{
			AddRef();
			formatData->string.assign(str);
		}

		PrintBufferWrapper(String&& str)
		{
			AddRef();
			formatData->string.assign(std::move(str));
		}

		PrintBufferWrapper* write(const String& str)
		{
			detail::PrintBuffer::operator<<(str);
			return this;
		}

		PrintBufferWrapper* write_T1(const void* ref1, int typeID1)
		{
			detail::PrintBuffer::operator<<(FormatBase(&ref1, &typeID1, 1));
			return this;
		}

		static PrintBufferWrapper* Create()
		{
			return new PrintBufferWrapper();
		}

		static PrintBufferWrapper* Create(const String& text)
		{
			return new PrintBufferWrapper(text);
		}

		static PrintBufferWrapper* Create(String&& text)
		{
			return new PrintBufferWrapper(std::move(text));
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

	static PrintBufferWrapper* PrintShl(const String& text, BindType*)
	{
		return PrintBufferWrapper::Create(text);
	}

	static PrintBufferWrapper* PrintShl_T1(const void* ref1, int typeID1, BindType*)
	{
		return PrintBufferWrapper::Create(FormatBase(&ref1, &typeID1, 1));
	}

	void RegisterPrint(asIScriptEngine* engine)
	{
		static const uint8 PrintImplPlaceholder = 0;
		const char PrintBufferTypeName[] = "PrintBuffer";
		const char PrintTypeName[] = "Print_impl";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(PrintBufferTypeName, asBEHAVE_FACTORY, "PrintBuffer@ f()", asFUNCTIONPR(PrintBufferWrapper::Create, (), PrintBufferWrapper*), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(PrintBufferTypeName, asBEHAVE_ADDREF, "void f()", asMETHOD(PrintBufferWrapper, AddRef), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(PrintBufferTypeName, asBEHAVE_RELEASE, "void f()", asMETHOD(PrintBufferWrapper, Release), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(PrintBufferTypeName, "PrintBuffer& opShl(const String&in text)", asMETHODPR(PrintBufferWrapper, write, (const String&), PrintBufferWrapper*), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(PrintBufferTypeName, "PrintBuffer& opShl(const ?&in)", asMETHODPR(PrintBufferWrapper, write_T1, (const void*, int), PrintBufferWrapper*), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(PrintTypeName, "PrintBuffer@ opShl(const String&in text) const", asFUNCTION(PrintShl), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(PrintTypeName, "PrintBuffer@ opShl(const ?&in) const", asFUNCTION(PrintShl_T1), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Print_impl Print", (void*)&PrintImplPlaceholder); assert(r >= 0);

		engine->RegisterGlobalFunction("void ClearPrint()", asFUNCTION(ClearPrint), asCALL_CDECL); assert(r >= 0);
	}
}
