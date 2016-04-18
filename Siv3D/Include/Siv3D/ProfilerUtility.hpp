//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Platfor.hpp"
# include "Time.hpp"
# include "Logger.hpp"

namespace s3d
{
    /// <summary>
    /// ミリ秒カウンター
    /// </summary>
    /// <remarks>
    /// 経過時間をミリ秒で計測します。
    /// </remarks>
    class MillisecClock
    {
    private:
        
        uint64 m_start = Time::GetMicrosec();
        
    public:
        
        /// <summary>
        /// 経過時間（ミリ秒）
        /// </summary>
        uint64 ms() const { return (Time::GetMicrosec() - m_start) / 1000ULL; }
        
        /// <summary>
        /// ログに経過時間を出力します。
        /// </summary>
        /// <returns>
        /// なし
        /// </returns>
        void log() const { Log(ms(), L"ms"); }
        
        /// <summary>
        /// 経過時間をデバッグ表示します。
        /// </summary>
        /// <returns>
        /// なし
        /// </returns>
        //void print() const { Println(ms(), L"ms"); }
    };
    
    /// <summary>
    /// マイクロ秒カウンター
    /// </summary>
    /// <remarks>
    /// 経過時間をマイクロ秒で計測します。
    /// </remarks>
    class MicrosecClock
    {
    private:
        
        uint64 m_start = Time::GetMicrosec();
        
    public:
        
        /// <summary>
        /// 経過時間（マイクロ秒）
        /// </summary>
        uint64 us() const { return Time::GetMicrosec() - m_start; }
        
        /// <summary>
        /// ログに経過時間を出力します。
        /// </summary>
        /// <returns>
        /// なし
        /// </returns>
        void log() const { Log(us(), L"us"); }
        
        /// <summary>
        /// 経過時間をデバッグ表示します。
        /// </summary>
        /// <returns>
        /// なし
        /// </returns>
        //void print() const { Println(us(), L"us"); }
    };
    
    /// <summary>
    /// ナノ秒カウンター
    /// </summary>
    /// <remarks>
    /// 経過時間をナノ秒で計測します。
    /// </remarks>
    class NanosecClock
    {
    private:
        
        uint64 m_start = Time::GetNanoosec();
        
    public:
        
        /// <summary>
        /// 経過時間（ナノ秒）
        /// </summary>
        uint64 ns() const { return Time::GetNanosec() - m_start; }
        
        /// <summary>
        /// ログに経過時間を出力します。
        /// </summary>
        /// <returns>
        /// なし
        /// </returns>
        void log() const { Log(ns(), L"ns"); }
        
        /// <summary>
        /// 経過時間をデバッグ表示します。
        /// </summary>
        /// <returns>
        /// なし
        /// </returns>
        //void print() const { Println(ns(), L"ns"); }
    };
    
# if defined(SIV3D_TARGET_WINDOWS)
    /// <summary>
    /// CPU サイクルカウンター
    /// </summary>
    /// <remarks>
    /// 経過時間を CPU サイクルで計測します。
    /// </remarks>
    class RDTSC
    {
    private:
        
        uint64 m_start = ::__rdtsc();
        
    public:

        ~RDTSC()
        {
            const auto result = ::__rdtsc() - m_start;

            Log(result, L" cycles");
        }
    };
# endif
}
