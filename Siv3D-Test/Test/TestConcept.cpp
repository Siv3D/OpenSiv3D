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

struct CustomAddressOf
{
	int n[2];

	const int* operator& () const
	{
		return &n[1];
	}
};

TEST(Concept, HasUnaryPlus)
{
	EXPECT_EQ(Concept::HasUnaryPlus<int32>::value, true);
	EXPECT_EQ(Concept::HasUnaryPlus<float>::value, true);
	EXPECT_EQ(Concept::HasUnaryPlus<String>::value, false);
	EXPECT_EQ(Concept::HasUnaryPlus<BigInt>::value, true);
	EXPECT_EQ(Concept::HasUnaryPlus<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasUnaryPlus<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasUnaryPlus<BinaryReader>::value, false);
}

TEST(Concept, HasNegate)
{
	EXPECT_EQ(Concept::HasNegate<int32>::value, true);
	EXPECT_EQ(Concept::HasNegate<float>::value, true);
	EXPECT_EQ(Concept::HasNegate<String>::value, false);
	EXPECT_EQ(Concept::HasNegate<BigInt>::value, true);
	EXPECT_EQ(Concept::HasNegate<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasNegate<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasNegate<BinaryReader>::value, false);
}

TEST(Concept, HasPreIncrement)
{
	EXPECT_EQ(Concept::HasPreIncrement<int32>::value, true);
	EXPECT_EQ(Concept::HasPreIncrement<float>::value, true);
	EXPECT_EQ(Concept::HasPreIncrement<String>::value, false);
	EXPECT_EQ(Concept::HasPreIncrement<BigInt>::value, true);
	EXPECT_EQ(Concept::HasPreIncrement<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasPreIncrement<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasPreIncrement<BinaryReader>::value, false);
}

TEST(Concept, HasPreDecrement)
{
	EXPECT_EQ(Concept::HasPreDecrement<int32>::value, true);
	EXPECT_EQ(Concept::HasPreDecrement<float>::value, true);
	EXPECT_EQ(Concept::HasPreDecrement<String>::value, false);
	EXPECT_EQ(Concept::HasPreDecrement<BigInt>::value, true);
	EXPECT_EQ(Concept::HasPreDecrement<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasPreDecrement<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasPreDecrement<BinaryReader>::value, false);
}

TEST(Concept, HasPostIncrement)
{
	EXPECT_EQ(Concept::HasPostIncrement<int32>::value, true);
	EXPECT_EQ(Concept::HasPostIncrement<float>::value, true);
	EXPECT_EQ(Concept::HasPostIncrement<String>::value, false);
	EXPECT_EQ(Concept::HasPostIncrement<BigInt>::value, true);
	EXPECT_EQ(Concept::HasPostIncrement<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasPostIncrement<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasPostIncrement<BinaryReader>::value, false);
}

TEST(Concept, HasOperatorBool)
{
	EXPECT_EQ(Concept::HasOperatorBool<int32>::value, true);
	EXPECT_EQ(Concept::HasOperatorBool<float>::value, true);
	EXPECT_EQ(Concept::HasOperatorBool<String>::value, false);
	EXPECT_EQ(Concept::HasOperatorBool<BigInt>::value, true);
	EXPECT_EQ(Concept::HasOperatorBool<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasOperatorBool<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasOperatorBool<BinaryReader>::value, true);
}

TEST(Concept, HasLogicalNot)
{
	EXPECT_EQ(Concept::HasLogicalNot<int32>::value, true);
	EXPECT_EQ(Concept::HasLogicalNot<float>::value, true);
	EXPECT_EQ(Concept::HasLogicalNot<String>::value, false);
	EXPECT_EQ(Concept::HasLogicalNot<BigInt>::value, true);
	EXPECT_EQ(Concept::HasLogicalNot<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasLogicalNot<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasLogicalNot<BinaryReader>::value, true);
}

TEST(Concept, HasComplement)
{
	EXPECT_EQ(Concept::HasComplement<int32>::value, true);
	EXPECT_EQ(Concept::HasComplement<float>::value, false);
	EXPECT_EQ(Concept::HasComplement<String>::value, false);
	EXPECT_EQ(Concept::HasComplement<BigInt>::value, false);
	EXPECT_EQ(Concept::HasComplement<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasComplement<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasComplement<BinaryReader>::value, false);
}

