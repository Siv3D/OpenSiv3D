//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <limits>
# include "Concepts.hpp"

namespace s3d
{
	namespace Math
	{
		inline namespace Constants
		{
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float E_v			= Float(2.718281828459045235360287471352662498L);

			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float Log2E_v		= Float(1.442695040888963407359924681001892137L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float Log10E_v		= Float(0.434294481903251827651128918916605082L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float Pi_v			= Float(3.141592653589793238462643383279502884L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float QuarterPi_v	= Float(0.785398163397448309615660845819875721L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float OneThirdPi_v	= Float(1.047197551196597746154214461093167628L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float HalfPi_v		= Float(1.570796326794896619231321691639751442L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float TwoPi_v		= Float(6.283185307179586476925286766559005768L);
				
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float Tau_v		= Float(6.283185307179586476925286766559005768L);
					
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float InvTwoPi_v	= Float(0.159154943091895335768883763372514362L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float InvPi_v		= Float(0.318309886183790671537767526745028724L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float InvSqrtPi_v	= Float(0.564189583547756286948079451560772586L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float Ln2_v		= Float(0.693147180559945309417232121458176568L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float Ln10_v		= Float(2.302585092994045684017991454684364208L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float Sqrt2_v		= Float(1.414213562373095048801688724209698078L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float Sqrt3_v		= Float(1.732050807568877293527446341505872366L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float InvSqrt2_v	= Float(0.707106781186547524400844362104849039L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float InvSqrt3_v	= Float(0.577350269189625764509148780501957456L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float EGamma_v		= Float(0.577215664901532860606512090082402431L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float Phi_v		= Float(1.618033988749894848204586834365638117L);
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float QNaN_v		= std::numeric_limits<Float>::quiet_NaN();
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float NaN_v		= std::numeric_limits<Float>::signaling_NaN();
			
			SIV3D_CONCEPT_FLOATING_POINT
			inline constexpr Float Inf_v		= std::numeric_limits<Float>::infinity();

			/// @brief (float) π
			inline constexpr float PiF			= Pi_v<float>;

			/// @brief (float) π/4
			inline constexpr float QuarterPiF	= QuarterPi_v<float>;

			/// @brief (float) π/3
			inline constexpr float OneThirdPiF	= OneThirdPi_v<float>;

			/// @brief (float) π/2
			inline constexpr float HalfPiF		= HalfPi_v<float>;

			/// @brief (float) 2π
			inline constexpr float TwoPiF		= TwoPi_v<float>;

			/// @brief (float) τ (2π)
			inline constexpr float TauF			= Tau_v<float>;

			/// @brief (float) 1/(2π)
			inline constexpr float InvTwoPiF	= InvTwoPi_v<float>;

			/// @brief (float) 1/π
			inline constexpr float InvPiF		= InvPi_v<float>;

			/// @brief (float) 1/√π
			inline constexpr float InvSqrtPiF	= InvSqrtPi_v<float>;

			/// @brief Quiet NaN
			inline constexpr float QNaNF		= QNaN_v<float>;

			/// @brief Signaling NaN
			inline constexpr float NaNF			= NaN_v<float>;

			/// @brief +Inf
			inline constexpr float InfF			= Inf_v<float>;


			/// @brief 自然対数の底 | Euler's number
			inline constexpr double E			= E_v<double>;

			/// @brief 2 を底とする e の対数
			inline constexpr double Log2E		= Log2E_v<double>;

			/// @brief 10 を底とする e の対数
			inline constexpr double Log10E		= Log10E_v<double>;

			/// @brief π
			inline constexpr double Pi			= Pi_v<double>;

			/// @brief π/4
			inline constexpr double QuarterPi	= QuarterPi_v<double>;

			/// @brief π/3
			inline constexpr double OneThirdPi	= OneThirdPi_v<double>;

			/// @brief π/2
			inline constexpr double HalfPi		= HalfPi_v<double>;

			/// @brief 2π
			inline constexpr double TwoPi		= TwoPi_v<double>;

			/// @brief τ (2π)
			inline constexpr double Tau			= Tau_v<double>;

			/// @brief 1/(2π)
			inline constexpr double InvTwoPi	= InvTwoPi_v<double>;

			/// @brief 1/π
			inline constexpr double InvPi		= InvPi_v<double>;

			/// @brief 1/√π
			inline constexpr double InvSqrtPi	= InvSqrtPi_v<double>;

			/// @brief 2 の自然対数
			inline constexpr double Ln2			= Ln2_v<double>;

			/// @brief 10 の自然対数
			inline constexpr double Ln10		= Ln10_v<double>;

			/// @brief √2
			inline constexpr double Sqrt2		= Sqrt2_v<double>;

			/// @brief √3
			inline constexpr double Sqrt3		= Sqrt3_v<double>;

			/// @brief 1/√2
			inline constexpr double InvSqrt2	= InvSqrt2_v<double>;

			/// @brief 1/√3
			inline constexpr double InvSqrt3	= InvSqrt3_v<double>;

			/// @brief オイラーの定数
			inline constexpr double EGamma		= EGamma_v<double>;

			/// @brief 黄金数 (φ) | Golden ratio
			inline constexpr double Phi			= Phi_v<double>;

			/// @brief Quiet NaN
			inline constexpr double QNaN		= QNaN_v<double>;

			/// @brief Signaling NaN
			inline constexpr double NaN			= NaN_v<double>;

			/// @brief +Inf
			inline constexpr double Inf			= Inf_v<double>;
		}
	}

	inline namespace Literals
	{
		inline namespace MathLiterals
		{
			[[nodiscard]] 
			inline constexpr double operator ""_pi(long double x) noexcept;

			[[nodiscard]]
			inline constexpr double operator ""_pi(unsigned long long x) noexcept;

			[[nodiscard]] 
			inline constexpr float operator ""_piF(long double x) noexcept;

			[[nodiscard]]
			inline constexpr float operator ""_piF(unsigned long long x) noexcept;


			[[nodiscard]]
			inline constexpr double operator ""_tau(long double x) noexcept;

			[[nodiscard]]
			inline constexpr double operator ""_tau(unsigned long long x) noexcept;

			[[nodiscard]]
			inline constexpr float operator ""_tauF(long double x) noexcept;

			[[nodiscard]]
			inline constexpr float operator ""_tauF(unsigned long long x) noexcept;


			[[nodiscard]]
			inline constexpr double operator ""_deg(long double deg) noexcept;

			[[nodiscard]]
			inline constexpr double operator ""_deg(unsigned long long deg) noexcept;

			[[nodiscard]]
			inline constexpr float operator ""_degF(long double deg) noexcept;

			[[nodiscard]]
			inline constexpr float operator ""_degF(unsigned long long deg) noexcept;
		}
	}
}

# include "detail/MathConstants.ipp"
