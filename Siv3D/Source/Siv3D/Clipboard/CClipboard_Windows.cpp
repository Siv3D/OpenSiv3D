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
# include <Siv3D/ReaderView.hpp>

namespace s3d
{
	namespace detail
	{
		static bool HasInvalidPremultipliedColors(const Color* image, const size_t num_pixels)
		{
			const Color* pSrc = image;
			const Color* const pSrcEnd = pSrc + num_pixels;

			while (pSrc != pSrcEnd)
			{
				if (pSrc->r > pSrc->a || pSrc->g > pSrc->a || pSrc->b > pSrc->a)
				{
					return true;
				}

				++pSrc;
			}

			return false;
		}

		static void LoadImageFromClipboard(Image& image)
		{
			const HANDLE hDIB = ::GetClipboardData(CF_DIB);

			if (!hDIB)
			{
				return;
			}

			const size_t memorySize = ::GlobalSize(hDIB);

			if (const void* memory = reinterpret_cast<uint8*>(::GlobalLock(hDIB)))
			{
				const BITMAPINFO* header = static_cast<const BITMAPINFO*>(memory);
				const int32 depth = header->bmiHeader.biBitCount;

				size_t colorTableSize = 0;

				if (depth == 8)
				{
					colorTableSize = header->bmiHeader.biClrUsed ? header->bmiHeader.biClrUsed
						: (1 << header->bmiHeader.biBitCount);
				}
				else if (depth == 32 && header->bmiHeader.biCompression == BI_BITFIELDS)
				{
					colorTableSize = 3;
				}

				const size_t offsetSize = header->bmiHeader.biSize + colorTableSize * sizeof(RGBQUAD);
				const void* bitmapData = static_cast<const Byte*>(memory) + offsetSize;

				const bool reversed	= header->bmiHeader.biHeight > 0;
				const int32 width	= header->bmiHeader.biWidth;
				const int32 height	= reversed ? header->bmiHeader.biHeight : -header->bmiHeader.biHeight;	
				const bool hasAlpha = (depth == 32)
					&& !HasInvalidPremultipliedColors(static_cast<const Color*>(bitmapData), width * height);
				image.resize(width, height);

				ReaderView reader(bitmapData, memorySize - offsetSize);

				switch (depth)
				{
				case 8:
					{
						uint8 palette[1024];
						reader.read(palette);

						const uint32 rowSize = width + (width % 4 ? 4 - width % 4 : 0);
						const int32 lineStep = reversed ? -width : width;
						Color* pDstLine = image[reversed ? height - 1 : 0];
						uint8* const buffer = static_cast<uint8*>(::malloc(rowSize));

						for (int32 y = 0; y < height; ++y)
						{
							if (y == height - 1)
							{
								reader.read(buffer, width);
							}
							else
							{
								reader.read(buffer, rowSize);
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
								reader.read(buffer, depthBytes * width);
							}
							else
							{
								reader.read(buffer, rowSize);
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

			}
			::GlobalUnlock(hDIB);
		}

		static void WriteBitmapToClipboard(HBITMAP hSourceBitmap, const Size& size)
		{
			HDC hDC				= ::GetDC(nullptr);
			HDC hCompatibleDC	= ::CreateCompatibleDC(nullptr);
			HDC hSourceDC		= ::CreateCompatibleDC(nullptr);
			HBITMAP hBitmap		= ::CreateCompatibleBitmap(hDC, size.x, size.y);
	
			if (!hBitmap)
			{
				::DeleteDC(hCompatibleDC);
				::DeleteDC(hSourceDC);
				::ReleaseDC(nullptr, hDC);
				return;
			}

			HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hCompatibleDC, hBitmap);
			HBITMAP hOldSource = (HBITMAP)::SelectObject(hSourceDC, hSourceBitmap);
			{
				const BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
				::GdiAlphaBlend(hCompatibleDC, 0, 0, size.x, size.y, hSourceDC, 0, 0, size.x, size.y, blend);
			}
			::SelectObject(hCompatibleDC, hOldBitmap);
			::SelectObject(hSourceDC, hOldSource);
			
			::DeleteObject(hOldBitmap);
			::DeleteObject(hOldSource);
			::DeleteDC(hCompatibleDC);
			::DeleteDC(hSourceDC);
			::ReleaseDC(nullptr, hDC);

			if (::OpenClipboard(nullptr))
			{
				::EmptyClipboard();
				::SetClipboardData(CF_BITMAP, hBitmap);
				::CloseClipboard();
			}

			::DeleteObject(hBitmap);
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
		else if (::IsClipboardFormatAvailable(CF_DIB))
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
		const size_t size = sizeof(char16_t) * (text.length() + 1);

		HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE, size);

		void* pDst = ::GlobalLock(hData);

		::memcpy(pDst, text.data(), size);
		
		::GlobalUnlock(hData);
		
		if (!::OpenClipboard(nullptr))
		{
			::EmptyClipboard();
			::SetClipboardData(CF_UNICODETEXT, hData);
			::CloseClipboard();
		}

		::GlobalFree(hData);
	}

	void CClipboard_Windows::setImage(const Image& image)
	{
		HDC hDC = ::GetDC(nullptr);
		BITMAPINFO header = {};
		header.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
		header.bmiHeader.biWidth		= image.width();
		header.bmiHeader.biHeight		= -image.height();
		header.bmiHeader.biPlanes		= 1;
		header.bmiHeader.biBitCount		= 32;
		header.bmiHeader.biCompression	= BI_RGB;

		void* bitmapData;
		HBITMAP hBitmap = ::CreateDIBSection(hDC, &header, DIB_RGB_COLORS, &bitmapData, nullptr, 0);

		if (bitmapData && hBitmap)
		{
			const Color* pSrc = image.data();
			const Color* pSrcEnd = pSrc + image.num_pixels();
			Color* pDst = static_cast<Color*>(bitmapData);

			while (pSrc != pSrcEnd)
			{
				if (pSrc->a == 255)
				{
					pDst->r = pSrc->b;
					pDst->g = pSrc->g;
					pDst->b = pSrc->r;
					pDst->a = 255;
				}
				else
				{
					const float fa = pSrc->a / 255.0f;
					pDst->r = static_cast<uint8>(pSrc->b * fa);
					pDst->g = static_cast<uint8>(pSrc->g * fa);
					pDst->b = static_cast<uint8>(pSrc->r * fa);
					pDst->a = pSrc->a;
				}

				++pDst;
				++pSrc;
			}

			detail::WriteBitmapToClipboard(hBitmap, image.size());
		}

		::DeleteObject(hBitmap);
		::ReleaseDC(nullptr, hDC);
	}

	void CClipboard_Windows::clear()
	{
		if (::OpenClipboard(nullptr))
		{
			::EmptyClipboard();
			::CloseClipboard();
		}
	
		m_text.clear();
		m_image.clear();
		m_filePaths.clear();
	}
}

# endif
