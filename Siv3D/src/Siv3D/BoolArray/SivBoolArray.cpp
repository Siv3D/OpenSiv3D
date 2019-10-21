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

# include <Siv3D/BoolArray.hpp>

namespace s3d
{
	Array<bool>::Array()
		: base_type()
	{
	
	}

	Array<bool>::Array(const size_type count, const value_type& value)
		: base_type(count, value)
	{
	
	}

	Array<bool>::Array(const size_type count)
		: base_type(count, false)
	{
	
	}

	Array<bool>::Array(const Array& other)
		: base_type(other)
	{
	
	}

	Array<bool>::Array(Array&& other) noexcept
		: base_type(std::move(other))
	{
	
	}

	Array<bool>::Array(std::initializer_list<value_type> init)
		: base_type(init.begin(), init.end())
	{
	
	}

	void Array<bool>::swap(Array& other)
	{
		base_type::swap(other);
	}

	bool Array<bool>::isEmpty() const noexcept
	{
		return empty();
	}

	Array<bool>::operator bool() const noexcept
	{
		return !empty();
	}

	void Array<bool>::release()
	{
		clear();

		shrink_to_fit();
	}

	size_t Array<bool>::size_bytes() const noexcept
	{
		return size() * sizeof(value_type);
	}

	void Array<bool>::push_front(const value_type& value)
	{
		insert(begin(), value);
	}

	void Array<bool>::pop_front()
	{
		erase(begin());
	}

	Array<bool>& Array<bool>::operator <<(const value_type& value)
	{
		push_back(value);

		return *this;
	}

	Array<bool>& Array<bool>::append(const Array& other_array)
	{
		insert(end(), other_array.begin(), other_array.end());

		return *this;
	}

	bool& Array<bool>::choice()
	{
		return choice(GetDefaultRNG());
	}

	const bool& Array<bool>::choice() const
	{
		return choice(GetDefaultRNG());
	}

	Array<Array<bool>> Array<bool>::chunk(const size_t n) const
	{
		Array<Array<value_type>> result;

		if (n == 0)
		{
			return result;
		}

		for (size_t i = 0; i < (size() + n - 1) / n; ++i)
		{
			result.push_back(slice(i * n, n));
		}

		return result;
	}

	size_t Array<bool>::count(const value_type& value) const
	{
		size_t result = 0;

		for (const auto& v : *this)
		{
			if (v == value)
			{
				++result;
			}
		}

		return result;
	}

	Array<bool>& Array<bool>::drop(const size_t n)
	{
		erase(begin(), begin() + std::min(n, size()));

		return *this;
	}

	Array<bool>& Array<bool>::dropBack(const size_t n)
	{
		erase(end() - std::min(n, size()), end());

		return *this;
	}

	Array<bool> Array<bool>::dropped(const size_t n) const
	{
		if (n >= size())
		{
			return Array();
		}

		return Array(begin() + n, end());
	}

	const bool& Array<bool>::fetch(const size_t index, const value_type& defaultValue) const
	{
		if (index >= size())
		{
			return defaultValue;
		}

		return operator[](index);
	}

	Array<bool>& Array<bool>::fill(const value_type& value)
	{
		std::fill(begin(), end(), value);

		return *this;
	}

	Array<Array<bool>> Array<bool>::in_groups(const size_t group) const
	{
		Array<Array<value_type>> result;

		if (group == 0)
		{
			return result;
		}

		const size_t div = size() / group;
		const size_t mod = size() % group;
		size_t index = 0;

		for (size_t i = 0; i < group; ++i)
		{
			const size_t length = div + (mod > 0 && mod > i);

			result.push_back(slice(index, length));

			index += length;
		}

		return result;
	}

	bool Array<bool>::includes(const value_type& value) const
	{
		for (const auto& v : *this)
		{
			if (v == value)
			{
				return true;
			}
		}

		return false;
	}

	bool Array<bool>::isSorted() const
	{
		const size_t size_ = size();

		if (size_ <= 1)
		{
			return true;
		}

		const value_type* p = data();

		for (size_t i = 0; i < size_ - 1; ++i)
		{
			if (p[i] > p[i + 1])
			{
				return false;
			}
		}

		return true;
	}

	String Array<bool>::join(const StringView sep, const StringView begin, const StringView end) const
	{
		String s;

		s.append(begin);

		value_type isFirst = true;

		for (const auto& v : *this)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				s.append(sep);
			}

