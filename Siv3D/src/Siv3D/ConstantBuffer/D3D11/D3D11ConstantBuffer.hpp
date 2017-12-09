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

# include <Siv3D/Windows.hpp>
# include <wrl.h>
# include <d3d11.h>
# include <Siv3D/ConstantBuffer.hpp>

using namespace Microsoft::WRL;

namespace s3d
{
	namespace detail
	{
		class ConstantBufferBase::ConstantBufferDetail
		{
		private:

			size_t m_bufferSize = 0;

			mutable ComPtr<ID3D11Buffer> m_buffer;

			bool init() const;

		public:

			explicit ConstantBufferDetail(size_t size);

			bool update(const void* data, size_t size);

			ID3D11Buffer* const* getBufferPtr() const;
		};
	}
}

# endif
