# include <Siv3D.hpp>
# include <emscripten/bind.h>

static MessageBoxResult result;

uint32 GetResult()
{
    return FromEnum(result);
}

static void WaitForFrames(uint32 frames)
{
	for (auto _ : step(frames)) 
	{
		System::Update();
	}
}

void Main()
{
	Scene::SetResizeMode(ResizeMode::Keep);

	WaitForFrames(60);
	result = System::MessageBoxOK(U"Normal MessageBox");

	WaitForFrames(300);  
	result = System::MessageBoxOKCancel(U"OK or Cancel MessageBox");

	WaitForFrames(300);
	result = System::MessageBoxOKCancel(U"OK or Cancel MessageBox");

	WaitForFrames(1000);
}

EMSCRIPTEN_BINDINGS(Bindings) {
    using namespace emscripten;

    function("GetResult", &GetResult);
}
