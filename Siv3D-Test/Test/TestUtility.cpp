//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Siv3DTest.hpp"

# if defined(SIV3D_DO_TEST)

using namespace s3d;

TEST(Utility, Max)
{
	EXPECT_EQ(Max(10, 20), 20);
	EXPECT_EQ(Max(20, 10), 20);
	EXPECT_EQ(Max(20, 20), 20);

	EXPECT_EQ(Max(-10.0, -20.0), -10.0);
	EXPECT_EQ(Max(-20.0, -10.0), -10.0);
	EXPECT_EQ(Max(-20.0, -20.0), -20.0);

	EXPECT_EQ(Max(String(L"AAA"), String(L"BBB")), String(L"BBB"));
	EXPECT_EQ(Max(String(L"BBB"), String(L"AAA")), String(L"BBB"));
	EXPECT_EQ(Max(String(L"BBB"), String(L"BBB")), String(L"BBB"));

	EXPECT_EQ(Max({ 10, 20, 30, 40 }), 40);
	EXPECT_EQ(Max({ 40, 30, 20, 10 }), 40);
	EXPECT_EQ(Max({ 40, 40, 40, 40 }), 40);

	EXPECT_EQ(Max({ -10.0, -20.0, -30.0, -40.0 }), -10.0);
	EXPECT_EQ(Max({ -40.0, -30.0, -20.0, -10.0 }), -10.0);
	EXPECT_EQ(Max({ -40.0, -40.0, -40.0, -40.0 }), -40.0);

	EXPECT_EQ(Max({ String(L"AAA"), String(L"BBB"), String(L"CCC"), String(L"DDD") }), String(L"DDD"));
	EXPECT_EQ(Max({ String(L"DDD"), String(L"CCC"), String(L"BBB"), String(L"AAA") }), String(L"DDD"));
	EXPECT_EQ(Max({ String(L"DDD"), String(L"DDD"), String(L"DDD"), String(L"DDD") }), String(L"DDD"));
}

TEST(Utility, Min)
{
	EXPECT_EQ(Min(10, 20), 10);
	EXPECT_EQ(Min(20, 10), 10);
	EXPECT_EQ(Min(20, 20), 20);

	EXPECT_EQ(Min(-10.0, -20.0), -20.0);
	EXPECT_EQ(Min(-20.0, -10.0), -20.0);
	EXPECT_EQ(Min(-20.0, -20.0), -20.0);

	EXPECT_EQ(Min(String(L"AAA"), String(L"BBB")), String(L"AAA"));
	EXPECT_EQ(Min(String(L"BBB"), String(L"AAA")), String(L"AAA"));
	EXPECT_EQ(Min(String(L"BBB"), String(L"BBB")), String(L"BBB"));

	EXPECT_EQ(Min({ 10, 20, 30, 40 }), 10);
	EXPECT_EQ(Min({ 40, 30, 20, 10 }), 10);
	EXPECT_EQ(Min({ 40, 40, 40, 40 }), 40);

	EXPECT_EQ(Min({ -10.0, -20.0, -30.0, -40.0 }), -40.0);
	EXPECT_EQ(Min({ -40.0, -30.0, -20.0, -10.0 }), -40.0);
	EXPECT_EQ(Min({ -40.0, -40.0, -40.0, -40.0 }), -40.0);

	EXPECT_EQ(Min({ String(L"AAA"), String(L"BBB"), String(L"CCC"), String(L"DDD") }), String(L"AAA"));
	EXPECT_EQ(Min({ String(L"DDD"), String(L"CCC"), String(L"BBB"), String(L"AAA") }), String(L"AAA"));
	EXPECT_EQ(Min({ String(L"DDD"), String(L"DDD"), String(L"DDD"), String(L"DDD") }), String(L"DDD"));
}

TEST(Utility, Clamp)
{
	EXPECT_EQ(Clamp(10, 20, 30), 20);
	EXPECT_EQ(Clamp(30, 10, 20), 20);
	EXPECT_EQ(Clamp(20, 20, 20), 20);

	EXPECT_EQ(Clamp(10.0, 20.0, 30.0), 20.0);
	EXPECT_EQ(Clamp(30.0, 10.0, 20.0), 20.0);
	EXPECT_EQ(Clamp(20.0, 20.0, 20.0), 20.0);

	EXPECT_EQ(Clamp(String(L"AAA"), String(L"BBB"), String(L"CCC")), String(L"BBB"));
	EXPECT_EQ(Clamp(String(L"CCC"), String(L"AAA"), String(L"BBB")), String(L"BBB"));
	EXPECT_EQ(Clamp(String(L"BBB"), String(L"BBB"), String(L"BBB")), String(L"BBB"));
}

TEST(Utility, InRange)
{

}

TEST(Utility, Erase_if)
{

}

TEST(Utility, Erase)
{

}

TEST(Utility, AllOf)
{

}

TEST(Utility, AnyOf)
{

}

TEST(Utility, NoneOf)
{

}

TEST(Utility, Sample)
{

}

TEST(Utility, AddressOf)
{

}

# endif
