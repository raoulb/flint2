/*
    Copyright (C) 2010 William Hart

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "test_helpers.h"
#include "ulong_extras.h"
#include "nmod_poly.h"

TEST_FUNCTION_START(nmod_poly_mul_KS)
{
    int i, result;

    /* Check aliasing of a and b */
    for (i = 0; i < 200 * flint_test_multiplier(); i++)
    {
        nmod_poly_t a, b, c;
        mp_limb_t n = n_randtest_not_zero(state);

        nmod_poly_init(a, n);
        nmod_poly_init(b, n);
        nmod_poly_init(c, n);
        nmod_poly_randtest(b, state, n_randint(state, 50));
        nmod_poly_randtest(c, state, n_randint(state, 50));

        nmod_poly_mul_KS(a, b, c, 0);
        nmod_poly_mul_KS(b, b, c, 0);

        result = (nmod_poly_equal(a, b));
        if (!result)
        {
            flint_printf("FAIL:\n");
            nmod_poly_print(a), flint_printf("\n\n");
            nmod_poly_print(b), flint_printf("\n\n");
            fflush(stdout);
            flint_abort();
        }

        nmod_poly_clear(a);
        nmod_poly_clear(b);
        nmod_poly_clear(c);
    }

    /* Check aliasing of a and c */
    for (i = 0; i < 200 * flint_test_multiplier(); i++)
    {
        nmod_poly_t a, b, c;
        mp_limb_t n = n_randtest_not_zero(state);

        nmod_poly_init(a, n);
        nmod_poly_init(b, n);
        nmod_poly_init(c, n);
        nmod_poly_randtest(b, state, n_randint(state, 50));
        nmod_poly_randtest(c, state, n_randint(state, 50));

        nmod_poly_mul_KS(a, b, c, 0);
        nmod_poly_mul_KS(c, b, c, 0);

        result = (nmod_poly_equal(a, c));
        if (!result)
        {
            flint_printf("FAIL:\n");
            nmod_poly_print(a), flint_printf("\n\n");
            nmod_poly_print(c), flint_printf("\n\n");
            fflush(stdout);
            flint_abort();
        }

        nmod_poly_clear(a);
        nmod_poly_clear(b);
        nmod_poly_clear(c);
    }

    /* Compare with mul_classical */
    for (i = 0; i < 200 * flint_test_multiplier(); i++)
    {
        nmod_poly_t a1, a2, b, c;
        mp_limb_t n = n_randtest_not_zero(state);

        nmod_poly_init(a1, n);
        nmod_poly_init(a2, n);
        nmod_poly_init(b, n);
        nmod_poly_init(c, n);
        nmod_poly_randtest(b, state, n_randint(state, 50));
        nmod_poly_randtest(c, state, n_randint(state, 50));

        nmod_poly_mul_classical(a1, b, c);
        nmod_poly_mul_KS(a2, b, c, 0);

        result = (nmod_poly_equal(a1, a2));
        if (!result)
        {
            flint_printf("FAIL:\n");
            nmod_poly_print(a1), flint_printf("\n\n");
            nmod_poly_print(a2), flint_printf("\n\n");
            fflush(stdout);
            flint_abort();
        }

        nmod_poly_clear(a1);
        nmod_poly_clear(a2);
        nmod_poly_clear(b);
        nmod_poly_clear(c);
    }

    TEST_FUNCTION_END;
}
