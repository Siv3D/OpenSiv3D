
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

bool Test(int32 min, int32 max)
{
	const size_t size = Random(min, max);
	Array<uint8> input(size);
	const int32 target = Random(0, 255);
	for (auto& in : input)
	{
		in = static_cast<uint8>(Random(0, target));
	}

	const auto compressed = Zlib::Compress(input);

	const auto decompressed = Zlib::Decompress(compressed);

	Array<uint8> output(decompressed.size());

	std::memcpy(output.data(), decompressed.data(), output.size_bytes());

	const bool result = (input == output);
	Logger << U"{} -> {} ({})"_fmt(input.size(), compressed.size(), result);

	return result;
}

bool TestSmall()
{
	return Test(0, 200);
}

bool TestLarge()
{
	return Test(4 * 1024, 256 * 1024);
}

void Main()
{
	int32 n = 0;

	while (System::Update())
	{
		if (!TestSmall())
		{
			Print << U"Fail S";
		}

		if (!TestLarge())
		{
			Print << U"Fail L";
		}

		if (++n % 100 == 0)
		{
			Print << n;
		}
	}
}
