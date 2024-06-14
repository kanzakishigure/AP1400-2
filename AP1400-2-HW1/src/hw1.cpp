#include "hw1.h"
#include <random>
#include <iomanip>
#include <iostream>
#include <algorithm>
namespace algebra
{
	Matrix zeros(size_t n, size_t m)
	{
		Matrix res = std::vector<std::vector<double>>(n, std::vector<double>(m, 0));

		return res;
	}

	Matrix ones(size_t n, size_t m)
	{
		Matrix res = std::vector<std::vector<double>>(n, std::vector<double>(m, 1));

		return res;
	}

	Matrix random(size_t n, size_t m, double min, double max)
	{

		if (min > max)
		{
			throw std::logic_error("min cannot be greater than max");
		}
		std::mt19937 randomEngine(123);
		std::uniform_real_distribution<double> distribution{ min,max };



		Matrix res = std::vector<std::vector<double>>(n, std::vector<double>(m, 0));
		for (auto& row : res)
		{
			std::for_each(row.begin(), row.end(), [&](double& key) { key = distribution(randomEngine); });
		}

		return res;
	}

	void show(const Matrix& matrix)
	{
		int maxCount = 0;

		//get the cell size
		for (auto& row : matrix)
		{
			for (auto element : row)
			{
				int temp = abs(element);
				int tCount = element < 0 ? 1 : 0;
				while (temp > 1)
				{
					tCount++;
					temp /= 10;
				}
				if (tCount >= maxCount)
				{
					maxCount = tCount;
				}
			}
		}

		// show the title
		for (int i = 0; i < matrix.front().size(); i++)
		{
			for (int j = 0; j < maxCount + 3; j++)
			{
				std::cout << "-";
			}
			std::cout << "--";
		}
		std::cout << std::endl;
		for (auto row : matrix)
		{

			for (auto num : row)
			{
				int numCount = num < 0 ? 1 : 0;
				double tempN = abs(num);
				if (tempN > 0.0f && tempN < 1.0f)
				{
					numCount++;
				}
				while (tempN > 1)
				{
					numCount++;
					tempN = tempN / 10;
				}


				std::cout << "|";
				std::cout << std::string(maxCount - numCount, ' ');
				std::cout << std::fixed << std::setprecision(3) << num;

			}
			std::cout << "|";
			std::cout << std::endl;
		}
		for (int i = 0; i < matrix.front().size(); i++)
		{
			for (int j = 0; j < maxCount + 3; j++)
			{
				std::cout << "-";
			}
			std::cout << "--";
		}
		std::cout << std::endl;

	}

	Matrix multiply(const Matrix& matrix, double c)
	{

		Matrix res = matrix;
		for (auto& row : res)
		{
			for (auto& num : row)
			{
				num = num * c;
			}
		}
		return res;
	}
	Matrix multiply(const Matrix& matrix1, const Matrix& matrix2)
	{
		if (matrix1.empty() || matrix2.empty())
		{
			return Matrix{};
		}
		if (matrix1.front().size() != matrix2.size())
		{
			throw std::logic_error(" Matrix can't be multiply");
		}

		Matrix res = std::vector<std::vector<double>>(matrix1.size(), std::vector<double>(matrix2.front().size(), 0));
		auto vecMultiply = [](std::vector<double> v1, std::vector<double> v2)->double {



			double res = 0;
			for (int index = 0; index < v1.size(); index++)
			{
				res += v1[index] * v2[index];
			}
			return res;
			};
		for (int m = 0; m < matrix1.size(); m++)
		{

			std::vector<double> rowVec = matrix1[m];
			for (int n = 0; n < matrix2.front().size(); n++)
			{
				std::vector<double> colVec(matrix2.size(), 0);
				for (int m2 = 0; m2 < matrix2.size(); m2++)
				{
					colVec[m2] = matrix2[m2][n];
				}
				res[m][n] = vecMultiply(rowVec, colVec);
			}
		}
		return res;
	}

	Matrix sum(const Matrix& matrix, double c)
	{
		Matrix res = matrix;
		for (auto& row : res)
		{
			for (auto& element : row)
			{
				element = element + c;
			}
		}
		return res;
	}

	Matrix sum(const Matrix& matrix1, const Matrix& matrix2)
	{
		if (matrix1.empty() && matrix2.empty())
		{
			return {};
		}
		if (matrix1.size() != matrix2.size() || matrix1.front().size() != matrix2.front().size())
		{
			throw std::logic_error(" matrix can not be sum");
		}
		Matrix res = std::vector<std::vector<double>>(matrix1.size(), std::vector<double>(matrix2.front().size(), 0));

		for (int m = 0; m < matrix1.size(); m++)
		{
			for (int n = 0; n < matrix1.front().size(); n++)
			{
				res[m][n] = matrix1[m][n] + matrix2[m][n];
			}
		}
		return res;
	}
	Matrix transpose(const Matrix& matrix)
	{
		if (matrix.empty())
		{
			return {};
		}
		Matrix res = std::vector<std::vector<double>>(matrix.front().size(), std::vector<double>(matrix.size(), 0));
		for (int m = 0; m < matrix.size(); m++)
		{
			for (int n = 0; n < matrix.front().size(); n++)
			{
				res[n][m] = matrix[m][n];
			}
		}
		return res;
	}

