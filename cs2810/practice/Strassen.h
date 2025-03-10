#include<bits/stdc++.h>
using namespace std;


void add_matrix(vector<vector<int> > matrix_A,vector<vector<int>> matrix_B,
				vector<vector<int> > &matrix_C,
				int split_index)
{
	for (auto i = 0; i < split_index; i++)
		for (auto j = 0; j < split_index; j++)
			matrix_C[i][j]
				= matrix_A[i][j] + matrix_B[i][j];
}


// This method is the treditional method which run in O(N^3) 
vector<vector<int>> NaiveImplementation(vector<vector<int>>&m1,vector<vector<int>>&m2,int n){
  vector<vector<int>>m3(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
          int item=0;
          for(int k=0;k<n;k++){
            item += m1[i][k]*m2[k][j];
          }
          m3[i][j]=item;
      }
    }
    return m3;
}

vector<vector<int>> multiply_matrix(vector<vector<int>> &matrix_A, vector<vector<int>> &matrix_B)
{
	
	int col_1 = matrix_A[0].size();

	// checking if the input is lower than 32 we run the NaiveMethod for multiplicaiton why ? ask TA
	if(col_1 <= 32){
		return NaiveImplementation(matrix_A,matrix_B,col_1); 
	}
	int row_1 = col_1;
	int col_2 = col_1;
	int row_2 = col_1;

	
	vector<int> result_matrix_row(col_2, 0);
	vector<vector<int> > result_matrix(row_1,result_matrix_row);

	if (col_1 == 1)
		result_matrix[0][0]= matrix_A[0][0] * matrix_B[0][0];
	else {
		int split_index = col_1 / 2;

		vector<int> row_vector(split_index, 0);
		vector<vector<int> > result_matrix_00(split_index,
											row_vector);
		vector<vector<int> > result_matrix_01(split_index,
											row_vector);
		vector<vector<int> > result_matrix_10(split_index,
											row_vector);
		vector<vector<int> > result_matrix_11(split_index,
											row_vector);

		vector<vector<int> > a00(split_index, row_vector);
		vector<vector<int> > a01(split_index, row_vector);
		vector<vector<int> > a10(split_index, row_vector);
		vector<vector<int> > a11(split_index, row_vector);
		vector<vector<int> > b00(split_index, row_vector);
		vector<vector<int> > b01(split_index, row_vector);
		vector<vector<int> > b10(split_index, row_vector);
		vector<vector<int> > b11(split_index, row_vector);

		for (auto i = 0; i < split_index; i++)
			for (auto j = 0; j < split_index; j++) {
				a00[i][j] = matrix_A[i][j];
				a01[i][j] = matrix_A[i][j + split_index];
				a10[i][j] = matrix_A[split_index + i][j];
				a11[i][j] = matrix_A[i + split_index]
									[j + split_index];
				b00[i][j] = matrix_B[i][j];
				b01[i][j] = matrix_B[i][j + split_index];
				b10[i][j] = matrix_B[split_index + i][j];
				b11[i][j] = matrix_B[i + split_index]
									[j + split_index];
			}

		add_matrix(multiply_matrix(a00, b00),
				multiply_matrix(a01, b10),
				result_matrix_00, split_index);
		add_matrix(multiply_matrix(a00, b01),
				multiply_matrix(a01, b11),
				result_matrix_01, split_index);
		add_matrix(multiply_matrix(a10, b00),
				multiply_matrix(a11, b10),
				result_matrix_10, split_index);
		add_matrix(multiply_matrix(a10, b01),
				multiply_matrix(a11, b11),
				result_matrix_11, split_index);

		for (auto i = 0; i < split_index; i++)
			for (auto j = 0; j < split_index; j++) {
				result_matrix[i][j]
					= result_matrix_00[i][j];
				result_matrix[i][j + split_index]
					= result_matrix_01[i][j];
				result_matrix[split_index + i][j]
					= result_matrix_10[i][j];
				result_matrix[i + split_index]
							[j + split_index]
					= result_matrix_11[i][j];
			}

		result_matrix_00.clear();
		result_matrix_01.clear();
		result_matrix_10.clear();
		result_matrix_11.clear();
		a00.clear();
		a01.clear();
		a10.clear();
		a11.clear();
		b00.clear();
		b01.clear();
		b10.clear();
		b11.clear();
	}
	return result_matrix;
}
