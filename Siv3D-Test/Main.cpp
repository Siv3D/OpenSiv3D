
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	using s3d::Lambda::_;

	Array<double> v{ 0.0, -0.1, 0.2, -0.3 };
	
	v >> Abs(_) >> Logger;
	
	Logger << FileSystem::FullPath(U"example/windmill.png");

	Logger << FileSystem::SpecialFolderPath(SpecialFolder::Caches);
	
	while (System::Update())
	{

	}
}
