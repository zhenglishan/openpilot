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
 *                      Code generated with SymPy 1.13.2                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4326724362728314406) {
   out_4326724362728314406[0] = delta_x[0] + nom_x[0];
   out_4326724362728314406[1] = delta_x[1] + nom_x[1];
   out_4326724362728314406[2] = delta_x[2] + nom_x[2];
   out_4326724362728314406[3] = delta_x[3] + nom_x[3];
   out_4326724362728314406[4] = delta_x[4] + nom_x[4];
   out_4326724362728314406[5] = delta_x[5] + nom_x[5];
   out_4326724362728314406[6] = delta_x[6] + nom_x[6];
   out_4326724362728314406[7] = delta_x[7] + nom_x[7];
   out_4326724362728314406[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8532044662853727335) {
   out_8532044662853727335[0] = -nom_x[0] + true_x[0];
   out_8532044662853727335[1] = -nom_x[1] + true_x[1];
   out_8532044662853727335[2] = -nom_x[2] + true_x[2];
   out_8532044662853727335[3] = -nom_x[3] + true_x[3];
   out_8532044662853727335[4] = -nom_x[4] + true_x[4];
   out_8532044662853727335[5] = -nom_x[5] + true_x[5];
   out_8532044662853727335[6] = -nom_x[6] + true_x[6];
   out_8532044662853727335[7] = -nom_x[7] + true_x[7];
   out_8532044662853727335[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2818647783441972676) {
   out_2818647783441972676[0] = 1.0;
   out_2818647783441972676[1] = 0.0;
   out_2818647783441972676[2] = 0.0;
   out_2818647783441972676[3] = 0.0;
   out_2818647783441972676[4] = 0.0;
   out_2818647783441972676[5] = 0.0;
   out_2818647783441972676[6] = 0.0;
   out_2818647783441972676[7] = 0.0;
   out_2818647783441972676[8] = 0.0;
   out_2818647783441972676[9] = 0.0;
   out_2818647783441972676[10] = 1.0;
   out_2818647783441972676[11] = 0.0;
   out_2818647783441972676[12] = 0.0;
   out_2818647783441972676[13] = 0.0;
   out_2818647783441972676[14] = 0.0;
   out_2818647783441972676[15] = 0.0;
   out_2818647783441972676[16] = 0.0;
   out_2818647783441972676[17] = 0.0;
   out_2818647783441972676[18] = 0.0;
   out_2818647783441972676[19] = 0.0;
   out_2818647783441972676[20] = 1.0;
   out_2818647783441972676[21] = 0.0;
   out_2818647783441972676[22] = 0.0;
   out_2818647783441972676[23] = 0.0;
   out_2818647783441972676[24] = 0.0;
   out_2818647783441972676[25] = 0.0;
   out_2818647783441972676[26] = 0.0;
   out_2818647783441972676[27] = 0.0;
   out_2818647783441972676[28] = 0.0;
   out_2818647783441972676[29] = 0.0;
   out_2818647783441972676[30] = 1.0;
   out_2818647783441972676[31] = 0.0;
   out_2818647783441972676[32] = 0.0;
   out_2818647783441972676[33] = 0.0;
   out_2818647783441972676[34] = 0.0;
   out_2818647783441972676[35] = 0.0;
   out_2818647783441972676[36] = 0.0;
   out_2818647783441972676[37] = 0.0;
   out_2818647783441972676[38] = 0.0;
   out_2818647783441972676[39] = 0.0;
   out_2818647783441972676[40] = 1.0;
   out_2818647783441972676[41] = 0.0;
   out_2818647783441972676[42] = 0.0;
   out_2818647783441972676[43] = 0.0;
   out_2818647783441972676[44] = 0.0;
   out_2818647783441972676[45] = 0.0;
   out_2818647783441972676[46] = 0.0;
   out_2818647783441972676[47] = 0.0;
   out_2818647783441972676[48] = 0.0;
   out_2818647783441972676[49] = 0.0;
   out_2818647783441972676[50] = 1.0;
   out_2818647783441972676[51] = 0.0;
   out_2818647783441972676[52] = 0.0;
   out_2818647783441972676[53] = 0.0;
   out_2818647783441972676[54] = 0.0;
   out_2818647783441972676[55] = 0.0;
   out_2818647783441972676[56] = 0.0;
   out_2818647783441972676[57] = 0.0;
   out_2818647783441972676[58] = 0.0;
   out_2818647783441972676[59] = 0.0;
   out_2818647783441972676[60] = 1.0;
   out_2818647783441972676[61] = 0.0;
   out_2818647783441972676[62] = 0.0;
   out_2818647783441972676[63] = 0.0;
   out_2818647783441972676[64] = 0.0;
   out_2818647783441972676[65] = 0.0;
   out_2818647783441972676[66] = 0.0;
   out_2818647783441972676[67] = 0.0;
   out_2818647783441972676[68] = 0.0;
   out_2818647783441972676[69] = 0.0;
   out_2818647783441972676[70] = 1.0;
   out_2818647783441972676[71] = 0.0;
   out_2818647783441972676[72] = 0.0;
   out_2818647783441972676[73] = 0.0;
   out_2818647783441972676[74] = 0.0;
   out_2818647783441972676[75] = 0.0;
   out_2818647783441972676[76] = 0.0;
   out_2818647783441972676[77] = 0.0;
   out_2818647783441972676[78] = 0.0;
   out_2818647783441972676[79] = 0.0;
   out_2818647783441972676[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6342720054699409588) {
   out_6342720054699409588[0] = state[0];
   out_6342720054699409588[1] = state[1];
   out_6342720054699409588[2] = state[2];
   out_6342720054699409588[3] = state[3];
   out_6342720054699409588[4] = state[4];
   out_6342720054699409588[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6342720054699409588[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6342720054699409588[7] = state[7];
   out_6342720054699409588[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1989156126485308035) {
   out_1989156126485308035[0] = 1;
   out_1989156126485308035[1] = 0;
   out_1989156126485308035[2] = 0;
   out_1989156126485308035[3] = 0;
   out_1989156126485308035[4] = 0;
   out_1989156126485308035[5] = 0;
   out_1989156126485308035[6] = 0;
   out_1989156126485308035[7] = 0;
   out_1989156126485308035[8] = 0;
   out_1989156126485308035[9] = 0;
   out_1989156126485308035[10] = 1;
   out_1989156126485308035[11] = 0;
   out_1989156126485308035[12] = 0;
   out_1989156126485308035[13] = 0;
   out_1989156126485308035[14] = 0;
   out_1989156126485308035[15] = 0;
   out_1989156126485308035[16] = 0;
   out_1989156126485308035[17] = 0;
   out_1989156126485308035[18] = 0;
   out_1989156126485308035[19] = 0;
   out_1989156126485308035[20] = 1;
   out_1989156126485308035[21] = 0;
   out_1989156126485308035[22] = 0;
   out_1989156126485308035[23] = 0;
   out_1989156126485308035[24] = 0;
   out_1989156126485308035[25] = 0;
   out_1989156126485308035[26] = 0;
   out_1989156126485308035[27] = 0;
   out_1989156126485308035[28] = 0;
   out_1989156126485308035[29] = 0;
   out_1989156126485308035[30] = 1;
   out_1989156126485308035[31] = 0;
   out_1989156126485308035[32] = 0;
   out_1989156126485308035[33] = 0;
   out_1989156126485308035[34] = 0;
   out_1989156126485308035[35] = 0;
   out_1989156126485308035[36] = 0;
   out_1989156126485308035[37] = 0;
   out_1989156126485308035[38] = 0;
   out_1989156126485308035[39] = 0;
   out_1989156126485308035[40] = 1;
   out_1989156126485308035[41] = 0;
   out_1989156126485308035[42] = 0;
   out_1989156126485308035[43] = 0;
   out_1989156126485308035[44] = 0;
   out_1989156126485308035[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1989156126485308035[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1989156126485308035[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1989156126485308035[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1989156126485308035[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1989156126485308035[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1989156126485308035[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1989156126485308035[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1989156126485308035[53] = -9.8000000000000007*dt;
   out_1989156126485308035[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1989156126485308035[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1989156126485308035[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1989156126485308035[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1989156126485308035[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1989156126485308035[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1989156126485308035[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1989156126485308035[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1989156126485308035[62] = 0;
   out_1989156126485308035[63] = 0;
   out_1989156126485308035[64] = 0;
   out_1989156126485308035[65] = 0;
   out_1989156126485308035[66] = 0;
   out_1989156126485308035[67] = 0;
   out_1989156126485308035[68] = 0;
   out_1989156126485308035[69] = 0;
   out_1989156126485308035[70] = 1;
   out_1989156126485308035[71] = 0;
   out_1989156126485308035[72] = 0;
   out_1989156126485308035[73] = 0;
   out_1989156126485308035[74] = 0;
   out_1989156126485308035[75] = 0;
   out_1989156126485308035[76] = 0;
   out_1989156126485308035[77] = 0;
   out_1989156126485308035[78] = 0;
   out_1989156126485308035[79] = 0;
   out_1989156126485308035[80] = 1;
}
void h_25(double *state, double *unused, double *out_1366347176962782561) {
   out_1366347176962782561[0] = state[6];
}
void H_25(double *state, double *unused, double *out_488815686218317304) {
   out_488815686218317304[0] = 0;
   out_488815686218317304[1] = 0;
   out_488815686218317304[2] = 0;
   out_488815686218317304[3] = 0;
   out_488815686218317304[4] = 0;
   out_488815686218317304[5] = 0;
   out_488815686218317304[6] = 1;
   out_488815686218317304[7] = 0;
   out_488815686218317304[8] = 0;
}
void h_24(double *state, double *unused, double *out_7280803622898136788) {
   out_7280803622898136788[0] = state[4];
   out_7280803622898136788[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5357630551246024156) {
   out_5357630551246024156[0] = 0;
   out_5357630551246024156[1] = 0;
   out_5357630551246024156[2] = 0;
   out_5357630551246024156[3] = 0;
   out_5357630551246024156[4] = 1;
   out_5357630551246024156[5] = 0;
   out_5357630551246024156[6] = 0;
   out_5357630551246024156[7] = 0;
   out_5357630551246024156[8] = 0;
   out_5357630551246024156[9] = 0;
   out_5357630551246024156[10] = 0;
   out_5357630551246024156[11] = 0;
   out_5357630551246024156[12] = 0;
   out_5357630551246024156[13] = 0;
   out_5357630551246024156[14] = 1;
   out_5357630551246024156[15] = 0;
   out_5357630551246024156[16] = 0;
   out_5357630551246024156[17] = 0;
}
void h_30(double *state, double *unused, double *out_7810958307984275832) {
   out_7810958307984275832[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5016512016345925502) {
   out_5016512016345925502[0] = 0;
   out_5016512016345925502[1] = 0;
   out_5016512016345925502[2] = 0;
   out_5016512016345925502[3] = 0;
   out_5016512016345925502[4] = 1;
   out_5016512016345925502[5] = 0;
   out_5016512016345925502[6] = 0;
   out_5016512016345925502[7] = 0;
   out_5016512016345925502[8] = 0;
}
void h_26(double *state, double *unused, double *out_161613134672941490) {
   out_161613134672941490[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4230319005092373528) {
   out_4230319005092373528[0] = 0;
   out_4230319005092373528[1] = 0;
   out_4230319005092373528[2] = 0;
   out_4230319005092373528[3] = 0;
   out_4230319005092373528[4] = 0;
   out_4230319005092373528[5] = 0;
   out_4230319005092373528[6] = 0;
   out_4230319005092373528[7] = 1;
   out_4230319005092373528[8] = 0;
}
void h_27(double *state, double *unused, double *out_279620528606318234) {
   out_279620528606318234[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2792917945161982285) {
   out_2792917945161982285[0] = 0;
   out_2792917945161982285[1] = 0;
   out_2792917945161982285[2] = 0;
   out_2792917945161982285[3] = 1;
   out_2792917945161982285[4] = 0;
   out_2792917945161982285[5] = 0;
   out_2792917945161982285[6] = 0;
   out_2792917945161982285[7] = 0;
   out_2792917945161982285[8] = 0;
}
void h_29(double *state, double *unused, double *out_8217040152657421758) {
   out_8217040152657421758[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4506280672031533318) {
   out_4506280672031533318[0] = 0;
   out_4506280672031533318[1] = 1;
   out_4506280672031533318[2] = 0;
   out_4506280672031533318[3] = 0;
   out_4506280672031533318[4] = 0;
   out_4506280672031533318[5] = 0;
   out_4506280672031533318[6] = 0;
   out_4506280672031533318[7] = 0;
   out_4506280672031533318[8] = 0;
}
void h_28(double *state, double *unused, double *out_4677572609887947246) {
   out_4677572609887947246[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8858064384608487724) {
   out_8858064384608487724[0] = 1;
   out_8858064384608487724[1] = 0;
   out_8858064384608487724[2] = 0;
   out_8858064384608487724[3] = 0;
   out_8858064384608487724[4] = 0;
   out_8858064384608487724[5] = 0;
   out_8858064384608487724[6] = 0;
   out_8858064384608487724[7] = 0;
   out_8858064384608487724[8] = 0;
}
void h_31(double *state, double *unused, double *out_8583736215483029063) {
   out_8583736215483029063[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4856527107325725004) {
   out_4856527107325725004[0] = 0;
   out_4856527107325725004[1] = 0;
   out_4856527107325725004[2] = 0;
   out_4856527107325725004[3] = 0;
   out_4856527107325725004[4] = 0;
   out_4856527107325725004[5] = 0;
   out_4856527107325725004[6] = 0;
   out_4856527107325725004[7] = 0;
   out_4856527107325725004[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4326724362728314406) {
  err_fun(nom_x, delta_x, out_4326724362728314406);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8532044662853727335) {
  inv_err_fun(nom_x, true_x, out_8532044662853727335);
}
void car_H_mod_fun(double *state, double *out_2818647783441972676) {
  H_mod_fun(state, out_2818647783441972676);
}
void car_f_fun(double *state, double dt, double *out_6342720054699409588) {
  f_fun(state,  dt, out_6342720054699409588);
}
void car_F_fun(double *state, double dt, double *out_1989156126485308035) {
  F_fun(state,  dt, out_1989156126485308035);
}
void car_h_25(double *state, double *unused, double *out_1366347176962782561) {
  h_25(state, unused, out_1366347176962782561);
}
void car_H_25(double *state, double *unused, double *out_488815686218317304) {
  H_25(state, unused, out_488815686218317304);
}
void car_h_24(double *state, double *unused, double *out_7280803622898136788) {
  h_24(state, unused, out_7280803622898136788);
}
void car_H_24(double *state, double *unused, double *out_5357630551246024156) {
  H_24(state, unused, out_5357630551246024156);
}
void car_h_30(double *state, double *unused, double *out_7810958307984275832) {
  h_30(state, unused, out_7810958307984275832);
}
void car_H_30(double *state, double *unused, double *out_5016512016345925502) {
  H_30(state, unused, out_5016512016345925502);
}
void car_h_26(double *state, double *unused, double *out_161613134672941490) {
  h_26(state, unused, out_161613134672941490);
}
void car_H_26(double *state, double *unused, double *out_4230319005092373528) {
  H_26(state, unused, out_4230319005092373528);
}
void car_h_27(double *state, double *unused, double *out_279620528606318234) {
  h_27(state, unused, out_279620528606318234);
}
void car_H_27(double *state, double *unused, double *out_2792917945161982285) {
  H_27(state, unused, out_2792917945161982285);
}
void car_h_29(double *state, double *unused, double *out_8217040152657421758) {
  h_29(state, unused, out_8217040152657421758);
}
void car_H_29(double *state, double *unused, double *out_4506280672031533318) {
  H_29(state, unused, out_4506280672031533318);
}
void car_h_28(double *state, double *unused, double *out_4677572609887947246) {
  h_28(state, unused, out_4677572609887947246);
}
void car_H_28(double *state, double *unused, double *out_8858064384608487724) {
  H_28(state, unused, out_8858064384608487724);
}
void car_h_31(double *state, double *unused, double *out_8583736215483029063) {
  h_31(state, unused, out_8583736215483029063);
}
void car_H_31(double *state, double *unused, double *out_4856527107325725004) {
  H_31(state, unused, out_4856527107325725004);
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
