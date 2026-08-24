#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2154331471386048889);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8657363058238728605);
void pose_H_mod_fun(double *state, double *out_4378726407183363418);
void pose_f_fun(double *state, double dt, double *out_5195038445783001597);
void pose_F_fun(double *state, double dt, double *out_3015220250778787201);
void pose_h_4(double *state, double *unused, double *out_597021366061506697);
void pose_H_4(double *state, double *unused, double *out_3624565405128650811);
void pose_h_10(double *state, double *unused, double *out_5914086608734437117);
void pose_H_10(double *state, double *unused, double *out_8960348806644161578);
void pose_h_13(double *state, double *unused, double *out_8425126202907977474);
void pose_H_13(double *state, double *unused, double *out_412291579796318010);
void pose_h_14(double *state, double *unused, double *out_2779692672946926767);
void pose_H_14(double *state, double *unused, double *out_338675451210833718);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}