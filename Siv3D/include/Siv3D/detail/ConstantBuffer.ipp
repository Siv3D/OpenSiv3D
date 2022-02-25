//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	template <class Type>
	inline ConstantBuffer<Type>::ConstantBuffer()
		: m_base{ Size } {}

	template <class Type>
	inline ConstantBuffer<Type>::ConstantBuffer(const Type& data)
		: ConstantBuffer{}
	{
		m_wrapper->data	= data;
	}

	template <class Type>
	inline ConstantBuffer<Type>::~ConstantBuffer()
	{
		AlignedDelete(m_wrapper);
	}

	template <class Type>
	inline ConstantBuffer<Type>& ConstantBuffer<Type>::operator =(const Type& data)
	{
		m_hasDirty = true;
		m_wrapper->data = data;
	 	return *this;
	}

	template <class Type>
	inline constexpr size_t ConstantBuffer<Type>::size() const noexcept
	{
		return Size;
	}

	template <class Type>
	inline const float* ConstantBuffer<Type>::data() const noexcept
	{
		return static_cast<const float*>(static_cast<const void*>(&(m_wrapper->data)));
	}

	template <class Type>
	inline Type& ConstantBuffer<Type>::get() noexcept
	{
		m_hasDirty = true;
		return *(m_wrapper->data);
	}

	template <class Type>
	inline const Type& ConstantBuffer<Type>::get() const noexcept
	{
		return *(m_wrapper->data);
	}

	template <class Type>
	inline bool ConstantBuffer<Type>::isDirty() const noexcept
	{
		return m_hasDirty;
	}

	template <class Type>
	inline bool ConstantBuffer<Type>::_update_if_dirty()
	{
		if (not m_hasDirty)
		{
			return false;
		}
		
		m_hasDirty = false;

		return m_base._internal_update(data(), Size);
	}

	template <class Type>
	inline const ConstantBufferBase& ConstantBuffer<Type>::base() const noexcept
	{
		return m_base;
	}

	template <class Type>
	inline Type& ConstantBuffer<Type>::operator *() noexcept
	{
		m_hasDirty = true;
		return *(m_wrapper->data);
	}

	template <class Type>
	inline const Type& ConstantBuffer<Type>::operator *() const noexcept
	{
		return *(m_wrapper->data);
	}

	template <class Type>
	inline Type* ConstantBuffer<Type>::operator ->() noexcept
	{
		m_hasDirty = true;
		return &(m_wrapper->data);
	}

	template <class Type>
	inline const Type* ConstantBuffer<Type>::operator ->() const noexcept
	{
		return &(m_wrapper->data);
	}
}
