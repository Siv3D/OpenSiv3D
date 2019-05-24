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

# include <Siv3D/SVM.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/MathConstants.hpp>
# include "CSVM.hpp"

namespace s3d
{
	namespace SVM
	{
		Paramter DefaultParameter(const size_t maxIndex)
		{
			Paramter param;
			param.svm_type		= C_SVC;
			param.kernel_type	= RBF;
			param.degree		= 3;
			param.gamma			= 1.0 / maxIndex;
			param.coef0			= 0;
			param.nu			= 0.5;
			param.cache_size	= 100;
			param.C				= 1;
			param.eps			= 1e-3;
			param.p				= 0.1;
			param.shrinking		= 1;
			param.probability	= 0;
			param.nr_weight		= 0;
			param.weight_label	= nullptr;
			param.weight		= nullptr;

			return param;
		}

		Problem::Problem()
			: pImpl(std::make_shared<ProblemDetail>())
		{

		}

		Problem::Problem(const double* pSupportVectors, const size_t num_dataset, const size_t dimensions)
			: Problem()
		{
			load(pSupportVectors, num_dataset, dimensions);
		}

		Problem::Problem(const Array<SparseSupportVector>& supportVectors)
			: Problem()
		{
			load(supportVectors);
		}

		Problem::Problem(const FilePath& path)
			: Problem()
		{
			load(path);
		}

		Problem::~Problem()
		{

		}

		bool Problem::load(const double* pSupportVectors, const size_t num_dataset, const size_t dimensions)
		{
			release();

			if (num_dataset == 0)
			{
				return false;
			}

			return pImpl->load(pSupportVectors, num_dataset, dimensions);
		}

		bool Problem::load(const Array<SparseSupportVector>& supportVectors)
		{
			release();

			if (supportVectors.isEmpty())
			{
				return false;
			}

			return pImpl->load(supportVectors);
		}

		bool Problem::load(const FilePath& path)
		{
			release();

			return pImpl->load(path);
		}

		void Problem::release()
		{
			pImpl->release();
		}

		Problem::operator bool() const
		{
			return pImpl->hasData();
		}

		bool Problem::hasData() const
		{
			return pImpl->hasData();
		}

		size_t Problem::num_SVs() const
		{
			return pImpl->num_SVs();
		}

		int32 Problem::getMaxIndex() const
		{
			return pImpl->getMaxIndex();
		}

		bool Problem::trainAndSaveModel(const FilePath& path, const Paramter& param) const
		{
			return pImpl->trainAndSaveModel(path, param);
		}
		
		PredictModel Problem::trainAndCreateModel(const Paramter& param) const
		{
			return pImpl->trainAndCreateModel(param);
		}


		PredictModel::PredictModel()
			: pImpl(std::make_shared<PredictModelDetail>())
		{

		}

		PredictModel::PredictModel(const FilePath& path)
			: PredictModel()
		{
			pImpl->load(path);
		}

		PredictModel::PredictModel(std::unique_ptr<svm_model*>&& ppModel)
			: PredictModel()
		{
			pImpl->set(std::move(ppModel));
		}

		PredictModel::~PredictModel()
		{

		}

		PredictModel::operator bool() const
		{
			return pImpl->hasData();
		}

		bool PredictModel::hasData() const
		{
			return pImpl->hasData();
		}

		bool PredictModel::load(const FilePath& path)
		{
			return pImpl->load(path);
		}

		void PredictModel::release()
		{
			pImpl->release();
		}

		size_t PredictModel::num_classes() const
		{
			return pImpl->num_classes();
		}

		Array<int32> PredictModel::getLabels() const
		{
			return pImpl->getLabels();
		}

		double PredictModel::predict(const Array<double>& vector) const
		{
			return pImpl->predict(vector);
		}

		double PredictModel::predict(const Array<std::pair<int32, double>>& vector) const
		{
			return pImpl->predict(vector);
		}

		Label PredictModel::predictProbability(const Array<double>& vector, Array<double>& probabilities) const
		{
			return pImpl->predictProbability(vector, probabilities);
		}

		double PredictModel::predictProbability(const Array<std::pair<int32, double>>& vector, Array<double>& probabilities) const
		{
			return pImpl->predictProbability(vector, probabilities);
		}




		SparseSupportVector ParseSVMLight(StringView view)
		{
			std::istringstream is(Unicode::NarrowAscii(view));

			SparseSupportVector result;

			if (double label; is >> label)
			{
				result.label = label;
			}
			else
			{
				result.label = Math::NaN;

				return result;
			}

			char unused;
			int32 index;
			double value;

			while (is >> index >> unused >> value)
			{
				result.vector.emplace_back(index, value);
			}

			return result;
		}

		Array<SparseSupportVector> LoadSVMLight(const FilePath& path)
		{
			Array<SVM::SparseSupportVector> results;

			TextReader reader(path);

			String line;

			while (reader.readLine(line))
			{
				results << ParseSVMLight(line);
			}

			return results;
		}

		bool SaveSVMLight(const FilePath& path, const Array<SparseSupportVector>& vector)
		{
			TextWriter writer(path, TextEncoding::UTF8_NO_BOM);

			if (!writer)
			{
				return false;
			}

			for (const auto& v : vector)
			{
				writer.writeln(Format(v));
			}

			return true;
		}

		double CalculateAccuracy(const PredictModel& model, const Array<SparseSupportVector>& testData)
		{
			int32 ok = 0, fail = 0;

			for (const auto& sv : testData)
			{
				++(model.predict(sv.vector) == sv.label ? ok : fail);
			}

			return (static_cast<double>(ok) / (ok + fail));
		}
	}

	void Formatter(FormatData& formatData, const SVM::SparseSupportVector& value)
	{
		formatData.string.append(ToString(value.label));
		
		for (const auto& elem : value.vector)
		{
			formatData.string.push_back(U' ');

			formatData.string.append(ToString(elem.first));

			formatData.string.push_back(U':');

			formatData.string.append(ToString(elem.second));
		}
	}
}
