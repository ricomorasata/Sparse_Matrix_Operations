
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


#include "formats.h"


/**For convenience, calloc() is called so that, upon successful memory allocation,
 * the array entries are initialized to zero.*/
void allocate_COO_matrix(SparseMatrix *mat) {

	int *row_index	= calloc(mat->nnz , INT_SIZE);
	IS_POINTER_VALID(row_index);
	mat->ia = row_index; 

	int *col_index	= calloc(mat->nnz , INT_SIZE);
	IS_POINTER_VALID(row_index);
	mat->ja = col_index; 

	double *val	= calloc(mat->nnz , DOUBLE_SIZE);
	IS_POINTER_VALID(val);
	mat->a = val; 
}

void allocate_CSR_matrix(SparseMatrix *mat) {

	int *row_ptr = calloc((mat->nr + 1) , INT_SIZE);
	IS_POINTER_VALID(row_ptr);
	mat->ia = row_ptr; 

	int *col_index = calloc(mat->nnz , INT_SIZE);
	IS_POINTER_VALID(col_index);
	mat->ja = col_index; 

	double *val	= calloc(mat->nnz , DOUBLE_SIZE);
	IS_POINTER_VALID(val);
	mat->a = val; 
}


void allocate_CSC_matrix(SparseMatrix *mat) {

	int *row_index	= calloc(mat->nnz , INT_SIZE);
	IS_POINTER_VALID(row_index);
	mat->ia = row_index; 

	int *col_ptr = calloc((mat->nr + 1) , INT_SIZE);
	IS_POINTER_VALID(col_ptr);
	mat->ja = col_ptr; 

	double *val	= calloc(mat->nnz , DOUBLE_SIZE);
	IS_POINTER_VALID(val);
	mat->a = val; 
}

void count_nonzeros_per_row_CSR(SparseMatrix *CSR, int *nnz_per_row) {

	for (int i = 0; i < CSR->nr; i++) {
		nnz_per_row[i] = CSR->ia[i + 1] - CSR->ia[i];
	}
}


void count_nonzeros_per_row_COO(SparseMatrix *COO, int *nnz_per_row) {

	int i, j, k, count;

	i = 0;
	j = 0;
	count = 0;

	while (i < COO->nr) {
	
		k = 1;
		
		while ((j < COO->nnz - 1) && (COO->ia[j] == COO->ia[j + 1])) {
			
			j++;
			k++;

			if ((COO->ia[j] != COO->ia[j + 1]) && (k >= 1)) {
				break;
			}
		}

		count += k;
		j = count;

		nnz_per_row[i] = k;
		i++;
	}

}



//This function assumes that the COO matrix is sorted.
void convert_COO_to_CSR(SparseMatrix *COO, SparseMatrix *CSR) {

	//Step 1: allocate CSR matrix
	CSR->nr 	= COO->nr;
	CSR->nnz 	= COO->nnz;
	allocate_CSR_matrix(CSR);

	//Step 2: copy data: the ja and a arrays will be the same
	memcpy(CSR->ja, COO->ja, COO->nnz * INT_SIZE);
	memcpy(CSR->a, COO->a, COO->nnz * DOUBLE_SIZE);

	//Step 3: fill out the row pointer array in CSR
	int *nzr = calloc(COO->nr, INT_SIZE);
	IS_POINTER_VALID(nzr);
	count_nonzeros_per_row_COO(COO, nzr);
	

	//Step 3: Populate the ia array in CSR
	CSR->ia[0] = 0;
	for (int i = 0; i < CSR->nr; i++) {
		CSR->ia[i + 1] = CSR->ia[i] + nzr[i];
	}

	free(nzr);
}

