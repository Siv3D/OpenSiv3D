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
# include <Siv3D/DateTime.hpp>
# include <Siv3D/Stopwatch.hpp>
# include <Siv3D/VariableSpeedStopwatch.hpp>
# include <Siv3D/Timer.hpp>
# include <Siv3D/MillisecClock.hpp>
# include <Siv3D/MicrosecClock.hpp>
# include <Siv3D/RDTSCClock.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/INI.hpp>
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
# include <Siv3D/Spline2D.hpp>
# include <Siv3D/Shape2D.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/Input.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
# include <Siv3D/TexturedCircle.hpp>
# include <Siv3D/TexturedRoundRect.hpp>
# include <Siv3D/DynamicTexture.hpp>
# include <Siv3D/VideoTexture.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/ScopedViewport2D.hpp>
# include <Siv3D/Camera2D.hpp>
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Icon.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/Audio.hpp>
# include <Siv3D/TextEditState.hpp>
# include "ScriptBind.hpp"
# include "ScriptOptional.hpp"

namespace s3d
{
	using namespace AngelScript;

	static void RegisterType(asIScriptEngine* const engine, const char* name, const int byteSize, const asDWORD flags)
	{
		[[maybe_unused]] const int32 r = engine->RegisterObjectType(name, byteSize, flags);
		assert(0 <= r);
	}

	static void RegisterEnum(asIScriptEngine* const engine, const char* name)
	{
		[[maybe_unused]] const int32 r = engine->RegisterEnum(name);
		assert(0 <= r);
	}

