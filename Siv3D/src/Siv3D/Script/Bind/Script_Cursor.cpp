//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Cursor.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterCursor(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->RegisterEnumValue("CursorStyle", "Arrow", 0); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "IBeam", 1); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "Cross", 2); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "Hand", 3); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "NotAllowed", 4); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "ResizeUpDown", 5); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "ResizeLeftRight", 6); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "Hidden", 7); assert(r >= 0);
		r = engine->RegisterEnumValue("CursorStyle", "Default", 0); assert(r >= 0);

		r = engine->SetDefaultNamespace("Cursor"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Point Pos()", asFUNCTION(Cursor::Pos), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point PreviousPos()", asFUNCTION(Cursor::PreviousPos), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Delta()", asFUNCTION(Cursor::Delta), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("Vec2 PosF()", asFUNCTION(Cursor::PosF), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 PreviousPosF()", asFUNCTION(Cursor::PreviousPosF), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 DeltaF()", asFUNCTION(Cursor::DeltaF), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("Point PosRaw()", asFUNCTION(Cursor::PosRaw), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point PreviousPosRaw()", asFUNCTION(Cursor::PreviousPosRaw), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point DeltaRaw()", asFUNCTION(Cursor::DeltaRaw), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Point ScreenPos()", asFUNCTION(Cursor::ScreenPos), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point PreviousScreenPos()", asFUNCTION(Cursor::PreviousScreenPos), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point ScreenDelta()", asFUNCTION(Cursor::ScreenDelta), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetPos(int32, int32)", asFUNCTIONPR(Cursor::SetPos, (int32, int32), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetPos(const Point& in)", asFUNCTIONPR(Cursor::SetPos, (const Point&), void), asCALL_CDECL); assert(r >= 0);
	
			r = engine->RegisterGlobalFunction("bool OnClientRect()", asFUNCTION(Cursor::OnClientRect), asCALL_CDECL); assert(r >= 0);
			
			//void SetTransformLocal(const Mat3x2& matrix);
			//void SetTransformCamera(const Mat3x2& matrix);
			//void SetTransformScreen(const Mat3x2& matrix);
			//[[nodiscard]] const Mat3x2& GetTransformLocal();
			//[[nodiscard]] const Mat3x2& GetTransformCamera();
			//[[nodiscard]] const Mat3x2& GetTransformScreen();

			r = engine->RegisterGlobalFunction("void ClipToWindow(bool)", asFUNCTION(Cursor::ClipToWindow), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("void RequestStyle(CursorStyle style)", asFUNCTION(Cursor::RequestStyle), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetDefaultStyle(CursorStyle style)", asFUNCTION(Cursor::SetDefaultStyle), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("CursorStyle GetRequestedStyle()", asFUNCTION(Cursor::GetRequestedStyle), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("CursorStyle GetDefaultStyle()", asFUNCTION(Cursor::GetDefaultStyle), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
