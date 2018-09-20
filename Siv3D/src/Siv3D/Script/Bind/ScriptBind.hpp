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

# pragma once

namespace AngelScript
{
	class asIScriptEngine;
}

namespace s3d
{
	enum class ScriptTypeID
	{
		Void = 0,
		Bool = 1,
		Int8 = 2,
		Int16 = 3,
		Int32 = 4,
		Int64 = 5,
		Uint8 = 6,
		Uint16 = 7,
		Uint32 = 8,
		Uint64 = 9,
		Float = 10,
		Double = 11,

		//Optional = ,
		Arg_samplingRate = 67108877,
		Arg_samplingRateValue,
		String,
		None_t,
		Duration,
		Date,
		DateTime,
		Stopwatch,
		CustomStopwatch,
		Timer,
		//TimeProfiler,
		MillisecClock,
		MicrosecClock,
		RDTSCClock,
		Color,
		ColorF,
		HSV,
		Point,
		Float2,
		Vec2,
		Vec3,
		Vec4,
		Circular,
		OffsetCircular,
		Mat3x2,
		Bezier2,
		Bezier3,
		Line,
		Rect,
		RectF,
		Circle,
		Ellipse,
		Triangle,
		Quad,
		RoundRect,
		Polygon,
		MultiPolygon,
		LineString,

		FloatRect,

		LineStyle,
		LineStyleParameters,
		Shape2D,

		//CursorStyle,

		//
		Image,
		Key,

		WaveSample,
		Wave,
		Audio,

		Texture,
		TextureRegion,
		TexturedQuad,
		TexturedCircle,
		TexturedRoundRect,
		DynamicTexture,
		Font,
		DrawableText,

		Transformer2D,
		ViewportBlock2D,

		Emoji,
		Icon,

		PrintBuffer,
		Print_impl,

	};

	void RegisterTypes(AngelScript::asIScriptEngine* engine);
	void RegisterUtility(AngelScript::asIScriptEngine* engine);
	void RegisterNamedArg(AngelScript::asIScriptEngine* engine);
	void RegisterFormat(AngelScript::asIScriptEngine* engine);
	void RegisterNone_t(AngelScript::asIScriptEngine* engine);
	void RegisterOptional(AngelScript::asIScriptEngine* engine);
	void RegisterDuration(AngelScript::asIScriptEngine* engine);
	void RegisterDate(AngelScript::asIScriptEngine* engine);
	void RegisterDateTime(AngelScript::asIScriptEngine* engine);
	void RegisterTime(AngelScript::asIScriptEngine* engine);
	void RegisterStopwatch(AngelScript::asIScriptEngine* engine);
	void RegisterCustomStopwatch(AngelScript::asIScriptEngine* engine);
	void RegisterTimer(AngelScript::asIScriptEngine* engine);
	//void RegisterTimeProfiler(AngelScript::asIScriptEngine* engine);
	void RegisterMillisecClock(AngelScript::asIScriptEngine* engine);
	void RegisterMicrosecClock(AngelScript::asIScriptEngine* engine);
	void RegisterRDTSCClock(AngelScript::asIScriptEngine* engine);
	//void RegisterDirectoryWatcher(AngelScript::asIScriptEngine* engine);
	void RegisterColor(AngelScript::asIScriptEngine* engine);
	void RegisterColorF(AngelScript::asIScriptEngine* engine);
	void RegisterPalette(AngelScript::asIScriptEngine* engine);
	void RegisterHSV(AngelScript::asIScriptEngine* engine);
	void RegisterPoint(AngelScript::asIScriptEngine* engine);
	void RegisterFloat2(AngelScript::asIScriptEngine* engine);
	void RegisterVec2(AngelScript::asIScriptEngine* engine);
	void RegisterVec3(AngelScript::asIScriptEngine* engine);
	void RegisterVec4(AngelScript::asIScriptEngine* engine);
	void RegisterCircular(AngelScript::asIScriptEngine* engine);
	void RegisterOffsetCircular(AngelScript::asIScriptEngine* engine);
	//void RegisterCylindrical(AngelScript::asIScriptEngine* engine);
	//void RegisterSpherical(AngelScript::asIScriptEngine* engine);
	void RegisterMat3x2(AngelScript::asIScriptEngine* engine);
	void RegisterBezier2(AngelScript::asIScriptEngine* engine);
	void RegisterBezier3(AngelScript::asIScriptEngine* engine);
	void RegisterLine(AngelScript::asIScriptEngine* engine);
	void RegisterRect(AngelScript::asIScriptEngine* engine);
	void RegisterRectF(AngelScript::asIScriptEngine* engine);
	void RegisterCircle(AngelScript::asIScriptEngine* engine);
	void RegisterEllipse(AngelScript::asIScriptEngine* engine);
	void RegisterTriangle(AngelScript::asIScriptEngine* engine);
	void RegisterQuad(AngelScript::asIScriptEngine* engine);
	void RegisterRoundRect(AngelScript::asIScriptEngine* engine);
	void RegisterPolygon(AngelScript::asIScriptEngine* engine);
	//void RegisterMultiPolygon(AngelScript::asIScriptEngine* engine);
	void RegisterLineString(AngelScript::asIScriptEngine* engine);