	Matrix minor(const Matrix& matrix, size_t n, size_t m)
	{
		if (matrix.empty())
		{
			return {};
		}
		Matrix res = std::vector<std::vector<double>>(matrix.size() - 1, std::vector<double>(matrix.front().size() - 1, 0));

		std::vector<double> push_element;
		for (int row = 0; row < matrix.size(); row++)
		{
			for (int col = 0; col < matrix.front().size(); col++)
			{
				if (row != n && m != col)
				{
					push_element.push_back(matrix[row][col]);
				}
			}
		}
		auto it = push_element.begin();
		for (auto& row : res)
		{
			for (auto& element : row)
			{
				element = *it;
				it++;
			}
		}
		return res;
	}

	double determinant(const Matrix& matrix)
	{
		if (matrix.empty())
		{
			return 1;
		}
		if (matrix.size() != matrix.front().size())
		{
			throw std::logic_error("matrix cannot be determinant");
		}
		if (matrix.size() < 2)
		{
			return matrix.front().front();
		}
		if (matrix.size() == 2 && matrix.front().size() == 2)
		{
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}

		double res = 0;
		int m = 0;
		//选择按行展开，展开行为第0行
		//实际应该进行优化，选择较快展开行
		for (int n = 0; n < matrix.front().size(); n++)
		{
			res += pow(-1, m + n + 2) * matrix[m][n] * determinant(minor(matrix, m, n));
		}

		return res;
	}
	Matrix inverse(const Matrix& matrix)
	{
		if (matrix.empty())
		{
			return {};
		}
		if (matrix.size() != matrix.front().size())
		{
			throw std::logic_error("matrix cannot be inverse");

		}
		// check matix have inverse matrix;
		if (determinant(matrix) == 0)
		{
			throw std::logic_error("matrix cannot be inverse, because the determinant of matrix is zero");
		}
		Matrix transMatrix = transpose(matrix);
		Matrix res = transMatrix;
		for (int row = 0; row < matrix.size(); row++)
		{
			for (int col = 0; col < matrix.front().size(); col++)
			{
				res[row][col] = pow(-1, row + col + 2) * determinant(minor(transMatrix, row, col));
			}
		}

		return multiply(res, 1.0 / determinant(matrix));
	}
	Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis)
	{
		if (matrix1.empty() && matrix2.empty())
		{
			return {};
		}
		if(matrix1.empty()&&!matrix2.empty())
		{
			return matrix2;
		}
		if (!matrix1.empty() && matrix2.empty())
		{
			return matrix1;
		}
		if (axis == 0||axis==1)
		{
			if (axis == 0 && matrix1.front().size() != matrix2.front().size())
			{
				throw std::logic_error("axis fail ,must have the same col num");
			}
			if (axis == 1 && matrix1.size() != matrix2.size())
			{
				throw std::logic_error("axis fail ,must have the same row num");
			}
		}
		else
		{
			throw std::logic_error("error axis");
		}

		Matrix res = matrix1;
		switch (axis)
		{
		case 0:
		{
			res.insert(res.end(), matrix2.begin(), matrix2.end());
		}
			break;
		case 1:
		{
			int index = 0;
			for (auto& row : res)
			{
				row.insert(row.end(), matrix2[index].begin(), matrix2[index].end());
				index++;
			}
		}
			break;
		}
		return res;
	}

	Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2)
	{
		if (!(r1 < matrix.size() && r2 < matrix.size()))
		{
			throw std::logic_error("invalid index");
		}
		Matrix res = matrix;
		std::vector<double>& row1 = res[r1];
		std::vector<double>& row2 = res[r2];
		row1.swap(row2);
		return res;
	}

	Matrix ero_multiply(const Matrix& matrix, size_t r, double c)
	{
		if( !(r<matrix.size()))
		{
			throw  std::logic_error("invalid index");
		}
		Matrix res = matrix;
		std::for_each(res[r].begin(), res[r].end(),[=](double& element ){
			element = element*c;
		});
		
		return res;
	}

	Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2)
	{
		
		if( !(r1<matrix.size()&& r2 < matrix.size()))
		{
			throw  std::logic_error("invalid index");
		}
		Matrix res = matrix;
		std::vector<double> vector = res[r1];
		std::for_each(vector.begin(), vector.end(),[=](double& element ){
			element = element*c;
		});
		
		auto it = vector.begin();
		std::for_each(res[r2].begin(), res[r2].end(), [&](double& element) {
			element = element + *it;
			it++;
			});
		return res;
		 
	}

	Matrix upper_triangular(const Matrix& matrix)
	{
		if(matrix.empty())
		{
			return {};
		}
		if (matrix.size() != matrix.front().size())
		{
			throw  std::logic_error("non-square matrices");
		}
		Matrix res = matrix;
		
		int index = 0;
		
		
		for(int n = 0; n<res.front().size(); n++)
		{
			if (index >= res.size())
			{
				break;
			}
			//check the col value is zero?
			if(res[index][n]==0)
			{
				int row = index+1;
				while (row < res.size())
				{
					if (res[row][n] != 0)
					{
						res = ero_swap(res, index, row);
						break;
					}
				}
			}
			
			
			for(int m = index+1;m<res.size();m++)
			{
				if (res[index][n] == 0)
				{
					continue;
				}
				double devied = -1.0f*res[m][n]/res[index][n];
				res = ero_sum(res,index,devied,m);
				
			}
			index++;
			
		}
		
		return res;
	}

	

}