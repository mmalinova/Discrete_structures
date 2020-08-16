// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_RAND_NUMBERS 100

typedef struct Set {
	unsigned * array;
	unsigned length;
} Set;

Set * set(unsigned number_of_blocks);
unsigned * random_generator(unsigned number_of_rand_numbers);
void print(Set * set);
unsigned find_element(Set * set, unsigned element);
Set * Union(Set * A, Set * B); //обединение
Set * intersection(Set * A, Set * B); //сечение
Set * difference(Set * A, Set * B); //разлика
Set * symmetric_difference(Set * A, Set * B); //симетрична разлика

int main(void)
{
	srand((unsigned)time(NULL));
	Set * A = set(5);
	Set * B = set(10);

	printf("Set A: \n");
	print(A);
	printf("Set B: \n");
	print(B);

	printf("Union between A and B is:\n");
	print(Union(A, B));
	printf("Difference between A and B is:\n");
	print(difference(A, B));
	printf("Intersection between A and B is:\n");
	print(intersection(A, B));
	printf("Symmetric difference between A and B is:\n");
	print(symmetric_difference(A, B));

	free(A);
	free(B);

	return 0;
}

unsigned * random_generator(unsigned number_of_blocks)
{
	unsigned * array = (unsigned*)malloc(sizeof(unsigned)*number_of_blocks);
	unsigned x, i = 0;

	while (i < number_of_blocks)
	{
		unsigned r = rand() % NUMBER_OF_RAND_NUMBERS + 1;

		for (x = 0; x < i; x++)
		{
			if (array[x] == r)
			{
				break;
			}
		}
		if (x == i)
		{
			array[i++] = r;
		}
	}
	return array;
}

Set * set(unsigned number_of_elements)
{
	Set * set = (Set*)malloc(sizeof(Set));
	set->array = (unsigned*)malloc(sizeof(unsigned)*number_of_elements);
	set->array = random_generator(number_of_elements);
	set->length = number_of_elements;

	return set;
}

void print(Set * set)
{
	unsigned i;
	for (i = 0; i < set->length; i++)
	{
		printf("%d\t", set->array[i]);
	}
	printf("\n");
}

Set * Union(Set * A, Set * B)
{
	unsigned i, index, length = A->length + B->length - intersection(A, B)->length;
	Set * result_set = (Set *)malloc(sizeof(Set));
	result_set->array = (unsigned*)realloc(A->array, sizeof(unsigned)*length);
	result_set->length = length;

	index = A->length;

	for (i = 0; i < B->length; i++)
	{
		if (!find_element(A, B->array[i]))
		{
			result_set->array[index++] = B->array[i];
		}
	}
	return result_set;
}

unsigned find_element(Set * set, unsigned element)
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

Set * intersection(Set * A, Set * B)
{
	unsigned i, j, index = 0;
	Set * result_set = (Set*)malloc(sizeof(Set));
	result_set->array = (unsigned*)malloc(sizeof(unsigned));
	result_set->length = 0;

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

Set  * difference(Set * A, Set * B)
{
	unsigned i, index = 0, length = A->length - intersection(A, B)->length;
	Set * result_set = (Set*)malloc(sizeof(Set));
	result_set->array = (unsigned*)malloc(sizeof(unsigned)*length);
	result_set->length = length;

	for (i = 0; i < A->length; i++) {
		if (find_element(B, A->array[i]) == 0) {
			result_set->array[index++] = A->array[i];
		}
	}
	return result_set;
}

Set * symmetric_difference(Set * A, Set * B)
{
	return Union(difference(A, B), difference(B, A));
}
