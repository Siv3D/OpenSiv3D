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
# include <Siv3D/Dialog.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterDialog(asIScriptEngine *engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("Dialog"); assert(r >= 0);
		{
			//Optional<FilePath> OpenFile(const Array<FileFilter> & filters = {}, const FilePath & defaultPath = U"", const String & title = U"");
			//Array<FilePath> OpenFiles(const Array<FileFilter> & filters = {}, const FilePath & defaultPath = U"", const String & title = U"");
			//Optional<FilePath> SaveFile(const Array<FileFilter> & filters = {}, const FilePath & defaultPath = U"", const String & title = U"");
			//Optional<FilePath> SelectFolder(const FilePath & defaultPath = U"", const String & title = U"");

			engine->RegisterGlobalFunction("Image OpenImage(const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTION(Dialog::OpenImage), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Texture OpenTexture(const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTIONPR(Dialog::OpenTexture, (const FilePath&, const String&), Texture), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Texture OpenTexture(TextureDesc, const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTIONPR(Dialog::OpenTexture, (TextureDesc, const FilePath&, const String&), Texture), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Wave OpenWave(const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTION(Dialog::OpenWave), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("Audio OpenAudio(const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTIONPR(Dialog::OpenAudio, (const FilePath&, const String&), Audio), asCALL_CDECL); assert(r >= 0);

			//Audio OpenAudio(Arg::loop_<bool> loop, const FilePath& defaultPath = U"", const String& title = U"");

			//~~//engine->RegisterGlobalFunction("Optional<String> SaveImage(const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTION(Dialog::SaveImage), asCALL_CDECL); assert(r >= 0);
			//~~//engine->RegisterGlobalFunction("Optional<String> SaveWave(const String& in defaultPath = \"\", const String& in title = \"\")", asFUNCTION(Dialog::SaveWave), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
