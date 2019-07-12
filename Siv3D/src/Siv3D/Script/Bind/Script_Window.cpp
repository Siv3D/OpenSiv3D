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
# include <Siv3D/Window.hpp>
# include "Script_Optional.hpp"
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void SetFullscreen1(bool fullscreen, const CScriptOptional& fullscreenResolution, WindowResizeOption resizeOption)
	{
		if (fullscreenResolution.HasValue())
		{
			Window::SetFullscreen(fullscreen , *static_cast<const Size*>(fullscreenResolution.At()), resizeOption);
		}
		else
		{
			Window::SetFullscreen(fullscreen, unspecified, resizeOption);
		}
	}

	void SetFullscreen2(bool fullscreen, uint8, WindowResizeOption resizeOption)
	{
		Window::SetFullscreen(fullscreen, unspecified, resizeOption);
	}

	void RegisterWindow(asIScriptEngine* engine)
	{
		int32 r = 0;

		{
			r = engine->RegisterEnumValue("WindowStyle", "Fixed", static_cast<uint32>(WindowStyle::Fixed)); assert(r >= 0);
			r = engine->RegisterEnumValue("WindowStyle", "Sizable", static_cast<uint32>(WindowStyle::Sizable)); assert(r >= 0);
			r = engine->RegisterEnumValue("WindowStyle", "Frameless", static_cast<uint32>(WindowStyle::Frameless)); assert(r >= 0);
		}

		{
			r = engine->RegisterEnumValue("WindowResizeOption", "ResizeSceneSize", static_cast<uint32>(WindowResizeOption::ResizeSceneSize)); assert(r >= 0);
			r = engine->RegisterEnumValue("WindowResizeOption", "KeepSceneSize", static_cast<uint32>(WindowResizeOption::KeepSceneSize)); assert(r >= 0);
			r = engine->RegisterEnumValue("WindowResizeOption", "UseDefaultScaleMode", static_cast<uint32>(WindowResizeOption::UseDefaultScaleMode)); assert(r >= 0);
		}

		r = engine->SetDefaultNamespace("Window"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const Point DefaultClientSize", (void*)&Window::DefaultClientSize); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetTitle(const String& in)", asFUNCTIONPR(Window::SetTitle, (const String&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("const String& GetTitle()", asFUNCTION(Window::GetTitle), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetStyle(WindowStyle)", asFUNCTION(Window::SetStyle), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("WindowStyle GetStyle()", asFUNCTION(Window::GetStyle), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Point ClientSize()", asFUNCTION(Window::ClientSize), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point ClientCenter()", asFUNCTION(Window::ClientCenter), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 ClientWidth()", asFUNCTION(Window::ClientWidth), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 ClientHeight()", asFUNCTION(Window::ClientHeight), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetPos(const Point& in)", asFUNCTIONPR(Window::SetPos, (const Point&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetPos(int32, int32)", asFUNCTIONPR(Window::SetPos, (int32, int32), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Centering()", asFUNCTION(Window::Centering), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("bool Resize(const Point& in, WindowResizeOption option = WindowResizeOption::ResizeSceneSize, bool resize = true)", asFUNCTIONPR(Window::Resize, (const Size&, WindowResizeOption, bool), bool), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool Resize(int32, int32, WindowResizeOption option = WindowResizeOption::ResizeSceneSize, bool resize = true)", asFUNCTIONPR(Window::Resize, (int32, int32, WindowResizeOption, bool), bool), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void Maximize()", asFUNCTION(Window::Maximize), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Restore()", asFUNCTION(Window::Restore), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Minimize()", asFUNCTION(Window::Minimize), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetFullscreen(bool, const Optional<Point>& in = unspecified, WindowResizeOption option = WindowResizeOption::ResizeSceneSize)", asFUNCTION(SetFullscreen1), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetFullscreen(bool, None_t, WindowResizeOption option = WindowResizeOption::ResizeSceneSize)", asFUNCTION(SetFullscreen2), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
