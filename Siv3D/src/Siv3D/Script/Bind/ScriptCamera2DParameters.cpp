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

# include <Siv3D/Script.hpp>
# include <Siv3D/Camera2D.hpp>
# include "ScriptCamera2DParameters.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ValueType = ScriptCamera2DParameters;

	static void ConstructDefault(ValueType* self)
	{
		new(self) ValueType();
	}

	static ValueType C2Make(int32 c)
	{
		Camera2DParameters cp = Camera2DParameters::Make(ToEnum<CameraControl>(static_cast<uint8>(c)));

		return ValueType
		{
			.minScale = cp.minScale,
			.maxScale = cp.maxScale,
			.scaleSmoothTime = cp.scaleSmoothTime,
			.positionSmoothTime = cp.positionSmoothTime,
			.wheelScaleFactor = cp.wheelScaleFactor,
			.grabSpeedFactor = cp.grabSpeedFactor,
			.controlScaleFactor = cp.controlScaleFactor,
			.controlSpeedFactor = cp.controlSpeedFactor,
			.type = static_cast<double>(c),
		};
	}

	static ValueType C2Default()
	{
		return C2Make(FromEnum(CameraControl::Default));
	}

	static ValueType C2MouseOnly()
	{
		return C2Make(FromEnum(CameraControl::Mouse));
	}

	static ValueType C2KeyboardOnly()
	{
		return C2Make(FromEnum(CameraControl::Keyboard));
	}

	static ValueType C2NoControl()
	{
		return C2Make(FromEnum(CameraControl::None_));
	}

	void RegisterCamera2DParameters(asIScriptEngine* engine)
	{
		constexpr char TypeName[] = "Camera2DParameters";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(TypeName, "double minScale", asOFFSET(ScriptCamera2DParameters, minScale)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double maxScale", asOFFSET(ScriptCamera2DParameters, maxScale)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double scaleSmoothTime", asOFFSET(ScriptCamera2DParameters, scaleSmoothTime)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double positionSmoothTime", asOFFSET(ScriptCamera2DParameters, positionSmoothTime)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double wheelScaleFactor", asOFFSET(ScriptCamera2DParameters, wheelScaleFactor)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double grabSpeedFactor", asOFFSET(ScriptCamera2DParameters, grabSpeedFactor)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double controlScaleFactor", asOFFSET(ScriptCamera2DParameters, controlScaleFactor)); assert(r >= 0);
		r = engine->RegisterObjectProperty(TypeName, "double controlSpeedFactor", asOFFSET(ScriptCamera2DParameters, controlSpeedFactor)); assert(r >= 0);

		//
		//	Constructor
		//
		r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructDefault), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Camera2DParameters Make(CameraControl)", asFUNCTION(C2Make), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Camera2DParameters Default()", asFUNCTION(C2Default), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Camera2DParameters MouseOnly()", asFUNCTION(C2MouseOnly), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Camera2DParameters KeyboardOnly()", asFUNCTION(C2KeyboardOnly), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Camera2DParameters NoControl()", asFUNCTION(C2NoControl), asCALL_CDECL); assert(r >= 0);
		}
	}
}
