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

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "AssetHandle.hpp"

namespace s3d
{
	class VertexShader
	{
	protected:

		class Handle {};

		using VertexShaderHandle = AssetHandle<Handle>;

		friend VertexShaderHandle::~AssetHandle();

		std::shared_ptr<VertexShaderHandle> m_handle;

	public:

		using IDType = VertexShaderHandle::IDType;

		VertexShader();

		explicit VertexShader(const FilePath& path);

		virtual ~VertexShader();

		void release();

		bool isEmpty() const;

		explicit operator bool() const
		{
			return !isEmpty();
		}

		IDType id() const;

		bool operator ==(const VertexShader& shader) const;

		bool operator !=(const VertexShader& shader) const;

		ByteArrayView getBinaryView() const;
	};
}
