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

# include <Siv3D/TextEncoding.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	namespace Unicode
	{
		TextEncoding GetTextEncoding(const IReader& reader)
		{
			if (not reader.isOpen())
			{
				return TextEncoding::UTF8_NO_BOM;
			}

			if (reader.size() == 0)
			{
				return TextEncoding::UTF8_NO_BOM;
			}

			{
				uint8 bom[3] = {};
				
				if (not reader.lookahead(bom))
				{
					return TextEncoding::UTF8_NO_BOM;
				}

				if ((bom[0] == 0xEF) && (bom[1] == 0xBB) && (bom[2] == 0xBF))
				{
					return TextEncoding::UTF8_WITH_BOM;
				}
				else if ((bom[0] == 0xFF) && (bom[1] == 0xFE))
				{
					return TextEncoding::UTF16LE;
				}
				else if ((bom[0] == 0xFE) && (bom[1] == 0xFF))
				{
					return TextEncoding::UTF16BE;
				}

				return TextEncoding::UTF8_NO_BOM;
			}
		}

		TextEncoding GetTextEncoding(const FilePathView path)
		{
			return GetTextEncoding(BinaryReader{ path });
		}
	}
}
