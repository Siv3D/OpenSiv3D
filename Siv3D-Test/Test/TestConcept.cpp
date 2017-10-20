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
	EXPECT_EQ(Concept::HasUnaryPlus_v<int32>, true);
	EXPECT_EQ(Concept::HasUnaryPlus_v<float>, true);
	EXPECT_EQ(Concept::HasUnaryPlus_v<String>, false);
	EXPECT_EQ(Concept::HasUnaryPlus_v<BigInt>, true);
	EXPECT_EQ(Concept::HasUnaryPlus_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasUnaryPlus_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasUnaryPlus_v<BinaryReader>, false);
}

TEST(Concept, HasNegate)
{
	EXPECT_EQ(Concept::HasNegate_v<int32>, true);
	EXPECT_EQ(Concept::HasNegate_v<float>, true);
	EXPECT_EQ(Concept::HasNegate_v<String>, false);
	EXPECT_EQ(Concept::HasNegate_v<BigInt>, true);
	EXPECT_EQ(Concept::HasNegate_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasNegate_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasNegate_v<BinaryReader>, false);
}

TEST(Concept, HasPreIncrement)
{
	EXPECT_EQ(Concept::HasPreIncrement_v<int32>, true);
	EXPECT_EQ(Concept::HasPreIncrement_v<float>, true);
	EXPECT_EQ(Concept::HasPreIncrement_v<String>, false);
	EXPECT_EQ(Concept::HasPreIncrement_v<BigInt>, true);
	EXPECT_EQ(Concept::HasPreIncrement_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasPreIncrement_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasPreIncrement_v<BinaryReader>, false);
}

TEST(Concept, HasPreDecrement)
{
	EXPECT_EQ(Concept::HasPreDecrement_v<int32>, true);
	EXPECT_EQ(Concept::HasPreDecrement_v<float>, true);
	EXPECT_EQ(Concept::HasPreDecrement_v<String>, false);
	EXPECT_EQ(Concept::HasPreDecrement_v<BigInt>, true);
	EXPECT_EQ(Concept::HasPreDecrement_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasPreDecrement_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasPreDecrement_v<BinaryReader>, false);
}

TEST(Concept, HasPostIncrement)
{
	EXPECT_EQ(Concept::HasPostIncrement_v<int32>, true);
	EXPECT_EQ(Concept::HasPostIncrement_v<float>, true);
	EXPECT_EQ(Concept::HasPostIncrement_v<String>, false);
	EXPECT_EQ(Concept::HasPostIncrement_v<BigInt>, true);
	EXPECT_EQ(Concept::HasPostIncrement_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasPostIncrement_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasPostIncrement_v<BinaryReader>, false);
}

TEST(Concept, HasOperatorBool)
{
	EXPECT_EQ(Concept::HasOperatorBool_v<int32>, true);
	EXPECT_EQ(Concept::HasOperatorBool_v<float>, true);
	EXPECT_EQ(Concept::HasOperatorBool_v<String>, true);
	EXPECT_EQ(Concept::HasOperatorBool_v<BigInt>, true);
	EXPECT_EQ(Concept::HasOperatorBool_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasOperatorBool_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasOperatorBool_v<BinaryReader>, true);
}

TEST(Concept, HasLogicalNot)
{
	EXPECT_EQ(Concept::HasLogicalNot_v<int32>, true);
	EXPECT_EQ(Concept::HasLogicalNot_v<float>, true);
	EXPECT_EQ(Concept::HasLogicalNot_v<String>, true);
	EXPECT_EQ(Concept::HasLogicalNot_v<BigInt>, true);
	EXPECT_EQ(Concept::HasLogicalNot_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasLogicalNot_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasLogicalNot_v<BinaryReader>, true);
}

TEST(Concept, HasComplement)
{
	EXPECT_EQ(Concept::HasComplement_v<int32>, true);
	EXPECT_EQ(Concept::HasComplement_v<float>, false);
	EXPECT_EQ(Concept::HasComplement_v<String>, false);
	EXPECT_EQ(Concept::HasComplement_v<BigInt>, false);
	EXPECT_EQ(Concept::HasComplement_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasComplement_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasComplement_v<BinaryReader>, false);
}

