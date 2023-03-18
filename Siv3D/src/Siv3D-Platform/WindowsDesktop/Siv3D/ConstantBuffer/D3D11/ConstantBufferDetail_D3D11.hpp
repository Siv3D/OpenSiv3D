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
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include <Siv3D/ConstantBuffer/IConstantBufferDetail.hpp>

namespace s3d
{
	class ConstantBufferDetail_D3D11 final : public IConstantBufferDetail
	{
	private:

		mutable ID3D11DeviceContext* m_context = nullptr;

		size_t m_bufferSize = 0;

		mutable ComPtr<ID3D11Buffer> m_buffer;

		bool init() const;

	public:

		explicit ConstantBufferDetail_D3D11(size_t size);

		bool update(const void* data, size_t size) override;

		ID3D11Buffer* const* getBufferPtr() const;
	};
}
