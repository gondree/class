#include <errno.h>
#include <lucas.h>

int lucas_errno = 0;

// force mcheck to be an inline function, no matter how we compile
__attribute__((always_inline)) static inline int mcheck(comb_t a, comb_t b);


int lucas(linfo_t *gen, int n, comb_t *ans)
{
    // missing logic
    return 0;
}

static inline int mcheck(comb_t a, comb_t b) {
    // A check, following CERT INT32-C
    if ( (a > 0 && b > 0 && (a > COMB_MAX / b)) ||
         (a > 0 && b < 0 && (b < COMB_MIN / a)) ||
         (a < 0 && b > 0 && (a < COMB_MIN / b)) ||
         (a < 0 && b < 0 && (b < COMB_MAX / a)) ) {
        lucas_errno = EOVERFLOW;
        return -1;
    }
    return 0;
}
