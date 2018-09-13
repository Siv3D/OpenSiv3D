
# include <Siv3D.hpp>

void Main()
{
	TextToSpeech::SetDefaultLanguage(SpeechLanguage::Japanese);

	const Font font(17, Typeface::Medium);
	const String s1 = U"文章読み上げ";
	const String s2 = U"Hello, world!";
	const String s3 = U"成田空港は、滑走路の近くで不発弾のようなものが見つかったため、２本ある滑走路のうちの１本を閉鎖していましたが、現場での撤去が終わり、午前８時20分に運用を再開しました。見つかったのはいわゆる「成田闘争」で反対派が使っていた「飛翔弾」とみられ、警察が確認を進めています。";
	const String s4 = U"A year after presiding over a sluggish and chaotic response to a devastating storm in Puerto Rico, the Trump administration girded on Wednesday for a test of its ability to do better as Hurricane Florence continued to bear down on the Carolina coast.";

	String exampleText;
	TextEditState textEdit;
	double volume = 1.0;
	double speed = 1.0;

	while (System::Update())
	{
		const bool isSpeaking = TextToSpeech::IsSpeaking();

		if (SimpleGUI::Button(U"1", Vec2(20, 20), 40))
		{
			exampleText = s1;
			TextToSpeech::Speak(exampleText);
			textEdit.clear();
		}

		if (SimpleGUI::Button(U"2", Vec2(80, 20), 40))
		{
			exampleText = s2;
			TextToSpeech::Speak(exampleText);
			textEdit.clear();
		}

		if (SimpleGUI::Button(U"3", Vec2(140, 20), 40))
		{
			exampleText = s3;
			TextToSpeech::Speak(exampleText);
			textEdit.clear();
		}

		if (SimpleGUI::Button(U"4", Vec2(200, 20), 40))
		{
			exampleText = s4;
			TextToSpeech::Speak(exampleText);
			textEdit.clear();
		}

		font(exampleText).draw(Rect(20, 70, 760, 90).stretched(-2).draw().stretched(-4), ColorF(0.25));

		if (SimpleGUI::TextBox(textEdit, Vec2(20, 170), 300))
		{
			exampleText.clear();
		}

		if (SimpleGUI::Button(U"Speak!", Vec2(340, 170)))
		{
			TextToSpeech::Speak(textEdit.text);
		}

		if (SimpleGUI::Slider(U"Volume:{:.2f}"_fmt(volume), volume, 0.0, 1.0, Vec2(20, 220), 150))
		{
			TextToSpeech::SetVolume(volume);
		}

		if (SimpleGUI::Slider(U"Speed:{:.2f}"_fmt(speed), speed, 0.0, 2.0, Vec2(20, 270), 150))
		{
			TextToSpeech::SetSpeed(speed);
		}

		if (isSpeaking)
		{
			if (SimpleGUI::Button(U"Pause", Vec2(20, 320)))
			{
				TextToSpeech::Pause();
			}
		}
		else
		{
			if (SimpleGUI::Button(U"Resume", Vec2(20, 320)))
			{
				TextToSpeech::Resume();
			}
		}
		
		Rect(Arg::center(400, 400), 50 + 12 * Periodic::Sine0_1(2.4s))
			.rotated(Time::GetMillisec() * 0.08_deg).draw(HSV(Time::GetMillisec() * 0.01, 0.4, 1.0));
	}
}
