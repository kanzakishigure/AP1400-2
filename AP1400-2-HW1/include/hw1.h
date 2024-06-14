#ifndef AP_HW1_H
#define AP_HW1_H
#include <vector>


namespace algebra
{
    
    using Matrix = std::vector<std::vector<double>>;

    //zeros implement this function so that it will create a n x m matrix with all elements equal to zero.
    Matrix zeros(std::size_t n, std::size_t m);
    
    //ones implement this function so that it will create a n x m matrix with all elements equal to one.
    Matrix ones(std::size_t n, std::size_t m);

    //random implement this function so that it will create a n x m matrix with all elements a random number between min and max.
    Matrix random(std::size_t n, std::size_t m, double min, double max);
    
    //show implement this function so that it will display the matrix in a beautiful way.
    void show(const Matrix& matrix);
    
    //implement this function so that it multiplies the matrix into the constant scalar c.
    Matrix multiply(const Matrix& matrix, double c);
    
    //implement this function so that it multiplies the matrix1 into matrix2. (this is not an element-wise multiplication)
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);

    //implement this function so that it adds the constant number c to every element of matrix.
    Matrix sum(const Matrix& matrix, double c);
    
    //implement this function so that it adds 2 matrices to each other.
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2);

    //transpose implement this function so that it will generate the transpose matrix of the input matrix.
    Matrix transpose(const Matrix& matrix);

    //implement this function so that it will create the minor of the input matrix with respect to nth row and mth column.
    Matrix minor(const Matrix& matrix, std::size_t n, std::size_t m);

    //determinant implement this function so that it calculates the determinant of the input matrix.
    double determinant(const Matrix& matrix);

    //inverse implement this function so that it generates the matrix's inverse.
    Matrix inverse(const Matrix& matrix);

    //concatenate implement this function so that it will concatenate matrix1 and matrix2 along the specified axis. (axis=0: on top of each other | axis=1: alongside each other).
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0);

    //swap swaps r1th row with r2th.
    Matrix ero_swap(const Matrix& matrix, std::size_t r1, std::size_t r2);

    //multiply multiplies every element in rth row with constant number c.
    Matrix ero_multiply(const Matrix& matrix, std::size_t r, double c);

    //sum adds   r1th x c   into r2th row.
    Matrix ero_sum(const Matrix& matrix, std::size_t r1, double c, std::size_t r2);
    
    //upper triangular implement this function so that it will calculate the upper triangular form of the matrix using the ERO operations.
    Matrix upper_triangular(const Matrix& matrix);
    

} // namespace algebra


#endif //AP_HW1_H
