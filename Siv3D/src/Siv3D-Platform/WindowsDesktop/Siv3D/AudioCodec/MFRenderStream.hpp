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

# pragma once
# include <list>
# include <Siv3D/Windows/Windows.hpp>
# include <Shlwapi.h>
# include <mfapi.h>
# include <mfidl.h>
# include <Mfreadwrite.h>
# include <process.h>
# include <Siv3D/IReader.hpp>

namespace s3d
{
	// 参考
	//	http://d.hatena.ne.jp/shiku_otomiya/20130913/p1
	//	http://d.hatena.ne.jp/shiku_otomiya/20130914/p1
	//	https://github.com/easyfungames/u4.4.4/tree/09e4225291f64f3543bde9e1a049ff92d1825297/Engine/Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf

	/**
	* Implements the state information for asynchronous reads of byte buffer sources.
	*
	* The @see FWmfByteStream class uses this class to store the state for asynchronous
	* read requests that are initiated with @see FWmfByteStream.BeginRead and completed
	* with @see FWmfByteStream.EndRead
	*/
	class FWmfMediaReadState
		: public IUnknown
	{
	public:

		/**
		* Creates and initializes a new instance.
		*
		* @param InReadBuffer The buffer that receives the read data.
		* @param InReadBufferSize The size of the read buffer.
		*/
		FWmfMediaReadState(BYTE* InReadBuffer, ULONG InReadBufferSize)
			: BytesRead(0)
			, ReadBuffer(InReadBuffer)
			, ReadBufferSize(InReadBufferSize)
			, RefCount(1)
		{ }
	public:
		/**
		* Sets the number of bytes read.
		*/
		void AddBytesRead(uint64_t InBytesRead)
		{
			BytesRead += InBytesRead;
		}
		/**
		* Gets a pointer to the buffer being read from.
		*
		* @return The buffer.
		*/
		BYTE* GetReadBuffer() const
		{
			return ReadBuffer;
		}
		/**
		* Gets the size of the buffer being read from.
		*
		* @return The size of the buffer (in bytes).
		*/
		ULONG GetReadBufferSize() const
		{
			return ReadBufferSize;
		}
		/**
		* Gets the actual number of bytes read.
		*
		* @return Bytes read count.
		*/
		uint64_t GetBytesRead() const
		{
			return BytesRead;
		}
	public:
		// IUnknown interface
		STDMETHODIMP QueryInterface(REFIID RefID, void** Object)
		{
			static const QITAB QITab[] =
			{
				QITABENT(FWmfMediaReadState, IUnknown),
				{ 0 }
			};
			return QISearch(this, QITab, RefID, Object);
		}
		STDMETHODIMP_(ULONG) AddRef()
		{
			return InterlockedIncrement(&RefCount);
		}
		STDMETHODIMP_(ULONG) Release()
		{
			int32_t CurrentRefCount = InterlockedDecrement(&RefCount);
			if (CurrentRefCount == 0)
			{
				delete this;
			}
			return CurrentRefCount;
		}
	private:
		// Number of bytes read.
		uint64_t BytesRead;
		// The buffer that receives the read data.
		BYTE* ReadBuffer;
		// The size of the read buffer.
		ULONG ReadBufferSize;
		// Holds a reference counter for this instance.
		long RefCount;
	};

	class MFReaderStream : public IMFAsyncCallback, public IMFByteStream
	{
	private:

		s3d::IReader* m_reader = nullptr;

		long m_refCount = 0;

	public:

		// IMFAsyncCallback interface
		STDMETHODIMP GetParameters(unsigned long*, unsigned long*)
		{
			return E_NOTIMPL;
		}

