//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include <gtest/gtest.h>

using namespace s3d;

TEST(Array, MemberTypes)
{
	EXPECT_EQ(typeid(typename Array<int32>::value_type),				typeid(int32));
	EXPECT_EQ(typeid(typename Array<int32>::pointer),					typeid(int32*));
	EXPECT_EQ(typeid(typename Array<int32>::const_pointer),				typeid(const int32*));
	EXPECT_EQ(typeid(typename Array<int32>::reference),					typeid(int32&));
	EXPECT_EQ(typeid(typename Array<int32>::const_reference),			typeid(const int32&));
	EXPECT_EQ(typeid(typename Array<int32>::iterator),					typeid(typename std::vector<int32>::iterator));
	EXPECT_EQ(typeid(typename Array<int32>::const_iterator),			typeid(typename std::vector<int32>::const_iterator));
	EXPECT_EQ(typeid(typename Array<int32>::reverse_iterator),			typeid(typename std::vector<int32>::reverse_iterator));
	EXPECT_EQ(typeid(typename Array<int32>::const_reverse_iterator),	typeid(typename std::vector<int32>::const_reverse_iterator));
	EXPECT_EQ(typeid(typename Array<int32>::size_type),					typeid(typename std::vector<int32>::size_type));
	EXPECT_EQ(typeid(typename Array<int32>::difference_type),			typeid(typename std::vector<int32>::difference_type));
	EXPECT_EQ(typeid(typename Array<int32>::allocator_type),			typeid(typename DefaultAllocator<int32>::type));
	EXPECT_EQ(typeid(typename Array<double>::allocator_type),			typeid(typename DefaultAllocator<double>::type));
    
# if defined(SIV3D_TARGET_WINDOWS)
	EXPECT_EQ(typeid(typename Array<__m128>::allocator_type),			typeid(typename DefaultAllocator<__m128>::type));
	EXPECT_EQ(typeid(typename Array<__m256>::allocator_type),			typeid(typename DefaultAllocator<__m256>::type));
# endif
}

TEST(Array, int32_Empty)
{
	const Array<int32> v;
}

TEST(Array, int32)
{
	Array<int32> v{1, 2, 3, 4};

	EXPECT_EQ(typeid(v.get_allocator()),	typeid(typename DefaultAllocator<int32>::type));
	EXPECT_EQ(v.at(0),			1);
	EXPECT_EQ(v.at(1),			2);
	EXPECT_EQ(v.at(2),			3);
	EXPECT_EQ(v.at(3),			4);
	EXPECT_THROW(v.at(4),		std::out_of_range);
	EXPECT_EQ(v[0],				1);
	EXPECT_EQ(v[1],				2);
	EXPECT_EQ(v[2],				3);
	EXPECT_EQ(v[3],				4);
	EXPECT_EQ(v.front(),		1);
	EXPECT_EQ(v.back(),			4);
	EXPECT_EQ(*v.data(),		1);
	EXPECT_EQ(*v.begin(),		1);
	EXPECT_EQ(*(v.end() - 1),	4);
	EXPECT_EQ(*v.cbegin(),		1);
	EXPECT_EQ(*(v.cend() - 1),	4);
	EXPECT_EQ(*v.rbegin(),		4);
	EXPECT_EQ(*(v.rend() - 1),	1);
	EXPECT_EQ(*v.crbegin(),		4);
	EXPECT_EQ(*(v.crend() - 1),	1);
	EXPECT_EQ(v.empty(),		false);
	EXPECT_EQ(v.size(),			4);
	EXPECT_EQ(v.count(),		4);
	EXPECT_EQ(v.isEmpty(),		false);
	EXPECT_EQ(v.size_bytes(),	sizeof(int32) * 4);
	EXPECT_GE(v.capacity(),		(size_t)4);
	
	{
		Array<int32> v2{ 1, 2, 3, 4 };
		v2.reserve(2000);
		EXPECT_GE(v2.capacity(),	(size_t)2000);
		v2.shrink_to_fit();
		EXPECT_LE(v2.capacity(),	(size_t)2000);
		v2.clear();
		EXPECT_EQ(v2.size(),		0);

		v2.insert(v2.end(), 2);
		v2.insert(v2.begin(), 1);
		v2.push_back(3);
		v2.emplace_back(4);
		v2.emplace(v2.end(), 5);
		v2.push_back(6);
		v2.push_back(7);
		v2.erase(v2.end() - 2);
		v2.pop_back();

		Array<int32> v3{ 1, 2, 3, 4, 5 };
		Array<int32> v4{ 1,2,3 };
		Array<int32> v5 = v4;
		EXPECT_EQ(v2,	v3);

		v2.swap(v4);
		EXPECT_EQ(v2,	v5);
		EXPECT_EQ(v4,	v3);

		v2.resize(50);
		EXPECT_EQ(v2.size(),	50);

		v2.resize(100, 123);
		EXPECT_EQ(v2.size(),	100);
		EXPECT_EQ(v2[99],		123);

		v2 << 234 << 345;
		EXPECT_EQ(v2[100],		234);
		EXPECT_EQ(v2[101],		345);
	}

	EXPECT_EQ(v.all(), true);
	EXPECT_EQ(v.all(IsOdd), false);
	const auto f = [](int n) { return n - 4; };
	EXPECT_EQ(v.all(f), false);



	const Array<int32> vg(10, Arg::generator = RNG(1, 6));
}

TEST(Array, int32_const)
{

}

TEST(Array, double)
{

}

TEST(Array, double_const)
{

}

TEST(Array, m128)
{
# if defined(SIV3D_TARGET_WINDOWS)

	Array<__m128> v(100);
	EXPECT_EQ(size_t(&v[0]) % 16, 0);

	v.resize(333);
	EXPECT_EQ(size_t(&v[0]) % 16, 0);

	v.resize(777);
	EXPECT_EQ(size_t(&v[0]) % 16, 0);

# endif
}

TEST(Array, m128_const)
{

}

TEST(Array, bool)
{
    
}

TEST(Array, bool_empty)
{
    const Array<bool> v;
}

TEST(Array, bool_const)
{

}

TEST(Array, Point)
{

}

TEST(Array, Point_const)
{

}
