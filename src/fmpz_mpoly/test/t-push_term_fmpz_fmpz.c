/*
    Copyright (C) 2018 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fmpz_mpoly.h"

int
main(void)
{
    slong i, j, k;
    FLINT_TEST_INIT(state);

    flint_printf("push_term_fmpz_fmpz....");
    fflush(stdout);

    /* Check pushback matches add */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        fmpz_mpoly_ctx_t ctx;
        fmpz_mpoly_t f1, f2, f3, m;
        flint_bitcnt_t coeff_bits, exp_bits;
        fmpz **exp, **exp2, *exp3;
        slong len, nvars;
        fmpz_t c, c2;

        fmpz_mpoly_ctx_init_rand(ctx, state, 10);
        fmpz_mpoly_init(f1, ctx);
        fmpz_mpoly_init(f2, ctx);
        fmpz_mpoly_init(f3, ctx);
        fmpz_mpoly_init(m, ctx);
        fmpz_init(c);
        fmpz_init(c2);

        nvars = fmpz_mpoly_ctx_nvars(ctx);

        exp = (fmpz **) flint_malloc(nvars*sizeof(fmpz *));
        exp2 = (fmpz **) flint_malloc(nvars*sizeof(fmpz *));
        exp3 = (fmpz *) flint_malloc(nvars*sizeof(fmpz));
        for (k = 0; k < nvars; k++)
        {
            exp[k] = (fmpz *) flint_malloc(sizeof(fmpz));
            fmpz_init(exp[k]);
            exp2[k] = (fmpz *) flint_malloc(sizeof(fmpz));
            fmpz_init(exp2[k]);
            fmpz_init(exp3+k);
        }

        len = n_randint(state, 20);
        coeff_bits = n_randint(state, 100) + 1;
        exp_bits = n_randint(state, 200);

        fmpz_mpoly_zero(f1, ctx);
        fmpz_mpoly_zero(f2, ctx);

        for (j = 0; j < len; j++)
        {
            /* get random term */
            fmpz_randtest(c, state, coeff_bits);
            for (k = 0; k < nvars; k++){
                fmpz_randtest_unsigned(exp[k], state, exp_bits);
                fmpz_set(exp3 + k, exp[k]);
            }

            /* add it to f1 */
            fmpz_mpoly_zero(m, ctx);
            fmpz_mpoly_set_coeff_fmpz_fmpz(m, c, exp, ctx);
            fmpz_mpoly_add(f1, f1, m, ctx);
            fmpz_mpoly_assert_canonical(f1, ctx);

            /* push it back on f2 */
            fmpz_mpoly_push_term_fmpz_fmpz(f2, c, exp, ctx);

            /* push it on f3 */
            fmpz_mpoly_push_term_fmpz_ffmpz(f3, c, exp3, ctx);

            /* make sure last term matches */
            fmpz_mpoly_get_term_coeff_fmpz(c2, f2, fmpz_mpoly_length(f2, ctx) - 1, ctx);
            fmpz_mpoly_get_term_exp_fmpz(exp2, f2, fmpz_mpoly_length(f2, ctx) - 1, ctx);
            if (!fmpz_equal(c, c2))
            {
                printf("FAIL\n");
                flint_printf("Check pushed coefficient matches\ni=%wd, j=%wd\n", i, j);
                fflush(stdout);
                flint_abort();
            }
            for (k = 0; k < nvars; k++)
            {
                if (!fmpz_equal(exp[k], exp2[k]))
                {
                    printf("FAIL\n");
                    flint_printf("Check pushed exponent matches\ni=%wd, j=%wd\n", i, j);
                    fflush(stdout);
                    flint_abort();
                }
            }
        }

        fmpz_mpoly_sort_terms(f2, ctx);
        fmpz_mpoly_combine_like_terms(f2, ctx);
        fmpz_mpoly_assert_canonical(f2, ctx);

        fmpz_mpoly_sort_terms(f3, ctx);
        fmpz_mpoly_combine_like_terms(f3, ctx);
        fmpz_mpoly_assert_canonical(f3, ctx);

        if (!fmpz_mpoly_equal(f1, f2, ctx))
        {
            printf("FAIL\n");
            flint_printf("Check pushed polynomial matches add\ni=%wd\n",i,j);
            fflush(stdout);
            flint_abort();
        }

        if (!fmpz_mpoly_equal(f1, f3, ctx)) {
            printf("FAIL\n");
            flint_printf(
                "Check pushed with ffmpz polynomial matches add\ni=%wd\n", i, j);
            fflush(stdout);
            flint_abort();
        }

        fmpz_clear(c2);
        fmpz_clear(c);
        fmpz_mpoly_clear(f1, ctx);
        fmpz_mpoly_clear(f2, ctx);
        fmpz_mpoly_clear(f3, ctx);
        fmpz_mpoly_clear(m, ctx);
        fmpz_mpoly_ctx_clear(ctx);

        for (k = 0; k < nvars; k++)
        {
            fmpz_clear(exp3 + k);
            fmpz_clear(exp2[k]);
            flint_free(exp2[k]);
            fmpz_clear(exp[k]);
            flint_free(exp[k]);
        }
        flint_free(exp3);
        flint_free(exp2);
        flint_free(exp);
    }

    FLINT_TEST_CLEANUP(state);

    flint_printf("PASS\n");
    return 0;
}

