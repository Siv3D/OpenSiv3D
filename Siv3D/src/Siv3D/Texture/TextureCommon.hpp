//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Byte.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ColorF.hpp>
# include <Siv3D/TextureFormat.hpp>

namespace s3d
{
	[[nodiscard]]
	Array<Byte> GenerateInitialColorBuffer(const Size& size, const ColorF& color, const TextureFormat& format);

	void FillByColor(void* const buffer, const Size& size, const uint32 dstStride, const ColorF& color, const TextureFormat& format);

	void FillRegionByColor(void* const buffer, const Size& size, const uint32 dstStride, const Rect& rect, const ColorF& color, const TextureFormat& format);

	void FillByImage(void* const buffer, const Size& size, const uint32 dstStride, const void* pData, const uint32 srcStride, const TextureFormat& format);

	void FillRegionByImage(void* const buffer, const Size& size, const uint32 dstStride, const void* pData, const uint32 srcStride, const Rect& rect, const TextureFormat& format);
}
