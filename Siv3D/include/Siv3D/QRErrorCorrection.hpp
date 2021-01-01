//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	/// @brief 誤り訂正レベル
	enum class QRErrorCorrection
	{
		/// @brief 約 7%
		Low,

		/// @brief 約 15%
		Medium,

		/// @brief 約 25%
		Quartile,

		/// @brief 約 30%
		High,
	};
}
