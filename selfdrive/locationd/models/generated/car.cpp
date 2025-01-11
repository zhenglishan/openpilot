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
 *                      Code generated with SymPy 1.13.3                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2128346571522714278) {
   out_2128346571522714278[0] = delta_x[0] + nom_x[0];
   out_2128346571522714278[1] = delta_x[1] + nom_x[1];
   out_2128346571522714278[2] = delta_x[2] + nom_x[2];
   out_2128346571522714278[3] = delta_x[3] + nom_x[3];
   out_2128346571522714278[4] = delta_x[4] + nom_x[4];
   out_2128346571522714278[5] = delta_x[5] + nom_x[5];
   out_2128346571522714278[6] = delta_x[6] + nom_x[6];
   out_2128346571522714278[7] = delta_x[7] + nom_x[7];
   out_2128346571522714278[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7912846920589436786) {
   out_7912846920589436786[0] = -nom_x[0] + true_x[0];
   out_7912846920589436786[1] = -nom_x[1] + true_x[1];
   out_7912846920589436786[2] = -nom_x[2] + true_x[2];
   out_7912846920589436786[3] = -nom_x[3] + true_x[3];
   out_7912846920589436786[4] = -nom_x[4] + true_x[4];
   out_7912846920589436786[5] = -nom_x[5] + true_x[5];
   out_7912846920589436786[6] = -nom_x[6] + true_x[6];
   out_7912846920589436786[7] = -nom_x[7] + true_x[7];
   out_7912846920589436786[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4362440514772547881) {
   out_4362440514772547881[0] = 1.0;
   out_4362440514772547881[1] = 0.0;
   out_4362440514772547881[2] = 0.0;
   out_4362440514772547881[3] = 0.0;
   out_4362440514772547881[4] = 0.0;
   out_4362440514772547881[5] = 0.0;
   out_4362440514772547881[6] = 0.0;
   out_4362440514772547881[7] = 0.0;
   out_4362440514772547881[8] = 0.0;
   out_4362440514772547881[9] = 0.0;
   out_4362440514772547881[10] = 1.0;
   out_4362440514772547881[11] = 0.0;
   out_4362440514772547881[12] = 0.0;
   out_4362440514772547881[13] = 0.0;
   out_4362440514772547881[14] = 0.0;
   out_4362440514772547881[15] = 0.0;
   out_4362440514772547881[16] = 0.0;
   out_4362440514772547881[17] = 0.0;
   out_4362440514772547881[18] = 0.0;
   out_4362440514772547881[19] = 0.0;
   out_4362440514772547881[20] = 1.0;
   out_4362440514772547881[21] = 0.0;
   out_4362440514772547881[22] = 0.0;
   out_4362440514772547881[23] = 0.0;
   out_4362440514772547881[24] = 0.0;
   out_4362440514772547881[25] = 0.0;
   out_4362440514772547881[26] = 0.0;
   out_4362440514772547881[27] = 0.0;
   out_4362440514772547881[28] = 0.0;
   out_4362440514772547881[29] = 0.0;
   out_4362440514772547881[30] = 1.0;
   out_4362440514772547881[31] = 0.0;
   out_4362440514772547881[32] = 0.0;
   out_4362440514772547881[33] = 0.0;
   out_4362440514772547881[34] = 0.0;
   out_4362440514772547881[35] = 0.0;
   out_4362440514772547881[36] = 0.0;
   out_4362440514772547881[37] = 0.0;
   out_4362440514772547881[38] = 0.0;
   out_4362440514772547881[39] = 0.0;
   out_4362440514772547881[40] = 1.0;
   out_4362440514772547881[41] = 0.0;
   out_4362440514772547881[42] = 0.0;
   out_4362440514772547881[43] = 0.0;
   out_4362440514772547881[44] = 0.0;
   out_4362440514772547881[45] = 0.0;
   out_4362440514772547881[46] = 0.0;
   out_4362440514772547881[47] = 0.0;
   out_4362440514772547881[48] = 0.0;
   out_4362440514772547881[49] = 0.0;
   out_4362440514772547881[50] = 1.0;
   out_4362440514772547881[51] = 0.0;
   out_4362440514772547881[52] = 0.0;
   out_4362440514772547881[53] = 0.0;
   out_4362440514772547881[54] = 0.0;
   out_4362440514772547881[55] = 0.0;
   out_4362440514772547881[56] = 0.0;
   out_4362440514772547881[57] = 0.0;
   out_4362440514772547881[58] = 0.0;
   out_4362440514772547881[59] = 0.0;
   out_4362440514772547881[60] = 1.0;
   out_4362440514772547881[61] = 0.0;
   out_4362440514772547881[62] = 0.0;
   out_4362440514772547881[63] = 0.0;
   out_4362440514772547881[64] = 0.0;
   out_4362440514772547881[65] = 0.0;
   out_4362440514772547881[66] = 0.0;
   out_4362440514772547881[67] = 0.0;
   out_4362440514772547881[68] = 0.0;
   out_4362440514772547881[69] = 0.0;
   out_4362440514772547881[70] = 1.0;
   out_4362440514772547881[71] = 0.0;
   out_4362440514772547881[72] = 0.0;
   out_4362440514772547881[73] = 0.0;
   out_4362440514772547881[74] = 0.0;
   out_4362440514772547881[75] = 0.0;
   out_4362440514772547881[76] = 0.0;
   out_4362440514772547881[77] = 0.0;
   out_4362440514772547881[78] = 0.0;
   out_4362440514772547881[79] = 0.0;
   out_4362440514772547881[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3378896944494616523) {
   out_3378896944494616523[0] = state[0];
   out_3378896944494616523[1] = state[1];
   out_3378896944494616523[2] = state[2];
   out_3378896944494616523[3] = state[3];
   out_3378896944494616523[4] = state[4];
   out_3378896944494616523[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3378896944494616523[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3378896944494616523[7] = state[7];
   out_3378896944494616523[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7143490918223144660) {
   out_7143490918223144660[0] = 1;
   out_7143490918223144660[1] = 0;
   out_7143490918223144660[2] = 0;
   out_7143490918223144660[3] = 0;
   out_7143490918223144660[4] = 0;
   out_7143490918223144660[5] = 0;
   out_7143490918223144660[6] = 0;
   out_7143490918223144660[7] = 0;
   out_7143490918223144660[8] = 0;
   out_7143490918223144660[9] = 0;
   out_7143490918223144660[10] = 1;
   out_7143490918223144660[11] = 0;
   out_7143490918223144660[12] = 0;
   out_7143490918223144660[13] = 0;
   out_7143490918223144660[14] = 0;
   out_7143490918223144660[15] = 0;
   out_7143490918223144660[16] = 0;
   out_7143490918223144660[17] = 0;
   out_7143490918223144660[18] = 0;
   out_7143490918223144660[19] = 0;
   out_7143490918223144660[20] = 1;
   out_7143490918223144660[21] = 0;
   out_7143490918223144660[22] = 0;
   out_7143490918223144660[23] = 0;
   out_7143490918223144660[24] = 0;
   out_7143490918223144660[25] = 0;
   out_7143490918223144660[26] = 0;
   out_7143490918223144660[27] = 0;
   out_7143490918223144660[28] = 0;
   out_7143490918223144660[29] = 0;
   out_7143490918223144660[30] = 1;
   out_7143490918223144660[31] = 0;
   out_7143490918223144660[32] = 0;
   out_7143490918223144660[33] = 0;
   out_7143490918223144660[34] = 0;
   out_7143490918223144660[35] = 0;
   out_7143490918223144660[36] = 0;
   out_7143490918223144660[37] = 0;
   out_7143490918223144660[38] = 0;
   out_7143490918223144660[39] = 0;
   out_7143490918223144660[40] = 1;
   out_7143490918223144660[41] = 0;
   out_7143490918223144660[42] = 0;
   out_7143490918223144660[43] = 0;
   out_7143490918223144660[44] = 0;
   out_7143490918223144660[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7143490918223144660[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7143490918223144660[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7143490918223144660[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7143490918223144660[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7143490918223144660[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7143490918223144660[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7143490918223144660[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7143490918223144660[53] = -9.8000000000000007*dt;
   out_7143490918223144660[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7143490918223144660[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7143490918223144660[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7143490918223144660[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7143490918223144660[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7143490918223144660[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7143490918223144660[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7143490918223144660[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7143490918223144660[62] = 0;
   out_7143490918223144660[63] = 0;
   out_7143490918223144660[64] = 0;
   out_7143490918223144660[65] = 0;
   out_7143490918223144660[66] = 0;
   out_7143490918223144660[67] = 0;
   out_7143490918223144660[68] = 0;
   out_7143490918223144660[69] = 0;
   out_7143490918223144660[70] = 1;
   out_7143490918223144660[71] = 0;
   out_7143490918223144660[72] = 0;
   out_7143490918223144660[73] = 0;
   out_7143490918223144660[74] = 0;
   out_7143490918223144660[75] = 0;
   out_7143490918223144660[76] = 0;
   out_7143490918223144660[77] = 0;
   out_7143490918223144660[78] = 0;
   out_7143490918223144660[79] = 0;
   out_7143490918223144660[80] = 1;
}
void h_25(double *state, double *unused, double *out_6318664847144539943) {
   out_6318664847144539943[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5666779624964519501) {
   out_5666779624964519501[0] = 0;
   out_5666779624964519501[1] = 0;
   out_5666779624964519501[2] = 0;
   out_5666779624964519501[3] = 0;
   out_5666779624964519501[4] = 0;
   out_5666779624964519501[5] = 0;
   out_5666779624964519501[6] = 1;
   out_5666779624964519501[7] = 0;
   out_5666779624964519501[8] = 0;
}
void h_24(double *state, double *unused, double *out_2969761211601569774) {
   out_2969761211601569774[0] = state[4];
   out_2969761211601569774[1] = state[5];
}
void H_24(double *state, double *unused, double *out_908792181626998600) {
   out_908792181626998600[0] = 0;
   out_908792181626998600[1] = 0;
   out_908792181626998600[2] = 0;
   out_908792181626998600[3] = 0;
   out_908792181626998600[4] = 1;
   out_908792181626998600[5] = 0;
   out_908792181626998600[6] = 0;
   out_908792181626998600[7] = 0;
   out_908792181626998600[8] = 0;
   out_908792181626998600[9] = 0;
   out_908792181626998600[10] = 0;
   out_908792181626998600[11] = 0;
   out_908792181626998600[12] = 0;
   out_908792181626998600[13] = 0;
   out_908792181626998600[14] = 1;
   out_908792181626998600[15] = 0;
   out_908792181626998600[16] = 0;
   out_908792181626998600[17] = 0;
}
void h_30(double *state, double *unused, double *out_2681215318890517593) {
   out_2681215318890517593[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3148446666457270874) {
   out_3148446666457270874[0] = 0;
   out_3148446666457270874[1] = 0;
   out_3148446666457270874[2] = 0;
   out_3148446666457270874[3] = 0;
   out_3148446666457270874[4] = 1;
   out_3148446666457270874[5] = 0;
   out_3148446666457270874[6] = 0;
   out_3148446666457270874[7] = 0;
   out_3148446666457270874[8] = 0;
}
void h_26(double *state, double *unused, double *out_3284531203566995110) {
   out_3284531203566995110[0] = state[7];
}
void H_26(double *state, double *unused, double *out_9038461129870975891) {
   out_9038461129870975891[0] = 0;
   out_9038461129870975891[1] = 0;
   out_9038461129870975891[2] = 0;
   out_9038461129870975891[3] = 0;
   out_9038461129870975891[4] = 0;
   out_9038461129870975891[5] = 0;
   out_9038461129870975891[6] = 0;
   out_9038461129870975891[7] = 1;
   out_9038461129870975891[8] = 0;
}
void h_27(double *state, double *unused, double *out_3899919234076685917) {
   out_3899919234076685917[0] = state[3];
}
void H_27(double *state, double *unused, double *out_924852595273327657) {
   out_924852595273327657[0] = 0;
   out_924852595273327657[1] = 0;
   out_924852595273327657[2] = 0;
   out_924852595273327657[3] = 1;
   out_924852595273327657[4] = 0;
   out_924852595273327657[5] = 0;
   out_924852595273327657[6] = 0;
   out_924852595273327657[7] = 0;
   out_924852595273327657[8] = 0;
}
void h_29(double *state, double *unused, double *out_3624725171792180028) {
   out_3624725171792180028[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2638215322142878690) {
   out_2638215322142878690[0] = 0;
   out_2638215322142878690[1] = 1;
   out_2638215322142878690[2] = 0;
   out_2638215322142878690[3] = 0;
   out_2638215322142878690[4] = 0;
   out_2638215322142878690[5] = 0;
   out_2638215322142878690[6] = 0;
   out_2638215322142878690[7] = 0;
   out_2638215322142878690[8] = 0;
}
void h_28(double *state, double *unused, double *out_6504324554885383568) {
   out_6504324554885383568[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7720614339212409264) {
   out_7720614339212409264[0] = 1;
   out_7720614339212409264[1] = 0;
   out_7720614339212409264[2] = 0;
   out_7720614339212409264[3] = 0;
   out_7720614339212409264[4] = 0;
   out_7720614339212409264[5] = 0;
   out_7720614339212409264[6] = 0;
   out_7720614339212409264[7] = 0;
   out_7720614339212409264[8] = 0;
}
void h_31(double *state, double *unused, double *out_404931820473791570) {
   out_404931820473791570[0] = state[8];
}
void H_31(double *state, double *unused, double *out_5636133663087559073) {
   out_5636133663087559073[0] = 0;
   out_5636133663087559073[1] = 0;
   out_5636133663087559073[2] = 0;
   out_5636133663087559073[3] = 0;
   out_5636133663087559073[4] = 0;
   out_5636133663087559073[5] = 0;
   out_5636133663087559073[6] = 0;
   out_5636133663087559073[7] = 0;
   out_5636133663087559073[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2128346571522714278) {
  err_fun(nom_x, delta_x, out_2128346571522714278);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7912846920589436786) {
  inv_err_fun(nom_x, true_x, out_7912846920589436786);
}
void car_H_mod_fun(double *state, double *out_4362440514772547881) {
  H_mod_fun(state, out_4362440514772547881);
}
void car_f_fun(double *state, double dt, double *out_3378896944494616523) {
  f_fun(state,  dt, out_3378896944494616523);
}
void car_F_fun(double *state, double dt, double *out_7143490918223144660) {
  F_fun(state,  dt, out_7143490918223144660);
}
void car_h_25(double *state, double *unused, double *out_6318664847144539943) {
  h_25(state, unused, out_6318664847144539943);
}
void car_H_25(double *state, double *unused, double *out_5666779624964519501) {
  H_25(state, unused, out_5666779624964519501);
}
void car_h_24(double *state, double *unused, double *out_2969761211601569774) {
  h_24(state, unused, out_2969761211601569774);
}
void car_H_24(double *state, double *unused, double *out_908792181626998600) {
  H_24(state, unused, out_908792181626998600);
}
void car_h_30(double *state, double *unused, double *out_2681215318890517593) {
  h_30(state, unused, out_2681215318890517593);
}
void car_H_30(double *state, double *unused, double *out_3148446666457270874) {
  H_30(state, unused, out_3148446666457270874);
}
void car_h_26(double *state, double *unused, double *out_3284531203566995110) {
  h_26(state, unused, out_3284531203566995110);
}
void car_H_26(double *state, double *unused, double *out_9038461129870975891) {
  H_26(state, unused, out_9038461129870975891);
}
void car_h_27(double *state, double *unused, double *out_3899919234076685917) {
  h_27(state, unused, out_3899919234076685917);
}
void car_H_27(double *state, double *unused, double *out_924852595273327657) {
  H_27(state, unused, out_924852595273327657);
}
void car_h_29(double *state, double *unused, double *out_3624725171792180028) {
  h_29(state, unused, out_3624725171792180028);
}
void car_H_29(double *state, double *unused, double *out_2638215322142878690) {
  H_29(state, unused, out_2638215322142878690);
}
void car_h_28(double *state, double *unused, double *out_6504324554885383568) {
  h_28(state, unused, out_6504324554885383568);
}
void car_H_28(double *state, double *unused, double *out_7720614339212409264) {
  H_28(state, unused, out_7720614339212409264);
}
void car_h_31(double *state, double *unused, double *out_404931820473791570) {
  h_31(state, unused, out_404931820473791570);
}
void car_H_31(double *state, double *unused, double *out_5636133663087559073) {
  H_31(state, unused, out_5636133663087559073);
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
