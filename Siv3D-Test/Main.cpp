
# include <Siv3D.hpp>

void Main()
{
	Print << FileSystem::SpecialFolderPath(SpecialFolder::SystemFonts);
	Print << FileSystem::SpecialFolderPath(SpecialFolder::LocalFonts);
	Print << FileSystem::SpecialFolderPath(SpecialFolder::UserFonts);
	
	/*
	const Font font1(45, FileSystem::SpecialFolderPath(SpecialFolder::SystemFonts) + U"ヒラギノ角ゴシック W5.ttc");
	const Font font2(45, FileSystem::SpecialFolderPath(SpecialFolder::SystemFonts) + U"Helvetica.dfont");
	const Font font3(45, FileSystem::SpecialFolderPath(SpecialFolder::UserFonts) + U"SourceCodePro-Regular.ttf");
	*/
	
	while (System::Update())
	{
		/*
		font1(U"ヒラギノ角ゴシック W5").draw(20, 40);
		
		font2(U"Helvetica").draw(20, 140);
		
		font3(U"SourceCodePro-Regular").draw(20, 230);
		 */
	}
}
