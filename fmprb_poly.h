/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Fredrik Johansson

******************************************************************************/

#ifndef FMPRB_POLY_H
#define FMPRB_POLY_H

#include "fmprb.h"
#include "fmpz_poly.h"
#include "fmpq_poly.h"

typedef struct
{
    fmprb_struct * coeffs;
    long length;
    long alloc;
}
fmprb_poly_struct;

typedef fmprb_poly_struct fmprb_poly_t[1];


/* Memory management */

void fmprb_poly_init(fmprb_poly_t poly);

void fmprb_poly_init2(fmprb_poly_t poly, long len);

void fmprb_poly_clear(fmprb_poly_t poly);

void fmprb_poly_fit_length(fmprb_poly_t poly, long len);

void _fmprb_poly_set_length(fmprb_poly_t poly, long len);

void _fmprb_poly_normalise(fmprb_poly_t poly);

static __inline__ void
fmprb_poly_swap(fmprb_poly_t poly1, fmprb_poly_t poly2)
{
    fmprb_poly_struct t = *poly1;
    *poly1 = *poly2;
    *poly2 = t;
}

void fmprb_poly_set(fmprb_poly_t poly, const fmprb_poly_t src);

/* Basic manipulation */

static __inline__ long fmprb_poly_length(const fmprb_poly_t poly)
{
    return poly->length;
}

static __inline__ void fmprb_poly_zero(fmprb_poly_t poly)
{
    poly->length = 0;
}

static __inline__ void
fmprb_poly_one(fmprb_poly_t poly)
{
    fmprb_poly_fit_length(poly, 1);
    fmprb_one(poly->coeffs);
    _fmprb_poly_set_length(poly, 1);
}

/* Conversions */

void fmprb_poly_set_fmpz_poly(fmprb_poly_t poly, const fmpz_poly_t src, long prec);

void fmprb_poly_set_fmpq_poly(fmprb_poly_t poly, const fmpq_poly_t src, long prec);

/* Comparisons */

int fmprb_poly_contains_fmpq_poly(const fmprb_poly_t poly1, const fmpq_poly_t poly2);

int fmprb_poly_equal(const fmprb_poly_t A, const fmprb_poly_t B);

/* IO */

void fmprb_poly_printd(const fmprb_poly_t poly, long digits);

/* Arithmetic */

void fmprb_poly_add(fmprb_poly_t res, const fmprb_poly_t poly1,
              const fmprb_poly_t poly2, long prec);

void _fmprb_poly_mullow_ztrunc(fmprb_struct * res,
    const fmprb_struct * poly1, long len1,
    const fmprb_struct * poly2, long len2, long n, long prec);

void fmprb_poly_mullow_ztrunc(fmprb_poly_t res, const fmprb_poly_t poly1,
                                            const fmprb_poly_t poly2,
                                                long n, long prec);

void _fmprb_poly_mullow_classical(fmprb_struct * res,
    const fmprb_struct * poly1, long len1,
    const fmprb_struct * poly2, long len2, long n, long prec);

void fmprb_poly_mullow_classical(fmprb_poly_t res, const fmprb_poly_t poly1,
                                            const fmprb_poly_t poly2,
                                                long n, long prec);

void _fmprb_poly_mullow(fmprb_struct * C,
    const fmprb_struct * A, long lenA,
    const fmprb_struct * B, long lenB, long n, long prec);

void fmprb_poly_mullow(fmprb_poly_t res, const fmprb_poly_t poly1,
              const fmprb_poly_t poly2, long len, long prec);

void _fmprb_poly_mul(fmprb_struct * C,
    const fmprb_struct * A, long lenA,
    const fmprb_struct * B, long lenB, long prec);

void fmprb_poly_mul(fmprb_poly_t res, const fmprb_poly_t poly1,
              const fmprb_poly_t poly2, long prec);

void _fmprb_poly_inv_series(fmprb_struct * Qinv, const fmprb_struct * Q, long len, long prec);

void fmprb_poly_inv_series(fmprb_poly_t Qinv, const fmprb_poly_t Q, long n, long prec);

/* Derivative and integral */

void _fmprb_poly_derivative(fmprb_struct * res, const fmprb_struct * poly, long len, long prec);

void fmprb_poly_derivative(fmprb_poly_t res, const fmprb_poly_t poly, long prec);

void _fmprb_poly_integral(fmprb_struct * res, const fmprb_struct * poly, long len, long prec);

void fmprb_poly_integral(fmprb_poly_t res, const fmprb_poly_t poly, long prec);

/* Special functions */

void _fmprb_poly_log_series(fmprb_struct * res, fmprb_struct * f, long n, long prec);

void fmprb_poly_log_series(fmprb_poly_t res, const fmprb_poly_t f, long n, long prec);

void _fmprb_poly_exp_series_basecase(fmprb_struct * f,
        const fmprb_struct * h, long hlen, long n, long prec);

void fmprb_poly_exp_series_basecase(fmprb_poly_t f, const fmprb_poly_t h, long n, long prec);

void fmprb_poly_log_gamma_series(fmprb_poly_t z, long n, long prec);

#endif

