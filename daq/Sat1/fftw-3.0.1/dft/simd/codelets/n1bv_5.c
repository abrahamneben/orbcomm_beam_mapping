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
/* Generated on Sat Jul  5 21:40:11 EDT 2003 */

#include "codelet-dft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_notw_c -simd -compact -variables 4 -sign 1 -n 5 -name n1bv_5 -include n1b.h */

/*
 * This function contains 16 FP additions, 6 FP multiplications,
 * (or, 13 additions, 3 multiplications, 3 fused multiply/add),
 * 18 stack variables, and 10 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: algsimp.ml,v 1.7 2003/03/15 20:29:42 stevenj Exp $
 * $Id: fft.ml,v 1.2 2003/03/15 20:29:42 stevenj Exp $
 * $Id: gen_notw_c.ml,v 1.9 2003/04/16 21:21:53 athena Exp $
 */

#include "n1b.h"

static void n1bv_5(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, int v, int ivs, int ovs)
{
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DVK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     int i;
     const R *xi;
     R *xo;
     xi = ii;
     xo = io;
     BEGIN_SIMD();
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs)) {
	  V Tb, T3, Tc, T6, Ta;
	  Tb = LD(&(xi[0]), ivs, &(xi[0]));
	  {
	       V T1, T2, T8, T4, T5, T9;
	       T1 = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
	       T2 = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
	       T8 = VADD(T1, T2);
	       T4 = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
	       T5 = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
	       T9 = VADD(T4, T5);
	       T3 = VSUB(T1, T2);
	       Tc = VADD(T8, T9);
	       T6 = VSUB(T4, T5);
	       Ta = VMUL(LDK(KP559016994), VSUB(T8, T9));
	  }
	  ST(&(xo[0]), VADD(Tb, Tc), ovs, &(xo[0]));
	  {
	       V T7, Tf, Te, Tg, Td;
	       T7 = VBYI(VFMA(LDK(KP951056516), T3, VMUL(LDK(KP587785252), T6)));
	       Tf = VBYI(VFNMS(LDK(KP951056516), T6, VMUL(LDK(KP587785252), T3)));
	       Td = VFNMS(LDK(KP250000000), Tc, Tb);
	       Te = VADD(Ta, Td);
	       Tg = VSUB(Td, Ta);
	       ST(&(xo[WS(os, 1)]), VADD(T7, Te), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 3)]), VSUB(Tg, Tf), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 4)]), VSUB(Te, T7), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 2)]), VADD(Tf, Tg), ovs, &(xo[0]));
	  }
     }
     END_SIMD();
}

static const kdft_desc desc = { 5, "n1bv_5", {13, 3, 3, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1bv_5) (planner *p) {
     X(kdft_register) (p, n1bv_5, &desc);
}
