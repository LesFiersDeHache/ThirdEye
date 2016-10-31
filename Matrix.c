#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <err.h>
#include <time.h>

#define Uint unsigned int
#define Ulong unsigned long long

// STRUCT
typedef struct Mat {

    Uint x_len;
    Uint y_len;
    float* tab;

} Mat;

//INIT
Mat* newMat(Uint x_len, Uint y_len, float fill) {
    
    Mat* mat = malloc(sizeof(Mat));
    if (mat == NULL) { err(1, "Mat : newMat : malloc failed (1)"); }
    mat->x_len = x_len;
    mat->y_len = y_len;
    
    mat->tab = malloc(sizeof(float) * x_len * y_len);
    if (mat->tab == NULL) { err(1, "Mat : newMat : malloc failed (2)"); } 
    for (Ulong i = 0 ; i < x_len * y_len ; ++i) {
        mat->tab[i] = fill;
    }

    return mat;
}

Mat* newMatRandom(Uint x_len, Uint y_len, float mult, float add) {
    
    Mat* mat;
    //TODO
    return mat;
}

//FREE
void freeMat(Mat* mat) {
    free(mat);   
}

//GET/SET

//Get value
float getInMat(Mat* mat, Uint x, Uint y) {
    assert(x < mat->x_len && y < mat->y_len);
    return mat->tab[x * mat->y_len + y];
}

//Set value
void setInMat(Mat* mat, Uint x, Uint y, float new_value) {
    assert(x < mat->x_len && y < mat->y_len);
    mat->tab[x * mat->y_len + y] = new_value;
}

//Get len X
Uint getLenXMat(Mat* mat) {
    return mat->x_len;
}

//Get len Y
Uint getLenYMat(Mat* mat) {
    return mat->y_len;
}

//PRINT MAT

void printMat(Mat* mat) {
    
    printf("[");
    for ( Uint x = 0 ; x < mat->x_len ; ++x ) {
        if (x > 0) {
            printf(" ");
        }
        printf("[");
        for ( Uint y = 0 ; y < mat->y_len ; ++y ) {
            printf("%f, ", mat->tab[x * mat->y_len + y]);
        }
        printf("]");
        if (x < mat->x_len - 1) {
            printf("\n");
        }
    }
    printf("]\n\n");
}

//OPERATIONS

Mat* ope_Mcopy(Mat* mat) {
    
    Mat* mat_sol = newMat(mat->x_len, mat->y_len, 0.0);
    Ulong index = 0;

    for ( Uint x = 0 ; x < mat->x_len ; ++x ) {
        
        for ( Uint y = 0 ; y < mat->x_len ; ++x ) {
            
            index = x * mat->y_len + y;
            mat_sol->tab[index] = mat->tab[index];
        }
    }

    return mat_sol;
}

//Matrix + Real = Other matrix
Mat* ope_MpR(Mat* mat, float r) {

    Mat* mat_sol = newMat(mat->x_len, mat->y_len, 0.0);

    for ( Uint x = 0 ; x < mat->x_len ; ++x ) {
        
        for ( Uint y = 0 ; y < mat->y_len ; ++y ) {
            
            mat_sol->tab[x * mat->y_len + y] = mat->tab[x * mat->y_len + y] + r;
        }
    }
    return mat_sol;
}

//Matrix * Real = Other Matrix
Mat* ope_MxR(Mat* mat, float r) {
    
    Mat* mat_sol = newMat(mat->x_len, mat->y_len, 1.0);

    for ( Uint x = 0 ; x < mat->x_len ; ++x ) {
        
        for ( Uint y = 0 ; y < mat->y_len ; ++y ) {
            
            mat_sol->tab[x * mat->y_len + y] = mat->tab[x * mat->y_len + y] * r;
        }
    }
    return mat_sol;
}

//Matrix + Matrix = Other Matrix
Mat* ope_MpM(Mat* mat1, Mat* mat2) {

    assert(mat1->x_len == mat2->x_len && mat1->y_len == mat2->y_len);
    
    Mat* mat_sol = newMat(mat1->x_len, mat1->y_len, 0.0);

    for ( Uint x = 0 ; x < mat1->x_len ; ++x ) {
        
        for ( Uint y = 0 ; y < mat1->y_len ; ++y ) {
            Ulong index = x * mat1->y_len + y;
            mat_sol->tab[index] = mat1->tab[index] + mat2->tab[index];
        }
    }
    
    return mat_sol;
}

Mat* ope_MsM(Mat* mat1, Mat* mat2) {

    assert(mat1->x_len == mat2->x_len && mat1->y_len == mat2->y_len);
    
    Mat* mat_sol = newMat(mat1->x_len, mat1->y_len, 0.0);

    for ( Uint x = 0 ; x < mat1->x_len ; ++x ) {
        
        for ( Uint y = 0 ; y < mat1->y_len ; ++y ) {
            Ulong index = x * mat1->y_len + y;
            mat_sol->tab[index] = mat1->tab[index] - mat2->tab[index];
        }
    }
    
    return mat_sol;
}

