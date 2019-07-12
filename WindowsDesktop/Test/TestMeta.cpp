
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

namespace TestMeta
{
	template <class Type>
	using size_func_t = decltype(std::declval<Type&>().size());
}

TEST_CASE("Meta")
{
	using namespace TestMeta;

	REQUIRE(Meta::HasUnaryPlus_v<bool> == true);
	REQUIRE(Meta::HasUnaryPlus_v<int32> == true);
	REQUIRE(Meta::HasUnaryPlus_v<Byte> == false);
	REQUIRE(Meta::HasUnaryPlus_v<String> == false);
	REQUIRE(Meta::HasUnaryPlus_v<Point> == true);
	REQUIRE(Meta::HasUnaryPlus_v<None_t> == false);

	REQUIRE(Meta::HasNegate_v<bool> == true);
	REQUIRE(Meta::HasNegate_v<int32> == true);
	REQUIRE(Meta::HasNegate_v<Byte> == false);
	REQUIRE(Meta::HasNegate_v<String> == false);
	REQUIRE(Meta::HasNegate_v<Point> == true);
	REQUIRE(Meta::HasNegate_v<None_t> == false);

	REQUIRE(Meta::HasPreIncrement_v<bool> == false);
	REQUIRE(Meta::HasPreIncrement_v<int32> == true);
	REQUIRE(Meta::HasPreIncrement_v<Byte> == false);
	REQUIRE(Meta::HasPreIncrement_v<String> == false);
	REQUIRE(Meta::HasPreIncrement_v<Point> == false);
	REQUIRE(Meta::HasPreIncrement_v<None_t> == false);

	REQUIRE(Meta::HasPreDecrement_v<bool> == false);
	REQUIRE(Meta::HasPreDecrement_v<int32> == true);
	REQUIRE(Meta::HasPreDecrement_v<Byte> == false);
	REQUIRE(Meta::HasPreDecrement_v<String> == false);
	REQUIRE(Meta::HasPreDecrement_v<Point> == false);
	REQUIRE(Meta::HasPreDecrement_v<None_t> == false);

	REQUIRE(Meta::HasOperatorBool_v<bool> == true);
	REQUIRE(Meta::HasOperatorBool_v<int32> == true);
	REQUIRE(Meta::HasOperatorBool_v<Byte> == false);
	REQUIRE(Meta::HasOperatorBool_v<String> == true);
	REQUIRE(Meta::HasOperatorBool_v<Point> == false);
	REQUIRE(Meta::HasOperatorBool_v<None_t> == false);

	REQUIRE(Meta::HasLogicalNot_v<bool> == true);
	REQUIRE(Meta::HasLogicalNot_v<int32> == true);
	REQUIRE(Meta::HasLogicalNot_v<Byte> == false);
	REQUIRE(Meta::HasLogicalNot_v<String> == true);
	REQUIRE(Meta::HasLogicalNot_v<Point> == false);
	REQUIRE(Meta::HasLogicalNot_v<None_t> == false);

	REQUIRE(Meta::HasComplement_v<bool> == true);
	REQUIRE(Meta::HasComplement_v<int32> == true);
	REQUIRE(Meta::HasComplement_v<Byte> == true);
	REQUIRE(Meta::HasComplement_v<String> == false);
	REQUIRE(Meta::HasComplement_v<Point> == false);
	REQUIRE(Meta::HasComplement_v<None_t> == false);

	REQUIRE(Meta::HasAddressOf_v<bool> == true);
	REQUIRE(Meta::HasAddressOf_v<int32> == true);
	REQUIRE(Meta::HasAddressOf_v<Byte> == true);
	REQUIRE(Meta::HasAddressOf_v<String> == true);
	REQUIRE(Meta::HasAddressOf_v<Point> == true);
	REQUIRE(Meta::HasAddressOf_v<None_t> == true);

	REQUIRE(Meta::HasOverloadedAddressOf_v<bool> == false);
	REQUIRE(Meta::HasOverloadedAddressOf_v<int32> == false);
	REQUIRE(Meta::HasOverloadedAddressOf_v<Byte> == false);
	REQUIRE(Meta::HasOverloadedAddressOf_v<String> == false);
	REQUIRE(Meta::HasOverloadedAddressOf_v<Point> == false);
	REQUIRE(Meta::HasOverloadedAddressOf_v<None_t> == false);

	REQUIRE(Meta::HasPostIncrement_v<bool> == false);
	REQUIRE(Meta::HasPostIncrement_v<int32> == true);
	REQUIRE(Meta::HasPostIncrement_v<Byte> == false);
	REQUIRE(Meta::HasPostIncrement_v<String> == false);
	REQUIRE(Meta::HasPostIncrement_v<Point> == false);
	REQUIRE(Meta::HasPostIncrement_v<None_t> == false);

	REQUIRE(Meta::HasPostDecrement_v<bool> == false);
	REQUIRE(Meta::HasPostDecrement_v<int32> == true);
	REQUIRE(Meta::HasPostDecrement_v<Byte> == false);
	REQUIRE(Meta::HasPostDecrement_v<String> == false);
	REQUIRE(Meta::HasPostDecrement_v<Point> == false);
	REQUIRE(Meta::HasPostDecrement_v<None_t> == false);

	REQUIRE(Meta::HasPlus_v<bool> == true);
	REQUIRE(Meta::HasPlus_v<int32> == true);
	REQUIRE(Meta::HasPlus_v<Byte> == false);
	REQUIRE(Meta::HasPlus_v<String> == true);
	REQUIRE(Meta::HasPlus_v<Point> == true);
	REQUIRE(Meta::HasPlus_v<None_t> == false);

	REQUIRE(Meta::HasMinus_v<bool> == true);
	REQUIRE(Meta::HasMinus_v<int32> == true);
	REQUIRE(Meta::HasMinus_v<Byte> == false);
	REQUIRE(Meta::HasMinus_v<String> == false);
	REQUIRE(Meta::HasMinus_v<Point> == true);
	REQUIRE(Meta::HasMinus_v<None_t> == false);

	REQUIRE(Meta::HasMultiply_v<bool> == true);
	REQUIRE(Meta::HasMultiply_v<int32> == true);
	REQUIRE(Meta::HasMultiply_v<Byte> == false);
	REQUIRE(Meta::HasMultiply_v<String> == false);
	REQUIRE(Meta::HasMultiply_v<Point> == true);
	REQUIRE(Meta::HasMultiply_v<None_t> == false);
	REQUIRE(Meta::HasMultiply_v<Point, int32> == true);

	REQUIRE(Meta::HasDivide_v<bool> == true);
	REQUIRE(Meta::HasDivide_v<int32> == true);
	REQUIRE(Meta::HasDivide_v<Byte> == false);
	REQUIRE(Meta::HasDivide_v<String> == false);
	REQUIRE(Meta::HasDivide_v<Point> == true);
	REQUIRE(Meta::HasDivide_v<None_t> == false);
	REQUIRE(Meta::HasDivide_v<Point, int32> == true);

	REQUIRE(Meta::HasModulus_v<bool> == true);
	REQUIRE(Meta::HasModulus_v<int32> == true);
	REQUIRE(Meta::HasModulus_v<Byte> == false);
	REQUIRE(Meta::HasModulus_v<String> == false);
	REQUIRE(Meta::HasModulus_v<Point> == false);
	REQUIRE(Meta::HasModulus_v<None_t> == false);
	REQUIRE(Meta::HasModulus_v<Point, int32> == false);

	REQUIRE(Meta::HasPlusAssign_v<bool> == true);
	REQUIRE(Meta::HasPlusAssign_v<int32> == true);
	REQUIRE(Meta::HasPlusAssign_v<Byte> == false);
	REQUIRE(Meta::HasPlusAssign_v<String> == true);
	REQUIRE(Meta::HasPlusAssign_v<Point> == true);
	REQUIRE(Meta::HasPlusAssign_v<None_t> == false);
	REQUIRE(Meta::HasPlusAssign_v<Point, int32> == false);

	REQUIRE(Meta::HasMinusAssign_v<bool> == true);
	REQUIRE(Meta::HasMinusAssign_v<int32> == true);
	REQUIRE(Meta::HasMinusAssign_v<Byte> == false);
	REQUIRE(Meta::HasMinusAssign_v<String> == false);
	REQUIRE(Meta::HasMinusAssign_v<Point> == true);
	REQUIRE(Meta::HasMinusAssign_v<None_t> == false);
	REQUIRE(Meta::HasMinusAssign_v<Point, int32> == false);

	REQUIRE(Meta::HasMultiplyAssign_v<bool> == true);
	REQUIRE(Meta::HasMultiplyAssign_v<int32> == true);
	REQUIRE(Meta::HasMultiplyAssign_v<Byte> == false);
	REQUIRE(Meta::HasMultiplyAssign_v<String> == false);
	REQUIRE(Meta::HasMultiplyAssign_v<Point> == false);
	REQUIRE(Meta::HasMultiplyAssign_v<None_t> == false);
	REQUIRE(Meta::HasMultiplyAssign_v<Point, int32> == true);

	REQUIRE(Meta::HasDivideAssign_v<bool> == true);
	REQUIRE(Meta::HasDivideAssign_v<int32> == true);
	REQUIRE(Meta::HasDivideAssign_v<Byte> == false);
	REQUIRE(Meta::HasDivideAssign_v<String> == false);
	REQUIRE(Meta::HasDivideAssign_v<Point> == false);
	REQUIRE(Meta::HasDivideAssign_v<None_t> == false);
	REQUIRE(Meta::HasDivideAssign_v<Point, int32> == true);

	REQUIRE(Meta::HasModulusAssign_v<bool> == true);
	REQUIRE(Meta::HasModulusAssign_v<int32> == true);
	REQUIRE(Meta::HasModulusAssign_v<Byte> == false);
	REQUIRE(Meta::HasModulusAssign_v<String> == false);
	REQUIRE(Meta::HasModulusAssign_v<Point> == false);
	REQUIRE(Meta::HasModulusAssign_v<None_t> == false);
	REQUIRE(Meta::HasModulusAssign_v<Point, int32> == false);

	REQUIRE(Meta::HasEqualTo_v<bool> == true);
	REQUIRE(Meta::HasEqualTo_v<int32> == true);
	REQUIRE(Meta::HasEqualTo_v<Byte> == true);
	REQUIRE(Meta::HasEqualTo_v<String> == true);
	REQUIRE(Meta::HasEqualTo_v<Point> == true);
	REQUIRE(Meta::HasEqualTo_v<None_t> == false);
	REQUIRE(Meta::HasEqualTo_v<Point, int32> == false);
	REQUIRE(Meta::HasEqualTo_v<None_t, Optional<int32>> == true);

	REQUIRE(Meta::HasNotEqualTo_v<bool> == true);
	REQUIRE(Meta::HasNotEqualTo_v<int32> == true);
	REQUIRE(Meta::HasNotEqualTo_v<Byte> == true);
	REQUIRE(Meta::HasNotEqualTo_v<String> == true);
	REQUIRE(Meta::HasNotEqualTo_v<Point> == true);
	REQUIRE(Meta::HasNotEqualTo_v<None_t> == false);
	REQUIRE(Meta::HasNotEqualTo_v<Point, int32> == false);
	REQUIRE(Meta::HasNotEqualTo_v<None_t, Optional<int32>> == true);

	REQUIRE(Meta::HasLessThan_v<bool> == true);
	REQUIRE(Meta::HasLessThan_v<int32> == true);
	REQUIRE(Meta::HasLessThan_v<Byte> == true);
	REQUIRE(Meta::HasLessThan_v<String> == true);
	REQUIRE(Meta::HasLessThan_v<Point> == false);
	REQUIRE(Meta::HasLessThan_v<None_t> == false);
	REQUIRE(Meta::HasLessThan_v<Point, int32> == false);
	REQUIRE(Meta::HasLessThan_v<None_t, Optional<int32>> == true);

	REQUIRE(Meta::HasLessThanEqual_v<bool> == true);
	REQUIRE(Meta::HasLessThanEqual_v<int32> == true);
	REQUIRE(Meta::HasLessThanEqual_v<Byte> == true);
	REQUIRE(Meta::HasLessThanEqual_v<String> == true);
	REQUIRE(Meta::HasLessThanEqual_v<Point> == false);
	REQUIRE(Meta::HasLessThanEqual_v<None_t> == false);
	REQUIRE(Meta::HasLessThanEqual_v<Point, int32> == false);
	REQUIRE(Meta::HasLessThanEqual_v<None_t, Optional<int32>> == true);

	REQUIRE(Meta::HasGreaterThan_v<bool> == true);
	REQUIRE(Meta::HasGreaterThan_v<int32> == true);
	REQUIRE(Meta::HasGreaterThan_v<Byte> == true);
	REQUIRE(Meta::HasGreaterThan_v<String> == true);
	REQUIRE(Meta::HasGreaterThan_v<Point> == false);
	REQUIRE(Meta::HasGreaterThan_v<None_t> == false);
	REQUIRE(Meta::HasGreaterThan_v<Point, int32> == false);
	REQUIRE(Meta::HasGreaterThan_v<None_t, Optional<int32>> == true);

	REQUIRE(Meta::HasGreaterThanEqual_v<bool> == true);
	REQUIRE(Meta::HasGreaterThanEqual_v<int32> == true);
	REQUIRE(Meta::HasGreaterThanEqual_v<Byte> == true);
	REQUIRE(Meta::HasGreaterThanEqual_v<String> == true);
	REQUIRE(Meta::HasGreaterThanEqual_v<Point> == false);
	REQUIRE(Meta::HasGreaterThanEqual_v<None_t> == false);
	REQUIRE(Meta::HasGreaterThanEqual_v<Point, int32> == false);
	REQUIRE(Meta::HasGreaterThanEqual_v<None_t, Optional<int32>> == true);

	REQUIRE(Meta::HasBitwiseAnd_v<bool> == true);
	REQUIRE(Meta::HasBitwiseAnd_v<int32> == true);
	REQUIRE(Meta::HasBitwiseAnd_v<Byte> == true);
	REQUIRE(Meta::HasBitwiseAnd_v<String> == false);
	REQUIRE(Meta::HasBitwiseAnd_v<Point> == false);
	REQUIRE(Meta::HasBitwiseAnd_v<None_t> == false);
	REQUIRE(Meta::HasBitwiseAnd_v<Point, int32> == false);
	REQUIRE(Meta::HasBitwiseAnd_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasBitwiseOr_v<bool> == true);
	REQUIRE(Meta::HasBitwiseOr_v<int32> == true);
	REQUIRE(Meta::HasBitwiseOr_v<Byte> == true);
	REQUIRE(Meta::HasBitwiseOr_v<String> == false);
	REQUIRE(Meta::HasBitwiseOr_v<Point> == false);
	REQUIRE(Meta::HasBitwiseOr_v<None_t> == false);
	REQUIRE(Meta::HasBitwiseOr_v<Point, int32> == false);
	REQUIRE(Meta::HasBitwiseOr_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasBitwiseXor_v<bool> == true);
	REQUIRE(Meta::HasBitwiseXor_v<int32> == true);
	REQUIRE(Meta::HasBitwiseXor_v<Byte> == true);
	REQUIRE(Meta::HasBitwiseXor_v<String> == false);
	REQUIRE(Meta::HasBitwiseXor_v<Point> == false);
	REQUIRE(Meta::HasBitwiseXor_v<None_t> == false);
	REQUIRE(Meta::HasBitwiseXor_v<Point, int32> == false);
	REQUIRE(Meta::HasBitwiseXor_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasBitwiseAndAssign_v<bool> == true);
	REQUIRE(Meta::HasBitwiseAndAssign_v<int32> == true);
	REQUIRE(Meta::HasBitwiseAndAssign_v<Byte> == true);
	REQUIRE(Meta::HasBitwiseAndAssign_v<String> == false);
	REQUIRE(Meta::HasBitwiseAndAssign_v<Point> == false);
	REQUIRE(Meta::HasBitwiseAndAssign_v<None_t> == false);
	REQUIRE(Meta::HasBitwiseAndAssign_v<Point, int32> == false);
	REQUIRE(Meta::HasBitwiseAndAssign_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasBitwiseOrAssign_v<bool> == true);
	REQUIRE(Meta::HasBitwiseOrAssign_v<int32> == true);
	REQUIRE(Meta::HasBitwiseOrAssign_v<Byte> == true);
	REQUIRE(Meta::HasBitwiseOrAssign_v<String> == false);
	REQUIRE(Meta::HasBitwiseOrAssign_v<Point> == false);
	REQUIRE(Meta::HasBitwiseOrAssign_v<None_t> == false);
	REQUIRE(Meta::HasBitwiseOrAssign_v<Point, int32> == false);
	REQUIRE(Meta::HasBitwiseOrAssign_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasBitwiseXorAssign_v<bool> == true);
	REQUIRE(Meta::HasBitwiseXorAssign_v<int32> == true);
	REQUIRE(Meta::HasBitwiseXorAssign_v<Byte> == true);
	REQUIRE(Meta::HasBitwiseXorAssign_v<String> == false);
	REQUIRE(Meta::HasBitwiseXorAssign_v<Point> == false);
	REQUIRE(Meta::HasBitwiseXorAssign_v<None_t> == false);
	REQUIRE(Meta::HasBitwiseXorAssign_v<Point, int32> == false);
	REQUIRE(Meta::HasBitwiseXorAssign_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasLeftShift_v<bool> == true);
	REQUIRE(Meta::HasLeftShift_v<int32> == true);
	REQUIRE(Meta::HasLeftShift_v<Byte> == false);
	REQUIRE(Meta::HasLeftShift_v<String> == false);
	REQUIRE(Meta::HasLeftShift_v<Point> == false);
	REQUIRE(Meta::HasLeftShift_v<None_t> == false);
	REQUIRE(Meta::HasLeftShift_v<Byte, int32> == true);
	REQUIRE(Meta::HasLeftShift_v<Point, int32> == false);
	REQUIRE(Meta::HasLeftShift_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasRightShift_v<bool> == true);
	REQUIRE(Meta::HasRightShift_v<int32> == true);
	REQUIRE(Meta::HasRightShift_v<Byte> == false);
	REQUIRE(Meta::HasRightShift_v<String> == false);
	REQUIRE(Meta::HasRightShift_v<Point> == false);
	REQUIRE(Meta::HasRightShift_v<None_t> == false);
	REQUIRE(Meta::HasRightShift_v<Byte, int32> == true);
	REQUIRE(Meta::HasRightShift_v<Point, int32> == false);
	REQUIRE(Meta::HasRightShift_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasLeftShiftAssign_v<bool> == true);
	REQUIRE(Meta::HasLeftShiftAssign_v<int32> == true);
	REQUIRE(Meta::HasLeftShiftAssign_v<Byte> == false);
	REQUIRE(Meta::HasLeftShiftAssign_v<String> == false);
	REQUIRE(Meta::HasLeftShiftAssign_v<Point> == false);
	REQUIRE(Meta::HasLeftShiftAssign_v<None_t> == false);
	REQUIRE(Meta::HasLeftShiftAssign_v<Byte, int32> == true);
	REQUIRE(Meta::HasLeftShiftAssign_v<Point, int32> == false);
	REQUIRE(Meta::HasLeftShiftAssign_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasRightShiftAssign_v<bool> == true);
	REQUIRE(Meta::HasRightShiftAssign_v<int32> == true);
	REQUIRE(Meta::HasRightShiftAssign_v<Byte> == false);
	REQUIRE(Meta::HasRightShiftAssign_v<String> == false);
	REQUIRE(Meta::HasRightShiftAssign_v<Point> == false);
	REQUIRE(Meta::HasRightShiftAssign_v<None_t> == false);
	REQUIRE(Meta::HasRightShiftAssign_v<Byte, int32> == true);
	REQUIRE(Meta::HasRightShiftAssign_v<Point, int32> == false);
	REQUIRE(Meta::HasRightShiftAssign_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasLogicalAnd_v<bool> == true);
	REQUIRE(Meta::HasLogicalAnd_v<int32> == true);
	REQUIRE(Meta::HasLogicalAnd_v<Byte> == false);
	REQUIRE(Meta::HasLogicalAnd_v<String> == true);
	REQUIRE(Meta::HasLogicalAnd_v<Point> == false);
	REQUIRE(Meta::HasLogicalAnd_v<None_t> == false);
	REQUIRE(Meta::HasLogicalAnd_v<Byte, int32> == false);
	REQUIRE(Meta::HasLogicalAnd_v<Point, int32> == false);
	REQUIRE(Meta::HasLogicalAnd_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::HasLogicalOr_v<bool> == true);
	REQUIRE(Meta::HasLogicalOr_v<int32> == true);
	REQUIRE(Meta::HasLogicalOr_v<Byte> == false);
	REQUIRE(Meta::HasLogicalOr_v<String> == true);
	REQUIRE(Meta::HasLogicalOr_v<Point> == false);
	REQUIRE(Meta::HasLogicalOr_v<None_t> == false);
	REQUIRE(Meta::HasLogicalOr_v<Byte, int32> == false);
	REQUIRE(Meta::HasLogicalOr_v<Point, int32> == false);
	REQUIRE(Meta::HasLogicalOr_v<None_t, Optional<int32>> == false);

	REQUIRE(Meta::IsDetected_v<size_func_t, bool> == false);
	REQUIRE(Meta::IsDetected_v<size_func_t, int32> == false);
	REQUIRE(Meta::IsDetected_v<size_func_t, Byte> == false);
	REQUIRE(Meta::IsDetected_v<size_func_t, String> == true);
	REQUIRE(Meta::IsDetected_v<size_func_t, Point> == false);
	REQUIRE(Meta::IsDetected_v<size_func_t, None_t> == false);
	REQUIRE(Meta::IsDetected_v<size_func_t, Byte, int32> == false);
	REQUIRE(Meta::IsDetected_v<size_func_t, Point, int32> == false);
	REQUIRE(Meta::IsDetected_v<size_func_t, None_t, Optional<int32>> == false);
	REQUIRE(Meta::IsDetected_v<size_func_t, Array<Vec2>> == true);
	REQUIRE(Meta::IsDetected_v<size_func_t, std::array<double, 20>> == true);

	//IsDetectedExact_v

	//IsDetectedConvertible_v
}

# endif
