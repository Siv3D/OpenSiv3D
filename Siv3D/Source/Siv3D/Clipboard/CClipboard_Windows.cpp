//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"
# include "CClipboard_Windows.hpp"
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace detail
	{
		void LoadImageFromClipboard(Image& image)
		{
			const HANDLE hDIB = ::GetClipboardData(CF_DIBV5);

			if (!hDIB)
			{
				return;
			}

			const void* memory = reinterpret_cast<uint8*>(::GlobalLock(hDIB));

			const BITMAPV5HEADER* header = static_cast<const BITMAPV5HEADER*>(memory);
	
			if (header->bV5Size != sizeof(BITMAPV5HEADER)
				|| (header->bV5Compression != 0 && header->bV5Compression != 3))
			{
				::GlobalUnlock(hDIB);

				return;
			}
		
			//Log << L"----";
			//Log << header->bV5Size;
			//Log << header->bV5Width;
			//Log << header->bV5Height;
			//Log << header->bV5Planes;
			//Log << header->bV5BitCount;
			//Log << header->bV5Compression;
			//Log << header->bV5SizeImage;
			//Log << header->bV5XPelsPerMeter;
			//Log << header->bV5YPelsPerMeter;
			//Log << header->bV5ClrUsed;
			//Log << header->bV5ClrImportant;
			//Log << header->bV5RedMask;
			//Log << header->bV5GreenMask;
			//Log << header->bV5BlueMask;
			//Log << header->bV5AlphaMask;
			//Log << header->bV5CSType;
			//Log << header->bV5Endpoints;
			//Log << header->bV5GammaRed;
			//Log << header->bV5GammaGreen;
			//Log << header->bV5GammaBlue;
			//Log << header->bV5Intent;
			//Log << header->bV5ProfileData;
			//Log << header->bV5ProfileSize;
			//Log << header->bV5Reserved;
			//Log << L"----";

			const bool reversed	= header->bV5Height > 0;
			const int32 width	= header->bV5Width;
			const int32 height	= reversed ? header->bV5Height : -header->bV5Height;
			const bool hasAlpha = (header->bV5Compression == BI_BITFIELDS)
				&& (header->bV5BitCount == 32);

			image.resize(width, height);

			const uint8* data = static_cast<const uint8*>(memory) + sizeof(BITMAPV5HEADER);

			if (header->bV5Compression == BI_BITFIELDS)
			{
				data += 12;
			}

			switch (const int32 depth = header->bV5BitCount)
			{
			case 8:
				{
					uint8 palette[1024];
					::memcpy(palette, data, sizeof(palette));
					data += sizeof(palette);

					const uint32 rowSize = width + (width % 4 ? 4 - width % 4 : 0);
					const int32 lineStep = reversed ? -width : width;
					Color* pDstLine = image[reversed ? height - 1 : 0];
					uint8* const buffer = static_cast<uint8*>(::malloc(rowSize));

					for (int32 y = 0; y < height; ++y)
					{
						if (y == height - 1)
						{
							::memcpy(buffer, data, width);
							data += width;
						}
						else
						{
							::memcpy(buffer, data, rowSize);
							data += rowSize;
						}

						const uint8* pSrc = buffer;
						const Color* const pDstEnd = pDstLine + width;

						for (Color* pDst = pDstLine; pDst != pDstEnd; ++pDst)
						{
							const uint8 *src = palette + ((*pSrc++) << 2);
							
							pDst->set(src[2], src[1], src[0]);
						}

						pDstLine += lineStep;
					}

					::free(buffer);

					break;
				}
			case 24:
			case 32:
				{
					const size_t rowSize = depth == 24 ? width * 3 + width % 4 : width * 4;			
					const int32 depthBytes = depth / 8;
					const int32 lineStep = reversed ? -width : width;
					Color* pDstLine = image[reversed ? height - 1 : 0];
					uint8* const buffer = static_cast<uint8*>(::malloc(rowSize));

					for (int32 y = 0; y < height; ++y)
					{
						if (y == height - 1)
						{
							::memcpy(buffer, data, depthBytes * width);
							data += depthBytes * width;
						}
						else
						{
							::memcpy(buffer, data, rowSize);
							data += rowSize;
						}

						const Color* const pDstEnd = pDstLine + width;
						const uint8* pSrc = buffer;

						for (Color* pDst = pDstLine; pDst != pDstEnd; ++pDst)
						{
							pDst->set(pSrc[2], pSrc[1], pSrc[0], hasAlpha ? pSrc[3] : 255);

							pSrc += depthBytes;
						}

						pDstLine += lineStep;
					}

					::free(buffer);

					break;
				}
			}
			
			::GlobalUnlock(hDIB);
		}
	}

	CClipboard_Windows::CClipboard_Windows()
	{

	}

	CClipboard_Windows::~CClipboard_Windows()
	{

	}

	bool CClipboard_Windows::init()
	{
		m_sequenceNumber = ::GetClipboardSequenceNumber();

		return true;
	}

	void CClipboard_Windows::update()
	{
		const uint32 currentSequenceNumber = ::GetClipboardSequenceNumber();

		m_hasChanged = (currentSequenceNumber != m_sequenceNumber);

		m_sequenceNumber = currentSequenceNumber;

		if (!m_hasChanged)
		{
			return;
		}

		m_text.clear();
		m_image.clear();
		m_filePaths.clear();

		if (::IsClipboardFormatAvailable(CF_TEXT))
		{
			if (!::OpenClipboard(nullptr))
			{
				return;
			}

			if (const HGLOBAL hGlobal = static_cast<HGLOBAL>(::GetClipboardData(CF_TEXT)))
			{
				m_text = CharacterSet::Widen(static_cast<char*>(::GlobalLock(hGlobal)));

				::GlobalUnlock(hGlobal);
			}

			::CloseClipboard();
		}
		else if (::IsClipboardFormatAvailable(CF_DIBV5))
		{
			if (!::OpenClipboard(nullptr))
			{
				return;
			}
			
			detail::LoadImageFromClipboard(m_image);

			::CloseClipboard();
		}
		else if (::IsClipboardFormatAvailable(CF_HDROP))
		{
			if (!::OpenClipboard(nullptr))
			{
				return;
			}

			if (const HDROP hDrop = (HDROP)::GetClipboardData(CF_HDROP))
			{
				const uint32 dropSize = ::DragQueryFileW(hDrop, ~0u, nullptr, 0);

				m_filePaths.reserve(dropSize);

				wchar_t tmpFilePath[MAX_PATH];

				for (uint32 i = 0; i < dropSize; ++i)
				{
					::DragQueryFileW(hDrop, i, tmpFilePath, MAX_PATH);

					m_filePaths.push_back(FileSystem::FullPath(tmpFilePath));
				}
			}

			::CloseClipboard();
		}
	}

	bool CClipboard_Windows::hasChanged()
	{
		return m_hasChanged;
	}

	bool CClipboard_Windows::hasText()
	{
		return !m_text.isEmpty();
	}

	bool CClipboard_Windows::hasImage()
	{
		return !m_image.isEmpty();
	}

	bool CClipboard_Windows::hasFilePaths()
	{
		return !m_filePaths.isEmpty();
	}

	const String& CClipboard_Windows::getText()
	{
		return m_text;
	}

	const Image& CClipboard_Windows::getImage()
	{
		return m_image;
	}

	const Array<FilePath>& CClipboard_Windows::getFilePaths()
	{
		return m_filePaths;
	}

	void CClipboard_Windows::setText(const String& text)
	{
		if (!::OpenClipboard(nullptr))
		{
			return;
		}

		::EmptyClipboard();

		const size_t size = sizeof(char16_t) * (text.length() + 1);

		HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE, size);

		void* pDst = ::GlobalLock(hData);

		::memcpy(pDst, text.data(), size);
		
		::GlobalUnlock(hData);
		
		::SetClipboardData(CF_UNICODETEXT, hData);
		
		::CloseClipboard();
	}

	void CClipboard_Windows::setImage(const Image& image)
	{
		if (!::OpenClipboard(nullptr))
		{
			return;
		}

		::EmptyClipboard();

		const int32 width		= image.width();
		const int32 height		= image.height();
		const int32 rowSize		= ((width * 32 + 31) / 32) * 4;
		const size_t dataSize	= sizeof(BITMAPV5HEADER) + height * rowSize;
		HANDLE hData			= ::GlobalAlloc(GMEM_MOVEABLE, dataSize);
		uint8* const memory		= reinterpret_cast<uint8_t*>(::GlobalLock(hData));

		BITMAPV5HEADER header	= {};
		header.bV5Size			= sizeof(BITMAPV5HEADER);
		header.bV5Width			= width;
		header.bV5Height		= -height;
		header.bV5Planes		= 1;
		header.bV5BitCount		= 32;
		header.bV5Compression	= BI_RGB;
		header.bV5SizeImage		= height * rowSize;
		header.bV5RedMask		= 0x00FF0000;
		header.bV5GreenMask		= 0x0000FF00;
		header.bV5BlueMask		= 0x000000FF;
		header.bV5AlphaMask		= 0xFF000000;
		header.bV5CSType		= LCS_sRGB;
		header.bV5Intent		= LCS_GM_IMAGES;
		*(reinterpret_cast<BITMAPV5HEADER*>(memory)) = header;

		uint8* const pBegin = memory + sizeof(BITMAPV5HEADER);
		const Color* pSrc = image.data();

		for (int32 y = 0; y < height; ++y)
		{
			uint8* pDst = pBegin + rowSize * y;

			for (int32 x = 0; x < width; ++x)
			{
				*pDst++ = pSrc->b;
				*pDst++ = pSrc->g;
				*pDst++ = pSrc->r;
				*pDst++ = 255;
				++pSrc;
			}
		}

		::GlobalUnlock(hData);

		::SetClipboardData(CF_DIBV5, hData);

		::CloseClipboard();
	}

	void CClipboard_Windows::clear()
	{
		if (!::OpenClipboard(nullptr))
		{
			return;
		}

		::EmptyClipboard();

		::CloseClipboard();
		
		m_text.clear();
		m_image.clear();
		m_filePaths.clear();
	}
}

# endif
