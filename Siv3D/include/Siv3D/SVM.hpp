//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <array>
# include "Fwd.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "MathConstants.hpp"

S3D_DISABLE_MSVC_WARNINGS_PUSH(4458)
# include "../ThirdParty/libsvm/svm.h"
S3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace SVM
	{
		template <size_t _Dimensions>
		struct SupportVector
		{
			static constexpr int32 Dimensions = _Dimensions;

			double label;

			std::array<double, Dimensions> vector;
		};

		class Problem
		{
		private:

			svm_problem m_problem = { 0, nullptr, nullptr };

			Array<svm_node> m_nodes;

			bool m_hasData = false;

		public:

			Problem() = default;

			template <size_t D>
			Problem(const Array<SupportVector<D>>& supportVectors)
			{
				load(supportVectors);
			}

			~Problem()
			{
				release();
			}

			template <size_t Dimensions>
			bool load(const Array<SupportVector<Dimensions>>& supportVectors)
			{
				if (m_hasData)
				{
					release();
				}

				if (supportVectors.isEmpty())
				{
					return false;
				}

				const size_t num_dataset = static_cast<int32>(supportVectors.size());

				m_problem.l = static_cast<int32>(num_dataset);
				m_problem.y = new double[num_dataset];
				m_problem.x = new svm_node*[num_dataset];
				m_nodes.resize((Dimensions + 1) * num_dataset);

				for (int32 i = 0; i < num_dataset; ++i)
				{
					m_problem.y[i] = supportVectors[i].label;

					const size_t indexOffset = (Dimensions + 1) * i;

					for (int32 k = 0; k < Dimensions; ++k)
					{
						m_nodes[indexOffset + k].index = (k + 1);
						m_nodes[indexOffset + k].value = supportVectors[i].vector[k];
					}

					m_nodes[indexOffset + Dimensions].index = -1;
					m_problem.x[i] = &m_nodes[indexOffset];
				}

				m_hasData = true;

				return true;
			}

			void release()
			{
				if (!m_hasData)
				{
					return;
				}

				delete[] m_problem.y;
				delete[] m_problem.x;

				m_problem.l = 0;
				m_nodes.release();

				m_hasData = false;
			}

			explicit operator bool() const
			{
				return m_hasData;
			}

			bool hasData() const
			{
				return m_hasData;
			}

			bool saveModel(const FilePath& path, const svm_parameter& param) const
			{
				if (!m_hasData)
				{
					return false;
				}

				svm_model* model = svm_train(&m_problem, &param);

				const int32 result = svm_save_model(path.narrow().c_str(), model);

				svm_free_and_destroy_model(&model);

				return (result == 0);
			}
		};

		class PredictModel
		{
		private:

			svm_model * m_model = nullptr;

		public:

			PredictModel() = default;

			PredictModel(const FilePath& path)
			{
				load(path);
			}

			~PredictModel()
			{
				release();
			}

			explicit operator bool() const
			{
				return (m_model != nullptr);
			}

			bool load(const FilePath& path)
			{
				if (m_model)
				{
					release();
				}

				m_model = svm_load_model(path.narrow().c_str());

				return (m_model != nullptr);
			}

			void release()
			{
				if (!m_model)
				{
					return;
				}

				svm_free_and_destroy_model(&m_model);

				m_model = nullptr;
			}

			int32 num_classes() const
			{
				if (!m_model)
				{
					return 0;
				}

				return m_model->nr_class;
			}

			double predict(const Array<double>& vector) const
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
		};
	}
}