TEST(Concept, HasAddressOf)
{
	EXPECT_EQ(Concept::HasAddressOf<int32>::value, true);
	EXPECT_EQ(Concept::HasAddressOf<float>::value, true);
	EXPECT_EQ(Concept::HasAddressOf<String>::value, true);
	EXPECT_EQ(Concept::HasAddressOf<BigInt>::value, true);
	EXPECT_EQ(Concept::HasAddressOf<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasAddressOf<Array<Date>>::value, true);
	EXPECT_EQ(Concept::HasAddressOf<BinaryReader>::value, true);

	EXPECT_EQ(Concept::HasAddressOf<CustomAddressOf>::value, true);
}

TEST(Concept, HasOverloadedAddressOf)
{
	EXPECT_EQ(Concept::HasOverloadedAddressOf<int32>::value, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf<float>::value, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf<String>::value, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf<BigInt>::value, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf<BinaryReader>::value, false);

	EXPECT_EQ(Concept::HasOverloadedAddressOf<CustomAddressOf>::value, true);
}

TEST(Concept, HasPostDecrement)
{
	EXPECT_EQ(Concept::HasPostDecrement<int32>::value, true);
	EXPECT_EQ(Concept::HasPostDecrement<float>::value, true);
	EXPECT_EQ(Concept::HasPostDecrement<String>::value, false);
	EXPECT_EQ(Concept::HasPostDecrement<BigInt>::value, true);
	EXPECT_EQ(Concept::HasPostDecrement<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasPostDecrement<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasPostDecrement<BinaryReader>::value, false);
}

TEST(Concept, HasPlus)
{
	EXPECT_EQ(Concept::HasPlus<int32>::value, true);
	EXPECT_EQ(Concept::HasPlus<float>::value, true);
	EXPECT_EQ(Concept::HasPlus<String>::value, true);
	EXPECT_EQ(Concept::HasPlus<BigInt>::value, true);
	EXPECT_EQ(Concept::HasPlus<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasPlus<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasPlus<BinaryReader>::value, false);
}

TEST(Concept, HasMinus)
{
	EXPECT_EQ(Concept::HasMinus<int32>::value, true);
	EXPECT_EQ(Concept::HasMinus<float>::value, true);
	EXPECT_EQ(Concept::HasMinus<String>::value, false);
	EXPECT_EQ(Concept::HasMinus<BigInt>::value, true);
	EXPECT_EQ(Concept::HasMinus<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasMinus<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasMinus<BinaryReader>::value, false);
}

TEST(Concept, HasMultiply)
{
	EXPECT_EQ(Concept::HasMultiply<int32>::value, true);
	EXPECT_EQ(Concept::HasMultiply<float>::value, true);
	EXPECT_EQ(Concept::HasMultiply<String>::value, false);
	EXPECT_EQ(Concept::HasMultiply<BigInt>::value, true);
	EXPECT_EQ(Concept::HasMultiply<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasMultiply<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasMultiply<BinaryReader>::value, false);
}

TEST(Concept, HasDivide)
{
	EXPECT_EQ(Concept::HasDivide<int32>::value, true);
	EXPECT_EQ(Concept::HasDivide<float>::value, true);
	EXPECT_EQ(Concept::HasDivide<String>::value, false);
	EXPECT_EQ(Concept::HasDivide<BigInt>::value, true);
	EXPECT_EQ(Concept::HasDivide<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasDivide<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasDivide<BinaryReader>::value, false);
}

TEST(Concept, HasModulus)
{
	EXPECT_EQ(Concept::HasModulus<int32>::value, true);
	EXPECT_EQ(Concept::HasModulus<float>::value, false);
	EXPECT_EQ(Concept::HasModulus<String>::value, false);
	EXPECT_EQ(Concept::HasModulus<BigInt>::value, true);
	EXPECT_EQ(Concept::HasModulus<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasModulus<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasModulus<BinaryReader>::value, false);
}


