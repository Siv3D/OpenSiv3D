
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

Array<Rect> Generate()
{
	Array<Rect> rects(Random(4, 32));

	for (auto& rect : rects)
	{
		const Point pos = RandomPoint(Rect(0, 0, Scene::Size() - Size(150, 150)));
		rect.set(pos, Random(20, 150), Random(20, 150));
	}

	return rects;
}

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF(0.99));
	Array<Rect> input, output;
	Size size(0, 0);
	Point offset(0, 0);
	Stopwatch s(true);

	while (System::Update())
	{
		if (s > 1.8s)
		{
			input = Generate();
			std::tie(output, size) = RectanglePacking::Pack(input, 1024);
			offset = (Scene::Size() - size) / 2;
			for (auto& rect : output)
			{
				rect.moveBy(offset);
			}

			s.restart();
		}

		const double k = Min(s.sF() * 10, 1.0);
		const double t = Saturate(s.sF() - 0.2);
		const double e = EaseInOutExpo(t);
		Rect(offset, size).draw(ColorF(0.7, e));

		for (auto i : step(input.size()))
		{
			const auto& in = input[i];
			const auto& out = output[i];
			const Vec2 pos = in.pos.lerp(out.pos, e);
			const RectF rect(pos, out.size);
			rect.scaledAt(rect.center(), k)
				.draw(HSV(i * 25.0, 0.65, 0.9))
				.drawFrame(2, 0, ColorF(0.25));
		}
	}
}
