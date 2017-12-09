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

# pragma once
# include "Fwd.hpp"
# include "Key.hpp"

namespace s3d
{
	/// <summary>
	/// Ctrl + break キー
	/// </summary>
	constexpr Key KeyCancel{ InputDevice::Keyboard, 0x03 };

	/// <summary>
	/// Backspace キー
	/// </summary>
	constexpr Key KeyBackspace{ InputDevice::Keyboard, 0x08 };

	/// <summary>
	/// Tab キー
	/// </summary>
	constexpr Key KeyTab{ InputDevice::Keyboard, 0x09 };

	/// <summary>
	/// Clear(NumLock を外した状態のテンキー5) キー
	/// </summary>
	constexpr Key KeyClear{ InputDevice::Keyboard, 0x0C };

	/// <summary>
	/// Enter キー
	/// </summary>
	constexpr Key KeyEnter{ InputDevice::Keyboard, 0x0D };

	/// <summary>
	/// Shift キー
	/// </summary>
	constexpr Key KeyShift{ InputDevice::Keyboard, 0x10 };

	/// <summary>
	/// Ctrl キー
	/// </summary>
	constexpr Key KeyControl{ InputDevice::Keyboard, 0x11 };

	/// <summary>
	/// Alt キー
	/// </summary>
	constexpr Key KeyAlt{ InputDevice::Keyboard, 0x12 };

	/// <summary>
	/// Pause キー
	/// </summary>
	constexpr Key KeyPause{ InputDevice::Keyboard, 0x13 };

	/// <summary>
	/// Escape キー
	/// </summary>
	constexpr Key KeyEscape{ InputDevice::Keyboard, 0x1B };

	/// <summary>
	/// スペースキー
	/// </summary>
	constexpr Key KeySpace{ InputDevice::Keyboard, 0x20 };

	/// <summary>
	/// PageUp キー
	/// </summary>
	constexpr Key KeyPageUp{ InputDevice::Keyboard, 0x21 };

	/// <summary>
	/// PageDown キー
	/// </summary>
	constexpr Key KeyPageDown{ InputDevice::Keyboard, 0x22 };

	/// <summary>
	/// End キー
	/// </summary>
	constexpr Key KeyEnd{ InputDevice::Keyboard, 0x23 };

	/// <summary>
	/// Home キー
	/// </summary>
	constexpr Key KeyHome{ InputDevice::Keyboard, 0x24 };

	/// <summary>
	/// ← キー
	/// </summary>
	constexpr Key KeyLeft{ InputDevice::Keyboard, 0x25 };

	/// <summary>
	/// ↑ キー
	/// </summary>
	constexpr Key KeyUp{ InputDevice::Keyboard, 0x26 };

	/// <summary>
	/// → キー
	/// </summary>
	constexpr Key KeyRight{ InputDevice::Keyboard, 0x27 };

	/// <summary>
	/// ↓ キー
	/// </summary>
	constexpr Key KeyDown{ InputDevice::Keyboard, 0x28 };

	/// <summary>
	/// PrintScreen キー
	/// </summary>
	constexpr Key KeyPrintScreen{ InputDevice::Keyboard, 0x2C };

	/// <summary>
	/// Insert キー
	/// </summary>
	constexpr Key KeyInsert{ InputDevice::Keyboard, 0x2D };

	/// <summary>
	/// Delete キー
	/// </summary>
	constexpr Key KeyDelete{ InputDevice::Keyboard, 0x2E };

	/// <summary>
	/// 0 キー
	/// </summary>
	constexpr Key Key0{ InputDevice::Keyboard, 0x30 };

	/// <summary>
	/// 1 キー
	/// </summary>
	constexpr Key Key1{ InputDevice::Keyboard, 0x31 };

	/// <summary>
	/// 2 キー
	/// </summary>
	constexpr Key Key2{ InputDevice::Keyboard, 0x32 };

	/// <summary>
	/// 3 キー
	/// </summary>
	constexpr Key Key3{ InputDevice::Keyboard, 0x33 };

	/// <summary>
	/// 4 キー
	/// </summary>
	constexpr Key Key4{ InputDevice::Keyboard, 0x34 };

	/// <summary>
	/// 5 キー
	/// </summary>
	constexpr Key Key5{ InputDevice::Keyboard, 0x35 };

	/// <summary>
	/// 6 キー
	/// </summary>
	constexpr Key Key6{ InputDevice::Keyboard, 0x36 };

	/// <summary>
	/// 7 キー
	/// </summary>
	constexpr Key Key7{ InputDevice::Keyboard, 0x37 };

	/// <summary>
	/// 8 キー
	/// </summary>
	constexpr Key Key8{ InputDevice::Keyboard, 0x38 };

	/// <summary>
	/// 9 キー
	/// </summary>
	constexpr Key Key9{ InputDevice::Keyboard, 0x39 };