		STDMETHODIMP Invoke(IMFAsyncResult* AsyncResult)
		{
			// recover read state
			IUnknown* State = NULL;
			HRESULT Result = AsyncResult->GetState(&State);

			if (FAILED(Result))
				return E_FAIL;

			IMFAsyncResult* CallerResult = NULL;
			Result = State->QueryInterface(IID_PPV_ARGS(&CallerResult));

			if (FAILED(Result))
				return E_FAIL;

			IUnknown* Unknown = NULL;
			Result = CallerResult->GetObject(&Unknown);

			if (FAILED(Result))
				return E_FAIL;

			FWmfMediaReadState* ReadState = static_cast<FWmfMediaReadState*>(Unknown);
			// perform the read
			ULONG cbRead;
			Read(ReadState->GetReadBuffer(), static_cast<ULONG>(ReadState->GetReadBufferSize() - ReadState->GetBytesRead()), &cbRead);
			ReadState->AddBytesRead(cbRead);
			// notify caller
			if (CallerResult != NULL)
			{
				CallerResult->SetStatus(Result);
				p_MFInvokeCallback(CallerResult);
			}
			// clean up
			if (CallerResult != NULL)
			{
				CallerResult->Release();
			}
			if (Unknown != NULL)
			{
				Unknown->Release();
			}
			if (State != NULL)
			{
				State->Release();
			}
			return S_OK;
		}


	public:

		inline static decltype(MFCreateAttributes)* p_MFCreateAttributes = nullptr;
		inline static decltype(MFCreateAsyncResult)* p_MFCreateAsyncResult = nullptr;
		inline static decltype(MFInvokeCallback)* p_MFInvokeCallback = nullptr;

		MFReaderStream(s3d::IReader* reader)
			: m_hAsyncThread(nullptr)
			, m_hThreadEvent(nullptr)
			, m_lpAttributes(nullptr)
		{
			::InitializeCriticalSection(&m_vCSStream);

			::InitializeCriticalSection(&m_vCSQueue);

			if (FAILED(p_MFCreateAttributes(&m_lpAttributes, 0)))
			{
				return;
			}

			AddRef();

			m_reader = reader;
		}

		virtual ~MFReaderStream()
		{
			//LOG_TEST(L"~MFReaderStream");

			Close();

			::DeleteCriticalSection(&m_vCSQueue);

			::DeleteCriticalSection(&m_vCSStream);

			//LOG_TEST(L"~MFReaderStream: done");
		}

		//IUnknownの機能を実装する
		STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
		{
			return NonDelegatingQueryInterface(riid, ppv);
		}

		STDMETHODIMP_(ULONG) AddRef()
		{
			//LOG_TEST(L"AddRef to ", m_refCount + 1);

			return InterlockedIncrement(&m_refCount);
		}

		STDMETHODIMP_(ULONG) Release()
		{
			//LOG_TEST(L"Release to ", m_refCount - 1);

			long CurrentRefCount = InterlockedDecrement(&m_refCount);

			if (CurrentRefCount == 0)
			{
				delete this;
			}

			return CurrentRefCount;
		}

		STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv)
		{
			static const QITAB QITab[] =
			{
				QITABENT(MFReaderStream, IMFByteStream),
				QITABENT(MFReaderStream, IMFAsyncCallback),
				{ 0 }
			};

			return QISearch(this, QITab, riid, ppv);
		}

		//IMFByteStreamの実装
		STDMETHODIMP GetCapabilities(DWORD *pdwCapabilities)
		{
			if (!pdwCapabilities)
			{
				return E_POINTER;
			}

			if (!IsValidStream()) return E_HANDLE;

			*pdwCapabilities = MFBYTESTREAM_IS_READABLE | MFBYTESTREAM_IS_SEEKABLE;

			return S_OK;
		}

		STDMETHODIMP GetLength(QWORD *pqwLength)
		{
			if (!pqwLength)
			{
				return E_POINTER;
			}

			*pqwLength = m_reader->size();

			return S_OK;
		}

		STDMETHODIMP SetLength(QWORD)
		{
			return E_NOTIMPL;
		}

		STDMETHODIMP GetCurrentPosition(QWORD *pqwPosition)
		{
			if (!pqwPosition)
			{
				return E_POINTER;
			}

			*pqwPosition = m_ullStreamPos;

			return S_OK;
		}

		STDMETHODIMP SetCurrentPosition(QWORD qwPosition)
		{
			if (qwPosition > static_cast<QWORD>(m_reader->size()))
			{
				qwPosition = m_reader->size();
			}

			return Seek(msoBegin, qwPosition, 0, NULL);
		}

		STDMETHODIMP IsEndOfStream(BOOL *pfEndOfStream)
		{
			if (!pfEndOfStream)
			{
				return E_POINTER;
			}

			*pfEndOfStream = m_ullStreamPos >= static_cast<uint64_t>(m_reader->size()) ? TRUE : FALSE;

			return S_OK;
		}