//This implementation assumes that the COO matrix is stored in row major ordering.
void convert_CSR_to_COO(SparseMatrix *CSR, SparseMatrix *COO) {

	//Step 1: allocate COO matrix
	COO->nr 	= CSR->nr;
	COO->nnz 	= CSR->nnz;
	allocate_COO_matrix(COO);

	//Step 2: populate the ja and a arrays of the CSR matrix
	memcpy(COO->ja, CSR->ja, CSR->nnz * INT_SIZE);
	memcpy(COO->a, CSR->a, CSR->nnz * DOUBLE_SIZE);

	//Step 3: populate the ia array of the CSR matrix
	int i, j, k;
	i = 0;
	while (i < COO->nr) {
		
		j = CSR->ia[i];
		while (j < COO->nnz) {
			
			for (k = 0; k < CSR->ia[i + 1] - j; k++) {
				COO->ia[j] = i;
			}
			j++;
		}
		i++;
	}

}


void convert_CSR_to_CSC(SparseMatrix *CSR, SparseMatrix *CSC) {

	//Step 1: allocate CSC matrix
	CSC->nnz 	= CSR->nnz;
	CSC->nr 	= CSR->nr;
	allocate_CSC_matrix(CSC);

	int i, j, k, index;

	//Step 2: populate column pointer array
	for (i = 0; i < CSC->nr; i++) {

		for (j = CSR->ia[i]; j < CSR->ia[i + 1]; j++) {
			k 			= CSR->ja[j]  + 1;
			CSC->ja[k] += 1;
		}
	}

	CSC->ja[0] = 0;
	for (i = 0; i < CSC->nr; i++) {
		CSC->ja[i + 1] += CSC->ja[i];
	}

	//Step 3: populate ia and a
	for (i = 0; i < CSC->nr; i++) {

		for (j = CSR->ia[i]; j < CSR->ia[i + 1]; j++) {
			k 		= CSR->ja[j];
			index 	= CSC->ja[k];
			CSC->a[index] 	= CSR->a[j];
			CSC->ia[index] 	= i;
			CSC->ja[k] 		= index + 1;
		}
	}

	for (i = CSC->nr - 1; i >= 0; i--) {
		CSC->ja[i + 1] = CSC->ja[i];
	}
	CSC->ja[0] = 0;
}

void convert_CSC_to_CSR(SparseMatrix *CSC, SparseMatrix *CSR) {

	
	//Step 1: allocate CSR matrix
	CSR->nnz 	= CSC->nnz;
	CSR->nr 	= CSC->nr;
	allocate_CSR_matrix(CSR);

	int i, j, k, index;

	//Step 2: populate row pointer array
	for (i = 0; i < CSR->nr; i++) {

		for (j = CSC->ja[i]; j < CSC->ja[i + 1]; j++) {
			k = CSC->ia[j]  + 1;
			CSR->ia[k] += 1;
		}
	}

	CSR->ia[0] = 0;
	for (i = 0; i < CSR->nr; i++) {
		CSR->ia[i + 1] += CSR->ia[i];
	}

	//Step 3: populate ia and a
	for (i = 0; i < CSR->nr; i++) {

		for (j = CSC->ja[i]; j < CSC->ja[i + 1]; j++) {
			k 		= CSC->ia[j];
			index 	= CSR->ia[k];
			CSR->a[index] 	= CSC->a[j];
			CSR->ja[index] 	= i;
			CSR->ia[k] 		= index + 1;
		}
	}

	for (i = CSR->nr - 1; i >= 0; i--) {
		CSR->ia[i + 1] = CSR->ia[i];
	}
	CSR->ia[0] = 0;

}

void 	transpose_CSR(const SparseMatrix *CSR, SparseMatrix *transpose) {

	transpose->nr 	= CSR->nr;
	transpose->nnz 	= CSR->nnz;
	allocate_CSR_matrix(transpose);

	int i, j, k;
	int *row_count = calloc(transpose->nr, INT_SIZE);
	IS_POINTER_VALID(row_count);

	//Count the number of entries in each column of the input matrix
	for (i = 0; i < CSR->nnz; i++) {
		row_count[CSR->ja[i]]++;	
	}
	
	//Compute the row pointers from the row_count array
	transpose->ia[0] = 0;
	for (i = 0; i < transpose->nr; i++) {
		transpose->ia[i + 1] = transpose->ia[i] + row_count[i];
	}

	//Reset the row_count array for reuse
	for (i = 0; i < transpose->nr; i++) {
		row_count[i] = transpose->ia[i];
	}

	//Populate the ja and a arrays in transpose
	for (i = 0; i < CSR->nr; i++) {

		for (j = CSR->ia[i]; j < CSR->ia[i + 1]; j++) {
			k = row_count[CSR->ja[j]]++;
			transpose->ja[k] 	= i;
			transpose->a[k] 	= CSR->a[j];
		}
	}

	free(row_count);
}

