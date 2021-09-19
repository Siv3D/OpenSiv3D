//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/ConstantBuffer/IConstantBufferDetail.hpp>

namespace s3d
{
	class ConstantBufferDetail_GLES3 final : public IConstantBufferDetail
	{
	private:

		size_t m_bufferSize = 0;

		mutable GLuint m_uniformBuffer = 0;

	public:

		explicit ConstantBufferDetail_GLES3(size_t size);

		~ConstantBufferDetail_GLES3();

		bool update(const void* data, size_t size) override;

		GLuint getHandle() const;

		void initBuffer() const;
	};
}
