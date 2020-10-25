//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/Shader.hpp>
# include <Siv3D/ShaderStatge.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include "VertexShader/MetalVertexShader.hpp"
# include "PixelShader/MetalPixelShader.hpp"
# import <Metal/Metal.h>

namespace s3d
{
	class CRenderer_Metal;

	class CShader_Metal final : public ISiv3DShader
	{
	private:

		CRenderer_Metal* pRenderer = nullptr;
		id<MTLDevice> m_device = nil;
		
		id<MTLLibrary> m_defaultLibrary = nil;
		
		// VS の管理
		AssetHandleManager<VertexShader::IDType, MetalVertexShader> m_vertexShaders{ U"VertexShader" };

		// PS の管理
		AssetHandleManager<PixelShader::IDType, MetalPixelShader> m_pixelShaders{ U"PixelShader" };

	public:

		CShader_Metal();

		~CShader_Metal() override;

		void init() override;

		VertexShader::IDType createVSFromFile(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;
		
		VertexShader::IDType createVSFromSource(StringView source, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;


		PixelShader::IDType createPSFromFile(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;
	
		PixelShader::IDType createPSFromSource(StringView source, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;

		// 指定した VS を管理から除外
		void releaseVS(VertexShader::IDType handleID) override;

		// 指定した PS を管理から除外
		void releasePS(PixelShader::IDType handleID) override;
	
		// 指定した VS を context にセット
		void setVS(VertexShader::IDType handleID) override {}

		// 指定した PS を context にセット
		void setPS(PixelShader::IDType handleID) override {}
	
		const Blob& getBinaryVS(VertexShader::IDType handleID) override;

		const Blob& getBinaryPS(PixelShader::IDType handleID) override;

		void setConstantBufferVS(uint32 slot, const ConstantBufferBase& cb) override {}

		void setConstantBufferPS(uint32 slot, const ConstantBufferBase& cb) override {}
		
		
		id<MTLFunction> getFunctionVS(VertexShader::IDType handleID);
		
		id<MTLFunction> getFunctionPS(PixelShader::IDType handleID);
	};
}
