/*
 * Copyright (c) 2003 Matteo Frigo
 * Copyright (c) 2003 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sat Jul  5 22:11:54 EDT 2003 */

#include "codelet-rdft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_hc2r -compact -variables 4 -sign 1 -n 2 -name hc2rIII_2 -dft-III -include hc2rIII.h */

/*
 * This function contains 0 FP additions, 2 FP multiplications,
 * (or, 0 additions, 2 multiplications, 0 fused multiply/add),
 * 4 stack variables, and 4 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: algsimp.ml,v 1.7 2003/03/15 20:29:42 stevenj Exp $
 * $Id: fft.ml,v 1.2 2003/03/15 20:29:42 stevenj Exp $
 * $Id: gen_hc2r.ml,v 1.14 2003/04/17 19:25:50 athena Exp $
 */

#include "hc2rIII.h"

static void hc2rIII_2(const R *ri, const R *ii, R *O, stride ris, stride iis, stride os, int v, int ivs, int ovs)
{
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     int i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, O = O + ovs) {
	  E T1, T2;
	  T1 = ri[0];
	  O[0] = KP2_000000000 * T1;
	  T2 = ii[0];
	  O[WS(os, 1)] = -(KP2_000000000 * T2);
     }
}

static const khc2r_desc desc = { 2, "hc2rIII_2", {0, 2, 0, 0}, &GENUS, 0, 0, 0, 0, 0 };

void X(codelet_hc2rIII_2) (planner *p) {
     X(khc2rIII_register) (p, hc2rIII_2, &desc);
}
