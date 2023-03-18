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

# include <Siv3D/Script.hpp>
# include <Siv3D/ImageFormat.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterImageFormat(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;
		{
			constexpr char TypeName[] = "ImageFormat";
			r = engine->RegisterEnumValue(TypeName, "Unknown", static_cast<int32>(ImageFormat::Unknown)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "DDS", static_cast<int32>(ImageFormat::DDS)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "PNG", static_cast<int32>(ImageFormat::PNG)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "JPEG", static_cast<int32>(ImageFormat::JPEG)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "JPEG2000", static_cast<int32>(ImageFormat::JPEG2000)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "BMP", static_cast<int32>(ImageFormat::BMP)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "WebP", static_cast<int32>(ImageFormat::WebP)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "GIF", static_cast<int32>(ImageFormat::GIF)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "TIFF", static_cast<int32>(ImageFormat::TIFF)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "TGA", static_cast<int32>(ImageFormat::TGA)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "PPM", static_cast<int32>(ImageFormat::PPM)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "SVG", static_cast<int32>(ImageFormat::SVG)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Unspecified", static_cast<int32>(ImageFormat::Unspecified)); assert(r >= 0);
		}
	}

}
