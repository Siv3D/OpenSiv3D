//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/DateTime.hpp>
# include <Siv3D/Stopwatch.hpp>
# include <Siv3D/VariableSpeedStopwatch.hpp>
# include <Siv3D/Timer.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ColorHSV.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/OffsetCircular.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Bezier2.hpp>
# include <Siv3D/Bezier3.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/LineString.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	namespace detail
	{
		[[nodiscard]]
		static const asITypeInfo* GetTypeInfo(const int32 typeID)
		{
			const asIScriptContext* context = asGetActiveContext();
			const asIScriptEngine* engine = context->GetEngine();
			return engine->GetTypeInfoById(typeID);
		}

		[[nodiscard]]
		static String GetTypeName(const asITypeInfo* ti)
		{
			if (const uint32 subTypeCount = ti->GetSubTypeCount())
			{
				String name = Unicode::WidenAscii(ti->GetName());
				name.push_back(U'<');
				//bool isFirst = true;

				//for (size_t i = 0; i < subTypeCount; ++i)
				//{
				//	std::string subTypeName = GetTypeName(ti->GetSubTypeId(i));

				//	if (isFirst)
				//	{
				//		name += subTypeName;
				//		isFirst = false;
				//	}
				//	else
				//	{
				//		name += ", ";
				//		name += subTypeName;
				//	}
				//}

				name.push_back(U'>');
				return name;
			}
			else
			{
				return Unicode::WidenAscii(ti->GetName());
			}
		}

		[[nodiscard]]
		static bool IsEnum(const asITypeInfo* ti)
		{
			return static_cast<bool>(ti->GetFlags() & asOBJ_ENUM);
		}

		[[nodiscard]]
		static String GetEnumValue(const asITypeInfo* ti, int32 value)
		{
			for (int n = ti->GetEnumValueCount(); (n-- > 0); )
			{
				int enumValue;
				const char* enumName = ti->GetEnumValueByIndex(n, &enumValue);

				if (enumValue == value)
				{
					return Unicode::WidenAscii(enumName);
				}
			}

			return{};
		}
	}

	String FormatBase(const void** args, const int32* types, size_t num_args)
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
			case ScriptTypeID::Char32:
				Formatter(formatData, *static_cast<const char32*>(ref));
				break;
			case ScriptTypeID::String:
				Formatter(formatData, *static_cast<const String*>(ref));
				break;
			case ScriptTypeID::None_t:
				Formatter(formatData, U"none");
				break;
			case ScriptTypeID::Duration:
				Formatter(formatData, *static_cast<const Duration*>(ref));
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
			case ScriptTypeID::VariableSpeedStopwatch:
				Formatter(formatData, *static_cast<const VariableSpeedStopwatch*>(ref));
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
			case ScriptTypeID::Float2:
				Formatter(formatData, *static_cast<const Float2*>(ref));
				break;
			case ScriptTypeID::Vec2:
				Formatter(formatData, *static_cast<const Vec2*>(ref));
				break;
			case ScriptTypeID::Float3:
				Formatter(formatData, *static_cast<const Float3*>(ref));
				break;
			case ScriptTypeID::Vec3:
				Formatter(formatData, *static_cast<const Vec3*>(ref));
				break;
			case ScriptTypeID::Float4:
				Formatter(formatData, *static_cast<const Float4*>(ref));
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
			case ScriptTypeID::Mat3x2:
				Formatter(formatData, *static_cast<const Mat3x2*>(ref));
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
			case ScriptTypeID::LineString:
				Formatter(formatData, *static_cast<const LineString*>(ref));
				break;
			default:
			{
				const asITypeInfo* ti = detail::GetTypeInfo(FromEnum(typeID));
				const String typeName = detail::GetTypeName(ti);

				if (detail::IsEnum(ti))
				{
					Formatter(formatData, (typeName + U"::" + detail::GetEnumValue(ti, *static_cast<const int32*>(ref))));
				}
				else
				{
					Formatter(formatData, (U"[" + typeName + U" value (Format not implemented)]"));
				}
			}
			break;
			}
		}

		return formatData.string;
	}

	static String Fotmat_V()
	{
		return String();
	}

	static String Format_S(const String& s)
	{
		return s;
	}

	static String Format_T1(
		const void* ref1, int typeID1
	)
	{
		return FormatBase(&ref1, &typeID1, 1);
	}

	static String Format_T2(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2
	)
	{
		const void* args[] = { ref1, ref2 };
		const int types[] = { typeID1, typeID2 };
		return FormatBase(args, types, std::size(args));
	}

	static String Format_T3(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3
	)
	{
		const void* args[] = { ref1, ref2, ref3 };
		const int types[] = { typeID1, typeID2, typeID3 };
		return FormatBase(args, types, std::size(args));
	}

	static String Format_T4(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4 };
		return FormatBase(args, types, std::size(args));
	}

	static String Format_T5(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5 };
		return FormatBase(args, types, std::size(args));
	}

	static String Format_T6(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const void* ref6, int typeID6
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6 };
		return FormatBase(args, types, std::size(args));
	}

	static String Format_T7(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const void* ref6, int typeID6,
		const void* ref7, int typeID7
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7 };
		return FormatBase(args, types, std::size(args));
	}

	static String Format_T8(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const void* ref6, int typeID6,
		const void* ref7, int typeID7,
		const void* ref8, int typeID8
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7, ref8 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7, typeID8 };
		return FormatBase(args, types, std::size(args));
	}

	static String Format_T9(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const void* ref6, int typeID6,
		const void* ref7, int typeID7,
		const void* ref8, int typeID8,
		const void* ref9, int typeID9
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7, ref8, ref9 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7, typeID8, typeID9 };
		return FormatBase(args, types, std::size(args));
	}

	static String Format_T10(
		const void* ref1, int typeID1,
		const void* ref2, int typeID2,
		const void* ref3, int typeID3,
		const void* ref4, int typeID4,
		const void* ref5, int typeID5,
		const void* ref6, int typeID6,
		const void* ref7, int typeID7,
		const void* ref8, int typeID8,
		const void* ref9, int typeID9,
		const void* ref10, int typeID10
	)
	{
		const void* args[] = { ref1, ref2, ref3, ref4, ref5, ref6, ref7, ref8, ref9, ref10 };
		const int types[] = { typeID1, typeID2, typeID3, typeID4, typeID5, typeID6, typeID7, typeID8, typeID9, typeID10 };
		return FormatBase(args, types, std::size(args));
	}

	void RegisterFormat(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterGlobalFunction("String Format()", asFUNCTION(Fotmat_V), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("String Format(const String& in)", asFUNCTION(Format_S), asCALL_CDECL); assert(r >= 0);
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
