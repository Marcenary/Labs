#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

class ILoggable {
public:
	virtual void logToScreen() const = 0;
	virtual void logToFile(const string& filename) const = 0;
	virtual double calculate() const = 0;
};
class IShuffle {
public:
	virtual void shuffle() const = 0;
	virtual void shuffle(size_t i, size_t j) const = 0;
};
class ExpressionEvaluator :ILoggable {
protected:
	int operandsCount;
	double* operand_arr;
public:
	ExpressionEvaluator() : operandsCount(20) {
		operand_arr = new double[operandsCount] {0};
	}
	ExpressionEvaluator(int count) : operandsCount(count) {
		operand_arr = new double[operandsCount] {0};
	}
	virtual ~ExpressionEvaluator() = default;
	void setOperand(size_t pos, double value) {
		if (pos >= 0 && pos <= operandsCount)
			operand_arr[pos-1] = value;
		else
			cout << "Position exit array out" << endl;
	}
	void setOperands(double ops[], size_t n) {
		if (n > 0 && n <= operandsCount)
			for (int i = 0; i < n; i++)
				operand_arr[i] = ops[i];
		else
			cout << "Position exit array out" << endl;
	}
	void print() {
		for (int i = 0; i < operandsCount; i++) {
			cout << operand_arr[i] << " ";
		}
	}
};
class Subtractor : public ExpressionEvaluator, public IShuffle {
public:
	Subtractor() : ExpressionEvaluator() {}
	Subtractor(int count) : ExpressionEvaluator(count) {}
	double calculate() const override {
		double res = 0;
		for (int i = 0; i < operandsCount; i++) {
			res += operand_arr[i];
		}
		return res;
	}
	void logToScreen() const override {
		for (int i = 1; i <= operandsCount; i++) {
			if (i == 1) {
				cout << operand_arr[i - 1];
				continue;
			}
			cout << " + " << operand_arr[i - 1];
		}
		cout << " = " << calculate() << endl;
	}
	void logToFile(const  string& filename) const override {
		ofstream out;
		out.open(filename, ios::app);
		if (out.is_open()) {
			for (int i = 1; i <= operandsCount; i++) {
				if (i == 1) {
					out << operand_arr[i - 1];
					continue;
				}
				out << " + " << operand_arr[i - 1];
			}
			out << endl;
		}
	}
	void shuffle() const override {
		//Bubble metod
		for (int i = 0; i < operandsCount - 1; i++)
			for (int j = 0; j < operandsCount - i - 1; j++)
				if (operand_arr[j] < operand_arr[j + 1]) {
					double temp = operand_arr[j];
					operand_arr[j] = operand_arr[j + 1];
					operand_arr[j + 1] = temp;
				}
			
	}
	void shuffle(size_t i, size_t j) const override {
		//Bubble metod
		for (int l = i; l < j - 1; l++) 
			for (int g = i; g < j - (l-i) - 1; g++)
				if (operand_arr[g] < operand_arr[g + 1]) {
					double temp = operand_arr[g];
					operand_arr[g] = operand_arr[g + 1];
					operand_arr[g + 1] = temp;
				}
	}
};
class Multiplier : public ExpressionEvaluator, public IShuffle {
public:
	Multiplier() : ExpressionEvaluator() {}
	Multiplier(int count) : ExpressionEvaluator(count) {}
	double calculate() const override {
		double res = 1;
		for (int i = 0; i < operandsCount; i++) {
			res *= operand_arr[i];
		}
		return res;
	}
	void logToScreen() const override {
		for (int i = 1; i <= operandsCount; i++) {
			if (i == 1) {
				cout << operand_arr[i - 1];
				continue;
			}
			cout << " * " << operand_arr[i - 1];
		}
		cout << " = " << calculate() << endl;
	}
	void logToFile(const  string& filename) const override {
		ofstream out;
		out.open(filename, ios::app);
		if (out.is_open()) {
			for (int i = 1; i <= operandsCount; i++) {
				if (i == 1) {
					out << operand_arr[i - 1];
					continue;
				}
				out << " * " << operand_arr[i - 1];
			}
			out << endl;
		}
	}
	void shuffle() const override {
		//Bubble metod
		for (int i = 0; i < operandsCount - 1; i++)
			for (int j = 0; j < operandsCount - i - 1; j++)
				if (operand_arr[j] < operand_arr[j + 1]) {
					double temp = operand_arr[j];
					operand_arr[j] = operand_arr[j + 1];
					operand_arr[j + 1] = temp;
				}

	}
	void shuffle(size_t i, size_t j) const override {
		//Bubble metod
		for (int l = i; l < j - 1; l++)
			for (int g = i; g < j - (l - i) - 1; g++)
				if (operand_arr[g] < operand_arr[g + 1]) {
					double temp = operand_arr[g];
					operand_arr[g] = operand_arr[g + 1];
					operand_arr[g + 1] = temp;
				}
	}
};
class CustomExpression : public ExpressionEvaluator, public IShuffle {
public:
	CustomExpression() : ExpressionEvaluator() {}
	CustomExpression(int count) : ExpressionEvaluator(count) {}
	double calculate() const override {
		double res = 1;
		for (int i = 1; i <= operandsCount; i++) {
			res += i*operand_arr[i-1];
		}
		return res;
	}
	void logToScreen() const override {
		for (int i = 1; i <= operandsCount; i++) {
			if (i == 1) {
				cout << i << "*" << operand_arr[i - 1];
				continue;
			}
			cout << " + (" << i << "*" << operand_arr[i - 1] << ")";
		}
		cout << " = " << calculate() << endl;
	}
	void logToFile(const  string& filename) const override {
		fstream out;
		out.open(filename, ios::app);
		if (out.is_open()) {
			for (int i = 1; i <= operandsCount; i++) {
				if (i == 1) {
					out << i << "*" << operand_arr[i - 1];
					continue;
				}
				out << " + (" << i << "*" << operand_arr[i - 1] << ")";
			}
			out << endl;
		}
	}
	void shuffle() const override {
		//Bubble metod
		for (int i = 0; i < operandsCount - 1; i++)
			for (int j = 0; j < operandsCount - i - 1; j++)
				if (operand_arr[j] < operand_arr[j + 1]) {
					double temp = operand_arr[j];
					operand_arr[j] = operand_arr[j + 1];
					operand_arr[j + 1] = temp;
				}

	}
	void shuffle(size_t i, size_t j) const override {
		//Bubble metod
		for (int l = i; l < j - 1; l++)
			for (int g = i; g < j - (l - i) - 1; g++)
				if (operand_arr[g] < operand_arr[g + 1]) {
					double temp = operand_arr[g];
					operand_arr[g] = operand_arr[g + 1];
					operand_arr[g + 1] = temp;
				}
	}
};

int main() {
	Subtractor w(10);
	Multiplier s(10);
	CustomExpression d(10);
	double arr[10]{1.4, 34, 2.3, 45.2, 54.3, 34.4, 15, 25, 100, 23.4};
	w.setOperands(arr, 10);
	s.setOperands(arr, 10);
	d.setOperands(arr, 10);
	d.shuffle();
	w.logToScreen();
	s.logToScreen();
	d.logToScreen();
	w.logToFile("D:\\sdss.txt");
	s.logToFile("D:\\sdss.txt");
	d.logToFile("D:\\sdss.txt");
}