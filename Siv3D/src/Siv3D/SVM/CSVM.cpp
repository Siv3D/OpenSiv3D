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

# define _CRT_SECURE_NO_WARNINGS
# include "CSVM.hpp"
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		static bool ExitInputError(int32 lineNumber)
		{
			LOG_FAIL(U"Wrong input format at line {}"_fmt(lineNumber));

			return false;
		}
	}

	namespace SVM
	{
		Problem::CProblem::CProblem()
		{

		}

		Problem::CProblem::~CProblem()
		{
			release();
		}

		bool Problem::CProblem::load(const double* pSupportVectors, const size_t num_dataset, const size_t dimensions)
		{
			m_problem.l = static_cast<int32>(num_dataset);
			m_problem.y = new double[num_dataset];
			m_problem.x = new svm_node*[num_dataset];
			m_nodes.resize((dimensions + 1) * num_dataset);

			const size_t stride = (dimensions + 1);

			for (int32 i = 0; i < num_dataset; ++i)
			{
				m_problem.y[i] = pSupportVectors[0];

				const size_t indexOffset = (dimensions + 1) * i;

				for (int32 k = 0; k < dimensions; ++k)
				{
					m_nodes[indexOffset + k].index = (k + 1);
					m_nodes[indexOffset + k].value = pSupportVectors[k + 1];
				}

				m_nodes[indexOffset + dimensions].index = -1;
				m_problem.x[i] = &m_nodes[indexOffset];

				pSupportVectors += stride;
			}

			m_maxIndex = static_cast<int32>(dimensions);
			m_hasData = true;

			return true;
		}

		bool Problem::CProblem::load(const Array<SparseSupportVector>& supportVectors)
		{
			const size_t num_dataset = supportVectors.size();
			size_t num_elements = 0;
			int32 maxIndex = 0;

			for (const auto& supportVector : supportVectors)
			{
				num_elements += supportVector.vector.size() + 1;

				maxIndex = std::max(maxIndex, supportVector.vector.back().first);
			}

			m_problem.l = static_cast<int32>(num_dataset);
			m_problem.y = new double[num_dataset];
			m_problem.x = new svm_node*[num_dataset];
			m_nodes.resize(num_elements * num_dataset);

			size_t indexOffset = 0;

			for (int32 i = 0; i < num_dataset; ++i)
			{
				m_problem.y[i] = supportVectors[i].label;

				const size_t num_elements_vector = supportVectors[i].vector.size();

				for (int32 k = 0; k < num_elements_vector; ++k)
				{
					m_nodes[indexOffset + k].index = supportVectors[i].vector[k].first;
					m_nodes[indexOffset + k].value = supportVectors[i].vector[k].second;
				}

				m_nodes[indexOffset + num_elements_vector].index = -1;
				m_problem.x[i] = &m_nodes[indexOffset];

				indexOffset += (num_elements_vector + 1);
			}

			m_maxIndex = maxIndex;
			m_hasData = true;

			return true;
		}

		bool Problem::CProblem::load(const FilePath& path)
		{
			int max_index, inst_max_index, i;
			size_t elements, j;
			FILE *fp = fopen(path.narrow().c_str(), "r");
			char *endptr;
			char *idx, *val, *label;

			if (fp == NULL)
			{
				LOG_FAIL(U"Could not open `{}`"_fmt(path));

				return false;
			}

			m_problem.l = 0;
			elements = 0;

			m_max_line_len = 1024;
			m_line = (char*)::malloc(m_max_line_len);
			while (readline(fp) != NULL)
			{
				char *p = strtok(m_line, " \t"); // label

											   // features
				while (1)
				{
					p = strtok(NULL, " \t");
					if (p == NULL || *p == '\n') // check '\n' as ' ' may be after the last feature
						break;
					++elements;
				}
				++elements;
				++m_problem.l;
			}
			rewind(fp);

			m_problem.y = new double[m_problem.l];
			m_problem.x = new svm_node*[m_problem.l];
			m_nodes.resize(elements);

			max_index = 0;
			j = 0;
			for (i = 0; i<m_problem.l; i++)
			{
				inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0
				readline(fp);
				m_problem.x[i] = &m_nodes[j];
				label = strtok(m_line, " \t\n");

				if (label == NULL) // empty line
				{
					return detail::ExitInputError(i + 1);
				}

				m_problem.y[i] = strtod(label, &endptr);
				if (endptr == label || *endptr != '\0')
				{
					return detail::ExitInputError(i + 1);
				}

				while (1)
				{
					idx = strtok(NULL, ":");
					val = strtok(NULL, " \t");

					if (val == NULL)
						break;

					errno = 0;
					m_nodes[j].index = (int)strtol(idx, &endptr, 10);
					if (endptr == idx || errno != 0 || *endptr != '\0' || m_nodes[j].index <= inst_max_index)
					{
						return detail::ExitInputError(i + 1);
					}
					else
						inst_max_index = m_nodes[j].index;

					errno = 0;
					m_nodes[j].value = strtod(val, &endptr);
					if (endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
					{
						return detail::ExitInputError(i + 1);
					}

					++j;
				}

				if (inst_max_index > max_index)
					max_index = inst_max_index;
				m_nodes[j++].index = -1;
			}

			fclose(fp);

			m_maxIndex = max_index;
			m_hasData = true;

			return true;
		}

		void Problem::CProblem::release()
		{
			if (!m_hasData)
			{
				return;
			}

			m_max_line_len = 0;
			free(m_line);
			delete[] m_problem.y;
			delete[] m_problem.x;

			m_line = nullptr;
			m_problem.y = nullptr;
			m_problem.x = nullptr;

			m_maxIndex = 0;
			m_problem.l = 0;
			m_nodes.release();

			m_hasData = false;
		}

		bool Problem::CProblem::hasData() const
		{
			return m_hasData;
		}

		size_t Problem::CProblem::num_SVs() const
		{
			return m_problem.l;
		}

		int32 Problem::CProblem::getMaxIndex() const
		{
			return m_maxIndex;
		}

		bool Problem::CProblem::trainAndSaveModel(const FilePath& path, const Paramter& param) const
		{
			if (!m_hasData)
			{
				return false;
			}

			svm_model* model = svm_train(&m_problem, &param);

			const FilePath parentFilePath = FileSystem::ParentPath(path);

			if (!FileSystem::Exists(parentFilePath) && !FileSystem::CreateDirectories(parentFilePath))
			{
				return false;
			}

			const int32 result = svm_save_model(path.narrow().c_str(), model);

			svm_free_and_destroy_model(&model);

			return (result == 0);
		}

		PredictModel Problem::CProblem::trainAndCreateModel(const Paramter& param) const
		{
			if (!m_hasData)
			{
				return PredictModel();
			}

			return PredictModel(std::make_unique<svm_model*>(svm_train(&m_problem, &param)));
		}

		char* Problem::CProblem::readline(FILE *input)
		{
			int len;

			if (fgets(m_line, m_max_line_len, input) == NULL)
				return NULL;

			while (strrchr(m_line, '\n') == NULL)
			{
				m_max_line_len *= 2;
				m_line = (char*)realloc(m_line, m_max_line_len);
				len = (int)strlen(m_line);
				if (fgets(m_line + len, m_max_line_len - len, input) == NULL)
					break;
			}
			return m_line;
		}





		PredictModel::CPredictModel::CPredictModel()
		{

		}

		PredictModel::CPredictModel::~CPredictModel()
		{
			release();
		}

		bool PredictModel::CPredictModel::hasData() const
		{
			return (m_model != nullptr);
		}

		bool PredictModel::CPredictModel::load(const FilePath& path)
		{
			if (m_model)
			{
				release();
			}

			m_model = svm_load_model(path.narrow().c_str());

			return (m_model != nullptr);
		}

		bool PredictModel::CPredictModel::set(std::unique_ptr<svm_model*>&& ppModel)
		{
			if (m_model)
			{
				release();
			}

			m_model = *ppModel;

			return (m_model != nullptr);
		}

		void PredictModel::CPredictModel::release()
		{
			if (!m_model)
			{
				return;
			}

			svm_free_and_destroy_model(&m_model);

			m_model = nullptr;
		}

		size_t PredictModel::CPredictModel::num_classes() const
		{
			if (!m_model)
			{
				return 0;
			}

			return m_model->nr_class;
		}

		Array<int32> PredictModel::CPredictModel::getLabels() const
		{
			if (!m_model || !m_model->label)
			{
				return Array<int32>();
			}

			return Array<int32>(m_model->label, m_model->label + m_model->nr_class);
		}

		Label PredictModel::CPredictModel::predict(const Array<double>& vector) const
		{
			if (!m_model)
			{
				return Math::NaN;
			}

			Array<svm_node> node(vector.size() + 1);

			for (int32 i = 0; i < vector.size(); ++i)
			{
				node[i].index = i + 1;

				node[i].value = vector[i];
			}

			node.back().index = -1;

			return svm_predict(m_model, node.data());
		}

		Label PredictModel::CPredictModel::predict(const Array<std::pair<int32, double>>& vector) const
		{
			if (!m_model)
			{
				return Math::NaN;
			}

			Array<svm_node> node(vector.size() + 1);

			for (int32 i = 0; i < vector.size(); ++i)
			{
				node[i].index = vector[i].first;

				node[i].value = vector[i].second;
			}

			node.back().index = -1;

			return svm_predict(m_model, node.data());
		}

		Label PredictModel::CPredictModel::predictProbability(const Array<double>& vector, Array<double>& probabilities) const
		{
			if (!m_model)
			{
				probabilities.clear();

				return Math::NaN;
			}

			Array<svm_node> node(vector.size() + 1);

			for (int32 i = 0; i < vector.size(); ++i)
			{
				node[i].index = i + 1;

				node[i].value = vector[i];
			}

			node.back().index = -1;

			probabilities.resize(m_model->nr_class);

			return svm_predict_probability(m_model, node.data(), probabilities.data());
		}

		Label PredictModel::CPredictModel::predictProbability(const Array<std::pair<int32, double>>& vector, Array<double>& probabilities) const
		{
			if (!m_model)
			{
				probabilities.clear();

				return Math::NaN;
			}

			Array<svm_node> node(vector.size() + 1);

			for (int32 i = 0; i < vector.size(); ++i)
			{
				node[i].index = vector[i].first;

				node[i].value = vector[i].second;
			}

			node.back().index = -1;

			probabilities.resize(m_model->nr_class, 3);

			return svm_predict_probability(m_model, node.data(), probabilities.data());
		}
	}
}
