
# include <Siv3D.hpp>

void Main()
{
	const Array<int32> v = { 10,20,30,40,50 };
	const std::array<int32, 5> a = { 10,20,30,40,50 };
	const std::deque<int32> d = { 10,20,30,40,50 };
	const std::list<int32> l = { 10,20,30,40,50 };

	Print << Sample(v);
	Print << Sample(v.begin(), v.end());
	Print << Sample(a);
	Print << Sample(d);
	Print << Sample(l);
	Print << Sample({ 10,20,30,40,50 });

	Print << Sample(3, v);
	Print << Sample(3, v.begin(), v.end());
	Print << Sample(3, a);
	Print << Sample(3, d);
	Print << Sample(3, l);
	Print << Sample(3, { 10,20,30,40,50 });

	const DiscreteDistribution<> dist({ 80, 40, 20, 10, 1 });

	Print << DiscreteSample(v, dist);
	Print << DiscreteSample(v.begin(), v.end(), dist);
	Print << DiscreteSample(a, dist);
	Print << DiscreteSample(d, dist);
	Print << DiscreteSample(l, dist);
	Print << DiscreteSample({ 10,20,30,40,50 }, dist);

	Array<size_t> results(5);

	Print << dist.probabilities();

	for (auto i : step(100000))
	{
		++results[dist(GetDefaultRNG())];
	}

	Print << results;

	while (System::Update())
	{

	}
}

