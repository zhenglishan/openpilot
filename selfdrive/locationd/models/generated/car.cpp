#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_309734491217568898) {
   out_309734491217568898[0] = delta_x[0] + nom_x[0];
   out_309734491217568898[1] = delta_x[1] + nom_x[1];
   out_309734491217568898[2] = delta_x[2] + nom_x[2];
   out_309734491217568898[3] = delta_x[3] + nom_x[3];
   out_309734491217568898[4] = delta_x[4] + nom_x[4];
   out_309734491217568898[5] = delta_x[5] + nom_x[5];
   out_309734491217568898[6] = delta_x[6] + nom_x[6];
   out_309734491217568898[7] = delta_x[7] + nom_x[7];
   out_309734491217568898[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1598877300122141743) {
   out_1598877300122141743[0] = -nom_x[0] + true_x[0];
   out_1598877300122141743[1] = -nom_x[1] + true_x[1];
   out_1598877300122141743[2] = -nom_x[2] + true_x[2];
   out_1598877300122141743[3] = -nom_x[3] + true_x[3];
   out_1598877300122141743[4] = -nom_x[4] + true_x[4];
   out_1598877300122141743[5] = -nom_x[5] + true_x[5];
   out_1598877300122141743[6] = -nom_x[6] + true_x[6];
   out_1598877300122141743[7] = -nom_x[7] + true_x[7];
   out_1598877300122141743[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7156428947201751020) {
   out_7156428947201751020[0] = 1.0;
   out_7156428947201751020[1] = 0.0;
   out_7156428947201751020[2] = 0.0;
   out_7156428947201751020[3] = 0.0;
   out_7156428947201751020[4] = 0.0;
   out_7156428947201751020[5] = 0.0;
   out_7156428947201751020[6] = 0.0;
   out_7156428947201751020[7] = 0.0;
   out_7156428947201751020[8] = 0.0;
   out_7156428947201751020[9] = 0.0;
   out_7156428947201751020[10] = 1.0;
   out_7156428947201751020[11] = 0.0;
   out_7156428947201751020[12] = 0.0;
   out_7156428947201751020[13] = 0.0;
   out_7156428947201751020[14] = 0.0;
   out_7156428947201751020[15] = 0.0;
   out_7156428947201751020[16] = 0.0;
   out_7156428947201751020[17] = 0.0;
   out_7156428947201751020[18] = 0.0;
   out_7156428947201751020[19] = 0.0;
   out_7156428947201751020[20] = 1.0;
   out_7156428947201751020[21] = 0.0;
   out_7156428947201751020[22] = 0.0;
   out_7156428947201751020[23] = 0.0;
   out_7156428947201751020[24] = 0.0;
   out_7156428947201751020[25] = 0.0;
   out_7156428947201751020[26] = 0.0;
   out_7156428947201751020[27] = 0.0;
   out_7156428947201751020[28] = 0.0;
   out_7156428947201751020[29] = 0.0;
   out_7156428947201751020[30] = 1.0;
   out_7156428947201751020[31] = 0.0;
   out_7156428947201751020[32] = 0.0;
   out_7156428947201751020[33] = 0.0;
   out_7156428947201751020[34] = 0.0;
   out_7156428947201751020[35] = 0.0;
   out_7156428947201751020[36] = 0.0;
   out_7156428947201751020[37] = 0.0;
   out_7156428947201751020[38] = 0.0;
   out_7156428947201751020[39] = 0.0;
   out_7156428947201751020[40] = 1.0;
   out_7156428947201751020[41] = 0.0;
   out_7156428947201751020[42] = 0.0;
   out_7156428947201751020[43] = 0.0;
   out_7156428947201751020[44] = 0.0;
   out_7156428947201751020[45] = 0.0;
   out_7156428947201751020[46] = 0.0;
   out_7156428947201751020[47] = 0.0;
   out_7156428947201751020[48] = 0.0;
   out_7156428947201751020[49] = 0.0;
   out_7156428947201751020[50] = 1.0;
   out_7156428947201751020[51] = 0.0;
   out_7156428947201751020[52] = 0.0;
   out_7156428947201751020[53] = 0.0;
   out_7156428947201751020[54] = 0.0;
   out_7156428947201751020[55] = 0.0;
   out_7156428947201751020[56] = 0.0;
   out_7156428947201751020[57] = 0.0;
   out_7156428947201751020[58] = 0.0;
   out_7156428947201751020[59] = 0.0;
   out_7156428947201751020[60] = 1.0;
   out_7156428947201751020[61] = 0.0;
   out_7156428947201751020[62] = 0.0;
   out_7156428947201751020[63] = 0.0;
   out_7156428947201751020[64] = 0.0;
   out_7156428947201751020[65] = 0.0;
   out_7156428947201751020[66] = 0.0;
   out_7156428947201751020[67] = 0.0;
   out_7156428947201751020[68] = 0.0;
   out_7156428947201751020[69] = 0.0;
   out_7156428947201751020[70] = 1.0;
   out_7156428947201751020[71] = 0.0;
   out_7156428947201751020[72] = 0.0;
   out_7156428947201751020[73] = 0.0;
   out_7156428947201751020[74] = 0.0;
   out_7156428947201751020[75] = 0.0;
   out_7156428947201751020[76] = 0.0;
   out_7156428947201751020[77] = 0.0;
   out_7156428947201751020[78] = 0.0;
   out_7156428947201751020[79] = 0.0;
   out_7156428947201751020[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8687771038779355274) {
   out_8687771038779355274[0] = state[0];
   out_8687771038779355274[1] = state[1];
   out_8687771038779355274[2] = state[2];
   out_8687771038779355274[3] = state[3];
   out_8687771038779355274[4] = state[4];
   out_8687771038779355274[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8687771038779355274[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8687771038779355274[7] = state[7];
   out_8687771038779355274[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2586617639560263372) {
   out_2586617639560263372[0] = 1;
   out_2586617639560263372[1] = 0;
   out_2586617639560263372[2] = 0;
   out_2586617639560263372[3] = 0;
   out_2586617639560263372[4] = 0;
   out_2586617639560263372[5] = 0;
   out_2586617639560263372[6] = 0;
   out_2586617639560263372[7] = 0;
   out_2586617639560263372[8] = 0;
   out_2586617639560263372[9] = 0;
   out_2586617639560263372[10] = 1;
   out_2586617639560263372[11] = 0;
   out_2586617639560263372[12] = 0;
   out_2586617639560263372[13] = 0;
   out_2586617639560263372[14] = 0;
   out_2586617639560263372[15] = 0;
   out_2586617639560263372[16] = 0;
   out_2586617639560263372[17] = 0;
   out_2586617639560263372[18] = 0;
   out_2586617639560263372[19] = 0;
   out_2586617639560263372[20] = 1;
   out_2586617639560263372[21] = 0;
   out_2586617639560263372[22] = 0;
   out_2586617639560263372[23] = 0;
   out_2586617639560263372[24] = 0;
   out_2586617639560263372[25] = 0;
   out_2586617639560263372[26] = 0;
   out_2586617639560263372[27] = 0;
   out_2586617639560263372[28] = 0;
   out_2586617639560263372[29] = 0;
   out_2586617639560263372[30] = 1;
   out_2586617639560263372[31] = 0;
   out_2586617639560263372[32] = 0;
   out_2586617639560263372[33] = 0;
   out_2586617639560263372[34] = 0;
   out_2586617639560263372[35] = 0;
   out_2586617639560263372[36] = 0;
   out_2586617639560263372[37] = 0;
   out_2586617639560263372[38] = 0;
   out_2586617639560263372[39] = 0;
   out_2586617639560263372[40] = 1;
   out_2586617639560263372[41] = 0;
   out_2586617639560263372[42] = 0;
   out_2586617639560263372[43] = 0;
   out_2586617639560263372[44] = 0;
   out_2586617639560263372[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2586617639560263372[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2586617639560263372[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2586617639560263372[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2586617639560263372[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2586617639560263372[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2586617639560263372[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2586617639560263372[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2586617639560263372[53] = -9.8100000000000005*dt;
   out_2586617639560263372[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2586617639560263372[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2586617639560263372[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2586617639560263372[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2586617639560263372[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2586617639560263372[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2586617639560263372[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2586617639560263372[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2586617639560263372[62] = 0;
   out_2586617639560263372[63] = 0;
   out_2586617639560263372[64] = 0;
   out_2586617639560263372[65] = 0;
   out_2586617639560263372[66] = 0;
   out_2586617639560263372[67] = 0;
   out_2586617639560263372[68] = 0;
   out_2586617639560263372[69] = 0;
   out_2586617639560263372[70] = 1;
   out_2586617639560263372[71] = 0;
   out_2586617639560263372[72] = 0;
   out_2586617639560263372[73] = 0;
   out_2586617639560263372[74] = 0;
   out_2586617639560263372[75] = 0;
   out_2586617639560263372[76] = 0;
   out_2586617639560263372[77] = 0;
   out_2586617639560263372[78] = 0;
   out_2586617639560263372[79] = 0;
   out_2586617639560263372[80] = 1;
}
void h_25(double *state, double *unused, double *out_416627313290698941) {
   out_416627313290698941[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2036759278710486217) {
   out_2036759278710486217[0] = 0;
   out_2036759278710486217[1] = 0;
   out_2036759278710486217[2] = 0;
   out_2036759278710486217[3] = 0;
   out_2036759278710486217[4] = 0;
   out_2036759278710486217[5] = 0;
   out_2036759278710486217[6] = 1;
   out_2036759278710486217[7] = 0;
   out_2036759278710486217[8] = 0;
}
void h_24(double *state, double *unused, double *out_3126241056150136646) {
   out_3126241056150136646[0] = state[4];
   out_3126241056150136646[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4209408877715985783) {
   out_4209408877715985783[0] = 0;
   out_4209408877715985783[1] = 0;
   out_4209408877715985783[2] = 0;
   out_4209408877715985783[3] = 0;
   out_4209408877715985783[4] = 1;
   out_4209408877715985783[5] = 0;
   out_4209408877715985783[6] = 0;
   out_4209408877715985783[7] = 0;
   out_4209408877715985783[8] = 0;
   out_4209408877715985783[9] = 0;
   out_4209408877715985783[10] = 0;
   out_4209408877715985783[11] = 0;
   out_4209408877715985783[12] = 0;
   out_4209408877715985783[13] = 0;
   out_4209408877715985783[14] = 1;
   out_4209408877715985783[15] = 0;
   out_4209408877715985783[16] = 0;
   out_4209408877715985783[17] = 0;
}
void h_30(double *state, double *unused, double *out_5803749869556315028) {
   out_5803749869556315028[0] = state[4];
}
void H_30(double *state, double *unused, double *out_481573679796762410) {
   out_481573679796762410[0] = 0;
   out_481573679796762410[1] = 0;
   out_481573679796762410[2] = 0;
   out_481573679796762410[3] = 0;
   out_481573679796762410[4] = 1;
   out_481573679796762410[5] = 0;
   out_481573679796762410[6] = 0;
   out_481573679796762410[7] = 0;
   out_481573679796762410[8] = 0;
}
void h_26(double *state, double *unused, double *out_802076601895469383) {
   out_802076601895469383[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1267766691050314384) {
   out_1267766691050314384[0] = 0;
   out_1267766691050314384[1] = 0;
   out_1267766691050314384[2] = 0;
   out_1267766691050314384[3] = 0;
   out_1267766691050314384[4] = 0;
   out_1267766691050314384[5] = 0;
   out_1267766691050314384[6] = 0;
   out_1267766691050314384[7] = 1;
   out_1267766691050314384[8] = 0;
}
void h_27(double *state, double *unused, double *out_6815668830704548087) {
   out_6815668830704548087[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2705167750980705627) {
   out_2705167750980705627[0] = 0;
   out_2705167750980705627[1] = 0;
   out_2705167750980705627[2] = 0;
   out_2705167750980705627[3] = 1;
   out_2705167750980705627[4] = 0;
   out_2705167750980705627[5] = 0;
   out_2705167750980705627[6] = 0;
   out_2705167750980705627[7] = 0;
   out_2705167750980705627[8] = 0;
}
void h_29(double *state, double *unused, double *out_3178219302450525737) {
   out_3178219302450525737[0] = state[1];
}
void H_29(double *state, double *unused, double *out_991805024111154594) {
   out_991805024111154594[0] = 0;
   out_991805024111154594[1] = 1;
   out_991805024111154594[2] = 0;
   out_991805024111154594[3] = 0;
   out_991805024111154594[4] = 0;
   out_991805024111154594[5] = 0;
   out_991805024111154594[6] = 0;
   out_991805024111154594[7] = 0;
   out_991805024111154594[8] = 0;
}
void h_28(double *state, double *unused, double *out_8594289191560670844) {
   out_8594289191560670844[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4090593992958375980) {
   out_4090593992958375980[0] = 1;
   out_4090593992958375980[1] = 0;
   out_4090593992958375980[2] = 0;
   out_4090593992958375980[3] = 0;
   out_4090593992958375980[4] = 0;
   out_4090593992958375980[5] = 0;
   out_4090593992958375980[6] = 0;
   out_4090593992958375980[7] = 0;
   out_4090593992958375980[8] = 0;
}
void h_31(double *state, double *unused, double *out_8080033367973041051) {
   out_8080033367973041051[0] = state[8];
}
void H_31(double *state, double *unused, double *out_641558588816962908) {
   out_641558588816962908[0] = 0;
   out_641558588816962908[1] = 0;
   out_641558588816962908[2] = 0;
   out_641558588816962908[3] = 0;
   out_641558588816962908[4] = 0;
   out_641558588816962908[5] = 0;
   out_641558588816962908[6] = 0;
   out_641558588816962908[7] = 0;
   out_641558588816962908[8] = 1;
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

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_309734491217568898) {
  err_fun(nom_x, delta_x, out_309734491217568898);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1598877300122141743) {
  inv_err_fun(nom_x, true_x, out_1598877300122141743);
}
void car_H_mod_fun(double *state, double *out_7156428947201751020) {
  H_mod_fun(state, out_7156428947201751020);
}
void car_f_fun(double *state, double dt, double *out_8687771038779355274) {
  f_fun(state,  dt, out_8687771038779355274);
}
void car_F_fun(double *state, double dt, double *out_2586617639560263372) {
  F_fun(state,  dt, out_2586617639560263372);
}
void car_h_25(double *state, double *unused, double *out_416627313290698941) {
  h_25(state, unused, out_416627313290698941);
}
void car_H_25(double *state, double *unused, double *out_2036759278710486217) {
  H_25(state, unused, out_2036759278710486217);
}
void car_h_24(double *state, double *unused, double *out_3126241056150136646) {
  h_24(state, unused, out_3126241056150136646);
}
void car_H_24(double *state, double *unused, double *out_4209408877715985783) {
  H_24(state, unused, out_4209408877715985783);
}
void car_h_30(double *state, double *unused, double *out_5803749869556315028) {
  h_30(state, unused, out_5803749869556315028);
}
void car_H_30(double *state, double *unused, double *out_481573679796762410) {
  H_30(state, unused, out_481573679796762410);
}
void car_h_26(double *state, double *unused, double *out_802076601895469383) {
  h_26(state, unused, out_802076601895469383);
}
void car_H_26(double *state, double *unused, double *out_1267766691050314384) {
  H_26(state, unused, out_1267766691050314384);
}
void car_h_27(double *state, double *unused, double *out_6815668830704548087) {
  h_27(state, unused, out_6815668830704548087);
}
void car_H_27(double *state, double *unused, double *out_2705167750980705627) {
  H_27(state, unused, out_2705167750980705627);
}
void car_h_29(double *state, double *unused, double *out_3178219302450525737) {
  h_29(state, unused, out_3178219302450525737);
}
void car_H_29(double *state, double *unused, double *out_991805024111154594) {
  H_29(state, unused, out_991805024111154594);
}
void car_h_28(double *state, double *unused, double *out_8594289191560670844) {
  h_28(state, unused, out_8594289191560670844);
}
void car_H_28(double *state, double *unused, double *out_4090593992958375980) {
  H_28(state, unused, out_4090593992958375980);
}
void car_h_31(double *state, double *unused, double *out_8080033367973041051) {
  h_31(state, unused, out_8080033367973041051);
}
void car_H_31(double *state, double *unused, double *out_641558588816962908) {
  H_31(state, unused, out_641558588816962908);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
