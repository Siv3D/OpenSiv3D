
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# include <deque>
# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

TEST_CASE("TypeTraits")
{
	SECTION("IsPair")
	{
		REQUIRE(IsPair_v<int32> == false);
		REQUIRE(IsPair_v<std::pair<int32, String>> == true);
		REQUIRE(IsPair_v<Optional<std::pair<int32, int32>>> == false);
		REQUIRE(IsPair_v<std::tuple<int32, String>> == false);
	}

	SECTION("IsMemoryContiguousContainer")
	{
		REQUIRE(IsMemoryContiguousContainer_v<int32> == false);
		REQUIRE(IsMemoryContiguousContainer_v<std::pair<int32, String>> == false);
		REQUIRE(IsMemoryContiguousContainer_v<Optional<std::pair<int32, int32>>> == false);
		REQUIRE(IsMemoryContiguousContainer_v<std::tuple<int32, String>> == false);

		REQUIRE(IsMemoryContiguousContainer_v<std::array<int32, 10>> == true);
		REQUIRE(IsMemoryContiguousContainer_v<std::vector<bool>> == true);
		REQUIRE(IsMemoryContiguousContainer_v<std::vector<String>> == false);
		REQUIRE(IsMemoryContiguousContainer_v<Array<Point>> == true);
		REQUIRE(IsMemoryContiguousContainer_v<std::string> == true);
		REQUIRE(IsMemoryContiguousContainer_v<std::u32string> == true);
		REQUIRE(IsMemoryContiguousContainer_v<String> == true);
		REQUIRE(IsMemoryContiguousContainer_v<StringView> == true);

		REQUIRE(IsMemoryContiguousContainer_v<std::deque<int32>> == false);
	}

	SECTION("IsConvertibleToByteArrayView")
	{
		REQUIRE(IsConvertibleToByteArrayView_v<int32> == true);
		REQUIRE(IsConvertibleToByteArrayView_v<Byte> == true);
		REQUIRE(IsConvertibleToByteArrayView_v<Point> == true);
		REQUIRE(IsConvertibleToByteArrayView_v<ColorF> == true);
		REQUIRE(IsConvertibleToByteArrayView_v<String> == true);
		REQUIRE(IsConvertibleToByteArrayView_v<std::array<int32, 10>> == true);
		REQUIRE(IsConvertibleToByteArrayView_v<int[20]> == true);
		REQUIRE(IsConvertibleToByteArrayView_v<std::u32string> == true);
		REQUIRE(IsConvertibleToByteArrayView_v<StringView> == true);

		REQUIRE(IsConvertibleToByteArrayView_v<std::pair<int32, String>> == false);
		REQUIRE(IsConvertibleToByteArrayView_v<Array<String>> == false);
		REQUIRE(IsConvertibleToByteArrayView_v<std::deque<int32>> == false);
	}

	SECTION("CommonFloat")
	{
		REQUIRE(std::is_same_v<CommonFloat_t<int32, int32>, double>);
		REQUIRE(std::is_same_v<CommonFloat_t<int32, float>, float>);
		REQUIRE(std::is_same_v<CommonFloat_t<float, int32>, float>);
		REQUIRE(std::is_same_v<CommonFloat_t<int32, double>, double>);
		REQUIRE(std::is_same_v<CommonFloat_t<double, int32>, double>);

		REQUIRE(std::is_same_v<CommonFloat_t<float, float>, float>);
		REQUIRE(std::is_same_v<CommonFloat_t<float, double>, double>);
		REQUIRE(std::is_same_v<CommonFloat_t<double, float>, double>);
		REQUIRE(std::is_same_v<CommonFloat_t<double, double>, double>);
	}
}

# endif
