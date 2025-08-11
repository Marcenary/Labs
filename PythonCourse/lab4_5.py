import numpy as np

# Создаем матрицы A и B
A = np.random.rand(3, 5)  # Матрица размерности 3x5
B = np.random.rand(5, 2)  # Матрица размерности 5x2

# Умножение матриц
result_mult = np.dot(A, B)
print("Результат умножения матриц A и B:")
print(result_mult)

# Создаем матрицу размерности 5x3 и вектор размерности 3x1
matrix_5x3 = np.random.rand(5, 3)
vector_3d = np.random.rand(3, 1)

# Умножение матрицы на вектор
result_vector_mult = np.dot(matrix_5x3, vector_3d)
print("Результат умножения матрицы на вектор:")
print(result_vector_mult)

# Создаем матрицу коэффициентов и вектор свободных членов
coeff_matrix = np.array([[2, 1, -1], [-3, -1, 2], [-2, 1, 2]])
constants = np.array([8, -11, -3])

# Решение системы линейных уравнений
solution = np.linalg.solve(coeff_matrix, constants)
print("Решение системы линейных уравнений:")
print(solution)

# Создаем квадратную матрицу 5x5
matrix_5x5 = np.random.rand(5, 5)

# Расчет определителя
determinant = np.linalg.det(matrix_5x5)
print("Определитель матрицы 5x5:")
print(determinant)

# Создаем квадратную матрицу 5x5
matrix_5x5 = np.random.rand(5, 5)

# Получение обратной матрицы
inverse_matrix = np.linalg.inv(matrix_5x5)

# Транспонирование матрицы
transposed_matrix = matrix_5x5.T

print("Обратная матрица:")
print(inverse_matrix)
print("Транспонированная матрица:")
print(transposed_matrix)

