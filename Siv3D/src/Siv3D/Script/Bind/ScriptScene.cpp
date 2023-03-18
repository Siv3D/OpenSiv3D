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
# include <Siv3D/Scene.hpp>

namespace s3d
{
	using namespace AngelScript;

	static constexpr int32 DefaultResizeMode = FromEnum(Scene::DefaultResizeMode);

	static void SceneSetResizeMode(int32 resizeMode)
	{
		Scene::SetResizeMode(ToEnum<ResizeMode>(static_cast<uint8>(resizeMode)));
	}

	static int32 SceneGetResizeMode()
	{
		return FromEnum(Scene::GetResizeMode());
	}

	void RegisterScene(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Scene"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const Point DefaultSceneSize", (void*)&Scene::DefaultSceneSize); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const ResizeMode DefaultResizeMode", (void*)&DefaultResizeMode); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const ColorF DefaultBackgroundColor", (void*)&Scene::DefaultBackgroundColor); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const ColorF DefaultLetterBoxColor", (void*)&Scene::DefaultLetterBoxColor); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const double DefaultMaxDeltaTime", (void*)&Scene::DefaultMaxDeltaTime); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void Resize(Point)", asFUNCTIONPR(Scene::Resize, (Size), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Resize(int32, int32)", asFUNCTIONPR(Scene::Resize, (int32, int32), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Size()", asFUNCTION(Scene::Size), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Width()", asFUNCTION(Scene::Width), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Height()", asFUNCTION(Scene::Height), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Center()", asFUNCTION(Scene::Center), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 CenterF()", asFUNCTION(Scene::CenterF), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Rect Rect()", asFUNCTION(Scene::Rect), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetResizeMode(ResizeMode)", asFUNCTION(SceneSetResizeMode), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("ResizeMode GetResizeMode()", asFUNCTION(SceneGetResizeMode), asCALL_CDECL); assert(r >= 0);

			//SetTextureFilter
			//GetTextureFilter

			r = engine->RegisterGlobalFunction("void SetBackground(const ColorF& in)", asFUNCTION(Scene::SetBackground), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("const ColorF& GetBackground()", asFUNCTION(Scene::GetBackground), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetLetterbox(const ColorF& in)", asFUNCTION(Scene::SetLetterbox), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("const ColorF& GetLetterBox()", asFUNCTION(Scene::GetLetterBox), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetMaxDeltaTime(double)", asFUNCTION(Scene::SetMaxDeltaTime), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double GetMaxDeltaTime()", asFUNCTION(Scene::GetMaxDeltaTime), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double DeltaTime()", asFUNCTION(Scene::DeltaTime), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Time()", asFUNCTION(Scene::Time), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("int32 FrameCount()", asFUNCTION(Scene::FrameCount), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 ClientToScene(Vec2)", asFUNCTION(Scene::ClientToScene), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
