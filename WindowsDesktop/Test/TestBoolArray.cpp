
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

TEST_CASE("BoolArray")
{
	{
		Array<bool> v;
		REQUIRE(v.size() == 0);
	}

	{
		Array<bool> v{};
		REQUIRE(v.size() == 0);
	}

	{
		Array<bool> v{ true };
		REQUIRE(v.size() == 1);
	}

	{
		Array<bool> v = { true };
		REQUIRE(v.size() == 1);
	}

	{
		Array<bool> v = { true, false };
		REQUIRE(v.size() == 2);
	}

	{
		Array<bool> v{ true, false };
		REQUIRE(v.size() == 2);
	}

	{
		Array<bool> v = { true, false, true, true, false };
		REQUIRE(v.size() == 5);
	}

	{
		Array<bool> v{ true, false, true, true, false };
		REQUIRE(v.size() == 5);
	}

	{
		Array<bool> v(10);
		REQUIRE(v.size() == 10);
	}

	{
		Array<bool> v(10, true);
		REQUIRE(v.size() == 10);
	}

	{
		struct Gen
		{
			bool operator()()
			{
				return true;
			}
		};

		Array<bool> v(10, Arg::generator = Gen());
		REQUIRE(v.size() == 10);
		REQUIRE(v.front() == true);
		REQUIRE(v.back() == true);
	}

	{
		Array<bool> v(10, Arg::generator = []() { return true; });
		REQUIRE(v.size() == 10);
		REQUIRE(v.front() == true);
		REQUIRE(v.back() == true);
	}

	{
		struct Gen
		{
			bool operator()(size_t i)
			{
				return IsEven(i);
			}
		};

		Array<bool> v(10, Arg::indexedGenerator = Gen());
		REQUIRE(v.size() == 10);
		REQUIRE(v.front() == true);
		REQUIRE(v.back() == false);
	}

	{
		Array<bool> v(10, Arg::indexedGenerator = IsEven);
		REQUIRE(v.size() == 10);
		REQUIRE(v.front() == true);
		REQUIRE(v.back() == false);
	}


	{
		Array<bool> v;
		REQUIRE(v.size() == 0);
		REQUIRE(v.isEmpty() == true);
		REQUIRE(static_cast<bool>(v) == false);
		REQUIRE(v.size_bytes() == 0);
		REQUIRE_THROWS_AS(v.at(0), std::out_of_range);
	}

	{
		const Array<bool> v0 = { true, false, true, true }, v1 = { true, false, true, true, false };
		REQUIRE(v0 == v0);
		REQUIRE(v0 != v1);
		REQUIRE(v1 != v0);
		REQUIRE(v1 == v1);
		REQUIRE(v0 == MakeArray(true, false, true, true));
		REQUIRE(Array<bool>() == Array<bool>());
		REQUIRE(Array<bool>() != v0);
		REQUIRE(v0 != Array<bool>());
	}

	/*
	{
		Array<bool> v = { 10, 20, 30, 40, 50 };
		REQUIRE(v.size() == 5);
		REQUIRE(v.isEmpty() == false);
		REQUIRE(static_cast<bool>(v) == true);
		REQUIRE(v.size_bytes() == (5 * sizeof(bool)));
		REQUIRE(v[0] == 10);
		REQUIRE(v[4] == 50);
		REQUIRE(v[0] == 10);
		REQUIRE(v[4] == 50);
		REQUIRE_NOTHROW(v.at(4));
		REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
	}

	{
		Array<bool> v(1000);
		v.release();
		REQUIRE(v.size() == 0);
		REQUIRE(v.capacity() < 1000);
	}

	{
		Array<bool> v;
		v.push_front(20);
		REQUIRE(v == Array<bool>{20});

		v.push_front(10);
		REQUIRE(v == Array<bool>{10, 20});

		v.pop_front();
		REQUIRE(v == Array<bool>{20});

		v.pop_front();
		REQUIRE(v == Array<bool>{});

		v << 10 << 20;
		REQUIRE(v == MakeArray(10, 20));

		v.append(MakeArray(30, 40));
		REQUIRE(v == MakeArray(10, 20, 30, 40));
	}

	{
		REQUIRE(Array<bool>{10, 20, 30, 40, 50}[4] == 50);
		REQUIRE(Array<bool>{10, 20, 30, 40, 50}.at(4) == 50);
	}

	{
		const Array<bool> v;
		REQUIRE(v.all(IsEven) == true);
		REQUIRE(v.all(IsOdd) == true);
		REQUIRE(v.any(IsEven) == false);
		REQUIRE(v.any(IsOdd) == false);
		REQUIRE(v.none(IsEven) == true);
		REQUIRE(v.none(IsOdd) == true);
	}

	{
		const Array<bool> v = { 12, 34, 56, 78, 90 };
		REQUIRE(v.all(IsEven) == true);
		REQUIRE(v.all(IsOdd) == false);
		REQUIRE(v.any(IsEven) == true);
		REQUIRE(v.any(IsOdd) == false);
		REQUIRE(v.none(IsEven) == false);
		REQUIRE(v.none(IsOdd) == true);
	}

	{
		const Array<bool> v = { 12, 34, 56, 78, 90 };
		REQUIRE(v.includes(v.choice()));
		REQUIRE(v.choice(5) == v);
		REQUIRE(v.includes(v.choice(GetDefaultRNG())));
		REQUIRE(v.choice(5, GetDefaultRNG()) == v);
	}

	{
		const Array<bool> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		REQUIRE(v.chunk(0) == Array<Array<bool>>{});
		REQUIRE(v.chunk(4) == Array<Array<bool>>{ { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }});
		REQUIRE(v.chunk(5) == Array<Array<bool>>{ { 0, 1, 2, 3, 4 }, { 5, 6, 7, 8, 9 }, { 10, 11 }});
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.count(10) == 2);
		REQUIRE(v.count(40) == 0);
		REQUIRE(v.count_if(Equal(10)) == 2);
		REQUIRE(v.count_if(LessThan(30)) == 4);
		REQUIRE(v.count_if([](bool n) { return n != 10 && n != 50; }) == 4);
	}

	{
		const Array<bool> v = { 12, 34, 56, 78, 90 };
		REQUIRE(v.dropped(0) == MakeArray(12, 34, 56, 78, 90));
		REQUIRE(v.dropped(2) == MakeArray(56, 78, 90));
		REQUIRE(v.dropped(100) == MakeArray<bool>());
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.dropped_while(LessThan(30)) == MakeArray(30, 20, 50, 30, 20, 10));
		REQUIRE(v.dropped_while(LessThan(0)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		REQUIRE(v.dropped_while(LessThan(100)) == MakeArray<bool>());
	}

	{
		bool count = 0;
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		v.each([&](bool) { ++count; });
		v.each([&](const bool&) { ++count; });
		REQUIRE(count == 14);
	}

	{
		bool count = 0;
		Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		v.each([&](bool& n) { ++count; n *= 2; });
		v.each([&](bool) { ++count; });
		REQUIRE(count == 14);
		REQUIRE(v == MakeArray(20, 60, 40, 100, 60, 40, 20));
	}

	{
		size_t count = 0;
		const Array<bool> v = { 10, 30, 20 };
		v.each_index([&](size_t i, bool) { count += i; });
		v.each_index([&](size_t, const bool& n) { count += n; });
		REQUIRE(count == 63);
	}

	{
		size_t count = 0;
		Array<bool> v = { 10, 30, 20 };
		v.each_index([&](size_t i, bool& n) { count += i; n *= 2; });
		v.each_index([&](size_t, const bool& n) { count += n; });
		REQUIRE(count == 123);
	}

	{
		const Array<bool> v = { 10, 30, 20 };
		REQUIRE(v.fetch(1, -1) == 30);
		REQUIRE(v.fetch(5, -1) == -1);
		const Array<bool> v2;
		REQUIRE(v2.fetch(0, -1) == -1);
	}

	{
		Array<bool> v(10);
		v.fill(123);
		REQUIRE(v.size() == 10);
		REQUIRE(v.all(Equal(123)));
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.filter(LessThan(25)) == MakeArray(10, 20, 20, 10));
	}

	{
		const Array<bool> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		REQUIRE(v.in_groups(0) == Array<Array<bool>>{});
		REQUIRE(v.in_groups(2) == Array<Array<bool>>{ { 0, 1, 2, 3, 4, 5 }, { 6, 7, 8, 9, 10, 11 }});
		REQUIRE(v.in_groups(5) == Array<Array<bool>>{ { 0, 1, 2}, { 3, 4, 5 }, { 6, 7 }, { 8, 9 }, { 10, 11 }});
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.includes(50));
		REQUIRE(v.includes(40) == false);
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.includes_if(IsEven) == true);
		REQUIRE(v.includes_if(GreaterThan(100)) == false);
	}

	{
		const Array<bool> v0 = { 10, 30, 20, 50, 30, 20, 10 };
		const Array<bool> v1 = { 10, 10, 20, 20, 30, 50 };

		REQUIRE(v0.isSorted() == false);
		REQUIRE(v1.isSorted() == true);
	}

	{
		const Array<bool> v0 = {};
		const Array<bool> v1 = { 12, 34, 56 };

		REQUIRE(v0.join() == U"{}");
		REQUIRE(v0.join(U"\t", U"[", U"]") == U"[]");

		REQUIRE(v1.join() == U"{12, 34, 56}");
		REQUIRE(v1.join(U"\t", U"[", U"]") == U"[12\t34\t56]");
	}

	{
		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.keep_if(LessThan(100)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		}

		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.keep_if(LessThan(25)) == MakeArray(10, 20, 20, 10));
		}

		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.keep_if(LessThan(0)) == MakeArray<bool>());
		}
	}

	{
		const Array<bool> v = { 10, 20, 30 };
		REQUIRE(v.map(Plus(1)) == MakeArray(11, 21, 31));
	}

	{
		using Arg::_;
		const Array<bool> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.reduce(_ + _, 0) == 15);
		REQUIRE(v.reduce(_ * _, 1) == 120);
	}

	{
		using Arg::_;
		const Array<bool> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.reduce(_ + _, 0) == 15);
		REQUIRE(v.reduce(_ * _, 1) == 120);
	}

	{
		using Arg::_;
		const Array<bool> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.reduce1(_ + _) == 15);
		REQUIRE(v.reduce1(_ * _) == 120);

		const Array<bool> v1 = {};
		REQUIRE_THROWS_AS(v1.reduce1(_ + _), std::out_of_range);
	}

	{
		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove(10) == MakeArray(30, 20, 50, 30, 20));
		}

		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove(100) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		}
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.removed(10) == MakeArray(30, 20, 50, 30, 20));
		REQUIRE(v.removed(100) == MakeArray(10, 30, 20, 50, 30, 20, 10));

		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).removed(10) == MakeArray(30, 20, 50, 30, 20));
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).removed(100) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove_at(1).remove_at(2) == MakeArray(10, 20, 30, 20, 10));
		}

		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE_THROWS_AS(v.remove_at(7), std::out_of_range);
		}
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.removed_at(1) == MakeArray(10, 20, 50, 30, 20, 10));
		REQUIRE(v.removed_at(3) == MakeArray(10, 30, 20, 30, 20, 10));
		REQUIRE_THROWS_AS(v.removed_at(7), std::out_of_range);
	}

	{
		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove_if(LessThan(25)) == MakeArray(30, 50, 30));
		}

		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove_if(LessThan(100)) == MakeArray<bool>());
		}

		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.remove_if(LessThan(0)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		}
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.removed_if(LessThan(25)) == MakeArray(30, 50, 30));
		REQUIRE(v.removed_if(LessThan(100)) == MakeArray<bool>());
		REQUIRE(v.removed_if(LessThan(0)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).removed_if(LessThan(25)) == MakeArray(30, 50, 30));
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).removed_if(LessThan(100)) == MakeArray<bool>());
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).removed_if(LessThan(0)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.replace(10, 40) == MakeArray(40, 30, 20, 50, 30, 20, 40));
		}

		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.replace(0, 40) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		}
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.replaced(10, 40) == MakeArray(40, 30, 20, 50, 30, 20, 40));
		REQUIRE(v.replaced(0, 40) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).replaced(10, 40) == MakeArray(40, 30, 20, 50, 30, 20, 40));
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).replaced(0, 40) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.replace_if(LessThan(25), -1) == MakeArray(-1, 30, -1, 50, 30, -1, -1));
		}

		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.replace_if(LessThan(100), -1) == MakeArray(-1, -1, -1, -1, -1, -1, -1));
		}

		{
			Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
			REQUIRE(v.replace_if(LessThan(0), -1) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		}
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
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
		Array<bool> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.reverse() == MakeArray(5, 4, 3, 2, 1));
	}

	{
		const Array<bool> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.reversed() == MakeArray(5, 4, 3, 2, 1));
	}

	{
		const Array<bool> v = { 1, 2, 3, 4, 5 };
		REQUIRE(MakeArray(1, 2, 3, 4, 5).reversed() == MakeArray(5, 4, 3, 2, 1));
	}

	{
		bool i = 0;
		Array<bool> v = { 1, 2, 3, 4, 5 };
		v.reverse_each([&](bool& n) { n += i; ++i; });
		REQUIRE(v.all(Equal(5)));
	}

	{
		bool i = 0;
		const Array<bool> v = { 1, 2, 3, 4, 5 };
		v.reverse_each([&](bool n) { i = i * 10 + n; });
		REQUIRE(i == 54321);
	}

	{
		Array<bool> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.rotate(0) == MakeArray(1, 2, 3, 4, 5));
		REQUIRE(v.rotate(1) == MakeArray(2, 3, 4, 5, 1));
		REQUIRE(v.rotate(-1) == MakeArray(1, 2, 3, 4, 5));
		REQUIRE(v.rotate(54) == MakeArray(5, 1, 2, 3, 4));
		REQUIRE(v.rotate(-54) == MakeArray(1, 2, 3, 4, 5));
	}

	{
		const Array<bool> v = { 1, 2, 3, 4, 5 };
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
			Array<bool> v = Range(0, 100);
			v.shuffle();
			REQUIRE(v != Range(0, 100).asArray());
		}

		{
			Array<bool> v = Range(0, 100);
			v.shuffle(GetDefaultRNG());
			REQUIRE(v != Range(0, 100).asArray());
		}
	}

	{
		const Array<bool> v = Range(0, 100);
		REQUIRE(v.shuffled() != Range(0, 100).asArray());
		REQUIRE(v.shuffled(GetDefaultRNG()) != Range(0, 100).asArray());
		REQUIRE(Range(0, 100).asArray().shuffled() != Range(0, 100).asArray());
		REQUIRE(Range(0, 100).asArray().shuffled(GetDefaultRNG()) != Range(0, 100).asArray());
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.slice(0) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		REQUIRE(v.slice(1) == MakeArray(30, 20, 50, 30, 20, 10));
		REQUIRE(v.slice(3) == MakeArray(50, 30, 20, 10));
		REQUIRE(v.slice(7) == MakeArray<bool>());

		REQUIRE(v.slice(0, 0) == MakeArray<bool>());
		REQUIRE(v.slice(0, 1) == MakeArray(10));
		REQUIRE(v.slice(0, 3) == MakeArray(10, 30, 20));
		REQUIRE(v.slice(0, 7) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		REQUIRE(v.slice(0, 10) == MakeArray(10, 30, 20, 50, 30, 20, 10));

		REQUIRE(v.slice(2, 0) == MakeArray<bool>());
		REQUIRE(v.slice(2, 1) == MakeArray(20));
		REQUIRE(v.slice(2, 3) == MakeArray(20, 50, 30));
		REQUIRE(v.slice(2, 7) == MakeArray(20, 50, 30, 20, 10));
		REQUIRE(v.slice(2, 10) == MakeArray(20, 50, 30, 20, 10));

		REQUIRE(v.slice(7, 0) == MakeArray<bool>());
		REQUIRE(v.slice(7, 1) == MakeArray<bool>());
		REQUIRE(v.slice(7, 10) == MakeArray<bool>());
	}

	{
		Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.sort() == MakeArray(10, 10, 20, 20, 30, 30, 50));
	}

	{
		Array<Obj> v = { { 50, 0 }, { 10, 0 }, { 30, 0 }, { 20, 0 }, { 20, 1 }, { 50, 1 }, { 20, 2 }, { 20, 3 }, { 10, 1 }};
		REQUIRE(v.stable_sort() == MakeArray(
			Obj{ 10, 0 }, Obj{ 10, 1 }, Obj{ 20, 0 }, Obj{ 20, 1 }, Obj{ 20, 2 }, Obj{ 20, 3 }, Obj{ 30, 0 }, Obj{ 50, 0 }, Obj{ 50, 1 }));
	}

	{
		Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.sort_by(std::greater<>()) == MakeArray(50, 30, 30, 20, 20, 10, 10));
	}

	{
		Array<Obj> v = { { 50, 0 }, { 10, 0 }, { 30, 0 }, { 20, 0 }, { 20, 1 }, { 50, 1 }, { 20, 2 }, { 20, 3 }, { 10, 1 } };
		REQUIRE(v.stable_sort_by([](const Obj& a, const Obj& b) { return a.id < b.id; }) == MakeArray(
			Obj{ 50, 0 }, Obj{ 10, 0 }, Obj{ 30, 0 }, Obj{ 20, 0 }, Obj{ 20, 1 }, Obj{ 50, 1 }, Obj{ 10, 1 }, Obj{ 20, 2 }, Obj{ 20, 3 }));
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
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
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
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
		const Array<bool> v = { 1, 2, 3, 4, 5 };
		REQUIRE(v.sum() == 15);

		const Array<String> vs = { U"AA", U"BB", U"CC" };
		REQUIRE(vs.sum() == U"AABBCC");
	}

	{
		const Array<float> v = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };
		REQUIRE(v.sumF() == 1.5f);
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.take(0) == MakeArray<bool>());
		REQUIRE(v.take(1) == MakeArray(10));
		REQUIRE(v.take(3) == MakeArray(10, 30, 20));
		REQUIRE(v.take(7) == MakeArray(10, 30, 20, 50, 30, 20, 10));
		REQUIRE(v.take(100) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.take_while(LessThan(0)) == MakeArray<bool>());
		REQUIRE(v.take_while(LessThan(25)) == MakeArray(10));
		REQUIRE(v.take_while(LessThan(100)) == MakeArray(10, 30, 20, 50, 30, 20, 10));
	}

	{
		Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.unique() == MakeArray(10, 20, 30, 50));
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.uniqued() == MakeArray(10, 20, 30, 50));
	}

	{
		REQUIRE(MakeArray(10, 30, 20, 50, 30, 20, 10).uniqued() == MakeArray(10, 20, 30, 50));
	}

	{
		const Array<bool> v = { 10, 30, 20, 50, 30, 20, 10 };
		REQUIRE(v.values_at({}) == MakeArray<bool>());
		REQUIRE(v.values_at({ 0, 1, 2 }) == MakeArray(10, 30, 20));
		REQUIRE(v.values_at({ 6, 0 }) == MakeArray(10, 10));
		REQUIRE_THROWS_AS(v.values_at({ 6, 7 }), std::out_of_range);
	}

	{
		const Array<bool> v = Range(0, 100'000);
		REQUIRE(v.parallel_count_if(IsPrime) == 9592);
	}

	{
		std::atomic_int64_t sum = 0;
		Array<bool> v = Range(0, 100'000);
		v.parallel_each([](bool& n) { n *= 2; });
		v.parallel_each([&](bool n) { sum += n; });
		REQUIRE(sum == 10000100000LL);
	}

	{
		const Array<bool> v = Range(0, 100'000);
		REQUIRE(v.map(Plus(1)) == Range(1, 100'001).asArray());
	}
	*/
}

# endif
