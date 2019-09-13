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
# include <Shader/IShader.hpp>
# include <AssetHandleManager/AssetHandleManager.hpp>
# include "VertexShader_GL.hpp"
# include "PixelShader_GL.hpp"

namespace s3d
{
	class CShader_GL : public ISiv3DShader
	{
	private:

		AssetHandleManager<VertexShaderID, VertexShader_GL> m_vertexShaders{ U"VertexShader" };
		
		AssetHandleManager<PixelShaderID, PixelShader_GL> m_pixelShaders{ U"PixelShader" };
		
		// [エンジン PS]
		Array<PixelShader> m_enginePSs;
		
	public:

		CShader_GL();

		~CShader_GL() override;

		bool init();

		VertexShaderID createVS(ByteArray&& binary, const Array<ConstantBufferBinding>& bindings) override;
		VertexShaderID createVSFromFile(const FilePath& path, const Array<ConstantBufferBinding>& bindings) override;
		VertexShaderID createVSFromSource(const String&, const Array<ConstantBufferBinding>&);

		PixelShaderID createPS(ByteArray&& binary, const Array<ConstantBufferBinding>& bindings) override;
		PixelShaderID createPSFromFile(const FilePath& path, const Array<ConstantBufferBinding>& bindings) override;
		PixelShaderID createPSFromSource(const String& source, const Array<ConstantBufferBinding>& bindings);

		void release(VertexShaderID handleID) override;
		void release(PixelShaderID handleID) override;

		ByteArrayView getBinaryView(VertexShaderID handleID) override;
		ByteArrayView getBinaryView(PixelShaderID handleID) override;

		void setVS(VertexShaderID handleID) override {}
		void setPS(PixelShaderID handleID) override {}
		
		// エンジン PS を取得
		const PixelShader& getEnginePS(const EnginePS ps) const override;
		
		GLuint getVSProgram(VertexShaderID handleID);
		GLuint getPSProgram(PixelShaderID handleID);
		void setPSSamplerUniform(PixelShaderID handleID);
	};
}
