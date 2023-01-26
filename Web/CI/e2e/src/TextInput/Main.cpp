# include <Siv3D.hpp>
# include <emscripten/emscripten.h>

static String Text;

typedef char __attribute__((address_space(10)))* externref;

EM_JS(externref, UTF8ToJsString, (const char* text), {
 	return UTF8ToString(text);
});

EMSCRIPTEN_KEEPALIVE
extern "C" externref GetResult()
{
    return UTF8ToJsString(Text.narrow().c_str());
}

void Main()
{
	Scene::SetResizeMode(ResizeMode::Keep);
	TextEditState textState;

	Platform::Web::System::DisbaleBrowserKeyboardShortcuts();
	
	while (System::Update())
	{
		if (SimpleGUI::TextBox(textState, Vec2(10, 10), 750))
		{
			Text = textState.text;
		}
    }
}
