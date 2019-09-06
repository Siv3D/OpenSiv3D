# include <Siv3D.hpp> // OpenSiv3D v0.4.1

// 定数バッファ (PS_1)
struct PoissonDisk
{
	// 1 ピクセルあたりの UV サイズ
	Float2 pixelSize;

	// サンプリング半径
	float diskRadius;

	// 定数バッファのサイズを
	// 16 の倍数にするためのパディング用の値
	float _unused = 0.0f;
};

void Main()
{
	// シーンの背景色を淡い水色に設定
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Texture windmill(U"example/windmill.png");

	// Poisson-Disc Sampling 用のピクセルシェーダ
	// シェーダファイルの拡張子は、Windows では hlsl, macOS/Linux では frag を選択
	// {} 内は定数バッファの名前と、対応する定数インデックス
	const PixelShader ps(U"example/shader/poisson_disk" SIV3D_SELECT_SHADER(U".hlsl", U".frag"),
		{ { U"PSConstants2D", 0 }, { U"PoissonDisk", 1 } });

	// 定数バッファ
	ConstantBuffer<PoissonDisk> cb;
	cb->pixelSize = Float2(1.0, 1.0) / windmill.size();

	// サンプリング半径
	double diskRadius = 0.0;

	while (System::Update())
	{
		// サンプリング半径をスライダーで変更
		SimpleGUI::Slider(U"diskRadius", diskRadius, 0.0, 8.0, Vec2(10, 340), 120, 200);

		cb->diskRadius = static_cast<float>(diskRadius);

		{
			// 定数バッファを設定
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

			// Poisson-Disc Sampling 用のシェーダを開始
			ScopedCustomShader2D shader(ps);
			windmill.draw(10, 10);
		}
	}
}
