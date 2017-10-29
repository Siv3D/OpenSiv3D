
# include <Siv3D.hpp>

void Main()
{
	const Array<int32> v = { 10,20,30 };

	auto v2 = v.map(Format(_, U"m"));

	v2.size();

	size_t s = v.count_if(_ == 50);

	s;
}
