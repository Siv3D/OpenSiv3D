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
	namespace Platform
	{
	# if SIV3D_PLATFORM(WINDOWS)

		template <size_t Alignment>
		[[nodiscard]]
		inline void* AlignedMalloc(size_t size) noexcept
		{
			return ::_aligned_malloc(size, Alignment);
		}

		inline void AlignedFree(void* const p) noexcept
		{
			::_aligned_free(p);
		}

	# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX) || SIV3D_PLATFORM(WEB)

		template <size_t Alignment>
		[[nodiscard]]
		inline void* AlignedMalloc(size_t size) noexcept
		{
			if (Alignment > Platform::MinAlignment)
			{
				void* p = nullptr;
				
				if (::posix_memalign(&p, Alignment, size) != 0)
				{
					return nullptr;
				}

				return p;
			}
			else
			{
				return std::malloc(size);
			}
		}

		inline void AlignedFree(void* const p) noexcept
		{
			std::free(p);
		}

	# else

		# error Unimplemented

	# endif
	}

	template <class Type, size_t Alignment>
	inline Type* AlignedMalloc(const size_t n)
	{
		return static_cast<Type*>(Platform::AlignedMalloc<Alignment>(sizeof(Type) * n));
	}

	inline void AlignedFree(void* const p)
	{
		Platform::AlignedFree(p);
	}

	template <class Type, class ...Args, std::enable_if_t<std::is_constructible_v<Type, Args...>>*>
	inline Type* AlignedNew(Args&&... args)
	{
		Type* p = AlignedMalloc<Type>();

		if (p == nullptr)
		{
			throw std::bad_alloc();
		}

		::new (p) Type(std::forward<Args>(args)...);

		return p;
	}

	template <class Type>
	inline void AlignedDelete(Type* const p)
	{
		if (p == nullptr)
		{
			return;
		}

		p->~Type();

		AlignedFree(p);
	}

	inline bool IsAligned(const void* const p, const size_t alignment) noexcept
	{
		return ((reinterpret_cast<std::uintptr_t>(p) % alignment) == 0);
	}

	template <class Type>
	inline void AlignedDeleter<Type>::operator() (Type* p)
	{
		AlignedDelete(p);
	}
}
