
# include <Siv3D.hpp>

void Main()
{
	Font font(40);
	
	while (System::Update())
	{
		font(U"㈱12345凾").draw();
	}
}
