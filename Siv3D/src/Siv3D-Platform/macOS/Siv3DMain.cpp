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
		
			void SetInitialPath(const FilePath& path);
		}
	
		FilePath ParentPath(FilePath path, size_t n)
		{
			if (path.count(U'/') <= n)
			{
				return FilePath(U"NN");
			}

			while (path)
			{
				if (path.back() == U'/')
				{
					if (n == 0)
					{
						break;
					}
					
					--n;
				}
				
				path.pop_back();
			}
			
			return path;
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

		FilePath modulePath = detail::ParentPath(path, 2);

		if (modulePath.ends_with(U'/'))
		{
			modulePath.pop_back();
		}
		
		const FilePath currentDirectory = detail::ParentPath(path, 3);
		
		detail::init::SetInitialPath(currentDirectory);
		
		detail::init::SetModulePath(modulePath);
				
		::chdir(currentDirectory.narrow().c_str());

		return true;
	}
}

int main(int, char*[])
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
	
	//Logger.writeRawHTML_UTF8("<hr width=\"99%\">");

	Main();
	
	//Logger.writeRawHTML_UTF8("<hr width=\"99%\">");
}
