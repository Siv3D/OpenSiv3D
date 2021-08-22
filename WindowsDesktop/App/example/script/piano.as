
void Main()
{
	// 白鍵の大きさ
	const Point keySize(55, 400);

	// 楽器の種類
	const GMInstrument instrument = GMInstrument::Piano1;

	// ウインドウをリサイズ
	Window::Resize(12 * keySize.x, keySize.y);

	// 鍵盤の数
	const int32 NumKeys = 20;

	// 音を作成
	Array<Audio> sounds;
	for (int32 i = 0; i < NumKeys; ++i)
	{
		sounds << Audio(instrument, (PianoKey::A3 + i), _s(0.5));
	}

	// 対応するキー
	const Array<Input> keys =
	{
		KeyTab, Key1, KeyQ,
		KeyW, Key3, KeyE, Key4, KeyR, KeyT, Key6, KeyY, Key7, KeyU, Key8, KeyI,
		KeyO, Key0, KeyP, KeyMinus, KeyEnter,
	};

	// 描画位置計算用のオフセット値
	const Array<int32> keyPositions =
	{
		0, 1, 2, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22
	};

	while (System::Update())
	{
		// キーが押されたら対応する音を再生
		for (int32 i = 0; i < NumKeys; ++i)
		{
			if (keys[i].down())
			{
				sounds[i].playOneShot(0, 0.5);
			}
		}

		// 白鍵を描画
		for (int32 i = 0; i < NumKeys; ++i)
		{
			// オフセット値が偶数
			if (IsEven(keyPositions[i]))
			{
				RectF(keyPositions[i] / 2 * keySize.x, 0, keySize.x, keySize.y)
					.stretched(-1).draw(keys[i].pressed() ? Palette::Pink : Palette::White);
			}
		}

		// 黒鍵を描画
		for (int32 i = 0; i < NumKeys; ++i)
		{
			// オフセット値が奇数
			if (IsOdd(keyPositions[i]))
			{
				RectF(keySize.x * 0.68 + keyPositions[i] / 2 * keySize.x, 0, keySize.x * 0.58, keySize.y * 0.62)
					.draw(keys[i].pressed() ? Palette::Pink : Color(24));
			}
		}
	}
}
