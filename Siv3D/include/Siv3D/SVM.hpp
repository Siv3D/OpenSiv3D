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

# pragma once
# include <array>
# include "Fwd.hpp"
# include "String.hpp"
# include "Array.hpp"
# include <ThirdParty/libsvm/svm.h>

namespace s3d
{
	namespace SVM
	{
		using Paramter = svm_parameter;

		using Label = double;

		Paramter DefaultParameter(size_t maxIndex);

		template <size_t _Dimensions>
		struct SupportVector
		{
			static constexpr int32 Dimensions = _Dimensions;

			Label label;

			std::array<double, Dimensions> vector;
		};

		struct SparseSupportVector
		{
			Label label;

			Array<std::pair<int32, double>> vector;
		};

		class Problem
		{
		private:

			class ProblemDetail;

			std::shared_ptr<ProblemDetail> pImpl;

		public:

			Problem();

			template <size_t Dimensions>
			Problem(const Array<SupportVector<Dimensions>>& supportVectors)
				: Problem()
			{
				load(supportVectors);
			}

			Problem(const double* pSupportVectors, size_t num_dataset, size_t dimensions);

			Problem(const Array<SparseSupportVector>& supportVectors);

			Problem(const FilePath& path);

			~Problem();

			template <size_t Dimensions>
			bool load(const Array<SupportVector<Dimensions>>& supportVectors)
			{
				release();

				if (supportVectors.isEmpty())
				{
					return false;
				}

				return load(&supportVectors[0].label, supportVectors.size(), Dimensions);
			}

			bool load(const double* pSupportVectors, size_t num_dataset, size_t dimensions);

			bool load(const Array<SparseSupportVector>& supportVectors);

			bool load(const FilePath& path);

			void release();

			[[nodiscard]] explicit operator bool() const;

			[[nodiscard]] bool hasData() const;

			[[nodiscard]] size_t num_SVs() const;

			[[nodiscard]] int32 getMaxIndex() const;

			bool trainAndSaveModel(const FilePath& path, const Paramter& param) const;

			[[nodiscard]] PredictModel trainAndCreateModel(const Paramter& param) const;
		};

		class PredictModel
		{
		private:

			class PredictModelDetail;

			std::shared_ptr<PredictModelDetail> pImpl;

		public:

			PredictModel();

			PredictModel(const FilePath& path);

			PredictModel(std::unique_ptr<svm_model*>&& ppModel);

			~PredictModel();

			[[nodiscard]] explicit operator bool() const;

			[[nodiscard]] bool hasData() const;

			bool load(const FilePath& path);

			void release();

			[[nodiscard]] size_t num_classes() const;

			[[nodiscard]] Array<int32> getLabels() const;

			[[nodiscard]] Label predict(const Array<double>& vector) const;

			[[nodiscard]] Label predict(const Array<std::pair<int32, double>>& vector) const;

			[[nodiscard]] Label predictProbability(const Array<double>& vector, Array<double>& probabilities) const;

			[[nodiscard]] Label predictProbability(const Array<std::pair<int32, double>>& vector, Array<double>& probabilities) const;
		};

		[[nodiscard]] SparseSupportVector ParseSVMLight(StringView view);

		[[nodiscard]] Array<SparseSupportVector> LoadSVMLight(const FilePath& path);

		bool SaveSVMLight(const FilePath& path, const Array<SparseSupportVector>& vector);

		[[nodiscard]] double CalculateAccuracy(const PredictModel& model, const Array<SparseSupportVector>& testData);
	}

	void Formatter(FormatData& formatData, const SVM::SparseSupportVector& value);
}
