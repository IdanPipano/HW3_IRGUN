/********************************************************
 * Kernels to be optimized
 ********************************************************/

#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "beans--------",              /* Team name */

    "Harry Potter",     /* First member full name */
    "potter@nowhere.edu",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    naive_rotate(dim, src, dst);
}


void rotate_version1(int dim, pixel *src, pixel *dst)
{
    register int i, j;
    register int temp1 = 0;
    register int dim_squared = dim*dim;
    register int temp2;


    for (i = 0; i < dim; i++)
    {
        temp2 = dim_squared - dim +i;
        for (j = 0; j < dim; j++)
        {
            dst[temp2] = src[temp1];
            temp2 -= dim;
            temp1++;

        }

    }
}


void rotate_version2(int dim, pixel *src, pixel *dst)
{
    register int i, j=0;
    register int temp1 = 0;
    register int dim_squared = dim*dim;
    register int temp2;


    for (i = 0; i < dim; i++)
    {
        j+=dim;
        temp2 = dim_squared - dim +i;
        for (; temp1 < j; )
        {
            dst[temp2] = src[temp1];
            temp2 -= dim;
            temp1++;
        }

    }
}



void rotate_version3(int dim, pixel *src, pixel *dst)
{
    register int i, j;
    register int dim_divide_by_2 = dim>>1;
    register int dim_squared = dim*dim;
    register int j_dim;
    register int i_dim = -dim;
    register int temp2;
    for (i = 0; i < dim_divide_by_2; i++)
    {
        i_dim += dim;
        temp2 = dim-i-1;
        j_dim = 0-dim;
        for (j = 0; j < temp2; j++)
        {
            j_dim += dim;
            dst[i_dim+j] = src[j_dim+ dim-1-i];
            dst[j_dim+ dim-i-1] = src[dim_squared-i_dim-1-j];
            dst[dim_squared-i_dim-1-j] = src[dim_squared-dim-j_dim + i];
            dst[dim_squared-dim-j_dim + i] = src[i_dim+ j];
        }

    }
}


/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);
    add_rotate_function(&rotate_version1 , "works with about speedup = 2");
    add_rotate_function(&rotate_version2 , "version2-- works with about speedup = 2");
    add_rotate_function(&rotate_version3 , "version3");

    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}


