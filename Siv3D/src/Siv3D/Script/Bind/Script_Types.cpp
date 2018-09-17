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
# include "Script_Optional.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterTypes(asIScriptEngine* engine)
	{
		int32 r = 0;
		r = engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE | asGetTypeTraits<String>()); assert(r >= 0);
		r = engine->RegisterObjectType("None_t", 1, asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Optional<class T>", sizeof(CScriptOptional), asOBJ_VALUE | asOBJ_TEMPLATE | asOBJ_APP_CLASS_CDAK); assert(r >= 0);

		r = engine->RegisterObjectType("Date", sizeof(Date), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("DateTime", sizeof(DateTime), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Stopwatch", sizeof(Stopwatch), asOBJ_VALUE | asGetTypeTraits<Stopwatch>()); assert(r >= 0);
		r = engine->RegisterObjectType("CustomStopwatch", sizeof(CustomStopwatch), asOBJ_VALUE | asGetTypeTraits<CustomStopwatch>()); assert(r >= 0);
		r = engine->RegisterObjectType("Timer", sizeof(Timer), asOBJ_VALUE | asGetTypeTraits<Timer>()); assert(r >= 0);
		//r = engine->RegisterObjectType("TimeProfiler", sizeof(Timer), asOBJ_VALUE | asGetTypeTraits<TimeProfiler>()); assert(r >= 0);
		r = engine->RegisterObjectType("MillisecClock", sizeof(MillisecClock), asOBJ_VALUE | asGetTypeTraits<MillisecClock>()); assert(r >= 0);
		r = engine->RegisterObjectType("MicrosecClock", sizeof(MicrosecClock), asOBJ_VALUE | asGetTypeTraits<MicrosecClock>()); assert(r >= 0);
		r = engine->RegisterObjectType("RDTSCClock", sizeof(RDTSCClock), asOBJ_VALUE | asGetTypeTraits<RDTSCClock>()); assert(r >= 0);


		r = engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("ColorF", sizeof(ColorF), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("HSV", sizeof(HSV), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Point", sizeof(Point), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Float2", sizeof(Float2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Vec2", sizeof(Vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Vec3", sizeof(Vec3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Vec4", sizeof(Vec4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Circular", sizeof(Circular), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("OffsetCircular", sizeof(OffsetCircular), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Mat3x2", sizeof(Mat3x2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Bezier2", sizeof(Bezier2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Bezier3", sizeof(Bezier3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Line", sizeof(Line), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Rect", sizeof(Rect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("RectF", sizeof(RectF), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Circle", sizeof(Circle), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Ellipse", sizeof(Ellipse), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Triangle", sizeof(Triangle), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Quad", sizeof(Quad), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("RoundRect", sizeof(RoundRect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);
		r = engine->RegisterObjectType("Polygon", sizeof(Polygon), asOBJ_VALUE | asGetTypeTraits<Polygon>()); assert(r >= 0);

		///
		/// bad
		r = engine->RegisterObjectType("MultiPolygon", sizeof(MultiPolygon), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C); assert(r >= 0);
		
		r = engine->RegisterObjectType("LineString", sizeof(LineString), asOBJ_VALUE | asGetTypeTraits<LineString>()); assert(r >= 0);
		r = engine->RegisterObjectType("FloatRect", sizeof(FloatRect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);


		r = engine->RegisterObjectType("LineStyle", sizeof(LineStyle), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<LineStyle>()); assert(r >= 0);
		r = engine->RegisterObjectType("LineStyleParameters", sizeof(LineStyle::Parameters), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<LineStyle::Parameters>()); assert(r >= 0);

		r = engine->RegisterObjectType("Shape2D", sizeof(Shape2D), asOBJ_VALUE | asGetTypeTraits<Shape2D>()); assert(r >= 0);

		r = engine->RegisterObjectType("Image", sizeof(Image), asOBJ_VALUE | asGetTypeTraits<Image>()); assert(r >= 0);

		r = engine->RegisterObjectType("Key", sizeof(Key), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C); assert(r >= 0);

		r = engine->RegisterObjectType("Texture", sizeof(Texture), asOBJ_VALUE | asGetTypeTraits<Texture>()); assert(r >= 0);
		r = engine->RegisterObjectType("TextureRegion", sizeof(TextureRegion), asOBJ_VALUE | asGetTypeTraits<TextureRegion>()); assert(r >= 0);
		r = engine->RegisterObjectType("TexturedQuad", sizeof(TexturedQuad), asOBJ_VALUE | asGetTypeTraits<TexturedQuad>()); assert(r >= 0);
		r = engine->RegisterObjectType("TexturedCircle", sizeof(TexturedCircle), asOBJ_VALUE | asGetTypeTraits<TexturedCircle>()); assert(r >= 0);
		r = engine->RegisterObjectType("TexturedRoundRect", sizeof(TexturedRoundRect), asOBJ_VALUE | asGetTypeTraits<TexturedRoundRect>()); assert(r >= 0);
		r = engine->RegisterObjectType("DynamicTexture", sizeof(DynamicTexture), asOBJ_VALUE | asGetTypeTraits<DynamicTexture>()); assert(r >= 0);
		r = engine->RegisterObjectType("Font", sizeof(Font), asOBJ_VALUE | asGetTypeTraits<Font>()); assert(r >= 0);
		r = engine->RegisterObjectType("DrawableText", sizeof(DrawableText), asOBJ_VALUE | asGetTypeTraits<DrawableText>()); assert(r >= 0);
		r = engine->RegisterObjectType("Transformer2D", sizeof(Transformer2D), asOBJ_VALUE | asGetTypeTraits<Transformer2D>()); assert(r >= 0);
		r = engine->RegisterObjectType("ViewportBlock2D", sizeof(ViewportBlock2D), asOBJ_VALUE | asGetTypeTraits<ViewportBlock2D>()); assert(r >= 0);

		r = engine->RegisterObjectType("Emoji", sizeof(Emoji), asOBJ_VALUE | asGetTypeTraits<Emoji>()); assert(r >= 0);
		r = engine->RegisterObjectType("Icon", sizeof(Icon), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C); assert(r >= 0);

		//r = engine->RegisterObjectType("Webcam", sizeof(Webcam), asOBJ_VALUE | asOBJ_APP_CLASS_CD); assert(r >= 0);

		r = engine->RegisterObjectType("PrintBuffer", 0, asOBJ_REF); assert(r >= 0);
		r = engine->RegisterObjectType("Print_impl", 1, asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

		r = engine->RegisterEnum("WindowEvent"); assert(r >= 0);
		r = engine->RegisterEnum("CursorStyle"); assert(r >= 0);
		r = engine->RegisterEnum("ImageFormat"); assert(r >= 0);
		r = engine->RegisterEnum("FloodFillConnectivity"); assert(r >= 0);
		r = engine->RegisterEnum("TextureDesc"); assert(r >= 0);
		r = engine->RegisterEnum("TextureFormat"); assert(r >= 0);
		r = engine->RegisterEnum("Typeface"); assert(r >= 0);
		r = engine->RegisterEnum("FontStyle"); assert(r >= 0);

		assert(engine->GetTypeIdByDecl("String") == static_cast<int32>(ScriptTypeID::String));
		assert(engine->GetTypeIdByDecl("None_t") == static_cast<int32>(ScriptTypeID::None_t));
		assert(engine->GetTypeIdByDecl("Date") == static_cast<int32>(ScriptTypeID::Date));
		assert(engine->GetTypeIdByDecl("DateTime") == static_cast<int32>(ScriptTypeID::DateTime));
		assert(engine->GetTypeIdByDecl("Stopwatch") == static_cast<int32>(ScriptTypeID::Stopwatch));
		assert(engine->GetTypeIdByDecl("CustomStopwatch") == static_cast<int32>(ScriptTypeID::CustomStopwatch));
		assert(engine->GetTypeIdByDecl("Timer") == static_cast<int32>(ScriptTypeID::Timer));
		//assert(engine->GetTypeIdByDecl("TimeProfiler") == static_cast<int32>(ScriptTypeID::TimeProfiler));
		assert(engine->GetTypeIdByDecl("MillisecClock") == static_cast<int32>(ScriptTypeID::MillisecClock));
		assert(engine->GetTypeIdByDecl("MicrosecClock") == static_cast<int32>(ScriptTypeID::MicrosecClock));
		assert(engine->GetTypeIdByDecl("RDTSCClock") == static_cast<int32>(ScriptTypeID::RDTSCClock));
		assert(engine->GetTypeIdByDecl("Color") == static_cast<int32>(ScriptTypeID::Color));
		assert(engine->GetTypeIdByDecl("ColorF") == static_cast<int32>(ScriptTypeID::ColorF));
		assert(engine->GetTypeIdByDecl("HSV") == static_cast<int32>(ScriptTypeID::HSV));
		assert(engine->GetTypeIdByDecl("Point") == static_cast<int32>(ScriptTypeID::Point));
		assert(engine->GetTypeIdByDecl("Float2") == static_cast<int32>(ScriptTypeID::Float2));
		assert(engine->GetTypeIdByDecl("Vec2") == static_cast<int32>(ScriptTypeID::Vec2));
		assert(engine->GetTypeIdByDecl("Vec3") == static_cast<int32>(ScriptTypeID::Vec3));
		assert(engine->GetTypeIdByDecl("Vec4") == static_cast<int32>(ScriptTypeID::Vec4));
		assert(engine->GetTypeIdByDecl("Circular") == static_cast<int32>(ScriptTypeID::Circular));
		assert(engine->GetTypeIdByDecl("OffsetCircular") == static_cast<int32>(ScriptTypeID::OffsetCircular));
		assert(engine->GetTypeIdByDecl("Mat3x2") == static_cast<int32>(ScriptTypeID::Mat3x2));
		assert(engine->GetTypeIdByDecl("Bezier2") == static_cast<int32>(ScriptTypeID::Bezier2));
		assert(engine->GetTypeIdByDecl("Bezier3") == static_cast<int32>(ScriptTypeID::Bezier3));
		assert(engine->GetTypeIdByDecl("Line") == static_cast<int32>(ScriptTypeID::Line));
		assert(engine->GetTypeIdByDecl("Rect") == static_cast<int32>(ScriptTypeID::Rect));
		assert(engine->GetTypeIdByDecl("RectF") == static_cast<int32>(ScriptTypeID::RectF));
		assert(engine->GetTypeIdByDecl("Circle") == static_cast<int32>(ScriptTypeID::Circle));
		assert(engine->GetTypeIdByDecl("Ellipse") == static_cast<int32>(ScriptTypeID::Ellipse));
		assert(engine->GetTypeIdByDecl("Triangle") == static_cast<int32>(ScriptTypeID::Triangle));
		assert(engine->GetTypeIdByDecl("Quad") == static_cast<int32>(ScriptTypeID::Quad));
		assert(engine->GetTypeIdByDecl("RoundRect") == static_cast<int32>(ScriptTypeID::RoundRect));
		assert(engine->GetTypeIdByDecl("Polygon") == static_cast<int32>(ScriptTypeID::Polygon));
		assert(engine->GetTypeIdByDecl("MultiPolygon") == static_cast<int32>(ScriptTypeID::MultiPolygon));
		assert(engine->GetTypeIdByDecl("LineString") == static_cast<int32>(ScriptTypeID::LineString));

		assert(engine->GetTypeIdByDecl("FloatRect") == static_cast<int32>(ScriptTypeID::FloatRect));

		assert(engine->GetTypeIdByDecl("LineStyle") == static_cast<int32>(ScriptTypeID::LineStyle));
		assert(engine->GetTypeIdByDecl("LineStyleParameters") == static_cast<int32>(ScriptTypeID::LineStyleParameters));
		assert(engine->GetTypeIdByDecl("Shape2D") == static_cast<int32>(ScriptTypeID::Shape2D));

		assert(engine->GetTypeIdByDecl("Image") == static_cast<int32>(ScriptTypeID::Image));

		assert(engine->GetTypeIdByDecl("Key") == static_cast<int32>(ScriptTypeID::Key));

		assert(engine->GetTypeIdByDecl("Texture") == static_cast<int32>(ScriptTypeID::Texture));
		assert(engine->GetTypeIdByDecl("TextureRegion") == static_cast<int32>(ScriptTypeID::TextureRegion));
		assert(engine->GetTypeIdByDecl("TexturedQuad") == static_cast<int32>(ScriptTypeID::TexturedQuad));
		assert(engine->GetTypeIdByDecl("TexturedCircle") == static_cast<int32>(ScriptTypeID::TexturedCircle));
		assert(engine->GetTypeIdByDecl("TexturedRoundRect") == static_cast<int32>(ScriptTypeID::TexturedRoundRect));
		assert(engine->GetTypeIdByDecl("DynamicTexture") == static_cast<int32>(ScriptTypeID::DynamicTexture));
		assert(engine->GetTypeIdByDecl("Font") == static_cast<int32>(ScriptTypeID::Font));
		assert(engine->GetTypeIdByDecl("DrawableText") == static_cast<int32>(ScriptTypeID::DrawableText));
		assert(engine->GetTypeIdByDecl("Transformer2D") == static_cast<int32>(ScriptTypeID::Transformer2D));
		assert(engine->GetTypeIdByDecl("ViewportBlock2D") == static_cast<int32>(ScriptTypeID::ViewportBlock2D));

		assert(engine->GetTypeIdByDecl("Emoji") == static_cast<int32>(ScriptTypeID::Emoji));
		assert(engine->GetTypeIdByDecl("Icon") == static_cast<int32>(ScriptTypeID::Icon));

		assert(engine->GetTypeIdByDecl("PrintBuffer") == static_cast<int32>(ScriptTypeID::PrintBuffer));
		assert(engine->GetTypeIdByDecl("Print_impl") == static_cast<int32>(ScriptTypeID::Print_impl));
		//

		//assert(engine->GetTypeIdByDecl("CursorStyle") == static_cast<int>(ScriptTypeID::CursorStyle));

		
		r = engine->RegisterTypedef("size_t", "uint64"); assert(r >= 0);
	}
}
