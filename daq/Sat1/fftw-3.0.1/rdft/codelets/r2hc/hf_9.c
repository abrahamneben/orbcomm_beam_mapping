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
/* Generated on Sat Jul  5 21:57:01 EDT 2003 */

#include "codelet-rdft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_hc2hc -compact -variables 4 -n 9 -dit -name hf_9 -include hf.h */

/*
 * This function contains 96 FP additions, 72 FP multiplications,
 * (or, 60 additions, 36 multiplications, 36 fused multiply/add),
 * 41 stack variables, and 36 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: algsimp.ml,v 1.7 2003/03/15 20:29:42 stevenj Exp $
 * $Id: fft.ml,v 1.2 2003/03/15 20:29:42 stevenj Exp $
 * $Id: gen_hc2hc.ml,v 1.9 2003/04/17 19:25:50 athena Exp $
 */

#include "hf.h"

static const R *hf_9(R *rio, R *iio, const R *W, stride ios, int m, int dist)
{
     DK(KP939692620, +0.939692620785908384054109277324731469936208134);
     DK(KP342020143, +0.342020143325668733044099614682259580763083368);
     DK(KP984807753, +0.984807753012208059366743024589523013670643252);
     DK(KP173648177, +0.173648177666930348851716626769314796000375677);
     DK(KP642787609, +0.642787609686539326322643409907263432907559884);
     DK(KP766044443, +0.766044443118978035202392650555416673935832457);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     int i;
     for (i = m - 2; i > 0; i = i - 2, rio = rio + dist, iio = iio - dist, W = W + 16) {
	  E T1, T1B, TQ, T1G, Tc, TN, T1A, T1H, TL, T1x, T17, T1o, T1c, T1n, Tu;
	  E T1w, TW, T1k, T11, T1l;
	  {
	       E T6, TO, Tb, TP;
	       T1 = rio[0];
	       T1B = iio[-WS(ios, 8)];
	       {
		    E T3, T5, T2, T4;
		    T3 = rio[WS(ios, 3)];
		    T5 = iio[-WS(ios, 5)];
		    T2 = W[4];
		    T4 = W[5];
		    T6 = FMA(T2, T3, T4 * T5);
		    TO = FNMS(T4, T3, T2 * T5);
	       }
	       {
		    E T8, Ta, T7, T9;
		    T8 = rio[WS(ios, 6)];
		    Ta = iio[-WS(ios, 2)];
		    T7 = W[10];
		    T9 = W[11];
		    Tb = FMA(T7, T8, T9 * Ta);
		    TP = FNMS(T9, T8, T7 * Ta);
	       }
	       TQ = KP866025403 * (TO - TP);
	       T1G = KP866025403 * (Tb - T6);
	       Tc = T6 + Tb;
	       TN = FNMS(KP500000000, Tc, T1);
	       T1A = TO + TP;
	       T1H = FNMS(KP500000000, T1A, T1B);
	  }
	  {
	       E Tz, T19, TE, T14, TJ, T15, TK, T1a;
	       {
		    E Tw, Ty, Tv, Tx;
		    Tw = rio[WS(ios, 2)];
		    Ty = iio[-WS(ios, 6)];
		    Tv = W[2];
		    Tx = W[3];
		    Tz = FMA(Tv, Tw, Tx * Ty);
		    T19 = FNMS(Tx, Tw, Tv * Ty);
	       }
	       {
		    E TB, TD, TA, TC;
		    TB = rio[WS(ios, 5)];
		    TD = iio[-WS(ios, 3)];
		    TA = W[8];
		    TC = W[9];
		    TE = FMA(TA, TB, TC * TD);
		    T14 = FNMS(TC, TB, TA * TD);
	       }
	       {
		    E TG, TI, TF, TH;
		    TG = rio[WS(ios, 8)];
		    TI = iio[0];
		    TF = W[14];
		    TH = W[15];
		    TJ = FMA(TF, TG, TH * TI);
		    T15 = FNMS(TH, TG, TF * TI);
	       }
	       TK = TE + TJ;
	       T1a = T14 + T15;
	       TL = Tz + TK;
	       T1x = T19 + T1a;
	       {
		    E T13, T16, T18, T1b;
		    T13 = FNMS(KP500000000, TK, Tz);
		    T16 = KP866025403 * (T14 - T15);
		    T17 = T13 + T16;
		    T1o = T13 - T16;
		    T18 = KP866025403 * (TJ - TE);
		    T1b = FNMS(KP500000000, T1a, T19);
		    T1c = T18 + T1b;
		    T1n = T1b - T18;
	       }
	  }
	  {
	       E Ti, TY, Tn, TT, Ts, TU, Tt, TZ;
	       {
		    E Tf, Th, Te, Tg;
		    Tf = rio[WS(ios, 1)];
		    Th = iio[-WS(ios, 7)];
		    Te = W[0];
		    Tg = W[1];
		    Ti = FMA(Te, Tf, Tg * Th);
		    TY = FNMS(Tg, Tf, Te * Th);
	       }
	       {
		    E Tk, Tm, Tj, Tl;
		    Tk = rio[WS(ios, 4)];
		    Tm = iio[-WS(ios, 4)];
		    Tj = W[6];
		    Tl = W[7];
		    Tn = FMA(Tj, Tk, Tl * Tm);
		    TT = FNMS(Tl, Tk, Tj * Tm);
	       }
	       {
		    E Tp, Tr, To, Tq;
		    Tp = rio[WS(ios, 7)];
		    Tr = iio[-WS(ios, 1)];
		    To = W[12];
		    Tq = W[13];
		    Ts = FMA(To, Tp, Tq * Tr);
		    TU = FNMS(Tq, Tp, To * Tr);
	       }
	       Tt = Tn + Ts;
	       TZ = TT + TU;
	       Tu = Ti + Tt;
	       T1w = TY + TZ;
	       {
		    E TS, TV, TX, T10;
		    TS = FNMS(KP500000000, Tt, Ti);
		    TV = KP866025403 * (TT - TU);
		    TW = TS + TV;
		    T1k = TS - TV;
		    TX = KP866025403 * (Ts - Tn);
		    T10 = FNMS(KP500000000, TZ, TY);
		    T11 = TX + T10;
		    T1l = T10 - TX;
	       }
	  }
	  {
	       E T1y, Td, TM, T1v;
	       T1y = KP866025403 * (T1w - T1x);
	       Td = T1 + Tc;
	       TM = Tu + TL;
	       T1v = FNMS(KP500000000, TM, Td);
	       rio[0] = Td + TM;
	       rio[WS(ios, 3)] = T1v + T1y;
	       iio[-WS(ios, 6)] = T1v - T1y;
	  }
	  {
	       E T1D, T1z, T1C, T1E;
	       T1D = KP866025403 * (TL - Tu);
	       T1z = T1w + T1x;
	       T1C = T1A + T1B;
	       T1E = FNMS(KP500000000, T1z, T1C);
	       iio[0] = T1z + T1C;
	       iio[-WS(ios, 3)] = T1D + T1E;
	       rio[WS(ios, 6)] = T1D - T1E;
	  }
	  {
	       E TR, T1I, T1e, T1J, T1i, T1F, T1f, T1K;
	       TR = TN + TQ;
	       T1I = T1G + T1H;
	       {
		    E T12, T1d, T1g, T1h;
		    T12 = FMA(KP766044443, TW, KP642787609 * T11);
		    T1d = FMA(KP173648177, T17, KP984807753 * T1c);
		    T1e = T12 + T1d;
		    T1J = KP866025403 * (T1d - T12);
		    T1g = FNMS(KP642787609, TW, KP766044443 * T11);
		    T1h = FNMS(KP984807753, T17, KP173648177 * T1c);
		    T1i = KP866025403 * (T1g - T1h);
		    T1F = T1g + T1h;
	       }
	       rio[WS(ios, 1)] = TR + T1e;
	       iio[-WS(ios, 1)] = T1F + T1I;
	       T1f = FNMS(KP500000000, T1e, TR);
	       iio[-WS(ios, 7)] = T1f - T1i;
	       rio[WS(ios, 4)] = T1f + T1i;
	       T1K = FNMS(KP500000000, T1F, T1I);
	       rio[WS(ios, 7)] = T1J - T1K;
	       iio[-WS(ios, 4)] = T1J + T1K;
	  }
	  {
	       E T1j, T1M, T1q, T1O, T1u, T1L, T1r, T1N;
	       T1j = TN - TQ;
	       T1M = T1H - T1G;
	       {
		    E T1m, T1p, T1s, T1t;
		    T1m = FMA(KP173648177, T1k, KP984807753 * T1l);
		    T1p = FNMS(KP939692620, T1o, KP342020143 * T1n);
		    T1q = T1m + T1p;
		    T1O = KP866025403 * (T1p - T1m);
		    T1s = FNMS(KP984807753, T1k, KP173648177 * T1l);
		    T1t = FMA(KP342020143, T1o, KP939692620 * T1n);
		    T1u = KP866025403 * (T1s + T1t);
		    T1L = T1s - T1t;
	       }
	       rio[WS(ios, 2)] = T1j + T1q;
	       iio[-WS(ios, 2)] = T1L + T1M;
	       T1r = FNMS(KP500000000, T1q, T1j);
	       iio[-WS(ios, 8)] = T1r - T1u;
	       iio[-WS(ios, 5)] = T1r + T1u;
	       T1N = FMS(KP500000000, T1L, T1M);
	       rio[WS(ios, 5)] = T1N - T1O;
	       rio[WS(ios, 8)] = T1O + T1N;
	  }
     }
     return W;
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 9},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 9, "hf_9", twinstr, {60, 36, 36, 0}, &GENUS, 0, 0, 0 };

void X(codelet_hf_9) (planner *p) {
     X(khc2hc_dit_register) (p, hf_9, &desc);
}
