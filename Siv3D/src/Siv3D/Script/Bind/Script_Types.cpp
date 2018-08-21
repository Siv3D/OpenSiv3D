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

# include <Siv3D.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterTypes(asIScriptEngine *engine)
	{
		int r = 0;
		//r = engine->RegisterObjectType("Optional<class T>", 0, asOBJ_REF | asOBJ_GC | asOBJ_TEMPLATE); assert(r >= 0);
		r = engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE | asGetTypeTraits<String>()); assert(r >= 0);
		
		r = engine->RegisterObjectType("Date", sizeof(Date), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLINTS); assert(r >= 0);
		r = engine->RegisterObjectType("DateTime", sizeof(DateTime), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLINTS); assert(r >= 0);
		r = engine->RegisterObjectType("Stopwatch", sizeof(Stopwatch), asOBJ_VALUE | asGetTypeTraits<Stopwatch>()); assert(r >= 0);
		r = engine->RegisterObjectType("CustomStopwatch", sizeof(CustomStopwatch), asOBJ_VALUE | asGetTypeTraits<CustomStopwatch>()); assert(r >= 0);
		r = engine->RegisterObjectType("Timer", sizeof(Timer), asOBJ_VALUE | asGetTypeTraits<Timer>()); assert(r >= 0);
		//r = engine->RegisterObjectType("TimeProfiler", sizeof(Timer), asOBJ_VALUE | asGetTypeTraits<TimeProfiler>()); assert(r >= 0);
		r = engine->RegisterObjectType("MillisecClock", sizeof(MillisecClock), asOBJ_VALUE | asGetTypeTraits<MillisecClock>()); assert(r >= 0);
		r = engine->RegisterObjectType("MicrosecClock", sizeof(MicrosecClock), asOBJ_VALUE | asGetTypeTraits<MicrosecClock>()); assert(r >= 0);
		r = engine->RegisterObjectType("RDTSCClock", sizeof(RDTSCClock), asOBJ_VALUE | asGetTypeTraits<RDTSCClock>()); assert(r >= 0);


		r = engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLINTS); assert(r >= 0);
		r = engine->RegisterObjectType("ColorF", sizeof(ColorF), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("HSV", sizeof(HSV), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("Point", sizeof(Point), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLINTS); assert(r >= 0);
		r = engine->RegisterObjectType("Vec2", sizeof(Vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("Vec3", sizeof(Vec3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("Vec4", sizeof(Vec4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("Circular", sizeof(Circular), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("Line", sizeof(Line), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("Rect", sizeof(Rect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLINTS); assert(r >= 0);
		r = engine->RegisterObjectType("RectF", sizeof(RectF), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("Circle", sizeof(Circle), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("Ellipse", sizeof(Ellipse), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("Triangle", sizeof(Triangle), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("Quad", sizeof(Quad), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);
		r = engine->RegisterObjectType("RoundRect", sizeof(RoundRect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C | asOBJ_APP_CLASS_ALLFLOATS); assert(r >= 0);

		///
		/// bad
		r = engine->RegisterObjectType("Polygon", sizeof(Polygon), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("LineString", sizeof(LineString), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C); assert(r >= 0);

		//r = engine->RegisterObjectType("Image", sizeof(ImageWrapper), asOBJ_REF); assert(r >= 0);

		//r = engine->RegisterObjectType("Key", sizeof(Key), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C); assert(r >= 0);

		//r = engine->RegisterObjectType("Texture", sizeof(Texture), asOBJ_VALUE | asOBJ_APP_CLASS_CD); assert(r >= 0);
		//r = engine->RegisterObjectType("DynamicTexture", sizeof(DynamicTexture), asOBJ_VALUE | asOBJ_APP_CLASS_CD); assert(r >= 0);
		//r = engine->RegisterObjectType("Font", sizeof(Font), asOBJ_VALUE | asOBJ_APP_CLASS_CD); assert(r >= 0);
		//r = engine->RegisterObjectType("DrawableString", sizeof(DrawableString), asOBJ_VALUE | asOBJ_APP_CLASS_D); assert(r >= 0);
		//r = engine->RegisterObjectType("Webcam", sizeof(Webcam), asOBJ_VALUE | asOBJ_APP_CLASS_CD); assert(r >= 0);

		r = engine->RegisterObjectType("Print_impl", 1, asOBJ_VALUE | asOBJ_POD); assert(r >= 0);
		r = engine->RegisterObjectType("PrintBuffer", 1, asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

		r = engine->RegisterEnum("CursorStyle"); assert(r >= 0);


		assert(engine->GetTypeIdByDecl("String") == static_cast<int>(ScriptTypeID::String));
		assert(engine->GetTypeIdByDecl("Date") == static_cast<int>(ScriptTypeID::Date));
		assert(engine->GetTypeIdByDecl("DateTime") == static_cast<int>(ScriptTypeID::DateTime));
		assert(engine->GetTypeIdByDecl("Stopwatch") == static_cast<int>(ScriptTypeID::Stopwatch));
		assert(engine->GetTypeIdByDecl("CustomStopwatch") == static_cast<int>(ScriptTypeID::CustomStopwatch));
		assert(engine->GetTypeIdByDecl("Timer") == static_cast<int>(ScriptTypeID::Timer));
		//assert(engine->GetTypeIdByDecl("TimeProfiler") == static_cast<int>(ScriptTypeID::TimeProfiler));
		assert(engine->GetTypeIdByDecl("MillisecClock") == static_cast<int>(ScriptTypeID::MillisecClock));
		assert(engine->GetTypeIdByDecl("MicrosecClock") == static_cast<int>(ScriptTypeID::MicrosecClock));
		assert(engine->GetTypeIdByDecl("RDTSCClock") == static_cast<int>(ScriptTypeID::RDTSCClock));
		assert(engine->GetTypeIdByDecl("Color") == static_cast<int>(ScriptTypeID::Color));
		assert(engine->GetTypeIdByDecl("ColorF") == static_cast<int>(ScriptTypeID::ColorF));
		assert(engine->GetTypeIdByDecl("HSV") == static_cast<int>(ScriptTypeID::HSV));
		assert(engine->GetTypeIdByDecl("Point") == static_cast<int>(ScriptTypeID::Point));
		assert(engine->GetTypeIdByDecl("Vec2") == static_cast<int>(ScriptTypeID::Vec2));
		assert(engine->GetTypeIdByDecl("Vec3") == static_cast<int>(ScriptTypeID::Vec3));
		assert(engine->GetTypeIdByDecl("Vec4") == static_cast<int>(ScriptTypeID::Vec4));
		assert(engine->GetTypeIdByDecl("Circular") == static_cast<int>(ScriptTypeID::Circular));
		assert(engine->GetTypeIdByDecl("Line") == static_cast<int>(ScriptTypeID::Line));
		assert(engine->GetTypeIdByDecl("Rect") == static_cast<int>(ScriptTypeID::Rect));
		assert(engine->GetTypeIdByDecl("RectF") == static_cast<int>(ScriptTypeID::RectF));
		assert(engine->GetTypeIdByDecl("Circle") == static_cast<int>(ScriptTypeID::Circle));
		assert(engine->GetTypeIdByDecl("Ellipse") == static_cast<int>(ScriptTypeID::Ellipse));
		assert(engine->GetTypeIdByDecl("Triangle") == static_cast<int>(ScriptTypeID::Triangle));
		assert(engine->GetTypeIdByDecl("Quad") == static_cast<int>(ScriptTypeID::Quad));
		assert(engine->GetTypeIdByDecl("RoundRect") == static_cast<int>(ScriptTypeID::RoundRect));
		assert(engine->GetTypeIdByDecl("Polygon") == static_cast<int>(ScriptTypeID::Polygon));
		assert(engine->GetTypeIdByDecl("LineString") == static_cast<int>(ScriptTypeID::LineString));


		assert(engine->GetTypeIdByDecl("Print_impl") == static_cast<int>(ScriptTypeID::Print_impl));
		assert(engine->GetTypeIdByDecl("PrintBuffer") == static_cast<int>(ScriptTypeID::PrintBuffer));

		//assert(engine->GetTypeIdByDecl("CursorStyle") == static_cast<int>(ScriptTypeID::CursorStyle));

		//assert(engine->GetTypeIdByDecl("Image") == static_cast<int>(ScriptTypeID::Image));

		//assert(engine->GetTypeIdByDecl("Key") == static_cast<int>(ScriptTypeID::Key));
		//assert(engine->GetTypeIdByDecl("Texture") == static_cast<int>(ScriptTypeID::Texture));
		//assert(engine->GetTypeIdByDecl("DynamicTexture") == static_cast<int>(ScriptTypeID::DynamicTexture));
		//assert(engine->GetTypeIdByDecl("Font") == static_cast<int>(ScriptTypeID::Font));
		//assert(engine->GetTypeIdByDecl("DrawableString") == static_cast<int>(ScriptTypeID::DrawableString));
	}
}