TEST(Concept, HasPlusAssign)
{
	EXPECT_EQ(Concept::HasPlusAssign<int32>::value, true);
	EXPECT_EQ(Concept::HasPlusAssign<float>::value, true);
	EXPECT_EQ(Concept::HasPlusAssign<String>::value, true);
	EXPECT_EQ(Concept::HasPlusAssign<BigInt>::value, true);
	EXPECT_EQ(Concept::HasPlusAssign<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasPlusAssign<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasPlusAssign<BinaryReader>::value, false);
}

TEST(Concept, HasMinusAssign)
{
	EXPECT_EQ(Concept::HasMinusAssign<int32>::value, true);
	EXPECT_EQ(Concept::HasMinusAssign<float>::value, true);
	EXPECT_EQ(Concept::HasMinusAssign<String>::value, false);
	EXPECT_EQ(Concept::HasMinusAssign<BigInt>::value, true);
	EXPECT_EQ(Concept::HasMinusAssign<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasMinusAssign<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasMinusAssign<BinaryReader>::value, false);
}

TEST(Concept, HasMultiplyAssign)
{
	EXPECT_EQ(Concept::HasMultiplyAssign<int32>::value, true);
	EXPECT_EQ(Concept::HasMultiplyAssign<float>::value, true);
	EXPECT_EQ(Concept::HasMultiplyAssign<String>::value, false);
	EXPECT_EQ(Concept::HasMultiplyAssign<BigInt>::value, true);
	EXPECT_EQ(Concept::HasMultiplyAssign<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasMultiplyAssign<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasMultiplyAssign<BinaryReader>::value, false);
}

TEST(Concept, HasDivideAssign)
{
	EXPECT_EQ(Concept::HasDivideAssign<int32>::value, true);
	EXPECT_EQ(Concept::HasDivideAssign<float>::value, true);
	EXPECT_EQ(Concept::HasDivideAssign<String>::value, false);
	EXPECT_EQ(Concept::HasDivideAssign<BigInt>::value, true);
	EXPECT_EQ(Concept::HasDivideAssign<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasDivideAssign<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasDivideAssign<BinaryReader>::value, false);
}

TEST(Concept, HasModulesAssign)
{
	EXPECT_EQ(Concept::HasModulusAssign<int32>::value, true);
	EXPECT_EQ(Concept::HasModulusAssign<float>::value, false);
	EXPECT_EQ(Concept::HasModulusAssign<String>::value, false);
	EXPECT_EQ(Concept::HasModulusAssign<BigInt>::value, true);
	EXPECT_EQ(Concept::HasModulusAssign<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasModulusAssign<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasModulusAssign<BinaryReader>::value, false);
}

TEST(Concept, HasEqualTo)
{
	EXPECT_EQ(Concept::HasEqualTo<int32>::value, true);
	EXPECT_EQ(Concept::HasEqualTo<float>::value, true);
	EXPECT_EQ(Concept::HasEqualTo<String>::value, true);
	EXPECT_EQ(Concept::HasEqualTo<BigInt>::value, true);
	EXPECT_EQ(Concept::HasEqualTo<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasEqualTo<Array<Date>>::value, true);
	EXPECT_EQ(Concept::HasEqualTo<BinaryReader>::value, false);
}

TEST(Concept, HasNotEqualTo)
{
	EXPECT_EQ(Concept::HasNotEqualTo<int32>::value, true);
	EXPECT_EQ(Concept::HasNotEqualTo<float>::value, true);
	EXPECT_EQ(Concept::HasNotEqualTo<String>::value, true);
	EXPECT_EQ(Concept::HasNotEqualTo<BigInt>::value, true);
	EXPECT_EQ(Concept::HasNotEqualTo<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasNotEqualTo<Array<Date>>::value, true);
	EXPECT_EQ(Concept::HasNotEqualTo<BinaryReader>::value, false);
}

TEST(Concept, HasLessThan)
{
	EXPECT_EQ(Concept::HasLessThan<int32>::value, true);
	EXPECT_EQ(Concept::HasLessThan<float>::value, true);
	EXPECT_EQ(Concept::HasLessThan<String>::value, true);
	EXPECT_EQ(Concept::HasLessThan<BigInt>::value, true);
	EXPECT_EQ(Concept::HasLessThan<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasLessThan<Array<Date>>::value, true);
	EXPECT_EQ(Concept::HasLessThan<BinaryReader>::value, false);
}

