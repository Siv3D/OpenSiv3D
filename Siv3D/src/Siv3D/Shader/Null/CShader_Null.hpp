//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/Shader/IShader.hpp>

namespace s3d
{
	class CShader_Null final : public ISiv3DShader
	{
	public:

		CShader_Null();

		~CShader_Null() override;

		void init() override;

		VertexShader::IDType createVSFromFile(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;

		VertexShader::IDType createVSFromSource(StringView source, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;

		PixelShader::IDType createPSFromFile(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;

		PixelShader::IDType createPSFromSource(StringView source, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;

		void releaseVS(VertexShader::IDType handleID) override;

		void releasePS(PixelShader::IDType handleID) override;

		void setVS(VertexShader::IDType handleID) override;

		void setPS(PixelShader::IDType handleID) override;

		const Blob& getBinaryVS(VertexShader::IDType handleID) override;

		const Blob& getBinaryPS(PixelShader::IDType handleID) override;

		void setConstantBufferVS(uint32 slot, const ConstantBufferBase& cb) override;

		void setConstantBufferPS(uint32 slot, const ConstantBufferBase& cb) override;

		const VertexShader& getEngineVS(EngineVS vs) const override;

		const PixelShader& getEnginePS(EnginePS ps) const override;

		void setQuadWarpCB(const VS2DQuadWarp& vsCB, const PS2DQuadWarp& psCB) override;

	private:

		Blob m_emptyBinary;

		std::unique_ptr<VertexShader> m_emptyVS;

		std::unique_ptr<PixelShader> m_emptyPS;
	};
}
