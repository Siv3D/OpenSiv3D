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
# include <Siv3D/ConstantBuffer/IConstantBufferDetail.hpp>

namespace s3d
{
	class ConstantBufferDetail_Metal final : public IConstantBufferDetail
	{
	
	public:

		explicit ConstantBufferDetail_Metal(size_t size);

		bool update(const void* data, size_t size) override;
	};
}
