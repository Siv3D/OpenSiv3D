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

# include <Siv3D/Trail.hpp>
# include <Siv3D/TrailRenderer/ITrailRenderer.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	Trail::Trail(const double lifeTime, const ScaleFunction scaleFunc, const AlphaFunction alphaFunc) noexcept
		: m_baseLifeTime(static_cast<float>(lifeTime))
		, m_scaleFunc{ scaleFunc }
		, m_alphaFunc{ alphaFunc } {}

	void Trail::setLifeTime(const double lifeTime) noexcept
	{
		m_baseLifeTime = static_cast<float>(lifeTime);
	}

	float Trail::getLifeTime() const noexcept
	{
		return m_baseLifeTime;
	}

	void Trail::setScaleFunction(ScaleFunction scaleFunc) noexcept
	{
		m_scaleFunc = scaleFunc;
	}

	Trail::ScaleFunction Trail::getScaleFunction() const noexcept
	{
		return m_scaleFunc;
	}

	void Trail::setAlphaFunction(AlphaFunction alphaFunc) noexcept
	{
		m_alphaFunc = alphaFunc;
	}

	Trail::AlphaFunction Trail::getAlphaFunction() const noexcept
	{
		return m_alphaFunc;
	}

	size_t Trail::num_points() const noexcept
	{
		return m_ringBuffer.size();
	}

	void Trail::add(const Float2& pos, const ColorF& color, const double size)
	{
		const Point point{
			.pos = pos,
			.lifeTime = m_baseLifeTime,
			.halfThickness = (static_cast<float>(size) * 0.5f),
			.color = color.toFloat4() };

		if (m_ringBuffer.isEmpty())
		{
			m_ringBuffer.push(point);
		}
		else if (auto& back = m_ringBuffer.back(); back.pos == pos)
		{
			back = point;
		}
		else
		{
			m_ringBuffer.push(point);
		}
	}

	void Trail::update(const double deltaTime) noexcept
	{
		m_ringBuffer.update(static_cast<float>(deltaTime));
	}

	void Trail::clear() noexcept
	{
		m_ringBuffer.clear();
	}

	const Trail::Point& Trail::front() const noexcept
	{
		return m_ringBuffer.front();
	}

	const Trail::Point& Trail::back() const noexcept
	{
		return m_ringBuffer.back();
	}

	const Trail::Point& Trail::point(const size_t index) const noexcept
	{
		return m_ringBuffer.point(index);
	}

	void Trail::draw() const
	{
		SIV3D_ENGINE(TrailRenderer)->draw(*this);
	}

	void Trail::draw(const Texture& texture) const
	{
		SIV3D_ENGINE(TrailRenderer)->draw(*this, texture);
	}


	Trail::RingBuffer::RingBuffer()
		: m_points(MaxPoints) {}

	bool Trail::RingBuffer::isEmpty() const noexcept
	{
		return (m_size == 0);
	}

	bool Trail::RingBuffer::isFull() const noexcept
	{
		return (m_size == MaxPoints);
	}

	size_t Trail::RingBuffer::size() const noexcept
	{
		return m_size;
	}

	void Trail::RingBuffer::push(const Point& point) noexcept
	{
		if (isFull())
		{
			pop_front_non_empty();
		}

		m_points[(m_startIndex + m_size) & PointMask] = point;

		++m_size;
	}

	void Trail::RingBuffer::update(const float deltaTime) noexcept
	{
		for (auto& point : m_points)
		{
			point.lifeTime -= deltaTime;
		}

		while (m_size && (m_points[m_startIndex].lifeTime <= 0.0f))
		{
			m_startIndex = ((m_startIndex + 1) & PointMask);
			--m_size;
		}
	}

	void Trail::RingBuffer::clear() noexcept
	{
		m_startIndex = 0;
		m_size = 0;
	}

	const Trail::Point& Trail::RingBuffer::front() const noexcept
	{
		assert(m_size);
		return m_points[m_startIndex];
	}

	const Trail::Point& Trail::RingBuffer::back() const noexcept
	{
		assert(m_size);
		return m_points[(m_startIndex + m_size - 1) & PointMask];
	}

	Trail::Point& Trail::RingBuffer::back() noexcept
	{
		assert(m_size);
		return m_points[(m_startIndex + m_size - 1) & PointMask];
	}

	const Trail::Point& Trail::RingBuffer::point(const size_t index) const noexcept
	{
		assert(index < m_size);
		return m_points[(m_startIndex + index) & PointMask];
	}

	void Trail::RingBuffer::pop_front_non_empty() noexcept
	{
		assert(0 < m_size);
		m_startIndex = ((m_startIndex + 1) & PointMask);
		--m_size;
	}
}
