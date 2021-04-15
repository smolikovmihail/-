﻿
#include "pch.h"
#include <stdio.h>
#include <cmath>
#include <stdlib.h>

void sysout(double **a, double *y, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf_s("%f %f %f", a[i][j], "*x", j);
			if (j < n - 1)
				printf_s (" + ");
		}
		printf_s(" = ");
		printf_s("%d" , y[i]);
		printf_s("/n");
	}
	return;
}
double * gauss(double **a, double *y, int n)
{
	double *x, max;
	int k, index;
	const double eps = 0.00001;  // точность
	x = new double[n];
	k = 0;
	while (k < n)
	{
		// Поиск строки с максимальным a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max < eps)
		{
			// нет ненулевых диагональных элементов
			printf_s("Решение получить невозможно из-за нулевого столбца ");
			printf_s("%d",index);
			printf_s(" матрицы A");
			printf_s("/n");
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		// Нормализация уравнений
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	// обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}
int main()
{
	double **a, *y, *x;
	int n;
	system("chcp 1251");
	system("cls");
	printf_s( "Введите количество уравнений: ");

	scanf_s("%d" ,&n);
	a = new double*[n];
	y = new double[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			printf_s("a[");
			printf_s("%d", i); 
			printf_s("][");
			printf_s("%d",j); 
			printf_s( "]= ");
			scanf_s("%d", a[i][j]);
		}
	}
	for (int i = 0; i < n; i++)
	{
		printf_s("y[");
		printf_s("%d", i);
		printf_s( "]= ");
		scanf_s ("%d",y[i]);
	}
	sysout(a, y, n);
	x = gauss(a, y, n);
	for (int i = 0; i < n; i++)
	{
		printf_s("x[");
		printf_s("%d", i);
		printf_s("]=");
		printf_s("%d", x[i]);
		printf_s("/n");
	}
	getc;
	getc;
	return 0;
}
