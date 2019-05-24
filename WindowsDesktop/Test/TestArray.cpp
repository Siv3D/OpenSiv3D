
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# define SIV3D_CONCURRENT
# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

struct Obj
{
	int32 n;
	int32 id;

	bool operator <(const Obj& o) const
	{
		return n < o.n;
	}

	bool operator ==(const Obj& o) const
	{
		return (n == o.n) && (id == o.id);
	}
};

namespace s3d
{
	static void Formatter(FormatData& formatData, const Obj& value)
	{
		return Formatter(formatData, Point(value.n, value.id));
	}
}

TEST_CASE("Array")
{
	{
		Array<int32> v;
		REQUIRE(v.size() == 0);
	}

	{
		Array<int32> v{};
		REQUIRE(v.size() == 0);
	}

	{
		Array<int32> v{ 10 };
		REQUIRE(v.size() == 1);
	}

	{
		Array<int32> v = { 10 };
		REQUIRE(v.size() == 1);
	}

	{
		Array<int32> v = { 10, 20 };
		REQUIRE(v.size() == 2);
	}

	{
		Array<int32> v{ 10, 20 };
		REQUIRE(v.size() == 2);
	}

	{
		Array<int32> v = { 10, 20, 30, 40, 50 };
		REQUIRE(v.size() == 5);
	}

	{
		Array<int32> v{ 10, 20, 30, 40, 50 };
		REQUIRE(v.size() == 5);
	}

	{
		Array<int32> v(10);
		REQUIRE(v.size() == 10);
	}

	{
		Array<int32> v(10, 55);
		REQUIRE(v.size() == 10);
	}

	{
		struct Gen
		{
			int32 operator()()
			{
				return 123;
			}
		};

		Array<int32> v(10, Arg::generator = Gen());
		REQUIRE(v.size() == 10);
		REQUIRE(v.front() == 123);
		REQUIRE(v.back() == 123);
	}

	{
		Array<int32> v(10, Arg::generator = []() { return 123; });
		REQUIRE(v.size() == 10);
		REQUIRE(v.front() == 123);
		REQUIRE(v.back() == 123);
	}

	{
		struct Gen
		{
			int32 operator()(size_t i)
			{
				return 100 + static_cast<int32>(i);
			}
		};

		Array<int32> v(10, Arg::indexedGenerator = Gen());
		REQUIRE(v.size() == 10);
		REQUIRE(v.front() == 100);
		REQUIRE(v.back() == 109);
	}

	{
		Array<int32> v(10, Arg::indexedGenerator = [](size_t i) { return 100 + static_cast<int32>(i); });
		REQUIRE(v.size() == 10);
		REQUIRE(v.front() == 100);
		REQUIRE(v.back() == 109);
	}

	{
		Array<int32> v;
		REQUIRE(v.size() == 0);
		REQUIRE(v.count() == 0);
		REQUIRE(v.isEmpty() == true);
		REQUIRE(static_cast<bool>(v) == false);
		REQUIRE(v.size_bytes() == 0);
		REQUIRE_THROWS_AS(v.at(0), std::out_of_range);
	}

	{
		const Array<int32> v0 = { 1, 2, 3, 4 }, v1 = { 1, 2, 3, 4, 5 };
		REQUIRE(v0 == v0);
		REQUIRE(v0 != v1);
		REQUIRE(v1 != v0);
		REQUIRE(v1 == v1);
		REQUIRE(v0 == MakeArray(1, 2, 3, 4));
		REQUIRE(Array<int32>() == Array<int32>());
		REQUIRE(Array<int32>() != v0);
		REQUIRE(v0 != Array<int32>());
	}

	{
		REQUIRE(MakeArray<int32>() == Array<int32>{});
		REQUIRE(MakeArray(1) == Array<int32>{ 1 });
		REQUIRE(MakeArray(1, 2, 3) == Array<int32>{ 1, 2, 3});
		REQUIRE(MakeArray(40.0, 25.5f, 5.5f) == Array<double>{ 40.0, 25.5f, 5.5f });
	}

	{
		Array<int32> v = { 10, 20, 30, 40, 50 };
		REQUIRE(v.size() == 5);
		REQUIRE(v.count() == 5);
		REQUIRE(v.isEmpty() == false);
		REQUIRE(static_cast<bool>(v) == true);
		REQUIRE(v.size_bytes() == (5 * sizeof(int32)));
		REQUIRE(v[0] == 10);
		REQUIRE(v[4] == 50);
		REQUIRE(v[0] == 10);
		REQUIRE(v[4] == 50);
		REQUIRE_NOTHROW(v.at(4));
		REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
	}

	{
		Array<int32> v(1000);
		v.release();
		REQUIRE(v.size() == 0);
		REQUIRE(v.capacity() < 1000);
	}

	{
		Array<int32> v;
		v.push_front(20);
		REQUIRE(v == Array<int32>{20});

		v.push_front(10);
		REQUIRE(v == Array<int32>{10, 20});

		v.pop_front();
		REQUIRE(v == Array<int32>{20});

		v.pop_front();
		REQUIRE(v == Array<int32>{});

		v << 10 << 20;
		REQUIRE(v == MakeArray(10, 20));

		v.append(MakeArray(30, 40));
		REQUIRE(v == MakeArray(10, 20, 30, 40));
	}

	{
		REQUIRE(Array<int32>{10, 20, 30, 40, 50}[4] == 50);
		REQUIRE(Array<int32>{10, 20, 30, 40, 50}.at(4) == 50);
	}

	{
		const Array<int32> v;
		REQUIRE(v.all(IsEven) == true);
		REQUIRE(v.all(IsOdd) == true);
		REQUIRE(v.any(IsEven) == false);
		REQUIRE(v.any(IsOdd) == false);
		REQUIRE(v.none(IsEven) == true);
		REQUIRE(v.none(IsOdd) == true);
	}

	{
		const Array<int32> v = { 12, 34, 56, 78, 90 };
		REQUIRE(v.all(IsEven) == true);
		REQUIRE(v.all(IsOdd) == false);
		REQUIRE(v.any(IsEven) == true);
		REQUIRE(v.any(IsOdd) == false);
		REQUIRE(v.none(IsEven) == false);
		REQUIRE(v.none(IsOdd) == true);
	}

	{
		const Array<int32> v = { 12, 34, 56, 78, 90 };
		REQUIRE(v.includes(v.choice()));
		REQUIRE(v.choice(5) == v);
		REQUIRE(v.includes(v.choice(GetDefaultRNG())));
		REQUIRE(v.choice(5, GetDefaultRNG()) == v);
	}

	{
		const Array<int32> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		REQUIRE(v.chunk(0) == Array<Array<int32>>{});
		REQUIRE(v.chunk(4) == Array<Array<int32>>{ { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }});
		REQUIRE(v.chunk(5) == Array<Array<int32>>{ { 0, 1, 2, 3, 4 }, { 5, 6, 7, 8, 9 }, { 10, 11 }});
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.count(10) == 2);
		REQUIRE(v.count(40) == 0);
		REQUIRE(v.count_if(Equal(10)) == 2);
		REQUIRE(v.count_if(LessThan(30)) == 4);
		REQUIRE(v.count_if([](int32 n) { return n != 10 && n != 50; }) == 4);
	}

	{
		const Array<int32> v = { 12, 34, 56, 78, 90 };
		REQUIRE(v.dropped(0) == MakeArray(12, 34, 56, 78, 90));
		REQUIRE(v.dropped(2) == MakeArray(56, 78, 90));
		REQUIRE(v.dropped(100) == MakeArray<int32>());
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.dropped_while(LessThan(30)) == MakeArray(30, 20, 50, 30, 20, 10));
		REQUIRE(v.dropped_while(LessThan(0)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		REQUIRE(v.dropped_while(LessThan(100)) == MakeArray<int32>());
	}

	{
		int32 count = 0;
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		v.each([&](int32) { ++count; });
		v.each([&](const int32&) { ++count; });
		REQUIRE(count == 14);
	}

	{
		int32 count = 0;
		Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		v.each([&](int32& n) { ++count; n *= 2; });
		v.each([&](int32) { ++count; });
		REQUIRE(count == 14);
		REQUIRE(v == MakeArray(20, 60, 40, 100, 60, 40, 20));
	}

	{
		size_t count = 0;
		const Array<int32> v = { 10, 30, 20 };
		v.each_index([&](size_t i, int32) { count += i; });
		v.each_index([&](size_t, const int32& n) { count += n; });
		REQUIRE(count == 63);
	}

	{
		size_t count = 0;
		Array<int32> v = { 10, 30, 20 };
		v.each_index([&](size_t i, int32& n) { count += i; n *= 2; });
		v.each_index([&](size_t, const int32& n) { count += n; });
		REQUIRE(count == 123);
	}

	{
		const Array<int32> v = { 10, 30, 20 };
		REQUIRE(v.fetch(1, -1) == 30);
		REQUIRE(v.fetch(5, -1) == -1);
		const Array<int32> v2;
		REQUIRE(v2.fetch(0, -1) == -1);
	}

	{
		Array<int32> v(10);
		v.fill(123);
		REQUIRE(v.size() == 10);
		REQUIRE(v.all(Equal(123)));
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.filter(LessThan(25)) == MakeArray(10, 20, 20, 10));
	}

	{
		const Array<int32> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		REQUIRE(v.in_groups(0) == Array<Array<int32>>{});
		REQUIRE(v.in_groups(2) == Array<Array<int32>>{ { 0, 1, 2, 3, 4, 5 }, { 6, 7, 8, 9, 10, 11 }});
		REQUIRE(v.in_groups(5) == Array<Array<int32>>{ { 0, 1, 2}, { 3, 4, 5 }, { 6, 7 }, { 8, 9 }, { 10, 11 }});
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.includes(50));
		REQUIRE(v.includes(40) == false);
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.includes_if(IsEven) == true);
		REQUIRE(v.includes_if(GreaterThan(100)) == false);
	}

	{
		const Array<int32> v0 = { 10, 30, 20, 50, 30, 20, 10 };
		const Array<int32> v1 = { 10, 10, 20, 20, 30, 50 };

		REQUIRE(v0.isSorted() == false);
		REQUIRE(v1.isSorted() == true);
	}

	{
		const Array<int32> v0 = {};
		const Array<int32> v1 = { 12, 34, 56 };

		REQUIRE(v0.join() == U"{}");
		REQUIRE(v0.join(U"\t", U"[", U"]") == U"[]");

		REQUIRE(v1.join() == U"{12, 34, 56}");
		REQUIRE(v1.join(U"\t", U"[", U"]") == U"[12\t34\t56]");
	}

	{
		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.keep_if(LessThan(100)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		}

		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.keep_if(LessThan(25)) == MakeArray(10, 20, 20, 10));
		}

		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.keep_if(LessThan(0)) == MakeArray<int32>());
		}
	}

	{
		const Array<int32> v = { 10, 20, 30 };
		REQUIRE(v.map(Plus(1)) == MakeArray(11, 21, 31));
	}

	{
		using Arg::_;
		const Array<int32> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.reduce(_ + _, 0) == 15);
		REQUIRE(v.reduce(_ * _, 1) == 120);
	}

	{
		using Arg::_;
		const Array<int32> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.reduce(_ + _, 0) == 15);
		REQUIRE(v.reduce(_ * _, 1) == 120);
	}

	{
		using Arg::_;
		const Array<int32> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.reduce1(_ + _) == 15);
		REQUIRE(v.reduce1(_ * _) == 120);

		const Array<int32> v1 = {};
		REQUIRE_THROWS_AS(v1.reduce1(_ + _), std::out_of_range);
	}

	{
		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove(10) == MakeArray(30, 20, 50, 30, 20));
		}

		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove(100) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		}
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.removed(10) == MakeArray(30, 20, 50, 30, 20));
		REQUIRE(v.removed(100) == MakeArray(10, 30, 20, 50, 30, 20, 10));

		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).removed(10) == MakeArray(30, 20, 50, 30, 20));
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).removed(100) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove_at(1).remove_at(2) == MakeArray(10, 20, 30, 20, 10));
		}

		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE_THROWS_AS(v.remove_at(7), std::out_of_range);
		}
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.removed_at(1) == MakeArray(10, 20, 50, 30, 20, 10));
		REQUIRE(v.removed_at(3) == MakeArray(10, 30, 20, 30, 20, 10));
		REQUIRE_THROWS_AS(v.removed_at(7), std::out_of_range);
	}

	{
		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove_if(LessThan(25)) == MakeArray(30, 50, 30));
		}

		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove_if(LessThan(100)) == MakeArray<int32>());
		}

		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove_if(LessThan(0)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		}
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.removed_if(LessThan(25)) == MakeArray(30, 50, 30));
		REQUIRE(v.removed_if(LessThan(100)) == MakeArray<int32>());
		REQUIRE(v.removed_if(LessThan(0)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).removed_if(LessThan(25)) == MakeArray(30, 50, 30));
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).removed_if(LessThan(100)) == MakeArray<int32>());
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).removed_if(LessThan(0)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.replace(10, 40) == MakeArray(40, 30, 20, 50, 30, 20, 40));
		}

		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.replace(0, 40) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		}
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.replaced(10, 40) == MakeArray(40, 30, 20, 50, 30, 20, 40));
		REQUIRE(v.replaced(0, 40) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).replaced(10, 40) == MakeArray(40, 30, 20, 50, 30, 20, 40));
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).replaced(0, 40) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.replace_if(LessThan(25), -1) == MakeArray(-1, 30, -1, 50, 30, -1, -1));
		}

		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.replace_if(LessThan(100), -1) == MakeArray(-1, -1, -1, -1, -1, -1, -1));
		}

		{
			Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.replace_if(LessThan(0), -1) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		}
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.replaced_if(LessThan(25), -1) == MakeArray(-1, 30, -1, 50, 30, -1, -1));
		REQUIRE(v.replaced_if(LessThan(100), -1) == MakeArray(-1, -1, -1, -1, -1, -1, -1));
		REQUIRE(v.replaced_if(LessThan(0), -1) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).replaced_if(LessThan(25), -1) == MakeArray(-1, 30, -1, 50, 30, -1, -1));
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).replaced_if(LessThan(100), -1) == MakeArray(-1, -1, -1, -1, -1, -1, -1));
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).replaced_if(LessThan(0), -1) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		Array<int32> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.reverse() == MakeArray(5, 4, 3, 2, 1));
	}

	{
		const Array<int32> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.reversed() == MakeArray(5, 4, 3, 2, 1));
	}

	{
		const Array<int32> v = { 1, 2, 3, 4, 5 };
		REQUIRE(MakeArray(1, 2, 3, 4, 5).reversed() == MakeArray(5, 4, 3, 2, 1));
	}

	{
		int32 i = 0;
		Array<int32> v = { 1, 2, 3, 4, 5 };
		v.reverse_each([&](int32& n) { n += i; ++i; });
		REQUIRE(v.all(Equal(5)));
	}

	{
		int32 i = 0;
		const Array<int32> v = { 1, 2, 3, 4, 5 };
		v.reverse_each([&](int32 n) { i = i * 10 + n; });
		REQUIRE(i == 54321);
	}

	{
		Array<int32> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.rotate(0) == MakeArray(1, 2, 3, 4, 5));
		REQUIRE(v.rotate(1) == MakeArray(2, 3, 4, 5, 1));
		REQUIRE(v.rotate(-1) == MakeArray(1, 2, 3, 4, 5));
		REQUIRE(v.rotate(54) == MakeArray(5, 1, 2, 3, 4));
		REQUIRE(v.rotate(-54) == MakeArray(1, 2, 3, 4, 5));
	}

	{
		const Array<int32> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.rotated(0) == MakeArray(1, 2, 3, 4, 5));
		REQUIRE(v.rotated(1) == MakeArray(2, 3, 4, 5, 1));
		REQUIRE(v.rotated(-1) == MakeArray(5, 1, 2, 3, 4));
		REQUIRE(v.rotated(54) == MakeArray(5, 1, 2, 3, 4));
		REQUIRE(v.rotated(-54) == MakeArray(2, 3, 4, 5, 1));
	}

	{
		REQUIRE(MakeArray(1, 2, 3, 4, 5).rotated(0) == MakeArray(1, 2, 3, 4, 5));
		REQUIRE(MakeArray(1, 2, 3, 4, 5).rotated(1) == MakeArray(2, 3, 4, 5, 1));
		REQUIRE(MakeArray(1, 2, 3, 4, 5).rotated(-1) == MakeArray(5, 1, 2, 3, 4));
		REQUIRE(MakeArray(1, 2, 3, 4, 5).rotated(54) == MakeArray(5, 1, 2, 3, 4));
		REQUIRE(MakeArray(1, 2, 3, 4, 5).rotated(-54) == MakeArray(2, 3, 4, 5, 1));
	}

	{
		{
			Array<int32> v = Range(0, 100);
			v.shuffle();
			REQUIRE(v != Range(0, 100).asArray());
		}

		{
			Array<int32> v = Range(0, 100);
			v.shuffle(GetDefaultRNG());
			REQUIRE(v != Range(0, 100).asArray());
		}
	}

	{
		const Array<int32> v = Range(0, 100);
		REQUIRE(v.shuffled() != Range(0, 100).asArray());
		REQUIRE(v.shuffled(GetDefaultRNG()) != Range(0, 100).asArray());
		REQUIRE(Range(0, 100).asArray().shuffled() != Range(0, 100).asArray());
		REQUIRE(Range(0, 100).asArray().shuffled(GetDefaultRNG()) != Range(0, 100).asArray());
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.slice(0) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		REQUIRE(v.slice(1) == MakeArray(30, 20, 50, 30, 20, 10));
		REQUIRE(v.slice(3) == MakeArray(50, 30, 20, 10));
		REQUIRE(v.slice(7) == MakeArray<int32>());

		REQUIRE(v.slice(0, 0) == MakeArray<int32>());
		REQUIRE(v.slice(0, 1) == MakeArray(10));
		REQUIRE(v.slice(0, 3) == MakeArray(10, 30, 20));
		REQUIRE(v.slice(0, 7) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		REQUIRE(v.slice(0, 10) == MakeArray(10, 30, 20, 50, 30, 20, 10));

		REQUIRE(v.slice(2, 0) == MakeArray<int32>());
		REQUIRE(v.slice(2, 1) == MakeArray(20));
		REQUIRE(v.slice(2, 3) == MakeArray(20, 50, 30));
		REQUIRE(v.slice(2, 7) == MakeArray(20, 50, 30, 20, 10));
		REQUIRE(v.slice(2, 10) == MakeArray(20, 50, 30, 20, 10));

		REQUIRE(v.slice(7, 0) == MakeArray<int32>());
		REQUIRE(v.slice(7, 1) == MakeArray<int32>());
		REQUIRE(v.slice(7, 10) == MakeArray<int32>());
	}

	{
		Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.sort() == MakeArray(10, 10, 20, 20, 30, 30, 50));
	}

	{
		Array<Obj> v = { { 50, 0 }, { 10, 0 }, { 30, 0 }, { 20, 0 }, { 20, 1 }, { 50, 1 }, { 20, 2 }, { 20, 3 }, { 10, 1 }};
		REQUIRE(v.stable_sort() == MakeArray(
			Obj{ 10, 0 }, Obj{ 10, 1 }, Obj{ 20, 0 }, Obj{ 20, 1 }, Obj{ 20, 2 }, Obj{ 20, 3 }, Obj{ 30, 0 }, Obj{ 50, 0 }, Obj{ 50, 1 }));
	}

	{
		Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.sort_by(std::greater<>()) == MakeArray(50, 30, 30, 20, 20, 10, 10));
	}

	{
		Array<Obj> v = { { 50, 0 }, { 10, 0 }, { 30, 0 }, { 20, 0 }, { 20, 1 }, { 50, 1 }, { 20, 2 }, { 20, 3 }, { 10, 1 } };
		REQUIRE(v.stable_sort_by([](const Obj& a, const Obj& b) { return a.id < b.id; }) == MakeArray(
			Obj{ 50, 0 }, Obj{ 10, 0 }, Obj{ 30, 0 }, Obj{ 20, 0 }, Obj{ 20, 1 }, Obj{ 50, 1 }, Obj{ 10, 1 }, Obj{ 20, 2 }, Obj{ 20, 3 }));
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.sorted() == MakeArray(10, 10, 20, 20, 30, 30, 50));
	}

	{
		const Array<Obj> v = { { 50, 0 }, { 10, 0 }, { 30, 0 }, { 20, 0 }, { 20, 1 }, { 50, 1 }, { 20, 2 }, { 20, 3 }, { 10, 1 } };
		REQUIRE(v.stable_sorted() == MakeArray(
			Obj{ 10, 0 }, Obj{ 10, 1 }, Obj{ 20, 0 }, Obj{ 20, 1 }, Obj{ 20, 2 }, Obj{ 20, 3 }, Obj{ 30, 0 }, Obj{ 50, 0 }, Obj{ 50, 1 }));
	}

	{
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).sorted() == MakeArray(10, 10, 20, 20, 30, 30, 50));
	}

	{
		REQUIRE(MakeArray(
			Obj{ 50, 0 }, Obj{ 10, 0 }, Obj{ 30, 0 }, Obj{ 20, 0 }, Obj{ 20, 1 }, Obj{ 50, 1 }, Obj{ 20, 2 }, Obj{ 20, 3 }, Obj{ 10, 1 })
			.stable_sorted() == MakeArray(
			Obj{ 10, 0 }, Obj{ 10, 1 }, Obj{ 20, 0 }, Obj{ 20, 1 }, Obj{ 20, 2 }, Obj{ 20, 3 }, Obj{ 30, 0 }, Obj{ 50, 0 }, Obj{ 50, 1 }));
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.sorted_by(std::greater<>()) == MakeArray(50, 30, 30, 20, 20, 10, 10));
	}

	{
		const Array<Obj> v = { { 50, 0 }, { 10, 0 }, { 30, 0 }, { 20, 0 }, { 20, 1 }, { 50, 1 }, { 20, 2 }, { 20, 3 }, { 10, 1 } };
		REQUIRE(v.stable_sorted_by([](const Obj& a, const Obj& b) { return a.id < b.id; }) == MakeArray(
			Obj{ 50, 0 }, Obj{ 10, 0 }, Obj{ 30, 0 }, Obj{ 20, 0 }, Obj{ 20, 1 }, Obj{ 50, 1 }, Obj{ 10, 1 }, Obj{ 20, 2 }, Obj{ 20, 3 }));
	}

	{
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).sorted_by(std::greater<>()) == MakeArray(50, 30, 30, 20, 20, 10, 10));
	}

	{
		REQUIRE(MakeArray(
			Obj{ 50, 0 }, Obj{ 10, 0 }, Obj{ 30, 0 }, Obj{ 20, 0 }, Obj{ 20, 1 }, Obj{ 50, 1 }, Obj{ 20, 2 }, Obj{ 20, 3 }, Obj{ 10, 1 })
			.stable_sorted_by([](const Obj& a, const Obj& b) { return a.id < b.id; }) == MakeArray(
			Obj{ 50, 0 }, Obj{ 10, 0 }, Obj{ 30, 0 }, Obj{ 20, 0 }, Obj{ 20, 1 }, Obj{ 50, 1 }, Obj{ 10, 1 }, Obj{ 20, 2 }, Obj{ 20, 3 }));
	}

	{
		const Array<int32> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.sum() == 15);

		const Array<String> vs = { U"AA", U"BB", U"CC" };
		REQUIRE(vs.sum() == U"AABBCC");
	}

	{
		const Array<float> v = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };
		REQUIRE(v.sumF() == 1.5f);
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.take(0) == MakeArray<int32>());
		REQUIRE(v.take(1) == MakeArray(10));
		REQUIRE(v.take(3) == MakeArray(10, 30, 20));
		REQUIRE(v.take(7) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		REQUIRE(v.take(100) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.take_while(LessThan(0)) == MakeArray<int32>());
		REQUIRE(v.take_while(LessThan(25)) == MakeArray(10));
		REQUIRE(v.take_while(LessThan(100)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.unique() == MakeArray(10, 20, 30, 50));
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.uniqued() == MakeArray(10, 20, 30, 50));
	}

	{
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).uniqued() == MakeArray(10, 20, 30, 50));
	}

	{
		const Array<int32> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.values_at({}) == MakeArray<int32>());
		REQUIRE(v.values_at({ 0, 1, 2 }) == MakeArray(10, 30, 20));
		REQUIRE(v.values_at({ 6, 0 }) == MakeArray(10, 10));
		REQUIRE_THROWS_AS(v.values_at({ 6, 7 }), std::out_of_range);
	}

	{
		const Array<int32> v = Range(0, 100'000);
		REQUIRE(v.parallel_count_if(IsPrime) == 9592);
	}

	{
		std::atomic_int64_t sum = 0;
		Array<int32> v = Range(0, 100'000);
		v.parallel_each([](int32& n) { n *= 2; });
		v.parallel_each([&](int32 n) { sum += n; });
		REQUIRE(sum == 10000100000LL);
	}

	{
		const Array<int32> v = Range(0, 100'000);
		REQUIRE(v.map(Plus(1)) == Range(1, 100'001).asArray());
	}

	{
		REQUIRE(IsMemoryContiguousContainer_v<Array<int32>>);
		REQUIRE(IsMemoryContiguousContainer_v<Array<Vec2>>);
		REQUIRE(IsMemoryContiguousContainer_v<Array<String>> == false);
	}
}

# endif
