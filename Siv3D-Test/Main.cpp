
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	//RunTest();

	for (const auto& monitor : System::EnumMonitors())
	{
		Log << L"-------";
		Log << monitor.id;
		Log << monitor.name;
		Log << monitor.isPrimary;
		Log << monitor.displayRect;
		Log << monitor.workArea;
	}

	while (System::Update())
	{

	}
}
