#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2154331471386048889) {
   out_2154331471386048889[0] = delta_x[0] + nom_x[0];
   out_2154331471386048889[1] = delta_x[1] + nom_x[1];
   out_2154331471386048889[2] = delta_x[2] + nom_x[2];
   out_2154331471386048889[3] = delta_x[3] + nom_x[3];
   out_2154331471386048889[4] = delta_x[4] + nom_x[4];
   out_2154331471386048889[5] = delta_x[5] + nom_x[5];
   out_2154331471386048889[6] = delta_x[6] + nom_x[6];
   out_2154331471386048889[7] = delta_x[7] + nom_x[7];
   out_2154331471386048889[8] = delta_x[8] + nom_x[8];
   out_2154331471386048889[9] = delta_x[9] + nom_x[9];
   out_2154331471386048889[10] = delta_x[10] + nom_x[10];
   out_2154331471386048889[11] = delta_x[11] + nom_x[11];
   out_2154331471386048889[12] = delta_x[12] + nom_x[12];
   out_2154331471386048889[13] = delta_x[13] + nom_x[13];
   out_2154331471386048889[14] = delta_x[14] + nom_x[14];
   out_2154331471386048889[15] = delta_x[15] + nom_x[15];
   out_2154331471386048889[16] = delta_x[16] + nom_x[16];
   out_2154331471386048889[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8657363058238728605) {
   out_8657363058238728605[0] = -nom_x[0] + true_x[0];
   out_8657363058238728605[1] = -nom_x[1] + true_x[1];
   out_8657363058238728605[2] = -nom_x[2] + true_x[2];
   out_8657363058238728605[3] = -nom_x[3] + true_x[3];
   out_8657363058238728605[4] = -nom_x[4] + true_x[4];
   out_8657363058238728605[5] = -nom_x[5] + true_x[5];
   out_8657363058238728605[6] = -nom_x[6] + true_x[6];
   out_8657363058238728605[7] = -nom_x[7] + true_x[7];
   out_8657363058238728605[8] = -nom_x[8] + true_x[8];
   out_8657363058238728605[9] = -nom_x[9] + true_x[9];
   out_8657363058238728605[10] = -nom_x[10] + true_x[10];
   out_8657363058238728605[11] = -nom_x[11] + true_x[11];
   out_8657363058238728605[12] = -nom_x[12] + true_x[12];
   out_8657363058238728605[13] = -nom_x[13] + true_x[13];
   out_8657363058238728605[14] = -nom_x[14] + true_x[14];
   out_8657363058238728605[15] = -nom_x[15] + true_x[15];
   out_8657363058238728605[16] = -nom_x[16] + true_x[16];
   out_8657363058238728605[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4378726407183363418) {
   out_4378726407183363418[0] = 1.0;
   out_4378726407183363418[1] = 0.0;
   out_4378726407183363418[2] = 0.0;
   out_4378726407183363418[3] = 0.0;
   out_4378726407183363418[4] = 0.0;
   out_4378726407183363418[5] = 0.0;
   out_4378726407183363418[6] = 0.0;
   out_4378726407183363418[7] = 0.0;
   out_4378726407183363418[8] = 0.0;
   out_4378726407183363418[9] = 0.0;
   out_4378726407183363418[10] = 0.0;
   out_4378726407183363418[11] = 0.0;
   out_4378726407183363418[12] = 0.0;
   out_4378726407183363418[13] = 0.0;
   out_4378726407183363418[14] = 0.0;
   out_4378726407183363418[15] = 0.0;
   out_4378726407183363418[16] = 0.0;
   out_4378726407183363418[17] = 0.0;
   out_4378726407183363418[18] = 0.0;
   out_4378726407183363418[19] = 1.0;
   out_4378726407183363418[20] = 0.0;
   out_4378726407183363418[21] = 0.0;
   out_4378726407183363418[22] = 0.0;
   out_4378726407183363418[23] = 0.0;
   out_4378726407183363418[24] = 0.0;
   out_4378726407183363418[25] = 0.0;
   out_4378726407183363418[26] = 0.0;
   out_4378726407183363418[27] = 0.0;
   out_4378726407183363418[28] = 0.0;
   out_4378726407183363418[29] = 0.0;
   out_4378726407183363418[30] = 0.0;
   out_4378726407183363418[31] = 0.0;
   out_4378726407183363418[32] = 0.0;
   out_4378726407183363418[33] = 0.0;
   out_4378726407183363418[34] = 0.0;
   out_4378726407183363418[35] = 0.0;
   out_4378726407183363418[36] = 0.0;
   out_4378726407183363418[37] = 0.0;
   out_4378726407183363418[38] = 1.0;
   out_4378726407183363418[39] = 0.0;
   out_4378726407183363418[40] = 0.0;
   out_4378726407183363418[41] = 0.0;
   out_4378726407183363418[42] = 0.0;
   out_4378726407183363418[43] = 0.0;
   out_4378726407183363418[44] = 0.0;
   out_4378726407183363418[45] = 0.0;
   out_4378726407183363418[46] = 0.0;
   out_4378726407183363418[47] = 0.0;
   out_4378726407183363418[48] = 0.0;
   out_4378726407183363418[49] = 0.0;
   out_4378726407183363418[50] = 0.0;
   out_4378726407183363418[51] = 0.0;
   out_4378726407183363418[52] = 0.0;
   out_4378726407183363418[53] = 0.0;
   out_4378726407183363418[54] = 0.0;
   out_4378726407183363418[55] = 0.0;
   out_4378726407183363418[56] = 0.0;
   out_4378726407183363418[57] = 1.0;
   out_4378726407183363418[58] = 0.0;
   out_4378726407183363418[59] = 0.0;
   out_4378726407183363418[60] = 0.0;
   out_4378726407183363418[61] = 0.0;
   out_4378726407183363418[62] = 0.0;
   out_4378726407183363418[63] = 0.0;
   out_4378726407183363418[64] = 0.0;
   out_4378726407183363418[65] = 0.0;
   out_4378726407183363418[66] = 0.0;
   out_4378726407183363418[67] = 0.0;
   out_4378726407183363418[68] = 0.0;
   out_4378726407183363418[69] = 0.0;
   out_4378726407183363418[70] = 0.0;
   out_4378726407183363418[71] = 0.0;
   out_4378726407183363418[72] = 0.0;
   out_4378726407183363418[73] = 0.0;
   out_4378726407183363418[74] = 0.0;
   out_4378726407183363418[75] = 0.0;
   out_4378726407183363418[76] = 1.0;
   out_4378726407183363418[77] = 0.0;
   out_4378726407183363418[78] = 0.0;
   out_4378726407183363418[79] = 0.0;
   out_4378726407183363418[80] = 0.0;
   out_4378726407183363418[81] = 0.0;
   out_4378726407183363418[82] = 0.0;
   out_4378726407183363418[83] = 0.0;
   out_4378726407183363418[84] = 0.0;
   out_4378726407183363418[85] = 0.0;
   out_4378726407183363418[86] = 0.0;
   out_4378726407183363418[87] = 0.0;
   out_4378726407183363418[88] = 0.0;
   out_4378726407183363418[89] = 0.0;
   out_4378726407183363418[90] = 0.0;
   out_4378726407183363418[91] = 0.0;
   out_4378726407183363418[92] = 0.0;
   out_4378726407183363418[93] = 0.0;
   out_4378726407183363418[94] = 0.0;
   out_4378726407183363418[95] = 1.0;
   out_4378726407183363418[96] = 0.0;
   out_4378726407183363418[97] = 0.0;
   out_4378726407183363418[98] = 0.0;
   out_4378726407183363418[99] = 0.0;
   out_4378726407183363418[100] = 0.0;
   out_4378726407183363418[101] = 0.0;
   out_4378726407183363418[102] = 0.0;
   out_4378726407183363418[103] = 0.0;
   out_4378726407183363418[104] = 0.0;
   out_4378726407183363418[105] = 0.0;
   out_4378726407183363418[106] = 0.0;
   out_4378726407183363418[107] = 0.0;
   out_4378726407183363418[108] = 0.0;
   out_4378726407183363418[109] = 0.0;
   out_4378726407183363418[110] = 0.0;
   out_4378726407183363418[111] = 0.0;
   out_4378726407183363418[112] = 0.0;
   out_4378726407183363418[113] = 0.0;
   out_4378726407183363418[114] = 1.0;
   out_4378726407183363418[115] = 0.0;
   out_4378726407183363418[116] = 0.0;
   out_4378726407183363418[117] = 0.0;
   out_4378726407183363418[118] = 0.0;
   out_4378726407183363418[119] = 0.0;
   out_4378726407183363418[120] = 0.0;
   out_4378726407183363418[121] = 0.0;
   out_4378726407183363418[122] = 0.0;
   out_4378726407183363418[123] = 0.0;
   out_4378726407183363418[124] = 0.0;
   out_4378726407183363418[125] = 0.0;
   out_4378726407183363418[126] = 0.0;
   out_4378726407183363418[127] = 0.0;
   out_4378726407183363418[128] = 0.0;
   out_4378726407183363418[129] = 0.0;
   out_4378726407183363418[130] = 0.0;
   out_4378726407183363418[131] = 0.0;
   out_4378726407183363418[132] = 0.0;
   out_4378726407183363418[133] = 1.0;
   out_4378726407183363418[134] = 0.0;
   out_4378726407183363418[135] = 0.0;
   out_4378726407183363418[136] = 0.0;
   out_4378726407183363418[137] = 0.0;
   out_4378726407183363418[138] = 0.0;
   out_4378726407183363418[139] = 0.0;
   out_4378726407183363418[140] = 0.0;
   out_4378726407183363418[141] = 0.0;
   out_4378726407183363418[142] = 0.0;
   out_4378726407183363418[143] = 0.0;
   out_4378726407183363418[144] = 0.0;
   out_4378726407183363418[145] = 0.0;
   out_4378726407183363418[146] = 0.0;
   out_4378726407183363418[147] = 0.0;
   out_4378726407183363418[148] = 0.0;
   out_4378726407183363418[149] = 0.0;
   out_4378726407183363418[150] = 0.0;
   out_4378726407183363418[151] = 0.0;
   out_4378726407183363418[152] = 1.0;
   out_4378726407183363418[153] = 0.0;
   out_4378726407183363418[154] = 0.0;
   out_4378726407183363418[155] = 0.0;
   out_4378726407183363418[156] = 0.0;
   out_4378726407183363418[157] = 0.0;
   out_4378726407183363418[158] = 0.0;
   out_4378726407183363418[159] = 0.0;
   out_4378726407183363418[160] = 0.0;
   out_4378726407183363418[161] = 0.0;
   out_4378726407183363418[162] = 0.0;
   out_4378726407183363418[163] = 0.0;
   out_4378726407183363418[164] = 0.0;
   out_4378726407183363418[165] = 0.0;
   out_4378726407183363418[166] = 0.0;
   out_4378726407183363418[167] = 0.0;
   out_4378726407183363418[168] = 0.0;
   out_4378726407183363418[169] = 0.0;
   out_4378726407183363418[170] = 0.0;
   out_4378726407183363418[171] = 1.0;
   out_4378726407183363418[172] = 0.0;
   out_4378726407183363418[173] = 0.0;
   out_4378726407183363418[174] = 0.0;
   out_4378726407183363418[175] = 0.0;
   out_4378726407183363418[176] = 0.0;
   out_4378726407183363418[177] = 0.0;
   out_4378726407183363418[178] = 0.0;
   out_4378726407183363418[179] = 0.0;
   out_4378726407183363418[180] = 0.0;
   out_4378726407183363418[181] = 0.0;
   out_4378726407183363418[182] = 0.0;
   out_4378726407183363418[183] = 0.0;
   out_4378726407183363418[184] = 0.0;
   out_4378726407183363418[185] = 0.0;
   out_4378726407183363418[186] = 0.0;
   out_4378726407183363418[187] = 0.0;
   out_4378726407183363418[188] = 0.0;
   out_4378726407183363418[189] = 0.0;
   out_4378726407183363418[190] = 1.0;
   out_4378726407183363418[191] = 0.0;
   out_4378726407183363418[192] = 0.0;
   out_4378726407183363418[193] = 0.0;
   out_4378726407183363418[194] = 0.0;
   out_4378726407183363418[195] = 0.0;
   out_4378726407183363418[196] = 0.0;
   out_4378726407183363418[197] = 0.0;
   out_4378726407183363418[198] = 0.0;
   out_4378726407183363418[199] = 0.0;
   out_4378726407183363418[200] = 0.0;
   out_4378726407183363418[201] = 0.0;
   out_4378726407183363418[202] = 0.0;
   out_4378726407183363418[203] = 0.0;
   out_4378726407183363418[204] = 0.0;
   out_4378726407183363418[205] = 0.0;
   out_4378726407183363418[206] = 0.0;
   out_4378726407183363418[207] = 0.0;
   out_4378726407183363418[208] = 0.0;
   out_4378726407183363418[209] = 1.0;
   out_4378726407183363418[210] = 0.0;
   out_4378726407183363418[211] = 0.0;
   out_4378726407183363418[212] = 0.0;
   out_4378726407183363418[213] = 0.0;
   out_4378726407183363418[214] = 0.0;
   out_4378726407183363418[215] = 0.0;
   out_4378726407183363418[216] = 0.0;
   out_4378726407183363418[217] = 0.0;
   out_4378726407183363418[218] = 0.0;
   out_4378726407183363418[219] = 0.0;
   out_4378726407183363418[220] = 0.0;
   out_4378726407183363418[221] = 0.0;
   out_4378726407183363418[222] = 0.0;
   out_4378726407183363418[223] = 0.0;
   out_4378726407183363418[224] = 0.0;
   out_4378726407183363418[225] = 0.0;
   out_4378726407183363418[226] = 0.0;
   out_4378726407183363418[227] = 0.0;
   out_4378726407183363418[228] = 1.0;
   out_4378726407183363418[229] = 0.0;
   out_4378726407183363418[230] = 0.0;
   out_4378726407183363418[231] = 0.0;
   out_4378726407183363418[232] = 0.0;
   out_4378726407183363418[233] = 0.0;
   out_4378726407183363418[234] = 0.0;
   out_4378726407183363418[235] = 0.0;
   out_4378726407183363418[236] = 0.0;
   out_4378726407183363418[237] = 0.0;
   out_4378726407183363418[238] = 0.0;
   out_4378726407183363418[239] = 0.0;
   out_4378726407183363418[240] = 0.0;
   out_4378726407183363418[241] = 0.0;
   out_4378726407183363418[242] = 0.0;
   out_4378726407183363418[243] = 0.0;
   out_4378726407183363418[244] = 0.0;
   out_4378726407183363418[245] = 0.0;
   out_4378726407183363418[246] = 0.0;
   out_4378726407183363418[247] = 1.0;
   out_4378726407183363418[248] = 0.0;
   out_4378726407183363418[249] = 0.0;
   out_4378726407183363418[250] = 0.0;
   out_4378726407183363418[251] = 0.0;
   out_4378726407183363418[252] = 0.0;
   out_4378726407183363418[253] = 0.0;
   out_4378726407183363418[254] = 0.0;
   out_4378726407183363418[255] = 0.0;
   out_4378726407183363418[256] = 0.0;
   out_4378726407183363418[257] = 0.0;
   out_4378726407183363418[258] = 0.0;
   out_4378726407183363418[259] = 0.0;
   out_4378726407183363418[260] = 0.0;
   out_4378726407183363418[261] = 0.0;
   out_4378726407183363418[262] = 0.0;
   out_4378726407183363418[263] = 0.0;
   out_4378726407183363418[264] = 0.0;
   out_4378726407183363418[265] = 0.0;
   out_4378726407183363418[266] = 1.0;
   out_4378726407183363418[267] = 0.0;
   out_4378726407183363418[268] = 0.0;
   out_4378726407183363418[269] = 0.0;
   out_4378726407183363418[270] = 0.0;
   out_4378726407183363418[271] = 0.0;
   out_4378726407183363418[272] = 0.0;
   out_4378726407183363418[273] = 0.0;
   out_4378726407183363418[274] = 0.0;
   out_4378726407183363418[275] = 0.0;
   out_4378726407183363418[276] = 0.0;
   out_4378726407183363418[277] = 0.0;
   out_4378726407183363418[278] = 0.0;
   out_4378726407183363418[279] = 0.0;
   out_4378726407183363418[280] = 0.0;
   out_4378726407183363418[281] = 0.0;
   out_4378726407183363418[282] = 0.0;
   out_4378726407183363418[283] = 0.0;
   out_4378726407183363418[284] = 0.0;
   out_4378726407183363418[285] = 1.0;
   out_4378726407183363418[286] = 0.0;
   out_4378726407183363418[287] = 0.0;
   out_4378726407183363418[288] = 0.0;
   out_4378726407183363418[289] = 0.0;
   out_4378726407183363418[290] = 0.0;
   out_4378726407183363418[291] = 0.0;
   out_4378726407183363418[292] = 0.0;
   out_4378726407183363418[293] = 0.0;
   out_4378726407183363418[294] = 0.0;
   out_4378726407183363418[295] = 0.0;
   out_4378726407183363418[296] = 0.0;
   out_4378726407183363418[297] = 0.0;
   out_4378726407183363418[298] = 0.0;
   out_4378726407183363418[299] = 0.0;
   out_4378726407183363418[300] = 0.0;
   out_4378726407183363418[301] = 0.0;
   out_4378726407183363418[302] = 0.0;
   out_4378726407183363418[303] = 0.0;
   out_4378726407183363418[304] = 1.0;
   out_4378726407183363418[305] = 0.0;
   out_4378726407183363418[306] = 0.0;
   out_4378726407183363418[307] = 0.0;
   out_4378726407183363418[308] = 0.0;
   out_4378726407183363418[309] = 0.0;
   out_4378726407183363418[310] = 0.0;
   out_4378726407183363418[311] = 0.0;
   out_4378726407183363418[312] = 0.0;
   out_4378726407183363418[313] = 0.0;
   out_4378726407183363418[314] = 0.0;
   out_4378726407183363418[315] = 0.0;
   out_4378726407183363418[316] = 0.0;
   out_4378726407183363418[317] = 0.0;
   out_4378726407183363418[318] = 0.0;
   out_4378726407183363418[319] = 0.0;
   out_4378726407183363418[320] = 0.0;
   out_4378726407183363418[321] = 0.0;
   out_4378726407183363418[322] = 0.0;
   out_4378726407183363418[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5195038445783001597) {
   out_5195038445783001597[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5195038445783001597[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5195038445783001597[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5195038445783001597[3] = dt*state[12] + state[3];
   out_5195038445783001597[4] = dt*state[13] + state[4];
   out_5195038445783001597[5] = dt*state[14] + state[5];
   out_5195038445783001597[6] = state[6];
   out_5195038445783001597[7] = state[7];
   out_5195038445783001597[8] = state[8];
   out_5195038445783001597[9] = state[9];
   out_5195038445783001597[10] = state[10];
   out_5195038445783001597[11] = state[11];
   out_5195038445783001597[12] = state[12];
   out_5195038445783001597[13] = state[13];
   out_5195038445783001597[14] = state[14];
   out_5195038445783001597[15] = state[15];
   out_5195038445783001597[16] = state[16];
   out_5195038445783001597[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3015220250778787201) {
   out_3015220250778787201[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3015220250778787201[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3015220250778787201[2] = 0;
   out_3015220250778787201[3] = 0;
   out_3015220250778787201[4] = 0;
   out_3015220250778787201[5] = 0;
   out_3015220250778787201[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3015220250778787201[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3015220250778787201[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3015220250778787201[9] = 0;
   out_3015220250778787201[10] = 0;
   out_3015220250778787201[11] = 0;
   out_3015220250778787201[12] = 0;
   out_3015220250778787201[13] = 0;
   out_3015220250778787201[14] = 0;
   out_3015220250778787201[15] = 0;
   out_3015220250778787201[16] = 0;
   out_3015220250778787201[17] = 0;
   out_3015220250778787201[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3015220250778787201[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3015220250778787201[20] = 0;
   out_3015220250778787201[21] = 0;
   out_3015220250778787201[22] = 0;
   out_3015220250778787201[23] = 0;
   out_3015220250778787201[24] = 0;
   out_3015220250778787201[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3015220250778787201[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3015220250778787201[27] = 0;
   out_3015220250778787201[28] = 0;
   out_3015220250778787201[29] = 0;
   out_3015220250778787201[30] = 0;
   out_3015220250778787201[31] = 0;
   out_3015220250778787201[32] = 0;
   out_3015220250778787201[33] = 0;
   out_3015220250778787201[34] = 0;
   out_3015220250778787201[35] = 0;
   out_3015220250778787201[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3015220250778787201[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3015220250778787201[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3015220250778787201[39] = 0;
   out_3015220250778787201[40] = 0;
   out_3015220250778787201[41] = 0;
   out_3015220250778787201[42] = 0;
   out_3015220250778787201[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3015220250778787201[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3015220250778787201[45] = 0;
   out_3015220250778787201[46] = 0;
   out_3015220250778787201[47] = 0;
   out_3015220250778787201[48] = 0;
   out_3015220250778787201[49] = 0;
   out_3015220250778787201[50] = 0;
   out_3015220250778787201[51] = 0;
   out_3015220250778787201[52] = 0;
   out_3015220250778787201[53] = 0;
   out_3015220250778787201[54] = 0;
   out_3015220250778787201[55] = 0;
   out_3015220250778787201[56] = 0;
   out_3015220250778787201[57] = 1;
   out_3015220250778787201[58] = 0;
   out_3015220250778787201[59] = 0;
   out_3015220250778787201[60] = 0;
   out_3015220250778787201[61] = 0;
   out_3015220250778787201[62] = 0;
   out_3015220250778787201[63] = 0;
   out_3015220250778787201[64] = 0;
   out_3015220250778787201[65] = 0;
   out_3015220250778787201[66] = dt;
   out_3015220250778787201[67] = 0;
   out_3015220250778787201[68] = 0;
   out_3015220250778787201[69] = 0;
   out_3015220250778787201[70] = 0;
   out_3015220250778787201[71] = 0;
   out_3015220250778787201[72] = 0;
   out_3015220250778787201[73] = 0;
   out_3015220250778787201[74] = 0;
   out_3015220250778787201[75] = 0;
   out_3015220250778787201[76] = 1;
   out_3015220250778787201[77] = 0;
   out_3015220250778787201[78] = 0;
   out_3015220250778787201[79] = 0;
   out_3015220250778787201[80] = 0;
   out_3015220250778787201[81] = 0;
   out_3015220250778787201[82] = 0;
   out_3015220250778787201[83] = 0;
   out_3015220250778787201[84] = 0;
   out_3015220250778787201[85] = dt;
   out_3015220250778787201[86] = 0;
   out_3015220250778787201[87] = 0;
   out_3015220250778787201[88] = 0;
   out_3015220250778787201[89] = 0;
   out_3015220250778787201[90] = 0;
   out_3015220250778787201[91] = 0;
   out_3015220250778787201[92] = 0;
   out_3015220250778787201[93] = 0;
   out_3015220250778787201[94] = 0;
   out_3015220250778787201[95] = 1;
   out_3015220250778787201[96] = 0;
   out_3015220250778787201[97] = 0;
   out_3015220250778787201[98] = 0;
   out_3015220250778787201[99] = 0;
   out_3015220250778787201[100] = 0;
   out_3015220250778787201[101] = 0;
   out_3015220250778787201[102] = 0;
   out_3015220250778787201[103] = 0;
   out_3015220250778787201[104] = dt;
   out_3015220250778787201[105] = 0;
   out_3015220250778787201[106] = 0;
   out_3015220250778787201[107] = 0;
   out_3015220250778787201[108] = 0;
   out_3015220250778787201[109] = 0;
   out_3015220250778787201[110] = 0;
   out_3015220250778787201[111] = 0;
   out_3015220250778787201[112] = 0;
   out_3015220250778787201[113] = 0;
   out_3015220250778787201[114] = 1;
   out_3015220250778787201[115] = 0;
   out_3015220250778787201[116] = 0;
   out_3015220250778787201[117] = 0;
   out_3015220250778787201[118] = 0;
   out_3015220250778787201[119] = 0;
   out_3015220250778787201[120] = 0;
   out_3015220250778787201[121] = 0;
   out_3015220250778787201[122] = 0;
   out_3015220250778787201[123] = 0;
   out_3015220250778787201[124] = 0;
   out_3015220250778787201[125] = 0;
   out_3015220250778787201[126] = 0;
   out_3015220250778787201[127] = 0;
   out_3015220250778787201[128] = 0;
   out_3015220250778787201[129] = 0;
   out_3015220250778787201[130] = 0;
   out_3015220250778787201[131] = 0;
   out_3015220250778787201[132] = 0;
   out_3015220250778787201[133] = 1;
   out_3015220250778787201[134] = 0;
   out_3015220250778787201[135] = 0;
   out_3015220250778787201[136] = 0;
   out_3015220250778787201[137] = 0;
   out_3015220250778787201[138] = 0;
   out_3015220250778787201[139] = 0;
   out_3015220250778787201[140] = 0;
   out_3015220250778787201[141] = 0;
   out_3015220250778787201[142] = 0;
   out_3015220250778787201[143] = 0;
   out_3015220250778787201[144] = 0;
   out_3015220250778787201[145] = 0;
   out_3015220250778787201[146] = 0;
   out_3015220250778787201[147] = 0;
   out_3015220250778787201[148] = 0;
   out_3015220250778787201[149] = 0;
   out_3015220250778787201[150] = 0;
   out_3015220250778787201[151] = 0;
   out_3015220250778787201[152] = 1;
   out_3015220250778787201[153] = 0;
   out_3015220250778787201[154] = 0;
   out_3015220250778787201[155] = 0;
   out_3015220250778787201[156] = 0;
   out_3015220250778787201[157] = 0;
   out_3015220250778787201[158] = 0;
   out_3015220250778787201[159] = 0;
   out_3015220250778787201[160] = 0;
   out_3015220250778787201[161] = 0;
   out_3015220250778787201[162] = 0;
   out_3015220250778787201[163] = 0;
   out_3015220250778787201[164] = 0;
   out_3015220250778787201[165] = 0;
   out_3015220250778787201[166] = 0;
   out_3015220250778787201[167] = 0;
   out_3015220250778787201[168] = 0;
   out_3015220250778787201[169] = 0;
   out_3015220250778787201[170] = 0;
   out_3015220250778787201[171] = 1;
   out_3015220250778787201[172] = 0;
   out_3015220250778787201[173] = 0;
   out_3015220250778787201[174] = 0;
   out_3015220250778787201[175] = 0;
   out_3015220250778787201[176] = 0;
   out_3015220250778787201[177] = 0;
   out_3015220250778787201[178] = 0;
   out_3015220250778787201[179] = 0;
   out_3015220250778787201[180] = 0;
   out_3015220250778787201[181] = 0;
   out_3015220250778787201[182] = 0;
   out_3015220250778787201[183] = 0;
   out_3015220250778787201[184] = 0;
   out_3015220250778787201[185] = 0;
   out_3015220250778787201[186] = 0;
   out_3015220250778787201[187] = 0;
   out_3015220250778787201[188] = 0;
   out_3015220250778787201[189] = 0;
   out_3015220250778787201[190] = 1;
   out_3015220250778787201[191] = 0;
   out_3015220250778787201[192] = 0;
   out_3015220250778787201[193] = 0;
   out_3015220250778787201[194] = 0;
   out_3015220250778787201[195] = 0;
   out_3015220250778787201[196] = 0;
   out_3015220250778787201[197] = 0;
   out_3015220250778787201[198] = 0;
   out_3015220250778787201[199] = 0;
   out_3015220250778787201[200] = 0;
   out_3015220250778787201[201] = 0;
   out_3015220250778787201[202] = 0;
   out_3015220250778787201[203] = 0;
   out_3015220250778787201[204] = 0;
   out_3015220250778787201[205] = 0;
   out_3015220250778787201[206] = 0;
   out_3015220250778787201[207] = 0;
   out_3015220250778787201[208] = 0;
   out_3015220250778787201[209] = 1;
   out_3015220250778787201[210] = 0;
   out_3015220250778787201[211] = 0;
   out_3015220250778787201[212] = 0;
   out_3015220250778787201[213] = 0;
   out_3015220250778787201[214] = 0;
   out_3015220250778787201[215] = 0;
   out_3015220250778787201[216] = 0;
   out_3015220250778787201[217] = 0;
   out_3015220250778787201[218] = 0;
   out_3015220250778787201[219] = 0;
   out_3015220250778787201[220] = 0;
   out_3015220250778787201[221] = 0;
   out_3015220250778787201[222] = 0;
   out_3015220250778787201[223] = 0;
   out_3015220250778787201[224] = 0;
   out_3015220250778787201[225] = 0;
   out_3015220250778787201[226] = 0;
   out_3015220250778787201[227] = 0;
   out_3015220250778787201[228] = 1;
   out_3015220250778787201[229] = 0;
   out_3015220250778787201[230] = 0;
   out_3015220250778787201[231] = 0;
   out_3015220250778787201[232] = 0;
   out_3015220250778787201[233] = 0;
   out_3015220250778787201[234] = 0;
   out_3015220250778787201[235] = 0;
   out_3015220250778787201[236] = 0;
   out_3015220250778787201[237] = 0;
   out_3015220250778787201[238] = 0;
   out_3015220250778787201[239] = 0;
   out_3015220250778787201[240] = 0;
   out_3015220250778787201[241] = 0;
   out_3015220250778787201[242] = 0;
   out_3015220250778787201[243] = 0;
   out_3015220250778787201[244] = 0;
   out_3015220250778787201[245] = 0;
   out_3015220250778787201[246] = 0;
   out_3015220250778787201[247] = 1;
   out_3015220250778787201[248] = 0;
   out_3015220250778787201[249] = 0;
   out_3015220250778787201[250] = 0;
   out_3015220250778787201[251] = 0;
   out_3015220250778787201[252] = 0;
   out_3015220250778787201[253] = 0;
   out_3015220250778787201[254] = 0;
   out_3015220250778787201[255] = 0;
   out_3015220250778787201[256] = 0;
   out_3015220250778787201[257] = 0;
   out_3015220250778787201[258] = 0;
   out_3015220250778787201[259] = 0;
   out_3015220250778787201[260] = 0;
   out_3015220250778787201[261] = 0;
   out_3015220250778787201[262] = 0;
   out_3015220250778787201[263] = 0;
   out_3015220250778787201[264] = 0;
   out_3015220250778787201[265] = 0;
   out_3015220250778787201[266] = 1;
   out_3015220250778787201[267] = 0;
   out_3015220250778787201[268] = 0;
   out_3015220250778787201[269] = 0;
   out_3015220250778787201[270] = 0;
   out_3015220250778787201[271] = 0;
   out_3015220250778787201[272] = 0;
   out_3015220250778787201[273] = 0;
   out_3015220250778787201[274] = 0;
   out_3015220250778787201[275] = 0;
   out_3015220250778787201[276] = 0;
   out_3015220250778787201[277] = 0;
   out_3015220250778787201[278] = 0;
   out_3015220250778787201[279] = 0;
   out_3015220250778787201[280] = 0;
   out_3015220250778787201[281] = 0;
   out_3015220250778787201[282] = 0;
   out_3015220250778787201[283] = 0;
   out_3015220250778787201[284] = 0;
   out_3015220250778787201[285] = 1;
   out_3015220250778787201[286] = 0;
   out_3015220250778787201[287] = 0;
   out_3015220250778787201[288] = 0;
   out_3015220250778787201[289] = 0;
   out_3015220250778787201[290] = 0;
   out_3015220250778787201[291] = 0;
   out_3015220250778787201[292] = 0;
   out_3015220250778787201[293] = 0;
   out_3015220250778787201[294] = 0;
   out_3015220250778787201[295] = 0;
   out_3015220250778787201[296] = 0;
   out_3015220250778787201[297] = 0;
   out_3015220250778787201[298] = 0;
   out_3015220250778787201[299] = 0;
   out_3015220250778787201[300] = 0;
   out_3015220250778787201[301] = 0;
   out_3015220250778787201[302] = 0;
   out_3015220250778787201[303] = 0;
   out_3015220250778787201[304] = 1;
   out_3015220250778787201[305] = 0;
   out_3015220250778787201[306] = 0;
   out_3015220250778787201[307] = 0;
   out_3015220250778787201[308] = 0;
   out_3015220250778787201[309] = 0;
   out_3015220250778787201[310] = 0;
   out_3015220250778787201[311] = 0;
   out_3015220250778787201[312] = 0;
   out_3015220250778787201[313] = 0;
   out_3015220250778787201[314] = 0;
   out_3015220250778787201[315] = 0;
   out_3015220250778787201[316] = 0;
   out_3015220250778787201[317] = 0;
   out_3015220250778787201[318] = 0;
   out_3015220250778787201[319] = 0;
   out_3015220250778787201[320] = 0;
   out_3015220250778787201[321] = 0;
   out_3015220250778787201[322] = 0;
   out_3015220250778787201[323] = 1;
}
void h_4(double *state, double *unused, double *out_597021366061506697) {
   out_597021366061506697[0] = state[6] + state[9];
   out_597021366061506697[1] = state[7] + state[10];
   out_597021366061506697[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3624565405128650811) {
   out_3624565405128650811[0] = 0;
   out_3624565405128650811[1] = 0;
   out_3624565405128650811[2] = 0;
   out_3624565405128650811[3] = 0;
   out_3624565405128650811[4] = 0;
   out_3624565405128650811[5] = 0;
   out_3624565405128650811[6] = 1;
   out_3624565405128650811[7] = 0;
   out_3624565405128650811[8] = 0;
   out_3624565405128650811[9] = 1;
   out_3624565405128650811[10] = 0;
   out_3624565405128650811[11] = 0;
   out_3624565405128650811[12] = 0;
   out_3624565405128650811[13] = 0;
   out_3624565405128650811[14] = 0;
   out_3624565405128650811[15] = 0;
   out_3624565405128650811[16] = 0;
   out_3624565405128650811[17] = 0;
   out_3624565405128650811[18] = 0;
   out_3624565405128650811[19] = 0;
   out_3624565405128650811[20] = 0;
   out_3624565405128650811[21] = 0;
   out_3624565405128650811[22] = 0;
   out_3624565405128650811[23] = 0;
   out_3624565405128650811[24] = 0;
   out_3624565405128650811[25] = 1;
   out_3624565405128650811[26] = 0;
   out_3624565405128650811[27] = 0;
   out_3624565405128650811[28] = 1;
   out_3624565405128650811[29] = 0;
   out_3624565405128650811[30] = 0;
   out_3624565405128650811[31] = 0;
   out_3624565405128650811[32] = 0;
   out_3624565405128650811[33] = 0;
   out_3624565405128650811[34] = 0;
   out_3624565405128650811[35] = 0;
   out_3624565405128650811[36] = 0;
   out_3624565405128650811[37] = 0;
   out_3624565405128650811[38] = 0;
   out_3624565405128650811[39] = 0;
   out_3624565405128650811[40] = 0;
   out_3624565405128650811[41] = 0;
   out_3624565405128650811[42] = 0;
   out_3624565405128650811[43] = 0;
   out_3624565405128650811[44] = 1;
   out_3624565405128650811[45] = 0;
   out_3624565405128650811[46] = 0;
   out_3624565405128650811[47] = 1;
   out_3624565405128650811[48] = 0;
   out_3624565405128650811[49] = 0;
   out_3624565405128650811[50] = 0;
   out_3624565405128650811[51] = 0;
   out_3624565405128650811[52] = 0;
   out_3624565405128650811[53] = 0;
}
void h_10(double *state, double *unused, double *out_5914086608734437117) {
   out_5914086608734437117[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5914086608734437117[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5914086608734437117[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8960348806644161578) {
   out_8960348806644161578[0] = 0;
   out_8960348806644161578[1] = 9.8100000000000005*cos(state[1]);
   out_8960348806644161578[2] = 0;
   out_8960348806644161578[3] = 0;
   out_8960348806644161578[4] = -state[8];
   out_8960348806644161578[5] = state[7];
   out_8960348806644161578[6] = 0;
   out_8960348806644161578[7] = state[5];
   out_8960348806644161578[8] = -state[4];
   out_8960348806644161578[9] = 0;
   out_8960348806644161578[10] = 0;
   out_8960348806644161578[11] = 0;
   out_8960348806644161578[12] = 1;
   out_8960348806644161578[13] = 0;
   out_8960348806644161578[14] = 0;
   out_8960348806644161578[15] = 1;
   out_8960348806644161578[16] = 0;
   out_8960348806644161578[17] = 0;
   out_8960348806644161578[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8960348806644161578[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8960348806644161578[20] = 0;
   out_8960348806644161578[21] = state[8];
   out_8960348806644161578[22] = 0;
   out_8960348806644161578[23] = -state[6];
   out_8960348806644161578[24] = -state[5];
   out_8960348806644161578[25] = 0;
   out_8960348806644161578[26] = state[3];
   out_8960348806644161578[27] = 0;
   out_8960348806644161578[28] = 0;
   out_8960348806644161578[29] = 0;
   out_8960348806644161578[30] = 0;
   out_8960348806644161578[31] = 1;
   out_8960348806644161578[32] = 0;
   out_8960348806644161578[33] = 0;
   out_8960348806644161578[34] = 1;
   out_8960348806644161578[35] = 0;
   out_8960348806644161578[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8960348806644161578[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8960348806644161578[38] = 0;
   out_8960348806644161578[39] = -state[7];
   out_8960348806644161578[40] = state[6];
   out_8960348806644161578[41] = 0;
   out_8960348806644161578[42] = state[4];
   out_8960348806644161578[43] = -state[3];
   out_8960348806644161578[44] = 0;
   out_8960348806644161578[45] = 0;
   out_8960348806644161578[46] = 0;
   out_8960348806644161578[47] = 0;
   out_8960348806644161578[48] = 0;
   out_8960348806644161578[49] = 0;
   out_8960348806644161578[50] = 1;
   out_8960348806644161578[51] = 0;
   out_8960348806644161578[52] = 0;
   out_8960348806644161578[53] = 1;
}
void h_13(double *state, double *unused, double *out_8425126202907977474) {
   out_8425126202907977474[0] = state[3];
   out_8425126202907977474[1] = state[4];
   out_8425126202907977474[2] = state[5];
}
void H_13(double *state, double *unused, double *out_412291579796318010) {
   out_412291579796318010[0] = 0;
   out_412291579796318010[1] = 0;
   out_412291579796318010[2] = 0;
   out_412291579796318010[3] = 1;
   out_412291579796318010[4] = 0;
   out_412291579796318010[5] = 0;
   out_412291579796318010[6] = 0;
   out_412291579796318010[7] = 0;
   out_412291579796318010[8] = 0;
   out_412291579796318010[9] = 0;
   out_412291579796318010[10] = 0;
   out_412291579796318010[11] = 0;
   out_412291579796318010[12] = 0;
   out_412291579796318010[13] = 0;
   out_412291579796318010[14] = 0;
   out_412291579796318010[15] = 0;
   out_412291579796318010[16] = 0;
   out_412291579796318010[17] = 0;
   out_412291579796318010[18] = 0;
   out_412291579796318010[19] = 0;
   out_412291579796318010[20] = 0;
   out_412291579796318010[21] = 0;
   out_412291579796318010[22] = 1;
   out_412291579796318010[23] = 0;
   out_412291579796318010[24] = 0;
   out_412291579796318010[25] = 0;
   out_412291579796318010[26] = 0;
   out_412291579796318010[27] = 0;
   out_412291579796318010[28] = 0;
   out_412291579796318010[29] = 0;
   out_412291579796318010[30] = 0;
   out_412291579796318010[31] = 0;
   out_412291579796318010[32] = 0;
   out_412291579796318010[33] = 0;
   out_412291579796318010[34] = 0;
   out_412291579796318010[35] = 0;
   out_412291579796318010[36] = 0;
   out_412291579796318010[37] = 0;
   out_412291579796318010[38] = 0;
   out_412291579796318010[39] = 0;
   out_412291579796318010[40] = 0;
   out_412291579796318010[41] = 1;
   out_412291579796318010[42] = 0;
   out_412291579796318010[43] = 0;
   out_412291579796318010[44] = 0;
   out_412291579796318010[45] = 0;
   out_412291579796318010[46] = 0;
   out_412291579796318010[47] = 0;
   out_412291579796318010[48] = 0;
   out_412291579796318010[49] = 0;
   out_412291579796318010[50] = 0;
   out_412291579796318010[51] = 0;
   out_412291579796318010[52] = 0;
   out_412291579796318010[53] = 0;
}
void h_14(double *state, double *unused, double *out_2779692672946926767) {
   out_2779692672946926767[0] = state[6];
   out_2779692672946926767[1] = state[7];
   out_2779692672946926767[2] = state[8];
}
void H_14(double *state, double *unused, double *out_338675451210833718) {
   out_338675451210833718[0] = 0;
   out_338675451210833718[1] = 0;
   out_338675451210833718[2] = 0;
   out_338675451210833718[3] = 0;
   out_338675451210833718[4] = 0;
   out_338675451210833718[5] = 0;
   out_338675451210833718[6] = 1;
   out_338675451210833718[7] = 0;
   out_338675451210833718[8] = 0;
   out_338675451210833718[9] = 0;
   out_338675451210833718[10] = 0;
   out_338675451210833718[11] = 0;
   out_338675451210833718[12] = 0;
   out_338675451210833718[13] = 0;
   out_338675451210833718[14] = 0;
   out_338675451210833718[15] = 0;
   out_338675451210833718[16] = 0;
   out_338675451210833718[17] = 0;
   out_338675451210833718[18] = 0;
   out_338675451210833718[19] = 0;
   out_338675451210833718[20] = 0;
   out_338675451210833718[21] = 0;
   out_338675451210833718[22] = 0;
   out_338675451210833718[23] = 0;
   out_338675451210833718[24] = 0;
   out_338675451210833718[25] = 1;
   out_338675451210833718[26] = 0;
   out_338675451210833718[27] = 0;
   out_338675451210833718[28] = 0;
   out_338675451210833718[29] = 0;
   out_338675451210833718[30] = 0;
   out_338675451210833718[31] = 0;
   out_338675451210833718[32] = 0;
   out_338675451210833718[33] = 0;
   out_338675451210833718[34] = 0;
   out_338675451210833718[35] = 0;
   out_338675451210833718[36] = 0;
   out_338675451210833718[37] = 0;
   out_338675451210833718[38] = 0;
   out_338675451210833718[39] = 0;
   out_338675451210833718[40] = 0;
   out_338675451210833718[41] = 0;
   out_338675451210833718[42] = 0;
   out_338675451210833718[43] = 0;
   out_338675451210833718[44] = 1;
   out_338675451210833718[45] = 0;
   out_338675451210833718[46] = 0;
   out_338675451210833718[47] = 0;
   out_338675451210833718[48] = 0;
   out_338675451210833718[49] = 0;
   out_338675451210833718[50] = 0;
   out_338675451210833718[51] = 0;
   out_338675451210833718[52] = 0;
   out_338675451210833718[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_2154331471386048889) {
  err_fun(nom_x, delta_x, out_2154331471386048889);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8657363058238728605) {
  inv_err_fun(nom_x, true_x, out_8657363058238728605);
}
void pose_H_mod_fun(double *state, double *out_4378726407183363418) {
  H_mod_fun(state, out_4378726407183363418);
}
void pose_f_fun(double *state, double dt, double *out_5195038445783001597) {
  f_fun(state,  dt, out_5195038445783001597);
}
void pose_F_fun(double *state, double dt, double *out_3015220250778787201) {
  F_fun(state,  dt, out_3015220250778787201);
}
void pose_h_4(double *state, double *unused, double *out_597021366061506697) {
  h_4(state, unused, out_597021366061506697);
}
void pose_H_4(double *state, double *unused, double *out_3624565405128650811) {
  H_4(state, unused, out_3624565405128650811);
}
void pose_h_10(double *state, double *unused, double *out_5914086608734437117) {
  h_10(state, unused, out_5914086608734437117);
}
void pose_H_10(double *state, double *unused, double *out_8960348806644161578) {
  H_10(state, unused, out_8960348806644161578);
}
void pose_h_13(double *state, double *unused, double *out_8425126202907977474) {
  h_13(state, unused, out_8425126202907977474);
}
void pose_H_13(double *state, double *unused, double *out_412291579796318010) {
  H_13(state, unused, out_412291579796318010);
}
void pose_h_14(double *state, double *unused, double *out_2779692672946926767) {
  h_14(state, unused, out_2779692672946926767);
}
void pose_H_14(double *state, double *unused, double *out_338675451210833718) {
  H_14(state, unused, out_338675451210833718);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
