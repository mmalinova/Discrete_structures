// Ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_RAND_NUMBERS 10

typedef struct Set {
	char * array;
	unsigned length;
} Set;

Set * set(unsigned number_of_blocks);
char * random_generator(unsigned number_of_rand_numbers);
void print(Set * set);
unsigned find_element(Set * set, char element);
Set * Union(Set * A, Set * B, Set * C);
Set * Union_two_sets(Set * A, Set * B);
Set * intersection(Set * A, Set * B, Set * C);
Set * intersection_two_sets(Set * A, Set * B);
Set * difference(Set * A, Set * B, Set * C);
Set * difference_two_sets(Set * A, Set * B);
Set * symmetric_difference(Set * A, Set * B, Set * C);

int main(void)
{
	srand((unsigned)time(NULL));
	Set * A = set(5);
	Set * B = set(5);
	Set * C = set(7);

	printf("Set A: \n");
	print(A);
	printf("Set B: \n");
	print(B);
	printf("Set C: \n");
	print(C);

	printf("Union between A and B and C is:\n");
	print(Union(A, B, C));
	printf("Difference between A and B and C is:\n");
	print(difference(A, B, C));
	printf("Intersection between A and B and C is:\n");
	print(intersection(A, B, C));
	printf("Symmetric difference between A and B and C is:\n");
	print(symmetric_difference(A, B, C));

	free(A);
	free(B);
	free(C);

	return 0;
}

char * random_generator(unsigned number_of_blocks)
{
	char * array = (char*)malloc(sizeof(char)*number_of_blocks);
	unsigned x, i = 0;

	while (i < number_of_blocks)
	{
		char r = (char)(rand() % 26 + 65);

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
	set->array = (char*)malloc(sizeof(char)*number_of_elements);
	set->array = random_generator(number_of_elements);
	set->length = number_of_elements;

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

Set * Union_two_sets(Set * A, Set * B)
{
	unsigned i, index, length = A->length + B->length - intersection_two_sets(A, B)->length;
	Set * result_set = (Set *)malloc(sizeof(Set));
	result_set->array = (char*)realloc(A->array, sizeof(char)*length);
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

Set * Union(Set * A, Set * B, Set * C)
{
	return Union_two_sets(Union_two_sets(A, B), C);
}

unsigned find_element(Set * set, char element)
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

Set * intersection(Set * A, Set * B, Set * C)
{
	return intersection_two_sets(intersection_two_sets(A, B), C);
}

Set * intersection_two_sets(Set * A, Set * B)
{
	unsigned i, j, index = 0;
	Set * result_set = (Set*)malloc(sizeof(Set));
	result_set->array = (char*)malloc(sizeof(char));
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

Set  * difference_two_sets(Set * A, Set * B)
{
	unsigned i, index = 0, length = A->length - intersection_two_sets(A, B)->length;
	Set * result_set = (Set*)malloc(sizeof(Set));
	result_set->array = (char*)malloc(sizeof(char)*length);
	result_set->length = length;

	for (i = 0; i < A->length; i++) {
		if (!find_element(B, A->array[i])) {
			result_set->array[index++] = A->array[i];
		}
	}
	return result_set;
}

Set  * difference(Set * A, Set * B, Set * C)
{
	return difference_two_sets(difference_two_sets(A, B), C);
}

Set * symmetric_difference(Set * A, Set * B, Set * C)
{
	Set * A_B_C = difference_two_sets(difference_two_sets(A, B), C);
	Set * B_A_C = difference_two_sets(difference_two_sets(B, A), C);

	Set * B_C_A = difference_two_sets(difference_two_sets(B, C), A);
	Set * C_B_A = difference_two_sets(difference_two_sets(C, B), A);

	Set * A_C_B = difference_two_sets(difference_two_sets(A, C), B);
	Set * C_A_B = difference_two_sets(difference_two_sets(C, A), B);

	return Union_two_sets(Union(Union(A_B_C, B_A_C, B_C_A), C_B_A, A_C_B), C_A_B);
}
