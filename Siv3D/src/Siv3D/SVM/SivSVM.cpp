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

# include <Siv3D/SVM.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/MathConstants.hpp>
# include "CSVM.hpp"

namespace s3d
{
	namespace SVM
	{
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
			int32 index, value;

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

		double CalculateAccuracy(const PredictModel& model, const Array<SparseSupportVector>& testData)
		{
			int32 ok = 0, fail = 0;

			for (const auto& sv : testData)
			{
				++(model.predict(sv.vector) == sv.label ? ok : fail);
			}

			return (static_cast<double>(ok) / (ok + fail));
		}

		Problem::Problem()
			: pImpl(std::make_shared<CProblem>())
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
		


		PredictModel::PredictModel()
			: pImpl(std::make_shared<CPredictModel>())
		{

		}

		PredictModel::PredictModel(const FilePath& path)
			: PredictModel()
		{
			pImpl->load(path);
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

		int32 PredictModel::num_classes() const
		{
			return pImpl->num_classes();
		}

		double PredictModel::predict(const Array<double>& vector) const
		{
			return pImpl->predict(vector);
		}

		double PredictModel::predict(const Array<std::pair<int32, double>>& vector) const
		{
			return pImpl->predict(vector);
		}
	}
}
