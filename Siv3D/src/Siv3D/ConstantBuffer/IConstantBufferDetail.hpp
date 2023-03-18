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

namespace s3d
{
	class IConstantBufferDetail
	{
	public:

		static IConstantBufferDetail* Create(size_t size);

		virtual ~IConstantBufferDetail() = default;

	public:

		virtual bool update(const void* data, size_t size) = 0;
	};
}
