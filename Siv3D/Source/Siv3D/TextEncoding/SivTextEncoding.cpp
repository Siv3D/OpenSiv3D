//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TextEncoding.hpp>
# include <Siv3D/Utility.hpp>

namespace s3d
{
	namespace CharacterSet
	{
		TextEncoding GetEncoding(const IReader& reader, int32& bomSize)
		{
			bomSize = 0;

			if (!reader.isOpened())
			{
				return TextEncoding::UTF8;
			}

			if (reader.size() == 0)
			{
				return TextEncoding::Default;
			}

			{
				uint8 bom[3] = {};
				reader.lookahead(bom);

				if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)
				{
					bomSize = 3;
					return TextEncoding::UTF8;
				}
				else if (bom[0] == 0xFF && bom[1] == 0xFE)
				{
					bomSize = 2;
					return TextEncoding::UTF16LE;
				}
				else if (bom[0] == 0xFE && bom[1] == 0xFF)
				{
					bomSize = 2;
					return TextEncoding::UTF16BE;
				}
			}

			constexpr size_t bufferSize = 64 * 1024;

			uint8 buffer[bufferSize] = {};

			int64 sizeToRead = reader.size(), pos = 0, count = 0;

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
							return TextEncoding::ANSI;
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
							return TextEncoding::ANSI;
						}
					}
					else
					{
						if (!InRange<uint8>(c, 0x80, 0xBF))
						{
							return TextEncoding::ANSI;
						}

						--count;
					}

					if (count == 0)
					{
						head = true;
					}
				}
			}

			return TextEncoding::UTF8;
		}
	}
}