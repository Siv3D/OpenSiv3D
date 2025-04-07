//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ConstantBuffer.hpp>
# include "IConstantBufferDetail.hpp"

namespace s3d
{
	ConstantBufferBase::ConstantBufferBase(const size_t size)
		: pImpl{ IConstantBufferDetail::Create(size) }
	{

	}

	bool ConstantBufferBase::_internal_update(const void* const data, const size_t size)
	{
		return pImpl->update(data, size);
	}

	const IConstantBufferDetail* ConstantBufferBase::_detail() const
	{
		return pImpl.get();
	}
}