	/// <summary>
	/// A キー
	/// </summary>
	constexpr Key KeyA{ InputDevice::Keyboard, 0x41 };

	/// <summary>
	/// B キー
	/// </summary>
	constexpr Key KeyB{ InputDevice::Keyboard, 0x42 };

	/// <summary>
	/// C キー
	/// </summary>
	constexpr Key KeyC{ InputDevice::Keyboard, 0x43 };

	/// <summary>
	/// D キー
	/// </summary>
	constexpr Key KeyD{ InputDevice::Keyboard, 0x44 };

	/// <summary>
	/// E キー
	/// </summary>
	constexpr Key KeyE{ InputDevice::Keyboard, 0x45 };

	/// <summary>
	/// F キー
	/// </summary>
	constexpr Key KeyF{ InputDevice::Keyboard, 0x46 };

	/// <summary>
	/// G キー
	/// </summary>
	constexpr Key KeyG{ InputDevice::Keyboard, 0x47 };

	/// <summary>
	/// H キー
	/// </summary>
	constexpr Key KeyH{ InputDevice::Keyboard, 0x48 };

	/// <summary>
	/// I キー
	/// </summary>
	constexpr Key KeyI{ InputDevice::Keyboard, 0x49 };

	/// <summary>
	/// J キー
	/// </summary>
	constexpr Key KeyJ{ InputDevice::Keyboard, 0x4A };

	/// <summary>
	/// K キー
	/// </summary>
	constexpr Key KeyK{ InputDevice::Keyboard, 0x4B };

	/// <summary>
	/// L キー
	/// </summary>
	constexpr Key KeyL{ InputDevice::Keyboard, 0x4C };

	/// <summary>
	/// M キー
	/// </summary>
	constexpr Key KeyM{ InputDevice::Keyboard, 0x4D };

	/// <summary>
	/// N キー
	/// </summary>
	constexpr Key KeyN{ InputDevice::Keyboard, 0x4E };

	/// <summary>
	/// O キー
	/// </summary>
	constexpr Key KeyO{ InputDevice::Keyboard, 0x4F };

	/// <summary>
	/// P キー
	/// </summary>
	constexpr Key KeyP{ InputDevice::Keyboard, 0x50 };

	/// <summary>
	/// Q キー
	/// </summary>
	constexpr Key KeyQ{ InputDevice::Keyboard, 0x51 };

	/// <summary>
	/// R キー
	/// </summary>
	constexpr Key KeyR{ InputDevice::Keyboard, 0x52 };

	/// <summary>
	/// S キー
	/// </summary>
	constexpr Key KeyS{ InputDevice::Keyboard, 0x53 };

	/// <summary>
	/// T キー
	/// </summary>
	constexpr Key KeyT{ InputDevice::Keyboard, 0x54 };

	/// <summary>
	/// U キー
	/// </summary>
	constexpr Key KeyU{ InputDevice::Keyboard, 0x55 };

	/// <summary>
	/// V キー
	/// </summary>
	constexpr Key KeyV{ InputDevice::Keyboard, 0x56 };

	/// <summary>
	/// W キー
	/// </summary>
	constexpr Key KeyW{ InputDevice::Keyboard, 0x57 };

	/// <summary>
	/// X キー
	/// </summary>
	constexpr Key KeyX{ InputDevice::Keyboard, 0x58 };

	/// <summary>
	/// Y キー
	/// </summary>
	constexpr Key KeyY{ InputDevice::Keyboard, 0x59 };

	/// <summary>
	/// Z キー
	/// </summary>
	constexpr Key KeyZ{ InputDevice::Keyboard, 0x5A };

	/// <summary>
	/// Numpad 0 キー
	/// </summary>
	constexpr Key KeyNum0{ InputDevice::Keyboard, 0x60 };

	/// <summary>
	/// Numpad 1 キー
	/// </summary>
	constexpr Key KeyNum1{ InputDevice::Keyboard, 0x61 };

	/// <summary>
	/// Numpad 2 キー
	/// </summary>
	constexpr Key KeyNum2{ InputDevice::Keyboard, 0x62 };

	/// <summary>
	/// Numpad 3 キー
	/// </summary>
	constexpr Key KeyNum3{ InputDevice::Keyboard, 0x63 };

	/// <summary>
	/// Numpad 4 キー
	/// </summary>
	constexpr Key KeyNum4{ InputDevice::Keyboard, 0x64 };

	/// <summary>
	/// Numpad 5 キー
	/// </summary>
	constexpr Key KeyNum5{ InputDevice::Keyboard, 0x65 };

	/// <summary>
	/// Numpad 6 キー
	/// </summary>
	constexpr Key KeyNum6{ InputDevice::Keyboard, 0x66 };