	void RegisterTypes(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Arg"); assert(r >= 0);
		{
			r = engine->RegisterObjectType("topLeft_", sizeof(uint8), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);
			r = engine->RegisterObjectType("topLeft_Vec2", sizeof(Vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);

			r = engine->RegisterObjectType("center_", sizeof(uint8), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);
			r = engine->RegisterObjectType("center_Vec2", sizeof(Vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C); assert(r >= 0);

			r = engine->RegisterObjectType("sampleRate_", sizeof(uint8), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);
			r = engine->RegisterObjectType("sampleRate_uint32", sizeof(uint32), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
		
		RegisterType(engine, "char32", sizeof(char32), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<char32_t>());
		RegisterType(engine, "String", sizeof(String), asOBJ_VALUE | asGetTypeTraits<String>());
		RegisterType(engine, "None_t", sizeof(uint8), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Optional<class T>", sizeof(CScriptOptional), asOBJ_VALUE | asOBJ_TEMPLATE | asOBJ_APP_CLASS_CDAK);
		RegisterType(engine, "Duration", sizeof(Duration), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Date", sizeof(Date), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "DateTime", sizeof(DateTime), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Stopwatch", sizeof(Stopwatch), asOBJ_VALUE | asGetTypeTraits<Stopwatch>());
		RegisterType(engine, "VariableSpeedStopwatch", sizeof(VariableSpeedStopwatch), asOBJ_VALUE | asGetTypeTraits<VariableSpeedStopwatch>());
		RegisterType(engine, "Timer", sizeof(Timer), asOBJ_VALUE | asGetTypeTraits<Timer>());
		//r = engine->RegisterObjectType("TimeProfiler", sizeof(Timer), asOBJ_VALUE | asGetTypeTraits<TimeProfiler>()); assert(r >= 0);
		RegisterType(engine, "MillisecClock", sizeof(MillisecClock), asOBJ_VALUE | asGetTypeTraits<MillisecClock>());
		RegisterType(engine, "MicrosecClock", sizeof(MicrosecClock), asOBJ_VALUE | asGetTypeTraits<MicrosecClock>());
		RegisterType(engine, "RDTSCClock", sizeof(RDTSCClock), asOBJ_VALUE | asGetTypeTraits<RDTSCClock>());

		RegisterType(engine, "TextReader", sizeof(TextReader), asOBJ_VALUE | asGetTypeTraits<TextReader>());
		RegisterType(engine, "TextWriterBuffer", 0, asOBJ_REF);
		RegisterType(engine, "TextWriter", sizeof(TextWriter), asOBJ_VALUE | asGetTypeTraits<TextWriter>());
		RegisterType(engine, "INI", sizeof(INI), asOBJ_VALUE | asGetTypeTraits<INI>());

		RegisterType(engine, "Color", sizeof(Color), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "ColorF", sizeof(ColorF), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "HSV", sizeof(HSV), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);

		RegisterType(engine, "Point", sizeof(Point), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Float2", sizeof(Float2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Vec2", sizeof(Vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Float3", sizeof(Float3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Vec3", sizeof(Vec3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Float4", sizeof(Float4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Vec4", sizeof(Vec4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Circular", sizeof(Circular), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "OffsetCircular", sizeof(OffsetCircular), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Mat3x2", sizeof(Mat3x2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "TriangleIndex", sizeof(TriangleIndex), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);

		RegisterType(engine, "Bezier2", sizeof(Bezier2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Bezier3", sizeof(Bezier3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Line", sizeof(Line), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Rect", sizeof(Rect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "RectF", sizeof(RectF), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Circle", sizeof(Circle), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Ellipse", sizeof(Ellipse), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Triangle", sizeof(Triangle), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Quad", sizeof(Quad), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "RoundRect", sizeof(RoundRect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Polygon", sizeof(Polygon), asOBJ_VALUE | asGetTypeTraits<Polygon>());
		RegisterType(engine, "LineString", sizeof(LineString), asOBJ_VALUE | asGetTypeTraits<LineString>());
		RegisterType(engine, "Spline2D", sizeof(Spline2D), asOBJ_VALUE | asGetTypeTraits<Spline2D>());
		RegisterType(engine, "LineStyleParameters", sizeof(LineStyle::Parameters), asOBJ_VALUE | asOBJ_APP_CLASS_ALLINTS | asGetTypeTraits<LineStyle::Parameters>());
		RegisterType(engine, "LineStyle", sizeof(LineStyle), asOBJ_VALUE | asGetTypeTraits<LineStyle>());
		RegisterType(engine, "Shape2D", sizeof(Shape2D), asOBJ_VALUE | asGetTypeTraits<Shape2D>());
		RegisterType(engine, "FloatRect", sizeof(FloatRect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);

		RegisterType(engine, "Input", sizeof(Input), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Image", sizeof(Image), asOBJ_VALUE | asGetTypeTraits<Image>());

		RegisterType(engine, "TextureFormat", sizeof(TextureFormat), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Texture", sizeof(Texture), asOBJ_VALUE | asGetTypeTraits<Texture>());
		RegisterType(engine, "TextureRegion", sizeof(TextureRegion), asOBJ_VALUE | asGetTypeTraits<TextureRegion>());
		RegisterType(engine, "TexturedQuad", sizeof(TexturedQuad), asOBJ_VALUE | asGetTypeTraits<TexturedQuad>());
		RegisterType(engine, "TexturedCircle", sizeof(TexturedCircle), asOBJ_VALUE | asGetTypeTraits<TexturedCircle>());
		RegisterType(engine, "TexturedRoundRect", sizeof(TexturedRoundRect), asOBJ_VALUE | asGetTypeTraits<TexturedRoundRect>());
		RegisterType(engine, "DynamicTexture", sizeof(DynamicTexture), asOBJ_VALUE | asGetTypeTraits<DynamicTexture>());
		RegisterType(engine, "VideoTexture", sizeof(VideoTexture), asOBJ_VALUE | asGetTypeTraits<VideoTexture>());
		RegisterType(engine, "TextStyle", sizeof(TextStyle), asOBJ_VALUE | asOBJ_APP_CLASS_ALLFLOATS | asGetTypeTraits<TextStyle>());
		RegisterType(engine, "Font", sizeof(Font), asOBJ_VALUE | asGetTypeTraits<Font>());
		RegisterType(engine, "DrawableText", sizeof(DrawableText), asOBJ_VALUE | asGetTypeTraits<DrawableText>());
		RegisterType(engine, "Transformer2D", 0, asOBJ_REF | asOBJ_SCOPED);
		RegisterType(engine, "ScopedViewport2D", sizeof(ScopedViewport2D), asOBJ_VALUE | asGetTypeTraits<ScopedViewport2D>());
		RegisterType(engine, "Camera2D", sizeof(Camera2D), asOBJ_VALUE | asGetTypeTraits<Camera2D>());
		RegisterType(engine, "Emoji", sizeof(Emoji), asOBJ_VALUE | asGetTypeTraits<Emoji>());
		RegisterType(engine, "Icon", sizeof(Icon), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);

		RegisterType(engine, "WaveSample", sizeof(WaveSample), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Wave", sizeof(Wave), asOBJ_VALUE | asGetTypeTraits<Wave>());
		RegisterType(engine, "AudioFileStreaming", sizeof(uint8), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS | asOBJ_APP_CLASS_C);
		RegisterType(engine, "Audio", sizeof(Audio), asOBJ_VALUE | asGetTypeTraits<Audio>());

		RegisterType(engine, "PrintBuffer", 0, asOBJ_REF);
		RegisterType(engine, "Print_impl", sizeof(uint8), asOBJ_VALUE | asOBJ_POD);
		RegisterType(engine, "SayBuffer", 0, asOBJ_REF);
		RegisterType(engine, "Say_impl", sizeof(uint8), asOBJ_VALUE | asOBJ_POD);
		RegisterType(engine, "TextEditState", sizeof(TextEditState), asOBJ_VALUE | asGetTypeTraits<TextEditState>());


		RegisterEnum(engine, "TextEncoding");
		RegisterEnum(engine, "OpenMode");
		RegisterEnum(engine, "SpecialFolder");
		RegisterEnum(engine, "CopyOption");
		RegisterEnum(engine, "WindowStyle");
		RegisterEnum(engine, "CursorStyle");
		RegisterEnum(engine, "ResizeMode");
		RegisterEnum(engine, "TextInputMode");
		RegisterEnum(engine, "LanguageCode");
		RegisterEnum(engine, "TextureDesc");
		RegisterEnum(engine, "TexturePixelFormat");
		RegisterEnum(engine, "FontStyle");
		RegisterEnum(engine, "Typeface");
		RegisterEnum(engine, "FontMethod");
		RegisterEnum(engine, "ImageFormat");
		RegisterEnum(engine, "AdaptiveThresholdMethod");
		RegisterEnum(engine, "BorderType");
		RegisterEnum(engine, "FloodFillConnectivity");
		RegisterEnum(engine, "InterpolationAlgorithm");
		RegisterEnum(engine, "AudioFormat");
		RegisterEnum(engine, "GMInstrument");
		RegisterEnum(engine, "PianoKey");
		RegisterEnum(engine, "MixBus");
		RegisterEnum(engine, "CameraControl");

		assert(engine->GetTypeIdByDecl("char32") == static_cast<int32>(ScriptTypeID::Char32));
		assert(engine->GetTypeIdByDecl("String") == static_cast<int32>(ScriptTypeID::String));
		assert(engine->GetTypeIdByDecl("None_t") == static_cast<int32>(ScriptTypeID::None_t));
		assert(engine->GetTypeIdByDecl("Duration") == static_cast<int32>(ScriptTypeID::Duration));
		assert(engine->GetTypeIdByDecl("Date") == static_cast<int32>(ScriptTypeID::Date));
		assert(engine->GetTypeIdByDecl("DateTime") == static_cast<int32>(ScriptTypeID::DateTime));
		assert(engine->GetTypeIdByDecl("Stopwatch") == static_cast<int32>(ScriptTypeID::Stopwatch));
		assert(engine->GetTypeIdByDecl("VariableSpeedStopwatch") == static_cast<int32>(ScriptTypeID::VariableSpeedStopwatch));
		assert(engine->GetTypeIdByDecl("Timer") == static_cast<int32>(ScriptTypeID::Timer));
		//assert(engine->GetTypeIdByDecl("TimeProfiler") == static_cast<int32>(ScriptTypeID::TimeProfiler));
		assert(engine->GetTypeIdByDecl("MillisecClock") == static_cast<int32>(ScriptTypeID::MillisecClock));
		assert(engine->GetTypeIdByDecl("MicrosecClock") == static_cast<int32>(ScriptTypeID::MicrosecClock));
		assert(engine->GetTypeIdByDecl("RDTSCClock") == static_cast<int32>(ScriptTypeID::RDTSCClock));
		assert(engine->GetTypeIdByDecl("TextReader") == static_cast<int32>(ScriptTypeID::TextReader));
		assert(engine->GetTypeIdByDecl("TextWriterBuffer") == static_cast<int32>(ScriptTypeID::TextWriterBuffer));
		assert(engine->GetTypeIdByDecl("TextWriter") == static_cast<int32>(ScriptTypeID::TextWriter));
		assert(engine->GetTypeIdByDecl("INI") == static_cast<int32>(ScriptTypeID::INI));
		assert(engine->GetTypeIdByDecl("Color") == static_cast<int32>(ScriptTypeID::Color));
		assert(engine->GetTypeIdByDecl("ColorF") == static_cast<int32>(ScriptTypeID::ColorF));
		assert(engine->GetTypeIdByDecl("HSV") == static_cast<int32>(ScriptTypeID::HSV));
		assert(engine->GetTypeIdByDecl("Point") == static_cast<int32>(ScriptTypeID::Point));
		assert(engine->GetTypeIdByDecl("Float2") == static_cast<int32>(ScriptTypeID::Float2));
		assert(engine->GetTypeIdByDecl("Vec2") == static_cast<int32>(ScriptTypeID::Vec2));
		assert(engine->GetTypeIdByDecl("Float3") == static_cast<int32>(ScriptTypeID::Float3));
		assert(engine->GetTypeIdByDecl("Vec3") == static_cast<int32>(ScriptTypeID::Vec3));
		assert(engine->GetTypeIdByDecl("Float4") == static_cast<int32>(ScriptTypeID::Float4));
		assert(engine->GetTypeIdByDecl("Vec4") == static_cast<int32>(ScriptTypeID::Vec4));
		assert(engine->GetTypeIdByDecl("Circular") == static_cast<int32>(ScriptTypeID::Circular));
		assert(engine->GetTypeIdByDecl("OffsetCircular") == static_cast<int32>(ScriptTypeID::OffsetCircular));
		assert(engine->GetTypeIdByDecl("Mat3x2") == static_cast<int32>(ScriptTypeID::Mat3x2));
		assert(engine->GetTypeIdByDecl("TriangleIndex") == static_cast<int32>(ScriptTypeID::TriangleIndex));
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
		assert(engine->GetTypeIdByDecl("LineString") == static_cast<int32>(ScriptTypeID::LineString));
		assert(engine->GetTypeIdByDecl("Spline2D") == static_cast<int32>(ScriptTypeID::Spline2D));
		assert(engine->GetTypeIdByDecl("LineStyleParameters") == static_cast<int32>(ScriptTypeID::LineStyleParameters));
		assert(engine->GetTypeIdByDecl("LineStyle") == static_cast<int32>(ScriptTypeID::LineStyle));
		assert(engine->GetTypeIdByDecl("Shape2D") == static_cast<int32>(ScriptTypeID::Shape2D));
		assert(engine->GetTypeIdByDecl("FloatRect") == static_cast<int32>(ScriptTypeID::FloatRect));
		assert(engine->GetTypeIdByDecl("Input") == static_cast<int32>(ScriptTypeID::Input));
		assert(engine->GetTypeIdByDecl("Image") == static_cast<int32>(ScriptTypeID::Image));
		assert(engine->GetTypeIdByDecl("TextureFormat") == static_cast<int32>(ScriptTypeID::TextureFormat));
		assert(engine->GetTypeIdByDecl("Texture") == static_cast<int32>(ScriptTypeID::Texture));
		assert(engine->GetTypeIdByDecl("TextureRegion") == static_cast<int32>(ScriptTypeID::TextureRegion));
		assert(engine->GetTypeIdByDecl("TexturedQuad") == static_cast<int32>(ScriptTypeID::TexturedQuad));
		assert(engine->GetTypeIdByDecl("TexturedCircle") == static_cast<int32>(ScriptTypeID::TexturedCircle));
		assert(engine->GetTypeIdByDecl("TexturedRoundRect") == static_cast<int32>(ScriptTypeID::TexturedRoundRect));
		assert(engine->GetTypeIdByDecl("DynamicTexture") == static_cast<int32>(ScriptTypeID::DynamicTexture));
		assert(engine->GetTypeIdByDecl("VideoTexture") == static_cast<int32>(ScriptTypeID::VideoTexture));
		assert(engine->GetTypeIdByDecl("TextStyle") == static_cast<int32>(ScriptTypeID::TextStyle));
		assert(engine->GetTypeIdByDecl("Font") == static_cast<int32>(ScriptTypeID::Font));
		assert(engine->GetTypeIdByDecl("DrawableText") == static_cast<int32>(ScriptTypeID::DrawableText));
		assert(engine->GetTypeIdByDecl("Transformer2D") == static_cast<int32>(ScriptTypeID::Transformer2D));
		assert(engine->GetTypeIdByDecl("ScopedViewport2D") == static_cast<int32>(ScriptTypeID::ScopedViewport2D));	
		assert(engine->GetTypeIdByDecl("Camera2D") == static_cast<int32>(ScriptTypeID::Camera2D));
		assert(engine->GetTypeIdByDecl("Emoji") == static_cast<int32>(ScriptTypeID::Emoji));
		assert(engine->GetTypeIdByDecl("Icon") == static_cast<int32>(ScriptTypeID::Icon));
		assert(engine->GetTypeIdByDecl("WaveSample") == static_cast<int32>(ScriptTypeID::WaveSample));
		assert(engine->GetTypeIdByDecl("Wave") == static_cast<int32>(ScriptTypeID::Wave));
		assert(engine->GetTypeIdByDecl("AudioFileStreaming") == static_cast<int32>(ScriptTypeID::AudioFileStreaming));
		assert(engine->GetTypeIdByDecl("Audio") == static_cast<int32>(ScriptTypeID::Audio));
		assert(engine->GetTypeIdByDecl("PrintBuffer") == static_cast<int32>(ScriptTypeID::PrintBuffer));
		assert(engine->GetTypeIdByDecl("Print_impl") == static_cast<int32>(ScriptTypeID::Print_impl));
		assert(engine->GetTypeIdByDecl("SayBuffer") == static_cast<int32>(ScriptTypeID::SayBuffer));
		assert(engine->GetTypeIdByDecl("Say_impl") == static_cast<int32>(ScriptTypeID::Say_impl));
		assert(engine->GetTypeIdByDecl("TextEditState") == static_cast<int32>(ScriptTypeID::TextEditState));

		r = engine->RegisterTypedef("size_t", "uint64"); assert(r >= 0);
		r = engine->RegisterTypedef("GlyphIndex", "uint32"); assert(r >= 0);
	}
}