//Matrix * Matrix = Other Matrix
Mat* ope_MxM(Mat* mat1, Mat* mat2) {

    assert(mat1->x_len == mat2->x_len && mat1->y_len == mat2->y_len);
    
    Mat* mat_sol = newMat(mat1->x_len, mat1->y_len, 1.0);

    for ( Uint x = 0 ; x < mat1->x_len ; ++x ) {
        
        for ( Uint y = 0 ; y < mat1->y_len ; ++y ) {
            Ulong index = x * mat1->y_len + y;
            mat_sol->tab[index] = mat1->tab[index] * mat2->tab[index];
        }
    }
    
    return mat_sol;
}

//static : do not touch
static float computeMult(Mat* mat1, Mat* mat2, Uint i, Uint j, Uint rmax) {

    float result = 0; 
    
    Uint max1 = mat1->y_len;
    Uint max2 = mat2->y_len;
    for ( Uint r = 0 ; r < rmax ; ++r ) {
        result += mat1->tab[i * max1 + r] * mat2->tab[r * max2 + j];
    }

    return result;
}

//Matrix dot Matrix = Other matrix
Mat* ope_MdotM(Mat* mat1, Mat* mat2) {

    Uint x_len1 = mat1->x_len;
    Uint x_len2 = mat2->x_len;
    Uint y_len1 = mat1->y_len;
    Uint y_len2 = mat2->y_len;

    assert(y_len1 == x_len2);
    
    Mat* mat_sol = newMat(x_len1, y_len2, 1.0);

    for ( Uint x = 0 ; x < x_len1 ; ++x ) {
        
        for ( Uint y = 0 ; y < y_len2 ; ++y ) {
            
            mat_sol->tab[x * y_len2+y] = computeMult(mat1, mat2, x, y, y_len1);
        }
    }

    return mat_sol;
}

//Vector (1 dimension matrix, horizontal or vertical) dot Matrix = Othr Matrix
Mat* ope_VdotM(Mat* vect, Mat* mat) {

    Mat* mat_sol;
    
    //TODO

    return mat_sol;
}

//Vector (1 dimension matrix, horizontal or vertical) dot Vector = Other Matrix
Mat* ope_VdotV(Mat* vect1, Mat* vect2) {
    
    Mat* mat_sol;
    //TODO
    return mat_sol;
}

//Matrix transpose = other matrix
Mat* ope_Mt(Mat* mat) {
    
    Mat* mat_sol = newMat(mat->y_len, mat->x_len, 0.0);
    Ulong indexIn = 0;
    Ulong indexOut = 0;

    for ( Uint x = 0 ; x < mat->x_len ; ++x ) {
         
        for ( Uint y = 0 ; y < mat->y_len ; ++y ) {
            
            indexIn = x * mat->y_len + y;
            indexOut = y * mat->x_len + x;
            mat_sol->tab[indexOut] = mat->tab[indexIn];
        }
    }
    return mat_sol;
}

Mat* ope_apply_sigmoid(Mat* mat) {
    
    Mat* mat_sol;
    //TODO
    return mat_sol;
}

Mat* ope_apply_deriv_sigmoid(Mat* mat) {

    Mat* mat_sol;
    //TODO
    return mat_sol;
}

//MAIN
/*
int main() 
{
    //TUTORIAL :

    Mat* mat = newMat(4, 6, 2.0);
    Mat* matp = newMat(4, 6, 3.0);
    Mat* matm1 = newMat(4, 2, 2.0);
    Mat* matm2 = newMat(2, 3, 3.0);
    warnx("Get something in a Mat : %f", getInMat(mat, 0, 0));
    setInMat(mat, 1, 2, 5.0);
    
    warnx("Init matrix");
    printMat(mat);

    warnx("Matrix + Real");
    printMat(ope_MpR(mat, 1.2));

    warnx("Matrix * Real");
    printMat(ope_MxR(mat, 2.0));

    warnx("Matrix + Matrix");
    printMat(ope_MpM(mat, matp));

    warnx("Matrix - Matrix");
    printMat(ope_MsM(mat, matp));

    warnx("Matrix * Matrix (1 per 1)");
    printMat(ope_MxM(mat, matp));

    warnx("Matrix dot Matrix (matrix multiplication)");
    printMat(ope_MdotM(matm1, matm2));

    warnx("Matrix transpose");
    printMat(ope_Mt(mat));

    warnx("Freeeee");
    freeMat(mat);

    return 0;
}*/