int is_symmetric(SparseMatrix *CSR) {

	//Loop over all the rows
	for (int i = 0; i < CSR->nr; i++) {

		//Loop over the nonzero entries in each row
		for (int j = CSR->ia[i]; j < CSR->ia[i + 1]; j++) {

			int col = CSR->ja[j];
			double val = CSR->a[j];

			//Skip the diagonal entries
			if (col != i) {
				
				int low 	= CSR->ia[col];
				int high 	= CSR->ia[col + 1];
				int key 	= binary_search_in_range(CSR->ja, low, high, INT_SIZE, compare_int, &i, 1);
				if ((key != -1) && (CSR->a[key] == val)) {
					continue;
				}

				//The matrix is not symmetric
				else {
					return 0;
				}
			}
		}
	}

	//The matrix is symmetric
	return 1;
}


void extract_upper_triangular(SparseMatrix *CSR, SparseMatrix *upper) {

	upper->nr 	= CSR->nr;
	upper->nnz 	= (CSR->nnz - CSR->nr)/2 + CSR->nr;

	allocate_CSR_matrix(upper); 
	
	int k = 0;
	for (int i = 0; i < CSR->nr; i++) {

		int m = 0;
		for (int j = CSR->ia[i]; j < CSR->ia[i + 1]; j++) {

			//Populate ja and a
			if (CSR->ja[j] >= i) {
				m++; 
				upper->ja[k] 	= CSR->ja[j];
				upper->a[k] 	= CSR->a[j];
				k++;
			}
		}

		//Populate the row pointer array ia
		upper->ia[i + 1] = m + upper->ia[i];
	}

}


void extract_lower_triangular(SparseMatrix *CSR, SparseMatrix *lower) {

	lower->nr 	= CSR->nr;
	lower->nnz 	= (CSR->nnz - CSR->nr)/2 + CSR->nr;

	allocate_CSR_matrix(lower); 
	
	int k = 0;
	for (int i = 0; i < CSR->nr; i++) {

		int m = 0;
		for (int j = CSR->ia[i]; j < CSR->ia[i + 1]; j++) {

			//Populate ja and a
			if (CSR->ja[j] <= i) {
				m++; 
				lower->ja[k] 	= CSR->ja[j];
				lower->a[k] 	= CSR->a[j];
				k++;
			}

		}

		//Populate the row pointer array ia
		lower->ia[i + 1] = m + lower->ia[i];
	}

}

void print_CSR_matrix(SparseMatrix *CSR) {

	printf("CSR entries: \n");
	for (int i = 0; i < CSR->nnz; i++) {
		printf("ja[%d] = %d, a[%d] = %g\n", i, CSR->ja[i], i, CSR->a[i]);
	}

	for (int i = 0; i < CSR->nr + 1; i++) {
		printf("ia [%d] = %d\n", i, CSR->ia[i]);
	}
}


void print_CSC_matrix(SparseMatrix *CSC) {

	printf("CSC entries: \n");
	for (int i = 0; i < CSC->nnz; i++) {
		printf("ia[%d] = %d, a[%d] = %g\n", i, CSC->ia[i], i, CSC->a[i]);
	}

	for (int i = 0; i < CSC->nr + 1; i++) {
		printf("ja [%d] = %d\n", i, CSC->ja[i]);
	}
}


/**
 * This function converts a sparse matrix in COO format into CSR format.
 * The matrix in COO format is assumed to be sorted and stored in row-major order.
 * */

void deallocate_sparse_matrix(SparseMatrix *mat) {
	
	free(mat->ia);
	free(mat->ja);
	free(mat->a);
}
