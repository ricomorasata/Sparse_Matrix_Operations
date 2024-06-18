
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

/**
 * To check for memory issues, execute the following command:
 * valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="log.txt" ./bin/main
 */

int main(int argc, char const *argv[]) {

	int nr 	= 5;
	int nnz = 15;
	
	SparseMatrix CSR;
	CSR.nr = nr;
	CSR.nnz = nnz;
	allocate_CSR_matrix(&CSR);

	int ja[] 	= {0, 2, 4, 1, 3, 0, 2, 4, 1, 3, 4, 0, 2, 3, 4};
 	double a[] 	= {1, -4, 3, 8, 2, 4, 7, 4, 2, 9, 5, 3, 4, 5, 6};
	int ia[] 	= {0, 3, 5, 8, 11, 15};

	memcpy(CSR.ia, ia, (nr + 1) * INT_SIZE);
	memcpy(CSR.ja, ja, (nnz) * INT_SIZE);
	memcpy(CSR.a, a, (nnz) * DOUBLE_SIZE);

	int *nzr = calloc(nr, INT_SIZE);
	count_nonzeros_per_row_CSR(&CSR, nzr);

	printf("Number of nonzero elements per row: \n");
	for (int i = 0; i < CSR.nr; i++) {
		printf("%d\n", nzr[i]);
	}
	
	printf("\n");

	SparseMatrix CSC;
	convert_CSR_to_CSC(&CSR, &CSC);

	printf("\n");
	
	SparseMatrix CSR1;
	convert_CSC_to_CSR(&CSC, &CSR1);

	printf("\n");

	int sym_check = is_symmetric(&CSR1);
	printf("Is the sparse matrix symmetric? %d\n", sym_check);

	if (sym_check) {
		SparseMatrix LOWER;
		extract_lower_triangular(&CSR1, &LOWER);
		print_CSR_matrix(&LOWER);
		deallocate_sparse_matrix(&LOWER);
	}

	printf("\n");
	printf("Sparse matrix transpose: \n");

	SparseMatrix trans;
	transpose_CSR(&CSR, &trans);
	print_CSR_matrix(&trans);


	free(nzr);
	deallocate_sparse_matrix(&CSR);
	deallocate_sparse_matrix(&CSC);
	deallocate_sparse_matrix(&CSR1);
	deallocate_sparse_matrix(&trans);

	return 0;
}

