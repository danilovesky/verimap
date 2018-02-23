// Tri-State Buffer with active high enable (12348x)

//module BT1_ndr (A_1, A_0, E_1, E_0, Q_1, Q_0);
//  input A_1, A_0;
//  input E_1, E_0;
//  output Q_1, Q_0;
//  bufif1 (Q, A, E);
//endmodule


// Tri-State Buffer with active low enable (12348x)

//module BT1_ndr (A_1, A_0, EN_1, EN_0, Q_1, Q_0);
//  input A_1, A_0;
//  input EN_1, EN_0;
//  output Q_1, Q_0;
//  bufif0 (Q, A, EN);
//endmodule


// 2-Input XNOR (1234x)

module EN1_pdr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;

  OA22 inst_Q_1 (.A(A_1), .B(B_0), .C(A_0), .D(B_1), .Q(Q_1));
  AO22 inst_Q_0 (.A(A_0), .B(B_1), .C(A_1), .D(B_0), .Q(Q_0));
endmodule


module EN1_ndr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;

  AN22 inst_Q_1 (.A(A_0), .B(B_1), .C(A_1), .D(B_0), .Q(Q_1));
  ON22 inst_Q_0 (.A(A_1), .B(B_0), .C(A_0), .D(B_1), .Q(Q_0));
endmodule


module EN12_pdr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EN1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv2_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module EN12_ndr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EN1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv2_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module EN13_pdr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EN1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv3_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module EN13_ndr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EN1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv3_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module EN14_pdr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EN1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv4_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module EN14_ndr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EN1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv4_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


// 3-Input XNOR (1234x)

