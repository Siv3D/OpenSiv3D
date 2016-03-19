
# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>

void Main();

int WINAPI wWinMain(HINSTANCE, HINSTANCE, wchar_t*, int)
{
	Main();
}
