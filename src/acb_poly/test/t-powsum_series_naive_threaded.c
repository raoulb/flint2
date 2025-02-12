/*
    Copyright (C) 2013 Fredrik Johansson

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb_poly.h"

int main(void)
{
    slong iter;
    flint_rand_t state;

    flint_printf("powsum_series_naive_threaded....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 2000 * 0.1 * flint_test_multiplier(); iter++)
    {
        acb_t s, a, q;
        acb_ptr z1, z2;
        slong i, n, len, prec;

        acb_init(s);
        acb_init(a);
        acb_init(q);

        if (n_randint(state, 2))
        {
            acb_randtest(s, state, 1 + n_randint(state, 200), 3);
        }
        else
        {
            arb_set_ui(acb_realref(s), 1);
            arb_mul_2exp_si(acb_realref(s), acb_realref(s), -1);
            arb_randtest(acb_imagref(s), state, 1 + n_randint(state, 200), 4);
        }

        if (n_randint(state, 2))
            acb_one(a);
        else
            acb_randtest(a, state, 1 + n_randint(state, 200), 3);

        if (n_randint(state, 2))
            acb_one(q);
        else
            acb_randtest(q, state, 1 + n_randint(state, 200), 3);

        prec = 2 + n_randint(state, 200);
        n = n_randint(state, 100);
        len = 1 + n_randint(state, 10);

        z1 = _acb_vec_init(len);
        z2 = _acb_vec_init(len);

        _acb_poly_powsum_series_naive(z1, s, a, q, n, len, prec);
        flint_set_num_threads(1 + n_randint(state, 3));
        _acb_poly_powsum_series_naive_threaded(z2, s, a, q, n, len, prec);

        for (i = 0; i < len; i++)
        {
            if (!acb_overlaps(z1 + i, z2 + i))
            {
                flint_printf("FAIL: overlap\n\n");
                flint_printf("iter = %wd\n", iter);
                flint_printf("n = %wd, prec = %wd, len = %wd, i = %wd\n\n", n, prec, len, i);
                flint_printf("s = "); acb_printd(s, prec / 3.33); flint_printf("\n\n");
                flint_printf("a = "); acb_printd(a, prec / 3.33); flint_printf("\n\n");
                flint_printf("q = "); acb_printd(q, prec / 3.33); flint_printf("\n\n");
                flint_printf("z1 = "); acb_printd(z1 + i, prec / 3.33); flint_printf("\n\n");
                flint_printf("z2 = "); acb_printd(z2 + i, prec / 3.33); flint_printf("\n\n");
                flint_abort();
            }
        }

        acb_clear(a);
        acb_clear(s);
        acb_clear(q);
        _acb_vec_clear(z1, len);
        _acb_vec_clear(z2, len);
    }

    flint_randclear(state);
    flint_cleanup_master();
    flint_printf("PASS\n");
    return 0;
}
