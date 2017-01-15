
# include <Siv3D.hpp>

void Main()
{
	INIReader ini(L"example/test.ini");

	for (const auto& key : ini.getData())
	{
		Log << key.first << L"." << key.second.name << L"=" << key.second.value;
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
