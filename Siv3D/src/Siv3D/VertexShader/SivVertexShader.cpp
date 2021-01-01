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

# include <Siv3D/VertexShader.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<VertexShader>>::AssetIDWrapper()
	{
		if (!Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`VertexShader` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<VertexShader>>::~AssetIDWrapper()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Shader))
		{
			p->releaseVS(m_id);
		}
	}

	VertexShader::VertexShader()
	{

	}

	VertexShader::VertexShader(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
		: AssetHandle(std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Shader)->createVSFromFile(path, entryPoint, bindings)))
	{

	}

	const Blob& VertexShader::getBinary() const noexcept
	{
		return SIV3D_ENGINE(Shader)->getBinaryVS(m_handle->id());
	}
}
