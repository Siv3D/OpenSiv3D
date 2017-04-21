
# include <Siv3D.hpp>

void Main()
{
	const JSONReader json(L"example/test.json");

	if (!json)
	{
		return;
	}

	Log << L"---------";

	for (const auto& object : json.objectView())
	{
		Log << object.name;
	}

	Log << L"---------";

	for (const auto& member : json[L"北アメリカ"][L"カナダ"][L"公用語"].arrayView())
	{
		Log << member.getString();
	}

	Log << L"---------";

	Log << json[L"北アメリカ"][L"カナダ"][L"公用語"].arrayCount();
	Log << json[L"北アメリカ"][L"カナダ"][L"公用語"].arrayView()[1].getString();
	Log << json.isObject();
	Log << json[L"アジア"].isObject();
	Log << json[L"アジア"][L"日本"][L"面積"].getOpt<int32>();
	Log << json[L"アジア"][L"日本"][L"首都"].getString();
	Log << json[L"a"][L"日本"][L"面積"].getOpt<int32>();

	Log << L"---------";

	Log << json[L"アジア"][L"日本"][L"面積"].get<int32>();
	Log << json[L"アジア.日本.面積"].get<int32>();
	Log << json[L"アジア.日本.面積"].getOpt<int32>();
	Log << json[L"アジア.日本.面積"].getOr<int32>(-1);
	Log << json[L"アジア.hoge.foo"].getOpt<int32>();
	Log << json[L"アジア.hoge.foo"].getOr<int32>(-1);

	Log << L"---------";

	for (const auto& language : json[L"北アメリカ.カナダ.公用語"].arrayView())
	{
		Log << language.get<String>();
	}

	Log << L"---------";

	for (const auto& o : json[L"アジア"].objectView())
	{
		Log << o.name << L"の首都は" << o.value[L"首都"].get<String>();
	}

	while (System::Update())
	{

	}
}

/*
void Main()
{
	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS());

		if (KeyR.down())
		{
			Window::Resize(1280, 720);
		}
		
		for (auto p : step({10,10}))
		{
			Rect(p*20,18).draw(HSV(10*(p.x+p.y)));
		}

		Rect(100, 50, 80).draw({Palette::Orange, Palette::Orange, Palette::White, Palette::White});

		Rect(200, 50, 80).draw(Arg::left = Palette::Orange, Arg::right = Palette::White);

		Rect(400, 100, 100, 80).shearedX(40).draw(Palette::Yellow);

		Rect(Arg::center(320, 240), 160, 40).rotated(System::FrameCount() * 1_deg).draw(Palette::Seagreen);

		Triangle(Window::Center(), 80).draw(Palette::Orange);
		
		Rect(80, 160, 200).draw(Color(255, 127));

		Rect(300, 300, 200, 100).drawFrame(4);
	}
}
*/
