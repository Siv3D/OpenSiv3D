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
# include <Siv3D/Say.hpp>

namespace s3d
{
	String FormatBase(const void** args, const int* types, size_t num_args);

	using namespace AngelScript;

	using BindType = uint8;

	struct SayBufferWrapper : detail::SayBuffer
	{
		int32 refCount = 0;

		SayBufferWrapper()
		{
			AddRef();
		}

		SayBufferWrapper(const String& str)
		{
			AddRef();
			formatData->string.assign(str);
		}

		SayBufferWrapper(String&& str)
		{
			AddRef();
			formatData->string.assign(std::move(str));
		}

		SayBufferWrapper* write(const String& str)
		{
			detail::SayBuffer::operator<<(str);
			return this;
		}

		SayBufferWrapper* write_T1(const void* ref1, int typeID1)
		{
			detail::SayBuffer::operator<<(FormatBase(&ref1, &typeID1, 1));
			return this;
		}

		static SayBufferWrapper* Create()
		{
			return new SayBufferWrapper();
		}

		static SayBufferWrapper* Create(const String& text)
		{
			return new SayBufferWrapper(text);
		}

		static SayBufferWrapper* Create(String&& text)
		{
			return new SayBufferWrapper(std::move(text));
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

	static SayBufferWrapper* SayShl(const String& text, BindType*)
	{
		return SayBufferWrapper::Create(text);
	}

	static SayBufferWrapper* SayShl_T1(const void* ref1, int typeID1, BindType*)
	{
		return SayBufferWrapper::Create(FormatBase(&ref1, &typeID1, 1));
	}

	void RegisterSay(asIScriptEngine* engine)
	{
		static const uint8 SayImplPlaceholder = 0;
		const char SayBufferTypeName[] = "SayBuffer";
		const char SayTypeName[] = "Say_impl";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectBehaviour(SayBufferTypeName, asBEHAVE_FACTORY, "SayBuffer@ f()", asFUNCTIONPR(SayBufferWrapper::Create, (), SayBufferWrapper*), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(SayBufferTypeName, asBEHAVE_ADDREF, "void f()", asMETHOD(SayBufferWrapper, AddRef), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(SayBufferTypeName, asBEHAVE_RELEASE, "void f()", asMETHOD(SayBufferWrapper, Release), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(SayBufferTypeName, "SayBuffer& opShl(const String&in text)", asMETHODPR(SayBufferWrapper, write, (const String&), SayBufferWrapper*), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(SayBufferTypeName, "SayBuffer& opShl(const ?&in)", asMETHODPR(SayBufferWrapper, write_T1, (const void*, int), SayBufferWrapper*), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(SayTypeName, "SayBuffer@ opShl(const String&in text) const", asFUNCTION(SayShl), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(SayTypeName, "SayBuffer@ opShl(const ?&in) const", asFUNCTION(SayShl_T1), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Say_impl Say", (void*)&SayImplPlaceholder); assert(r >= 0);
	}
}
