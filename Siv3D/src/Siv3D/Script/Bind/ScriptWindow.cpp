//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/WindowState.hpp>

namespace s3d
{
	using namespace AngelScript;

	static void WindowSetStyle(int32 style)
	{
		Window::SetStyle(ToEnum<WindowStyle>(static_cast<uint8>(style)));
	}

	static int32 WindowGetStyle()
	{
		return FromEnum(Window::GetStyle());
	}

	static bool WindowResize(Point size, bool centering)
	{
		return Window::Resize(size, Centering{ centering });
	}

	static bool WindowResize2(int32 w, int32 h, bool centering)
	{
		return Window::Resize(w, h, Centering{ centering });
	}

	static bool WindowResizeVirtual(Point size, bool centering)
	{
		return Window::ResizeVirtual(size, Centering{ centering });
	}

	static bool WindowResizeVirtual2(int32 w, int32 h, bool centering)
	{
		return Window::ResizeVirtual(w, h, Centering{ centering });
	}

	static bool WindowResizeActual(Point size, bool centering)
	{
		return Window::ResizeActual(size, Centering{ centering });
	}

	static bool WindowResizeActual2(int32 w, int32 h, bool centering)
	{
		return Window::ResizeActual(w, h, Centering{ centering });
	}

	void RegisterWindow(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Window"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const Point DefaultClientSize", (void*)&Window::DefaultClientSize); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetTitle(const String& in)", asFUNCTIONPR(Window::SetTitle, (const String&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("const String& GetTitle()", asFUNCTION(Window::GetTitle), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetStyle(WindowStyle)", asFUNCTION(WindowSetStyle), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("WindowStyle GetStyle()", asFUNCTION(WindowGetStyle), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetPos(const Point& in)", asFUNCTIONPR(Window::SetPos, (Point), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetPos(int32, int32)", asFUNCTIONPR(Window::SetPos, (int32, int32), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point GetPos()", asFUNCTION(Window::GetPos), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void Centering()", asFUNCTION(Window::Centering), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Maximize()", asFUNCTION(Window::Maximize), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Restore()", asFUNCTION(Window::Restore), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Minimize()", asFUNCTION(Window::Minimize), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("bool Resize(Point, bool centering = Centering::Yes)", asFUNCTION(WindowResize), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool Resize(int32, int32, bool centering = Centering::Yes)", asFUNCTION(WindowResize2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool ResizeVirtual(Point, bool centering = Centering::Yes)", asFUNCTION(WindowResizeVirtual), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool ResizeVirtual(int32, int32, bool centering = Centering::Yes)", asFUNCTION(WindowResizeVirtual2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("bool ResizeActual(Point, bool centering = Centering::Yes)", asFUNCTION(WindowResizeActual), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool ResizeActual(int32, int32, bool centering = Centering::Yes)", asFUNCTION(WindowResizeActual2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetMinimumFrameBufferSize(Point)", asFUNCTION(Window::SetMinimumFrameBufferSize), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetFullscreen(bool, size_t monitorIndex = System::GetCurrentMonitorIndex())", asFUNCTION(Window::SetFullscreen), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetToggleFullscreenEnabled(bool enabled)", asFUNCTION(Window::SetToggleFullscreenEnabled), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool IsToggleFullscreenEnabled()", asFUNCTION(Window::IsToggleFullscreenEnabled), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
