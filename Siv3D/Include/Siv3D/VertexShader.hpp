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

		using IDType = VertexShaderHandle::IDType;

		static constexpr IDType NullHandleID = VertexShaderHandle::NullID;

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
}
