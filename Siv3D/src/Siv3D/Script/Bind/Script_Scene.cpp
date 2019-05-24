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
# include <Siv3D/Scene.hpp>
# include "Script_Optional.hpp"
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterScene(asIScriptEngine *engine)
	{
		int32 r = 0;

		{
			r = engine->RegisterEnumValue("ScaleMode", "ResizeFill", static_cast<uint32>(ScaleMode::ResizeFill)); assert(r >= 0);
			r = engine->RegisterEnumValue("ScaleMode", "AspectFit", static_cast<uint32>(ScaleMode::AspectFit)); assert(r >= 0);
		}

		r = engine->SetDefaultNamespace("Scene"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const Point DefaultSceneSize", (void*)& Scene::DefaultSceneSize); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const ScaleMode DefaultScaleMode", (void*)& Scene::DefaultScaleMode); assert(r >= 0);
			//TextureFilter DefaultFilter = TextureFilter::Linear;
			r = engine->RegisterGlobalProperty("const ColorF DefaultBackgroundColor", (void*)& Scene::DefaultBackgroundColor); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const ColorF DefaultLetterBoxColor", (void*)& Scene::DefaultLetterBoxColor); assert(r >= 0);
			r = engine->RegisterGlobalProperty("double DefaultMaxDeltaTime", (void*)& Scene::DefaultMaxDeltaTime); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void Resize(const Point& in)", asFUNCTIONPR(Scene::Resize, (const Size&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void Resize(int32, int32)", asFUNCTIONPR(Scene::Resize, (int32, int32), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Size()", asFUNCTION(Scene::Size), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Width()", asFUNCTION(Scene::Width), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 Height()", asFUNCTION(Scene::Height), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point Center()", asFUNCTION(Scene::Center), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 CenterF()", asFUNCTION(Scene::CenterF), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Rect Rect()", asFUNCTION(Scene::Rect), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("void SetScaleMode(ScaleMode)", asFUNCTION(Scene::SetScaleMode), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("ScaleMode GetScaleMode()", asFUNCTION(Scene::GetScaleMode), asCALL_CDECL); assert(r >= 0);
			
			//void SetTextureFilter(TextureFilter textureFilter);
			//TextureFilter GetTextureFilter();

			r = engine->RegisterGlobalFunction("void SetBackground(const ColorF& in)", asFUNCTION(Scene::SetBackground), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void SetLetterbox(const ColorF& in)", asFUNCTION(Scene::SetLetterbox), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("void SetMaxDeltaTime(double)", asFUNCTION(Scene::SetMaxDeltaTime), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double GetMaxDeltaTime()", asFUNCTION(Scene::GetMaxDeltaTime), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double DeltaTime()", asFUNCTION(Scene::DeltaTime), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Time()", asFUNCTION(Scene::Time), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int32 FrameCount()", asFUNCTION(Scene::FrameCount), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 ClientToScene(const Vec2& in)", asFUNCTION(Scene::ClientToScene), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
