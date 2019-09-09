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
# include <memory>
# include "Fwd.hpp"
# include "AssetHandle.hpp"
# include "String.hpp"
# include "NamedParameter.hpp"
# include "Array.hpp"
# include "ShaderCommon.hpp"

namespace s3d
{
	class VertexShader
	{
	protected:

		class Tag {};

		using VertexShaderHandle = AssetHandle<Tag>;

		friend VertexShaderHandle::AssetHandle();
	
		friend VertexShaderHandle::AssetHandle(const IDWrapperType id) noexcept;
		
		friend VertexShaderHandle::~AssetHandle();

		std::shared_ptr<VertexShaderHandle> m_handle;

	public:

		using IDType = VertexShaderHandle::IDWrapperType;

		VertexShader();

		VertexShader(const FilePath& path, const Array<ConstantBufferBinding>& bindings);
		
		//VertexShader(Arg::source_<String> source, const Array<ConstantBufferBinding>& bindings);

		virtual ~VertexShader();

		void release();

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const;

		[[nodiscard]] IDType id() const;

		[[nodiscard]] bool operator ==(const VertexShader& shader) const;

		[[nodiscard]] bool operator !=(const VertexShader& shader) const;

		[[nodiscard]] ByteArrayView getBinaryView() const;
	};

	using VertexShaderID = VertexShader::IDType;
}
