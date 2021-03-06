#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

//Just implemented Fractran

typedef struct frac_s *frac;
struct frac_s {
	int n, d;
	frac next;
};

frac parse(char *s);
int run(int v, char *s);

int main(void)
{
	run(2,	"1/2 2/1");

	return 0;
}

/* Input: A string in "17/91 78/85" format
 *
 * Output: The frac struct "queue" containing
 */
frac parse(char *s)
{
	int offset = 0;
	struct frac_s h = {0}, *p = &h;

	while (2 == sscanf(s, "%d/%d%n", &h.n, &h.d, &offset)) {
		s += offset;
		p = p->next = malloc(sizeof *p);
		*p = h;
		p->next = 0;
	}

	return h.next;
}

int run(int v, char *s)
{
	frac n, p = parse(s);
	mpz_t val;
	mpz_init_set_ui(val, v);

loop:	n = p;
	if (mpz_popcount(val) == 1)
		gmp_printf("\n[2^%d = %Zd]", mpz_scan1(val, 0), val);
	else
		gmp_printf(" %Zd", val);

	for (n = p; n; n = n->next) {
		// assuming the fractions are not reducible
		if (!mpz_divisible_ui_p(val, n->d)) continue;

		mpz_divexact_ui(val, val, n->d);
		mpz_mul_ui(val, val, n->n);
		goto loop;
	}

	gmp_printf("\nhalt: %Zd has no divisors\n", val);

	mpz_clear(val);
	while (p) {
		n = p->next;
		free(p);
		p = n;
	}

	return 0;
}
