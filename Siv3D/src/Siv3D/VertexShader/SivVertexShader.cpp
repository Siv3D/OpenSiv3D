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
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/ByteArrayView.hpp>
# include <Siv3D/EngineMessageBox.hpp>

namespace s3d
{
	template <>
	AssetHandle<VertexShader::Tag>::AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`VertexShader` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<VertexShader::Tag>::AssetHandle(const IDWrapperType id) noexcept
		: m_id(id)
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`VertexShader` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<VertexShader::Tag>::~AssetHandle()
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

	VertexShader::VertexShader()
		: m_handle(std::make_shared<VertexShaderHandle>())
	{

	}

	VertexShader::VertexShader(const FilePath& path, const Array<ConstantBufferBinding>& bindings)
		: m_handle(std::make_shared<VertexShaderHandle>(Siv3DEngine::Get<ISiv3DShader>()->createVSFromFile(std::move(path), bindings)))
	{

	}
	
	//VertexShader::VertexShader(Arg::source_<String> source, const Array<ConstantBufferBinding>& bindings)
	//	: m_handle(std::make_shared<VertexShaderHandle>(Siv3DEngine::GetShader()->createVSFromSource(source.value(), bindings)))
	//{
	//	
	//}

	VertexShader::~VertexShader()
	{

	}

	void VertexShader::release()
	{
		m_handle = std::make_shared<VertexShaderHandle>();
	}

	bool VertexShader::isEmpty() const
	{
		return m_handle->id().isNullAsset();
	}

	VertexShader::operator bool() const
	{
		return !isEmpty();
	}

	VertexShaderID VertexShader::id() const
	{
		return m_handle->id();
	}

	bool VertexShader::operator ==(const VertexShader& shader) const
	{
		return m_handle->id() == shader.m_handle->id();
	}

	bool VertexShader::operator !=(const VertexShader& shader) const
	{
		return m_handle->id() != shader.m_handle->id();
	}

	ByteArrayView VertexShader::getBinaryView() const
	{
		return Siv3DEngine::Get<ISiv3DShader>()->getBinaryView(m_handle->id());
	}
}
