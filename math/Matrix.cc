#include "Matrix.h"
#include <assert.h>
Matrix::Matrix()
{
    //cs *A=cs_spalloc(1,1,1,1,1);
    //cout<<"Matrix Created"<<endl;
}

Matrix::Matrix(int a,int b){
    A=cs_spalloc(a,b,1,1,1);
}

void Matrix::triple(int col,int row,double value){
    int x=cs_entry(A,col,row,value);
    if(!x) cout<<"error"<<endl;
}

void Matrix::CCS(){
    cs* AT;
    AT=cs_compress(A);
    cs_spfree(A);
    A=AT;    
}

int Matrix::density(){
    CS_INT m,n,*Ap;
    m = A->m ; n = A->n ; Ap = A->p;
    return (Ap[n]/m/n);
}

css* Matrix::amd(){
    css *r;
    CS_INT order=1;
    r=cs_schol(order,this->A);
    return r;
}

int Matrix::printMatrix(int brief){
    CS_INT p, j, m, n, nzmax, nz, *Ap, *Ai ;
    CS_ENTRY *Ax ;
    if (!A) { printf ("(null)\n") ; return (0) ; }
    m = A->m ; n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    nzmax = A->nzmax ; nz = A->nz ;
    printf ("CXSparse Version %d.%d.%d, %s.  %s\n", CS_VER, CS_SUBVER,
        CS_SUBSUB, CS_DATE, CS_COPYRIGHT) ;
    if (nz < 0)
    {
        printf ("%g-by-%g, nzmax: %g nnz: %g, 1-norm: %g\n", (double) m,
            (double) n, (double) nzmax, (double) (Ap [n]), cs_norm (A)) ;
        for (j = 0 ; j < n ; j++)
        {
            printf ("    col %g : locations %g to %g\n", (double) j, 
                (double) (Ap [j]), (double) (Ap [j+1]-1)) ;
            for (p = Ap [j] ; p < Ap [j+1] ; p++)
            {
                printf ("      %g : ", (double) (Ai [p])) ;
                #ifdef CS_COMPLEX
                    printf ("(%g, %g)\n",
                             Ax ? CS_REAL (Ax [p]) : 1, Ax ? CS_IMAG (Ax [p]) : 0) ;
                #else
                    printf ("%.18lf\n", Ax ? Ax [p] : 1) ;
                #endif
                    if (brief && p > 20) { printf ("  ...\n") ; return (1) ; }
            }
        }
    }
    else
    {
        printf ("triplet: %g-by-%g, nzmax: %g nnz: %g\n", (double) m,
            (double) n, (double) nzmax, (double) nz) ;
        for (p = 0 ; p < nz ; p++)
        {

            printf ("    %g %g : ", (double) (Ai [p]), (double) (Ap [p])) ;
            #ifdef CS_COMPLEX
                printf ("(%g, %g)\n",
                        Ax ? CS_REAL (Ax [p]) : 1, Ax ? CS_IMAG (Ax [p]) : 0) ;
            #else
                printf ("%g\n", Ax ? Ax [p] : 1) ;
            #endif
                if (brief && p > 20) { printf ("  ...\n") ; return (1) ; }
        }
    }
    return (1) ;
}


Matrix::~Matrix()
{
   // free (A->p);
   // cout<<"freed"<<endl;
    //assert(A=!NULL);
    //cout << "Matrix Object is being deleted" << endl;
    if(A!=NULL)          cs_spfree(A);
    //free(A->p);
   // free(A->i);
   // free(A->x);
    //free(A);
      //   cout<<"A do exist!!!!!!!"<<endl;
}