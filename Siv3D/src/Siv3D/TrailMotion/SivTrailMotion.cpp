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

# include <Siv3D/TrailMotion.hpp>

namespace s3d
{
	TrailMotion::TrailMotion(const double lifeTime, const double frequency, const Trail::ScaleFunction scaleFunc, const Trail::AlphaFunction alphaFunc)
		: m_trail{ lifeTime, scaleFunc, alphaFunc }
		, m_frequency(Clamp(frequency, MinFrequency, MaxFrequency)) {}

	TrailMotion& TrailMotion::setLifeTime(const double lifeTime) noexcept
	{
		m_trail.setLifeTime(lifeTime);
		return *this;
	}

	float TrailMotion::getLifeTime() const noexcept
	{
		return m_trail.getLifeTime();
	}

	TrailMotion& TrailMotion::setScaleFunction(const Trail::ScaleFunction scaleFunc) noexcept
	{
		m_trail.setScaleFunction(scaleFunc);
		return *this;
	}

	Trail::ScaleFunction TrailMotion::getScaleFunction() const noexcept
	{
		return m_trail.getScaleFunction();
	}

	TrailMotion& TrailMotion::setAlphaFunction(const Trail::AlphaFunction alphaFunc) noexcept
	{
		m_trail.setAlphaFunction(alphaFunc);
		return *this;
	}

	Trail::AlphaFunction TrailMotion::getAlphaFunction() const noexcept
	{
		return m_trail.getAlphaFunction();
	}

	size_t TrailMotion::num_points() const noexcept
	{
		return m_trail.num_points();
	}

	TrailMotion& TrailMotion::setFrequency(const double frequency)
	{
		m_frequency = Clamp(frequency, MinFrequency, MaxFrequency);
		return *this;
	}

	double TrailMotion::getFrequency() const noexcept
	{
		return m_frequency;
	}

	TrailMotion& TrailMotion::setCenter(const double x, const double y) noexcept
	{
		m_center.set(x, y);
		return *this;
	}

	TrailMotion& TrailMotion::setCenter(const Vec2& center) noexcept
	{
		m_center = center;
		return *this;
	}

	const Vec2& TrailMotion::getCenter() const noexcept
	{
		return m_center;
	}

	TrailMotion& TrailMotion::setPositionFunction(const std::function<Vec2(double)>& positionFunction)
	{
		m_positionFunction = positionFunction;
		return *this;
	}

	const std::function<Vec2(double)>& TrailMotion::getPositionFunction() const noexcept
	{
		return m_positionFunction;
	}

	TrailMotion& TrailMotion::setColor(const ColorF& color)
	{
		m_colorFunction = [color](double) { return color; };
		return *this;
	}

	TrailMotion& TrailMotion::setColorFunction(const std::function<ColorF(double)>& colorFunction)
	{
		m_colorFunction = colorFunction;
		return *this;
	}

	const std::function<ColorF(double)>& TrailMotion::getColorFunction() const noexcept
	{
		return m_colorFunction;
	}

	TrailMotion& TrailMotion::setSize(const double size)
	{
		m_sizeFunction = [size](double) { return size; };
		return *this;
	}

	TrailMotion& TrailMotion::setSizeFunction(const std::function<double(double)>& sizeFunction)
	{
		m_sizeFunction = sizeFunction;
		return *this;
	}

	const std::function<double(double)>& TrailMotion::getSizeFunction() const noexcept
	{
		return m_sizeFunction;
	}

	void TrailMotion::update(const double deltaTime)
	{
		m_accumulatedTime += deltaTime;

		const double timeStep = (1.0 / m_frequency);

		while (timeStep <= m_accumulatedTime)
		{
			m_time += timeStep;

			m_accumulatedTime -= timeStep;

			m_trail.update(timeStep);

			m_trail.add((m_center + m_positionFunction(m_time)), m_colorFunction(m_time), m_sizeFunction(m_time));
		}
	}

	void TrailMotion::draw() const
	{
		m_trail.draw();
	}

	void TrailMotion::draw(const Texture& texture) const
	{
		m_trail.draw(texture);
	}

	void TrailMotion::clear() noexcept
	{
		m_trail.clear();
	}
}
