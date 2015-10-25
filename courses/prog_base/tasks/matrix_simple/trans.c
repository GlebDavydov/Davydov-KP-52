void fillRand(int mat[4][4]){
	int i, j;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			mat[i][j] = rand()%1999-999;
		}
	}
}

void rotateCW270(int mat [4] [4]){
	int j, x;								//number of column 								//temporary
	for(j=-1; j<3; j++){
		x = mat[0][j];
		mat[0][j] = mat[j][3];
		mat[j][3] = mat[3][3-j];
		mat[3][3-j] = mat[3-j][0];
		mat[3-j][0] = x;
	}
	x = mat[1][2];						//for inner square[2]*[2]
	mat[1][2] = mat[2][2];
	mat[2][2] = mat[2][1];
	mat[2][1] = mat[1][1];
	mat[1][1] = x;
}

void flipH(int mat [4] [4]){
	int i, j, x;
	for(i=0; i<4; i++){
		for(j=0; j<2; j++){
			x = mat[i][j];
			mat[i][j] = mat[i][3-j];
			mat[i][3-j] = x;
		}
	}
}											//cycles might be adopted for square matrix of any size

void transposMain(int mat [4] [4]){
	int i, j, x;
	for(i=0; i<3; i++){
		for(j=i+1; j<4; j++){
			x = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = x;
		}
	}
}											//cycles might be adopted for square matrix of any size