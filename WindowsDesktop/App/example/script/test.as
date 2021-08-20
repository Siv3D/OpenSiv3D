
int Double(int n)
{
	return (n * 2);
}

int Add(int a, int b)
{
	return a + b;
}

double Add(double a, double b)
{
	return a + b;
}

String Hello()
{
	Array<String> texts = { "ABC", "DEF", "あいう" };

	String a = "AあA";
	String b = "いAうA🐱";

	return texts[0] + texts[1] + texts[2];
}

void ShowColor(const Color& in color)
{
	Print << color;
}

void ShowColorF(const ColorF& in color)
{
	Print << color;
}

void TestOptional(const Optional<double>& v)
{
	if (v)
		Print << v.value();
	else
		Print << "none";
}

void TestOptional(None_t)
{
	Print << "none";
}

void TestOptional(double v)
{
	Print << v;
}

int32 Test()
{
	Optional<int32> n = 200;

	Print << n;

	Print << "Siv3D";

	Print << 10 << 20 << 30;

	Optional<double> od;

	Print << od;

	Print << Date::Today();

	Print << DateTime::Now();

	Print << (Date::Today() == Date::Today());
	Print << (DateTime::Now() == DateTime::Now());
	Print << StartImmediately::Yes;

	Stopwatch stopwatch;
	Print << "---";
	Print << (stopwatch == Duration(0)); 
	Print << (stopwatch < Duration(1)); 
	Print << (stopwatch > Duration(-1)); 
	Print << (stopwatch < Duration(-1)); 
	Print << (stopwatch > Duration(1)); 

	Color color(11,22,33);
	ColorF colorF(0.1,0.2,0.3);
	HSV hsv(120.0, 1, 1);
	Print << color;
	Print << colorF;
	ShowColorF(color);
	ShowColor(colorF);
	ShowColorF(hsv);
	ShowColor(hsv);

	Print << Date::Today().format();
	//System::ShowInFileManager("example/windmill.png");


	Print << Point::Up() + Point::Right();

	Vec2 v = Point::Up();
	Print << v;

	v = Point::Right();
	Print << v;

	String s = "Siv3D";

	s[0] = 'T';
	s[1] = s[2];
	s[3] = 'あ';

	for (size_t i = 0; i < s.size(); ++i)
	{
		Print << (s[i] < 'z');

		Print << (s[i] + 1) << " " << ToUpper(s[i]);
	}

	Print << FileSystem::GetFolderPath(SpecialFolder::Desktop);

	String base;
	Print << FileSystem::ParentPath("./", 2, base);
	Print << base;
	Print << _deg(180);

	Print << Duration(30);
	Print << _h(30);

	Timer timer(_s(30), StartImmediately::Yes);
	Print << timer;

	Print << Linear::Palette::DefaultBackground;
	Print << Window::GetTitle();

	String text;

	TestOptional(200.0);
	TestOptional(unspecified);

	double value = 0.5;
	size_t select = 0;
	const Array<String> options = {"AAA", "BBB"};

	LineStyle::SquareDot(0.5);

	LineString ls = { Vec2(300, 300), Vec2(300, 400), Vec2(400, 400) };

	while(System::Update())
	{
		const Transformer2D t(Mat3x2::Scale(0.25), TransformCursor::Yes);

		ls.draw(LineStyle::RoundCap, 20);

		if (MouseL.down())
		{
			ls << Cursor::Pos();
		}

		SimpleGUI::Headline("Head", Vec2(20, 50), 200);
		SimpleGUI::Slider(value, Vec2(20, 90));
		SimpleGUI::HorizontalRadioButtons(select, {"AAA", "BBB"}, Vec2(20, 130));

		Arg::topLeft = Vec2(30,30);

		PutText("Hello", Cursor::Pos());
		PutText(timer.format(), 100, 20);
		PutText(timer.format(), Arg::topLeft(100, 80));
		PutText(timer.format(), Arg::center(100, 80));

		const Array<Input> inputs = Keyboard::GetAllInputs();

		for (size_t i = 0; i < inputs.size(); ++i)
		{
			Print << inputs[i].name();
		}
	}

	return n.value();
}
