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

# include <unistd.h>
# include <mach-o/dyld.h>
# include <iostream>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineMessageBox.hpp>
# include <System/ISystem.hpp>
# include <Siv3DEngine.hpp>

void Main();

namespace s3d
{
	namespace detail
	{
		namespace init
		{
			void SetModulePath(const FilePath& path);
		}
	}
	
	static bool InitPath()
	{
		char path_str[4096];
		uint32_t bufferSize = sizeof(path_str);
		
		if (_NSGetExecutablePath(path_str, &bufferSize) != 0)
		{
			return false;
		}
		
		const String path = Unicode::Widen(path_str);
		
		FilePath modulePath = FileSystem::ParentPath(path, 2);
		
		if (modulePath.ends_with(U'/'))
		{
			modulePath.pop_back();
		}

		detail::init::SetModulePath(modulePath);
		
		::chdir(FileSystem::ParentPath(path, 3).narrow().c_str());
		
		return true;
	}
}

int main()
{
	using namespace s3d;
	
	std::cout << "Siv3D for macOS\n";
	
	if (!InitPath())
	{
		return -1;
	}
	
	Siv3DEngine engine;
	
	try
	{
		Siv3DEngine::Get<ISiv3DSystem>()->init();
	}
	catch (const EngineError& error)
	{
		const String text = U"EngineError: {}"_fmt(error.what());
		LOG_ERROR(text);
		EngineMessageBox::Show(text);
		return -1;
	}
	
	//Logger.writeRawHTML_UTF8(u8"<hr width=\"99%\">");

	Main();
	
	//Logger.writeRawHTML_UTF8(u8"<hr width=\"99%\">");
}
