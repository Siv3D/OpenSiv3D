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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include "CDragDrop.hpp"
# include <shlobj.h>

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
					return 0;
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

				std::lock_guard resourceGuard(m_mutex);

				if (SUCCEEDED(pDataObj->QueryGetData(&formatetc)))
				{
					if (m_acceptFilePath)
					{
						*pdwEffect = DROPEFFECT_COPY;

						m_itemType = DragItemType::FilePaths;

						m_dragOver = true;

						return S_OK;
					}
					else
					{
						*pdwEffect = DROPEFFECT_NONE;
						return DRAGDROP_S_CANCEL;
					}
				}

				formatetc.cfFormat = CF_UNICODETEXT;

				if (SUCCEEDED(pDataObj->QueryGetData(&formatetc)))
				{
					if (m_acceptText)
					{
						*pdwEffect = DROPEFFECT_LINK;

						m_itemType = DragItemType::Text;

						m_dragOver = true;

						return S_OK;
					}
					else
					{
						*pdwEffect = DROPEFFECT_NONE;
						return DRAGDROP_S_CANCEL;
					}
				}

				*pdwEffect = DROPEFFECT_NONE;
				return DRAGDROP_S_CANCEL;
			}

			HRESULT __stdcall DragOver(DWORD, POINTL pt, DWORD*)
			{
				std::lock_guard resourceGuard(m_mutex);

				POINT pos{ pt.x, pt.y };

				::ScreenToClient(m_hWnd, &pos);

				m_dragOverPos.set(pos.x, pos.y);

				return S_OK;
			}

			HRESULT __stdcall DragLeave()
			{
				std::lock_guard resourceGuard(m_mutex);

				m_dragOver = false;

				return S_OK;
			}

			HRESULT __stdcall Drop(IDataObject* pDataObj, DWORD, POINTL pt, DWORD*)
			{
				std::lock_guard resourceGuard(m_mutex);

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
							m_droppedTexts.push_back({ Unicode::FromWstring(static_cast<const wchar_t*>(pData)), m_dragOverPos, timeMillisec });

							::GlobalUnlock(medium.hGlobal);
						}
					}
					else
					{
						if (HDROP hDrop = static_cast<HDROP>(::GlobalLock(medium.hGlobal)))
						{
							const size_t num_drops = ::DragQueryFileW(hDrop, 0xffFFffFF, nullptr, 0);

							wchar_t tmpFilePath[MAX_PATH];

							for (uint32 i = 0; i < num_drops; ++i)
							{
								::DragQueryFileW(hDrop, i, tmpFilePath, MAX_PATH);

								m_droppedFilePaths.emplace_back(FileSystem::FullPath(Unicode::FromWstring(tmpFilePath)), m_dragOverPos, timeMillisec);
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
				std::lock_guard resourceGuard(m_mutex);

				m_acceptFilePath = accept;
			}

			void acceptText(const bool accept)
			{
				std::lock_guard resourceGuard(m_mutex);

				m_acceptText = accept;
			}

			std::tuple<Array<DroppedFilePath>, Array<DroppedText>, DragItemType, Point, bool> getStatus()
			{
				std::lock_guard resourceGuard(m_mutex);

				const std::tuple<Array<DroppedFilePath>, Array<DroppedText>, DragItemType, Point, bool> status{ m_droppedFilePaths, m_droppedTexts, m_itemType, m_dragOverPos, m_dragOver };

				m_droppedFilePaths.clear();

				m_droppedTexts.clear();

				return status;
			}
		};

		class DropSource : public IDropSource
		{
		private:

			std::atomic<uint32> m_refCount = { 0 };

		public:

			DropSource()
				: m_refCount(1)
			{

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
					return 0;
				}

				return m_refCount;
			}

			HRESULT __stdcall QueryInterface(REFIID iid, void** ppv) override
			{
				if (IsEqualIID(iid, IID_IUnknown) || IsEqualIID(iid, IID_IDropSource))
				{
					AddRef();

					*ppv = this;

					return S_OK;
				}
				else
				{
					*ppv = nullptr;

					return E_NOINTERFACE;
				}
			}

			HRESULT __stdcall QueryContinueDrag(BOOL escapePressed, DWORD keyState) override
			{
				if (escapePressed)
				{
					return DRAGDROP_S_CANCEL;
				}

				if ((keyState & (MK_LBUTTON | MK_RBUTTON)) == (MK_LBUTTON | MK_RBUTTON))
				{
					return DRAGDROP_S_CANCEL;
				}

				if ((keyState & (MK_LBUTTON | MK_RBUTTON)) == 0)
				{
					return DRAGDROP_S_DROP;
				}

				return S_OK;
			}

			HRESULT __stdcall GiveFeedback(DWORD) override
			{
				return DRAGDROP_S_USEDEFAULTCURSORS;
			}
		};

		static void CopyFormatEtc(FORMATETC *dst, FORMATETC *src)
		{
			*dst = *src;

			if (src->ptd)
			{
				dst->ptd = static_cast<DVTARGETDEVICE*>(::CoTaskMemAlloc(sizeof(DVTARGETDEVICE)));

				if (dst->ptd)
				{
					*(dst->ptd) = *(src->ptd);
				}
			}
		}

		static HRESULT CreateEnumFormatEtc(size_t nNumFormats, FORMATETC *pFormatEtc, IEnumFORMATETC **ppEnumFormatEtc);

		class CEnumFormatEtc : public IEnumFORMATETC
		{
		private:

			std::atomic<uint32> m_refCount = { 0 };

			size_t m_index = 0;

			Array<FORMATETC> m_formatEtcs;

		public:

			CEnumFormatEtc(FORMATETC* pFormatEtc, size_t nNumFormats)
				: m_refCount(1)
				, m_formatEtcs(nNumFormats)
			{
				for (size_t i = 0; i < nNumFormats; ++i)
				{
					CopyFormatEtc(&m_formatEtcs[i], &pFormatEtc[i]);
				}
			}

			~CEnumFormatEtc()
			{
				for (auto& formatEtc : m_formatEtcs)
				{
					::CoTaskMemFree(formatEtc.ptd);
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
					return 0;
				}

				return m_refCount;
			}

			HRESULT __stdcall QueryInterface(REFIID iid, void** ppv) override
			{
				if (IsEqualIID(iid, IID_IUnknown) || IsEqualIID(iid, IID_IEnumFORMATETC))
				{
					AddRef();

					*ppv = this;

					return S_OK;
				}
				else
				{
					*ppv = nullptr;

					return E_NOINTERFACE;
				}
			}

			HRESULT __stdcall Next(ULONG celt, FORMATETC* pFormatEtc, ULONG* pceltFetched) override
			{
				if (celt == 0 || pFormatEtc == 0)
				{
					return E_INVALIDARG;
				}

				ULONG copied = 0;

				while (m_index < m_formatEtcs.size() && copied < celt)
				{
					CopyFormatEtc(&pFormatEtc[copied], &m_formatEtcs[m_index]);
					++copied;
					++m_index;
				}

				if (pceltFetched != nullptr)
				{
					*pceltFetched = copied;
				}

				return (copied == celt) ? S_OK : S_FALSE;
			}

			HRESULT __stdcall Skip(ULONG celt) override
			{
				m_index += celt;

				return (m_index <= m_formatEtcs.size()) ? S_OK : S_FALSE;
			}

			HRESULT __stdcall Reset() override
			{
				m_index = 0;

				return S_OK;
			}

			HRESULT __stdcall Clone(IEnumFORMATETC** ppEnumFormatEtc) override
			{
				HRESULT hr = CreateEnumFormatEtc(m_formatEtcs.size(), m_formatEtcs.data(), ppEnumFormatEtc);

				if (SUCCEEDED(hr))
				{
					((CEnumFormatEtc*)*ppEnumFormatEtc)->m_index = m_index;
				}

				return hr;
			}
		};

		static HRESULT CreateEnumFormatEtc(size_t nNumFormats, FORMATETC* pFormatEtc, IEnumFORMATETC** ppEnumFormatEtc)
		{
			if (nNumFormats == 0 || pFormatEtc == 0 || ppEnumFormatEtc == 0)
			{
				return E_INVALIDARG;
			}

			*ppEnumFormatEtc = new CEnumFormatEtc(pFormatEtc, nNumFormats);

			return (*ppEnumFormatEtc) ? S_OK : E_OUTOFMEMORY;
		}

		static HGLOBAL Copy(HGLOBAL hMem)
		{
			const size_t size = ::GlobalSize(hMem);

			PVOID pDst = ::GlobalAlloc(GMEM_FIXED, size);

			if (pDst)
			{
				if (const PVOID pSrc = ::GlobalLock(hMem))
				{
					std::memcpy(pDst, pSrc, size);

					::GlobalUnlock(hMem);
				}
			}

			return pDst;
		}

		class DataObject : public IDataObject
		{
		private:

			std::atomic<uint32> m_refCount = { 0 };

			Array<FORMATETC> m_formatEtcs;

			Array<STGMEDIUM> m_stgMediums;

			int32 indexOfFormatEtc(FORMATETC* pFormatEtc) const
			{
				int32 index = 0;

				for (const auto& formatEtc : m_formatEtcs)
				{
					if ((pFormatEtc->tymed & formatEtc.tymed)
						&& (pFormatEtc->cfFormat == formatEtc.cfFormat)
						&& (pFormatEtc->dwAspect == formatEtc.dwAspect))
					{
						return index;
					}

					++index;
				}

				return -1;
			}

		public:

			DataObject(FORMATETC* fmtetc, STGMEDIUM* stgmed, size_t count)
				: m_refCount(1)
				, m_formatEtcs(count)
				, m_stgMediums(count)
			{
				for (size_t i = 0; i < count; ++i)
				{
					m_formatEtcs[i] = fmtetc[i];
					m_stgMediums[i] = stgmed[i];
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
					return 0;
				}

				return m_refCount;
			}

			HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject) override
			{
				if (IsEqualIID(iid, IID_IUnknown) || IsEqualIID(iid, IID_IDataObject))
				{
					AddRef();

					*ppvObject = this;

					return S_OK;
				}
				else
				{
					*ppvObject = nullptr;

					return E_NOINTERFACE;
				}
			}

			HRESULT __stdcall GetData(FORMATETC *pFormatEtc, STGMEDIUM *pMedium) override
			{
				if (!(pFormatEtc->tymed &TYMED_HGLOBAL)
					|| (pFormatEtc->cfFormat != CF_HDROP)
					|| (pFormatEtc->dwAspect != DVASPECT_CONTENT))
				{
					return DV_E_FORMATETC;
				}

				QueryGetData(pFormatEtc);

				int32 index = indexOfFormatEtc(pFormatEtc);

				if (index == -1)
				{
					return DV_E_FORMATETC;
				}

				pMedium->tymed = m_formatEtcs[index].tymed;
				pMedium->pUnkForRelease = nullptr;

				if (m_formatEtcs[index].tymed == TYMED_HGLOBAL)
				{
					pMedium->hGlobal = Copy(m_stgMediums[index].hGlobal);

					return S_OK;
				}
				else
				{
					return DV_E_FORMATETC;
				}
			}

			HRESULT __stdcall GetDataHere(FORMATETC*, STGMEDIUM*) override
			{
				return DATA_E_FORMATETC;
			}

			HRESULT __stdcall QueryGetData(FORMATETC* pFmtC) override
			{
				if ((pFmtC->tymed &TYMED_HGLOBAL)
					&& (pFmtC->cfFormat == CF_HDROP)
					&& (pFmtC->dwAspect == DVASPECT_CONTENT))
				{
					return (indexOfFormatEtc(pFmtC) == -1) ? DV_E_FORMATETC : S_OK;
				}
				else
				{
					return DV_E_FORMATETC;
				}
			}

			HRESULT __stdcall GetCanonicalFormatEtc(FORMATETC*, FORMATETC* pFormatEtcOut) override
			{
				pFormatEtcOut->ptd = nullptr;

				return E_NOTIMPL;
			}

			HRESULT __stdcall SetData(FORMATETC*, STGMEDIUM*, BOOL) override
			{
				return E_NOTIMPL;
			}

			HRESULT __stdcall EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC** ppEnumFormatEtc) override
			{
				if (dwDirection == DATADIR_GET)
				{
					return CreateEnumFormatEtc(m_formatEtcs.size(), m_formatEtcs.data(), ppEnumFormatEtc);
				}
				else
				{
					return E_NOTIMPL;
				}
			}

			HRESULT __stdcall DAdvise(FORMATETC*, DWORD, IAdviseSink*, DWORD*) override
			{
				return OLE_E_ADVISENOTSUPPORTED;
			}

			HRESULT __stdcall DUnadvise(DWORD) override
			{
				return OLE_E_ADVISENOTSUPPORTED;
			}

			HRESULT __stdcall EnumDAdvise(IEnumSTATDATA**) override
			{
				return OLE_E_ADVISENOTSUPPORTED;
			}
		};

		static void BeginDrop(IDataObject** lpDataObejct, IDropSource** lpDropSource, const Array<FilePath>& paths)
		{
			// must be double null terminated
			std::wstring data;
			{
				for (const auto& path : paths)
				{
					data += (FileSystem::FullPath(path)).toWstr();
					data.push_back(L'\0');
				}

				data.push_back(L'\0');
			}

			const size_t data_size_bytes = (sizeof(wchar_t) * data.size());

			FORMATETC formatetc;
			formatetc.cfFormat = CF_HDROP;
			formatetc.ptd = nullptr;
			formatetc.dwAspect = DVASPECT_CONTENT;
			formatetc.lindex = -1;
			formatetc.tymed = TYMED_HGLOBAL;

			STGMEDIUM medium
			{
				.tymed		= TYMED_HGLOBAL,
				.hGlobal	= ::GlobalAlloc(GMEM_MOVEABLE, sizeof(DROPFILES) + data_size_bytes)
			};
			
			if (void* p = ::GlobalLock(medium.hGlobal))
			{
				((DROPFILES*)p)->pFiles = sizeof(DROPFILES);
				((DROPFILES*)p)->fWide = true;
				std::memcpy((char*)p + sizeof(DROPFILES), data.data(), data_size_bytes);
				::GlobalUnlock(medium.hGlobal);
			}

			*lpDataObejct = new DataObject(&formatetc, &medium, 1);
			*lpDropSource = new DropSource();
		}
	}

	CDragDrop::CDragDrop() {}

	CDragDrop::~CDragDrop()
	{
		LOG_SCOPED_TRACE(U"CDragDrop::~CDragDrop()");

		::RevokeDragDrop(m_hWnd);
	}

	void CDragDrop::init()
	{
		LOG_SCOPED_TRACE(U"CDragDrop::init()");

		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());

		detail::DropTarget* p = new detail::DropTarget(m_hWnd);

		LOG_TRACE(U"QueryInterface(IID_IDropTarget)");

		if (FAILED(p->QueryInterface(IID_IDropTarget, (void**)&m_pDropTarget)))
		{
			p->Release();
			throw EngineError{ U"DropTarget::QueryInterface() failed" };
		}

		LOG_TRACE(U"RegisterDragDrop()");

		if (FAILED(::RegisterDragDrop(m_hWnd, m_pDropTarget)))
		{
			LOG_WARNING(U"RegisterDragDrop() failed");
		}
		else
		{
			m_initialized = true;
		}

		m_pDropTarget->Release();
	}

	void CDragDrop::update()
	{
		if (not m_initialized)
		{
			return;
		}

		const auto status = m_pDropTarget->getStatus();

		const Array<DroppedFilePath>& filePaths = std::get<Array<DroppedFilePath>>(status);

		m_droppedFilePaths.insert(m_droppedFilePaths.end(), filePaths.begin(), filePaths.end());

		const Array<DroppedText>& texts = std::get<Array<DroppedText>>(status);

		m_droppedTexts.insert(m_droppedTexts.end(), texts.begin(), texts.end());

		m_dragOver = std::get<bool>(status);

		m_itemType = std::get<DragItemType>(status);

		m_dragOverPos = std::get<Point>(status);
	}

	void CDragDrop::acceptFilePaths(const bool accept)
	{
		if (not m_initialized)
		{
			return;
		}

		m_pDropTarget->acceptFilePaths(accept);
	}

	void CDragDrop::acceptText(const bool accept)
	{
		if (not m_initialized)
		{
			return;
		}

		m_pDropTarget->acceptText(accept);
	}

	Optional<DragStatus> CDragDrop::dragOver() const
	{
		if (not m_dragOver)
		{
			return none;
		}

		return DragStatus{ m_itemType, Scene::ClientToScene(m_dragOverPos).asPoint() };
	}

	bool CDragDrop::hasNewFilePaths() const
	{
		return !m_droppedFilePaths.isEmpty();
	}

	bool CDragDrop::hasNewText() const
	{
		return !m_droppedTexts.isEmpty();
	}

	void CDragDrop::clear()
	{
		m_droppedFilePaths.clear();

		m_droppedTexts.clear();
	}

	Array<DroppedFilePath> CDragDrop::getDroppedFilePaths()
	{
		Array<DroppedFilePath> dropped(std::move(m_droppedFilePaths));

		for (auto& item : dropped)
		{
			item.pos = Scene::ClientToScene(item.pos).asPoint();
		}

		return dropped;
	}

	Array<DroppedText> CDragDrop::getDroppedText()
	{
		Array<DroppedText> dropped(std::move(m_droppedTexts));

		for (auto& item : dropped)
		{
			item.pos = Scene::ClientToScene(item.pos).asPoint();
		}

		return dropped;
	}

	void CDragDrop::makeDragDrop(const Array<FilePath>& paths)
	{
		if (not m_initialized)
		{
			return;
		}

		std::lock_guard lock{ m_mutex };

		m_newDragPaths = paths;
	}

	void CDragDrop::process()
	{
		if (not m_initialized)
		{
			return;
		}

		Array<FilePath> paths;

		{
			std::lock_guard lock{ m_mutex };

			if (m_newDragPaths)
			{
				paths.swap(m_newDragPaths);
			}
		}

		if (not paths)
		{
			return;
		}

		{
			ComPtr<IDataObject> dataObject;
			ComPtr<IDropSource> dropSource;

			detail::BeginDrop(&dataObject, &dropSource, paths);

			DWORD dropEffect;
			HRESULT hr = ::DoDragDrop(dataObject.Get(), dropSource.Get(), DROPEFFECT_MOVE | DROPEFFECT_COPY, &dropEffect);

			if (hr == DRAGDROP_S_DROP)
			{
				//if ((dropEffect & DROPEFFECT_COPY) == DROPEFFECT_COPY)
				//{
				//	Print << U"Copy";
				//}

				//if ((dropEffect & DROPEFFECT_MOVE) == DROPEFFECT_MOVE)
				//{
				//	Print << U"Move";
				//}

				//if ((dropEffect & DROPEFFECT_LINK) == DROPEFFECT_LINK)
				//{
				//	Print << U"Link";
				//}
			}
			else if (hr == DRAGDROP_S_CANCEL)
			{
				//LOG_ERROR(U"A2");
			}
			else
			{
				//LOG_ERROR(U"E1");
			}
		}
	}
}
