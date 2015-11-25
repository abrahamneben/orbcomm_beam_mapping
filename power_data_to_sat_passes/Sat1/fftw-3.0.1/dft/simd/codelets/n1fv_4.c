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
/* Generated on Sat Jul  5 21:40:06 EDT 2003 */

#include "codelet-dft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_notw_c -simd -compact -variables 4 -n 4 -name n1fv_4 -include n1f.h */

/*
 * This function contains 8 FP additions, 0 FP multiplications,
 * (or, 8 additions, 0 multiplications, 0 fused multiply/add),
 * 11 stack variables, and 8 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: algsimp.ml,v 1.7 2003/03/15 20:29:42 stevenj Exp $
 * $Id: fft.ml,v 1.2 2003/03/15 20:29:42 stevenj Exp $
 * $Id: gen_notw_c.ml,v 1.9 2003/04/16 21:21:53 athena Exp $
 */

#include "n1f.h"

static void n1fv_4(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, int v, int ivs, int ovs)
{
     int i;
     const R *xi;
     R *xo;
     xi = ri;
     xo = ro;
     BEGIN_SIMD();
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs)) {
	  V T3, T7, T6, T8;
	  {
	       V T1, T2, T4, T5;
	       T1 = LD(&(xi[0]), ivs, &(xi[0]));
	       T2 = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
	       T3 = VSUB(T1, T2);
	       T7 = VADD(T1, T2);
	       T4 = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
	       T5 = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
	       T6 = VBYI(VSUB(T4, T5));
	       T8 = VADD(T4, T5);
	  }
	  ST(&(xo[WS(os, 1)]), VSUB(T3, T6), ovs, &(xo[WS(os, 1)]));
	  ST(&(xo[0]), VADD(T7, T8), ovs, &(xo[0]));
	  ST(&(xo[WS(os, 3)]), VADD(T3, T6), ovs, &(xo[WS(os, 1)]));
	  ST(&(xo[WS(os, 2)]), VSUB(T7, T8), ovs, &(xo[0]));
     }
     END_SIMD();
}

static const kdft_desc desc = { 4, "n1fv_4", {8, 0, 0, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1fv_4) (planner *p) {
     X(kdft_register) (p, n1fv_4, &desc);
}
