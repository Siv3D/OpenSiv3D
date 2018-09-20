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
# include <Siv3D/Graphics.hpp>
# include "Script_Optional.hpp"
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void SetTargetFrameRateHz(const CScriptOptional& targetFrameRateHz)
	{
		if (targetFrameRateHz.HasValue())
		{
			Graphics::SetTargetFrameRateHz(*static_cast<const double*>(targetFrameRateHz.At()));
		}
		else
		{
			Graphics::SetTargetFrameRateHz(none);
		}
	}

	void SetTargetFrameRateHzNone(uint8)
	{
		Graphics::SetTargetFrameRateHz(none);
	}

	static CScriptOptional GetTargetFrameRateHz()
	{
		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Optional<double>");

		if (const auto result = Graphics::GetTargetFrameRateHz())
		{
			double value = result.value();

			return CScriptOptional(&value, typeID);
		}
		else
		{
			return CScriptOptional(typeID);
		}
	}

	void RegisterGraphics(asIScriptEngine *engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("Graphics"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("void SetBackground(const ColorF& in)", asFUNCTION(Graphics::SetBackground), asCALL_CDECL); assert(r >= 0);
			//[[nodiscard]] Array<DisplayOutput> EnumOutputs();
			engine->RegisterGlobalFunction("void SetBackground(bool fullScreen, const Point& size, uint32 displayIndex = 0, double refreshRateHz = 60.0)", asFUNCTION(Graphics::SetFullScreen), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetTargetFrameRateHz(const Optional<double>& in targetFrameRateHz)", asFUNCTION(SetTargetFrameRateHz), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("void SetTargetFrameRateHz(None_t)", asFUNCTION(SetTargetFrameRateHzNone), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Optional<double> GetTargetFrameRateHz()", asFUNCTION(GetTargetFrameRateHz), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("double GetDisplayRefreshRateHz()", asFUNCTION(Graphics::GetDisplayRefreshRateHz), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
