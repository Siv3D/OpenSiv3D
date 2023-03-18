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
# include <Siv3D/INI.hpp>

namespace s3d
{
	using namespace AngelScript;

	using BindType = INI;

	static void DefaultConstruct(BindType* self)
	{
		new(self) BindType();
	}

	static void CopyConstruct(const INI& other, BindType* self)
	{
		new(self) BindType(other);
	}

	static void ConstructF(const FilePath& path, BindType* self)
	{
		new(self) BindType(path);
	}

	static void Destruct(BindType* self)
	{
		self->~INI();
	}

	static bool Load(const FilePath& path, BindType& self)
	{
		return self.load(path);
	}

	static bool HasSection(const String& section, const BindType& self)
	{
		return self.hasSection(section);
	}

	static bool HasValue(const String& section, const String& name, const BindType& self)
	{
		return self.hasValue(section, name);
	}

	static String GetValue(const String& section, const String& name, const BindType& self)
	{
		return self.getValue(section, name);
	}

	static bool HasGlobalValue(const String& name, const BindType& self)
	{
		return self.hasGlobalValue(name);
	}

	static String GetGlobalValue(const String& name, const BindType& self)
	{
		return self.getGlobalValue(name);
	}

	static String GetValue2(const String& section_dot_name, const BindType& self)
	{
		return self[section_dot_name];
	}

	static void AddSection(const String& section, BindType& self)
	{
		return self.addSection(section);
	}

	static void RemoveSection(const String& section, BindType& self)
	{
		return self.removeSection(section);
	}

	static void Write(const String& section, const String& name, const String& value, BindType& self)
	{
		self.write(section, name, value);
	}

	static void WriteGlobal(const String& name, const String& value, BindType& self)
	{
		self.writeGlobal(name, value);
	}

	static bool Save(const FilePath& path, const BindType& self)
	{
		return self.save(path);
	}

	void RegisterINI(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "INI";
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const INI& in)", asFUNCTION(CopyConstruct), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f(const String& in)", asFUNCTION(ConstructF), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool load(const String& in)", asFUNCTION(Load), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void clear()", asMETHODPR(INI, clear, (), void), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool isEmpty() const", asMETHODPR(INI, isEmpty, () const, bool), asCALL_THISCALL); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool opImplConv() const", asMETHODPR(INI, operator bool, () const, bool), asCALL_THISCALL); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool hasSection(const String& in) const", asFUNCTION(HasSection), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "bool hasValue(const String& in, const String& in) const", asFUNCTION(HasValue), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "String getValue(const String& in, const String& in) const", asFUNCTION(GetValue), asCALL_CDECL_OBJLAST);
			r = engine->RegisterObjectMethod(TypeName, "bool hasGlobalValue(const String& in) const", asFUNCTION(HasGlobalValue), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "String getGlobalValue(const String& in) const", asFUNCTION(GetGlobalValue), asCALL_CDECL_OBJLAST);

			// operator []
			r = engine->RegisterObjectMethod(TypeName, "String opIndex(const String& in) const", asFUNCTION(GetValue2), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "void addSection(const String& in)", asFUNCTION(AddSection), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void removeSection(const String& in)", asFUNCTION(RemoveSection), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "void write(const String& in, const String& in, const String& in)", asFUNCTION(Write), asCALL_CDECL_OBJLAST); assert(r >= 0);
			r = engine->RegisterObjectMethod(TypeName, "void writeGlobal(const String& in, const String& in)", asFUNCTION(WriteGlobal), asCALL_CDECL_OBJLAST); assert(r >= 0);

			r = engine->RegisterObjectMethod(TypeName, "bool save(const String& in)", asFUNCTION(Save), asCALL_CDECL_OBJLAST); assert(r >= 0);
		}
	}
}
