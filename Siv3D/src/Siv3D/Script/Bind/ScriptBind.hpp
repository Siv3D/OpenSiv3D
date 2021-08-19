//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>

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

		//Arg_samplingRate = 67108877,
		//Arg_samplingRateValue,

		TopLeft_ = 67108877,
		TopLeft_Vec2,
		Center_,
		Center_Vec2,

		Char32,
		String,
		None_t,
		Duration,
		Date,
		DateTime,
		Stopwatch,
		VariableSpeedStopwatch,
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
		Float3,
		Vec3,
		Float4,
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

		//
		Input,

		Image,

		WaveSample,
		Wave,
		Audio,

		TextureFormat,
		Texture,
		TextureRegion,
		TexturedQuad,
		TexturedCircle,
		TexturedRoundRect,
		DynamicTexture,
		Font,
		DrawableText,

		Transformer2D,
		ScopedViewport2D,

		Emoji,
		Icon,

		PrintBuffer,
		Print_impl,
		SayBuffer,
		Say_impl,
	};

	using AngelScript::asIScriptEngine;

	void RegisterTypes(asIScriptEngine* engine);
	void RegisterYesNo(asIScriptEngine* engine);
	void RegisterNamedParameter(asIScriptEngine* engine);
	void RegisterUtility(asIScriptEngine* engine);
	void RegisterChar(asIScriptEngine* engine);
	void RegisterNone_t(asIScriptEngine* engine);
	void RegisterOptional(asIScriptEngine* engine);
	void RegisterNumber(asIScriptEngine* engine);
	void RegisterFloatingPoint(asIScriptEngine* engine);

	void RegisterDuration(asIScriptEngine* engine);
	void RegisterDate(asIScriptEngine* engine);
	void RegisterDateTime(asIScriptEngine* engine);
	void RegisterTime(asIScriptEngine* engine);
	void RegisterStopwatch(asIScriptEngine* engine);
	void RegisterVariableSpeedStopwatch(asIScriptEngine* engine);
	void RegisterTimer(asIScriptEngine* engine);
	void RegisterProfiler(asIScriptEngine* engine);
	void RegisterMillisecClock(asIScriptEngine* engine);
	void RegisterMicrosecClock(asIScriptEngine* engine);
	void RegisterRDTSCClock(asIScriptEngine* engine);

	void RegisterSpecialFolder(asIScriptEngine* engine);
	void RegisterCopyOption(asIScriptEngine* engine);
	void RegisterFileSystem(asIScriptEngine* engine);
	void RegisterResource(asIScriptEngine* engine);
	void RegisterMathConstants(asIScriptEngine* engine);
	void RegisterMath(asIScriptEngine* engine);
	void RegisterEasing(asIScriptEngine* engine);
	void RegisterPeriodic(asIScriptEngine* engine);
	void RegisterPrimeNumber(asIScriptEngine* engine);

	void RegisterColor(asIScriptEngine* engine);
	void RegisterColorF(asIScriptEngine* engine);
	void RegisterHSV(asIScriptEngine* engine);
	void RegisterPalette(asIScriptEngine* engine);

	void RegisterPoint(asIScriptEngine* engine);
	void RegisterVec2(asIScriptEngine* engine);
	void RegisterFloat2(asIScriptEngine* engine);


	void RegisterPolygon(asIScriptEngine* engine);



	void RegisterInput(asIScriptEngine* engine);
	void RegisterKeyboard(asIScriptEngine* engine);
	void RegisterMouse(asIScriptEngine* engine);


	void RegisterRandom(asIScriptEngine* engine);
	void RegisterPrint(asIScriptEngine* engine);
	void RegisterPutText(asIScriptEngine* engine);
	void RegisterThreading(asIScriptEngine* engine);
	void RegisterUserAction(asIScriptEngine* engine);
	void RegisterSystem(asIScriptEngine* engine);
	void RegisterWindowStyle(asIScriptEngine* engine);
	void RegisterWindow(asIScriptEngine* engine);
	void RegisterMonitor(asIScriptEngine* engine);
	void RegisterCursorStyle(asIScriptEngine* engine);
	void RegisterCursor(asIScriptEngine* engine);
	void RegisterGraphics(asIScriptEngine* engine);
	void RegisterResizeMode(asIScriptEngine* engine);
	void RegisterScene(asIScriptEngine* engine);
	void RegisterTextInputMode(asIScriptEngine* engine);
	void RegisterTextInput(asIScriptEngine* engine);
	void RegisterSimpleGUI(asIScriptEngine* engine);
	void RegisterLanguageCode(asIScriptEngine* engine);
	void RegisterTextToSpeech(asIScriptEngine* engine);
	void RegisterSay(asIScriptEngine* engine);

}
