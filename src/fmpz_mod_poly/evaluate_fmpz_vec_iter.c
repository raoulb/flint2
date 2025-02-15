/*
    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2012 William Hart

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fmpz_mod.h"
#include "fmpz_mod_poly.h"

void
_fmpz_mod_poly_evaluate_fmpz_vec_iter(fmpz * ys, const fmpz * coeffs, slong len,
    const fmpz * xs, slong n, const fmpz_mod_ctx_t ctx)
{
    slong i;
    for (i = 0; i < n; i++)
        _fmpz_mod_poly_evaluate_fmpz(ys + i, coeffs, len, xs + i, ctx);
}

void fmpz_mod_poly_evaluate_fmpz_vec_iter(fmpz * ys, const fmpz_mod_poly_t poly,
                           const fmpz * xs, slong n, const fmpz_mod_ctx_t ctx)
{
    _fmpz_mod_poly_evaluate_fmpz_vec_iter(ys, poly->coeffs,
                               poly->length, xs, n, ctx);
}