TEST(Concept, HasAddressOf)
{
	EXPECT_EQ(Concept::HasAddressOf_v<int32>, true);
	EXPECT_EQ(Concept::HasAddressOf_v<float>, true);
	EXPECT_EQ(Concept::HasAddressOf_v<String>, true);
	EXPECT_EQ(Concept::HasAddressOf_v<BigInt>, true);
	EXPECT_EQ(Concept::HasAddressOf_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasAddressOf_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasAddressOf_v<BinaryReader>, true);

	EXPECT_EQ(Concept::HasAddressOf_v<CustomAddressOf>, true);
}

TEST(Concept, HasOverloadedAddressOf)
{
	EXPECT_EQ(Concept::HasOverloadedAddressOf_v<int32>, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf_v<float>, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf_v<String>, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf_v<BigInt>, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasOverloadedAddressOf_v<BinaryReader>, false);

	EXPECT_EQ(Concept::HasOverloadedAddressOf_v<CustomAddressOf>, true);
}

TEST(Concept, HasPostDecrement)
{
	EXPECT_EQ(Concept::HasPostDecrement_v<int32>, true);
	EXPECT_EQ(Concept::HasPostDecrement_v<float>, true);
	EXPECT_EQ(Concept::HasPostDecrement_v<String>, false);
	EXPECT_EQ(Concept::HasPostDecrement_v<BigInt>, true);
	EXPECT_EQ(Concept::HasPostDecrement_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasPostDecrement_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasPostDecrement_v<BinaryReader>, false);
}

TEST(Concept, HasPlus)
{
	EXPECT_EQ(Concept::HasPlus_v<int32>, true);
	EXPECT_EQ(Concept::HasPlus_v<float>, true);
	EXPECT_EQ(Concept::HasPlus_v<String>, true);
	EXPECT_EQ(Concept::HasPlus_v<BigInt>, true);
	EXPECT_EQ(Concept::HasPlus_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasPlus_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasPlus_v<BinaryReader>, false);
}

TEST(Concept, HasMinus)
{
	EXPECT_EQ(Concept::HasMinus_v<int32>, true);
	EXPECT_EQ(Concept::HasMinus_v<float>, true);
	EXPECT_EQ(Concept::HasMinus_v<String>, false);
	EXPECT_EQ(Concept::HasMinus_v<BigInt>, true);
	EXPECT_EQ(Concept::HasMinus_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasMinus_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasMinus_v<BinaryReader>, false);
}

TEST(Concept, HasMultiply)
{
	EXPECT_EQ(Concept::HasMultiply_v<int32>, true);
	EXPECT_EQ(Concept::HasMultiply_v<float>, true);
	EXPECT_EQ(Concept::HasMultiply_v<String>, false);
	EXPECT_EQ(Concept::HasMultiply_v<BigInt>, true);
	EXPECT_EQ(Concept::HasMultiply_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasMultiply_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasMultiply_v<BinaryReader>, false);
}

TEST(Concept, HasDivide)
{
	EXPECT_EQ(Concept::HasDivide_v<int32>, true);
	EXPECT_EQ(Concept::HasDivide_v<float>, true);
	EXPECT_EQ(Concept::HasDivide_v<String>, false);
	EXPECT_EQ(Concept::HasDivide_v<BigInt>, true);
	EXPECT_EQ(Concept::HasDivide_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasDivide_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasDivide_v<BinaryReader>, false);
}

TEST(Concept, HasModulus)
{
	EXPECT_EQ(Concept::HasModulus_v<int32>, true);
	EXPECT_EQ(Concept::HasModulus_v<float>, false);
	EXPECT_EQ(Concept::HasModulus_v<String>, false);
	EXPECT_EQ(Concept::HasModulus_v<BigInt>, true);
	EXPECT_EQ(Concept::HasModulus_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasModulus_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasModulus_v<BinaryReader>, false);
}


