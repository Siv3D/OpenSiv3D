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

# pragma once
# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <Siv3D/ConstantBuffer.hpp>

namespace s3d
{
	namespace detail
	{
		class ConstantBufferBase::ConstantBufferDetail
		{
		private:

			mutable ID3D11DeviceContext* m_context = nullptr;

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
