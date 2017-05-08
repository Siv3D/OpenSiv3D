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
		
		AssetHandleManager<VertexShader::IDType, std::shared_ptr<VertexShader_GL>> m_vertexShaders{ S3DSTR("VertexShader") };
		
		AssetHandleManager<PixelShader::IDType, std::shared_ptr<PixelShader_GL>> m_pixelShaders{ S3DSTR("PixelShader") };

	public:

		CShader_GL();

		~CShader_GL() override;

		bool init();

		VertexShader::IDType createVS(ByteArray&&) override { return 0; }

		VertexShader::IDType createVSFromFile(const FilePath&, const Array<BindingPoint>&) override { return 0; }
		
		VertexShader::IDType createVSFromSource(const String& source, const Array<BindingPoint>& bindingPoints) override;

		PixelShader::IDType createPS(ByteArray&&) override { return 0; }

		PixelShader::IDType createPSFromFile(const FilePath&, const Array<BindingPoint>&) override { return 0; }
		
		PixelShader::IDType createPSFromSource(const String& source, const Array<BindingPoint>& bindingPoints) override;

		void releaseVS(VertexShader::IDType handleID) override;

		void releasePS(PixelShader::IDType handleID) override;
		
		ByteArrayView getBinaryViewVS(VertexShader::IDType) override
		{
			return ByteArrayView();
		}

		ByteArrayView getBinaryViewPS(PixelShader::IDType) override
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
		
		void setVS(VertexShader::IDType) override {}

		void setPS(PixelShader::IDType) override {}
		
		GLuint getVSProgram(VertexShader::IDType handleID);
		
		GLuint getPSProgram(PixelShader::IDType handleID);
	};
}

# endif
