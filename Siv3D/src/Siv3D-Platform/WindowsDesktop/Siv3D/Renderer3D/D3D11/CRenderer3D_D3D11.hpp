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
# include <Siv3D/Mat4x4.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include "D3D11Renderer3DCommand.hpp"

namespace s3d
{
	class CRenderer_D3D11;
	class CShader_D3D11;
	class CTexture_D3D11;
	class CMesh_D3D11;

	struct D3D11StandardVS3D
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

	struct D3D11StandardPS3D
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

	struct VSConstants3D
	{
		Mat4x4 localToWorld = Mat4x4::Identity();
		Mat4x4 worldToProjected = Mat4x4::Identity();
		Float4 diffuse = Float4{ 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct PSConstants3D
	{
		Float4 placeholder{ 1.0f, 1.0f, 1.0f, 1.0f };
	};

	class CRenderer3D_D3D11 final : public ISiv3DRenderer3D
	{
	public:

		CRenderer3D_D3D11();

		~CRenderer3D_D3D11() override;

		void init() override;

		void addMesh(const Mesh& mesh, const Mat4x4& mat, const Float4& color) override;

		void addTexturedMesh(const Mesh& mesh, const Texture& texture, const Mat4x4& mat, const Float4& color) override;

		void setCameraTransform(const Mat4x4& matrix) override;

		void setRenderTarget(const Optional<RenderTexture>& rt) override;

		Optional<RenderTexture> getRenderTarget() const override;

		void flush();


	private:

		CRenderer_D3D11* pRenderer = nullptr;
		CShader_D3D11* pShader = nullptr;
		CTexture_D3D11* pTexture = nullptr;
		CMesh_D3D11* pMesh = nullptr;
		ID3D11Device* m_device = nullptr;
		ID3D11DeviceContext* m_context = nullptr;

		std::unique_ptr<D3D11StandardVS3D> m_standardVS;
		std::unique_ptr<D3D11StandardPS3D> m_standardPS;

		ConstantBuffer<VSConstants3D> m_vsConstants3D;
		ConstantBuffer<PSConstants3D> m_psConstants3D;

		ComPtr<ID3D11InputLayout> m_inputLayout;

		D3D11Renderer3DCommandManager m_commandManager;

		Optional<VertexShader> m_currentCustomVS;
		Optional<PixelShader> m_currentCustomPS;
	};
}
