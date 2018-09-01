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
# include <Siv3D/Format.hpp>
# include <Siv3D/Date.hpp>
# include <Siv3D/DateTime.hpp>
# include <Siv3D/Stopwatch.hpp>
# include <Siv3D/CustomStopwatch.hpp>
# include <Siv3D/Timer.hpp>
# include <Siv3D/Color.hpp>
# include <Siv3D/HSV.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/OffsetCircular.hpp>
# include <Siv3D/Bezier2.hpp>
# include <Siv3D/Bezier3.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/Ellipse.hpp>
# include <Siv3D/Line.hpp>
# include <Siv3D/Triangle.hpp>
# include <Siv3D/Quad.hpp>
# include <Siv3D/RoundRect.hpp>
# include <Siv3D/Polygon.hpp>
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
				Formatter(formatData, *static_cast<const int8*>(ref));
				break;
			case ScriptTypeID::Int16:
				Formatter(formatData, *static_cast<const int16*>(ref));
				break;
			case ScriptTypeID::Int32:
				Formatter(formatData, *static_cast<const int32*>(ref));
				break;
			case ScriptTypeID::Int64:
				Formatter(formatData, *static_cast<const int64*>(ref));
				break;
			case ScriptTypeID::Uint8:
				Formatter(formatData, *static_cast<const uint8*>(ref));
				break;
			case ScriptTypeID::Uint16:
				Formatter(formatData, *static_cast<const uint16*>(ref));
				break;
			case ScriptTypeID::Uint32:
				Formatter(formatData, *static_cast<const uint32*>(ref));
				break;
			case ScriptTypeID::Uint64:
				Formatter(formatData, *static_cast<const uint64*>(ref));
				break;
			case ScriptTypeID::Float:
				Formatter(formatData, *static_cast<const float*>(ref));
				break;
			case ScriptTypeID::Double:
				Formatter(formatData, *static_cast<const double*>(ref));
				break;
			case ScriptTypeID::String:
				Formatter(formatData, *static_cast<const String*>(ref));
				break;
			case ScriptTypeID::Date:
				Formatter(formatData, *static_cast<const Date*>(ref));
				break;
			case ScriptTypeID::DateTime:
				Formatter(formatData, *static_cast<const DateTime*>(ref));
				break;
			case ScriptTypeID::Stopwatch:
				Formatter(formatData, *static_cast<const Stopwatch*>(ref));
				break;
			case ScriptTypeID::CustomStopwatch:
				Formatter(formatData, *static_cast<const CustomStopwatch*>(ref));
				break;
			case ScriptTypeID::Timer:
				Formatter(formatData, *static_cast<const Timer*>(ref));
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
			case ScriptTypeID::Vec3:
				Formatter(formatData, *static_cast<const Vec3*>(ref));
				break;
			case ScriptTypeID::Vec4:
				Formatter(formatData, *static_cast<const Vec4*>(ref));
				break;
			case ScriptTypeID::Circular:
				Formatter(formatData, *static_cast<const Circular*>(ref));
				break;
			case ScriptTypeID::OffsetCircular:
				Formatter(formatData, *static_cast<const OffsetCircular*>(ref));
				break;
			case ScriptTypeID::Bezier2:
				Formatter(formatData, *static_cast<const Bezier2*>(ref));
				break;
			case ScriptTypeID::Bezier3:
				Formatter(formatData, *static_cast<const Bezier3*>(ref));
				break;
			case ScriptTypeID::Line:
				Formatter(formatData, *static_cast<const Line*>(ref));
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
			case ScriptTypeID::Triangle:
				Formatter(formatData, *static_cast<const Triangle*>(ref));
				break;
			case ScriptTypeID::Quad:
				Formatter(formatData, *static_cast<const Quad*>(ref));
				break;
			case ScriptTypeID::RoundRect:
				Formatter(formatData, *static_cast<const RoundRect*>(ref));
				break;
			case ScriptTypeID::Polygon:
				Formatter(formatData, *static_cast<const Polygon*>(ref));
				break;
			default:
				Formatter(formatData, Format(U"[Undefined Format TypeID: ", static_cast<int>(typeID), U"]"));
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
		return FormatBase(args, types, std::size(args));
	}

	String Format_T3(
		const void *ref1, int typeID1,
		const void *ref2, int typeID2,
		const void *ref3, int typeID3
	)
	{
		const void* args[] = { ref1, ref2, ref3 };
		const int types[] = { typeID1, typeID2, typeID3 };
		return FormatBase(args, types, std::size(args));
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
		return FormatBase(args, types, std::size(args));
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
		return FormatBase(args, types, std::size(args));
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
		return FormatBase(args, types, std::size(args));
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
		return FormatBase(args, types, std::size(args));
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
		return FormatBase(args, types, std::size(args));
	}

	String Format_T9(
		const void *ref1, int typeID1,
		const void *ref2, int typeID2,
		const void *ref3, int typeID3,
		const void *ref4, int typeID4,
		const void *ref5, int typeID5,
		const void *ref6, int typeID6,
		const void *ref7, int typeID7,
		const void *ref8, int typeID8,
		const void *ref9, int typeID9
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7, ref8, ref9 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7, typeID8, typeID9 };
		return FormatBase(args, types, std::size(args));
	}

	String Format_T10(
		const void *ref1, int typeID1,
		const void *ref2, int typeID2,
		const void *ref3, int typeID3,
		const void *ref4, int typeID4,
		const void *ref5, int typeID5,
		const void *ref6, int typeID6,
		const void *ref7, int typeID7,
		const void *ref8, int typeID8,
		const void *ref9, int typeID9,
		const void *ref10, int typeID10
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7, ref8, ref9, ref10 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7, typeID8, typeID9, typeID10 };
		return FormatBase(args, types, std::size(args));
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
		r = engine->RegisterGlobalFunction("String Format(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in)", asFUNCTION(Format_T9), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in, const ?&in)", asFUNCTION(Format_T10), asCALL_CDECL); assert(r >= 0);

	}
}