			s.append(ToString(v));
		}

		s.append(end);

		return s;
	}

	Array<bool>& Array<bool>::remove(const value_type& value)
	{
		erase(std::remove(begin(), end(), value), end());

		return *this;
	}

	Array<bool> Array<bool>::removed(const value_type& value) const &
	{
		Array new_array;

		for (const auto& v : *this)
		{
			if (v != value)
			{
				new_array.push_back(v);
			}
		}

		return new_array;
	}

	Array<bool> Array<bool>::removed(const value_type& value) &&
	{
		erase(std::remove(begin(), end(), value), end());

		shrink_to_fit();

		return std::move(*this);
	}

	Array<bool>& Array<bool>::remove_at(const size_t index)
	{
		if (index >= size())
		{
			throw std::out_of_range("Array::remove_at() index out of range");
		}

		erase(begin() + index);

		return *this;
	}

	Array<bool> Array<bool>::removed_at(const size_t index) const
	{
		if (index >= size())
		{
			throw std::out_of_range("Array::removed_at() index out of range");
		}

		Array new_array;

		new_array.reserve(size() - 1);

		new_array.insert(new_array.end(), begin(), begin() + index);

		new_array.insert(new_array.end(), begin() + index + 1, end());

		return new_array;
	}

	Array<bool>& Array<bool>::replace(const value_type& oldValue, const value_type& newValue)
	{
		for (auto& v : *this)
		{
			if (v == oldValue)
			{
				v = newValue;
			}
		}

		return *this;
	}

	Array<bool> Array<bool>::replaced(const value_type& oldValue, const value_type& newValue) const &
	{
		Array new_array;

		new_array.reserve(size());

		for (const auto& v : *this)
		{
			if (v == oldValue)
			{
				new_array.push_back(newValue);
			}
			else
			{
				new_array.push_back(v);
			}
		}

		return new_array;
	}

	Array<bool> Array<bool>::replaced(const value_type& oldValue, const value_type& newValue) &&
	{
		replace(oldValue, newValue);

		return std::move(*this);
	}

	Array<bool>& Array<bool>::reverse()
	{
		std::reverse(begin(), end());

		return *this;
	}

	Array<bool> Array<bool>::reversed() const &
	{
		return Array(rbegin(), rend());
	}

	Array<bool> Array<bool>::reversed() &&
	{
		reverse();

		return std::move(*this);
	}

	Array<bool>& Array<bool>::rotate(std::ptrdiff_t count)
	{
		if (empty())
		{
			;
		}
		else if (count > 0) // rotation to the left
		{
			if (static_cast<size_t>(count) > size())
			{
				count %= size();
			}

			std::rotate(begin(), begin() + count, end());
		}
		else if (count < 0) // rotation to the right
		{
			count = -count;

			if (static_cast<size_t>(count) > size())
			{
				count %= size();
			}

			std::rotate(rbegin(), rbegin() + count, rend());
		}

		return *this;
	}

	Array<bool> Array<bool>::rotated(const std::ptrdiff_t count) const &
	{
		return Array(*this).rotate(count);
	}

	Array<bool> Array<bool>::rotated(const std::ptrdiff_t count) &&
	{
		rotate(count);

		return std::move(*this);
	}

	Array<bool>& Array<bool>::rsort()
	{
		std::sort(begin(), end(), std::greater<>());

		return *this;
	}

	Array<bool> Array<bool>::rsorted() const&
	{
		return Array(*this).rsort();
	}

	Array<bool> Array<bool>::rsorted() &&
	{
		rsort();

		return std::move(*this);
	}

	Array<bool>& Array<bool>::shuffle()
	{
		return shuffle(GetDefaultRNG());
	}

	Array<bool> Array<bool>::shuffled() const &
	{
		return shuffled(GetDefaultRNG());
	}

	Array<bool> Array<bool>::shuffled() &&
	{
		return shuffled(GetDefaultRNG());
	}

	Array<bool> Array<bool>::slice(const size_t index) const
	{
		if (index >= size())
		{
			return Array();
		}

		return Array(begin() + index, end());
	}

	Array<bool> Array<bool>::slice(const size_t index, const size_t length) const
	{
		if (index >= size())
		{
			return Array();
		}

		return Array(begin() + index, begin() + std::min(index + length, size()));
	}

	Array<bool>& Array<bool>::sort()
	{
		std::sort(begin(), end());

		return *this;
	}

	Array<bool>& Array<bool>::stable_sort()
	{
		std::sort(begin(), end());

		return *this;
	}

	Array<bool> Array<bool>::sorted() const &
	{
		return Array(*this).sort();
	}

	Array<bool> Array<bool>::stable_sorted() const &
	{
		return Array(*this).sort();
	}

	Array<bool> Array<bool>::sorted() &&
	{
		sort();

		return std::move(*this);
	}

	Array<bool> Array<bool>::stable_sorted() &&
	{
		sort();

		return std::move(*this);
	}

	size_t Array<bool>::sum() const
	{
		return count(true);
	}

	Array<bool> Array<bool>::take(const size_t n) const
	{
		return Array(begin(), begin() + std::min(n, size()));
	}

	Array<bool>& Array<bool>::unique()
	{
		sort();

		erase(std::unique(begin(), end()), end());

		return *this;
	}

	Array<bool> Array<bool>::uniqued() const &
	{
		return Array(*this).unique();
	}

	Array<bool> Array<bool>::uniqued() &&
	{
		sort();

		erase(std::unique(begin(), end()), end());

		shrink_to_fit();

		return std::move(*this);
	}

	Array<bool> Array<bool>::values_at(std::initializer_list<size_t> indices) const
	{
		Array new_array;

		new_array.reserve(indices.size());

		for (auto index : indices)
		{
			if (index >= size())
			{
				throw std::out_of_range("Array::values_at() index out of range");
			}

			new_array.push_back(operator[](index));
		}

		return new_array;
	}
}
