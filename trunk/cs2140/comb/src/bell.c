#include <errno.h>
#include <bell.h>

int bell_errno = 0;

int _bell(int n1, int n2, comb_t *ans)
{
    // missing logic
    return 0;
}


int bell(int n, comb_t *ans)
{
    return _bell(n, n, ans);
}


