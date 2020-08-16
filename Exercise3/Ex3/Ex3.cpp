// Ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Set {
	unsigned * array;
	unsigned length;
} Set;

typedef struct Pair {
	unsigned x;
	unsigned y;
} Pair;

typedef struct Relation {
	Pair * pairs;
	unsigned long long length;
} Relation;


Set * create_set(unsigned n);
void print(Set * set);
unsigned long long c(unsigned n, unsigned k);
Relation * generate_combinations(unsigned n, unsigned k);

int main(int argc, const char * argv[]) {
	unsigned n = 5, k = 2, i, j, matrix[5][5];

	Relation *all_combinations = generate_combinations(n, k);
	for (i = 1; i <= n; i++) {
		matrix[i][i] = pow(i, 2) + pow(i, 2);
	}

	for (i = 0; i < all_combinations->length; i++) {
		matrix[all_combinations->pairs[i].x][all_combinations->pairs[i].y] = matrix[all_combinations->pairs[i].y][all_combinations->pairs[i].x] = pow(all_combinations->pairs[i].x, 2) + pow(all_combinations->pairs[i].y, 2);
	}
	printf("\n");
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			printf("%d\t\t", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
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
	unsigned long long fact = 1, i;
	if (n < 0) {
		return 0;
	}
	for (i = 2; i <= n; i++) {
		fact = fact * i;
	}
	return fact;
}

unsigned long long c(unsigned n, unsigned k) {
	return fact(n) / (fact(k)*fact(n - k));
}

Relation * generate_combinations(unsigned n, unsigned k) {
	unsigned i, j, max_val, m, index = 0;

	Set * set = create_set(k);

	unsigned long long number_of_combinations = c(n, k);
	Relation * rel = (Relation*)malloc(sizeof(Relation));
	rel->pairs = (Pair*)malloc(sizeof(Pair)*number_of_combinations);
	rel->length = number_of_combinations;

	for (i = 0; i < k; i++) {
		set->array[i] = i + 1;
	}

	rel->pairs[index].x = set->array[0];
	rel->pairs[index].y = set->array[1];
	index++;

	for (i = 2; i <= number_of_combinations; i++) {
		m = k - 1;
		max_val = n;
		while (*(set->array + m) == max_val) {
			m = m - 1;
			max_val = max_val - 1;
		}
		*(set->array + m) = *(set->array + m) + 1;
		for (j = m + 1; j <= k; j++)
			*(set->array + j) = *(set->array + j - 1) + 1;

		rel->pairs[index].x = set->array[0];
		rel->pairs[index].y = set->array[1];
		index++;
	}
	return rel;
}