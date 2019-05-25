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
	class PixelShader
	{
	protected:

		class Tag {};

		using PixelShaderHandle = AssetHandle<Tag>;
		
		friend PixelShaderHandle::AssetHandle();
		
		friend PixelShaderHandle::AssetHandle(const IDWrapperType id) noexcept;

		friend PixelShaderHandle::~AssetHandle();

		std::shared_ptr<PixelShaderHandle> m_handle;

	public:

		using IDType = PixelShaderHandle::IDWrapperType;

		PixelShader();

		explicit PixelShader(const FilePath& path, const Array<BindingPoint>& bindingPoints = {});
		
		//explicit PixelShader(Arg::source_<String> source, const Array<BindingPoint>& bindingPoints = {});

		virtual ~PixelShader();

		void release();

		bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const;

		[[nodiscard]] IDType id() const;

		[[nodiscard]] bool operator ==(const PixelShader& shader) const;

		[[nodiscard]] bool operator !=(const PixelShader& shader) const;

		[[nodiscard]] ByteArrayView getBinaryView() const;
	};

	using PixelShaderID = PixelShader::IDType;
}
