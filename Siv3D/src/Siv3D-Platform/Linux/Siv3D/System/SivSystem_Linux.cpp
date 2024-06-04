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

# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>
# include <pwd.h>
# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static bool Run(const char* program, char* argv[])
		{
			sigset_t set, oldset;
			sigemptyset(&set);
			sigaddset(&set, SIGCHLD);
			sigprocmask(SIG_BLOCK, &set, &oldset);

			pid_t pid;
			if (pid = fork(); pid == 0)
			{
				if (not fork())
				{
					close(0);
					open("/dev/null", O_RDONLY);
					close(1);
					open("/dev/null", O_WRONLY);
					close(2);
					open("/dev/null", O_WRONLY);

					setsid();

					execv(program, argv);
					_exit(0);
				}
				else
				{
					_exit(0);
				}
			}
			else if (pid < 0)
			{
				sigprocmask(SIG_SETMASK, &oldset, 0);
				return false;
			}

			int status = 0;
			while (waitpid(pid, &status, 0) < 0)
			{
				if (errno != EINTR)
				{
					sigprocmask(SIG_SETMASK, &oldset, 0);
					return false;
				}
			}

			sigprocmask(SIG_SETMASK, &oldset, 0);
			return true;
		}	
	}

	namespace System
	{
		bool LaunchBrowser(const FilePathView _url)
		{
			String url{ _url };
			const bool isWebPage = url.starts_with(U"http://")
				|| url.starts_with(U"https://");

			if (not isWebPage)
			{
				if (not FileSystem::IsFile(_url))
				{
					return false;
				}

				const String extension = FileSystem::Extension(_url);
				const bool isHTML = (extension == U"html") || (extension == U"htm");

				if (not isHTML)
				{
					return false;
				}

				url = FileSystem::FullPath(_url);
			}

			std::string urlc = url.toUTF8();
			char* argv[] = { (char*)"xdg-open", urlc.data(), nullptr };
			return detail::Run("/usr/bin/xdg-open", argv);
		}

		bool ShowInFileManager(const FilePathView path)
		{
			if (not FileSystem::Exists(path))
			{
				return false;
			}

			std::string pathc = path.toUTF8();
			char* argv[] = { (char*)"nautilus", pathc.data(), nullptr };
			return detail::Run("/usr/bin/nautilus", argv);
		}

		String ComputerName()
		{
			char name[256];
			
			if (gethostname(name, sizeof(name)) == 0)
			{
				return Unicode::Widen(name);
			}
			else
			{
				return{};
			}
		}

		String UserName()
		{
			if (const char* username = std::getenv("USER"))
			{
				return Unicode::Widen(username);
			}
			else if (const char* username = std::getenv("USERNAME"))
			{
				return Unicode::Widen(username);
			}
			else if (const char* username = std::getenv("LOGNAME"))
			{
				return Unicode::Widen(username);
			}
			else if (const passwd* pw = getpwuid(getuid()))
			{
				return Unicode::Widen(pw->pw_name);
			}
			else
			{
				return{};
			}
		}

		String FullUserName()
		{
			if (const passwd* pw = getpwuid(getuid()))
			{
				std::string gecos = pw->pw_gecos;

				if (const size_t pos = gecos.find_first_of(',');
					pos != std::string::npos)
				{
					gecos.resize(pos);
				}

				return Unicode::Widen(gecos);
			}
			else
			{
				return{};
			}
		}

		String DefaultLocale()
		{
			if (const char* locale = setlocale(LC_ALL, ""))
			{
				return Unicode::Widen(locale).replace(U'_', U'-');
			}
			else
			{
				return U"en-US";
			}
		}

		String DefaultLanguage()
		{
			if (const char* language = std::getenv("LANG"))
			{
				return Unicode::Widen(language).replace(U'_', U'-');
			}
			else
			{
				return U"en-US";
			}
		}

		bool LaunchFile(const FilePathView fileName)
		{
			const std::string command = ("xdg-open '" + fileName.narrow() + "'");

			return (std::system(command.c_str()) == 0);
		}

		bool LaunchFileWithTextEditor(const FilePathView fileName)
		{
			const char* editor = std::getenv("VISUAL");

			if (editor == nullptr)
			{
				editor = std::getenv("EDITOR");

				if (editor == nullptr)
				{
					// gedit is the default text editor in Ubuntu
					if (std::system("which gedit >/dev/null 2>&1") == 0)
					{
						editor = "gedit";
					}
					else
					{
						editor = "vi";
					}
				}
			}

			const std::string command = (std::string(editor) + " '" + fileName.narrow() + "'");

			return (std::system(command.c_str()) == 0);
		}

		bool IsRunningInVisualStudio()
		{
			return false;
		}

		bool IsRunningInXcode()
		{
			return false;
		}
	}
}
