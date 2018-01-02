//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/SVM.hpp>

namespace s3d
{
	namespace SVM
	{
		class Problem::CProblem
		{
		private:

			svm_problem m_problem = { 0, nullptr, nullptr };

			int32 m_maxIndex = 0;

			Array<svm_node> m_nodes;

			bool m_hasData = false;

			char* m_line = nullptr;

			int32 m_max_line_len = 0;

			char* readline(FILE *input);

		public:

			CProblem();

			~CProblem();

			bool load(const double* pSupportVectors, size_t num_dataset, size_t dimensions);

			bool load(const Array<SparseSupportVector>& supportVectors);

			bool load(const FilePath& path);

			void release();

			bool hasData() const;

			size_t num_SVs() const;

			int32 getMaxIndex() const;

			bool trainAndSaveModel(const FilePath& path, const Paramter& param) const;
		};

		class PredictModel::CPredictModel
		{
		private:

			svm_model* m_model = nullptr;

		public:

			CPredictModel();

			~CPredictModel();

			bool hasData() const;

			bool load(const FilePath& path);

			void release();

			int32 num_classes() const;

			double predict(const Array<double>& vector) const;

			double predict(const Array<std::pair<int32, double>>& vector) const;
		};
	}
}
