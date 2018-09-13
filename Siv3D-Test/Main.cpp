
# include <Siv3D.hpp>

void Main()
{
	//const ManagedScript script(U"example/script.txt");

	TextToSpeech::SetDefaultLanguage(SpeechLanguage::Japanese);

	while (System::Update())
	{
		ClearPrint();

		Print << TextToSpeech::IsSpeaking();

		if (Key1.down())
		{
			TextToSpeech::Speak(U"あいうえお");
		}

		if (Key2.down())
		{
			TextToSpeech::Speak(U"Apple Unveils Bigger iPhones at Higher Prices, and a Heart-Tracking Watch");
		}

		if (Key3.down())
		{
			TextToSpeech::Speak(U"成田空港は、滑走路の近くで不発弾のようなものが見つかったため、２本ある滑走路のうちの１本を閉鎖していましたが、現場での撤去が終わり、午前８時20分に運用を再開しました。見つかったのはいわゆる「成田闘争」で反対派が使っていた「飛翔弾」とみられ、警察が確認を進めています。");
		}

		if (Key4.down())
		{
			TextToSpeech::Speak(U"A year after presiding over a sluggish and chaotic response to a devastating storm in Puerto Rico, the Trump administration girded on Wednesday for a test of its ability to do better as Hurricane Florence continued to bear down on the Carolina coast.");
		}

		if (KeyA.down())
		{
			TextToSpeech::Pause();
		}

		if (KeyB.down())
		{
			TextToSpeech::Resume();
		}

		Rect(Arg::center = Window::Center(), 40).rotated(Time::GetMillisec() * 0.1_deg).draw();

		//script.run();
	}
}
