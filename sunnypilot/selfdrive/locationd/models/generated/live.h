#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_3628365848344046256);
void live_err_fun(double *nom_x, double *delta_x, double *out_6295443651525959257);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_5016778686749548762);
void live_H_mod_fun(double *state, double *out_3124307667250517422);
void live_f_fun(double *state, double dt, double *out_3855252120620808202);
void live_F_fun(double *state, double dt, double *out_6373314768267289956);
void live_h_4(double *state, double *unused, double *out_8392290990091804700);
void live_H_4(double *state, double *unused, double *out_2382132954967791431);
void live_h_9(double *state, double *unused, double *out_5447470107075074223);
void live_H_9(double *state, double *unused, double *out_2140943308338200786);
void live_h_10(double *state, double *unused, double *out_798014640841998470);
void live_H_10(double *state, double *unused, double *out_161989994400435198);
void live_h_12(double *state, double *unused, double *out_4850662558630339455);
void live_H_12(double *state, double *unused, double *out_1761033929920197764);
void live_h_35(double *state, double *unused, double *out_8555185341301884211);
void live_H_35(double *state, double *unused, double *out_984529102404815945);
void live_h_32(double *state, double *unused, double *out_2059535512809754570);
void live_H_32(double *state, double *unused, double *out_7706339695940940482);
void live_h_13(double *state, double *unused, double *out_3160710045800691101);
void live_H_13(double *state, double *unused, double *out_6160969372880276886);
void live_h_14(double *state, double *unused, double *out_5447470107075074223);
void live_H_14(double *state, double *unused, double *out_2140943308338200786);
void live_h_33(double *state, double *unused, double *out_7365950650535280747);
void live_H_33(double *state, double *unused, double *out_4135086107043673549);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}