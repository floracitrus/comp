#include <stdio.h>

/* TASK:
In 1917 we all learned how to print array: you go through each row and print each column.
We are in 1927 now and we are much cooler than that! It is time to learn the secret 1927 print.
SPIRAL PRINT!!! Yeap, that is exactly how cool kids do it B)

 * Given a 2D array, print it in spiral form. See the following examples.
 *
 * Input:
 *         1    2   3   4
 *         5    6   7   8
 *         9   10  11  12
 *         13  14  15  16
 *Output:
 *  1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10
 *
 *
 *Input:
 *      1   2   3   4  5   6
 *      7   8   9  10  11  12
 *      13  14  15 16  17  18
 *Output:
 *  1 2 3 4 5 6 12 18 17 16 15 14 13 7 8 9 10 11
 *
 */
void spiralPrint(int m, int n, int a[m][n]){

}

/* Driver program to test above functions */
int main()
{
    int a[3][6] = { {1,  2,  3,  4,  5,  6},
        	        {7,  8,  9,  10, 11, 12},
        	        {13, 14, 15, 16, 17, 18}
                   };

    spiralPrint(3, 6, a);
    /* OUTPUT: 1 2 3 4 5 6 12 18 17 16 15 14 13 7 8 9 10 11 */
    int b[4][4] = { {1, 2, 3, 4},
                    {5, 6, 7,  8},
                    {9, 10, 11, 12},
                    {13, 14, 15, 16}
                  };

    spiralPrint(4,4,b);

    /*Output: 1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10*/

    int c[1][4] = {{1,2,3,4}};
    spiralPrint(1,4,c);
    /*Output: 1 2 3 4*/
    printf("Just make sure your program has same results as under tests\n");
    return 0;
}


