
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


#ifndef FORMATS_H
#define FORMATS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

//Some useful macros
#define INT_SIZE 		sizeof(int)
#define DOUBLE_SIZE 	sizeof(double)

/**
 * Checks whether memory allocation is successful.
 * The program will terminate in case the memory allocation fails.*/
#define IS_POINTER_VALID(ptr) 													\
	if (ptr == NULL) {															\
		fprintf(stderr, "%s", "Memory allocation failed, aborting...\n");		\
		exit(EXIT_FAILURE);														\
	}	


typedef struct {
	int 	nr;				//number of rows and columns; the sparse matrix is assumed to be square.
	int 	nnz;			//number of nonzero entries
	int 	*ia;			//row index array (COO and CSC), row pointer array (CSR)
	int 	*ja;			//column index array (COO and CSR), column pointer array (CSC)
	double 	*a;
} SparseMatrix;


void	allocate_COO_matrix(SparseMatrix *mat);

void	allocate_CSR_matrix(SparseMatrix *mat);

void	allocate_CSC_matrix(SparseMatrix *mat);

void 	count_nonzeros_per_row_CSR(SparseMatrix *CSR, int *nnz_per_row);

void 	count_nonzeros_per_row_COO(SparseMatrix *COO, int *nnz_per_row);

void 	convert_COO_to_CSR(SparseMatrix *COO, SparseMatrix *CSR);

void 	convert_CSR_to_COO(SparseMatrix *CSR, SparseMatrix *COO);

void 	convert_CSR_to_CSC(SparseMatrix *CSR, SparseMatrix *CSC);

void 	convert_CSC_to_CSR(SparseMatrix *CSC, SparseMatrix *CSR);

void 	transpose_CSR(const SparseMatrix *CSR, SparseMatrix *transpose);


/**
 * @return 	1 if the sparse matrix in CSR format is symmetric, and 0 otherwise.
 * */
int 	is_symmetric(SparseMatrix *CSR);

void 	extract_upper_triangular(SparseMatrix *CSR, SparseMatrix *upper);

void 	extract_lower_triangular(SparseMatrix *CSR, SparseMatrix *lower);

void 	print_CSR_matrix(SparseMatrix *CSR);

void 	print_CSC_matrix(SparseMatrix *CSR);

void 	plot_sparsity_pattern(SparseMatrix *mat);

void 	deallocate_sparse_matrix(SparseMatrix *mat);


#endif