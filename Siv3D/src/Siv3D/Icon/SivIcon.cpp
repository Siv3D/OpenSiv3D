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

# include <Siv3D/Icon.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	bool Icon::HasGlyph(const uint32 code)
	{
		return HasGlyph(detail::GetIconType(code), code);
	}

	bool Icon::HasGlyph(const Type type, const uint32 code)
	{
		return SIV3D_ENGINE(Font)->hasIcon(type, code);
	}

	Image Icon::CreateImage(const uint32 code, const int32 size)
	{
		return CreateImage(detail::GetIconType(code), code, size);
	}

	Image Icon::CreateImage(const Type type, const uint32 code, const int32 size)
	{
		return SIV3D_ENGINE(Font)->renderIconBitmap(type, code, size);
	}

	Image Icon::CreateSDFImage(const uint32 code, const int32 size, const int32 buffer)
	{
		return CreateSDFImage(detail::GetIconType(code), code, size, buffer);
	}

	Image Icon::CreateSDFImage(const Type type, const uint32 code, const int32 size, const int32 buffer)
	{
		return SIV3D_ENGINE(Font)->renderIconSDF(type, code, size, buffer);
	}

	Image Icon::CreateMSDFImage(const uint32 code, const int32 size, const int32 buffer)
	{
		return CreateMSDFImage(detail::GetIconType(code), code, size, buffer);
	}

	Image Icon::CreateMSDFImage(const Type type, const uint32 code, const int32 size, const int32 buffer)
	{
		return SIV3D_ENGINE(Font)->renderIconMSDF(type, code, size, buffer);
	}
}
