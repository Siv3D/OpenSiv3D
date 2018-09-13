
# include <Siv3D.hpp>

void Main()
{
	const Array<int32> languageCodes =
	{
		{ LanguageCode::EnglishUS },
		{ LanguageCode::ChineseCN },
		{ LanguageCode::FrenchFR },
		{ LanguageCode::GermanDE },
		{ LanguageCode::ItalianIT },
		{ LanguageCode::Japanese },
		{ LanguageCode::Korean },
		{ LanguageCode::SpanishES }
	};

	Array<String> languageOptions = 
	{
		U"en_US", U"zh_CN", U"fr_FR", U"de_DE ", U"it_IT", U"ja", U"ko", U"es_ES"
	};

	for (auto i : step(languageCodes.size()))
	{
		languageOptions[i] += TextToSpeech::HasLanguage(languageCodes[i]) ? U"" : U" (not available)";
	}

	const Font font(17, Typeface::Medium /*U"NotoSansCJKjp-Regular.otf"*/);
	const String s1 = U"アメリカとの関係悪化を背景に通貨リラが大きく値下がりしているトルコで、13日、中央銀行が金融政策を決める会合を開き、主な政策金利を現在の17.75％から大幅に引き上げ、24％とすることを決めました。決定を受けて通貨リラは値上がりしています。";
	const String s2 = U"A year after presiding over a sluggish and chaotic response to a devastating storm in Puerto Rico, the Trump administration girded on Wednesday for a test of its ability to do better as Hurricane Florence continued to bear down on the Carolina coast.";
	const String s3 = U"长城，是古代中国为抵御不同时期塞北游牧部落联盟的侵袭，修筑规模浩大的隔離牆或军事工程的统称。长城东西绵延上万华里，因此又称作万里长城。现存的长城遗蹟主要为始建于14世纪的明长城，西起嘉峪關，東至虎山長城，长城遗址跨越北京、天津、青海、山西、内蒙等15个省市自治区，总计有43721处长城遗产，长城也是自人类文明以来最巨大的单一建筑物。";
	const String s4 = U"Fruit d'une histoire politique longue et mouvementée, la France est une république constitutionnelle unitaire ayant un régime semi-présidentiel. La devise de la République est depuis 1875 « Liberté, Égalité, Fraternité » et son drapeau est constitué des trois couleurs nationales (bleu, blanc, rouge) disposées en trois bandes verticales d'égale largeur.";

	String exampleText;
	TextEditState textEdit;
	double volume = 1.0;
	double speed = 1.0;
	size_t languageIndex = 5;

	while (System::Update())
	{
		const int32 languageCode = languageCodes[languageIndex];
		const bool isSpeaking = TextToSpeech::IsSpeaking();

		if (SimpleGUI::Button(U"1", Vec2(20, 20), 40))
		{
			exampleText = s1;
			TextToSpeech::Speak(exampleText, languageCode);
			textEdit.clear();
		}

		if (SimpleGUI::Button(U"2", Vec2(80, 20), 40))
		{
			exampleText = s2;
			TextToSpeech::Speak(exampleText, languageCode);
			textEdit.clear();
		}

		if (SimpleGUI::Button(U"3", Vec2(140, 20), 40))
		{
			exampleText = s3;
			TextToSpeech::Speak(exampleText, languageCode);
			textEdit.clear();
		}

		if (SimpleGUI::Button(U"4", Vec2(200, 20), 40))
		{
			exampleText = s4;
			TextToSpeech::Speak(exampleText, languageCode);
			textEdit.clear();
		}

		font(exampleText).draw(Rect(20, 70, 760, 120).stretched(-2).draw().stretched(-4), ColorF(0.25));

		if (SimpleGUI::TextBox(textEdit, Vec2(20, 200), 300))
		{
			exampleText.clear();
		}

		if (SimpleGUI::Button(U"Speak!", Vec2(340, 200)))
		{
			TextToSpeech::Speak(textEdit.text, languageCode);
		}

		if (SimpleGUI::Slider(U"Volume:{:.2f}"_fmt(volume), volume, 0.0, 1.0, Vec2(20, 250), 150))
		{
			TextToSpeech::SetVolume(volume);
		}

		if (SimpleGUI::Slider(U"Speed:{:.2f}"_fmt(speed), speed, 0.0, 2.0, Vec2(20, 300), 150))
		{
			TextToSpeech::SetSpeed(speed);
		}

		if (isSpeaking)
		{
			if (SimpleGUI::Button(U"Pause", Vec2(20, 350)))
			{
				TextToSpeech::Pause();
			}
		}
		else
		{
			if (SimpleGUI::Button(U"Resume", Vec2(20, 350)))
			{
				TextToSpeech::Resume();
			}
		}

		SimpleGUI::RadioButtons(languageIndex, languageOptions, Vec2(340, 250));

		RectF(Arg::center(180, 480), 50 + 12 * Periodic::Sine0_1(2.4s))
			.rotated(Time::GetMillisec() * 0.08_deg).draw(HSV(Time::GetMillisec() * 0.01, 0.4, 1.0));
	}
}
