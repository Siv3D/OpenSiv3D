//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	String FormatBase(const void** args, const int* types, size_t num_args)
	{
		FormatData formatData;

		for (size_t i = 0; i < num_args; ++i)
		{
			const void* ref = args[i];
			const ScriptTypeID typeID = static_cast<ScriptTypeID>(types[i]);

			switch (typeID)
			{
			case ScriptTypeID::Void:
				break;
			case ScriptTypeID::Bool:
				Formatter(formatData, *static_cast<const bool*>(ref));
				break;
			case ScriptTypeID::Int8:
				Formatter(formatData, *static_cast<const signed char*>(ref));
				break;
			case ScriptTypeID::Int16:
				Formatter(formatData, *static_cast<const short*>(ref));
				break;
			case ScriptTypeID::Int32:
				Formatter(formatData, *static_cast<const int*>(ref));
				break;
			case ScriptTypeID::Int64:
				Formatter(formatData, *static_cast<const long long*>(ref));
				break;
			case ScriptTypeID::Uint8:
				Formatter(formatData, *static_cast<const unsigned char*>(ref));
				break;
			case ScriptTypeID::Uint16:
				Formatter(formatData, *static_cast<const unsigned short*>(ref));
				break;
			case ScriptTypeID::Uint32:
				Formatter(formatData, *static_cast<const unsigned*>(ref));
				break;
			case ScriptTypeID::Uint64:
				Formatter(formatData, *static_cast<const unsigned long long*>(ref));
				break;
			case ScriptTypeID::Float:
				Formatter(formatData, *static_cast<const float*>(ref));
				break;
			case ScriptTypeID::Double:
				Formatter(formatData, *static_cast<const double*>(ref));
				break;
			case ScriptTypeID::String:
				Formatter(formatData, *static_cast<const std::wstring*>(ref));
				break;
			case ScriptTypeID::Color:
				Formatter(formatData, *static_cast<const Color*>(ref));
				break;
			case ScriptTypeID::ColorF:
				Formatter(formatData, *static_cast<const ColorF*>(ref));
				break;
			case ScriptTypeID::HSV:
				Formatter(formatData, *static_cast<const HSV*>(ref));
				break;
			case ScriptTypeID::Point:
				Formatter(formatData, *static_cast<const Point*>(ref));
				break;
			case ScriptTypeID::Vec2:
				Formatter(formatData, *static_cast<const Vec2*>(ref));
				break;
			case ScriptTypeID::Circular:
				Formatter(formatData, *static_cast<const Circular*>(ref));
				break;
			case ScriptTypeID::Rect:
				Formatter(formatData, *static_cast<const Rect*>(ref));
				break;
			case ScriptTypeID::RectF:
				Formatter(formatData, *static_cast<const RectF*>(ref));
				break;
			case ScriptTypeID::Circle:
				Formatter(formatData, *static_cast<const Circle*>(ref));
				break;
			case ScriptTypeID::Ellipse:
				Formatter(formatData, *static_cast<const Ellipse*>(ref));
				break;
			case ScriptTypeID::Line:
				Formatter(formatData, *static_cast<const Line*>(ref));
				break;
			case ScriptTypeID::Triangle:
				Formatter(formatData, *static_cast<const Triangle*>(ref));
				break;
			case ScriptTypeID::Quad:
				Formatter(formatData, *static_cast<const Quad*>(ref));
				break;
			case ScriptTypeID::RoundRect:
				Formatter(formatData, *static_cast<const RoundRect*>(ref));
				break;
			default:
				Formatter(formatData, Format(L"[Undefined Format TypeID: ", static_cast<int>(typeID), L"]"));
				break;
			}
		}

		return formatData.string;
	}

	String Fotmat_V()
	{
		return String();
	}

	String Format_S(const String& s)
	{
		return s;
	}

	String Format_T1(
		const void *ref1, int typeID1
	)
	{
		return FormatBase(&ref1, &typeID1, 1);
	}

	String Format_T2(
		const void *ref1, int typeID1,
		const void *ref2, int typeID2
	)
	{
		const void* args[] = { ref1, ref2 };
		const int types[] = { typeID1, typeID2 };
		return FormatBase(args, types, 2);
	}

	String Format_T3(
		const void *ref1, int typeID1,
		const void *ref2, int typeID2,
		const void *ref3, int typeID3
	)
	{
		const void* args[] = { ref1, ref2, ref3 };
		const int types[] = { typeID1, typeID2, typeID3 };
		return FormatBase(args, types, 3);
	}

	String Format_T4(
		const void *ref1, int typeID1,
		const void *ref2, int typeID2,
		const void *ref3, int typeID3,
		const void *ref4, int typeID4
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4 };
		return FormatBase(args, types, 4);
	}

	String Format_T5(
		const void *ref1, int typeID1,
		const void *ref2, int typeID2,
		const void *ref3, int typeID3,
		const void *ref4, int typeID4,
		const void *ref5, int typeID5
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5 };
		return FormatBase(args, types, 5);
	}

	String Format_T6(
		const void *ref1, int typeID1,
		const void *ref2, int typeID2,
		const void *ref3, int typeID3,
		const void *ref4, int typeID4,
		const void *ref5, int typeID5,
		const void *ref6, int typeID6
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6 };
		return FormatBase(args, types, 6);
	}

	String Format_T7(
		const void *ref1, int typeID1,
		const void *ref2, int typeID2,
		const void *ref3, int typeID3,
		const void *ref4, int typeID4,
		const void *ref5, int typeID5,
		const void *ref6, int typeID6,
		const void *ref7, int typeID7
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7 };
		return FormatBase(args, types, 7);
	}

	String Format_T8(
		const void *ref1, int typeID1,
		const void *ref2, int typeID2,
		const void *ref3, int typeID3,
		const void *ref4, int typeID4,
		const void *ref5, int typeID5,
		const void *ref6, int typeID6,
		const void *ref7, int typeID7,
		const void *ref8, int typeID8
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7, ref8 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7, typeID8 };
		return FormatBase(args, types, 8);
	}

	void RegisterFormat(asIScriptEngine *engine)
	{
		int r = 0;
		r = engine->RegisterGlobalFunction("String Format()", asFUNCTION(Fotmat_V), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const String&in)", asFUNCTION(Format_S), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const ?&in)", asFUNCTION(Format_T1), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const ?&in, const ?&in)", asFUNCTION(Format_T2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const ?&in, const ?&in, const ?&in)", asFUNCTION(Format_T3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const ?&in, const ?&in, const ?&in, const ?&in)", asFUNCTION(Format_T4), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in)", asFUNCTION(Format_T5), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in)", asFUNCTION(Format_T6), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in)", asFUNCTION(Format_T7), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in)", asFUNCTION(Format_T8), asCALL_CDECL); assert(r >= 0);
	}
}