TEST(Concept, HasPlusAssign)
{
	EXPECT_EQ(Concept::HasPlusAssign_v<int32>, true);
	EXPECT_EQ(Concept::HasPlusAssign_v<float>, true);
	EXPECT_EQ(Concept::HasPlusAssign_v<String>, true);
	EXPECT_EQ(Concept::HasPlusAssign_v<BigInt>, true);
	EXPECT_EQ(Concept::HasPlusAssign_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasPlusAssign_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasPlusAssign_v<BinaryReader>, false);
}

TEST(Concept, HasMinusAssign)
{
	EXPECT_EQ(Concept::HasMinusAssign_v<int32>, true);
	EXPECT_EQ(Concept::HasMinusAssign_v<float>, true);
	EXPECT_EQ(Concept::HasMinusAssign_v<String>, false);
	EXPECT_EQ(Concept::HasMinusAssign_v<BigInt>, true);
	EXPECT_EQ(Concept::HasMinusAssign_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasMinusAssign_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasMinusAssign_v<BinaryReader>, false);
}

TEST(Concept, HasMultiplyAssign)
{
	EXPECT_EQ(Concept::HasMultiplyAssign_v<int32>, true);
	EXPECT_EQ(Concept::HasMultiplyAssign_v<float>, true);
	EXPECT_EQ(Concept::HasMultiplyAssign_v<String>, false);
	EXPECT_EQ(Concept::HasMultiplyAssign_v<BigInt>, true);
	EXPECT_EQ(Concept::HasMultiplyAssign_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasMultiplyAssign_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasMultiplyAssign_v<BinaryReader>, false);
}

TEST(Concept, HasDivideAssign)
{
	EXPECT_EQ(Concept::HasDivideAssign_v<int32>, true);
	EXPECT_EQ(Concept::HasDivideAssign_v<float>, true);
	EXPECT_EQ(Concept::HasDivideAssign_v<String>, false);
	EXPECT_EQ(Concept::HasDivideAssign_v<BigInt>, true);
	EXPECT_EQ(Concept::HasDivideAssign_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasDivideAssign_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasDivideAssign_v<BinaryReader>, false);
}

TEST(Concept, HasModulesAssign)
{
	EXPECT_EQ(Concept::HasModulusAssign_v<int32>, true);
	EXPECT_EQ(Concept::HasModulusAssign_v<float>, false);
	EXPECT_EQ(Concept::HasModulusAssign_v<String>, false);
	EXPECT_EQ(Concept::HasModulusAssign_v<BigInt>, true);
	EXPECT_EQ(Concept::HasModulusAssign_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasModulusAssign_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasModulusAssign_v<BinaryReader>, false);
}

TEST(Concept, HasEqualTo)
{
	EXPECT_EQ(Concept::HasEqualTo_v<int32>, true);
	EXPECT_EQ(Concept::HasEqualTo_v<float>, true);
	EXPECT_EQ(Concept::HasEqualTo_v<String>, true);
	EXPECT_EQ(Concept::HasEqualTo_v<BigInt>, true);
	EXPECT_EQ(Concept::HasEqualTo_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasEqualTo_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasEqualTo_v<BinaryReader>, false);
}

TEST(Concept, HasNotEqualTo)
{
	EXPECT_EQ(Concept::HasNotEqualTo_v<int32>, true);
	EXPECT_EQ(Concept::HasNotEqualTo_v<float>, true);
	EXPECT_EQ(Concept::HasNotEqualTo_v<String>, true);
	EXPECT_EQ(Concept::HasNotEqualTo_v<BigInt>, true);
	EXPECT_EQ(Concept::HasNotEqualTo_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasNotEqualTo_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasNotEqualTo_v<BinaryReader>, false);
}

TEST(Concept, HasLessThan)
{
	EXPECT_EQ(Concept::HasLessThan_v<int32>, true);
	EXPECT_EQ(Concept::HasLessThan_v<float>, true);
	EXPECT_EQ(Concept::HasLessThan_v<String>, true);
	EXPECT_EQ(Concept::HasLessThan_v<BigInt>, true);
	EXPECT_EQ(Concept::HasLessThan_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasLessThan_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasLessThan_v<BinaryReader>, false);
}

