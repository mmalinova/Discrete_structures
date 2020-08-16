// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	int length;
} Relation;

unsigned * random_generator(unsigned numbers, unsigned max, unsigned min);
Set * set(unsigned number_of_elements, unsigned max, unsigned min);
void print(Set * set);
Relation * cartesian_product(Set * A, Set * B);
void print_cartesian_product(Relation * cartesian_product);

int main(int argc, const char * argv[]) {
	srand((unsigned)time(NULL));
	Set * A = set(3, 90, 65);
	Set * B = set(7, 90, 65);
	Set * C = set(5, 90, 65);
	Set * D = set(3, 90, 65);

	printf("Set A: \n");
	print(A);
	printf("Set B: \n");
	print(B);

	printf("Set C: \n");
	print(C);
	printf("Set D: \n");
	print(D);

	printf("\n");

	Relation * result = cartesian_product(A, A);
	print_cartesian_product(result);

	Relation * result1 = cartesian_product(A, B);
	print_cartesian_product(result1);

	free(A);
	free(B);
	free(C);
	free(D);
	free(result);
	free(result1);

	return 0;
}

Relation * cartesian_product(Set * A, Set * B) {
	Relation * relation = (Relation*)malloc(sizeof(Relation));
	int length = A->length * B->length;
	relation->pairs = (Pair*)malloc(sizeof(Pair)*length);
	relation->length = length;

	int i, j, index = 0;

	for (i = 0; i < A->length; i++) {
		for (j = 0; j < B->length; j++) {
			relation->pairs[index].x = A->array[i];
			relation->pairs[index].y = B->array[j];
			index = index + 1;
		}
	}
	return relation;
}


unsigned * random_generator(unsigned number_of_blocks, unsigned max, unsigned min)
{
	unsigned * array = (unsigned*)malloc(sizeof(unsigned)*number_of_blocks);
	unsigned x, i = 0;

	while (i < number_of_blocks)
	{
		int r = rand() % (max + 1 - min) + min;

		for (x = 0; x < i; x++)
		{
			if (array[x] == r)
			{
				break;
			}
		}
		if (x == i)
		{
			array[i] = r;
			i = i + 1;
		}
	}
	return array;
}

Set * set(unsigned number_of_elements, unsigned max, unsigned min)
{
	Set * set = (Set*)malloc(sizeof(Set));
	set->length = number_of_elements;
	set->array = random_generator(set->length, max, min);

	return set;
}

void print(Set * set)
{
	int i;
	for (i = 0; i < set->length; i++)
	{
		printf("%c\t", set->array[i]);
	}
	printf("\n");
}

void print_cartesian_product(Relation * result) {
	printf("Length of cartesian product is %d.\n", result->length);

	printf("{");
	for (int i = 0; i < result->length; i++) {
		printf("(%c, %c)", result->pairs[i].x, result->pairs[i].y);
		if (i <= result->length - 2) {
			printf(",");
		}
	}
	printf("}\n");
}