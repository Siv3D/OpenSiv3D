# include <Siv3D.hpp>
# include <emscripten/bind.h>

static String Text;

std::string GetText()
{
    return Text.narrow();
}

void Main()
{
	Scene::SetResizeMode(ResizeMode::Keep);
	TextEditState textState;
	
	while (System::Update())
	{
		if (SimpleGUI::TextBox(textState, Vec2(10, 10), 750))
		{
			Text = textState.text;
		}
    }
}

EMSCRIPTEN_BINDINGS(Bindings) {
    using namespace emscripten;

    function("GetText", &GetText);
}
