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

namespace s3d
{
	/// @brief QR コードの誤り訂正レベル
	enum class QRErrorCorrection : uint8
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
