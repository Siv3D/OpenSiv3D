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
		SampleRate_,
		SampleRate_Uint32,

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

		TextReader,
		TextWriterBuffer,
		TextWriter,
		INI,

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
		TriangleIndex,
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
		//MultiPolygon,
		LineString,
		Spline2D,
		LineStyleParameters,
		LineStyle,
		Shape2D,
		FloatRect,

		//
		Input,
		Image,
		TextureFormat,
		Texture,
		TextureRegion,
		TexturedQuad,
		TexturedCircle,
		TexturedRoundRect,
		DynamicTexture,
		VideoTexture,
		TextStyle,
		Font,
		DrawableText,
		Transformer2D,
		ScopedViewport2D,
		Camera2DParameters,
		Camera2D,
		Emoji,
		Icon,

		WaveSample,
		Wave,
		AudioFileStreaming,
		Audio,

		PrintBuffer,
		Print_impl,
		SayBuffer,
		Say_impl,
		TextEditState,
		LicenseInfo,

		XInputVibration,
		XInput_helper,
		XInput_impl,
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
	void RegisterParse(asIScriptEngine* engine);

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

	void RegisterTextEncoding(asIScriptEngine* engine);
	void RegisterOpenMode(asIScriptEngine* engine);
	void RegisterTextReader(asIScriptEngine* engine);
	void RegisterTextWriter(asIScriptEngine* engine);
	void RegisterINI(asIScriptEngine* engine);

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
	void RegisterVec3(asIScriptEngine* engine);
	void RegisterFloat3(asIScriptEngine* engine);
	void RegisterVec4(asIScriptEngine* engine);
	void RegisterFloat4(asIScriptEngine* engine);
	void RegisterCircular(asIScriptEngine* engine);
	void RegisterOffsetCircular(asIScriptEngine* engine);
	void RegisterMat3x2(asIScriptEngine* engine);
	void RegisterTriangleIndex(asIScriptEngine* engine);
	void RegisterBezier2(asIScriptEngine* engine);
	void RegisterBezier3(asIScriptEngine* engine);
	void RegisterLine(asIScriptEngine* engine);
	void RegisterRect(asIScriptEngine* engine);
	void RegisterRectF(asIScriptEngine* engine);
	void RegisterCircle(asIScriptEngine* engine);
	void RegisterEllipse(asIScriptEngine* engine);
	void RegisterTriangle(asIScriptEngine* engine);
	void RegisterQuad(asIScriptEngine* engine);
	void RegisterRoundRect(asIScriptEngine* engine);
	void RegisterPolygon(asIScriptEngine* engine);
	void RegisterLineString(asIScriptEngine* engine);
	void RegisterSpline2D(asIScriptEngine* engine);
	void RegisterLineStyleParameters(asIScriptEngine* engine);
	void RegisterLineStyle(asIScriptEngine* engine);
	void RegisterShape2D(asIScriptEngine* engine);
	void RegisterFloatRect(asIScriptEngine* engine);
	void RegisterInterpolation(asIScriptEngine* engine);

	void RegisterTexturePixelFormat(asIScriptEngine* engine);
	void RegisterTextureFormat(asIScriptEngine* engine);
	void RegisterTextureDesc(asIScriptEngine* engine);
	void RegisterTexture(asIScriptEngine* engine);
	void RegisterTextureRegion(asIScriptEngine* engine);
	void RegisterTexturedQuad(asIScriptEngine* engine);
	void RegisterTexturedCircle(asIScriptEngine* engine);
	void RegisterTexturedRoundRect(asIScriptEngine* engine);
	void RegisterDynamicTexture(asIScriptEngine* engine);
	void RegisterVideoTexture(asIScriptEngine* engine);

	void RegisterFontStyle(asIScriptEngine * engine);
	void RegisterTypeface(asIScriptEngine * engine);
	void RegisterFontMethod(asIScriptEngine * engine);
	void RegisterTextStyle(asIScriptEngine* engine);
	void RegisterFont(asIScriptEngine* engine);
	void RegisterDrawableText(asIScriptEngine* engine);

	void RegisterInput(asIScriptEngine* engine);
	void RegisterKeyboard(asIScriptEngine* engine);
	void RegisterMouse(asIScriptEngine* engine);
	void RegisterXInput(asIScriptEngine* engine);

	void RegisterImageFormat(asIScriptEngine* engine);
	void RegisterImage(asIScriptEngine* engine);

	void RegisterTransformer2D(asIScriptEngine* engine);
	void RegisterScopedViewport2D(asIScriptEngine* engine);
	void RegisterCamera2DParameters(asIScriptEngine* engine);
	void RegisterCameraControl(asIScriptEngine* engine);
	void RegisterCamera2D(asIScriptEngine* engine);

	void RegisterEmoji(asIScriptEngine* engine);
	void RegisterIcon(asIScriptEngine* engine);
	void RegisterAudioFormat(asIScriptEngine* engine);
	void RegisterGMInstrument(asIScriptEngine* engine);
	void RegisterPianoKey(asIScriptEngine* engine);
	void RegisterWaveSample(asIScriptEngine* engine);
	void RegisterWave(asIScriptEngine* engine);
	void RegisterMixBus(asIScriptEngine* engine);
	void RegisterAudio(asIScriptEngine* engine);
	void RegisterGlobalAudio(asIScriptEngine* engine);

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
	void RegisterGraphics2D(asIScriptEngine* engine);
	void RegisterResizeMode(asIScriptEngine* engine);
	void RegisterScene(asIScriptEngine* engine);
	void RegisterTextInputMode(asIScriptEngine* engine);
	void RegisterTextInput(asIScriptEngine* engine);
	void RegisterTextEditState(asIScriptEngine* engine);
	void RegisterLicenseInfo(asIScriptEngine* engine);
	void RegisterLicenseManager(asIScriptEngine* engine);
	void RegisterSimpleGUI(asIScriptEngine* engine);
	void RegisterLanguageCode(asIScriptEngine* engine);
	void RegisterTextToSpeech(asIScriptEngine* engine);
	void RegisterSay(asIScriptEngine* engine);
	void RegisterDialog(asIScriptEngine* engine);
}
