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

# include "CXInput.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
    CXInput::CXInput()
    : m_inputs{{ detail::XInput_impl(0), detail::XInput_impl(1),
        detail::XInput_impl(2), detail::XInput_impl(3) }}
    {
        
    }
    
    CXInput::~CXInput()
    {
        LOG_TRACE(U"CXInput::~CXInput()");
    }
    
    void CXInput::init()
    {
		LOG_TRACE(U"CXInput::init()");

		LOG_INFO(U"ℹ️ CXInput initialized");
    }
    
    void CXInput::update(const bool)
    {
        
    }
    
    bool CXInput::isConnected([[maybe_unused]] const size_t userIndex) const
    {
        assert(userIndex < XInput.MaxUserCount);
        
        return false;
    }
    
    void CXInput::setDeadZone([[maybe_unused]] const size_t userIndex, const DeadZoneIndex, const DeadZone&)
    {
        assert(userIndex < XInput.MaxUserCount);
    }
    
    void CXInput::setVibration([[maybe_unused]] const size_t userIndex, const double, const double)
    {
        assert(userIndex < XInput.MaxUserCount);
    }
    
    std::pair<double, double> CXInput::getVibration([[maybe_unused]] const size_t userIndex) const
    {
        assert(userIndex < XInput.MaxUserCount);
        
        return{ 0.0, 0.0 };
    }
    
    void CXInput::pauseVibration([[maybe_unused]] const size_t userIndex)
    {
        assert(userIndex < XInput.MaxUserCount);
    }
    
    void CXInput::resumeVibration([[maybe_unused]] const size_t userIndex)
    {
        assert(userIndex < XInput.MaxUserCount);
    }
    
    bool CXInput::down([[maybe_unused]] const size_t userIndex, const uint32) const
    {
        assert(userIndex < XInput.MaxUserCount);
        
        return false;
    }
    
    bool CXInput::pressed([[maybe_unused]] const size_t userIndex, const uint32) const
    {
        assert(userIndex < XInput.MaxUserCount);
        
        return false;
    }
    
    bool CXInput::up([[maybe_unused]] const size_t userIndex, const uint32) const
    {
        assert(userIndex < XInput.MaxUserCount);
        
        return false;
    }
    
    Duration CXInput::pressedDuration([[maybe_unused]] const size_t userIndex, const uint32) const
    {
        assert(userIndex < XInput.MaxUserCount);
        
        return Duration(0.0);
    }
    
    const detail::XInput_impl& CXInput::getInput(const size_t userIndex) const
    {
        assert(userIndex < XInput.MaxUserCount);
        
        return m_inputs[userIndex];
    }
}
