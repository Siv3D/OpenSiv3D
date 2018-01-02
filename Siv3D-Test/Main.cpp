# include <Siv3D.hpp>

void Main()
{
	const SVM::Problem problem(U"example/a1a");	// 訓練データをロード
	
	const SVM::Paramter param = SVM::DefaultParameter(problem.getMaxIndex()); // パラメータ

	problem.trainAndSaveModel(U"a1a.model.txt", param); // 学習 & モデルを保存
	
	const SVM::PredictModel model(U"a1a.model.txt"); // 予測モデルのロード

	// テストデータの読み込み
	TextReader reader(U"example/a1a.t");
	String line;
	int32 ok = 0, fail = 0;

	while (reader.readLine(line))
	{
		const auto sv = SVM::ParseSVMLight(line);
		++(model.predict(sv.vector) == sv.label ? ok : fail);
	}

	Print << U"識別率: {:.1f} % ({} vs {})"_fmt(100.0 * ok / (ok + fail), ok, fail);

	while (System::Update())
	{

	}
}