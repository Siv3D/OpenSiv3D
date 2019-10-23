//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <limits>

namespace s3d
{
	namespace Math
	{
		inline namespace Constants
		{
			template <class T> inline constexpr T E_v			= T(2.718281828459045235360287471352662498L);
			template <class T> inline constexpr T Log2E_v		= T(1.442695040888963407359924681001892137L);
			template <class T> inline constexpr T Log10E_v		= T(0.434294481903251827651128918916605082L);
			template <class T> inline constexpr T Pi_v			= T(3.141592653589793238462643383279502884L);
			template <class T> inline constexpr T QuarterPi_v	= T(0.785398163397448309615660845819875721L);
			template <class T> inline constexpr T OneThirdPi_v	= T(1.047197551196597746154214461093167628L);
			template <class T> inline constexpr T HalfPi_v		= T(1.570796326794896619231321691639751442L);
			template <class T> inline constexpr T TwoPi_v		= T(6.283185307179586476925286766559005768L);
			template <class T> inline constexpr T InvTwoPi_v	= T(0.159154943091895335768883763372514362L);
			template <class T> inline constexpr T InvPi_v		= T(0.318309886183790671537767526745028724L);
			template <class T> inline constexpr T InvSqrtPi_v	= T(0.564189583547756286948079451560772586L);
			template <class T> inline constexpr T Ln2_v			= T(0.693147180559945309417232121458176568L);
			template <class T> inline constexpr T Ln10_v		= T(2.302585092994045684017991454684364208L);
			template <class T> inline constexpr T Sqrt2_v		= T(1.414213562373095048801688724209698078L);
			template <class T> inline constexpr T Sqrt3_v		= T(1.732050807568877293527446341505872366L);
			template <class T> inline constexpr T InvSqrt2_v	= T(1.570796326794896619231321691639751442L);
			template <class T> inline constexpr T InvSqrt3_v	= T(0.577350269189625764509148780501957456L);
			template <class T> inline constexpr T EGamma_v		= T(0.577215664901532860606512090082402431L);
			template <class T> inline constexpr T Phi_v			= T(1.618033988749894848204586834365638117L);
			template <class T> inline constexpr T QNaN_v		= std::numeric_limits<T>::quiet_NaN();
			template <class T> inline constexpr T NaN_v			= std::numeric_limits<T>::signaling_NaN();
			template <class T> inline constexpr T Inf_v			= std::numeric_limits<T>::infinity();


			/// <summary>
			/// (float) π
			/// </summary>
			inline constexpr float PiF			= Pi_v<float>;

			/// <summary>
			/// (float) π/4
			/// </summary>
			inline constexpr float QuarterPiF	= QuarterPi_v<float>;

			/// <summary>
			/// (float) π/3
			/// </summary>
			inline constexpr float OneThirdPiF	= OneThirdPi_v<float>;

			/// <summary>
			/// (float) π/2
			/// </summary>
			inline constexpr float HalfPiF		= HalfPi_v<float>;

			/// <summary>
			/// (float) 2 * π
			/// </summary>
			inline constexpr float TwoPiF		= TwoPi_v<float>;


			/// <summary>
			/// 自然対数の底
			/// Euler's number
			/// </summary>
			inline constexpr double E			= E_v<double>;

			/// <summary>
			/// 2 を底とする e の対数
			/// </summary>
			inline constexpr double Log2E		= Log2E_v<double>;
			
			/// <summary>
			/// 10 を底とする e の対数
			/// </summary>
			inline constexpr double Log10E		= Log10E_v<double>;

			/// <summary>
			/// π
			/// </summary>
			inline constexpr double Pi			= Pi_v<double>;

			/// <summary>
			/// π/4
			/// </summary>
			inline constexpr double QuarterPi	= QuarterPi_v<double>;

			/// <summary>
			/// π/3
			/// </summary>
			inline constexpr double OneThirdPi	= OneThirdPi_v<double>;

			/// <summary>
			/// π/2
			/// </summary>
			inline constexpr double HalfPi		= HalfPi_v<double>;

			/// <summary>
			/// 2 * π
			/// </summary>
			inline constexpr double TwoPi		= TwoPi_v<double>;

			/// <summary>
			/// 1 / (2π)
			/// </summary>
			inline constexpr double InvTwoPi	= InvTwoPi_v<double>;

			/// <summary>
			/// 1 / π
			/// </summary>
			inline constexpr double InvPi		= InvPi_v<double>;
	
			/// <summary>
			/// 1 / √π
			/// </summary>
			inline constexpr double InvSqrtPi	= InvSqrtPi_v<double>;

			/// <summary>
			/// 2 の自然対数
			/// </summary>
			inline constexpr double Ln2			= Ln2_v<double>;

			/// <summary>
			/// 10 の自然対数
			/// </summary>
			inline constexpr double Ln10		= Ln10_v<double>;

			/// <summary>
			/// √2
			/// </summary>			
			inline constexpr double Sqrt2		= Sqrt2_v<double>;

			/// <summary>
			/// √3
			/// </summary>		
			inline constexpr double Sqrt3		= Sqrt3_v<double>;

			/// <summary>
			/// 1 / √2
			/// </summary>		
			inline constexpr double InvSqrt2	= InvSqrt2_v<double>;

			/// <summary>
			/// 1 / √3
			/// </summary>		
			inline constexpr double InvSqrt3	= InvSqrt3_v<double>;

			/// <summary>
			/// オイラーの定数
			/// </summary>				
			inline constexpr double EGamma		= EGamma_v<double>;

			/// <summary>
			/// 黄金数 (φ)
			/// Golden Ratio
			/// </summary>
			inline constexpr double Phi			= Phi_v<double>;

			/// <summary> 
			/// Quiet NaN
			/// </summary>
			inline constexpr double QNaN		= QNaN_v<double>;

			/// <summary>
			/// Signaling NaN
			/// </summary>
			inline constexpr double NaN			= NaN_v<double>;

			/// <summary>
			/// +Inf
			/// </summary>
			inline constexpr double Inf			= Inf_v<double>;
		}
	}

	inline namespace Literals
	{
		inline namespace MathLiterals
		{
			[[nodiscard]] inline constexpr double operator ""_pi(long double x)
			{
				return static_cast<double>(x * Math::Constants::Pi);
			}

			[[nodiscard]] inline constexpr double operator ""_pi(unsigned long long x)
			{
				return static_cast<double>(x * Math::Constants::Pi);
			}

			[[nodiscard]] inline constexpr double operator ""_deg(long double deg)
			{
				return static_cast<double>(deg * Math::Constants::Pi / 180);
			}

			[[nodiscard]] inline constexpr double operator ""_deg(unsigned long long deg)
			{
				return static_cast<double>(deg * Math::Constants::Pi / 180);
			}
		}
	}
}