TEST(Concept, HasLessThanEqual)
{
	EXPECT_EQ(Concept::HasLessThanEqual_v<int32>, true);
	EXPECT_EQ(Concept::HasLessThanEqual_v<float>, true);
	EXPECT_EQ(Concept::HasLessThanEqual_v<String>, true);
	EXPECT_EQ(Concept::HasLessThanEqual_v<BigInt>, true);
	EXPECT_EQ(Concept::HasLessThanEqual_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasLessThanEqual_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasLessThanEqual_v<BinaryReader>, false);
}

TEST(Concept, HasGreaterThan)
{
	EXPECT_EQ(Concept::HasGreaterThan_v<int32>, true);
	EXPECT_EQ(Concept::HasGreaterThan_v<float>, true);
	EXPECT_EQ(Concept::HasGreaterThan_v<String>, true);
	EXPECT_EQ(Concept::HasGreaterThan_v<BigInt>, true);
	EXPECT_EQ(Concept::HasGreaterThan_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasGreaterThan_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasGreaterThan_v<BinaryReader>, false);
}

TEST(Concept, HasGreaterThanEqual)
{
	EXPECT_EQ(Concept::HasGreaterThanEqual_v<int32>, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual_v<float>, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual_v<String>, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual_v<BigInt>, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasGreaterThanEqual_v<BinaryReader>, false);
}

TEST(Concept, HasBitwiseAnd)
{
	EXPECT_EQ(Concept::HasBitwiseAnd_v<int32>, true);
	EXPECT_EQ(Concept::HasBitwiseAnd_v<float>, false);
	EXPECT_EQ(Concept::HasBitwiseAnd_v<String>, false);
	EXPECT_EQ(Concept::HasBitwiseAnd_v<BigInt>, true);
	EXPECT_EQ(Concept::HasBitwiseAnd_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasBitwiseAnd_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasBitwiseAnd_v<BinaryReader>, false);
}

TEST(Concept, HasBitwiseOr)
{
	EXPECT_EQ(Concept::HasBitwiseOr_v<int32>, true);
	EXPECT_EQ(Concept::HasBitwiseOr_v<float>, false);
	EXPECT_EQ(Concept::HasBitwiseOr_v<String>, false);
	EXPECT_EQ(Concept::HasBitwiseOr_v<BigInt>, true);
	EXPECT_EQ(Concept::HasBitwiseOr_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasBitwiseOr_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasBitwiseOr_v<BinaryReader>, false);
}

TEST(Concept, HasBitwiseXor)
{
	EXPECT_EQ(Concept::HasBitwiseXor_v<int32>, true);
	EXPECT_EQ(Concept::HasBitwiseXor_v<float>, false);
	EXPECT_EQ(Concept::HasBitwiseXor_v<String>, false);
	EXPECT_EQ(Concept::HasBitwiseXor_v<BigInt>, true);
	EXPECT_EQ(Concept::HasBitwiseXor_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasBitwiseXor_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasBitwiseXor_v<BinaryReader>, false);
}

TEST(Concept, HasBitwiseAndAssign)
{
	EXPECT_EQ(Concept::HasBitwiseAndAssign_v<int32>, true);
	EXPECT_EQ(Concept::HasBitwiseAndAssign_v<float>, false);
	EXPECT_EQ(Concept::HasBitwiseAndAssign_v<String>, false);
	EXPECT_EQ(Concept::HasBitwiseAndAssign_v<BigInt>, true);
	EXPECT_EQ(Concept::HasBitwiseAndAssign_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasBitwiseAndAssign_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasBitwiseAndAssign_v<BinaryReader>, false);
}

TEST(Concept, HasBitwiseOrAssign)
{
	EXPECT_EQ(Concept::HasBitwiseOrAssign_v<int32>, true);
	EXPECT_EQ(Concept::HasBitwiseOrAssign_v<float>, false);
	EXPECT_EQ(Concept::HasBitwiseOrAssign_v<String>, false);
	EXPECT_EQ(Concept::HasBitwiseOrAssign_v<BigInt>, true);
	EXPECT_EQ(Concept::HasBitwiseOrAssign_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasBitwiseOrAssign_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasBitwiseOrAssign_v<BinaryReader>, false);
}

