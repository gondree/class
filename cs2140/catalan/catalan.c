/* ----------------------------------------------------------------------------
 * A simple program, that may contain memory-related errors.
 *
 * Contains a few functions for doing dynamic programming problems
 * related to computing Catalan numbers. The program exercises our functions' 
 * logic in various ways.
 * ----------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// Pretend that FOREVER is a very large number ---
//  our methods, and the trial logic used to invoke them,
//  should be appropriate for long-lived processes
#define FOREVER 1

// Catalan number type
typedef int catalan_t;

// Holds the dynamic programming state for computing Catalan numbers
typedef struct {
    int len;
    catalan_t *buf;
} catalan_work_t;

// ----------------------------------------------------------------------------
// Support Functions

//
// This function implements the recurrence for the Catalan numbers
// suitable for use in dynamic programming problems.
//
// Computes the (n+1)-th Catalan number and places it in c[n].
//  (The first Catalan number, C_0, is stored in c[0]).
// Assumes c[0 ... n-1] holds the previous Catalan numbers.
//
// Parameters:
//   n - the Catalan value C_n to be computed
//   c - an array holding the previous Catalan numbers
//   len - length of the array
//
// Return values:
//  0 on success
//  -1 on error, and errno is set.
//
int catalan(int n, catalan_t *c, int len)
{
    int i;

    if (!c || (len < 0) || (n > len - 1)) {
        errno = EINVAL;
        return -1;
    }

    if (n == 0) {
        c[n] = 1;
    } else if (n > 0) {
        // c[n] = SUM_{i=0}^{n-1} ( c[i] * c[n-1-i] )
        c[n] = 0;
        for (i = 0; i < n; i++) {
            c[n] += c[i] * c[n-1-i];
        }
    } else {
        errno = EINVAL;
        return -1;
    } 
    return 0;
} // catalan


//
// Fills the output buffer with the first n+1 Catalan numbers
//  (The first Catalan number is C_0).
// If the user-supplied buffer is not large enough, it is grown.
//
// Parameters:
//  n - the greatest Catalan number to compute: C_0, ..., C_n
//  ptr - pointer to the user's catalan_work_t "work buffer"
//
// Return values:
//  0 on success
//  -1 on error, and errno is set
//
int catalan_fill(int n, catalan_work_t *ptr)
{
    int i;

    if (!ptr || (ptr->len < 0)) {
        errno = EINVAL;
        return -1;
    }

    if (!(ptr->buf) || (n > ptr->len-1)) {
        // if an adequate buffer was not given, then grow it
        ptr->buf = (catalan_t *) realloc(ptr->buf, (n+1)*sizeof(catalan_t));
        if (!(ptr->buf)) {
            perror("realloc");
            return -1;
        }
        ptr->len = n+1;
    }
    for(i = 0; i <= n; i++) {
        if (catalan(i, ptr->buf, ptr->len)) {
            return -1;
        }
    }
    return 0;
} // catalan_fill


//
// Returns an array with the first n+1 Catalan numbers
//
// Parameters:
//  n - the greatest Catalan number to compute: C_0, ..., C_n
//
// Return values:
//  a pointer to the list of answers on success
//  NULL on error
//
catalan_t *catalan_answers(int n)
{
    catalan_work_t ans;
    if (n < 0) {
        return NULL;
    }
    ans.buf = NULL;
    ans.len = 0;
    if (catalan_fill(n, &ans)) {
        return NULL;
    }
    return ans.buf;
}

//
// Prints a simple message related to Catalan numbers
//
void printc(char *message, int n, catalan_t x)
{
    printf("%s%d is %d\n", message, n, x);
}


// ----------------------------------------------------------------------------
// Calculates C_10, the number of Dyck words of length 20
//
void test_1(void)
{
    int i;
    const int total = 10;
    catalan_t *ans;

    ans = (catalan_t *) malloc(total * sizeof(catalan_t));
    
    for (i = 0; i < total; i++) {
        catalan(i, ans, total);
    }
    printc("The number of Dyck words of length ", 2*total, ans[total]);
    free(ans);
}


// ----------------------------------------------------------------------------
// Prints C_20, the 21st Catalan number
//
void test_2(void)
{
    catalan_work_t ans;
    const int total = 20;
    
    if (catalan_fill(total, &ans)) {
        exit(-1);
    }
    printc("Catalan number C_", ans.len-1, ans.buf[ans.len-1]);

    free(ans.buf);
}


// ----------------------------------------------------------------------------
// Prints C_20, the 21st Catalan number
//
void test_3(void)
{
    const int total = 20;
    catalan_t *i;
    catalan_work_t *ans;
    
    ans = (catalan_work_t *) malloc(sizeof(catalan_work_t));
    i = (catalan_t *) malloc(total*sizeof(catalan_t));
    ans->buf = i;
    free(i);
    ans->len = total;

    catalan_fill(total, ans);
    printc("Catalan number C_", ans->len-1, ans->buf[ans->len-1]);

    free(ans);
}


int main(int argc, char**argv)
{
    int i, test_number;

    if (argc != 2) {
        fprintf(stderr, "Syntax:\n\t%s <test-number>\n", argv[0]);
        return -1;
    }
    test_number = atoi(argv[1]);
    srand(getpid());

    for (i = 0; i < FOREVER; i++) {
        switch (test_number) {
            case 1:
                test_1();
                break;
            case 2:
                test_2();
                break;
            case 3:
                test_3();
                break;
            default:
                printf("\tInvalid test requested.\n");
                return -1;
        }
    }
    return 0;
}
