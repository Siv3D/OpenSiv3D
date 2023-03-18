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
# include <Siv3D/TextWriter.hpp>

namespace s3d
{
	String FormatBase(const void** args, const int* types, size_t num_args);

	using namespace AngelScript;

	using BindType = TextWriter;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const TextWriter& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void Destruct(TextWriter* self)
	{
		self->~TextWriter();
	}


	static void ConstructFT(const FilePath& path, int32 textEncoding, BindType* self)
	{
		new(self) BindType(path, ToEnum<TextEncoding>(static_cast<uint8>(textEncoding)));
	}

	static void ConstructFOT(const FilePath& path, int32 openMode, int32 textEncoding, BindType* self)
	{
		new(self) BindType(path, ToEnum<OpenMode>(static_cast<uint8>(openMode)), ToEnum<TextEncoding>(static_cast<uint8>(textEncoding)));
	}

	static bool OpenFT(const FilePath& path, int32 textEncoding, BindType& self)
	{
		return self.open(path, ToEnum<TextEncoding>(static_cast<uint8>(textEncoding)));
	}

	static bool OpenFOT(const FilePath& path, int32 openMode, int32 textEncoding, BindType& self)
	{
		return self.open(path, ToEnum<OpenMode>(static_cast<uint8>(openMode)), ToEnum<TextEncoding>(static_cast<uint8>(textEncoding)));
	}



	static int32 GetTextEncoding(const TextWriter& self)
	{
		return FromEnum(self.encoding());
	}

	static String GetPath(const TextWriter& self)
	{
		return self.path();
	}


	struct TextWriterBufferWrapper : detail::TextWriterBuffer
	{
		int32 refCount = 0;

		TextWriterBufferWrapper()
			: TextWriterBuffer{ _empty } {}

		TextWriterBufferWrapper(const String& str, TextWriter& writer)
			: TextWriterBuffer{ writer }
		{
			AddRef();
			formatData->string.assign(str);
		}

		TextWriterBufferWrapper(String&& str, TextWriter& writer)
			: TextWriterBuffer{ writer }
		{
			AddRef();
			formatData->string.assign(std::move(str));
		}

		TextWriterBufferWrapper* write(const String& str)
		{
			detail::TextWriterBuffer::operator<<(str);
			return this;
		}

		TextWriterBufferWrapper* write_T1(const void* ref1, int typeID1)
		{
			detail::TextWriterBuffer::operator<<(FormatBase(&ref1, &typeID1, 1));
			return this;
		}

		static TextWriterBufferWrapper* Create()
		{
			return new TextWriterBufferWrapper();
		}

		static TextWriterBufferWrapper* Create(const String& str, TextWriter& writer)
		{
			return new TextWriterBufferWrapper(str, writer);
		}

		static TextWriterBufferWrapper* Create(String&& text, TextWriter& writer)
		{
			return new TextWriterBufferWrapper(std::move(text), writer);
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

		TextWriter _empty;
	};



	static TextWriterBufferWrapper* TextWriterShl(const String& text, BindType& self)
	{
		return TextWriterBufferWrapper::Create(text, self);
	}

	static TextWriterBufferWrapper* TextWriterShl_T1(const void* ref1, int typeID1, BindType& self)
	{
		return TextWriterBufferWrapper::Create(FormatBase(&ref1, &typeID1, 1), self);
	}


	void RegisterTextWriter(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			const char BufferTypeName[] = "TextWriterBuffer";
			r = engine->RegisterObjectBehaviour(BufferTypeName, asBEHAVE_FACTORY, "TextWriterBuffer@ f()", asFUNCTIONPR(TextWriterBufferWrapper::Create, (), TextWriterBufferWrapper*), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(BufferTypeName, asBEHAVE_ADDREF, "void f()", asMETHOD(TextWriterBufferWrapper, AddRef), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(BufferTypeName, asBEHAVE_RELEASE, "void f()", asMETHOD(TextWriterBufferWrapper, Release), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(BufferTypeName, "TextWriterBuffer& opShl(const String&in text)", asMETHODPR(TextWriterBufferWrapper, write, (const String&), TextWriterBufferWrapper*), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(BufferTypeName, "TextWriterBuffer& opShl(const ?&in)", asMETHODPR(TextWriterBufferWrapper, write_T1, (const void*, int), TextWriterBufferWrapper*), asCALL_THISCALL); assert(r >= 0);
		}

		{
			constexpr char TypeName[] = "TextWriter";

			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const TextWriter& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, TextEncoding)", asFUNCTION(ConstructFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in, OpenMode openMode = OpenMode::Trunc, TextEncoding encoding = TextEncoding::UTF8_WITH_BOM)", asFUNCTION(ConstructFOT), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool open(const String& in, TextEncoding)", asFUNCTION(OpenFT), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool open(const String& in, OpenMode openMode = OpenMode::Trunc, TextEncoding encoding = TextEncoding::UTF8_WITH_BOM)", asFUNCTION(OpenFOT), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void close() const", asMETHODPR(BindType, close, (), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isOpen() const", asMETHODPR(BindType, isOpen, () const, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asMETHODPR(BindType, operator bool, () const, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void clear() const", asMETHODPR(BindType, clear, (), void), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "void write(uint32)", asMETHODPR(BindType, write, (char32), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void write(const String&)", asMETHODPR(BindType, write, (const String&), void), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "void writeln(uint32)", asMETHODPR(BindType, writeln, (char32), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void writeln(const String&)", asMETHODPR(BindType, writeln, (const String&), void), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "TextWriterBuffer@ opShl(const String&in text) const", asFUNCTION(TextWriterShl), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "TextWriterBuffer@ opShl(const ?&in) const", asFUNCTION(TextWriterShl_T1), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "TextEncoding encoding() const", asFUNCTION(GetTextEncoding), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "String path() const", asFUNCTION(GetPath), asCALL_CDECL_OBJLAST); assert(r >= 0);
		}
	}
}
