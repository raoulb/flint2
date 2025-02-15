/*
    Copyright (C) 2013 Mike Hansen

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include "ulong_extras.h"
#include "fmpz.h"
#include "fq_nmod.h"
#include "fq_nmod_mat.h"
#include "fq_nmod_poly.h"

#ifdef T
#undef T
#endif

#define T fq_nmod
#define CAP_T FQ_NMOD
#include "fq_poly_templates/profile/p-iterated_frobenius.c"
#undef CAP_T
#undef T
