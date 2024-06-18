
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


#include "utilities.h"

int compare_int(const void *v1, const void *v2) {

	int a = *(int *)v1;
	int b = *(int *)v2;
	return ((a > b) - (a < b));
}


int compare_double(const void *v1, const void *v2) {

	double a = *(double *)v1;
	double b = *(double *)v2;
	return ((a > b) - (a < b));
}

void swap(void *v1, void *v2, size_t element_size) {

	char *a = (char *)v1;
	char *b = (char *)v2;
	char temp[element_size];

	memcpy(temp, a, element_size);
	memmove(a, b, element_size);
	memcpy(b, temp, element_size);
}


void reverse_array(void *arr, size_t n, size_t element_size) {

	for (size_t i = 0, j = n - 1; i < j; i++, j--) {

		char *base = (char *)arr;
		swap(base + i * element_size, base + j * element_size, element_size);
	}
}


int is_sorted_ascending(void *arr, size_t n, size_t element_size, comparator comp) {

	char *base = (char *)arr;
	for (size_t i = 0; i < n - 1; i++) {

		if (comp(base + i * element_size, base + (i + 1) * element_size) > 0) {
			return 0;
		}
	}
	return 1;
}

int is_sorted_descending(void *arr, size_t n, size_t element_size, comparator comp) {

	char *base = (char *)arr;
	for (size_t i = 0; i < n - 1; i++) {

		if (comp(base + i * element_size, base + (i + 1) * element_size) < 0) {
			return 0;
		}
	}
	return 1;
}


int is_sorted(void *arr, size_t n, size_t element_size, comparator comp) {

	int asc = is_sorted_ascending(arr, n, element_size, comp);
	int desc = is_sorted_descending(arr, n, element_size, comp);

	if (asc == 1) {
		return 1;
	}
	if (desc == 1) {
		return 0;
	}
	else {
		return -1;
	}
}


void merge_sorted_arrays(void *arr1, size_t n1, void *arr2, size_t n2, void *arr3, size_t element_size, comparator comp, int dir) {

	char temp[(n1 + n2) * element_size];

	size_t i = 1;
	size_t j = 1;
	size_t k = 1;

	char *base1 = (char *)arr1;
	char *base2 = (char *)arr2;
	
	while ((i <= n1) && (j <= n2)) {

		if (((dir == 1) && (comp(base1 + (i - 1) * element_size, base2 + (j - 1) * element_size) < 0)) || \
			((dir == 0) && (comp(base1 + (i - 1) * element_size, base2 + (j - 1) * element_size) > 0))) {

			memcpy(temp + (k - 1) * element_size, base1 + (i - 1) * element_size, element_size);
			i++; k++;
		}
		else {
			memcpy(temp + (k - 1) * element_size, base2 + (j - 1) * element_size, element_size);
			j++; k++;
		}
	}

	for ( ; i <= n1; i++) {
		memcpy(temp + (k - 1) * element_size, base1 + (i - 1) * element_size, element_size);
		k++;
	}

	for ( ; j <= n2; j++) {
		memcpy(temp + (k - 1) * element_size, base2 + (j - 1) * element_size, element_size);
		k++;
	
	}

	memcpy(arr3, temp, (n1 + n2) * element_size);

}


int linear_search_in_range(void *arr, size_t low, size_t high, size_t element_size, comparator comp, void *key) {

	char *base = (char *)arr;
	for (size_t i = low; i < high; i++) {
		if (comp(key, base + i * element_size) == 0) {
			return i;
		}
	}
	return -1;
}


int binary_search_in_range(void *arr, size_t low, size_t high, size_t element_size, comparator comp, void *key, int dir) {

	char *base = (char *)arr;

	while (low <= high) {

		int mid = low + (high - low)/2;
		if (comp(base + mid * element_size, key) == 0) {
			return mid;
		}
		if (((dir == 1) && comp(base + mid * element_size, key) < 0) || \
			((dir == 0) && comp(base + mid * element_size, key) > 0) ) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
		
	}

	return -1;
}



void *get_max(void *arr, size_t n, size_t element_size, comparator comp, int dir) {

	char 	*base = (char *)arr;
	char 	max[element_size];

	if (dir == 1) {
		return base + (n - 1) * element_size;
	}

	if (dir == 0) {
		return base;
	}

	else {
		size_t j = 0;
		memcpy(max, base, element_size);
		for (size_t i = 1; i < n; i++) {
			if (comp(base + i * element_size, max) > 0) {
				memcpy(max, base + i * element_size, element_size);
				j = i;
			}
		}
		return base + j * element_size;
	}

}


void *get_min(void *arr, size_t n, size_t element_size, comparator comp, int dir) {

	char 	*base = (char *)arr;
	char 	min[element_size];

	if (dir == 1) {
		return base;
	}

	if (dir == 0) {
		return base + (n - 1) * element_size;
	}

	else {
		size_t j = 0;
		memcpy(min, base, element_size);
		for (size_t i = 1; i < n; i++) {
			if (comp(base + i * element_size, min) < 0) {
				memcpy(min, base + i * element_size, element_size);
				j = i;
			}
		}
		return base + j * element_size;
	}

}