module EN3_pdr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;
  wire spinv_C_1, spinv_C_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv1_ndr inst_spinv_C (.i_1(C_1), .i_0(C_0), .z_1(spinv_C_1), .z_0(spinv_C_0));
  EN1_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(spinv_C_1), .B_0(spinv_C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EN3_ndr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  EN1_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(C_1), .B_0(C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EN32_pdr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;
  wire spinv_C_1, spinv_C_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv1_ndr inst_spinv_C (.i_1(C_1), .i_0(C_0), .z_1(spinv_C_1), .z_0(spinv_C_0));
  EN12_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(spinv_C_1), .B_0(spinv_C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EN32_ndr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  EN12_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(C_1), .B_0(C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EN33_pdr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;
  wire spinv_C_1, spinv_C_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv1_ndr inst_spinv_C (.i_1(C_1), .i_0(C_0), .z_1(spinv_C_1), .z_0(spinv_C_0));
  EN13_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(spinv_C_1), .B_0(spinv_C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EN33_ndr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  EN13_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(C_1), .B_0(C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EN34_pdr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;
  wire spinv_C_1, spinv_C_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv1_ndr inst_spinv_C (.i_1(C_1), .i_0(C_0), .z_1(spinv_C_1), .z_0(spinv_C_0));
  EN14_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(spinv_C_1), .B_0(spinv_C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EN34_ndr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  EN14_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(C_1), .B_0(C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


// 2-Input XOR (1234x)

module EO1_pdr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;

  AO22 inst_Q_1 (.A(A_0), .B(B_1), .C(A_1), .D(B_0), .Q(Q_1));
  OA22 inst_Q_0 (.A(A_1), .B(B_0), .C(A_0), .D(B_1), .Q(Q_0));
endmodule


module EO1_ndr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;

  ON22 inst_Q_1 (.A(A_1), .B(B_0), .C(A_0), .D(B_1), .Q(Q_1));
  AN22 inst_Q_0 (.A(A_0), .B(B_1), .C(A_1), .D(B_0), .Q(Q_0));
endmodule


module EO12_pdr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv2_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module EO12_ndr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv2_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module EO13_pdr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv3_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module EO13_ndr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv3_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module EO14_pdr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv4_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module EO14_ndr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv4_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


// 3-Input XOR (1234x)

module EO3_pdr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;
  wire spinv_C_1, spinv_C_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv1_ndr inst_spinv_C (.i_1(C_1), .i_0(C_0), .z_1(spinv_C_1), .z_0(spinv_C_0));
  EO1_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(spinv_C_1), .B_0(spinv_C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EO3_ndr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  EO1_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(C_1), .B_0(C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EO32_pdr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;
  wire spinv_C_1, spinv_C_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv1_ndr inst_spinv_C (.i_1(C_1), .i_0(C_0), .z_1(spinv_C_1), .z_0(spinv_C_0));
  EO12_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(spinv_C_1), .B_0(spinv_C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EO32_ndr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  EO12_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(C_1), .B_0(C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EO33_pdr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;
  wire spinv_C_1, spinv_C_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv1_ndr inst_spinv_C (.i_1(C_1), .i_0(C_0), .z_1(spinv_C_1), .z_0(spinv_C_0));
  EO13_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(spinv_C_1), .B_0(spinv_C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EO33_ndr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  EO13_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(C_1), .B_0(C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EO34_pdr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;
  wire spinv_C_1, spinv_C_0;

  EO1_ndr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  spinv1_ndr inst_spinv_C (.i_1(C_1), .i_0(C_0), .z_1(spinv_C_1), .z_0(spinv_C_0));
  EO14_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(spinv_C_1), .B_0(spinv_C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module EO34_ndr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;
  wire w_1, w_0;

  EO1_pdr inst_w (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(w_1), .Q_0(w_0));
  EO14_ndr inst_Q (.A_1(w_1), .A_0(w_0), .B_1(C_1), .B_0(C_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


// Full-Adder (1234x)

module FA1_pdr (A_1, A_0, B_1, B_0, CI_1, CI_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  input CI_1, CI_0;
  output CO_1, CO_0;
  output S_1, S_0;
  wire net_1_1, net_1_0;
  wire net_2_1, net_2_0;
  wire net_3_1, net_3_0;

  and_ndr inst_net_1 (.A_1(B_1), .A_0(B_0), .B_1(CI_1), .B_0(CI_0), .Q_1(net_1_1), .Q_0(net_1_0));
  and_ndr inst_net_2 (.A_1(A_1), .A_0(A_0), .B_1(CI_1), .B_0(CI_0), .Q_1(net_2_1), .Q_0(net_2_0));
  and_ndr inst_net_3 (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(net_3_1), .Q_0(net_3_0));
  or3_ndr inst_CO (.A_1(net_1_1), .A_0(net_1_0), .B_1(net_2_1), .B_0(net_2_0), .C_1(net_3_1), .C_0(net_3_0), .Q_1(CO_1), .Q_0(CO_0));
  EO3_pdr inst_S  (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .C_1(CI_1), .C_0(CI_0), .Q_1(S_1), .Q_0(S_0));
endmodule


module FA12_pdr (A_1, A_0, B_1, B_0, CI_1, CI_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  input CI_1, CI_0;
  output CO_1, CO_0;
  output S_1, S_0;
  wire net_1_1, net_1_0;
  wire net_2_1, net_2_0;
  wire net_3_1, net_3_0;

  and_ndr inst_net_1 (.A_1(B_1), .A_0(B_0), .B_1(CI_1), .B_0(CI_0), .Q_1(net_1_1), .Q_0(net_1_0));
  and_ndr inst_net_2 (.A_1(A_1), .A_0(A_0), .B_1(CI_1), .B_0(CI_0), .Q_1(net_2_1), .Q_0(net_2_0));
  and_ndr inst_net_3 (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(net_3_1), .Q_0(net_3_0));
  or3_ndr inst_CO (.A_1(net_1_1), .A_0(net_1_0), .B_1(net_2_1), .B_0(net_2_0), .C_1(net_3_1), .C_0(net_3_0), .Q_1(CO_1), .Q_0(CO_0));
  EO32_pdr inst_S  (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .C_1(CI_1), .C_0(CI_0), .Q_1(S_1), .Q_0(S_0));
endmodule


module FA13_pdr (A_1, A_0, B_1, B_0, CI_1, CI_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  input CI_1, CI_0;
  output CO_1, CO_0;
  output S_1, S_0;
  wire net_1_1, net_1_0;
  wire net_2_1, net_2_0;
  wire net_3_1, net_3_0;

  and_ndr inst_net_1 (.A_1(B_1), .A_0(B_0), .B_1(CI_1), .B_0(CI_0), .Q_1(net_1_1), .Q_0(net_1_0));
  and_ndr inst_net_2 (.A_1(A_1), .A_0(A_0), .B_1(CI_1), .B_0(CI_0), .Q_1(net_2_1), .Q_0(net_2_0));
  and_ndr inst_net_3 (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(net_3_1), .Q_0(net_3_0));
  or3_ndr inst_CO (.A_1(net_1_1), .A_0(net_1_0), .B_1(net_2_1), .B_0(net_2_0), .C_1(net_3_1), .C_0(net_3_0), .Q_1(CO_1), .Q_0(CO_0));
  EO33_pdr inst_S  (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .C_1(CI_1), .C_0(CI_0), .Q_1(S_1), .Q_0(S_0));
endmodule


module FA14_pdr (A_1, A_0, B_1, B_0, CI_1, CI_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  input CI_1, CI_0;
  output CO_1, CO_0;
  output S_1, S_0;
  wire net_1_1, net_1_0;
  wire net_2_1, net_2_0;
  wire net_3_1, net_3_0;

  and_ndr inst_net_1 (.A_1(B_1), .A_0(B_0), .B_1(CI_1), .B_0(CI_0), .Q_1(net_1_1), .Q_0(net_1_0));
  and_ndr inst_net_2 (.A_1(A_1), .A_0(A_0), .B_1(CI_1), .B_0(CI_0), .Q_1(net_2_1), .Q_0(net_2_0));
  and_ndr inst_net_3 (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(net_3_1), .Q_0(net_3_0));
  or3_ndr inst_CO (.A_1(net_1_1), .A_0(net_1_0), .B_1(net_2_1), .B_0(net_2_0), .C_1(net_3_1), .C_0(net_3_0), .Q_1(CO_1), .Q_0(CO_0));
  EO34_pdr inst_S  (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .C_1(CI_1), .C_0(CI_0), .Q_1(S_1), .Q_0(S_0));
endmodule


// Half-Adder (1234x)

module HA1_pdr (A_1, A_0, B_1, B_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  output CO_1, CO_0;
  output S_1, S_0;

  and_pdr inst_CO (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(CO_1), .Q_0(CO_0));
  EO1_pdr inst_S (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(S_1), .Q_0(S_0));
endmodule


module HA1_ndr (A_1, A_0, B_1, B_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  output CO_1, CO_0;
  output S_1, S_0;

  and_ndr inst_CO (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(CO_1), .Q_0(CO_0));
  EO1_ndr inst_S (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(S_1), .Q_0(S_0));
endmodule


module HA12_pdr (A_1, A_0, B_1, B_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  output CO_1, CO_0;
  output S_1, S_0;

  and_pdr inst_CO (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(CO_1), .Q_0(CO_0));
  EO12_pdr inst_S (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(S_1), .Q_0(S_0));
endmodule


module HA12_ndr (A_1, A_0, B_1, B_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  output CO_1, CO_0;
  output S_1, S_0;

  and_ndr inst_CO (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(CO_1), .Q_0(CO_0));  
  EO12_ndr inst_S (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(S_1), .Q_0(S_0));
endmodule


module HA13_pdr (A_1, A_0, B_1, B_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  output CO_1, CO_0;
  output S_1, S_0;

  and_pdr inst_CO (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(CO_1), .Q_0(CO_0));
  EO13_pdr inst_S (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(S_1), .Q_0(S_0));
endmodule


module HA13_ndr (A_1, A_0, B_1, B_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  output CO_1, CO_0;
  output S_1, S_0;

  and_ndr inst_CO (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(CO_1), .Q_0(CO_0));  
  EO13_ndr inst_S (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(S_1), .Q_0(S_0));
endmodule


module HA14_pdr (A_1, A_0, B_1, B_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  output CO_1, CO_0;
  output S_1, S_0;

  and_pdr inst_CO (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(CO_1), .Q_0(CO_0));
  EO14_pdr inst_S (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(S_1), .Q_0(S_0));
endmodule


module HA14_ndr (A_1, A_0, B_1, B_0, CO_1, CO_0, S_1, S_0);
  input A_1, A_0;
  input B_1, B_0;
  output CO_1, CO_0;
  output S_1, S_0;

  and_ndr inst_CO (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(CO_1), .Q_0(CO_0));  
  EO14_ndr inst_S (.A_1(A_1), .A_0(A_0), .B_1(B_1), .B_0(B_0), .Q_1(S_1), .Q_0(S_0));
endmodule


// 2:1 Inverting Multiplexer (124x)

module IMU2_pdr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;

  OA22 inst_Q_1 (.A(I0_0), .B(S_1), .C(I1_0), .D(S_0), .Q(Q_1));
  AO22 inst_Q_0 (.A(I0_1), .B(S_0), .C(I1_1), .D(S_1), .Q(Q_0));
endmodule


module IMU2_ndr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;

  AN22 inst_Q_1 (.A(I0_1), .B(S_0), .C(I1_1), .D(S_1), .Q(Q_1));
  ON22 inst_Q_0 (.A(I0_0), .B(S_1), .C(I1_0), .D(S_0), .Q(Q_0));
endmodule


module IMU22_pdr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;
  wire w_1, w_0;

  IMU2_ndr inst_w (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .Q_1(w_1), .Q_0(w_0), .S_1(S_1), .S_0(S_0));
  spinv2_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module IMU22_ndr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;
  wire w_1, w_0;

  IMU2_pdr inst_w (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .Q_1(w_1), .Q_0(w_0), .S_1(S_1), .S_0(S_0));
  spinv2_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module IMU24_pdr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;
  wire w_1, w_0;

  IMU2_ndr inst_w (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .Q_1(w_1), .Q_0(w_0), .S_1(S_1), .S_0(S_0));
  spinv4_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


module IMU24_ndr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;
  wire w_1, w_0;

  IMU2_pdr inst_w (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .Q_1(w_1), .Q_0(w_0), .S_1(S_1), .S_0(S_0));
  spinv4_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));
endmodule


// 4:1 Inverting Multiplexer (124x)

module IMU4_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  IMU2_ndr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module IMU4_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  IMU2_pdr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module IMU42_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  IMU22_ndr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module IMU42_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  IMU22_pdr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module IMU44_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  IMU24_ndr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module IMU44_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  IMU24_pdr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


// 8:1 Inverting Multiplexer (124x)

module IMU8_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  IMU2_pdr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module IMU8_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  IMU2_ndr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module IMU82_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  IMU22_pdr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module IMU82_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  IMU22_ndr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module IMU84_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  IMU24_pdr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module IMU84_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  IMU24_ndr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


// Inverting Tristate Buffer with Active High Enable (1234{LP}x)

//module IT1_pdr (A_1, A_0, E_1, E_0, Q_1, Q_0);
//  input A_1, A_0;
//  input E_1, E_0;
//  output Q_1, Q_0;
//  notif1 (Q, A, E);
//endmodule


// Inverting Tristate Buffer with Active Low Enable (1234{LP}x)

//module IT2_pdr (A_1, A_0, EN_1, EN_0, Q_1, Q_0);
//  input A_1, A_0;
//  input EN_1, EN_0;
//  output Q_1, Q_0;
//  notif0 (Q, A, EN);
//endmodule


// 2:1 Multiplexer (124x)

module MU2_pdr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;

  AO22 inst_Q_1 (.A(I0_1), .B(S_0), .C(I1_1), .D(S_1), .Q(Q_1));
  OA22 inst_Q_0 (.A(I0_0), .B(S_1), .C(I1_0), .D(S_0), .Q(Q_0));
endmodule


module MU2_ndr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;

  ON22 inst_Q_1 (.A(I0_0), .B(S_1), .C(I1_0), .D(S_0), .Q(Q_1));
  AN22 inst_Q_0 (.A(I0_1), .B(S_0), .C(I1_1), .D(S_1), .Q(Q_0));
endmodule


module MU22_pdr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;
  wire w_1, w_0;

  MU2_ndr inst_w (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .Q_1(w_1), .Q_0(w_0), .S_1(S_1), .S_0(S_0));
  spinv2_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));  
endmodule


module MU22_ndr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;
  wire w_1, w_0;

  MU2_pdr inst_w (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .Q_1(w_1), .Q_0(w_0), .S_1(S_1), .S_0(S_0));
  spinv2_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));  
endmodule


module MU24_pdr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;
  wire w_1, w_0;

  MU2_ndr inst_w (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .Q_1(w_1), .Q_0(w_0), .S_1(S_1), .S_0(S_0));
  spinv4_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));  
endmodule


module MU24_ndr (I0_1, I0_0, I1_1, I1_0, Q_1, Q_0, S_1, S_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  output Q_1, Q_0;
  input S_1, S_0;
  wire w_1, w_0;

  MU2_pdr inst_w (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .Q_1(w_1), .Q_0(w_0), .S_1(S_1), .S_0(S_0));
  spinv4_ndr inst_Q (.i_1(w_1), .i_0(w_0), .z_1(Q_1), .z_0(Q_0));  
endmodule


// 4:1 Multiplexer (124x)

module MU4_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  
  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module MU4_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  
  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_pdr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module MU42_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  
  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU22_ndr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module MU42_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  
  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU22_pdr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module MU44_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  
  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU24_ndr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module MU44_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  
  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU24_pdr inst_Q (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


// 8:1 Multiplexer (124x)

module MU8_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  MU2_pdr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module MU8_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  MU2_ndr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module MU82_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  MU22_pdr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module MU82_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  MU22_ndr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module MU84_pdr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  MU24_pdr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


module MU84_ndr (I0_1, I0_0, I1_1, I1_0, I2_1, I2_0, I3_1, I3_0, I4_1, I4_0, I5_1, I5_0, I6_1, I6_0, I7_1, I7_0, Q_1, Q_0, S0_1, S0_0, S1_1, S1_0, S2_1, S2_0);
  input I0_1, I0_0;
  input I1_1, I1_0;
  input I2_1, I2_0;
  input I3_1, I3_0;
  input I4_1, I4_0;
  input I5_1, I5_0;
  input I6_1, I6_0;
  input I7_1, I7_0;
  output Q_1, Q_0;
  input S0_1, S0_0;
  input S1_1, S1_0;
  input S2_1, S2_0;
  wire II0_1, II0_0;
  wire II1_1, II1_0;
  wire II2_1, II2_0;
  wire II3_1, II3_0;
  wire III0_1, III0_0;
  wire III1_1, III1_0;
  wire spinv_S1_1, spinv_S1_0;
  
  MU2_ndr inst_II0 (.I0_1(I0_1), .I0_0(I0_0), .I1_1(I1_1), .I1_0(I1_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II0_1), .Q_0(II0_0));
  MU2_ndr inst_II1 (.I0_1(I2_1), .I0_0(I2_0), .I1_1(I3_1), .I1_0(I3_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II1_1), .Q_0(II1_0));
  MU2_ndr inst_II2 (.I0_1(I4_1), .I0_0(I4_0), .I1_1(I5_1), .I1_0(I5_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II2_1), .Q_0(II2_0));
  MU2_ndr inst_II3 (.I0_1(I6_1), .I0_0(I6_0), .I1_1(I7_1), .I1_0(I7_0), .S_1(S0_1), .S_0(S0_0), .Q_1(II3_1), .Q_0(II3_0));

  spinv_ndr inst_spinv_S1 (.i_1(S1_1), .i_0(S1_0), .z_1(spinv_S1_1), .z_0(spinv_S1_0));
  MU2_ndr inst_III0 (.I0_1(II0_1), .I0_0(II0_0), .I1_1(II1_1), .I1_0(II1_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III0_1), .Q_0(III0_0));
  MU2_ndr inst_III1 (.I0_1(II2_1), .I0_0(II2_0), .I1_1(II3_1), .I1_0(II3_0), .S_1(spinv_S1_1), .S_0(spinv_S1_0), .Q_1(III1_1), .Q_0(III1_0));
  MU24_ndr inst_Q (.I0_1(III0_1), .I0_0(III0_0), .I1_1(III1_1), .I1_0(III1_0), .S_1(S2_1), .S_0(S2_0), .Q_1(Q_1), .Q_0(Q_0));
endmodule


// Bus Holder

//module SIGNALHOLD_pdr (SIG_1, SIG_0);
//   inout SIG_1, SIG_0;
//   buf (SIG_buf, SIG);
//endmodule


// Spacer converter (12348x)

module spinv_ndr (i_1, i_0, z_1, z_0);
  input i_1, i_0;
  output z_1, z_0;

  IN1 inst_z_1 (.A(i_0), .Q(z_1));
  IN1 inst_z_0 (.A(i_1), .Q(z_0));
endmodule 


module spinv1_ndr (i_1, i_0, z_1, z_0);
  input i_1, i_0;
  output z_1, z_0;

  IN1 inst_z_1 (.A(i_0), .Q(z_1));
  IN1 inst_z_0 (.A(i_1), .Q(z_0));
endmodule 


module spinv2_ndr (i_1, i_0, z_1, z_0);
  input i_1, i_0;
  output z_1, z_0;

  IN2 inst_z_1 (.A(i_0), .Q(z_1));
  IN2 inst_z_0 (.A(i_1), .Q(z_0));
endmodule 


module spinv3_ndr (i_1, i_0, z_1, z_0);
  input i_1, i_0;
  output z_1, z_0;

  IN3 inst_z_1 (.A(i_0), .Q(z_1));
  IN3 inst_z_0 (.A(i_1), .Q(z_0));
endmodule 


module spinv4_ndr (i_1, i_0, z_1, z_0);
  input i_1, i_0;
  output z_1, z_0;

  IN4 inst_z_1 (.A(i_0), .Q(z_1));
  IN4 inst_z_0 (.A(i_1), .Q(z_0));
endmodule 


module spinv8_ndr (i_1, i_0, z_1, z_0);
  input i_1, i_0;
  output z_1, z_0;

  IN8 inst_z_1 (.A(i_0), .Q(z_1));
  IN8 inst_z_0 (.A(i_1), .Q(z_0));
endmodule 


// 2-Input ANDs for HAs and FAs

module and_pdr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;

  AND2 inst_Q_1 (.A(A_1), .B(B_1), .Q(Q_1));
  OR2 inst_Q_0 (.A(A_0), .B(B_0), .Q(Q_0));
endmodule


module and_ndr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;

  NO2 inst_Q_1 (.A(A_0), .B(B_0), .Q(Q_1));
  NA2 inst_Q_0 (.A(A_1), .B(B_1), .Q(Q_0));
endmodule


// 2-Input ORs for HAs and FAs

module or_pdr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;

  OR2 inst_Q_1 (.A(A_1), .B(B_1), .Q(Q_1));
  AND2 inst_Q_0 (.A(A_0), .B(B_0), .Q(Q_0));
endmodule


module or_ndr (A_1, A_0, B_1, B_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  output Q_1, Q_0;

  NA2 inst_Q_1 (.A(A_0), .B(B_0), .Q(Q_1));
  NO2 inst_Q_0 (.A(A_1), .B(B_1), .Q(Q_0));
endmodule


// 3-Input ORs for HAs and FAs

module or3_pdr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;

  OR3 inst_Q_1 (.A(A_1), .B(B_1), .C(C_1), .Q(Q_1));
  AND3 inst_Q_0 (.A(A_0), .B(B_0), .C(C_0), .Q(Q_0));
endmodule


module or3_ndr (A_1, A_0, B_1, B_0, C_1, C_0, Q_1, Q_0);
  input A_1, A_0;
  input B_1, B_0;
  input C_1, C_0;
  output Q_1, Q_0;

  NA3 inst_Q_1 (.A(A_0), .B(B_0), .C(C_0), .Q(Q_1));
  NO3 inst_Q_0 (.A(A_1), .B(B_1), .C(C_1), .Q(Q_0));
endmodule