	/// <summary>
	/// Numpad 7 キー
	/// </summary>
	constexpr Key KeyNum7{ InputDevice::Keyboard, 0x67 };

	/// <summary>
	/// Numpad 8 キー
	/// </summary>
	constexpr Key KeyNum8{ InputDevice::Keyboard, 0x68 };

	/// <summary>
	/// Numpad 9 キー
	/// </summary>
	constexpr Key KeyNum9{ InputDevice::Keyboard, 0x69 };

	/// <summary>
	/// Numpad * キー
	/// </summary>
	constexpr Key KeyNumMultiply{ InputDevice::Keyboard, 0x6A };

	/// <summary>
	/// Numpad + キー
	/// </summary>
	constexpr Key KeyNumAdd{ InputDevice::Keyboard, 0x6B };

	/// <summary>
	/// Numpad Enter キー
	/// </summary>
	constexpr Key KeyNumEnter{ InputDevice::Keyboard, 0x6C};

	/// <summary>
	/// Numpad - キー
	/// </summary>
	constexpr Key KeyNumSubtract{ InputDevice::Keyboard, 0x6D };

	/// <summary>
	/// Numpad . キー
	/// </summary>
	constexpr Key KeyNumDecimal{ InputDevice::Keyboard, 0x6E };

	/// <summary>
	/// Numpad / キー
	/// </summary>
	constexpr Key KeyNumDivide{ InputDevice::Keyboard, 0x6F };

	/// <summary>
	/// F1 キー
	/// </summary>
	constexpr Key KeyF1{ InputDevice::Keyboard, 0x70 };

	/// <summary>
	/// F2 キー
	/// </summary>
	constexpr Key KeyF2{ InputDevice::Keyboard, 0x71 };

	/// <summary>
	/// F3 キー
	/// </summary>
	constexpr Key KeyF3{ InputDevice::Keyboard, 0x72 };

	/// <summary>
	/// F4 キー
	/// </summary>
	constexpr Key KeyF4{ InputDevice::Keyboard, 0x73 };

	/// <summary>
	/// F5 キー
	/// </summary>
	constexpr Key KeyF5{ InputDevice::Keyboard, 0x74 };

	/// <summary>
	/// F6 キー
	/// </summary>
	constexpr Key KeyF6{ InputDevice::Keyboard, 0x75 };

	/// <summary>
	/// F7 キー
	/// </summary>
	constexpr Key KeyF7{ InputDevice::Keyboard, 0x76 };

	/// <summary>
	/// F8 キー
	/// </summary>
	constexpr Key KeyF8{ InputDevice::Keyboard, 0x77 };

	/// <summary>
	/// F9 キー
	/// </summary>
	constexpr Key KeyF9{ InputDevice::Keyboard, 0x78 };

	/// <summary>
	/// F10 キー
	/// </summary>
	constexpr Key KeyF10{ InputDevice::Keyboard, 0x79 };

	/// <summary>
	/// F11 キー
	/// </summary>
	constexpr Key KeyF11{ InputDevice::Keyboard, 0x7A };

	/// <summary>
	/// F12 キー
	/// </summary>
	constexpr Key KeyF12{ InputDevice::Keyboard, 0x7B };

	/// <summary>
	/// F13 キー
	/// </summary>
	constexpr Key KeyF13{ InputDevice::Keyboard, 0x7C };

	/// <summary>
	/// F14 キー
	/// </summary>
	constexpr Key KeyF14{ InputDevice::Keyboard, 0x7D };

	/// <summary>
	/// F15 キー
	/// </summary>
	constexpr Key KeyF15{ InputDevice::Keyboard, 0x7E };

	/// <summary>
	/// F16 キー
	/// </summary>
	constexpr Key KeyF16{ InputDevice::Keyboard, 0x7F };

	/// <summary>
	/// F17 キー
	/// </summary>
	constexpr Key KeyF17{ InputDevice::Keyboard, 0x80 };

	/// <summary>
	/// F18 キー
	/// </summary>
	constexpr Key KeyF18{ InputDevice::Keyboard, 0x81 };

	/// <summary>
	/// F19 キー
	/// </summary>
	constexpr Key KeyF19{ InputDevice::Keyboard, 0x82 };

	/// <summary>
	/// F20 キー
	/// </summary>
	constexpr Key KeyF20{ InputDevice::Keyboard, 0x83 };

	/// <summary>
	/// F21 キー
	/// </summary>
	constexpr Key KeyF21{ InputDevice::Keyboard, 0x84 };

	/// <summary>
	/// F22 キー
	/// </summary>
	constexpr Key KeyF22{ InputDevice::Keyboard, 0x85 };

	/// <summary>
	/// F23 キー
	/// </summary>
	constexpr Key KeyF23{ InputDevice::Keyboard, 0x86 };

	/// <summary>
	/// F24 キー
	/// </summary>
	constexpr Key KeyF24{ InputDevice::Keyboard, 0x87 };

