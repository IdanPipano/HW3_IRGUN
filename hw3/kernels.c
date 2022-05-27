/********************************************************
 * Kernels to be optimized
 ********************************************************/

#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
        "beans--------",              /* Team name */

        "Gur Keinan",     /* First member full name */
        "Gur.Keinan@campus.technion.ac.il",  /* First member email address */

        "Idan Pipano",                   /* Second member full name (leave blank if none) */
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

void naive_rotate(int dim, pixel *src, pixel *dst) {
    int i, j;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[RIDX(dim - 1 - j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";

void rotate(int dim, pixel *src, pixel *dst) {
    naive_rotate(dim, src, dst);
}


void rotate_version1(int dim, pixel *src, pixel *dst) {
    register int i, j;
    register int temp1 = 0;
    register int dim_squared_minus_dim = dim * dim - dim;
    register int temp2;


    for (i = 0; i < dim; i++) {
        temp2 = dim_squared_minus_dim + i;
        for (j = 0; j < dim; j++) {
            dst[temp2] = src[temp1];
            temp2 -= dim;
            temp1++;

        }

    }
}


void rotate_version2(int dim, pixel *src, pixel *dst) {
    register int i = dim - 1, j;
    register pixel *src1 = src;
    register int register_dim = dim;
    register pixel *dim_squared_minus_dim = dst + dim * dim - 1;
    register int dim_times_2 = dim + dim;
    register int dim_times_3 = dim + dim + dim;
    register pixel *dest1;


    for (; i >= 0; --i) {
        j = register_dim - 1;
        dest1 = dim_squared_minus_dim - i;

        for (; j > 1; j -= 3) {
            *dest1 = *src1;
            *(dest1 - register_dim) = *(src1 + 1);
            *(dest1 - dim_times_2) = *(src1 + 2);
            dest1 -= dim_times_3;
            src1 += 3;
        }

        for (; j >= 0; j--) {
            *dest1 = *src1;
            dest1 -= register_dim;
            src1++;
        }


    }
}


void rotate_version_Doron(int dim, pixel *src, pixel *dst)
{
    register int i, j, x, y;
    register int dim1 = dim;

    for (i = 0; i < dim1; i+=16)
        for (j = 0; j < dim1; j++) {
            x = RIDX(dim1 - 1 - j, i, dim1);
            y = RIDX(i, j, dim1);
            dst[x] = src[y];
            y += dim1;
            dst[x+1] = src[y];
            y += dim1;
            dst[x+2] = src[y];
            y += dim1;
            dst[x+3] = src[y];
            y += dim1;
            dst[x+4] = src[y];
            y += dim1;
            dst[x+5] = src[y];
            y += dim1;
            dst[x+6] = src[y];
            y += dim1;
            dst[x+7] = src[y];
            y += dim1;
            dst[x+8] = src[y];
            y += dim1;
            dst[x+9] = src[y];
            y += dim1;
            dst[x+10] = src[y];
            y += dim1;
            dst[x+11] = src[y];
            y += dim1;
            dst[x+12] = src[y];
            y += dim1;
            dst[x+13] = src[y];
            y += dim1;
            dst[x+14] = src[y];
            y += dim1;
            dst[x+15] = src[y];
        }
}


void rotate_version_Doron_with_improvements(int dim, pixel *src, pixel *dst)
{
    int i, j, x, y;
    int dim1 = dim;
    int temp1 = dim*(-12) +1;
    int temp2 = dim*dim+16;
    int dimX2 = 2*dim1;
    int dimX3 = 3*dim1;

    x = temp2-dim1-16;
    y = 0;

    for (i = 0; i < dim1; i+=16)
    {
        y = i*dim;
        for (j = 0; j < dim1; j++) {
            dst[x] = src[y];
            dst[x+1] = src[y+dim1];
            dst[x+2] = src[y+dimX2];
            y += dimX3;
            dst[x+3] = src[y];
            dst[x+4] = src[y+dim1];
            dst[x+5] = src[y+dimX2];
            y += dimX3;
            dst[x+6] = src[y];
            dst[x+7] = src[y+dim1];
            dst[x+8] = src[y+dimX2];
            y += dimX3;
            dst[x+9] = src[y];
            dst[x+10] = src[y+dim1];
            dst[x+11] = src[y+dimX2];
            y += dimX3;
            dst[x+12] = src[y];
            dst[x+13] = src[y+dim1];
            dst[x+14] = src[y+dimX2];
            dst[x+15] = src[y+dimX3];
            x -= dim1;
            y += temp1;

        }
        x += temp2;


}
}



void rotate_version3(int dim, pixel *src, pixel *dst) {
    register int i = dim - 1, j;
    register pixel *src1 = src;
    register int register_dim = dim;
    register pixel *dim_squared_minus_dim = dst + dim * dim - 1;
    register pixel *dest1;


    for (; i >= 0; --i) {
        j = register_dim - 1;
        dest1 = dim_squared_minus_dim - i;

        for (; j > 1; j -= 16) {
            *dest1 = *src1;
            dest1 -= register_dim;
            *dest1 = *(src1+1);
            dest1 -= register_dim;
            *dest1 = *(src1+2);
            dest1 -= register_dim;
            *dest1 = *(src1+3);
            dest1 -= register_dim;
            *dest1 = *(src1+4);
            dest1 -= register_dim;
            *dest1 = *(src1+5);
            dest1 -= register_dim;
            *dest1 = *(src1+6);
            dest1 -= register_dim;
            *dest1 = *(src1+7);
            dest1 -= register_dim;
            *dest1 = *(src1+8);
            dest1 -= register_dim;
            *dest1 = *(src1+9);
            dest1 -= register_dim;
            *dest1 = *(src1+10);
            dest1 -= register_dim;
            *dest1 = *(src1+11);
            dest1 -= register_dim;
            *dest1 = *(src1+12);
            dest1 -= register_dim;
            *dest1 = *(src1+13);
            dest1 -= register_dim;
            *dest1 = *(src1+14);
            dest1 -= register_dim;
            *dest1 = *(src1+15);
            dest1 -= register_dim;
            src1 += 16;
        }

        for (; j >= 0; j--) {
            *dest1 = *src1;
            dest1 -= register_dim;
            src1++;
        }


    }
}



void rotate_version4(int dim, pixel *src, pixel *dst) {
    register pixel *limit = src;
    register int i;
    register int dim_squared_minus_dim = dim * dim - dim;
    register int temp2;
    register int dim2 = 2 * dim;
    register int dim3 = dim2 + dim;


    for (i = 0; i < dim; i++) {
        limit += dim;
        temp2 = dim_squared_minus_dim + i;
        pixel *limit_minus_3 = limit - 3;
        for (; src < limit_minus_3;) {
            *(dst + temp2) = *src;
            *(dst + temp2 - dim) = *(src + 1);
            *(dst + temp2 - dim2) = *(src + 2);
            temp2 -= dim3;
            src += 3;
        }
        for (; src < limit;) {
            dst[temp2] = *src;
            src++;
            temp2 -= dim;
        }

    }
}


void rotate_Itamar(int dim, pixel *src, pixel *dst) {
    int i, j;
    if (dim > 300) {
        int data_src, data_dst;

        for (i = 0; i < dim; i += 16) {
            for (j = 0; j < dim; ++j) {
                data_src = dim * (dim - 1 - j) + i;
                data_dst = dim * i + j;

                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
                ++ data_src;
                data_dst += dim;
                dst[data_src] = src[data_dst];
            }
        }
    }
    else {
        pixel *dst_end = dst + dim * dim;

        pixel *data_dest;
        pixel *data_src = src;

        for (i = dim; i >= 1; --i) {
            j = dim - 1;
            data_dest = dst_end - i;
            for (; j >= 0; --j) {
                *data_dest = *(data_src);
                data_dest -= dim;
                ++data_src;
            }
        }
    }
}

void rotate_num(int dim, pixel *src, pixel *dst)
{
    int i, j, data_src, data_dst;

    for (i = 0; i < dim; i += 16) {
        for (j = 0; j < dim; ++j) {
            data_src = dim * (dim - 1 - j) + i;
            data_dst = dim * i + j;

            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
            ++ data_src;
            data_dst += dim;
            dst[data_src] = src[data_dst];
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

void register_rotate_functions() {
    add_rotate_function(&naive_rotate, naive_rotate_descr);
    add_rotate_function(&rotate, rotate_descr);
    //add_rotate_function(&rotate_version1 , "version1- works with about speedup = 2");
    //add_rotate_function(&rotate_version2 , "version2- works with about speedup = 2");
    //add_rotate_function(&rotate_version3 , "version3");
    //add_rotate_function(&rotate_version4 , "version4");
    //add_rotate_function(&rotate_Itamar , "version_Itamar");
    //add_rotate_function(&rotate_num , "version_Itamar");


    //add_rotate_function(&rotate_version_Doron , "version_Doron");
    add_rotate_function(&rotate_version_Doron_with_improvements , "version_gur+doron");

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
static void initialize_pixel_sum(pixel_sum *sum) {
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) {
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) {
    current_pixel->red = (unsigned short) (sum.red / sum.num);
    current_pixel->green = (unsigned short) (sum.green / sum.num);
    current_pixel->blue = (unsigned short) (sum.blue / sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) {
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for (ii = max(i - 1, 0); ii <= min(i + 1, dim - 1); ii++)
        for (jj = max(j - 1, 0); jj <= min(j + 1, dim - 1); jj++)
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

void naive_smooth(int dim, pixel *src, pixel *dst) {
    int i, j;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}


