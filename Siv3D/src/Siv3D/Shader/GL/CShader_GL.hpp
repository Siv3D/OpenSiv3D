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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "../IShader.hpp"
# include <Siv3D/Array.hpp>
# include <Siv3D/ByteArrayView.hpp>
# include "VertexShader_GL.hpp"
# include "PixelShader_GL.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"

namespace s3d
{
	class CShader_GL : public ISiv3DShader
	{
	private:

		Array<VertexShader> m_standardVSs;

		Array<PixelShader> m_standardPSs;
		
		AssetHandleManager<VertexShaderID, VertexShader_GL> m_vertexShaders{ U"VertexShader" };
		
		AssetHandleManager<PixelShaderID, PixelShader_GL> m_pixelShaders{ U"PixelShader" };

	public:

		CShader_GL();

		~CShader_GL() override;

		bool init();

		VertexShaderID createVS(ByteArray&&) override { return VertexShaderID::NullAsset(); }

		VertexShaderID createVSFromFile(const FilePath& path, const Array<BindingPoint>&) override;
		
		VertexShaderID createVSFromSource(const String& source, const Array<BindingPoint>& bindingPoints) override;

		PixelShaderID createPS(ByteArray&&) override { return PixelShaderID::NullAsset(); }

		PixelShaderID createPSFromFile(const FilePath& path, const Array<BindingPoint>&) override;
		
		PixelShaderID createPSFromSource(const String& source, const Array<BindingPoint>& bindingPoints) override;

		void releaseVS(VertexShaderID handleID) override;

		void releasePS(PixelShaderID handleID) override;
		
		ByteArrayView getBinaryViewVS(VertexShaderID) override
		{
			return ByteArrayView();
		}

		ByteArrayView getBinaryViewPS(PixelShaderID) override
		{
			return ByteArrayView();
		}

		const VertexShader& getStandardVS(size_t index) const override
		{
			return m_standardVSs[index];
		}

		const PixelShader& getStandardPS(size_t index) const override
		{
			return m_standardPSs[index];
		}
		
		void setVS(VertexShaderID) override {}

		void setPS(PixelShaderID) override {}
		
		GLuint getVSProgram(VertexShaderID handleID);
		
		GLuint getPSProgram(PixelShaderID handleID);
		
		void setPSSamplerUniform(PixelShaderID handleID);
	};
}

# endif