TEST(Concept, HasLessThanEqual)
{
	EXPECT_EQ(Concept::HasLessThanEqual<int32>::value, true);
	EXPECT_EQ(Concept::HasLessThanEqual<float>::value, true);
	EXPECT_EQ(Concept::HasLessThanEqual<String>::value, true);
	EXPECT_EQ(Concept::HasLessThanEqual<BigInt>::value, true);
	EXPECT_EQ(Concept::HasLessThanEqual<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasLessThanEqual<Array<Date>>::value, true);
	EXPECT_EQ(Concept::HasLessThanEqual<BinaryReader>::value, false);
}

TEST(Concept, HasGreaterThan)
{
	EXPECT_EQ(Concept::HasGreaterThan<int32>::value, true);
	EXPECT_EQ(Concept::HasGreaterThan<float>::value, true);
	EXPECT_EQ(Concept::HasGreaterThan<String>::value, true);
	EXPECT_EQ(Concept::HasGreaterThan<BigInt>::value, true);
	EXPECT_EQ(Concept::HasGreaterThan<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasGreaterThan<Array<Date>>::value, true);
	EXPECT_EQ(Concept::HasGreaterThan<BinaryReader>::value, false);
}

TEST(Concept, HasGreaterThanEqual)
{
	EXPECT_EQ(Concept::HasGreaterThanEqual<int32>::value, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual<float>::value, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual<String>::value, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual<BigInt>::value, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual<Array<Date>>::value, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual<BinaryReader>::value, false);
}

TEST(Concept, HasBitwiseAnd)
{
	EXPECT_EQ(Concept::HasBitwiseAnd<int32>::value, true);
	EXPECT_EQ(Concept::HasBitwiseAnd<float>::value, false);
	EXPECT_EQ(Concept::HasBitwiseAnd<String>::value, false);
	EXPECT_EQ(Concept::HasBitwiseAnd<BigInt>::value, true);
	EXPECT_EQ(Concept::HasBitwiseAnd<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseAnd<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseAnd<BinaryReader>::value, false);
}

TEST(Concept, HasBitwiseOr)
{
	EXPECT_EQ(Concept::HasBitwiseOr<int32>::value, true);
	EXPECT_EQ(Concept::HasBitwiseOr<float>::value, false);
	EXPECT_EQ(Concept::HasBitwiseOr<String>::value, false);
	EXPECT_EQ(Concept::HasBitwiseOr<BigInt>::value, true);
	EXPECT_EQ(Concept::HasBitwiseOr<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseOr<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseOr<BinaryReader>::value, false);
}

TEST(Concept, HasBitwiseXor)
{
	EXPECT_EQ(Concept::HasBitwiseXor<int32>::value, true);
	EXPECT_EQ(Concept::HasBitwiseXor<float>::value, false);
	EXPECT_EQ(Concept::HasBitwiseXor<String>::value, false);
	EXPECT_EQ(Concept::HasBitwiseXor<BigInt>::value, true);
	EXPECT_EQ(Concept::HasBitwiseXor<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseXor<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseXor<BinaryReader>::value, false);
}

TEST(Concept, HasBitwiseAndAssign)
{
	EXPECT_EQ(Concept::HasBitwiseAndAssign<int32>::value, true);
	EXPECT_EQ(Concept::HasBitwiseAndAssign<float>::value, false);
	EXPECT_EQ(Concept::HasBitwiseAndAssign<String>::value, false);
	EXPECT_EQ(Concept::HasBitwiseAndAssign<BigInt>::value, true);
	EXPECT_EQ(Concept::HasBitwiseAndAssign<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseAndAssign<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseAndAssign<BinaryReader>::value, false);
}

TEST(Concept, HasBitwiseOrAssign)
{
	EXPECT_EQ(Concept::HasBitwiseOrAssign<int32>::value, true);
	EXPECT_EQ(Concept::HasBitwiseOrAssign<float>::value, false);
	EXPECT_EQ(Concept::HasBitwiseOrAssign<String>::value, false);
	EXPECT_EQ(Concept::HasBitwiseOrAssign<BigInt>::value, true);
	EXPECT_EQ(Concept::HasBitwiseOrAssign<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseOrAssign<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseOrAssign<BinaryReader>::value, false);
}

