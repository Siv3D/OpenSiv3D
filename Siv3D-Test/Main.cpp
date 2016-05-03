
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;

void Main()
{
	Array<String> vs(10000);

	int i = 0;

	for (auto& s : vs)
	{
		s = Format(1.2345 * i++);
	}

	{
		auto b = Time::GetMicrosec();

		for (const auto& s : vs)
		{
			ParseFloat<double>(s);
		}

		Log(Time::GetMicrosec() - b);
	}

	{
		auto b = Time::GetMicrosec();

		for (const auto& s : vs)
		{
			::wcstod(s.data(), nullptr);
		}

		Log(Time::GetMicrosec() - b);
	}
	
	//RunTest();
}
