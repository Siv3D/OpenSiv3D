//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
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
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Time.hpp>

#include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		class DropTarget : public IDropTarget
		{
		private:

			HWND m_hWnd = nullptr;

			std::atomic<uint32> m_refCount = { 0 };

			std::mutex m_mutex;

			Array<DroppedFilePath> m_droppedFilePaths;

			Array<DroppedText> m_droppedTexts;

			DragItemType m_itemType = DragItemType::FilePaths;

			Point m_dragOverPos = Point::Zero();

			bool m_dragOver = false;

			bool m_acceptFilePath = true;

			bool m_acceptText = false;

		public:

			explicit DropTarget(HWND hWnd)
				: IDropTarget()
				, m_hWnd(hWnd) {}

			HRESULT __stdcall QueryInterface(const IID& iid, void** ppv) override
			{
				if (IsEqualIID(iid, IID_IUnknown) || IsEqualIID(iid, IID_IDropTarget))
				{
					AddRef();

					*ppv = static_cast<IDropTarget*>(this);

					return S_OK;
				}
				else
				{
					*ppv = nullptr;

					return E_NOINTERFACE;
				}				
			}

			ULONG __stdcall AddRef() override
			{
				return ++m_refCount;
			}

			ULONG __stdcall Release() override
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
				formatetc.cfFormat	= CF_HDROP;
				formatetc.ptd		= nullptr;
				formatetc.dwAspect	= DVASPECT_CONTENT;
				formatetc.lindex	= -1;
				formatetc.tymed		= TYMED_HGLOBAL;

				std::lock_guard<std::mutex> resourceGuard(m_mutex);

				if (m_acceptFilePath && SUCCEEDED(pDataObj->QueryGetData(&formatetc)))
				{
					*pdwEffect = DROPEFFECT_COPY;

					m_itemType = DragItemType::FilePaths;

					m_dragOver = true;

					return S_OK;
				}

				formatetc.cfFormat = CF_UNICODETEXT;

				if (m_acceptText && SUCCEEDED(pDataObj->QueryGetData(&formatetc)))
				{
					*pdwEffect = DROPEFFECT_LINK;

					m_itemType = DragItemType::Text;

					m_dragOver = true;

					return S_OK;
				}

				*pdwEffect = DROPEFFECT_NONE;

				return DRAGDROP_S_CANCEL;
			}

			HRESULT __stdcall DragOver(DWORD, POINTL pt, DWORD*)
			{
				std::lock_guard<std::mutex> resourceGuard(m_mutex);

				POINT pos{ pt.x, pt.y };

				::ScreenToClient(m_hWnd, &pos);

				m_dragOverPos.set(pos.x, pos.y);

				return S_OK;
			}

			HRESULT __stdcall DragLeave()
			{
				std::lock_guard<std::mutex> resourceGuard(m_mutex);

				m_dragOver = false;

				return S_OK;
			}

			HRESULT __stdcall Drop(IDataObject* pDataObj, DWORD, POINTL pt, DWORD*)
			{
				std::lock_guard<std::mutex> resourceGuard(m_mutex);

				POINT pos{ pt.x, pt.y };

				::ScreenToClient(m_hWnd, &pos);

				m_dragOverPos.set(pos.x, pos.y);

				m_dragOver = false;

				FORMATETC formatetc;
				formatetc.cfFormat	= m_itemType == DragItemType::FilePaths ? CF_HDROP : CF_UNICODETEXT;
				formatetc.ptd		= nullptr;
				formatetc.dwAspect	= DVASPECT_CONTENT;
				formatetc.lindex	= -1;
				formatetc.tymed		= TYMED_HGLOBAL;

				if ((!m_acceptFilePath && m_itemType == DragItemType::FilePaths)
					|| (!m_acceptText && m_itemType == DragItemType::Text))
				{
					return DRAGDROP_S_CANCEL;
				}

				if (FAILED(pDataObj->QueryGetData(&formatetc)))
				{
					return E_FAIL;
				}

				STGMEDIUM medium;
				{
					if (FAILED(pDataObj->GetData(&formatetc, &medium)))
					{
						return E_FAIL;
					}

					uint64 timeMillisec = Time::GetMillisec();

					if (m_itemType == DragItemType::Text)
					{
						if (const LPVOID pData = ::GlobalLock(medium.hGlobal))
						{
							m_droppedTexts.push_back({ String(static_cast<const wchar*>(pData)), m_dragOverPos, timeMillisec });

							::GlobalUnlock(medium.hGlobal);
						}
					}
					else
					{
						if (HDROP hDrop = static_cast<HDROP>(::GlobalLock(medium.hGlobal)))
						{
							const size_t num_drops = ::DragQueryFileW(hDrop, 0xffFFffFF, nullptr, 0);

							wchar tmpFilePath[MAX_PATH];

							for (uint32 i = 0; i < num_drops; ++i)
							{
								::DragQueryFileW(hDrop, i, tmpFilePath, MAX_PATH);

								m_droppedFilePaths.push_back({ FileSystem::FullPath(tmpFilePath), m_dragOverPos, timeMillisec });
							}

							::GlobalUnlock(medium.hGlobal);
						}
					}
				}
				::ReleaseStgMedium(&medium);

				return S_OK;
			}

			void acceptFilePaths(const bool accept)
			{
				std::lock_guard<std::mutex> resourceGuard(m_mutex);

				m_acceptFilePath = accept;
			}

			void acceptText(const bool accept)
			{
				std::lock_guard<std::mutex> resourceGuard(m_mutex);

				m_acceptText = accept;
			}

			std::tuple<Array<DroppedFilePath>, Array<DroppedText>, DragItemType, Point, bool> getStatus()
			{
				std::lock_guard<std::mutex> resourceGuard(m_mutex);

				const std::tuple<Array<DroppedFilePath>, Array<DroppedText>, DragItemType, Point, bool> status{ m_droppedFilePaths, m_droppedTexts, m_itemType, m_dragOverPos, m_dragOver };

				m_droppedFilePaths.clear();

				m_droppedTexts.clear();

				return status;
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

		HWND hWnd = Siv3DEngine::GetWindow()->getHandle();

		detail::DropTarget* p = new detail::DropTarget(hWnd);

		if (FAILED(p->QueryInterface(IID_IDropTarget, (void**)&m_pDropTarget)))
		{
			return false;
		}

		if (FAILED(::RegisterDragDrop(hWnd, m_pDropTarget)))
		{
			return false;
		}

		m_pDropTarget->Release();

		return true;
	}
	
	bool CDragDrop_Windows::update()
	{
		const auto status = m_pDropTarget->getStatus();

		const Array<DroppedFilePath>& filePaths = std::get<Array<DroppedFilePath>>(status);
		
		m_droppedFilePaths.insert(m_droppedFilePaths.end(), filePaths.begin(), filePaths.end());

		const Array<DroppedText>& texts = std::get<Array<DroppedText>>(status);

		m_droppedTexts.insert(m_droppedTexts.end(), texts.begin(), texts.end());

		m_dragOver = std::get<bool>(status);

		m_itemType = std::get<DragItemType>(status);

		m_dragOverPos = std::get<Point>(status);

		return true;
	}

	void CDragDrop_Windows::acceptFilePaths(const bool accept)
	{
		m_pDropTarget->acceptFilePaths(accept);
	}

	void CDragDrop_Windows::acceptText(const bool accept)
	{
		m_pDropTarget->acceptText(accept);
	}

	Optional<DragStatus> CDragDrop_Windows::dragOver() const
	{
		if (!m_dragOver)
		{
			return none;
		}

		return DragStatus{ m_itemType, m_dragOverPos };
	}

	bool CDragDrop_Windows::hasNewFilePaths() const
	{
		return !m_droppedFilePaths.isEmpty();
	}

	bool CDragDrop_Windows::hasNewText() const
	{
		return !m_droppedTexts.isEmpty();
	}

	void CDragDrop_Windows::clear()
	{
		m_droppedFilePaths.clear();

		m_droppedTexts.clear();
	}

	Array<DroppedFilePath> CDragDrop_Windows::getDroppedFilePaths()
	{
		Array<DroppedFilePath> dropped(std::move(m_droppedFilePaths));

		return dropped;
	}

	Array<DroppedText> CDragDrop_Windows::getDroppedText()
	{
		Array<DroppedText> dropped(std::move(m_droppedTexts));

		return dropped;
	}
}

# endif