	/// <summary>
	/// NumLock キー
	/// </summary>
	constexpr Key KeyNumLock{ InputDevice::Keyboard, 0x90 };

	/// <summary>
	/// 左 Shift キー
	/// </summary>
	constexpr Key KeyLShift{ InputDevice::Keyboard, 0xA0 };

	/// <summary>
	/// 右 Shift キー
	/// </summary>
	constexpr Key KeyRShift{ InputDevice::Keyboard, 0xA1 };

	/// <summary>
	/// 左 Ctrl キー
	/// </summary>
	constexpr Key KeyLControl{ InputDevice::Keyboard, 0xA2 };

	/// <summary>
	/// 右 Ctrl キー
	/// </summary>
	constexpr Key KeyRControl{ InputDevice::Keyboard, 0xA3 };

	/// <summary>
	/// 左 Alt キー
	/// </summary>
	constexpr Key KeyLAlt{ InputDevice::Keyboard, 0xA4 };

	/// <summary>
	/// 右 Alt キー
	/// </summary>
	constexpr Key KeyRAlt{ InputDevice::Keyboard, 0xA5 };

	/// <summary>
	/// メディア 	Next Track ボタン
	/// </summary>
	constexpr Key KeyNextTrack{ InputDevice::Keyboard, 0xB0 };

	/// <summary>
	/// メディア 	Previous Track ボタン
	/// </summary>
	constexpr Key KeyPreviousTrack{ InputDevice::Keyboard, 0xB1 };

	/// <summary>
	/// メディア Stop ボタン
	/// </summary>
	constexpr Key KeyStopMedia{ InputDevice::Keyboard, 0xB2 };

	/// <summary>
	/// メディア Play / Pause ボタン
	/// </summary>
	constexpr Key KeyPlayPauseMedia{ InputDevice::Keyboard, 0xB3 };

	/// <summary>
	/// JP : キー
	/// </summary>
	constexpr Key KeyColon_JP{ InputDevice::Keyboard, 0xBA };

	/// <summary>
	/// US ; キー
	/// </summary>
	constexpr Key KeySemicolon_US{ InputDevice::Keyboard, 0xBA };

	/// <summary>
	/// JP ; キー
	/// </summary>
	constexpr Key KeySemicolon_JP{ InputDevice::Keyboard, 0xBB };

	/// <summary>
	/// US = キー
	/// </summary>
	constexpr Key KeyEqual_US{ InputDevice::Keyboard, 0xBB };

	/// <summary>
	/// , キー
	/// </summary>
	constexpr Key KeyComma{ InputDevice::Keyboard, 0xBC };

	/// <summary>
	/// - キー
	/// </summary>
	constexpr Key KeyMinus{ InputDevice::Keyboard, 0xBD };

	/// <summary>
	/// . キー
	/// </summary>
	constexpr Key KeyPeriod{ InputDevice::Keyboard, 0xBE };

	/// <summary>
	/// / キー
	/// </summary>
	constexpr Key KeySlash{ InputDevice::Keyboard, 0xBF };

	/// <summary>
	/// ` キー
	/// </summary>
	constexpr Key KeyGraveAccent{ InputDevice::Keyboard, 0xC0 };
	
	/// <summary>
	/// Command キー
	/// </summary>
	constexpr Key KeyCommand{ InputDevice::Keyboard, 0xD8 };
	
	/// <summary>
	/// 左 Command キー
	/// </summary>
	constexpr Key KeyLeftCommand{ InputDevice::Keyboard, 0xD9 };
	
	/// <summary>
	/// 右 Command キー
	/// </summary>
	constexpr Key KeyRightCommand{ InputDevice::Keyboard, 0xDA };
	
	/// <summary>
	/// [ キー
	/// </summary>
	constexpr Key KeyLBracket{ InputDevice::Keyboard, 0xDB };

	/// <summary>
	/// JP ￥ キー
	/// </summary>
	constexpr Key KeyYen_JP{ InputDevice::Keyboard, 0xDC };

	/// <summary>
	/// US \ キー
	/// </summary>
	constexpr Key KeyBackslash_US{ InputDevice::Keyboard, 0xDC };

	/// <summary>
	/// ] キー
	/// </summary>
	constexpr Key KeyRBracket{ InputDevice::Keyboard, 0xDD };

	/// <summary>
	/// JP ^ キー
	/// </summary>
	constexpr Key KeyCaret_JP{ InputDevice::Keyboard, 0xDE };

	/// <summary>
	/// US ' キー
	/// </summary>
	constexpr Key KeyApostrophe_US{ InputDevice::Keyboard, 0xDE };

	/// <summary>
	/// JP \ キー
	/// </summary>
	constexpr Key KeyBackslash_JP{ InputDevice::Keyboard, 0xE2 };
}
