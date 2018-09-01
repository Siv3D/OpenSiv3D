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

# include <Siv3D/Script.hpp>
# include <Siv3D/Periodic.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterWindow(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("Window"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Point Size()", asFUNCTION(Window::Size), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Center()", asFUNCTION(Window::Center), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Width()", asFUNCTION(Window::Width), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Height()", asFUNCTION(Window::Height), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Rect ClientRect()", asFUNCTION(Window::ClientRect), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetPos(const Point& in)", asFUNCTIONPR(Window::SetPos, (const Point&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetPos(int32, int32)", asFUNCTIONPR(Window::SetPos, (int32, int32), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Centering()", asFUNCTION(Window::Centering), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool Resize(int32, int32, bool resize = true)", asFUNCTIONPR(Window::Resize, (int32, int32, bool), bool), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool Resize(const Point& in, bool resize = true)", asFUNCTIONPR(Window::Resize, (const Size&, bool), bool), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetBaseSize(const Point& in)", asFUNCTIONPR(Window::SetBaseSize, (const Point&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point BaseSize()", asFUNCTION(Window::BaseSize), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Point BaseCenter()", asFUNCTION(Window::BaseCenter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 BaseWidth()", asFUNCTION(Window::BaseWidth), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 BaseHeight()", asFUNCTION(Window::BaseHeight), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Rect BaseClientRect()", asFUNCTION(Window::BaseClientRect), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
