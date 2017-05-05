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

# pragma once
# include <functional>
# include "Fwd.hpp"

namespace s3d
{
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

	enum class BlendOp : uint8
	{
		Add			= 1,
		Subtract	= 2,
		RevSubtract	= 3,
		Min			= 4,
		Max			= 5
	};

	/// <summary>
	/// ブレンドステート
	/// </summary>
	struct BlendState
	{
	private:

		enum class Predefined
		{
			NonPremultiplied,

			Opaque,

			Additive,

			Subtractive,

			Multiplicative,

			Multiplicative2X,

			Default = NonPremultiplied,
		};

	public:

		using StorageType = uint32;

		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct
			{
				bool enable : 3;

				Blend src : 5;

				Blend dst : 5;

				BlendOp op : 3;

				bool alphaToCoverageEnable : 3;

				Blend srcAlpha : 5;

				Blend dstAlpha : 5;

				BlendOp opAlpha : 3;
			};

			StorageType _data;
		};

		S3D_DISABLE_MSVC_WARNINGS_POP()

		explicit BlendState(
			bool _enable = true,
			Blend _src = Blend::SrcAlpha,
			Blend _dst = Blend::InvSrcAlpha,
			BlendOp _op = BlendOp::Add,
			Blend _srcAlpha = Blend::Zero,
			Blend _dstAlpha = Blend::One,
			BlendOp _opAlpha = BlendOp::Add,
			bool _alphaToCoverageEnable = false) noexcept
			: enable(_enable)
			, src(_src)
			, dst(_dst)
			, op(_op)
			, alphaToCoverageEnable(_alphaToCoverageEnable)
			, srcAlpha(_srcAlpha)
			, dstAlpha(_dstAlpha)
			, opAlpha(_opAlpha) {}

		BlendState(Predefined predefined)
		{
			static const BlendState predefinedStates[6] =
			{
				BlendState{ true },																// NonPremultiplied
				BlendState{ false },																// Opaque
				BlendState{ true, Blend::SrcAlpha,	Blend::One,			BlendOp::Add },	// Additive
				BlendState{ true, Blend::SrcAlpha,	Blend::One,			BlendOp::RevSubtract },	// Subtractive
				BlendState{ true, Blend::Zero,		Blend::SrcColor,	BlendOp::Add },	// Multiplicative
				BlendState{ true, Blend::DestColor,	Blend::SrcColor,	BlendOp::Add },	// Multiplicative2X
			};

			*this = predefinedStates[static_cast<size_t>(predefined)];
		}

		bool operator ==(const BlendState& b) const noexcept
		{
			return _data == b._data;
		}

		bool operator !=(const BlendState& b) const noexcept
		{
			return _data != b._data;
		}

		/// <summary>
		/// デフォルトのブレンド
		/// BlendState{ true }
		/// </summary>
		static const Predefined NonPremultiplied = Predefined::NonPremultiplied;

		/// <summary>
		/// 不透明
		/// BlendState{ false }
		/// </summary>
		static const Predefined Opaque = Predefined::Opaque;

		/// <summary>
		/// 加算ブレンド
		/// BlendState{ true, Blend::SrcAlpha, Blend::One, BlendOp::Add }
		/// </summary>
		static const Predefined Additive = Predefined::Additive;

		/// <summary>
		/// 減算ブレンド
		/// BlendState{ true, Blend::SrcAlpha, Blend::One, BlendOp::RevSubtract }
		/// </summary>
		static const Predefined Subtractive = Predefined::Subtractive;

		/// <summary>
		/// 乗算ブレンド
		/// BlendState{ true, Blend::Zero, Blend::SrcColor, BlendOp::Add }
		/// </summary>
		static const Predefined Multiplicative = Predefined::Multiplicative;

		/// <summary>
		/// 2X 乗算ブレンド
		/// BlendState{ true, Blend::DestColor, Blend::SrcColor, BlendOp::Add }
		/// </summary>
		static const Predefined Multiplicative2X = Predefined::Multiplicative2X;

		/// <summary>
		/// デフォルトのブレンド
		/// BlendState{ true }
		/// </summary>
		static const Predefined Default = Predefined::Default;
	};
}

namespace std
{
	template <>
	struct hash<s3d::BlendState>
	{
		size_t operator()(const s3d::BlendState& keyVal) const
		{
			return hash<s3d::BlendState::StorageType>()(keyVal._data);
		}
	};
}
