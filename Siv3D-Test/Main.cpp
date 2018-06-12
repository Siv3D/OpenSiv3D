
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	const Font font(32, Typeface::Medium);

	String text = U"史上初の米朝首脳会談が12日にシンガポールで行われるのを前に、現地では、米朝双方の代表団が非核化などをめぐって詰めの協議を行いました。";

	String previous, result;

	while (System::Update())
	{
		TextInput::UpdateText(text);

		const String current = text + TextInput::GetEditingText();

		if (current != previous)
		{
			//MillisecClock m;

			const auto morphemes = NLP::Japanese::AnalyzeMorphology(current);

			//m.print();

			Array<String> words;

			for (const auto& morpheme : morphemes)
			{
				if (morpheme)
				{
					if (morpheme.wordSubClassID)
					{
						words << U"{}({})"_fmt(morpheme.surface, morpheme.wordSubClass);
					}
					else
					{
						words << U"{}({})"_fmt(morpheme.surface, morpheme.wordClass);
					}
				}
			}

			result = words.join(U" ", U"", U"");
		}

		previous = current;

		font(current).draw(Window::ClientRect().stretched(-20));

		font(result).draw(Window::ClientRect().stretched(-20).movedBy(0, 200), Palette::Yellow);
	}
}