		STDMETHODIMP Read(BYTE *pb, ULONG cb, ULONG *pcbRead)
		{
			if (!pb || !pcbRead)
			{
				return E_POINTER;
			}

			return InnerRead(pb, cb, pcbRead, m_ullStreamPos);
		}

		STDMETHODIMP BeginRead(BYTE *pb, ULONG cb, IMFAsyncCallback *pCallback, IUnknown *punkState)
		{
			ASYNCITEM item; HRESULT hr;

			if (!pb || !pCallback)
			{
				return E_POINTER;
			}

			hr = p_MFCreateAsyncResult(NULL, pCallback, punkState, &item.lpResult);
			if (FAILED(hr)) return hr;

			item.pbBuffer = pb; item.cbSize = cb; item.cbRead = 0; item.nReadPos = m_ullStreamPos;

			CLockQueue lock(this);
			m_dequeWorkItem.push_back(item);
			::SetEvent(m_hThreadEvent);

			return S_OK;
		}


		STDMETHODIMP EndRead(IMFAsyncResult *pResult, ULONG *pcbRead)
		{
			if (!pResult || !pcbRead)
			{
				return E_POINTER;
			}

			dequeAsyncItem::iterator it, itend; HRESULT hr;

			CLockQueue lock(this);
			for (it = m_dequeDoneItem.begin(), itend = m_dequeDoneItem.end(), hr = E_FAIL; it != itend; ++it) {
				if (it->lpResult == pResult) {
					*pcbRead = it->cbRead;
					m_dequeDoneItem.erase(it);
					pResult->Release(); hr = S_OK;
					break;
				}
			}
			return hr;
		}

		STDMETHODIMP Write(const BYTE*, ULONG, ULONG*)
		{
			return E_NOTIMPL;
		}

		STDMETHODIMP BeginWrite(const BYTE*, ULONG, IMFAsyncCallback*, IUnknown*)
		{
			return E_NOTIMPL;
		}

		STDMETHODIMP EndWrite(IMFAsyncResult*, ULONG*)
		{
			return E_NOTIMPL;
		}

		STDMETHODIMP Seek(MFBYTESTREAM_SEEK_ORIGIN SeekOrigin, LONGLONG llSeekOffset, DWORD dwSeekFlags, QWORD *pqwCurrentPosition)
		{
			dwSeekFlags;

			int64_t llNewPos;

			CLockStream lock(this);
			switch (SeekOrigin) {
			case msoBegin: llNewPos = llSeekOffset; break;
			case msoCurrent: llNewPos = (int64_t)m_ullStreamPos + llSeekOffset; break;
			default: return E_INVALIDARG;
			}

			if (llNewPos < 0)
			{
				llNewPos = 0;
			}
			else if (llNewPos > m_reader->size())
			{
				llNewPos = m_reader->size();
			}

			m_ullStreamPos = llNewPos;

			if (pqwCurrentPosition != NULL) { *pqwCurrentPosition = m_ullStreamPos; }
			return S_OK;
		}

		STDMETHODIMP Flush()
		{
			return E_NOTIMPL;
		}

		STDMETHODIMP Close()
		{
			dequeAsyncItem::iterator it, itend;
			{
				CLockQueue lock(this);
				for (it = m_dequeWorkItem.begin(), itend = m_dequeWorkItem.end(); it != itend; ++it) { it->lpResult->Release(); }
				for (it = m_dequeDoneItem.begin(), itend = m_dequeDoneItem.end(); it != itend; ++it) { it->lpResult->Release(); }
				m_dequeWorkItem.clear(); m_dequeDoneItem.clear();
			}

			if (IsValidThread()) {
				::SetEvent(m_hThreadEvent);
				::WaitForSingleObject(m_hAsyncThread, INFINITE);
				::CloseHandle(m_hThreadEvent);
				::CloseHandle(m_hAsyncThread);
				m_hThreadEvent = NULL; m_hAsyncThread = NULL;
			}
			if (IsValidStream())
			{
				CLockStream lock(this);
				m_ullStreamPos = 0;
			}

			return S_OK;
		}

