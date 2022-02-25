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
# if  __has_include(<bit>)
#	include <bit>
# endif
# include <cstring>
# include <functional>
# include "Common.hpp"
# include "Utility.hpp"

namespace s3d
{
	/// @brief ブレンドモード
	enum class Blend : uint8
	{
		Zero			= 1,
		
		One				= 2,
		
		SrcColor		= 3,
		
		InvSrcColor		= 4,
		
		SrcAlpha		= 5,
		
		InvSrcAlpha		= 6,
		
		DestAlpha		= 7,
		
		InvDestAlpha	= 8,
		
		DestColor		= 9,
		
		InvDestColor	= 10,
		
		SrcAlphaSat		= 11,
		
		BlendFactor		= 14,
		
		InvBlendFactor	= 15,
		
		Src1Color		= 16,
		
		InvSrc1Color	= 17,
		
		Src1Alpha		= 18,
		
		InvSrc1Alpha	= 19
	};

	/// @brief ブレンド式
	enum class BlendOp : uint8
	{
		Add			= 1,
		
		Subtract	= 2,
		
		RevSubtract	= 3,
		
		Min			= 4,
		
		Max			= 5
	};

	/// @brief ブレンドステート
	struct BlendState
	{
	private:

		enum class Predefined
		{
			NonPremultiplied,

			Premultiplied,

			Opaque,

			Additive,

			AdditiveRGB,

			Subtractive,

			Multiplicative,

			Multiplicative2X,

			OpaqueAlphaToCoverage,

			MaxAlpha,

			Default2D = NonPremultiplied,

			Default3D = Opaque,
		};

	public:

		using storage_type = uint32;

		bool enable		: 1 = true;

		bool writeR		: 1 = true;

		bool writeG		: 1 = true;

		Blend src		: 5 = Blend::SrcAlpha;

		Blend dst		: 5 = Blend::InvSrcAlpha;

		BlendOp op		: 3 = BlendOp::Add;

		bool alphaToCoverageEnable : 1 = false;

		bool writeB		: 1 = true;

		bool writeA		: 1 = true;

		Blend srcAlpha	: 5 = Blend::Zero;

		Blend dstAlpha	: 5 = Blend::One;

		BlendOp opAlpha	: 3 = BlendOp::Add;

		SIV3D_NODISCARD_CXX20
		explicit constexpr BlendState(
			bool _enable = true,
			Blend _src = Blend::SrcAlpha,
			Blend _dst = Blend::InvSrcAlpha,
			BlendOp _op = BlendOp::Add,
			Blend _srcAlpha = Blend::Zero,
			Blend _dstAlpha = Blend::One,
			BlendOp _opAlpha = BlendOp::Add,
			bool _alphaToCoverageEnable = false,
			bool _writeR = true,
			bool _writeG = true,
			bool _writeB = true,
			bool _writeA = true
		) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr BlendState(Predefined predefined) noexcept;

		[[nodiscard]]
		storage_type asValue() const noexcept;

		[[nodiscard]]
		bool operator ==(const BlendState& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const BlendState& other) const noexcept;

		/// @brief デフォルトのブレンド
		/// @remark BlendState{ true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		static constexpr Predefined NonPremultiplied = Predefined::NonPremultiplied;

		/// @brief 乗算済みアルファブレンド
		/// @remark BlendState{ true, Blend::One, Blend::InvSrcAlpha, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		static constexpr Predefined Premultiplied = Predefined::Premultiplied;

		/// @brief 不透明
		/// @remark BlendState{ false }
		static constexpr Predefined Opaque = Predefined::Opaque;

		/// @brief 加算ブレンド
		/// @remark BlendState{ true, Blend::SrcAlpha, Blend::One, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		static constexpr Predefined Additive = Predefined::Additive;

		/// @brief 加算ブレンド (RGB)
		/// @remark BlendState{ true, Blend::One, Blend::One, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		static constexpr Predefined AdditiveRGB = Predefined::AdditiveRGB;

		/// @brief 減算ブレンド
		/// @remark BlendState{ true, Blend::SrcAlpha, Blend::One, BlendOp::RevSubtract, Blend::Zero, Blend::One, BlendOp::Add }
		static constexpr Predefined Subtractive = Predefined::Subtractive;

		/// @brief 乗算ブレンド
		/// @remark BlendState{ true, Blend::Zero, Blend::SrcColor, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		static constexpr Predefined Multiplicative = Predefined::Multiplicative;

		/// @brief 2X 乗算ブレンド
		/// @remark BlendState{ true, Blend::DestColor, Blend::SrcColor, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		static constexpr Predefined Multiplicative2X = Predefined::Multiplicative2X;

		/// @brief Alpha to Coverage
		/// @remark BlendState{ false, .alphaToCoverageEnable = true }	
		static constexpr Predefined OpaqueAlphaToCoverage = Predefined::OpaqueAlphaToCoverage;

		/// @brief アルファの最大値のみ更新
		/// @remark BlendState{ true, Blend::Zero, Blend::One, BlendOp::Add, Blend::SrcAlpha, Blend::DestAlpha, BlendOp::Max }
		static constexpr Predefined MaxAlpha = Predefined::MaxAlpha;

		/// @brief デフォルトのブレンド
		/// @remark BlendState{ true }	
		static constexpr Predefined Default2D = Predefined::Default2D;

		/// @brief デフォルトのブレンド
		/// @remark BlendState{ false }
		static constexpr Predefined Default3D = Predefined::Default3D;
	};
	static_assert(sizeof(BlendState) == sizeof(BlendState::storage_type));
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::BlendState>
{
	[[nodiscard]]
	size_t operator ()(const s3d::BlendState& value) const noexcept
	{
		return hash<s3d::BlendState::storage_type>()(value.asValue());
	}
};

# include "detail/BlendState.ipp"
