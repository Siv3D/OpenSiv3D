//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <atomic>
# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <shlobj.h>
# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"
# include "CDragDrop_Windows.hpp"
# include <Siv3D/Array.hpp>
# include <Siv3D/FileSystem.hpp>

#include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		class DropTarget : public IDropTarget
		{
		private:
		
			std::atomic<uint32> m_refCount = { 0 };

		public:

			HRESULT __stdcall QueryInterface(const IID& iid, void** ppv)
			{
				if (IsEqualIID(iid, IID_IUnknown) || IsEqualIID(iid, IID_IDropTarget))
				{
					*ppv = static_cast<IDropTarget*>(this);

					AddRef();

					return S_OK;
				}
				else
				{
					*ppv = nullptr;

					return E_NOINTERFACE;
				}				
			}

			ULONG __stdcall AddRef()
			{
				return ++m_refCount;
			}

			ULONG __stdcall Release()
			{
				if (--m_refCount == 0)
				{
					delete this;
				}

				return m_refCount;
			}

			HRESULT __stdcall DragEnter(IDataObject* pDataObj, DWORD, POINTL, DWORD* pdwEffect)
			{
				FORMATETC formatetc;
				formatetc.cfFormat	= CF_HDROP; // CF_TEXT
				formatetc.ptd		= nullptr;
				formatetc.dwAspect	= DVASPECT_CONTENT;
				formatetc.lindex	= -1;
				formatetc.tymed		= TYMED_HGLOBAL;

				if (FAILED(pDataObj->QueryGetData(&formatetc)))
				{
					/*
					*pdwEffect = DROPEFFECT_NONE;

					return DRAGDROP_S_CANCEL;
					*/

					formatetc.cfFormat = CF_TEXT;

					if (FAILED(pDataObj->QueryGetData(&formatetc)))
					{
						*pdwEffect = DROPEFFECT_NONE;

						return DRAGDROP_S_CANCEL;
					}
					else
					{
						*pdwEffect = DROPEFFECT_LINK;

						return S_OK;
					}
				}
				else
				{
					*pdwEffect = DROPEFFECT_COPY;

					return S_OK;
				}
			}

			HRESULT __stdcall DragOver(DWORD, POINTL pt, DWORD*)
			{
				//Log(L"DragOver");
				//Log(pt.x, L" ", pt.y);

				return S_OK;
			}

			HRESULT __stdcall DragLeave()
			{
				return S_OK;
			}

			HRESULT __stdcall Drop(IDataObject* pDataObj, DWORD, POINTL pt, DWORD*)
			{
				//Log(L"Drop");
				//Log(pt.x, L" ", pt.y);

				FORMATETC formatetc;
				formatetc.cfFormat	= CF_HDROP; // CF_TEXT
				formatetc.ptd		= nullptr;
				formatetc.dwAspect	= DVASPECT_CONTENT;
				formatetc.lindex	= -1;
				formatetc.tymed		= TYMED_HGLOBAL;

				if (FAILED(pDataObj->QueryGetData(&formatetc)))
				{
					formatetc.cfFormat = CF_TEXT;

					if (SUCCEEDED(pDataObj->QueryGetData(&formatetc)))
					{
						STGMEDIUM medium;

						if (FAILED(pDataObj->GetData(&formatetc, &medium)))
						{
							return E_FAIL;
						}

						if (const LPVOID pData = ::GlobalLock(medium.hGlobal))
						{
							Log(CharacterSet::FromUTF8(static_cast<char*>(pData)));

							::GlobalUnlock(medium.hGlobal);
						}

						return S_OK;
					}
					
					return DRAGDROP_S_CANCEL;
				}

				STGMEDIUM medium;
				
				if (FAILED(pDataObj->GetData(&formatetc, &medium)))
				{
					return E_FAIL;
				}

				Array<FilePath> droppedItems;

				if (HDROP hDrop = static_cast<HDROP>(::GlobalLock(medium.hGlobal)))
				{
					const size_t num_drops = ::DragQueryFileW(hDrop, 0xffFFffFF, nullptr, 0);

					droppedItems.resize(num_drops);

					wchar_t tmpFilePath[MAX_PATH];

					for (size_t i = 0; i < num_drops; ++i)
					{
						::DragQueryFileW(hDrop, i, tmpFilePath, MAX_PATH);

						droppedItems[i] = FileSystem::FullPath(tmpFilePath);
					}

					::GlobalUnlock(medium.hGlobal);
				}
				
				::ReleaseStgMedium(&medium);

				Log(droppedItems);

				return S_OK;
			}
		};
	}

	CDragDrop_Windows::CDragDrop_Windows()
	{
		
	}

	CDragDrop_Windows::~CDragDrop_Windows()
	{
		::RevokeDragDrop(Siv3DEngine::GetWindow()->getHandle());

		::OleUninitialize();
	}

	bool CDragDrop_Windows::init()
	{
		::OleInitialize(nullptr);

		detail::DropTarget* p = new detail::DropTarget;

		Log << (S_OK == p->QueryInterface(IID_IDropTarget, (void**)&m_pDropTarget));

		Log << (S_OK == ::RegisterDragDrop(Siv3DEngine::GetWindow()->getHandle(), m_pDropTarget));

		m_pDropTarget->Release();

		return true;
	}
	
	bool CDragDrop_Windows::update()
	{
		return true;
	}
}

# endif
