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
/* Generated on Sat Jul  5 22:11:11 EDT 2003 */

#include "codelet-rdft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_hc2r -compact -variables 4 -sign 1 -n 6 -name hc2r_6 -include hc2r.h */

/*
 * This function contains 14 FP additions, 4 FP multiplications,
 * (or, 12 additions, 2 multiplications, 2 fused multiply/add),
 * 17 stack variables, and 12 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: algsimp.ml,v 1.7 2003/03/15 20:29:42 stevenj Exp $
 * $Id: fft.ml,v 1.2 2003/03/15 20:29:42 stevenj Exp $
 * $Id: gen_hc2r.ml,v 1.14 2003/04/17 19:25:50 athena Exp $
 */

#include "hc2r.h"

static void hc2r_6(const R *ri, const R *ii, R *O, stride ris, stride iis, stride os, int v, int ivs, int ovs)
{
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     DK(KP1_732050807, +1.732050807568877293527446341505872366942805254);
     int i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, O = O + ovs) {
	  E T3, T7, Tc, Te, T6, T8, T1, T2, T9, Td;
	  T1 = ri[0];
	  T2 = ri[WS(ris, 3)];
	  T3 = T1 - T2;
	  T7 = T1 + T2;
	  {
	       E Ta, Tb, T4, T5;
	       Ta = ii[WS(iis, 2)];
	       Tb = ii[WS(iis, 1)];
	       Tc = KP1_732050807 * (Ta - Tb);
	       Te = KP1_732050807 * (Ta + Tb);
	       T4 = ri[WS(ris, 2)];
	       T5 = ri[WS(ris, 1)];
	       T6 = T4 - T5;
	       T8 = T4 + T5;
	  }
	  O[WS(os, 3)] = FMA(KP2_000000000, T6, T3);
	  O[0] = FMA(KP2_000000000, T8, T7);
	  T9 = T7 - T8;
	  O[WS(os, 4)] = T9 - Tc;
	  O[WS(os, 2)] = T9 + Tc;
	  Td = T3 - T6;
	  O[WS(os, 1)] = Td - Te;
	  O[WS(os, 5)] = Td + Te;
     }
}

static const khc2r_desc desc = { 6, "hc2r_6", {12, 2, 2, 0}, &GENUS, 0, 0, 0, 0, 0 };

void X(codelet_hc2r_6) (planner *p) {
     X(khc2r_register) (p, hc2r_6, &desc);
}
