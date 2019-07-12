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
# include <Siv3D/Windows.hpp>
# include <Shader/IShader.hpp>
# include <AssetHandleManager/AssetHandleManager.hpp>
# include <d3dcompiler.h>
# include "VertexShader_D3D11.hpp"
# include "PixelShader_D3D11.hpp"

namespace s3d
{
	class CShader_D3D11 : public ISiv3DShader
	{
	private:

		ID3D11Device* m_device = nullptr;
		ID3D11DeviceContext* m_context = nullptr;

		HMODULE m_d3dcompiler = nullptr;
		decltype(D3DCompile2)* p_D3DCompile2 = nullptr;

		AssetHandleManager<VertexShaderID, VertexShader_D3D11> m_vertexShaders{ U"VertexShader" };
		AssetHandleManager<PixelShaderID, PixelShader_D3D11> m_pixelShaders{ U"PixelShader" };

		void compileHLSL(IReader& reader, ByteArray& to, const char* filePath, const char* entryPoint, const char* target);

		void compileHLSLToFile(const FilePath& hlsl, const FilePath& to, const char* entryPoint, const char* target);

	public:

		CShader_D3D11();

		~CShader_D3D11() override;

		void init(ID3D11Device* device, ID3D11DeviceContext* context);

		VertexShaderID createVS(ByteArray&& binary, const Array<BindingPoint>& bindingPoints) override;
		VertexShaderID createVSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) override;
		//VertexShaderID createVSFromSource(const String&, const Array<BindingPoint>&) override

		PixelShaderID createPS(ByteArray&& binary, const Array<BindingPoint>& bindingPoints) override;
		PixelShaderID createPSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) override;
		//PixelShaderID createPSFromSource(const String& source, const Array<BindingPoint>& bindingPoints) override;

		void release(VertexShaderID handleID) override;
		void release(PixelShaderID handleID) override;

		ByteArrayView getBinaryView(VertexShaderID handleID) override;
		ByteArrayView getBinaryView(PixelShaderID handleID) override;

		void setVS(VertexShaderID handleID) override;
		void setPS(PixelShaderID handleID) override;
	};
}
