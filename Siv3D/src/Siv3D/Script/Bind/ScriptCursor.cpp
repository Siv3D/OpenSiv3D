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
# include <Siv3D/Cursor.hpp>

namespace s3d
{
	using namespace AngelScript;

	static void CursorSetDefaultStyle(int32 cursorStyle)
	{
		Cursor::SetDefaultStyle(ToEnum<CursorStyle>(static_cast<uint8>(cursorStyle)));
	}

	static void CursorRequestStyle(int32 cursorStyle)
	{
		Cursor::RequestStyle(ToEnum<CursorStyle>(static_cast<uint8>(cursorStyle)));
	}

	void RegisterCursor(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Cursor"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Point Pos()", asFUNCTION(Cursor::Pos), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 PosF()", asFUNCTION(Cursor::PosF), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Point PreviousPos()", asFUNCTION(Cursor::PreviousPos), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 PreviousPosF()", asFUNCTION(Cursor::PreviousPosF), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Point Delta()", asFUNCTION(Cursor::Delta), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 DeltaF()", asFUNCTION(Cursor::DeltaF), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Point PosRaw()", asFUNCTION(Cursor::PosRaw), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point PreviousPosRaw()", asFUNCTION(Cursor::PreviousPosRaw), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point DeltaRaw()", asFUNCTION(Cursor::DeltaRaw), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Point ScreenPos()", asFUNCTION(Cursor::ScreenPos), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point ScreenPreviousPos()", asFUNCTION(Cursor::ScreenPreviousPos), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point ScreenDelta()", asFUNCTION(Cursor::ScreenDelta), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetPos(int32, int32)", asFUNCTIONPR(Cursor::SetPos, (int32, int32), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetPos(Point)", asFUNCTIONPR(Cursor::SetPos, (Point), void), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool OnClientRect()", asFUNCTION(Cursor::OnClientRect), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool IsClippedToWindow()", asFUNCTION(Cursor::IsClippedToWindow), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void ClipToWindow(bool)", asFUNCTION(Cursor::ClipToWindow), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetDefaultStyle(CursorStyle style)", asFUNCTION(CursorSetDefaultStyle), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void RequestStyle(CursorStyle style)", asFUNCTION(CursorRequestStyle), asCALL_CDECL); assert(r >= 0);

			//RegisterCustomCursorStyle
			//RequestStyle

			//r = engine->RegisterGlobalFunction("const Mat3x2& GetLocalTransform()", asFUNCTION(Cursor::GetLocalTransform), asCALL_CDECL); assert(r >= 0);
			//r = engine->RegisterGlobalFunction("const Mat3x2& GetCameraTransform()", asFUNCTION(Cursor::GetCameraTransform), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
