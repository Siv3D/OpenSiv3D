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
		
	public:

		CShader_GL();

		~CShader_GL() override;

		bool init();

		VertexShaderID createVS(ByteArray&& binary) override;
		VertexShaderID createVSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) override;
		//VertexShaderID createVSFromSource(const String&, const Array<BindingPoint>&) override

		PixelShaderID createPS(ByteArray&& binary) override;
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