TEST(Concept, HasBitwiseXorAssign)
{
	EXPECT_EQ(Concept::HasBitwiseXorAssign<int32>::value, true);
	EXPECT_EQ(Concept::HasBitwiseXorAssign<float>::value, false);
	EXPECT_EQ(Concept::HasBitwiseXorAssign<String>::value, false);
	EXPECT_EQ(Concept::HasBitwiseXorAssign<BigInt>::value, true);
	EXPECT_EQ(Concept::HasBitwiseXorAssign<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseXorAssign<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasBitwiseXorAssign<BinaryReader>::value, false);
}

TEST(Concept, HasLeftShift)
{
	EXPECT_EQ(Concept::HasLeftShift<int32>::value, true);
	EXPECT_EQ(Concept::HasLeftShift<float>::value, false);
	EXPECT_EQ(Concept::HasLeftShift<String>::value, false);
	EXPECT_EQ(Concept::HasLeftShift<BigInt>::value, false);
	EXPECT_EQ(Concept::HasLeftShift<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasLeftShift<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasLeftShift<BinaryReader>::value, false);

	const bool b = Concept::HasLeftShift<String, wchar>::value;
	EXPECT_EQ(b, true);
}

TEST(Concept, HasRightShift)
{
	EXPECT_EQ(Concept::HasRightShift<int32>::value, true);
	EXPECT_EQ(Concept::HasRightShift<float>::value, false);
	EXPECT_EQ(Concept::HasRightShift<String>::value, false);
	EXPECT_EQ(Concept::HasRightShift<BigInt>::value, false);
	EXPECT_EQ(Concept::HasRightShift<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasRightShift<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasRightShift<BinaryReader>::value, false);
}

TEST(Concept, HasLeftShiftAssign)
{
	EXPECT_EQ(Concept::HasLeftShiftAssign<int32>::value, true);
	EXPECT_EQ(Concept::HasLeftShiftAssign<float>::value, false);
	EXPECT_EQ(Concept::HasLeftShiftAssign<String>::value, false);
	EXPECT_EQ(Concept::HasLeftShiftAssign<BigInt>::value, false);
	EXPECT_EQ(Concept::HasLeftShiftAssign<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasLeftShiftAssign<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasLeftShiftAssign<BinaryReader>::value, false);
}

TEST(Concept, HasRightShiftAssign)
{
	EXPECT_EQ(Concept::HasRightShiftAssign<int32>::value, true);
	EXPECT_EQ(Concept::HasRightShiftAssign<float>::value, false);
	EXPECT_EQ(Concept::HasRightShiftAssign<String>::value, false);
	EXPECT_EQ(Concept::HasRightShiftAssign<BigInt>::value, false);
	EXPECT_EQ(Concept::HasRightShiftAssign<Optional<double>>::value, false);
	EXPECT_EQ(Concept::HasRightShiftAssign<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasRightShiftAssign<BinaryReader>::value, false);
}

TEST(Concept, HasLogicalAnd)
{
	EXPECT_EQ(Concept::HasLogicalAnd<int32>::value, true);
	EXPECT_EQ(Concept::HasLogicalAnd<float>::value, true);
	EXPECT_EQ(Concept::HasLogicalAnd<String>::value, false);
	EXPECT_EQ(Concept::HasLogicalAnd<BigInt>::value, true);
	EXPECT_EQ(Concept::HasLogicalAnd<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasLogicalAnd<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasLogicalAnd<BinaryReader>::value, true);
}

TEST(Concept, HasLogicalOr)
{
	EXPECT_EQ(Concept::HasLogicalOr<int32>::value, true);
	EXPECT_EQ(Concept::HasLogicalOr<float>::value, true);
	EXPECT_EQ(Concept::HasLogicalOr<String>::value, false);
	EXPECT_EQ(Concept::HasLogicalOr<BigInt>::value, true);
	EXPECT_EQ(Concept::HasLogicalOr<Optional<double>>::value, true);
	EXPECT_EQ(Concept::HasLogicalOr<Array<Date>>::value, false);
	EXPECT_EQ(Concept::HasLogicalOr<BinaryReader>::value, true);
}