	void RegisterFloatRect(AngelScript::asIScriptEngine* engine);

	void RegisterLineStyle(AngelScript::asIScriptEngine* engine);
	void RegisterShape2D(AngelScript::asIScriptEngine* engine);
	void RegisterRandom(AngelScript::asIScriptEngine* engine);
	void RegisterMathConstants(AngelScript::asIScriptEngine* engine);
	void RegisterMath(AngelScript::asIScriptEngine* engine);

	void RegisterPeriodic(AngelScript::asIScriptEngine* engine);
	void RegisterEasing(AngelScript::asIScriptEngine* engine);

	void RegisterImage(AngelScript::asIScriptEngine* engine);

	void RegisterKey(AngelScript::asIScriptEngine* engine);
	void RegisterMouse(AngelScript::asIScriptEngine* engine);

	void RegisterSoundFont(AngelScript::asIScriptEngine* engine);
	void RegisterWave(AngelScript::asIScriptEngine* engine);
	void RegisterAudio(AngelScript::asIScriptEngine* engine);

	void RegisterTexture(AngelScript::asIScriptEngine* engine);
	void RegisterTextureRegion(AngelScript::asIScriptEngine* engine);
	void RegisterTexturedQuad(AngelScript::asIScriptEngine* engine);
	void RegisterTexturedCircle(AngelScript::asIScriptEngine* engine);
	void RegisterTexturedRoundRect(AngelScript::asIScriptEngine* engine);
	void RegisterDynamicTexture(AngelScript::asIScriptEngine* engine);
	void RegisterFont(AngelScript::asIScriptEngine* engine);
	void RegisterDrawableText(AngelScript::asIScriptEngine* engine);
	void RegisterTransformer2D(AngelScript::asIScriptEngine* engine);
	void RegisterViewportBlock2D(AngelScript::asIScriptEngine* engine);

	void RegisterEmoji(AngelScript::asIScriptEngine* engine);
	void RegisterIcon(AngelScript::asIScriptEngine* engine);

	void RegisterPrint(AngelScript::asIScriptEngine* engine);

	void RegisterSystem(AngelScript::asIScriptEngine* engine);
	void RegisterWindow(AngelScript::asIScriptEngine* engine);
	void RegisterCursor(AngelScript::asIScriptEngine* engine);
	void RegisterGraphics(AngelScript::asIScriptEngine* engine);
	void RegisterProfiler(AngelScript::asIScriptEngine* engine);
	void RegisterDialog(AngelScript::asIScriptEngine* engine);

	//void Register_Webcam(asIScriptEngine* engine);
}