		HRESULT Open(void)
		{
			unsigned int threadid;

			if (!IsValidStream()) return E_ABORT;

			if (!m_reader->isOpen()) return E_FAIL;

			m_hThreadEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
			if (m_hThreadEvent == NULL) return E_FAIL;

			m_hAsyncThread = (HANDLE)_beginthreadex(NULL, 0, &MFReaderStream::AsyncThread, this, 0, &threadid);
			if (m_hAsyncThread == NULL) { ::CloseHandle(m_hThreadEvent); m_hThreadEvent = NULL; return E_FAIL; }

			return S_OK;
		}


	protected:
		//内部ロックオブジェクト
		class CLockStream {
		public:
			CLockStream(MFReaderStream *obj) : m_obj(obj) { ::EnterCriticalSection(&obj->m_vCSStream); }
			~CLockStream() { ::LeaveCriticalSection(&m_obj->m_vCSStream); }
		private:
			MFReaderStream *m_obj;
		};

		class CLockQueue {
		public:
			CLockQueue(MFReaderStream *obj) : m_obj(obj) { ::EnterCriticalSection(&obj->m_vCSQueue); }
			~CLockQueue() { ::LeaveCriticalSection(&m_obj->m_vCSQueue); }
		private:
			MFReaderStream *m_obj;
		};

		//非同期処理アイテムの定義
		typedef struct _AsyncItem {
			IMFAsyncResult *lpResult;
			BYTE *pbBuffer;
			ULONG cbSize, cbRead;
			uint64_t nReadPos;
		} ASYNCITEM;

		using dequeAsyncItem = std::list<ASYNCITEM>;

		HRESULT InnerRead(BYTE *pb, ULONG cb, ULONG *pcbRead, uint64_t nReadPos)
		{
			if (!IsValidStream()) return E_HANDLE;

			CLockStream lock(this);

			m_reader->setPos(nReadPos);

			//if (!::SetFilePointerEx(m_hFileStream, *((LARGE_INTEGER *) &nReadPos), NULL, FILE_BEGIN)){ return E_FAIL; }

			*pcbRead = static_cast<ULONG>(m_reader->read(pb, cb));

			//if (!::ReadFile(m_hFileStream, pb, cb, pcbRead, NULL)) return E_FAIL;

			m_ullStreamPos = nReadPos + *pcbRead;

			return S_OK;
		}

		static unsigned int __stdcall AsyncThread(void *lpContext)
		{
			ASYNCITEM item; MFReaderStream *lpThis; HRESULT hr; DWORD dw;

			lpThis = (MFReaderStream *)lpContext;
			for (;;) {
				dw = WaitForSingleObject(lpThis->m_hThreadEvent, INFINITE);
				if (dw != WAIT_OBJECT_0 || lpThis->m_dequeWorkItem.empty()) break;

				while (!lpThis->m_dequeWorkItem.empty()) {
					{
						CLockQueue lock(lpThis);
						if (lpThis->m_dequeWorkItem.empty()) break;
						item = lpThis->m_dequeWorkItem.front();
						lpThis->m_dequeWorkItem.pop_front();
					}

					hr = lpThis->InnerRead(item.pbBuffer, item.cbSize, &item.cbRead, item.nReadPos);
					if (FAILED(hr)) { item.lpResult->Release(); break; }

					{
						CLockQueue lock(lpThis);
						lpThis->m_dequeDoneItem.push_back(item);
					}

					hr = p_MFInvokeCallback(item.lpResult);
				}
			}

			return 0;
		}

		inline bool IsValidStream(void) const { return m_reader->isOpen(); } //ストリームが有効かどうか
		inline bool IsValidThread(void) const { return m_hAsyncThread != NULL; } //スレッドが有効かどうか

	private:

		uint64_t m_ullStreamPos = 0; //ストリーム位置
		CRITICAL_SECTION m_vCSStream; //ストリーム同期ハンドル

		HANDLE m_hAsyncThread = nullptr; //非同期処理スレッド
		HANDLE m_hThreadEvent = nullptr; //スレッドイベント
		CRITICAL_SECTION m_vCSQueue; //キューアイテム同期ハンドル
		dequeAsyncItem m_dequeWorkItem; //未処理アイテムキュー
		dequeAsyncItem m_dequeDoneItem; //処理済みアイテムキュー
		IMFAttributes *m_lpAttributes = nullptr; //属性値管理
	};
}
