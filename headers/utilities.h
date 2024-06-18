
/*
 * SPARSE_MATRIX_OPERATIONS
 * This project presents the implementation of basic sparse matrix operations.
 *
 * Copyright (C) 2024, Rico Morasata.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * DISCLAIMER OF LIABILITY
 *
 * THIS SOFTWARE IS PROVIDED BY RICO MORASATA "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL RICO MORASATA BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Some useful macros
#define INT_SIZE 		sizeof(int)
#define DOUBLE_SIZE 	sizeof(double)


/**
 * @brief	This defines a function pointer to a comparator function.
 * 
 * @param	a: constant pointer to first element
 * @param	b: constant pointer to second element 
 * @return	a positive integer if element pointed by a is smaller than that pointed by b, 
 * 			a negative integer otherwise.
 * */
typedef int (*comparator)(const void *a, const void *b);


/**
 * @brief	Comparator function for integer values.
 * */
int 	compare_int(const void *a, const void *b);


/**
 * @brief	Comparator function for floating point values.
 * */
int 	compare_double(const void *a, const void *b);

/**
 * @brief	This function swaps two values.
 * @param	a 			: pointer to the first element
 * @param 	b 			: pointer to the second element
 * @param	element_size: size of elements
 * */
void 	swap(void *a, void *b, size_t element_size);


void 	reverse_array(void *arr, size_t n, size_t element_size);

/**
 * @brief 	Checks whether an array is sorted in ascending order.
 * @return 	1 if in ascending order, 0 otherwise.*/
int 	is_sorted_ascending(void *arr, size_t n, size_t element_size, comparator comp);

/**
 * @brief 	Checks whether an array is sorted in descending order.
 * @return 	1 if in descending order, 0 otherwise.*/
int 	is_sorted_descending(void *arr, size_t n, size_t element_size, comparator comp);

/**
 * @return	1 if the array is sorted in ascending order, 0 in descending order, and -1 if unsorted.
 * */
int 	is_sorted(void *arr, size_t n, size_t element_size, comparator comp);


/**
 * @brief Merges two sorted arrays arr1 and arr2 of length n1 and n2, respectively, into the array arr3.*/
void 	merge_sorted_arrays(void *arr1, size_t n1, void *arr2, size_t n2, void *arr3, size_t element_size, comparator comp, int dir);

/**
 * @brief 	Executes a linear search between the indices low and high to find the entry pointed to by key.
 * @return 	the index of the entry if present, -1 otherwise.*/
int 	linear_search_in_range(void *arr, size_t low, size_t high, size_t element_size, comparator comp, void *key);

/**
 * @brief 	Executes a binary search between the indices low and high to find the entry pointed to by key.
 * @return 	the index of the entry if present, -1 otherwise.*/
int 	binary_search_in_range(void *arr, size_t low, size_t high, size_t element_size, comparator comp, void *key, int dir);

/*@return	A pointer to the maximum element in the array.*/
void 	*get_max(void *arr, size_t n, size_t element_size, comparator comp, int dir);

/*@return	A pointer to the minimum element in the array.*/
void 	*get_min(void *arr, size_t n, size_t element_size, comparator comp, int dir);


#endif