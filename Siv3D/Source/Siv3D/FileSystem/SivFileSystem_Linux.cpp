#include <glib-2.0/glib.h>
#include <stdlib.h>
#include <string>

#include "Siv3D/FileSystem.hpp"

using namespace s3d;

std::string specialFolder(const int folder)
{
	const GUserDirectory folders[] = {
		G_USER_DIRECTORY_DESKTOP,
		G_USER_DIRECTORY_DOCUMENTS,
		G_USER_DIRECTORY_DOCUMENTS, //dummy
		G_USER_DIRECTORY_PICTURES,
		G_USER_DIRECTORY_MUSIC,
		G_USER_DIRECTORY_VIDEOS
	};

	std::string sf_path = "";
	if(folder == static_cast<int>(SpecialFolder::LocalAppData))
	{
		char* xch = getenv("XDG_CACHE_HOME");
		if(xch == NULL)
		{
			sf_path = getenv("HOME");
			sf_path += "/.cache";
		}
		else
			sf_path = xch;
	}
	else
		sf_path = g_get_user_special_dir(folders[folder]);

	return sf_path;
} 

bool trashFile(const char* path)
{
	/* TODO */
	//実装する
	return false;
}

