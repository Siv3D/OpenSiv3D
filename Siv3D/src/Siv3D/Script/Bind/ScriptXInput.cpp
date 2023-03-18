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
# include <Siv3D/XInput.hpp>
# include "ScriptOptional.hpp"

namespace s3d
{
	using namespace AngelScript;

	using ValueType = detail::XInput_impl;

	static const ValueType& XInputOpCall(size_t playerIndex)
	{
		return XInput(playerIndex);
	}

	static void ConstructXV(XInputVibration* self)
	{
		new(self) XInputVibration();
	}

	static void ConstructS(size_t playerIndex, ValueType* self)
	{
		new(self) ValueType(playerIndex);
	}

	static CScriptOptional XInputLeftThumbD4(double threshold, ValueType& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Optional<int32>");

		if (const auto result = self.leftThumbD4(threshold))
		{
			char32 value = *result;

			return CScriptOptional{ &value, typeID };
		}
		else
		{
			return CScriptOptional{ typeID };
		}
	}

	static CScriptOptional XInputLeftThumbD8(double threshold, ValueType& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Optional<int32>");

		if (const auto result = self.leftThumbD8(threshold))
		{
			char32 value = *result;

			return CScriptOptional{ &value, typeID };
		}
		else
		{
			return CScriptOptional{ typeID };
		}
	}

	static CScriptOptional XInputRightThumbD4(double threshold, ValueType& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Optional<int32>");

		if (const auto result = self.rightThumbD4(threshold))
		{
			char32 value = *result;

			return CScriptOptional{ &value, typeID };
		}
		else
		{
			return CScriptOptional{ typeID };
		}
	}

	static CScriptOptional XInputRightThumbD8(double threshold, ValueType& self)
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Optional<int32>");

		if (const auto result = self.rightThumbD8(threshold))
		{
			char32 value = *result;

			return CScriptOptional{ &value, typeID };
		}
		else
		{
			return CScriptOptional{ typeID };
		}
	}

	void RegisterXInput(asIScriptEngine* engine)
	{
		static const uint8 XInputHelperPlaceholder = 0;
		const char XInputVibrationTypeName[] = "XInputVibration";
		const char XInputHelperTypeName[] = "XInput_helper";
		const char XInputImplTypeName[] = "XInput_impl";

		[[maybe_unused]] int32 r = 0;
		r = engine->RegisterObjectProperty(XInputVibrationTypeName, "double leftMotor", asOFFSET(XInputVibration, leftMotor)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputVibrationTypeName, "double rightMotor", asOFFSET(XInputVibration, rightMotor)); assert(r >= 0);
		r = engine->RegisterObjectBehaviour(XInputVibrationTypeName, asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructXV), asCALL_CDECL_OBJLAST); assert(r >= 0);


		r = engine->RegisterObjectMethod(XInputHelperTypeName, "const XInput_impl& opCall(size_t) const", asFUNCTION(XInputOpCall), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const XInput_helper XInput", (void*)&XInputHelperPlaceholder); assert(r >= 0);

		r = engine->RegisterObjectProperty(XInputImplTypeName, "uint32 playerIndex", asOFFSET(ValueType, playerIndex)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonUp", asOFFSET(ValueType, buttonUp)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonDown", asOFFSET(ValueType, buttonDown)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonLeft", asOFFSET(ValueType, buttonLeft)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonRight", asOFFSET(ValueType, buttonRight)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonStart", asOFFSET(ValueType, buttonStart)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonMenu", asOFFSET(ValueType, buttonMenu)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonBack", asOFFSET(ValueType, buttonBack)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonView", asOFFSET(ValueType, buttonView)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonLThumb", asOFFSET(ValueType, buttonLThumb)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonRThumb", asOFFSET(ValueType, buttonRThumb)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonLB", asOFFSET(ValueType, buttonLB)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonRB", asOFFSET(ValueType, buttonRB)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonA", asOFFSET(ValueType, buttonA)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonB", asOFFSET(ValueType, buttonB)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonX", asOFFSET(ValueType, buttonX)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "Input buttonY", asOFFSET(ValueType, buttonY)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "double leftTrigger", asOFFSET(ValueType, leftTrigger)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "double rightTrigger", asOFFSET(ValueType, rightTrigger)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "double leftThumbX", asOFFSET(ValueType, leftThumbX)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "double leftThumbY", asOFFSET(ValueType, leftThumbY)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "double rightThumbX", asOFFSET(ValueType, rightThumbX)); assert(r >= 0);
		r = engine->RegisterObjectProperty(XInputImplTypeName, "double rightThumbY", asOFFSET(ValueType, rightThumbY)); assert(r >= 0);

		//
		//	Constructor
		//
		r = engine->RegisterObjectBehaviour(XInputImplTypeName, asBEHAVE_CONSTRUCT, "void f(size_t) explicit", asFUNCTION(ConstructS), asCALL_CDECL_OBJLAST); assert(r >= 0);

		r = engine->RegisterObjectMethod(XInputImplTypeName, "bool isConnected() const", asMETHODPR(ValueType, isConnected, () const, bool), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(XInputImplTypeName, "bool opImplConv() const", asMETHODPR(ValueType, operator bool, () const, bool), asCALL_THISCALL); assert(r >= 0);

		//setLeftTriggerDeadZone
		//setRightTriggerDeadZone
		//setLeftThumbDeadZone
		//setRightThumbDeadZone

		r = engine->RegisterObjectMethod(XInputImplTypeName, "Optional<int32> leftThumbD4(double threshold = 0.2) const", asFUNCTION(XInputLeftThumbD4), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(XInputImplTypeName, "Optional<int32> leftThumbD8(double threshold = 0.2) const", asFUNCTION(XInputLeftThumbD8), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(XInputImplTypeName, "Optional<int32> rightThumbD4(double threshold = 0.2) const", asFUNCTION(XInputRightThumbD4), asCALL_CDECL_OBJLAST); assert(r >= 0);
		r = engine->RegisterObjectMethod(XInputImplTypeName, "Optional<int32> rightThumbD8(double threshold = 0.2) const", asFUNCTION(XInputRightThumbD8), asCALL_CDECL_OBJLAST); assert(r >= 0);
	
		r = engine->RegisterObjectMethod(XInputImplTypeName, "void setVibration(const XInputVibration& in) const", asMETHODPR(ValueType, setVibration, (const XInputVibration&) const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(XInputImplTypeName, "const XInputVibration& getVibration() const", asMETHODPR(ValueType, getVibration, () const, const XInputVibration&), asCALL_THISCALL); assert(r >= 0);

		r = engine->RegisterObjectMethod(XInputImplTypeName, "void stopVibration() const", asMETHODPR(ValueType, stopVibration, () const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(XInputImplTypeName, "void pauseVibration() const", asMETHODPR(ValueType, pauseVibration, () const, void), asCALL_THISCALL); assert(r >= 0);
		r = engine->RegisterObjectMethod(XInputImplTypeName, "void resumeVibration() const", asMETHODPR(ValueType, resumeVibration, () const, void), asCALL_THISCALL); assert(r >= 0);
	}
}
