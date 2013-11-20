/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Sebastian Pancratz
    Copyright (C) 2012 Andres Goens
    Copyright (C) 2013 Mike Hansen

******************************************************************************/


#ifdef T

#include "templates.h"

#include <stdio.h>
#include <stdlib.h>

#include "ulong_extras.h"
#include "long_extras.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;

    flint_printf("pow... ");
    fflush(stdout);

    flint_randinit(state);

    /* Check aliasing: a = a^e */
    for (i = 0; i < 1000; i++)
    {
        TEMPLATE(T, ctx_t) ctx;
        TEMPLATE(T, t) a, b;
        fmpz_t e;

        TEMPLATE(T, ctx_randtest)(ctx, state);

        TEMPLATE(T, init)(a, ctx);
        TEMPLATE(T, init)(b, ctx);
        fmpz_init(e);

        TEMPLATE(T, randtest)(a, state, ctx);
        fmpz_randtest_unsigned(e, state, 6);

        TEMPLATE(T, pow)(b, a, e, ctx);
        TEMPLATE(T, pow)(a, a, e, ctx);

        result = (TEMPLATE(T, equal)(a, b, ctx));
        if (!result)
        {
            flint_printf("FAIL (alias):\n\n");
            flint_printf("a = "), TEMPLATE(T, print_pretty)(a, ctx), flint_printf("\n");
            flint_printf("b = "), TEMPLATE(T, print_pretty)(b, ctx), flint_printf("\n");
            abort();
        }

        TEMPLATE(T, clear)(a, ctx);
        TEMPLATE(T, clear)(b, ctx);
        fmpz_clear(e);

        TEMPLATE(T, ctx_clear)(ctx);
    }

    /* Compare with multiplication, for integral values */
    for (i = 0; i < 1000; i++)
    {
        TEMPLATE(T, ctx_t) ctx;

        TEMPLATE(T, t) a, b, c;
        fmpz_t e, f;

        TEMPLATE(T, ctx_randtest)(ctx, state);
        
        TEMPLATE(T, init)(a, ctx);
        TEMPLATE(T, init)(b, ctx);
        TEMPLATE(T, init)(c, ctx);
        fmpz_init(f);
        fmpz_init(e);

        TEMPLATE(T, randtest)(a, state, ctx);
        fmpz_randtest_unsigned(e, state, 6);

        TEMPLATE(T, pow)(b, a, e, ctx);
        TEMPLATE(T, one)(c, ctx);
        for (fmpz_one(f); fmpz_cmp(f, e) <= 0; fmpz_add_ui(f, f, 1))
        {
            TEMPLATE(T, mul)(c, c, a, ctx);
        }

        result = (TEMPLATE(T, equal)(b, c, ctx));
        if (!result)
        {
            flint_printf("FAIL (cmp with mul):\n\n");
            flint_printf("a = "), TEMPLATE(T, print_pretty)(a, ctx), flint_printf("\n");
            flint_printf("b = "), TEMPLATE(T, print_pretty)(b, ctx), flint_printf("\n");
            flint_printf("c = "), TEMPLATE(T, print_pretty)(b, ctx), flint_printf("\n");
            flint_printf("e = "), fmpz_print(e), flint_printf("\n");
            abort();
        }

        TEMPLATE(T, clear)(a, ctx);
        TEMPLATE(T, clear)(b, ctx);
        TEMPLATE(T, clear)(c, ctx);
        fmpz_clear(e);
        fmpz_clear(f);

        TEMPLATE(T, ctx_clear)(ctx);
    }

    flint_randclear(state);
    _fmpz_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}



#endif