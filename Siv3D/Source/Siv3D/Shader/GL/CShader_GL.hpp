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

namespace s3d
{
	class CShader_GL : public ISiv3DShader
	{
	private:

		Array<VertexShader> m_standardVSs;

		Array<PixelShader> m_standardPSs;

	public:

		CShader_GL();

		~CShader_GL() override;

		bool init();

		bool compileHLSL(IReader& reader, ByteArray& to, const char* filePath, const char* entryPoint, const char*target) override
		{
			return false;
		}

		VertexShader::IDType createVS(ByteArray&& binary) override { return 0; }

		PixelShader::IDType createPS(ByteArray&& binary) override { return 0; }

		void releaseVS(VertexShader::IDType handleID) override {}

		void releasePS(PixelShader::IDType handleID) override {}

		ByteArrayView getBinaryViewVS(VertexShader::IDType handleID) override
		{
			return ByteArrayView();
		}

		ByteArrayView getBinaryViewPS(PixelShader::IDType handleID) override
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

		void setVS(VertexShader::IDType handleID) override {}

		void setPS(PixelShader::IDType handleID) override {}
	};
}

# endif
