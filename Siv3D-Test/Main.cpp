# include <Siv3D.hpp>

void Main()
{
	{
		constexpr int32 Dimensions = 7;

		const Array<SVM::SupportVector<Dimensions>> supportVectors =
		{
			{ 1,{ 0.92,0.97,0.11,0.01,0.12,0.11,0.09 } },
			{ 1,{ 0.91,0.99,0.21,0.02,0.09,0.12,0.09 } },
			{ 1,{ 0.90,0.90,0.22,0.01,0.10,0.13,0.10 } },
			{ 2,{ 0.12,0.21,0.32,0.12,0.99,0.11,0.91 } },
			{ 2,{ 0.13,0.11,0.22,0.13,0.98,0.12,0.90 } },
			{ 2,{ 0.12,0.24,0.11,0.14,0.89,0.13,0.91 } },
			{ 3,{ 0.13,0.31,0.82,0.12,0.89,0.11,0.10 } },
			{ 3,{ 0.12,0.23,0.89,0.10,0.92,0.12,0.11 } },
			{ 3,{ 0.11,0.11,0.87,0.01,0.93,0.13,0.12 } },
			{ 3,{ 0.10,0.12,0.81,0.12,0.97,0.11,0.12 } },
		};

		svm_parameter param;
		param.svm_type = C_SVC;
		param.kernel_type = RBF;
		param.degree = 3;
		param.gamma = 1.0 / Dimensions;
		param.coef0 = 0;
		param.nu = 0.5;
		param.cache_size = 100;
		param.C = 1;
		param.eps = 1e-3;
		param.p = 0.1;
		param.shrinking = 1;
		param.probability = 0;
		param.nr_weight = 0;
		param.weight_label = nullptr;
		param.weight = nullptr;

		const SVM::Problem problem(supportVectors);

		problem.saveModel(U"model.txt", param);

		svm_destroy_param(&param);
	}

	{
		const SVM::PredictModel model(U"model.txt");

		const Array<double> vector = { 0.91,0.99,0.21,0.12,0.89,0.11,0.14 };

		Print << model.predict(vector);

		Print << MD5::FromFile(U"model.txt").asString().substr(0, 6);
	}

	while (System::Update())
	{

	}
}
