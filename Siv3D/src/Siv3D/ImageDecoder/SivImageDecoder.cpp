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

# include <Siv3D/ImageDecoder.hpp>
# include <Siv3D/BinaryReader.hpp>
# include "IImageDecoder.hpp"
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Browser.hpp>

namespace s3d
{
	namespace ImageDecoder
	{
		Optional<ImageInfo> GetImageInfo(const FilePathView path, const ImageFormat imageFormat)
		{
			BinaryReader reader(path);

			if (not reader)
			{
				return{};
			}

			return SIV3D_ENGINE(ImageDecoder)->getImageInfo(reader, path, imageFormat);
		}

		Optional<ImageInfo> GetImageInfo(IReader& reader, const ImageFormat imageFormat)
		{
			return SIV3D_ENGINE(ImageDecoder)->getImageInfo(reader, {}, imageFormat);
		}

		Image Decode(const FilePathView path, const ImageFormat imageFormat)
		{
		# if SIV3D_PLATFORM(WEB)
			Platform::Web::FetchFile(path);
		# endif

			BinaryReader reader(path);

			if (not reader)
			{
				return{};
			}

			return SIV3D_ENGINE(ImageDecoder)->decode(reader, path, imageFormat);
		}

		Image Decode(IReader& reader, const ImageFormat imageFormat)
		{
			return SIV3D_ENGINE(ImageDecoder)->decode(reader, {}, imageFormat);
		}

		Grid<uint16> DecodeGray16(FilePathView path, const ImageFormat imageFormat)
		{
			BinaryReader reader(path);

			if (not reader)
			{
				return{};
			}

			return SIV3D_ENGINE(ImageDecoder)->decodeGray16(reader, path, imageFormat);
		}

		Grid<uint16> DecodeGray16(IReader& reader, const ImageFormat imageFormat)
		{
			return SIV3D_ENGINE(ImageDecoder)->decodeGray16(reader, {}, imageFormat);
		}

		bool Add(std::unique_ptr<IImageDecoder>&& decoder)
		{
			return SIV3D_ENGINE(ImageDecoder)->add(std::move(decoder));
		}

		void Remove(const StringView name)
		{
			return SIV3D_ENGINE(ImageDecoder)->remove(name);
		}

		const Array<std::unique_ptr<IImageDecoder>>& Enum()
		{
			return SIV3D_ENGINE(ImageDecoder)->enumDecoder();
		}
	}
}
