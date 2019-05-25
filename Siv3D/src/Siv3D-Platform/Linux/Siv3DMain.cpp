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

# include <iostream>
# include <unistd.h>
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
}

int main(int, char* argv[])
{
	using namespace s3d;

	std::cout << "Siv3D for Linux\n";

	const FilePath path = Unicode::Widen(argv[0]);
	FilePath modulePath = FileSystem::ParentPath(path, 0);

	if (modulePath.ends_with(U'/'))
	{
		modulePath.pop_back();
	}

	detail::init::SetModulePath(modulePath);

	chdir(FileSystem::ParentPath(path, 0).narrow().c_str());

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
