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
# include <Siv3D/Dialog.hpp>

namespace s3d
{
	using namespace AngelScript;

	static Image OpenImage(const String& defaultPath, const String& title)
	{
		return Dialog::OpenImage(defaultPath, title);
	}

	static Texture OpenTexture(const String& defaultPath, const String& title)
	{
		return Dialog::OpenTexture(defaultPath, title);
	}

	static Texture OpenTextureD(int32 desc, const String& defaultPath, const String& title)
	{
		return Dialog::OpenTexture(ToEnum<TextureDesc>(static_cast<uint8>(desc)), defaultPath, title);
	}

	static Wave OpenWave(const String& defaultPath, const String& title)
	{
		return Dialog::OpenWave(defaultPath, title);
	}

	static Audio OpenAudio(const String& defaultPath, const String& title)
	{
		return Dialog::OpenAudio(defaultPath, title);
	}

	static Audio OpenAudioA(uint8, const String& defaultPath, const String& title)
	{
		return Dialog::OpenAudio(Audio::Stream, defaultPath, title);
	}

	void RegisterDialog(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Dialog"); assert(r >= 0);
		{
			//...

			engine->RegisterGlobalFunction("Image OpenImage(const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTION(OpenImage), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Texture OpenTexture(const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTION(OpenTexture), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Texture OpenTexture(TextureDesc, const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTION(OpenTextureD), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Wave OpenWave(const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTION(OpenWave), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Audio OpenAudio(const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTION(OpenAudio), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Audio OpenAudio(AudioFileStreaming, const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTION(OpenAudioA), asCALL_CDECL); assert(r >= 0);

			//...
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
