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
		String = 67108877,

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

		SayBuffer,
		Say_impl,

		Key,

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
	};

	using AngelScript::asIScriptEngine;

	void RegisterTypes(asIScriptEngine* engine);
	void RegisterYesNo(asIScriptEngine* engine);
	void RegisterUtility(asIScriptEngine* engine);
	void RegisterNone_t(asIScriptEngine* engine);
	void RegisterOptional(asIScriptEngine* engine);
	void RegisterDuration(asIScriptEngine* engine);
	void RegisterDate(asIScriptEngine* engine);
	void RegisterDateTime(asIScriptEngine* engine);
	void RegisterTime(asIScriptEngine* engine);
	void RegisterStopwatch(asIScriptEngine* engine);
	void RegisterVariableSpeedStopwatch(asIScriptEngine* engine);
	void RegisterTimer(asIScriptEngine* engine);
	void RegisterMillisecClock(asIScriptEngine* engine);
	void RegisterMicrosecClock(asIScriptEngine* engine);
	void RegisterRDTSCClock(asIScriptEngine* engine);

	void RegisterPrint(asIScriptEngine* engine);
}
