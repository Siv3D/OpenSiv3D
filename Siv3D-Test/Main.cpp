
# include <Siv3D.hpp>

void Main()
{
	const Image image(L"example/windmill.png");

	auto task = CreateConcurrentTask([&]()
	{
		Range(4, 20).map(Multiplies(0.1)).asArray().parallel_each([&](double t)
		{
			image.savePerceptualJPEG(L"b{}.jpg"_fmt(t), t);
		});
	});

	while (System::Update())
	{
		Window::SetTitle(L"変換中 ", String(9, L'□').insert(Time::GetMillisec() / 200 % 10, 1, L'■'));

		if (task.is_done())
		{
			break;
		}
	}
}

