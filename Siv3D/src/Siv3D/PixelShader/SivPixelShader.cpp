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

# include <Siv3DEngine.hpp>
# include <Shader/IShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/ByteArrayView.hpp>
# include <Siv3D/EngineMessageBox.hpp>

namespace s3d
{
	template <>
	AssetHandle<PixelShader::Tag>::AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`PixelShader` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<PixelShader::Tag>::AssetHandle(const IDWrapperType id) noexcept
		: m_id(id)
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`PixelShader` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<PixelShader::Tag>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::Get<ISiv3DShader>())
		{
			p->release(m_id);
		}
	}

	PixelShader::PixelShader()
		: m_handle(std::make_shared<PixelShaderHandle>())
	{

	}

	PixelShader::PixelShader(const FilePath& path, const Array<ConstantBufferBinding>& bindings)
		: m_handle(std::make_shared<PixelShaderHandle>(Siv3DEngine::Get<ISiv3DShader>()->createPSFromFile(std::move(path), bindings)))
	{

	}
	
	//PixelShader::PixelShader(Arg::source_<String> source, const Array<ConstantBufferBinding>& bindings)
	//	: m_handle(std::make_shared<PixelShaderHandle>(Siv3DEngine::Get<ISiv3DShader>()->createPSFromSource(source.value(), bindings)))
	//{
	//	
	//}

	PixelShader::~PixelShader()
	{

	}

	void PixelShader::release()
	{
		m_handle = std::make_shared<PixelShaderHandle>();
	}

	bool PixelShader::isEmpty() const
	{
		return m_handle->id().isNullAsset();
	}

	PixelShader::operator bool() const
	{
		return !isEmpty();
	}

	PixelShaderID PixelShader::id() const
	{
		return m_handle->id();
	}

	bool PixelShader::operator ==(const PixelShader& shader) const
	{
		return m_handle->id() == shader.m_handle->id();
	}

	bool PixelShader::operator !=(const PixelShader& shader) const
	{
		return m_handle->id() != shader.m_handle->id();
	}

	ByteArrayView PixelShader::getBinaryView() const
	{
		return Siv3DEngine::Get<ISiv3DShader>()->getBinaryView(m_handle->id());
	}
}
