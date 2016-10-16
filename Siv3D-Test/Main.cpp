
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;


void Main()
{
	{
		std::unordered_map<String, uint32> m1;
		std::unordered_map<String, uint32, FNV1aHash<String>> m2;
		std::unordered_map<String, uint32, Murmur2Hash<String>> m3;

		TimeProfiler tp;

		{				tp.begin(L"A1");
			for (auto i : Range(9991000, 9999000))
			{
				m1.emplace(Format(i), i);
			}

			for (auto n : step(2))
			{


				for (auto i : Range(9991000, 9999000))
				{
					m1[Format(i)];
				}

				tp.end();
			}
		}

		{				tp.begin(L"A2");
			for (auto i : Range(9991000, 9999000))
			{
				m2.emplace(Format(i), i);
			}

			for (auto n : step(2))
			{


				for (auto i : Range(9991000, 9999000))
				{
					m2[Format(i)];
				}

				tp.end();
			}
		}

		{				tp.begin(L"A3");
			for (auto i : Range(9991000, 9999000))
			{
				m3.emplace(Format(i), i);
			}

			for (auto n : step(2))
			{


				for (auto i : Range(9991000, 9999000))
				{
					m3[Format(i)];
				}

				tp.end();
			}
		}
	}

	{
		Array<String> strings;

		for (auto i : Range(99910000, 99990000))
		{
			strings.push_back(Format(i));
		}

		TimeProfiler tp;

		for (auto i : step(100))
		{
			tp.begin(L"string FNV1a");

			for (const auto& string : strings)
			{
				Hash::FNV1a(string.data(), string.size() * sizeof(wchar_t));
			}

			tp.end();
		}

		for (auto i : step(100))
		{
			tp.begin(L"string Murmur2");

			for (const auto& string : strings)
			{
				Hash::Murmur2(string.data(), string.size() * sizeof(wchar_t));
			}

			tp.end();
		}
	}

	{
		Array<size_t> values;

		for (auto i : Range(0, 1000))
		{
			values.push_back(i);
		}

		TimeProfiler tp;

		for (auto i : step(100))
		{
			tp.begin(L"size_t FNV1a");

			for (const auto& value : values)
			{
				Hash::FNV1a(value);
			}

			tp.end();
		}

		for (auto i : step(100))
		{
			tp.begin(L"size_t Murmur2");

			for (const auto& value : values)
			{
				Hash::Murmur2(value);
			}

			tp.end();
		}

		for (auto i : step(100))
		{
			tp.begin(L"size_t std::hash");

			for (const auto& value : values)
			{
				std::hash<size_t>()(value);
			}

			tp.end();
		}
	}

	//RunTest();
}



