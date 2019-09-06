# include <Siv3D.hpp> // OpenSiv3D v0.4.1

// 定数バッファ (PS_1)
struct GameOfLife
{
	Float2 pixelSize;
	Float2 _unused = {};
};

void Main()
{
	// ウィンドウを 1280x720 にリサイズ
	Window::Resize(1280, 720);
	
	// セルの数 (1280x720)
	constexpr Size FieldSize(1280, 720);
	
	// ライフゲーム用のピクセルシェーダ
	// シェーダファイルの拡張子は、Windows では hlsl, macOS/Linux では frag を選択
	// {} 内は定数バッファの名前と、対応する定数インデックス
	const PixelShader ps(U"example/shader/game_of_life" SIV3D_SELECT_SHADER(U".hlsl", U".frag"),
						 { { U"PSConstants2D", 0 }, { U"GameOfLife", 1 } });
	
	// 定数バッファ
	const ConstantBuffer<GameOfLife> cb({ Float2(1.0f, 1.0f) / FieldSize });
	
	// レンダーテクスチャ 1
	RenderTexture rt0(Image(FieldSize, Arg::generator = [](){ return Color(RandomBool() * 255); }));
	
	// レンダーテクスチャ 2
	RenderTexture rt1(FieldSize, ColorF(0.0));
	
	while (System::Update())
	{
		{
			// テクスチャフィルタなし
			ScopedRenderStates2D sampler(SamplerState::ClampNearest);
			
			// 現在の状態を画面に描く
			rt0.draw(ColorF(0.0, 1.0, 0.0));
			
			{
				// ライフゲーム用のシェーダ
				Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);
				ScopedCustomShader2D shader(ps);
				
				// 更新後の状態を描く rt1 に描く
				ScopedRenderTarget2D target(rt1);
				rt0.draw();
			}
		}
		
		// rt0 と rt1 を入れ替える
		std::swap(rt0, rt1);
	}
}
