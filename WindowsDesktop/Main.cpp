
# define SIV3D_CONCURRENT
# include <Siv3D.hpp>

void Main()
{
	Range(0, 15).parallel_each([](auto i)
	{
		Print << U"{}: {}"_fmt(std::this_thread::get_id(), i);
	});

	while (System::Update())
	{

	}
}
