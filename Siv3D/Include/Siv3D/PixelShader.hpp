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
	class PixelShader
	{
	protected:

		class Handle {};

		using PixelShaderHandle = AssetHandle<Handle>;

		friend PixelShaderHandle::~AssetHandle();

		std::shared_ptr<PixelShaderHandle> m_handle;

	public:

		using IDType = PixelShaderHandle::IDType;

		static constexpr IDType NullHandleID = PixelShaderHandle::NullID;

		PixelShader();

		explicit PixelShader(const FilePath& path, const Array<BindingPoint>& bindingPoints = {});
		
		explicit PixelShader(Arg::source_<String> source, const Array<BindingPoint>& bindingPoints = {});

		virtual ~PixelShader();

		void release();

		bool isEmpty() const;

		explicit operator bool() const
		{
			return !isEmpty();
		}

		IDType id() const;

		bool operator ==(const PixelShader& shader) const;

		bool operator !=(const PixelShader& shader) const;

		ByteArrayView getBinaryView() const;
	};
}
