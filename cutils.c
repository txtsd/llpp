#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/time.h>

#include "cutils.h"

void NORETURN_ATTR GCC_FMT_ATTR (2, 3) err (int exitcode, const char *fmt, ...)
{
    va_list ap;
    int savederrno = errno;

    va_start (ap, fmt);
    vfprintf (stdout, fmt, ap);
    va_end (ap);
    fprintf (stdout, ": %s\n", strerror (savederrno));
    fflush (stdout);
    _exit (exitcode);
}

void NORETURN_ATTR GCC_FMT_ATTR (2, 3) errx (int exitcode, const char *fmt, ...)
{
    va_list ap;

    va_start (ap, fmt);
    vfprintf (stdout, fmt, ap);
    va_end (ap);
    fputc ('\n', stdout);
    fflush (stdout);
    _exit (exitcode);
}

void *parse_pointer (const char *cap, const char *s)
{
    void *ptr;
    int ret = sscanf (s, "%" SCNxPTR, (uintptr_t *) &ptr);
    if (ret != 1) {
        errx (1, "%s: cannot parse pointer in `%s' (ret=%d)", cap, s, ret);
    }
    return ptr;
}

double now (void)
{
    struct timeval tv;
    gettimeofday (&tv, NULL);   /* gettimeofday shall always return zero */
    return tv.tv_sec + tv.tv_usec*1e-6;
}

void fmt_linkn (char *s, const char *c, unsigned int l, int n)
{
    div_t d;
    int sl = 0, nn = n;

    do { d = div (n, l); sl++; n = d.quot; } while (d.quot);
    for (int i = 0, n = nn; i < sl; ++i) {
        d = div (n, l);
        s[sl-1-i] = c[d.rem];
        n = d.quot;
    }
    s[sl] = 0;
}
