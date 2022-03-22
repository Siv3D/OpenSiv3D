# include <Siv3D.hpp>
# include <emscripten/bind.h>

static MessageBoxResult result;

MessageBoxResult GetResult()
{
    return result;
}

void Main()
{
	Scene::SetResizeMode(ResizeMode::Keep);
	
	System::Update();
	result = System::MessageBoxOK(U"Normal MessageBox");
    
	System::Update();
	result = System::MessageBoxOKCancel(U"OK or Cancel MessageBox");

	System::Update();
	result = System::MessageBoxOKCancel(U"OK or Cancel MessageBox");

	System::Update();
}

EMSCRIPTEN_BINDINGS(Bindings) {
    using namespace emscripten;

    function("GetResult", &GetResult);
}
