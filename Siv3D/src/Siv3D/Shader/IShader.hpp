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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>

namespace s3d
{
	enum class EnginePS
	{
		Copy,
		GaussianBlur_9,
	};

	class ISiv3DShader
	{
	public:

		static ISiv3DShader* Create();

		virtual ~ISiv3DShader() = default;

		virtual VertexShaderID createVS(ByteArray&& binary, const Array<ConstantBufferBinding>& bindings) = 0;
		virtual VertexShaderID createVSFromFile(const FilePath& path, const Array<ConstantBufferBinding>& bindings) = 0;
		//virtual VertexShaderID createVSFromSource(const String& source, const Array<ConstantBufferBinding>& bindings) = 0;

		virtual PixelShaderID createPS(ByteArray&& binary, const Array<ConstantBufferBinding>& bindings) = 0;
		virtual PixelShaderID createPSFromFile(const FilePath& path, const Array<ConstantBufferBinding>& bindings) = 0;
		//virtual PixelShaderID createPSFromSource(const String& source, const Array<ConstantBufferBinding>& bindings) = 0;

		virtual void release(VertexShaderID handleID) = 0;
		virtual void release(PixelShaderID handleID) = 0;

		virtual ByteArrayView getBinaryView(VertexShaderID handleID) = 0;
		virtual ByteArrayView getBinaryView(PixelShaderID handleID) = 0;

		virtual void setVS(VertexShaderID handleID) = 0;
		virtual void setPS(PixelShaderID handleID) = 0;

		virtual const PixelShader& getEnginePS(EnginePS ps) const = 0;
	};
}
