//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "AssetHandle.hpp"
# include "String.hpp"
# include "NamedParameter.hpp"
# include "Array.hpp"
# include "Shader.hpp"

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

		using IDType = VertexShaderHandle::IDWrapperType;

		VertexShader();

		explicit VertexShader(const FilePath& path, const Array<BindingPoint>& bindingPoints = {});
		
		explicit VertexShader(Arg::source_<String> source, const Array<BindingPoint>& bindingPoints = {});

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

	using VertexShaderID = VertexShader::IDType;
}
