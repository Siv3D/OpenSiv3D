
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	//Image image(Size(100, 100), Arg::generator = ([](Point) {return HSV(0.2, 0.5, 1.0); }));

	//Log << (int)Imaging::GetFormat(L"siv3d-kun.bmp");
	//Log << (int)Imaging::GetFormatFromFilePath(L"siv3d-kun.bmp");
	//Log << Imaging::GetSize(L"siv3d-kun.bmp");
	
	while (System::Update())
	{

	}
}




/*
//TextReader reader(L"test/text/cp932.txt");
TextReader reader(L"test/text/UTF8.txt");
//TextReader reader(L"test/text/UTF16LE_BOM.txt");
//TextReader reader(L"test/text/hokke.txt");

//Console << reader.isOpened();
//Console << reader.readAll();
//std::wifstream wifs("test/text/cp932.txt");

TextWriter writer(L"out.txt");

String line;// = reader.readAll();

char32_t ch;

while (reader.readChar(ch))
{
	Console << ch;
	//Console << line.length();
	//Console << (int)ch.value();
	//writer.writeln(ch);
	}
	
	while (System::Update())
	{
		
	}
	*/
	/*
	 while (System::Update())
	 {
		if (const auto dragOver = DragDrop::DragOver())
		{
	 Window::SetTitle(L"");
		}
	 
		if (DragDrop::HasNewFilePaths())
		{
	 for (const auto& drop : DragDrop::GetDroppedFilePaths())
	 {
	 if (!FileSystem::IsFile(drop.path))
	 {
	 continue;
	 }
	 
	 const String output = L"[{}] < {}"_fmt(
	 Hash::MD5FromFile(drop.path),
	 FileSystem::FileName(drop.path));
	 
	 Window::SetTitle(output);
	 
	 Console << output;
	 }
		}
	 }
	 */


/*
	const INIReader ini(L"example/test.ini");

	// すべてのデータを列挙
	for (const auto& key : ini)
	{
		Log << key.section << L"." << key.name << L"=" << key.value;
	}

	// Section を列挙
	for (const auto& section : ini.sections())
	{
		Log << section;
	}

	// 指定した Section のキーを列挙
	for (const auto& key : ini[L"Window"])
	{
		Log << key.name << L"=" << key.value;
	}

	// 指定した Section が存在するか調べる
	Log << ini.hasSection(L"Window");

	// 指定した Section と Name が存在するか調べる
	Log << ini.hasKey(L"Window.width");

	int32 a = ini.get<int32>(L"Window.width");
	int32 b = ini.getOr<int32>(L"Window.aaa", 640);
	Optional<int32> c = ini.getOpt<int32>(L"Window.aaa");
*/