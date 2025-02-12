/*
    Copyright (C) 2018, 2019 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "nmod_mpoly.h"

void _nmod_mpoly_push_exp_ffmpz(
    nmod_mpoly_t A,
    const fmpz * exp,
    const nmod_mpoly_ctx_t ctx)
{
    slong N;
    slong old_length = A->length;
    flint_bitcnt_t exp_bits;

    exp_bits = mpoly_exp_bits_required_ffmpz(exp, ctx->minfo);
    exp_bits = mpoly_fix_bits(exp_bits, ctx->minfo);
    nmod_mpoly_fit_length_fit_bits(A, old_length + 1, exp_bits, ctx);

    A->length = old_length + 1;
    N = mpoly_words_per_exp(A->bits, ctx->minfo);
    mpoly_set_monomial_ffmpz(A->exps + N*old_length, exp, A->bits, ctx->minfo);
}

void _nmod_mpoly_push_exp_pfmpz(
    nmod_mpoly_t A,
    fmpz * const * exp,
    const nmod_mpoly_ctx_t ctx)
{
    slong N;
    slong old_length = A->length;
    flint_bitcnt_t exp_bits;

    exp_bits = mpoly_exp_bits_required_pfmpz(exp, ctx->minfo);
    exp_bits = mpoly_fix_bits(exp_bits, ctx->minfo);
    nmod_mpoly_fit_length_fit_bits(A, old_length + 1, exp_bits, ctx);

    A->length = old_length + 1;
    N = mpoly_words_per_exp(A->bits, ctx->minfo);
    mpoly_set_monomial_pfmpz(A->exps + N*old_length, exp, A->bits, ctx->minfo);
}


void nmod_mpoly_push_term_ui_fmpz(
    nmod_mpoly_t A,
    ulong c,
    fmpz * const * exp,
    const nmod_mpoly_ctx_t ctx)
{
    _nmod_mpoly_push_exp_pfmpz(A, exp, ctx);
    if (c >= ctx->mod.n)
        NMOD_RED(c, c, ctx->mod);
    A->coeffs[A->length - 1] = c;
}

void nmod_mpoly_push_term_ui_ffmpz(
    nmod_mpoly_t A,
    ulong c,
    const fmpz * exp,
    const nmod_mpoly_ctx_t ctx)
{
    _nmod_mpoly_push_exp_ffmpz(A, exp, ctx);
    if (c >= ctx->mod.n)
        NMOD_RED(c, c, ctx->mod);
    A->coeffs[A->length - 1] = c;
}
