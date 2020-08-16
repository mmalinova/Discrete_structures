// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Set {
	unsigned * array;
	unsigned length;
} Set;

void generate_permutations(unsigned n);
void generate_combinations(unsigned n, unsigned k);
void print(Set * set);
unsigned long long fact(unsigned n);
void swap(unsigned * a, unsigned * b);
Set * create_set(unsigned n);

int main()
{

	generate_permutations(3);
	printf("\n");
	generate_combinations(5, 3);
	return 0;
}

Set * create_set(unsigned n) {
	Set * set = (Set*)malloc(sizeof(Set));
	set->array = (unsigned*)malloc(sizeof(unsigned)*n);
	set->length = n;

	unsigned i;
	for (i = 0; i < n; i++) {
		set->array[i] = i + 1;
	}

	return set;
}

void print(Set * set) {
	unsigned i;
	for (i = 0; i < set->length; i++) {
		printf("%d", set->array[i]);
	}
	printf("\n");
}

unsigned long long fact(unsigned n) {
	unsigned long long fact = 0, i;
	if (n < 0) {
		return 0;
	}
	for (i = 2; i <= n; i++) {
		fact = fact * i;
	}
	return fact;
}

void swap(unsigned * a, unsigned * b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void generate_permutations(unsigned n) {
	int i, m, k, p, q;
	Set * set = create_set(n);

	print(set);

	for (i = 2; i <= fact(n); i++)
	{
		m = n - 2;
		while (*(set->array + m) > *(set->array + m + 1)) {
			m = m - 1;
		}

		k = n - 1;

		while (*(set->array + m) > *(set->array + k)) {
			k = k - 1;
		}
		swap(&*(set->array + m), &*(set->array + k));
		p = m + 1;
		q = n - 1;
		while (p < q)
		{
			swap(&*(set->array + p), &*(set->array + q));
			p = p + 1;
			q = q - 1;
		}
		print(set);
	}

}

unsigned long long combinations(unsigned n, unsigned k) {
	return fact(n) / (fact(k)*fact(n - k));
}

void generate_combinations(unsigned n, unsigned k) {
	unsigned i, j, max_val, m;

	Set * set = create_set(k);

	print(set);

	for (i = 2; i <= combinations(n, k); i++) {
		m = k - 1;
		max_val = n;
		while (*(set->array + m) == max_val) {
			m = m - 1;
			max_val = max_val - 1;
		}
		*(set->array + m) = *(set->array + m) + 1;
		for (j = m + 1; j <= k; j++)
			*(set->array + j) = *(set->array + j - 1) + 1;

		print(set);
	}
}