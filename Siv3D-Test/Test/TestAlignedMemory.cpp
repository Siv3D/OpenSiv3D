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


struct alignas(16) Data16
{
	float v[4];
};

struct alignas(32) Data32
{
	float v[8];
};

struct alignas(64) Data64
{
	float v[4];
};

TEST(AlignedMemory, AlignedMalloc_0)
{
	{
		uint8* p = AlignedMalloc<uint8>(0);
		AlignedFree(p);
	}
	
	{
		uint16* p = AlignedMalloc<uint16>(0);
		AlignedFree(p);
	}
	
	{
		uint32* p = AlignedMalloc<uint32>(0);
		AlignedFree(p);
	}
	
	{
		uint64* p = AlignedMalloc<uint64>(0);
		AlignedFree(p);
	}
	
	{
		float* p = AlignedMalloc<float>(0);
		AlignedFree(p);
	}
	
	{
		double* p = AlignedMalloc<double>(0);
		AlignedFree(p);
	}
	
	{
		Data16* p = AlignedMalloc<Data16>(0);
		AlignedFree(p);
	}
	
	{
		Data32* p = AlignedMalloc<Data32>(0);
		AlignedFree(p);
	}
	
	{
		Data64* p = AlignedMalloc<Data64>(0);
		AlignedFree(p);
	}
}

TEST(AlignedMemory, AlignedMalloc_1)
{
	{
		uint8* p = AlignedMalloc<uint8>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedFree(p);
	}
	
	{
		uint16* p = AlignedMalloc<uint16>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedFree(p);
	}

	{
		uint32* p = AlignedMalloc<uint32>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedFree(p);
	}

	{
		uint64* p = AlignedMalloc<uint64>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 8));
		AlignedFree(p);
	}

	{
		float* p = AlignedMalloc<float>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedFree(p);
	}

	{
		double* p = AlignedMalloc<double>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 8));
		AlignedFree(p);
	}

	{
		Data16* p = AlignedMalloc<Data16>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 16));
		AlignedFree(p);
	}

	{
		Data32* p = AlignedMalloc<Data32>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 32));
		AlignedFree(p);
	}

	{
		Data64* p = AlignedMalloc<Data64>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 64));
		AlignedFree(p);
	}
}

TEST(AlignedMemory, AlignedMalloc_3)
{
	{
		uint8* p = AlignedMalloc<uint8>(3);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedFree(p);
	}
	
	{
		uint16* p = AlignedMalloc<uint16>(3);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedFree(p);
	}
	
	{
		uint32* p = AlignedMalloc<uint32>(3);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedFree(p);
	}
	
	{
		uint64* p = AlignedMalloc<uint64>(3);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 8));
		AlignedFree(p);
	}
	
	{
		float* p = AlignedMalloc<float>(3);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedFree(p);
	}
	
	{
		double* p = AlignedMalloc<double>(3);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 8));
		AlignedFree(p);
	}
	
	{
		Data16* p = AlignedMalloc<Data16>(3);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 16));
		AlignedFree(p);
	}
	
	{
		Data32* p = AlignedMalloc<Data32>(3);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 32));
		AlignedFree(p);
	}
	
	{
		Data64* p = AlignedMalloc<Data64>(3);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 64));
		AlignedFree(p);
	}
}

TEST(AlignedMemory, AlignedNew)
{
	{
		uint8* p = AlignedNew<uint8>(0);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedDelete(p);
	}
	
	{
		uint16* p = AlignedNew<uint16>(0);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedDelete(p);
	}
	
	{
		uint32* p = AlignedNew<uint32>(0);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedDelete(p);
	}
	
	{
		uint64* p = AlignedNew<uint64>(0);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 8));
		AlignedDelete(p);
	}
	
	{
		float* p = AlignedNew<float>(0);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, SIV3D_ALLOCATOR_MIN_ALIGNMENT));
		AlignedDelete(p);
	}
	
	{
		double* p = AlignedNew<double>(0);
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 8));
		AlignedDelete(p);
	}
	
	{
		Data16* p = AlignedNew<Data16>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 16));
		AlignedDelete(p);
	}
	
	{
		Data32* p = AlignedNew<Data32>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 32));
		AlignedDelete(p);
	}
	
	{
		Data64* p = AlignedNew<Data64>();
		EXPECT_NE(p, nullptr);
		EXPECT_TRUE(IsAligned(p, 64));
		AlignedDelete(p);
	}
}

TEST(AlignedMemory, HasAlignment)
{
	EXPECT_EQ(HasAlignment<int32>::value, false);
	EXPECT_EQ(HasAlignment<double>::value, false);
	EXPECT_EQ(HasAlignment<Data16>::value, SIV3D_ALLOCATOR_MIN_ALIGNMENT < 16);
	EXPECT_EQ(HasAlignment<Data32>::value, SIV3D_ALLOCATOR_MIN_ALIGNMENT < 32);
	EXPECT_EQ(HasAlignment<Data64>::value, SIV3D_ALLOCATOR_MIN_ALIGNMENT < 64);
}

TEST(AlignedMemory, MakeUnique)
{
	{
		auto p = MakeUnique<uint8>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), SIV3D_ALLOCATOR_MIN_ALIGNMENT));
	}
	
	{
		auto p = MakeUnique<uint16>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), SIV3D_ALLOCATOR_MIN_ALIGNMENT));
	}
	
	{
		auto p = MakeUnique<uint32>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), SIV3D_ALLOCATOR_MIN_ALIGNMENT));
	}
	
	{
		auto p = MakeUnique<uint64>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), SIV3D_ALLOCATOR_MIN_ALIGNMENT));
	}
	
	{
		auto p = MakeUnique<float>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), SIV3D_ALLOCATOR_MIN_ALIGNMENT));
	}
	
	{
		auto p = MakeUnique<double>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), SIV3D_ALLOCATOR_MIN_ALIGNMENT));
	}
	
	{
		auto p = MakeUnique<Data16>();
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), SIV3D_ALLOCATOR_MIN_ALIGNMENT));
	}
	
	{
		auto p = MakeUnique<Data32>();
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), SIV3D_ALLOCATOR_MIN_ALIGNMENT));
	}
	
	{
		auto p = MakeUnique<Data64>();
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), SIV3D_ALLOCATOR_MIN_ALIGNMENT));
	}
}

TEST(AlignedMemory, MakeShared)
{
	{
		auto p = MakeShared<uint8>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), 1));
	}
	
	{
		auto p = MakeShared<uint16>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), 2));
	}
	
	{
		auto p = MakeShared<uint32>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), 4));
	}
	
	{
		auto p = MakeShared<uint64>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), 8));
	}
	
	{
		auto p = MakeShared<float>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), 4));
	}
	
	{
		auto p = MakeShared<double>(0);
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), 8));
	}
	
	{
		auto p = MakeShared<Data16>();
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), 16));
	}
	
	{
		auto p = MakeShared<Data32>();
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), 32));
	}
	
	{
		auto p = MakeShared<Data64>();
		EXPECT_NE(p.get(), nullptr);
		EXPECT_TRUE(IsAligned(p.get(), 64));
	}
}

# endif
