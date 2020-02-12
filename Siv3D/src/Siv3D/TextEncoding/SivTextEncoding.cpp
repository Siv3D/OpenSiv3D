//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TextEncoding.hpp>
# include <Siv3D/Utility.hpp>

namespace s3d
{
	namespace Unicode
	{
		TextEncoding GetTextEncoding(const IReader& reader)
		{
			if (!reader.isOpen())
			{
				return TextEncoding::UTF8_NO_BOM;
			}

			if (reader.size() == 0)
			{
				return TextEncoding::UTF8_NO_BOM;
			}

			{
				uint8 bom[3] = {};
				reader.lookahead(bom);

				if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)
				{
					return TextEncoding::UTF8;
				}
				else if (bom[0] == 0xFF && bom[1] == 0xFE)
				{
					return TextEncoding::UTF16LE;
				}
				else if (bom[0] == 0xFE && bom[1] == 0xFF)
				{
					return TextEncoding::UTF16BE;
				}
			}

			constexpr size_t bufferSize = 4096;

			uint8 buffer[bufferSize] = {};

			uint64 sizeToRead = reader.size(), pos = 0, count = 0;

			bool head = true;

			while (sizeToRead)
			{
				const int64 read = reader.lookahead(buffer, pos, sizeToRead > bufferSize ? bufferSize : sizeToRead);

				sizeToRead -= read;

				pos += read;

				for (int64 i = 0; i < read; ++i)
				{
					const uint8 c = buffer[i];

					if (head)
					{
						head = false;

						if (c <= 0x7F)
						{
							count = 0;
						}
						else if (c < 0xC2)
						{
							return TextEncoding::Unknown;
						}
						else if (c <= 0xDF)
						{
							count = 1;
						}
						else if (c <= 0xEF)
						{
							count = 2;
						}
						else if (c <= 0xF7)
						{
							count = 3;
						}
						else if (c <= 0xFB)
						{
							count = 4;
						}
						else if (c <= 0xFD)
						{
							count = 5;
						}
						else
						{
							return TextEncoding::Unknown;
						}
					}
					else
					{
						if (!InRange<uint8>(c, 0x80, 0xBF))
						{
							return TextEncoding::Unknown;
						}

						--count;
					}

					if (count == 0)
					{
						head = true;
					}
				}
			}

			return TextEncoding::UTF8_NO_BOM;
		}
	}
}
