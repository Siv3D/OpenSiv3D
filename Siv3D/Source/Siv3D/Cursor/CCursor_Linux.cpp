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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "../Siv3DEngine.hpp"
# include "CCursor_Linux.hpp"

// TODO : implemantation
void Linux_GetScreenCursorPos(double* xpos, double* ypos) { }

namespace s3d
{
	CCursor_Linux::CCursor_Linux()
	{

	}

	CCursor_Linux::~CCursor_Linux()
	{

	}

	bool CCursor_Linux::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();

		update();
		 
		m_previousScreenPos = m_screenPos;
		m_previousClientPos_raw = m_screenPos;
		m_screenDelta.set(0, 0);
		m_clientDelta.set(0, 0);

		return true;
	}

	void CCursor_Linux::update()
	{
		double clientX, clientY;
		::glfwGetCursorPos(m_glfwWindow, &clientX, &clientY);
		m_clientPos_raw.set(static_cast<int32>(clientX), static_cast<int32>(clientY));
		m_previousClientPos_raw = m_clientPos_raw;

		m_clientPos_transformedVec2 = m_transformInv.transform(m_clientPos_raw);
		m_previousClientPos_transformedVec2 = m_transformInv.transform(m_previousClientPos_raw);

		m_clientPos_transformedPoint = m_clientPos_transformedVec2.asPoint();
		m_previousClientPos_transformedPoint = m_previousClientPos_transformedVec2.asPoint();

		m_screenPos.set(static_cast<int32>(clientX), static_cast<int32>(clientY));
		m_screenDelta = m_screenPos - m_previousScreenPos;
		m_previousScreenPos = m_screenPos;
	}

	const Point& CCursor_Linux::previousScreenPos() const
	{
		return m_previousScreenPos;
	}

	const Point& CCursor_Linux::screenPos() const
	{
		return m_screenPos;
	}

	const Point& CCursor_Linux::screenDelta() const
	{
		return m_screenDelta;
	}

	const Point& CCursor_Linux::previousClientPos() const
	{
		return m_previousClientPos;
	}

	const Point& CCursor_Linux::clientPos() const
	{
		return m_previousClientPos;
	}

	Point CCursor_Linux::clientDelta() const
	{
		return m_clientPos_transformedPoint - m_previousClientPos_transformedPoint;
	}

	const Vec2& CCursor_Linux::previousClientPosF() const
	{
		return m_previousClientPos_transformedVec2;
	}

	const Vec2& CCursor_Linux::clientPosF() const
	{
		return m_previousClientPos_transformedVec2;
	}

	Vec2 CCursor_Linux::clientDeltaF() const
	{
		return m_clientPos_transformedVec2 - m_previousClientPos_transformedVec2;
	}

	void CCursor_Linux::setPos(const int32 x, const int32 y)
	{

	}

	void CCursor_macOS::setTransform(const Mat3x2& matrix)
	{
		if (!::memcmp(&m_transform, &matrix, sizeof(Mat3x2)))
		{
			return;
		}

		m_transform = matrix;
		m_transformInv = m_transform.inverse();

		m_clientPos_transformedVec2 = m_transformInv.transform(m_clientPos_raw);
		m_previousClientPos_transformedVec2 = m_transformInv.transform(m_previousClientPos_raw);

		m_clientPos_transformedPoint = m_clientPos_transformedVec2.asPoint();
		m_previousClientPos_transformedPoint = m_previousClientPos_transformedVec2.asPoint();
	}

	const Mat3x2& CCursor_macOS::getTransform() const
	{
		return m_transform;
	}

	void CCursor_Linux::clip(const Optional<Rect>& rect)
	{
		m_clipRect = rect;
	}

	void CCursor_Linux::setStyle(CursorStyle style)
	{
		// [Siv3D ToDo]
	}

	CursorStyle CCursor_Linux::getStyle()
	{
		// [Siv3D ToDo]
		return CursorStyle::Default;
	}
}

# endif
