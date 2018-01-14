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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <d3dcompiler.h>
# include "../IShader.hpp"
# include "VertexShader_D3D11.hpp"
# include "PixelShader_D3D11.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"

namespace s3d
{
	class CShader_D3D11 : public ISiv3DShader
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		HINSTANCE m_d3dcompiler = nullptr;

	# if !defined(__MINGW32__)

		decltype(D3DCompile2)* p_D3DCompile2 = nullptr;

	# endif

		AssetHandleManager<VertexShaderID, VertexShader_D3D11> m_vertexShaders{ U"VertexShader" };

		AssetHandleManager<PixelShaderID, PixelShader_D3D11> m_pixelShaders{ U"PixelShader" };

		VertexShaderID m_currentVS = VertexShaderID::InvalidValue();

		PixelShaderID m_currentPS = PixelShaderID::InvalidValue();

		Array<VertexShader> m_standardVSs;

		Array<PixelShader> m_standardPSs;

		bool compileHLSL(IReader& reader, ByteArray& to, const char* filePath, const char* entryPoint, const char* target);
			
		bool compileHLSLToFile(const FilePath& hlsl, const FilePath& to, const char* entryPoint, const char* target);

	public:

		CShader_D3D11();

		~CShader_D3D11() override;

		bool init(ID3D11Device* device, ID3D11DeviceContext* context);

		VertexShaderID createVS(ByteArray&& binary) override;

		VertexShaderID createVSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) override;
		
		VertexShaderID createVSFromSource(const String&, const Array<BindingPoint>&) override
		{
			// [Siv3D ToDo];
			return VertexShaderID::NullAsset();
		}

		PixelShaderID createPS(ByteArray&& binary) override;

		PixelShaderID createPSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) override;
		
		PixelShaderID createPSFromSource(const String&, const Array<BindingPoint>&) override
		{
			// [Siv3D ToDo];
			return PixelShaderID::NullAsset();
		}

		void releaseVS(VertexShaderID handleID) override;

		void releasePS(PixelShaderID handleID) override;

		ByteArrayView getBinaryViewVS(VertexShaderID handleID) override;

		ByteArrayView getBinaryViewPS(PixelShaderID handleID) override;

		const VertexShader& getStandardVS(size_t index) const override;

		const PixelShader& getStandardPS(size_t index) const override;

		void setVS(VertexShaderID handleID) override;

		void setPS(PixelShaderID handleID) override;
	};
}

# endif
