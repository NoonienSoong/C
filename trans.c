//
//  trans.c
//  
//
//  Created by Nicholas  Jackson on 11/9/14.
//  netID naj273
//
//
/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    
    int Bsize = (M==32)?8:4;
    int block2=23,set,lines,j,i,temp;
    if(M == 32){
        
        for(set = 0; set < N;set += Bsize){
            for(lines = 0; lines < M; lines += Bsize){
                for(i = set; i < set + Bsize; i++){
                    for(j = lines; j < lines + Bsize; ++j){
                        if(j == i){
                            
                            temp = A[i][j];
                            
                                                   }
                        else{
                            B[j][i] = A[i][j];

                        }
                    }
                        if(set == lines){
                        B[i][i] = temp;
                        
                    }
                }
            }
        }
    }
    
   
    if(M == 64){

        for (lines = 0; lines < M; lines += Bsize) {
	    for (set = 0; set < N; set += Bsize) {
		for (i = set; i < set + Bsize; i++) {
		    for (j = lines; j < lines + Bsize; j++) {

			if (i == j)
			    temp = A[i][j];
			else {
			    
			    B[j][i] = A[i][j];
			  	
			}
		    }
		    
		    if (set == lines)
			B[i][i] = temp;
		    
		}

	    }
	}

    }


   
    if(M == 61){
        
        for(set = 0; set < N; set+= block2){
            for(lines = 0; lines < M; lines+=block2){
                for(i = set; i < set+block2; i++){
                    for(j = lines; j < lines+block2; ++j){
                        if(i > 66 || j > 60){
                            continue;
                        }
                        else{
                            B[j][i] = A[i][j];
                            
                        }
                    }
                }
            }
        }
    }
    
}
    
    
   
    


/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
    
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 
    
    /* Register any additional transpose functions */
    //registerTransFunction(trans, trans_desc); 
    
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;
    
     for (i = 0; i < N; i++) {
     for (j = 0; j < M; ++j) {
     if (A[i][j] != B[j][i]) {
     return 0;
     }
     }
}
     
    return 1;
}

