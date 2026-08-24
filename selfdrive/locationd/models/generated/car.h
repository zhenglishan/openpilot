#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_309734491217568898);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1598877300122141743);
void car_H_mod_fun(double *state, double *out_7156428947201751020);
void car_f_fun(double *state, double dt, double *out_8687771038779355274);
void car_F_fun(double *state, double dt, double *out_2586617639560263372);
void car_h_25(double *state, double *unused, double *out_416627313290698941);
void car_H_25(double *state, double *unused, double *out_2036759278710486217);
void car_h_24(double *state, double *unused, double *out_3126241056150136646);
void car_H_24(double *state, double *unused, double *out_4209408877715985783);
void car_h_30(double *state, double *unused, double *out_5803749869556315028);
void car_H_30(double *state, double *unused, double *out_481573679796762410);
void car_h_26(double *state, double *unused, double *out_802076601895469383);
void car_H_26(double *state, double *unused, double *out_1267766691050314384);
void car_h_27(double *state, double *unused, double *out_6815668830704548087);
void car_H_27(double *state, double *unused, double *out_2705167750980705627);
void car_h_29(double *state, double *unused, double *out_3178219302450525737);
void car_H_29(double *state, double *unused, double *out_991805024111154594);
void car_h_28(double *state, double *unused, double *out_8594289191560670844);
void car_H_28(double *state, double *unused, double *out_4090593992958375980);
void car_h_31(double *state, double *unused, double *out_8080033367973041051);
void car_H_31(double *state, double *unused, double *out_641558588816962908);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}