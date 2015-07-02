// Copyright 2013-2015 Stanford University
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/* Check mp_bases values.

Copyright 2002 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library.  If not, see http://www.gnu.org/licenses/.  */

#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "gmp-impl.h"
#include "longlong.h"
#include "tests.h"


int
main (int argc, char *argv[])
{
  mp_limb_t  want_bb, want_bb_inv;
  int        base, want_chars_per_limb;

  want_chars_per_limb = refmpn_chars_per_limb (10);
  if (MP_BASES_CHARS_PER_LIMB_10 != want_chars_per_limb)
    {
      printf ("MP_BASES_CHARS_PER_LIMB_10 wrong\n");
      abort ();
    }

  want_bb = refmpn_big_base (10);
  if (MP_BASES_BIG_BASE_10 != want_bb)
    {
      printf ("MP_BASES_BIG_BASE_10 wrong\n");
      abort ();
    }

  want_bb_inv = refmpn_invert_limb
    (want_bb << refmpn_count_leading_zeros (want_bb));
  if (MP_BASES_BIG_BASE_INVERTED_10 != want_bb_inv)
    {
      printf ("MP_BASES_BIG_BASE_INVERTED_10 wrong\n");
      abort ();
    }

  if (MP_BASES_NORMALIZATION_STEPS_10
      != refmpn_count_leading_zeros (MP_BASES_BIG_BASE_10))
    {
      printf ("MP_BASES_NORMALIZATION_STEPS_10 wrong\n");
      abort ();
    }

  for (base = 2; base < numberof (mp_bases); base++)
    {
      want_chars_per_limb = refmpn_chars_per_limb (base);
      if (mp_bases[base].chars_per_limb != want_chars_per_limb)
        {
          printf ("mp_bases[%d].chars_per_limb wrong\n", base);
          printf ("  got  %d\n", mp_bases[base].chars_per_limb);
          printf ("  want %d\n", want_chars_per_limb);
          abort ();
        }

      if (POW2_P (base))
        {
          want_bb = refmpn_count_trailing_zeros ((mp_limb_t) base);
          if (mp_bases[base].big_base != want_bb)
            {
              printf ("mp_bases[%d].big_base (log2 of base) wrong\n", base);
              abort ();
            }
        }
      else
        {
          want_bb = refmpn_big_base (base);
          if (mp_bases[base].big_base != want_bb)
            {
              printf ("mp_bases[%d].big_base wrong\n", base);
              abort ();
            }

#if USE_PREINV_DIVREM_1
          want_bb_inv = refmpn_invert_limb
            (want_bb << refmpn_count_leading_zeros (want_bb));
          if (mp_bases[base].big_base_inverted != want_bb_inv)
            {
              printf ("mp_bases[%d].big_base_inverted wrong\n", base);
              abort ();
            }
#endif
        }
    }

  exit (0);
}