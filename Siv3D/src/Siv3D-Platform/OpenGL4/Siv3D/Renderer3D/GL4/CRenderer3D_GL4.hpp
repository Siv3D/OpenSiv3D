//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Renderer3D/Renderer3DCommon.hpp>
# include "GL4Renderer3DCommand.hpp"

namespace s3d
{
	class CRenderer_GL4;
	class CShader_GL4;
	class CTexture_GL4;
	class CMesh_GL4;

	struct GL4StandardVS3D
	{
		VertexShader forward;

		VertexShader::IDType forwardID;

		bool setup()
		{
			const bool result = !!forward;

			forwardID = forward.id();

			return result;
		}
	};

	struct GL4StandardPS3D
	{
		PixelShader forwardShape;
		PixelShader forwardTexture;

		PixelShader::IDType forwardShapeID;
		PixelShader::IDType forwardTextureID;

		bool setup()
		{
			const bool result = forwardShape && forwardTexture;

			forwardShapeID = forwardShape.id();
			forwardTextureID = forwardTexture.id();

			return result;
		}
	};

	class CRenderer3D_GL4 final : public ISiv3DRenderer3D
	{
	public:

		CRenderer3D_GL4();

		~CRenderer3D_GL4() override;

		void init() override;

	private:

		CRenderer_GL4* pRenderer = nullptr;
		CShader_GL4* pShader = nullptr;
		CTexture_GL4* pTexture = nullptr;
		CMesh_GL4* pMesh = nullptr;

		std::unique_ptr<GL4StandardVS3D> m_standardVS;
		std::unique_ptr<GL4StandardPS3D> m_standardPS;

		ConstantBuffer<VSConstants3D> m_vsConstants3D;
		ConstantBuffer<PSConstants3D> m_psConstants3D;

		Optional<VertexShader> m_currentCustomVS;
		Optional<PixelShader> m_currentCustomPS;
	};
}