TEST(Concept, HasBitwiseXorAssign)
{
	EXPECT_EQ(Concept::HasBitwiseXorAssign_v<int32>, true);
	EXPECT_EQ(Concept::HasBitwiseXorAssign_v<float>, false);
	EXPECT_EQ(Concept::HasBitwiseXorAssign_v<String>, false);
	EXPECT_EQ(Concept::HasBitwiseXorAssign_v<BigInt>, true);
	EXPECT_EQ(Concept::HasBitwiseXorAssign_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasBitwiseXorAssign_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasBitwiseXorAssign_v<BinaryReader>, false);
}

TEST(Concept, HasLeftShift)
{
	EXPECT_EQ(Concept::HasLeftShift_v<int32>, true);
	EXPECT_EQ(Concept::HasLeftShift_v<float>, false);
	EXPECT_EQ(Concept::HasLeftShift_v<String>, false);
	EXPECT_EQ(Concept::HasLeftShift_v<BigInt>, false);
	EXPECT_EQ(Concept::HasLeftShift_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasLeftShift_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasLeftShift_v<BinaryReader>, false);

	const bool b = Concept::HasLeftShift_v<String, wchar>;
	EXPECT_EQ(b, true);
}

TEST(Concept, HasRightShift)
{
	EXPECT_EQ(Concept::HasRightShift_v<int32>, true);
	EXPECT_EQ(Concept::HasRightShift_v<float>, false);
	EXPECT_EQ(Concept::HasRightShift_v<String>, false);
	EXPECT_EQ(Concept::HasRightShift_v<BigInt>, false);
	EXPECT_EQ(Concept::HasRightShift_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasRightShift_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasRightShift_v<BinaryReader>, false);
}

TEST(Concept, HasLeftShiftAssign)
{
	EXPECT_EQ(Concept::HasLeftShiftAssign_v<int32>, true);
	EXPECT_EQ(Concept::HasLeftShiftAssign_v<float>, false);
	EXPECT_EQ(Concept::HasLeftShiftAssign_v<String>, false);
	EXPECT_EQ(Concept::HasLeftShiftAssign_v<BigInt>, false);
	EXPECT_EQ(Concept::HasLeftShiftAssign_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasLeftShiftAssign_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasLeftShiftAssign_v<BinaryReader>, false);
}

TEST(Concept, HasRightShiftAssign)
{
	EXPECT_EQ(Concept::HasRightShiftAssign_v<int32>, true);
	EXPECT_EQ(Concept::HasRightShiftAssign_v<float>, false);
	EXPECT_EQ(Concept::HasRightShiftAssign_v<String>, false);
	EXPECT_EQ(Concept::HasRightShiftAssign_v<BigInt>, false);
	EXPECT_EQ(Concept::HasRightShiftAssign_v<Optional<double>>, false);
	EXPECT_EQ(Concept::HasRightShiftAssign_v<Array<Date>>, false);
	EXPECT_EQ(Concept::HasRightShiftAssign_v<BinaryReader>, false);
}

TEST(Concept, HasLogicalAnd)
{
	EXPECT_EQ(Concept::HasLogicalAnd_v<int32>, true);
	EXPECT_EQ(Concept::HasLogicalAnd_v<float>, true);
	EXPECT_EQ(Concept::HasLogicalAnd_v<String>, true);
	EXPECT_EQ(Concept::HasLogicalAnd_v<BigInt>, true);
	EXPECT_EQ(Concept::HasLogicalAnd_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasLogicalAnd_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasLogicalAnd_v<BinaryReader>, true);
}

TEST(Concept, HasLogicalOr)
{
	EXPECT_EQ(Concept::HasLogicalOr_v<int32>, true);
	EXPECT_EQ(Concept::HasLogicalOr_v<float>, true);
	EXPECT_EQ(Concept::HasLogicalOr_v<String>, true);
	EXPECT_EQ(Concept::HasLogicalOr_v<BigInt>, true);
	EXPECT_EQ(Concept::HasLogicalOr_v<Optional<double>>, true);
	EXPECT_EQ(Concept::HasLogicalOr_v<Array<Date>>, true);
	EXPECT_EQ(Concept::HasLogicalOr_v<BinaryReader>, true);
}

# endif
