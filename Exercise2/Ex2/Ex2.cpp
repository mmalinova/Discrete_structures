// Ex2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	unsigned length;
} Relation;

unsigned * random_generator(unsigned numbers, unsigned max, unsigned min);
Set * set(unsigned number_of_elements, unsigned max, unsigned min);
void print(Set * set);
Relation * cartesian_product(Set * A, Set * B);
void print_cartesian_product(Relation * cartesian_product);

Relation * Union(Relation * rel1, Relation * rel2);
Relation * difference(Relation * rel1, Relation * rel2);
Set * difference_sets(Set * A, Set * B);
unsigned find_element(Relation * relation, Pair pair);
unsigned find_element_sets(Set * set, unsigned element);
Set * intersection_sets(Set * A, Set * B);
Relation * intersection(Relation * A, Relation * B);

int main(int argc, const char * argv[]) {
	srand((unsigned)time(NULL));
	Set * A = set(3, 90, 65);
	Set * B = set(3, 90, 65);
	Set * C = set(3, 90, 65);
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

	Relation * left_side = difference(cartesian_product(A, B), cartesian_product(C, D));
	Relation * right_side = Union(cartesian_product(difference_sets(A, C), B), cartesian_product(A, difference_sets(B, D)));
	print_cartesian_product(left_side);
	print_cartesian_product(right_side);

	free(A);
	free(B);
	free(C);
	free(D);
	free(left_side);
	free(right_side);

	return 0;
}

Relation * cartesian_product(Set * A, Set * B) {
	Relation * relation = (Relation*)malloc(sizeof(Relation));
	unsigned length = A->length * B->length;
	relation->pairs = (Pair*)malloc(sizeof(Pair)*length);
	relation->length = length;

	unsigned i, j, index = 0;

	for (i = 0; i < A->length; i++) {
		for (j = 0; j < B->length; j++) {
			relation->pairs[index].x = A->array[i];
			relation->pairs[index].y = B->array[j];
			index++;
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
		unsigned r = rand() % (max + 1 - min) + min;

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
	unsigned i;
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

Relation * intersection(Relation * A, Relation * B)
{
	unsigned i, j, index = 0;
	Relation * result_set = (Relation*)malloc(sizeof(Relation));
	result_set->pairs = (Pair*)malloc(sizeof(Pair));

	for (i = 0; i < B->length; i++)
	{
		for (j = 0; j < A->length; j++)
		{
			if (A->pairs[j].x == B->pairs[i].x && A->pairs[j].y == B->pairs[i].y)
			{
				result_set->pairs[index].x = A->pairs[j].x;
				result_set->pairs[index].y = A->pairs[j].y;
				index++;
			}
		}
	}
	result_set->length = index;
	return result_set;
}

Relation * Union(Relation * A, Relation * B) {
	unsigned i, index, length = A->length + B->length - intersection(A, B)->length;
	Relation *result_set = (Relation*)malloc(sizeof(Relation));
	result_set->pairs = (Pair*)realloc(A->pairs, sizeof(Pair)*length);
	result_set->length = length;

	index = A->length;

	for (i = 0; i < B->length; i++)
	{
		if (!find_element(A, B->pairs[i]))
		{
			result_set->pairs[index].x = B->pairs[i].x;
			result_set->pairs[index].y = B->pairs[i].y;
			index++;
		}
	}
	return result_set;
}

unsigned find_element(Relation * relation, Pair pair)
{
	unsigned i;
	for (i = 0; i < relation->length; i++)
	{
		if (pair.x == relation->pairs[i].x && pair.y == relation->pairs[i].y)
		{
			return 1;
		}
	}
	return 0;
}

unsigned find_element_sets(Set * set, unsigned element)
{
	unsigned i;
	for (i = 0; i < set->length; i++)
	{
		if (element == set->array[i])
		{
			return 1;
		}
	}
	return 0;
}

Relation * difference(Relation * rel1, Relation * rel2) {
	int i, index = 0;
	Relation * result_set = (Relation *)malloc(sizeof(Relation));
	int length = rel1->length - intersection(rel1, rel2)->length;
	result_set->pairs = (Pair *)malloc(sizeof(Pair) * length);
	result_set->length = length;

	for (i = 0; i < rel1->length; i++) {
		if (!find_element(rel2, rel1->pairs[i])) {
			result_set->pairs[index].x = rel1->pairs[i].x;
			result_set->pairs[index].y = rel1->pairs[i].y;
			index++;
		}
	}
	result_set->length = index;
	return result_set;
}

Set * intersection_sets(Set * A, Set * B)
{
	int i, j, index = 0;
	Set * result_set = (Set*)malloc(sizeof(Set));
	result_set->array = (unsigned*)malloc(sizeof(unsigned));

	for (i = 0; i < B->length; i++)
	{
		for (j = 0; j < A->length; j++)
		{
			if (A->array[j] == B->array[i])
			{
				result_set->array[index++] = A->array[j];
			}
		}
	}
	result_set->length = index;
	return result_set;
}


Set * difference_sets(Set * A, Set * B)
{
	int i, index = 0, length = A->length - intersection_sets(A, B)->length;
	Set * result_set = (Set*)malloc(sizeof(Set));
	result_set->array = (unsigned*)malloc(sizeof(unsigned)*length);
	result_set->length = length;

	for (i = 0; i < A->length; i++) {
		if (!find_element_sets(B, A->array[i])) {
			result_set->array[index++] = A->array[i];
		}
	}
	result_set->length = index;
	return result_set;
}
