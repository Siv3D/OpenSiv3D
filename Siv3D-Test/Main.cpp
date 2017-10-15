
# include <Siv3D.hpp>

void Main()
{
	String text = U"Siv3D あいうえお　漢字𩸽abc";

	Unicode::Translator_UTF32toUTF8 translator;

	std::string utf8Text;

	for (const auto ch : text)
	{
		utf8Text.append(translator.begin(), translator.begin() + translator.put(ch));
	}

	String text2 = Unicode::FromUTF8(utf8Text);
}
