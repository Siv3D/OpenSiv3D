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
		using StorageType = uint32;

		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct
			{
				bool enable : 3;

				Blend src : 5;

				Blend dest : 5;

				BlendOp op : 3;

				bool alphaToCoverageEnable : 3;

				Blend srcAlpha : 5;

				Blend destAlpha : 5;

				BlendOp opAlpha : 3;
			};

			StorageType _data;
		};

		S3D_DISABLE_MSVC_WARNINGS_POP()

		explicit BlendState(
			bool _enable = true,
			Blend _src = Blend::SrcAlpha,
			Blend _dest = Blend::InvSrcAlpha,
			BlendOp _op = BlendOp::Add,
			Blend _srcAlpha = Blend::Zero,
			Blend _destAlpha = Blend::One,
			BlendOp _opAlpha = BlendOp::Add,
			bool _alphaToCoverageEnable = false) noexcept
			: enable(_enable)
			, src(_src)
			, dest(_dest)
			, op(_op)
			, alphaToCoverageEnable(_alphaToCoverageEnable)
			, srcAlpha(_srcAlpha)
			, destAlpha(_destAlpha)
			, opAlpha(_opAlpha) {}

		bool operator ==(const BlendState& b) const noexcept
		{
			return _data == b._data;
		}

		bool operator !=(const BlendState& b) const noexcept
		{
			return _data != b._data;
		}
	};
}
