// Module spctrl generates a signal Q which is high for each odd clock 
// cycle and is low for each even clock cycle counting from the moment 
// when RN goes high. Clock cycle starts on negative edge of the clock.
//     ---------->time
// RN: 000111111111
//  C: 010101010101
//  Q: 000011001100

module spctrl (C, RN, Q);
  input C, RN;
  output Q;
  wire not_C;
  wire R;
  wire not_Q;
  wire csc, not_csc;

  IN1 inst_not_C (.A(C), .Q(not_C));
  IN1 inst_R (.A(RN), .Q(R));

  AN221 inst_Q (.A(not_Q), .B(C), .C(not_csc), .D(not_C), .E(R), .Q(Q));
  AN22 inst_not_csc0 (.A(csc), .B(not_C), .C(not_Q), .D(C), .Q(not_csc));  

  IN1 inst_not_Q (.A(Q), .Q(not_Q));
  NO2 inst_csc (.A(not_csc), .B(R), .Q(csc));
endmodule


module goctrl (C, DN, SN, GO);
  input C, DN, SN;
  output GO;
  wire w1, w0;
  wire not_SN;
  wire not_DN;
  wire SN_C;
  
  IN1 inst_not_SN (.A(SN), .Q(not_SN));
  OR2 inst_SN_C (.A(not_SN), .B(C), .Q(SN_C));
  IN1 inst_not_DN (.A(DN), .Q(not_DN));

  NO2 inst_w1 (.A(SN_C), .B(w0), .Q(w1));
  NO2 inst_w0 (.A(not_DN), .B(w1), .Q(w0));
  OR2 inst_GO (.A(SN_C), .B(w1), .Q(GO));
endmodule  



// <Q_1, Q_0> is enforced to all-ones spacer when SP is low. 
// Otherwise  <Q_1, Q_0> = <D_1, D_0> 

module spalt_ndr (C, D_1, D_0, Q_1, Q_0, SP);
  input C;
  input D_1, D_0;
  output Q_1, Q_0;
  input SP;
  
  AO221 inst_Q_1 (.A(C), .B(SP), .C(SP), .D(Q_1), .E(D_1), .Q(Q_1));
  AO221 inst_Q_0 (.A(C), .B(SP), .C(SP), .D(Q_0), .E(D_0), .Q(Q_0));
endmodule


module DSDR2SSDR (D_1, D_0, Q_1, Q_0);
  input D_1, D_0;
  output Q_1, Q_0;
  
  INO2 inst_Q_1 (.A(D_1), .B(D_0), .Q(Q_1));
  INO2 inst_Q_0 (.A(D_0), .B(D_1), .Q(Q_0));
endmodule


// SR2DR

module SR2DR_0dr (C, A, Q_1, Q_0, SP);
  input C;
  input A;
  input SP;
  output Q_1, Q_0;
  wire w_1, w_0;

  INO2 inst_w_1 (.A(A), .B(C), .Q(w_1));
  NO2 inst_w_0 (.A(A), .B(C), .Q(w_0));
  spalt_ndr inst_Q (.C(C), .D_1(w_1), .D_0(w_0), .Q_1(Q_1), .Q_0(Q_0), .SP(SP));
endmodule


module SR2DR_1dr (C, A, Q_1, Q_0, SP);
  input C;
  input A;
  input SP;
  output Q_1, Q_0;
  wire w_1, w_0;
  wire v_1, v_0;

  INO2 inst_w_1 (.A(A), .B(C), .Q(w_1));
  NO2 inst_w_0 (.A(A), .B(C), .Q(w_0));
  spalt_ndr inst_v (.C(C), .D_1(w_1), .D_0(w_0), .Q_1(v_1), .Q_0(v_0), .SP(SP));
  spinv_ndr inst_q (.i_1(v_1), .i_0(v_0), .z_1(Q_1), .z_0(Q_0));
endmodule


//DR2SR

module DR2SR_0dr (A_1, A_0, Q);
  input A_1, A_0;
  output Q;
  wire w_1, w_0;
  wire not_Q;

  DSDR2SSDR inst_w (.D_1(A_1), .D_0(A_0), .Q_1(w_1), .Q_0(w_0));

  NO22 inst_not_q (.A(w_1), .B(Q), .Q(not_Q));
  NO22 inst_Q (.A(w_0), .B(not_Q), .Q(Q));
endmodule


module DR2SR_1dr (A_1, A_0, Q);
  input A_1, A_0;
  output Q;
  wire w_1, w_0;
  wire not_Q;

  DSDR2SSDR inst_w (.D_1(A_1), .D_0(A_0), .Q_1(w_1), .Q_0(w_0));

  NO22 inst_not_q (.A(w_1), .B(Q), .Q(not_Q));
  NO22 inst_Q (.A(w_0), .B(not_Q), .Q(Q));
endmodule
