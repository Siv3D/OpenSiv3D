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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Version.hpp>
# include "CacheDirectory.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static String GetUniqueID(const StringView applicationName)
		{
			if (const auto name = String{ applicationName }.removed_if([](char32 c)
				{
					return (c == U'\\')
						|| (c == U'/')
						|| (c == U',')
						|| (c == U'.')
						|| (c == U';')
						|| (c == U':')
						|| (c == U'*')
						|| (c == U'?')
						|| (c == U'\"')
						|| (c == U'<')
						|| (c == U'>')
						|| (c == U'|');
				}))
			{
				return name;
			}
			else
			{
				return Format(U"{:0>16X}"_fmt(applicationName.hash()));
			}
		}
	}

	namespace CacheDirectory
	{
		FilePath Engine()
		{
			return FileSystem::GetFolderPath(SpecialFolder::LocalAppData)
				+ U"Siv3D/" SIV3D_VERSION_STRING U"/";
		}

		FilePath Apps(const StringView applicationName)
		{
			return FileSystem::GetFolderPath(SpecialFolder::LocalAppData)
				+ U"Siv3DApps/" + detail::GetUniqueID(applicationName) + U"/";
		}
	}
}
