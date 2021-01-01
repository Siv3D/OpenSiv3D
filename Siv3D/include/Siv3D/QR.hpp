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
# include "Common.hpp"
# include "Fwd.hpp"
# include "Grid.hpp"
# include "QRErrorCorrection.hpp"

namespace s3d
{
	namespace QR
	{
		/// @brief 
		inline constexpr int32 MinVersion = 1;

		/// @brief 
		inline constexpr int32 MaxVersion = 40;

		[[nodiscard]]
		Grid<bool> EncodeNumber(StringView s, QRErrorCorrection ec = QRErrorCorrection::Low, int32 minVersion = MinVersion);

		[[nodiscard]]
		Grid<bool> EncodeAlnum(StringView s, QRErrorCorrection ec = QRErrorCorrection::Low, int32 minVersion = MinVersion);

		[[nodiscard]]
		Grid<bool> EncodeText(StringView s, QRErrorCorrection ec = QRErrorCorrection::Low, int32 minVersion = MinVersion);

		[[nodiscard]]
		Grid<bool> EncodeBinary(const void* data, size_t size, QRErrorCorrection ec = QRErrorCorrection::Low, int32 minVersion = MinVersion);

		Image MakeImage(const Grid<bool>& qr, int32 cellSize = 16, size_t borderCells = 4);

		bool SaveSVG(FilePathView path, const Grid<bool>& code, size_t borderCells = 4);
	}
}
