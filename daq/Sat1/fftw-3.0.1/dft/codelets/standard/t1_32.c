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
/* Generated on Sat Jul  5 21:30:07 EDT 2003 */

#include "codelet-dft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_twiddle -compact -variables 4 -n 32 -name t1_32 -include t.h */

/*
 * This function contains 434 FP additions, 208 FP multiplications,
 * (or, 340 additions, 114 multiplications, 94 fused multiply/add),
 * 96 stack variables, and 128 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: algsimp.ml,v 1.7 2003/03/15 20:29:42 stevenj Exp $
 * $Id: fft.ml,v 1.2 2003/03/15 20:29:42 stevenj Exp $
 * $Id: gen_twiddle.ml,v 1.16 2003/04/16 19:51:27 athena Exp $
 */

#include "t.h"

static const R *t1_32(R *ri, R *ii, const R *W, stride ios, int m, int dist)
{
     DK(KP195090322, +0.195090322016128267848284868477022240927691618);
     DK(KP980785280, +0.980785280403230449126182236134239036973933731);
     DK(KP555570233, +0.555570233019602224742830813948532874374937191);
     DK(KP831469612, +0.831469612302545237078788377617905756738560812);
     DK(KP382683432, +0.382683432365089771728459984030398866761344562);
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     int i;
     for (i = m; i > 0; i = i - 1, ri = ri + dist, ii = ii + dist, W = W + 62) {
	  E Tj, T5F, T7C, T7Q, T35, T4T, T78, T7m, T1Q, T61, T5Y, T6J, T3K, T59, T41;
	  E T56, T2B, T67, T6e, T6O, T4b, T5d, T4s, T5g, TG, T7l, T5I, T73, T3a, T4U;
	  E T3f, T4V, T14, T5N, T5M, T6E, T3m, T4Y, T3r, T4Z, T1r, T5P, T5S, T6F, T3x;
	  E T51, T3C, T52, T2d, T5Z, T64, T6K, T3V, T57, T44, T5a, T2Y, T6f, T6a, T6P;
	  E T4m, T5h, T4v, T5e;
	  {
	       E T1, T76, T6, T75, Tc, T32, Th, T33;
	       T1 = ri[0];
	       T76 = ii[0];
	       {
		    E T3, T5, T2, T4;
		    T3 = ri[WS(ios, 16)];
		    T5 = ii[WS(ios, 16)];
		    T2 = W[30];
		    T4 = W[31];
		    T6 = FMA(T2, T3, T4 * T5);
		    T75 = FNMS(T4, T3, T2 * T5);
	       }
	       {
		    E T9, Tb, T8, Ta;
		    T9 = ri[WS(ios, 8)];
		    Tb = ii[WS(ios, 8)];
		    T8 = W[14];
		    Ta = W[15];
		    Tc = FMA(T8, T9, Ta * Tb);
		    T32 = FNMS(Ta, T9, T8 * Tb);
	       }
	       {
		    E Te, Tg, Td, Tf;
		    Te = ri[WS(ios, 24)];
		    Tg = ii[WS(ios, 24)];
		    Td = W[46];
		    Tf = W[47];
		    Th = FMA(Td, Te, Tf * Tg);
		    T33 = FNMS(Tf, Te, Td * Tg);
	       }
	       {
		    E T7, Ti, T7A, T7B;
		    T7 = T1 + T6;
		    Ti = Tc + Th;
		    Tj = T7 + Ti;
		    T5F = T7 - Ti;
		    T7A = T76 - T75;
		    T7B = Tc - Th;
		    T7C = T7A - T7B;
		    T7Q = T7B + T7A;
	       }
	       {
		    E T31, T34, T74, T77;
		    T31 = T1 - T6;
		    T34 = T32 - T33;
		    T35 = T31 - T34;
		    T4T = T31 + T34;
		    T74 = T32 + T33;
		    T77 = T75 + T76;
		    T78 = T74 + T77;
		    T7m = T77 - T74;
	       }
	  }
	  {
	       E T1y, T3G, T1O, T3Z, T1D, T3H, T1J, T3Y;
	       {
		    E T1v, T1x, T1u, T1w;
		    T1v = ri[WS(ios, 1)];
		    T1x = ii[WS(ios, 1)];
		    T1u = W[0];
		    T1w = W[1];
		    T1y = FMA(T1u, T1v, T1w * T1x);
		    T3G = FNMS(T1w, T1v, T1u * T1x);
	       }
	       {
		    E T1L, T1N, T1K, T1M;
		    T1L = ri[WS(ios, 25)];
		    T1N = ii[WS(ios, 25)];
		    T1K = W[48];
		    T1M = W[49];
		    T1O = FMA(T1K, T1L, T1M * T1N);
		    T3Z = FNMS(T1M, T1L, T1K * T1N);
	       }
	       {
		    E T1A, T1C, T1z, T1B;
		    T1A = ri[WS(ios, 17)];
		    T1C = ii[WS(ios, 17)];
		    T1z = W[32];
		    T1B = W[33];
		    T1D = FMA(T1z, T1A, T1B * T1C);
		    T3H = FNMS(T1B, T1A, T1z * T1C);
	       }
	       {
		    E T1G, T1I, T1F, T1H;
		    T1G = ri[WS(ios, 9)];
		    T1I = ii[WS(ios, 9)];
		    T1F = W[16];
		    T1H = W[17];
		    T1J = FMA(T1F, T1G, T1H * T1I);
		    T3Y = FNMS(T1H, T1G, T1F * T1I);
	       }
	       {
		    E T1E, T1P, T5W, T5X;
		    T1E = T1y + T1D;
		    T1P = T1J + T1O;
		    T1Q = T1E + T1P;
		    T61 = T1E - T1P;
		    T5W = T3G + T3H;
		    T5X = T3Y + T3Z;
		    T5Y = T5W - T5X;
		    T6J = T5W + T5X;
	       }
	       {
		    E T3I, T3J, T3X, T40;
		    T3I = T3G - T3H;
		    T3J = T1J - T1O;
		    T3K = T3I + T3J;
		    T59 = T3I - T3J;
		    T3X = T1y - T1D;
		    T40 = T3Y - T3Z;
		    T41 = T3X - T40;
		    T56 = T3X + T40;
	       }
	  }
	  {
	       E T2j, T4o, T2z, T49, T2o, T4p, T2u, T48;
	       {
		    E T2g, T2i, T2f, T2h;
		    T2g = ri[WS(ios, 31)];
		    T2i = ii[WS(ios, 31)];
		    T2f = W[60];
		    T2h = W[61];
		    T2j = FMA(T2f, T2g, T2h * T2i);
		    T4o = FNMS(T2h, T2g, T2f * T2i);
	       }
	       {
		    E T2w, T2y, T2v, T2x;
		    T2w = ri[WS(ios, 23)];
		    T2y = ii[WS(ios, 23)];
		    T2v = W[44];
		    T2x = W[45];
		    T2z = FMA(T2v, T2w, T2x * T2y);
		    T49 = FNMS(T2x, T2w, T2v * T2y);
	       }
	       {
		    E T2l, T2n, T2k, T2m;
		    T2l = ri[WS(ios, 15)];
		    T2n = ii[WS(ios, 15)];
		    T2k = W[28];
		    T2m = W[29];
		    T2o = FMA(T2k, T2l, T2m * T2n);
		    T4p = FNMS(T2m, T2l, T2k * T2n);
	       }
	       {
		    E T2r, T2t, T2q, T2s;
		    T2r = ri[WS(ios, 7)];
		    T2t = ii[WS(ios, 7)];
		    T2q = W[12];
		    T2s = W[13];
		    T2u = FMA(T2q, T2r, T2s * T2t);
		    T48 = FNMS(T2s, T2r, T2q * T2t);
	       }
	       {
		    E T2p, T2A, T6c, T6d;
		    T2p = T2j + T2o;
		    T2A = T2u + T2z;
		    T2B = T2p + T2A;
		    T67 = T2p - T2A;
		    T6c = T4o + T4p;
		    T6d = T48 + T49;
		    T6e = T6c - T6d;
		    T6O = T6c + T6d;
	       }
	       {
		    E T47, T4a, T4q, T4r;
		    T47 = T2j - T2o;
		    T4a = T48 - T49;
		    T4b = T47 - T4a;
		    T5d = T47 + T4a;
		    T4q = T4o - T4p;
		    T4r = T2u - T2z;
		    T4s = T4q + T4r;
		    T5g = T4q - T4r;
	       }
	  }
	  {
	       E To, T36, TE, T3d, Tt, T37, Tz, T3c;
	       {
		    E Tl, Tn, Tk, Tm;
		    Tl = ri[WS(ios, 4)];
		    Tn = ii[WS(ios, 4)];
		    Tk = W[6];
		    Tm = W[7];
		    To = FMA(Tk, Tl, Tm * Tn);
		    T36 = FNMS(Tm, Tl, Tk * Tn);
	       }
	       {
		    E TB, TD, TA, TC;
		    TB = ri[WS(ios, 12)];
		    TD = ii[WS(ios, 12)];
		    TA = W[22];
		    TC = W[23];
		    TE = FMA(TA, TB, TC * TD);
		    T3d = FNMS(TC, TB, TA * TD);
	       }
	       {
		    E Tq, Ts, Tp, Tr;
		    Tq = ri[WS(ios, 20)];
		    Ts = ii[WS(ios, 20)];
		    Tp = W[38];
		    Tr = W[39];
		    Tt = FMA(Tp, Tq, Tr * Ts);
		    T37 = FNMS(Tr, Tq, Tp * Ts);
	       }
	       {
		    E Tw, Ty, Tv, Tx;
		    Tw = ri[WS(ios, 28)];
		    Ty = ii[WS(ios, 28)];
		    Tv = W[54];
		    Tx = W[55];
		    Tz = FMA(Tv, Tw, Tx * Ty);
		    T3c = FNMS(Tx, Tw, Tv * Ty);
	       }
	       {
		    E Tu, TF, T5G, T5H;
		    Tu = To + Tt;
		    TF = Tz + TE;
		    TG = Tu + TF;
		    T7l = TF - Tu;
		    T5G = T36 + T37;
		    T5H = T3c + T3d;
		    T5I = T5G - T5H;
		    T73 = T5G + T5H;
	       }
	       {
		    E T38, T39, T3b, T3e;
		    T38 = T36 - T37;
		    T39 = To - Tt;
		    T3a = T38 - T39;
		    T4U = T39 + T38;
		    T3b = Tz - TE;
		    T3e = T3c - T3d;
		    T3f = T3b + T3e;
		    T4V = T3b - T3e;
	       }
	  }
	  {
	       E TM, T3i, T12, T3p, TR, T3j, TX, T3o;
	       {
		    E TJ, TL, TI, TK;
		    TJ = ri[WS(ios, 2)];
		    TL = ii[WS(ios, 2)];
		    TI = W[2];
		    TK = W[3];
		    TM = FMA(TI, TJ, TK * TL);
		    T3i = FNMS(TK, TJ, TI * TL);
	       }
	       {
		    E TZ, T11, TY, T10;
		    TZ = ri[WS(ios, 26)];
		    T11 = ii[WS(ios, 26)];
		    TY = W[50];
		    T10 = W[51];
		    T12 = FMA(TY, TZ, T10 * T11);
		    T3p = FNMS(T10, TZ, TY * T11);
	       }
	       {
		    E TO, TQ, TN, TP;
		    TO = ri[WS(ios, 18)];
		    TQ = ii[WS(ios, 18)];
		    TN = W[34];
		    TP = W[35];
		    TR = FMA(TN, TO, TP * TQ);
		    T3j = FNMS(TP, TO, TN * TQ);
	       }
	       {
		    E TU, TW, TT, TV;
		    TU = ri[WS(ios, 10)];
		    TW = ii[WS(ios, 10)];
		    TT = W[18];
		    TV = W[19];
		    TX = FMA(TT, TU, TV * TW);
		    T3o = FNMS(TV, TU, TT * TW);
	       }
	       {
		    E TS, T13, T5K, T5L;
		    TS = TM + TR;
		    T13 = TX + T12;
		    T14 = TS + T13;
		    T5N = TS - T13;
		    T5K = T3i + T3j;
		    T5L = T3o + T3p;
		    T5M = T5K - T5L;
		    T6E = T5K + T5L;
	       }
	       {
		    E T3k, T3l, T3n, T3q;
		    T3k = T3i - T3j;
		    T3l = TX - T12;
		    T3m = T3k + T3l;
		    T4Y = T3k - T3l;
		    T3n = TM - TR;
		    T3q = T3o - T3p;
		    T3r = T3n - T3q;
		    T4Z = T3n + T3q;
	       }
	  }
	  {
	       E T19, T3t, T1p, T3A, T1e, T3u, T1k, T3z;
	       {
		    E T16, T18, T15, T17;
		    T16 = ri[WS(ios, 30)];
		    T18 = ii[WS(ios, 30)];
		    T15 = W[58];
		    T17 = W[59];
		    T19 = FMA(T15, T16, T17 * T18);
		    T3t = FNMS(T17, T16, T15 * T18);
	       }
	       {
		    E T1m, T1o, T1l, T1n;
		    T1m = ri[WS(ios, 22)];
		    T1o = ii[WS(ios, 22)];
		    T1l = W[42];
		    T1n = W[43];
		    T1p = FMA(T1l, T1m, T1n * T1o);
		    T3A = FNMS(T1n, T1m, T1l * T1o);
	       }
	       {
		    E T1b, T1d, T1a, T1c;
		    T1b = ri[WS(ios, 14)];
		    T1d = ii[WS(ios, 14)];
		    T1a = W[26];
		    T1c = W[27];
		    T1e = FMA(T1a, T1b, T1c * T1d);
		    T3u = FNMS(T1c, T1b, T1a * T1d);
	       }
	       {
		    E T1h, T1j, T1g, T1i;
		    T1h = ri[WS(ios, 6)];
		    T1j = ii[WS(ios, 6)];
		    T1g = W[10];
		    T1i = W[11];
		    T1k = FMA(T1g, T1h, T1i * T1j);
		    T3z = FNMS(T1i, T1h, T1g * T1j);
	       }
	       {
		    E T1f, T1q, T5Q, T5R;
		    T1f = T19 + T1e;
		    T1q = T1k + T1p;
		    T1r = T1f + T1q;
		    T5P = T1f - T1q;
		    T5Q = T3t + T3u;
		    T5R = T3z + T3A;
		    T5S = T5Q - T5R;
		    T6F = T5Q + T5R;
	       }
	       {
		    E T3v, T3w, T3y, T3B;
		    T3v = T3t - T3u;
		    T3w = T1k - T1p;
		    T3x = T3v + T3w;
		    T51 = T3v - T3w;
		    T3y = T19 - T1e;
		    T3B = T3z - T3A;
		    T3C = T3y - T3B;
		    T52 = T3y + T3B;
	       }
	  }
	  {
	       E T1V, T3R, T20, T3S, T3Q, T3T, T26, T3M, T2b, T3N, T3L, T3O;
	       {
		    E T1S, T1U, T1R, T1T;
		    T1S = ri[WS(ios, 5)];
		    T1U = ii[WS(ios, 5)];
		    T1R = W[8];
		    T1T = W[9];
		    T1V = FMA(T1R, T1S, T1T * T1U);
		    T3R = FNMS(T1T, T1S, T1R * T1U);
	       }
	       {
		    E T1X, T1Z, T1W, T1Y;
		    T1X = ri[WS(ios, 21)];
		    T1Z = ii[WS(ios, 21)];
		    T1W = W[40];
		    T1Y = W[41];
		    T20 = FMA(T1W, T1X, T1Y * T1Z);
		    T3S = FNMS(T1Y, T1X, T1W * T1Z);
	       }
	       T3Q = T1V - T20;
	       T3T = T3R - T3S;
	       {
		    E T23, T25, T22, T24;
		    T23 = ri[WS(ios, 29)];
		    T25 = ii[WS(ios, 29)];
		    T22 = W[56];
		    T24 = W[57];
		    T26 = FMA(T22, T23, T24 * T25);
		    T3M = FNMS(T24, T23, T22 * T25);
	       }
	       {
		    E T28, T2a, T27, T29;
		    T28 = ri[WS(ios, 13)];
		    T2a = ii[WS(ios, 13)];
		    T27 = W[24];
		    T29 = W[25];
		    T2b = FMA(T27, T28, T29 * T2a);
		    T3N = FNMS(T29, T28, T27 * T2a);
	       }
	       T3L = T26 - T2b;
	       T3O = T3M - T3N;
	       {
		    E T21, T2c, T62, T63;
		    T21 = T1V + T20;
		    T2c = T26 + T2b;
		    T2d = T21 + T2c;
		    T5Z = T2c - T21;
		    T62 = T3R + T3S;
		    T63 = T3M + T3N;
		    T64 = T62 - T63;
		    T6K = T62 + T63;
	       }
	       {
		    E T3P, T3U, T42, T43;
		    T3P = T3L - T3O;
		    T3U = T3Q + T3T;
		    T3V = KP707106781 * (T3P - T3U);
		    T57 = KP707106781 * (T3U + T3P);
		    T42 = T3T - T3Q;
		    T43 = T3L + T3O;
		    T44 = KP707106781 * (T42 - T43);
		    T5a = KP707106781 * (T42 + T43);
	       }
	  }
	  {
	       E T2G, T4c, T2L, T4d, T4e, T4f, T2R, T4i, T2W, T4j, T4h, T4k;
	       {
		    E T2D, T2F, T2C, T2E;
		    T2D = ri[WS(ios, 3)];
		    T2F = ii[WS(ios, 3)];
		    T2C = W[4];
		    T2E = W[5];
		    T2G = FMA(T2C, T2D, T2E * T2F);
		    T4c = FNMS(T2E, T2D, T2C * T2F);
	       }
	       {
		    E T2I, T2K, T2H, T2J;
		    T2I = ri[WS(ios, 19)];
		    T2K = ii[WS(ios, 19)];
		    T2H = W[36];
		    T2J = W[37];
		    T2L = FMA(T2H, T2I, T2J * T2K);
		    T4d = FNMS(T2J, T2I, T2H * T2K);
	       }
	       T4e = T4c - T4d;
	       T4f = T2G - T2L;
	       {
		    E T2O, T2Q, T2N, T2P;
		    T2O = ri[WS(ios, 27)];
		    T2Q = ii[WS(ios, 27)];
		    T2N = W[52];
		    T2P = W[53];
		    T2R = FMA(T2N, T2O, T2P * T2Q);
		    T4i = FNMS(T2P, T2O, T2N * T2Q);
	       }
	       {
		    E T2T, T2V, T2S, T2U;
		    T2T = ri[WS(ios, 11)];
		    T2V = ii[WS(ios, 11)];
		    T2S = W[20];
		    T2U = W[21];
		    T2W = FMA(T2S, T2T, T2U * T2V);
		    T4j = FNMS(T2U, T2T, T2S * T2V);
	       }
	       T4h = T2R - T2W;
	       T4k = T4i - T4j;
	       {
		    E T2M, T2X, T68, T69;
		    T2M = T2G + T2L;
		    T2X = T2R + T2W;
		    T2Y = T2M + T2X;
		    T6f = T2X - T2M;
		    T68 = T4c + T4d;
		    T69 = T4i + T4j;
		    T6a = T68 - T69;
		    T6P = T68 + T69;
	       }
	       {
		    E T4g, T4l, T4t, T4u;
		    T4g = T4e - T4f;
		    T4l = T4h + T4k;
		    T4m = KP707106781 * (T4g - T4l);
		    T5h = KP707106781 * (T4g + T4l);
		    T4t = T4h - T4k;
		    T4u = T4f + T4e;
		    T4v = KP707106781 * (T4t - T4u);
		    T5e = KP707106781 * (T4u + T4t);
	       }
	  }
	  {
	       E T1t, T6X, T7a, T7c, T30, T7b, T70, T71;
	       {
		    E TH, T1s, T72, T79;
		    TH = Tj + TG;
		    T1s = T14 + T1r;
		    T1t = TH + T1s;
		    T6X = TH - T1s;
		    T72 = T6E + T6F;
		    T79 = T73 + T78;
		    T7a = T72 + T79;
		    T7c = T79 - T72;
	       }
	       {
		    E T2e, T2Z, T6Y, T6Z;
		    T2e = T1Q + T2d;
		    T2Z = T2B + T2Y;
		    T30 = T2e + T2Z;
		    T7b = T2Z - T2e;
		    T6Y = T6J + T6K;
		    T6Z = T6O + T6P;
		    T70 = T6Y - T6Z;
		    T71 = T6Y + T6Z;
	       }
	       ri[WS(ios, 16)] = T1t - T30;
	       ii[WS(ios, 16)] = T7a - T71;
	       ri[0] = T1t + T30;
	       ii[0] = T71 + T7a;
	       ri[WS(ios, 24)] = T6X - T70;
	       ii[WS(ios, 24)] = T7c - T7b;
	       ri[WS(ios, 8)] = T6X + T70;
	       ii[WS(ios, 8)] = T7b + T7c;
	  }
	  {
	       E T6H, T6T, T7g, T7i, T6M, T6U, T6R, T6V;
	       {
		    E T6D, T6G, T7e, T7f;
		    T6D = Tj - TG;
		    T6G = T6E - T6F;
		    T6H = T6D + T6G;
		    T6T = T6D - T6G;
		    T7e = T1r - T14;
		    T7f = T78 - T73;
		    T7g = T7e + T7f;
		    T7i = T7f - T7e;
	       }
	       {
		    E T6I, T6L, T6N, T6Q;
		    T6I = T1Q - T2d;
		    T6L = T6J - T6K;
		    T6M = T6I + T6L;
		    T6U = T6L - T6I;
		    T6N = T2B - T2Y;
		    T6Q = T6O - T6P;
		    T6R = T6N - T6Q;
		    T6V = T6N + T6Q;
	       }
	       {
		    E T6S, T7d, T6W, T7h;
		    T6S = KP707106781 * (T6M + T6R);
		    ri[WS(ios, 20)] = T6H - T6S;
		    ri[WS(ios, 4)] = T6H + T6S;
		    T7d = KP707106781 * (T6U + T6V);
		    ii[WS(ios, 4)] = T7d + T7g;
		    ii[WS(ios, 20)] = T7g - T7d;
		    T6W = KP707106781 * (T6U - T6V);
		    ri[WS(ios, 28)] = T6T - T6W;
		    ri[WS(ios, 12)] = T6T + T6W;
		    T7h = KP707106781 * (T6R - T6M);
		    ii[WS(ios, 12)] = T7h + T7i;
		    ii[WS(ios, 28)] = T7i - T7h;
	       }
	  }
	  {
	       E T5J, T7n, T7t, T6n, T5U, T7k, T6x, T6B, T6q, T7s, T66, T6k, T6u, T6A, T6h;
	       E T6l;
	       {
		    E T5O, T5T, T60, T65;
		    T5J = T5F - T5I;
		    T7n = T7l + T7m;
		    T7t = T7m - T7l;
		    T6n = T5F + T5I;
		    T5O = T5M - T5N;
		    T5T = T5P + T5S;
		    T5U = KP707106781 * (T5O - T5T);
		    T7k = KP707106781 * (T5O + T5T);
		    {
			 E T6v, T6w, T6o, T6p;
			 T6v = T67 + T6a;
			 T6w = T6e + T6f;
			 T6x = FNMS(KP382683432, T6w, KP923879532 * T6v);
			 T6B = FMA(KP923879532, T6w, KP382683432 * T6v);
			 T6o = T5N + T5M;
			 T6p = T5P - T5S;
			 T6q = KP707106781 * (T6o + T6p);
			 T7s = KP707106781 * (T6p - T6o);
		    }
		    T60 = T5Y - T5Z;
		    T65 = T61 - T64;
		    T66 = FMA(KP923879532, T60, KP382683432 * T65);
		    T6k = FNMS(KP923879532, T65, KP382683432 * T60);
		    {
			 E T6s, T6t, T6b, T6g;
			 T6s = T5Y + T5Z;
			 T6t = T61 + T64;
			 T6u = FMA(KP382683432, T6s, KP923879532 * T6t);
			 T6A = FNMS(KP382683432, T6t, KP923879532 * T6s);
			 T6b = T67 - T6a;
			 T6g = T6e - T6f;
			 T6h = FNMS(KP923879532, T6g, KP382683432 * T6b);
			 T6l = FMA(KP382683432, T6g, KP923879532 * T6b);
		    }
	       }
	       {
		    E T5V, T6i, T7r, T7u;
		    T5V = T5J + T5U;
		    T6i = T66 + T6h;
		    ri[WS(ios, 22)] = T5V - T6i;
		    ri[WS(ios, 6)] = T5V + T6i;
		    T7r = T6k + T6l;
		    T7u = T7s + T7t;
		    ii[WS(ios, 6)] = T7r + T7u;
		    ii[WS(ios, 22)] = T7u - T7r;
	       }
	       {
		    E T6j, T6m, T7v, T7w;
		    T6j = T5J - T5U;
		    T6m = T6k - T6l;
		    ri[WS(ios, 30)] = T6j - T6m;
		    ri[WS(ios, 14)] = T6j + T6m;
		    T7v = T6h - T66;
		    T7w = T7t - T7s;
		    ii[WS(ios, 14)] = T7v + T7w;
		    ii[WS(ios, 30)] = T7w - T7v;
	       }
	       {
		    E T6r, T6y, T7j, T7o;
		    T6r = T6n + T6q;
		    T6y = T6u + T6x;
		    ri[WS(ios, 18)] = T6r - T6y;
		    ri[WS(ios, 2)] = T6r + T6y;
		    T7j = T6A + T6B;
		    T7o = T7k + T7n;
		    ii[WS(ios, 2)] = T7j + T7o;
		    ii[WS(ios, 18)] = T7o - T7j;
	       }
	       {
		    E T6z, T6C, T7p, T7q;
		    T6z = T6n - T6q;
		    T6C = T6A - T6B;
		    ri[WS(ios, 26)] = T6z - T6C;
		    ri[WS(ios, 10)] = T6z + T6C;
		    T7p = T6x - T6u;
		    T7q = T7n - T7k;
		    ii[WS(ios, 10)] = T7p + T7q;
		    ii[WS(ios, 26)] = T7q - T7p;
	       }
	  }
	  {
	       E T3h, T4D, T7R, T7X, T3E, T7O, T4N, T4R, T46, T4A, T4G, T7W, T4K, T4Q, T4x;
	       E T4B, T3g, T7P;
	       T3g = KP707106781 * (T3a - T3f);
	       T3h = T35 - T3g;
	       T4D = T35 + T3g;
	       T7P = KP707106781 * (T4V - T4U);
	       T7R = T7P + T7Q;
	       T7X = T7Q - T7P;
	       {
		    E T3s, T3D, T4L, T4M;
		    T3s = FNMS(KP923879532, T3r, KP382683432 * T3m);
		    T3D = FMA(KP382683432, T3x, KP923879532 * T3C);
		    T3E = T3s - T3D;
		    T7O = T3s + T3D;
		    T4L = T4b + T4m;
		    T4M = T4s + T4v;
		    T4N = FNMS(KP555570233, T4M, KP831469612 * T4L);
		    T4R = FMA(KP831469612, T4M, KP555570233 * T4L);
	       }
	       {
		    E T3W, T45, T4E, T4F;
		    T3W = T3K - T3V;
		    T45 = T41 - T44;
		    T46 = FMA(KP980785280, T3W, KP195090322 * T45);
		    T4A = FNMS(KP980785280, T45, KP195090322 * T3W);
		    T4E = FMA(KP923879532, T3m, KP382683432 * T3r);
		    T4F = FNMS(KP923879532, T3x, KP382683432 * T3C);
		    T4G = T4E + T4F;
		    T7W = T4F - T4E;
	       }
	       {
		    E T4I, T4J, T4n, T4w;
		    T4I = T3K + T3V;
		    T4J = T41 + T44;
		    T4K = FMA(KP555570233, T4I, KP831469612 * T4J);
		    T4Q = FNMS(KP555570233, T4J, KP831469612 * T4I);
		    T4n = T4b - T4m;
		    T4w = T4s - T4v;
		    T4x = FNMS(KP980785280, T4w, KP195090322 * T4n);
		    T4B = FMA(KP195090322, T4w, KP980785280 * T4n);
	       }
	       {
		    E T3F, T4y, T7V, T7Y;
		    T3F = T3h + T3E;
		    T4y = T46 + T4x;
		    ri[WS(ios, 23)] = T3F - T4y;
		    ri[WS(ios, 7)] = T3F + T4y;
		    T7V = T4A + T4B;
		    T7Y = T7W + T7X;
		    ii[WS(ios, 7)] = T7V + T7Y;
		    ii[WS(ios, 23)] = T7Y - T7V;
	       }
	       {
		    E T4z, T4C, T7Z, T80;
		    T4z = T3h - T3E;
		    T4C = T4A - T4B;
		    ri[WS(ios, 31)] = T4z - T4C;
		    ri[WS(ios, 15)] = T4z + T4C;
		    T7Z = T4x - T46;
		    T80 = T7X - T7W;
		    ii[WS(ios, 15)] = T7Z + T80;
		    ii[WS(ios, 31)] = T80 - T7Z;
	       }
	       {
		    E T4H, T4O, T7N, T7S;
		    T4H = T4D + T4G;
		    T4O = T4K + T4N;
		    ri[WS(ios, 19)] = T4H - T4O;
		    ri[WS(ios, 3)] = T4H + T4O;
		    T7N = T4Q + T4R;
		    T7S = T7O + T7R;
		    ii[WS(ios, 3)] = T7N + T7S;
		    ii[WS(ios, 19)] = T7S - T7N;
	       }
	       {
		    E T4P, T4S, T7T, T7U;
		    T4P = T4D - T4G;
		    T4S = T4Q - T4R;
		    ri[WS(ios, 27)] = T4P - T4S;
		    ri[WS(ios, 11)] = T4P + T4S;
		    T7T = T4N - T4K;
		    T7U = T7R - T7O;
		    ii[WS(ios, 11)] = T7T + T7U;
		    ii[WS(ios, 27)] = T7U - T7T;
	       }
	  }
	  {
	       E T4X, T5p, T7D, T7J, T54, T7y, T5z, T5D, T5c, T5m, T5s, T7I, T5w, T5C, T5j;
	       E T5n, T4W, T7z;
	       T4W = KP707106781 * (T4U + T4V);
	       T4X = T4T - T4W;
	       T5p = T4T + T4W;
	       T7z = KP707106781 * (T3a + T3f);
	       T7D = T7z + T7C;
	       T7J = T7C - T7z;
	       {
		    E T50, T53, T5x, T5y;
		    T50 = FNMS(KP382683432, T4Z, KP923879532 * T4Y);
		    T53 = FMA(KP923879532, T51, KP382683432 * T52);
		    T54 = T50 - T53;
		    T7y = T50 + T53;
		    T5x = T5d + T5e;
		    T5y = T5g + T5h;
		    T5z = FNMS(KP195090322, T5y, KP980785280 * T5x);
		    T5D = FMA(KP195090322, T5x, KP980785280 * T5y);
	       }
	       {
		    E T58, T5b, T5q, T5r;
		    T58 = T56 - T57;
		    T5b = T59 - T5a;
		    T5c = FMA(KP555570233, T58, KP831469612 * T5b);
		    T5m = FNMS(KP831469612, T58, KP555570233 * T5b);
		    T5q = FMA(KP382683432, T4Y, KP923879532 * T4Z);
		    T5r = FNMS(KP382683432, T51, KP923879532 * T52);
		    T5s = T5q + T5r;
		    T7I = T5r - T5q;
	       }
	       {
		    E T5u, T5v, T5f, T5i;
		    T5u = T56 + T57;
		    T5v = T59 + T5a;
		    T5w = FMA(KP980785280, T5u, KP195090322 * T5v);
		    T5C = FNMS(KP195090322, T5u, KP980785280 * T5v);
		    T5f = T5d - T5e;
		    T5i = T5g - T5h;
		    T5j = FNMS(KP831469612, T5i, KP555570233 * T5f);
		    T5n = FMA(KP831469612, T5f, KP555570233 * T5i);
	       }
	       {
		    E T55, T5k, T7H, T7K;
		    T55 = T4X + T54;
		    T5k = T5c + T5j;
		    ri[WS(ios, 21)] = T55 - T5k;
		    ri[WS(ios, 5)] = T55 + T5k;
		    T7H = T5m + T5n;
		    T7K = T7I + T7J;
		    ii[WS(ios, 5)] = T7H + T7K;
		    ii[WS(ios, 21)] = T7K - T7H;
	       }
	       {
		    E T5l, T5o, T7L, T7M;
		    T5l = T4X - T54;
		    T5o = T5m - T5n;
		    ri[WS(ios, 29)] = T5l - T5o;
		    ri[WS(ios, 13)] = T5l + T5o;
		    T7L = T5j - T5c;
		    T7M = T7J - T7I;
		    ii[WS(ios, 13)] = T7L + T7M;
		    ii[WS(ios, 29)] = T7M - T7L;
	       }
	       {
		    E T5t, T5A, T7x, T7E;
		    T5t = T5p + T5s;
		    T5A = T5w + T5z;
		    ri[WS(ios, 17)] = T5t - T5A;
		    ri[WS(ios, 1)] = T5t + T5A;
		    T7x = T5C + T5D;
		    T7E = T7y + T7D;
		    ii[WS(ios, 1)] = T7x + T7E;
		    ii[WS(ios, 17)] = T7E - T7x;
	       }
	       {
		    E T5B, T5E, T7F, T7G;
		    T5B = T5p - T5s;
		    T5E = T5C - T5D;
		    ri[WS(ios, 25)] = T5B - T5E;
		    ri[WS(ios, 9)] = T5B + T5E;
		    T7F = T5z - T5w;
		    T7G = T7D - T7y;
		    ii[WS(ios, 9)] = T7F + T7G;
		    ii[WS(ios, 25)] = T7G - T7F;
	       }
	  }
     }
     return W;
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 32},
     {TW_NEXT, 1, 0}
};

static const ct_desc desc = { 32, "t1_32", twinstr, {340, 114, 94, 0}, &GENUS, 0, 0, 0 };

void X(codelet_t1_32) (planner *p) {
     X(kdft_dit_register) (p, t1_32, &desc);
}