// Verilog simulation library for csx HRDLIB 1.8V
// $Id: csx_HRDLIB.v,v 1.2 2001/09/28 11:59:36 mbo Exp mbo $
// Owner: austriamicrosystems AG  HIT-Kit: Digital
/*
   /*dsgdsg */
*/
`timescale 1ns/1ps
`celldefine 
module AN21 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  not (Q,Q_I);
  and (net_0, A, B);
  or (Q_I, net_0, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module AN211 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  not (Q,Q_I);
  and (net_2, B, A);
  or (Q_I, D, C, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module AN22 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  not (Q,Q_I);
  and (net_0, B, A);
  and (net_1, D, C);
  or (Q_I, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module AN221 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  not (Q,Q_I);
  and (net_0, B, A);
  and (net_1, C, D);
  or (Q_I, net_0, net_1, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module AN222 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  not (Q,Q_I);
  and (net_0, B, A);
  and (net_1, D, C);
  and (net_2, F, E);
  or (Q_I, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module AN31 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  not (Q,Q_I);
  and (net_0, B, A, C);
  or (Q_I, net_0, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module AN311 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  not (Q,Q_I);
  and (net_0, A, C, B);
  or (Q_I, net_0, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module AN32 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  not (Q,Q_I);
  and (net_0, A, C, B);
  and (net_1, D, E);
  or (Q_I, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module AN321 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  not (Q,Q_I);
  and (net_0, C, B, A);
  and (net_1, E, D);
  or (Q_I, net_0, net_1, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module AN322 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  not (Q,Q_I);
  and (net_0, B, A, C);
  and (net_1, D, E);
  and (net_2, G, F);
  or (Q_I, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module AN33 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  not (Q,Q_I);
  and (net_0, C, B, A);
  and (net_1, F, E, D);
  or (Q_I, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module AN331 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  not (Q,Q_I);
  and (net_0, C, B, A);
  and (net_1, E, D, F);
  or (Q_I, net_0, net_1, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module AN332 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  not (Q,Q_I);
  and (net_0, C, B, A);
  and (net_1, D, F, E);
  and (net_2, H, G);
  or (Q_I, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module AN333 (A, B, C, D, E, F, G, H, I, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  input I;
  output Q;

  not (Q,Q_I);
  and (net_0, C, B, A);
  and (net_1, F, E, D);
  and (net_2, I, H, G);
  or (Q_I, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
    (I => Q) = (1,1);
  endspecify
`endif

endmodule

module AND2 (A, B, Q);
  input A;
  input B;
  output Q;

  and (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module AND22 (A, B, Q);
  input A;
  input B;
  output Q;

  and (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module AND23 (A, B, Q);
  input A;
  input B;
  output Q;

  and (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module AND24 (A, B, Q);
  input A;
  input B;
  output Q;

  and (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module AND3 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  and (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module AND32 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  and (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module AND33 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  and (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module AND34 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  and (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module AND4 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  and (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module AND42 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  and (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module AND43 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  and (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module AND44 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  and (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module AND5 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  and (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module AND52 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  and (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module AND53 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  and (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module AND54 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  and (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module AND6 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  and (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module AND62 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  and (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module AND63 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  and (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module AND64 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  and (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module AND7 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  and (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module AND72 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  and (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module AND73 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  and (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module AND74 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  and (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module AND8 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  and (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module AND82 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  and (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module AND83 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  and (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module AND84 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  and (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module AO21 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  and (net_0, A, B);
  or (Q, net_0, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module AO211 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  and (net_2, B, A);
  or (Q, D, C, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module AO22 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  and (net_0, B, A);
  and (net_1, D, C);
  or (Q, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module AO221 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  and (net_0, B, A);
  and (net_1, C, D);
  or (Q, net_0, net_1, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module AO222 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  and (net_0, B, A);
  and (net_1, D, C);
  and (net_2, F, E);
  or (Q, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module AO31 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  and (net_0, B, A, C);
  or (Q, net_0, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module AO311 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  and (net_0, A, C, B);
  or (Q, net_0, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module AO32 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  and (net_0, A, C, B);
  and (net_1, D, E);
  or (Q, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module AO321 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  and (net_0, C, B, A);
  and (net_1, E, D);
  or (Q, net_0, net_1, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module AO322 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  and (net_0, B, A, C);
  and (net_1, D, E);
  and (net_2, G, F);
  or (Q, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module AO33 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  and (net_0, C, B, A);
  and (net_1, F, E, D);
  or (Q, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module AO331 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  and (net_0, C, B, A);
  and (net_1, E, D, F);
  or (Q, net_0, net_1, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module AO332 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  and (net_0, C, B, A);
  and (net_1, D, F, E);
  and (net_2, H, G);
  or (Q, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module AO333 (A, B, C, D, E, F, G, H, I, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  input I;
  output Q;

  and (net_0, C, B, A);
  and (net_1, F, E, D);
  and (net_2, I, H, G);
  or (Q, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
    (I => Q) = (1,1);
  endspecify
`endif

endmodule

module BT1 (A, E, Q);
  input A;
  input E;
  output Q;

  bufif1 (Q, A, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module BT12 (A, E, Q);
  input A;
  input E;
  output Q;

  bufif1 (Q, A, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module BT13 (A, E, Q);
  input A;
  input E;
  output Q;

  bufif1 (Q, A, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module BT14 (A, E, Q);
  input A;
  input E;
  output Q;

  bufif1 (Q, A, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module BT18 (A, E, Q);
  input A;
  input E;
  output Q;

  bufif1 (Q, A, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module BT2 (A, EN, Q);
  input A;
  input EN;
  output Q;

  bufif0 (Q, A, EN);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (EN => Q) = (1,1);
  endspecify
`endif

endmodule

module BT22 (A, EN, Q);
  input A;
  input EN;
  output Q;

  bufif0 (Q, A, EN);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (EN => Q) = (1,1);
  endspecify
`endif

endmodule

module BT23 (A, EN, Q);
  input A;
  input EN;
  output Q;

  bufif0 (Q, A, EN);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (EN => Q) = (1,1);
  endspecify
`endif

endmodule

module BT24 (A, EN, Q);
  input A;
  input EN;
  output Q;

  bufif0 (Q, A, EN);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (EN => Q) = (1,1);
  endspecify
`endif

endmodule

module BT28 (A, EN, Q);
  input A;
  input EN;
  output Q;

  bufif0 (Q, A, EN);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (EN => Q) = (1,1);
  endspecify
`endif

endmodule

module BU1 (A, Q);
  input A;
  output Q;

  buf (Q, A);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
  endspecify
`endif

endmodule

module BU2 (A, Q);
  input A;
  output Q;

  buf (Q, A);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
  endspecify
`endif

endmodule

module BU3 (A, Q);
  input A;
  output Q;

  buf (Q, A);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
  endspecify
`endif

endmodule

module BU4 (A, Q);
  input A;
  output Q;

  buf (Q, A);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
  endspecify
`endif

endmodule

module BU8 (A, Q);
  input A;
  output Q;

  buf (Q, A);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
  endspecify
`endif

endmodule

module DF8 (C, D, Q, QN);
  input C;
  input D;
  output Q;
  output QN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, 1, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
  endspecify
`endif

endmodule

module DF82 (C, D, Q, QN);
  input C;
  input D;
  output Q;
  output QN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, 1, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
  endspecify
`endif

endmodule

module DF84 (C, D, Q, QN);
  input C;
  input D;
  output Q;
  output QN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, 1, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
  endspecify
`endif

endmodule

module DF9 (C, D, Q, QN, SN);
  input C;
  input D;
  output Q;
  output QN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DF92 (C, D, Q, QN, SN);
  input C;
  input D;
  output Q;
  output QN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DF94 (C, D, Q, QN, SN);
  input C;
  input D;
  output Q;
  output QN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFA (C, D, Q, QN, RN);
  input C;
  input D;
  output Q;
  output QN;
  input RN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFA2 (C, D, Q, QN, RN);
  input C;
  input D;
  output Q;
  output QN;
  input RN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFA4 (C, D, Q, QN, RN);
  input C;
  input D;
  output Q;
  output QN;
  input RN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFB (C, D, Q, QN, RN, SN);
  input C;
  input D;
  output Q;
  output QN;
  input RN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, SN, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    (SN => QN) = (1,1);
    (SN => Q) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFB2 (C, D, Q, QN, RN, SN);
  input C;
  input D;
  output Q;
  output QN;
  input RN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, SN, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    (SN => QN) = (1,1);
    (SN => Q) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFB4 (C, D, Q, QN, RN, SN);
  input C;
  input D;
  output Q;
  output QN;
  input RN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  DFF_UDP (Q_buf, D, C, SN, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    (SN => QN) = (1,1);
    (SN => Q) = (1,1);
    $setup(posedge D, posedge C, 0, notifier);
    $setup(negedge D, posedge C, 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D, 0, notifier);
    $hold(posedge C, posedge D, 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFS8 (C, D, Q, QN, SD, SE);
  input C;
  input D;
  output Q;
  output QN;
  input SD;
  input SE;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, 1, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFS82 (C, D, Q, QN, SD, SE);
  input C;
  input D;
  output Q;
  output QN;
  input SD;
  input SE;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, 1, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFS84 (C, D, Q, QN, SD, SE);
  input C;
  input D;
  output Q;
  output QN;
  input SD;
  input SE;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, 1, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFS9 (C, D, Q, QN, SD, SE, SN);
  input C;
  input D;
  output Q;
  output QN;
  input SD;
  input SE;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFS92 (C, D, Q, QN, SD, SE, SN);
  input C;
  input D;
  output Q;
  output QN;
  input SD;
  input SE;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFS94 (C, D, Q, QN, SD, SE, SN);
  input C;
  input D;
  output Q;
  output QN;
  input SD;
  input SE;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFSA (C, D, Q, QN, RN, SD, SE);
  input C;
  input D;
  output Q;
  output QN;
  input RN;
  input SD;
  input SE;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFSA2 (C, D, Q, QN, RN, SD, SE);
  input C;
  input D;
  output Q;
  output QN;
  input RN;
  input SD;
  input SE;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFSA4 (C, D, Q, QN, RN, SD, SE);
  input C;
  input D;
  output Q;
  output QN;
  input RN;
  input SD;
  input SE;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFSB (C, D, Q, QN, RN, SD, SE, SN);
  input C;
  input D;
  output Q;
  output QN;
  input RN;
  input SD;
  input SE;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, SN, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFSB2 (C, D, Q, QN, RN, SD, SE, SN);
  input C;
  input D;
  output Q;
  output QN;
  input RN;
  input SD;
  input SE;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, SN, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DFSB4 (C, D, Q, QN, RN, SD, SE, SN);
  input C;
  input D;
  output Q;
  output QN;
  input RN;
  input SD;
  input SE;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  MUX_UDP (D_buf, D, SD, SE);
  DFF_UDP (Q_buf, D_buf, C, SN, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge C &&& (~SE), 0, notifier);
    $setup(negedge D, posedge C &&& (~SE), 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge D &&& (~SE), 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DL8 (D, GN, Q, QN);
  input D;
  input GN;
  output Q;
  output QN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, 1, 1, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DL82 (D, GN, Q, QN);
  input D;
  input GN;
  output Q;
  output QN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, 1, 1, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DL84 (D, GN, Q, QN);
  input D;
  input GN;
  output Q;
  output QN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, 1, 1, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DL8Z (D, EN, GN, Q);
  input D;
  input EN;
  input GN;
  output Q;

  reg notifier;
  bufif0 (Q, Q_buf,EN);
  LATCH_UDP (Q_buf, D, GN, 1, 1, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (EN => Q) = (1,1);
    (GN => Q) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DL8Z2 (D, EN, GN, Q);
  input D;
  input EN;
  input GN;
  output Q;

  reg notifier;
  bufif0 (Q, Q_buf,EN);
  LATCH_UDP (Q_buf, D, GN, 1, 1, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (EN => Q) = (1,1);
    (GN => Q) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DL8Z4 (D, EN, GN, Q);
  input D;
  input EN;
  input GN;
  output Q;

  reg notifier;
  bufif0 (Q, Q_buf,EN);
  LATCH_UDP (Q_buf, D, GN, 1, 1, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (EN => Q) = (1,1);
    (GN => Q) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DL9 (D, GN, Q, QN, SN);
  input D;
  input GN;
  output Q;
  output QN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, SN, 1, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $recovery(posedge SN, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $hold(posedge GN, posedge SN, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DL92 (D, GN, Q, QN, SN);
  input D;
  input GN;
  output Q;
  output QN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, SN, 1, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $recovery(posedge SN, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $hold(posedge GN, posedge SN, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DL94 (D, GN, Q, QN, SN);
  input D;
  input GN;
  output Q;
  output QN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, SN, 1, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $recovery(posedge SN, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $hold(posedge GN, posedge SN, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DLA (D, GN, Q, QN, RN);
  input D;
  input GN;
  output Q;
  output QN;
  input RN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, 1, RN, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $recovery(posedge RN, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $hold(posedge GN, posedge RN, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DLA2 (D, GN, Q, QN, RN);
  input D;
  input GN;
  output Q;
  output QN;
  input RN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, 1, RN, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $recovery(posedge RN, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $hold(posedge GN, posedge RN, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DLA4 (D, GN, Q, QN, RN);
  input D;
  input GN;
  output Q;
  output QN;
  input RN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, 1, RN, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $recovery(posedge RN, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $hold(posedge GN, posedge RN, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DLB (D, GN, Q, QN, RN, SN);
  input D;
  input GN;
  output Q;
  output QN;
  input RN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, SN, RN, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $recovery(posedge RN, posedge GN, 0, notifier);
    $recovery(posedge SN, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $hold(posedge GN, posedge RN, 0, notifier);
    $hold(posedge GN, posedge SN, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DLB2 (D, GN, Q, QN, RN, SN);
  input D;
  input GN;
  output Q;
  output QN;
  input RN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, SN, RN, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $recovery(posedge RN, posedge GN, 0, notifier);
    $recovery(posedge SN, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $hold(posedge GN, posedge RN, 0, notifier);
    $hold(posedge GN, posedge SN, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module DLB4 (D, GN, Q, QN, RN, SN);
  input D;
  input GN;
  output Q;
  output QN;
  input RN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  LATCH_UDP (Q_buf, D, GN, SN, RN, notifier);

`ifdef functional
`else
  specify
    (D => Q) = (1,1);
    (D => QN) = (1,1);
    (GN => Q) = (1,1);
    (GN => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge D, posedge GN, 0, notifier);
    $setup(negedge D, posedge GN, 0, notifier);
    $recovery(posedge RN, posedge GN, 0, notifier);
    $recovery(posedge SN, posedge GN, 0, notifier);
    $hold(posedge GN, negedge D, 0, notifier);
    $hold(posedge GN, posedge D, 0, notifier);
    $hold(posedge GN, posedge RN, 0, notifier);
    $hold(posedge GN, posedge SN, 0, notifier);
    $width(negedge GN, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module EN1 (A, B, Q);
  input A;
  input B;
  output Q;

  xnor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module EN12 (A, B, Q);
  input A;
  input B;
  output Q;

  xnor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module EN13 (A, B, Q);
  input A;
  input B;
  output Q;

  xnor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module EN14 (A, B, Q);
  input A;
  input B;
  output Q;

  xnor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module EN3 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  xnor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module EN32 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  xnor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module EN33 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  xnor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module EN34 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  xnor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module EO1 (A, B, Q);
  input A;
  input B;
  output Q;

  xor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module EO12 (A, B, Q);
  input A;
  input B;
  output Q;

  xor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module EO13 (A, B, Q);
  input A;
  input B;
  output Q;

  xor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module EO14 (A, B, Q);
  input A;
  input B;
  output Q;

  xor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module EO3 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  xor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module EO32 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  xor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module EO33 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  xor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module EO34 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  xor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module FA1 (A, B, CI, CO, S);
  input A;
  input B;
  input CI;
  output CO;
  output S;

  and (net_1, CI, B);
  and (net_2, CI, A);
  and (net_3, B, A);
  or ( CO, net_1, net_2, net_3);
  xor (S, CI, B, A);

`ifdef functional
`else
  specify
    (A => CO) = (1,1);
    (A => S) = (1,1);
    (B => CO) = (1,1);
    (B => S) = (1,1);
    (CI => CO) = (1,1);
    (CI => S) = (1,1);
  endspecify
`endif

endmodule

module FA12 (A, B, CI, CO, S);
  input A;
  input B;
  input CI;
  output CO;
  output S;

  and (net_1, CI, B);
  and (net_2, CI, A);
  and (net_3, B, A);
  or ( CO, net_1, net_2, net_3);
  xor (S, CI, B, A);

`ifdef functional
`else
  specify
    (A => CO) = (1,1);
    (A => S) = (1,1);
    (B => CO) = (1,1);
    (B => S) = (1,1);
    (CI => CO) = (1,1);
    (CI => S) = (1,1);
  endspecify
`endif

endmodule

module FA13 (A, B, CI, CO, S);
  input A;
  input B;
  input CI;
  output CO;
  output S;

  and (net_1, CI, B);
  and (net_2, CI, A);
  and (net_3, B, A);
  or ( CO, net_1, net_2, net_3);
  xor (S, CI, B, A);

`ifdef functional
`else
  specify
    (A => CO) = (1,1);
    (A => S) = (1,1);
    (B => CO) = (1,1);
    (B => S) = (1,1);
    (CI => CO) = (1,1);
    (CI => S) = (1,1);
  endspecify
`endif

endmodule

module FA14 (A, B, CI, CO, S);
  input A;
  input B;
  input CI;
  output CO;
  output S;

  and (net_1, CI, B);
  and (net_2, CI, A);
  and (net_3, B, A);
  or ( CO, net_1, net_2, net_3);
  xor (S, CI, B, A);

`ifdef functional
`else
  specify
    (A => CO) = (1,1);
    (A => S) = (1,1);
    (B => CO) = (1,1);
    (B => S) = (1,1);
    (CI => CO) = (1,1);
    (CI => S) = (1,1);
  endspecify
`endif

endmodule

module HA1 (A, B, CO, S);
  input A;
  input B;
  output CO;
  output S;

  and (net_1, B, A);
  buf ( CO, net_1);
  xor (S, B, A);

`ifdef functional
`else
  specify
    (A => CO) = (1,1);
    (A => S) = (1,1);
    (B => CO) = (1,1);
    (B => S) = (1,1);
  endspecify
`endif

endmodule

module HA12 (A, B, CO, S);
  input A;
  input B;
  output CO;
  output S;

  and (net_1, B, A);
  buf ( CO, net_1);
  xor (S, B, A);

`ifdef functional
`else
  specify
    (A => CO) = (1,1);
    (A => S) = (1,1);
    (B => CO) = (1,1);
    (B => S) = (1,1);
  endspecify
`endif

endmodule

module HA13 (A, B, CO, S);
  input A;
  input B;
  output CO;
  output S;

  and (net_1, B, A);
  buf ( CO, net_1);
  xor (S, B, A);

`ifdef functional
`else
  specify
    (A => CO) = (1,1);
    (A => S) = (1,1);
    (B => CO) = (1,1);
    (B => S) = (1,1);
  endspecify
`endif

endmodule

module HA14 (A, B, CO, S);
  input A;
  input B;
  output CO;
  output S;

  and (net_1, B, A);
  buf ( CO, net_1);
  xor (S, B, A);

`ifdef functional
`else
  specify
    (A => CO) = (1,1);
    (A => S) = (1,1);
    (B => CO) = (1,1);
    (B => S) = (1,1);
  endspecify
`endif

endmodule

module IMU2 (I0, I1, Q, S);
  input I0;
  input I1;
  output Q;
  input S;

  not (Q,Q_I);
  MUX_UDP (Q_I, I0, I1, S);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (S => Q) = (1,1);
  endspecify
`endif

endmodule

module IMU22 (I0, I1, Q, S);
  input I0;
  input I1;
  output Q;
  input S;

  not (Q,Q_I);
  MUX_UDP (Q_I, I0, I1, S);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (S => Q) = (1,1);
  endspecify
`endif

endmodule

module IMU24 (I0, I1, Q, S);
  input I0;
  input I1;
  output Q;
  input S;

  not (Q,Q_I);
  MUX_UDP (Q_I, I0, I1, S);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (S => Q) = (1,1);
  endspecify
`endif

endmodule

module IMU4 (I0, I1, I2, I3, Q, S0, S1);
  input I0;
  input I1;
  input I2;
  input I3;
  output Q;
  input S0;
  input S1;

  not (Q,Q_I);
  MUX_UDP (net_1, I0, I1, S0);
  MUX_UDP (net_2, I2, I3, S0);
  MUX_UDP (Q_I, net_1, net_2, S1);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
  endspecify
`endif

endmodule

module IMU42 (I0, I1, I2, I3, Q, S0, S1);
  input I0;
  input I1;
  input I2;
  input I3;
  output Q;
  input S0;
  input S1;

  not (Q,Q_I);
  MUX_UDP (net_1, I0, I1, S0);
  MUX_UDP (net_2, I2, I3, S0);
  MUX_UDP (Q_I, net_1, net_2, S1);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
  endspecify
`endif

endmodule

module IMU44 (I0, I1, I2, I3, Q, S0, S1);
  input I0;
  input I1;
  input I2;
  input I3;
  output Q;
  input S0;
  input S1;

  not (Q,Q_I);
  MUX_UDP (net_1, I0, I1, S0);
  MUX_UDP (net_2, I2, I3, S0);
  MUX_UDP (Q_I, net_1, net_2, S1);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
  endspecify
`endif

endmodule

module IMU8 (I0, I1, I2, I3, I4, I5, I6, I7, Q, S0, S1, S2);
  input I0;
  input I1;
  input I2;
  input I3;
  input I4;
  input I5;
  input I6;
  input I7;
  output Q;
  input S0;
  input S1;
  input S2;

  not (Q,Q_I);
  MUX_UDP (net_2, I0, I1, S0);
  MUX_UDP (net_3, I2, I3, S0);
  MUX_UDP (net_1, net_2, net_3, S1);
  MUX_UDP (net_5, I4, I5, S0);
  MUX_UDP (net_6, I6, I7, S0);
  MUX_UDP (net_4, net_5, net_6, S1);
  MUX_UDP (Q_I, net_1, net_4, S2);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (I4 => Q) = (1,1);
    (I5 => Q) = (1,1);
    (I6 => Q) = (1,1);
    (I7 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
    (S2 => Q) = (1,1);
  endspecify
`endif

endmodule

module IMU82 (I0, I1, I2, I3, I4, I5, I6, I7, Q, S0, S1, S2);
  input I0;
  input I1;
  input I2;
  input I3;
  input I4;
  input I5;
  input I6;
  input I7;
  output Q;
  input S0;
  input S1;
  input S2;

  not (Q,Q_I);
  MUX_UDP (net_2, I0, I1, S0);
  MUX_UDP (net_3, I2, I3, S0);
  MUX_UDP (net_1, net_2, net_3, S1);
  MUX_UDP (net_5, I4, I5, S0);
  MUX_UDP (net_6, I6, I7, S0);
  MUX_UDP (net_4, net_5, net_6, S1);
  MUX_UDP (Q_I, net_1, net_4, S2);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (I4 => Q) = (1,1);
    (I5 => Q) = (1,1);
    (I6 => Q) = (1,1);
    (I7 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
    (S2 => Q) = (1,1);
  endspecify
`endif

endmodule

module IMU84 (I0, I1, I2, I3, I4, I5, I6, I7, Q, S0, S1, S2);
  input I0;
  input I1;
  input I2;
  input I3;
  input I4;
  input I5;
  input I6;
  input I7;
  output Q;
  input S0;
  input S1;
  input S2;

  not (Q,Q_I);
  MUX_UDP (net_2, I0, I1, S0);
  MUX_UDP (net_3, I2, I3, S0);
  MUX_UDP (net_1, net_2, net_3, S1);
  MUX_UDP (net_5, I4, I5, S0);
  MUX_UDP (net_6, I6, I7, S0);
  MUX_UDP (net_4, net_5, net_6, S1);
  MUX_UDP (Q_I, net_1, net_4, S2);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (I4 => Q) = (1,1);
    (I5 => Q) = (1,1);
    (I6 => Q) = (1,1);
    (I7 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
    (S2 => Q) = (1,1);
  endspecify
`endif

endmodule

module IN1 (A, Q);
  input A;
  output Q;

  not (Q, A);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
  endspecify
`endif

endmodule

module IN2 (A, Q);
  input A;
  output Q;

  not (Q, A);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
  endspecify
`endif

endmodule

module IN3 (A, Q);
  input A;
  output Q;

  not (Q, A);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
  endspecify
`endif

endmodule

module IN4 (A, Q);
  input A;
  output Q;

  not (Q, A);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
  endspecify
`endif

endmodule

module IN8 (A, Q);
  input A;
  output Q;

  not (Q, A);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
  endspecify
`endif

endmodule

module INA2 (A, B, Q);
  input A;
  input B;
  output Q;

  not (B_i, B);
  or (Q, A, B_i);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module INA22 (A, B, Q);
  input A;
  input B;
  output Q;

  not (B_i, B);
  or (Q, A, B_i);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module INA23 (A, B, Q);
  input A;
  input B;
  output Q;

  not (B_i, B);
  or (Q, A, B_i);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module INA24 (A, B, Q);
  input A;
  input B;
  output Q;

  not (B_i, B);
  or (Q, A, B_i);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module INO2 (A, B, Q);
  input A;
  input B;
  output Q;

  not (B_i, B);
  and (Q, A, B_i);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module INO22 (A, B, Q);
  input A;
  input B;
  output Q;

  not (B_i, B);
  and (Q, A, B_i);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module INO23 (A, B, Q);
  input A;
  input B;
  output Q;

  not (B_i, B);
  and (Q, A, B_i);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module INO24 (A, B, Q);
  input A;
  input B;
  output Q;

  not (B_i, B);
  and (Q, A, B_i);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module IT1 (A, E, Q);
  input A;
  input E;
  output Q;

  notif1 (Q, A, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module IT12 (A, E, Q);
  input A;
  input E;
  output Q;

  notif1 (Q, A, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module IT13 (A, E, Q);
  input A;
  input E;
  output Q;

  notif1 (Q, A, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module IT14 (A, E, Q);
  input A;
  input E;
  output Q;

  notif1 (Q, A, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module IT1LP (A, E, Q);
  input A;
  input E;
  output Q;

  notif1 (Q, A, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module IT2 (A, EN, Q);
  input A;
  input EN;
  output Q;

  notif0 (Q, A, EN);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (EN => Q) = (1,1);
  endspecify
`endif

endmodule

module IT22 (A, EN, Q);
  input A;
  input EN;
  output Q;

  notif0 (Q, A, EN);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (EN => Q) = (1,1);
  endspecify
`endif

endmodule

module IT23 (A, EN, Q);
  input A;
  input EN;
  output Q;

  notif0 (Q, A, EN);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (EN => Q) = (1,1);
  endspecify
`endif

endmodule

module IT24 (A, EN, Q);
  input A;
  input EN;
  output Q;

  notif0 (Q, A, EN);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (EN => Q) = (1,1);
  endspecify
`endif

endmodule

module IT2LP (A, EN, Q);
  input A;
  input EN;
  output Q;

  notif0 (Q, A, EN);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (EN => Q) = (1,1);
  endspecify
`endif

endmodule

module JK9 (C, J, K, Q, QN, SN);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  DFF_UDP (Q_buf, JK, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge J, posedge C, 0, notifier);
    $setup(negedge J, posedge C, 0, notifier);
    $setup(posedge K, posedge C, 0, notifier);
    $setup(negedge K, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge J, 0, notifier);
    $hold(posedge C, posedge J, 0, notifier);
    $hold(posedge C, negedge K, 0, notifier);
    $hold(posedge C, posedge K, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JK92 (C, J, K, Q, QN, SN);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  DFF_UDP (Q_buf, JK, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge J, posedge C, 0, notifier);
    $setup(negedge J, posedge C, 0, notifier);
    $setup(posedge K, posedge C, 0, notifier);
    $setup(negedge K, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge J, 0, notifier);
    $hold(posedge C, posedge J, 0, notifier);
    $hold(posedge C, negedge K, 0, notifier);
    $hold(posedge C, posedge K, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JK94 (C, J, K, Q, QN, SN);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  DFF_UDP (Q_buf, JK, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge J, posedge C, 0, notifier);
    $setup(negedge J, posedge C, 0, notifier);
    $setup(posedge K, posedge C, 0, notifier);
    $setup(negedge K, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge J, 0, notifier);
    $hold(posedge C, posedge J, 0, notifier);
    $hold(posedge C, negedge K, 0, notifier);
    $hold(posedge C, posedge K, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JKA (C, J, K, Q, QN, RN);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input RN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  DFF_UDP (Q_buf, JK, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge J, posedge C, 0, notifier);
    $setup(negedge J, posedge C, 0, notifier);
    $setup(posedge K, posedge C, 0, notifier);
    $setup(negedge K, posedge C, 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $hold(posedge C, negedge J, 0, notifier);
    $hold(posedge C, posedge J, 0, notifier);
    $hold(posedge C, negedge K, 0, notifier);
    $hold(posedge C, posedge K, 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JKA2 (C, J, K, Q, QN, RN);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input RN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  DFF_UDP (Q_buf, JK, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge J, posedge C, 0, notifier);
    $setup(negedge J, posedge C, 0, notifier);
    $setup(posedge K, posedge C, 0, notifier);
    $setup(negedge K, posedge C, 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $hold(posedge C, negedge J, 0, notifier);
    $hold(posedge C, posedge J, 0, notifier);
    $hold(posedge C, negedge K, 0, notifier);
    $hold(posedge C, posedge K, 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JKA4 (C, J, K, Q, QN, RN);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input RN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  DFF_UDP (Q_buf, JK, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge J, posedge C, 0, notifier);
    $setup(negedge J, posedge C, 0, notifier);
    $setup(posedge K, posedge C, 0, notifier);
    $setup(negedge K, posedge C, 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $hold(posedge C, negedge J, 0, notifier);
    $hold(posedge C, posedge J, 0, notifier);
    $hold(posedge C, negedge K, 0, notifier);
    $hold(posedge C, posedge K, 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JKS9 (C, J, K, Q, QN, SD, SE, SN);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input SD;
  input SE;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  MUX_UDP (JK_buf, JK, SD, SE);
  DFF_UDP (Q_buf, JK_buf, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge J, posedge C &&& (~SE), 0, notifier);
    $setup(negedge J, posedge C &&& (~SE), 0, notifier);
    $setup(posedge K, posedge C &&& (~SE), 0, notifier);
    $setup(negedge K, posedge C &&& (~SE), 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge J &&& (~SE), 0, notifier);
    $hold(posedge C, posedge J &&& (~SE), 0, notifier);
    $hold(posedge C, negedge K &&& (~SE), 0, notifier);
    $hold(posedge C, posedge K &&& (~SE), 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JKS92 (C, J, K, Q, QN, SD, SE, SN);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input SD;
  input SE;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  MUX_UDP (JK_buf, JK, SD, SE);
  DFF_UDP (Q_buf, JK_buf, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge J, posedge C &&& (~SE), 0, notifier);
    $setup(negedge J, posedge C &&& (~SE), 0, notifier);
    $setup(posedge K, posedge C &&& (~SE), 0, notifier);
    $setup(negedge K, posedge C &&& (~SE), 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge J &&& (~SE), 0, notifier);
    $hold(posedge C, posedge J &&& (~SE), 0, notifier);
    $hold(posedge C, negedge K &&& (~SE), 0, notifier);
    $hold(posedge C, posedge K &&& (~SE), 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JKS94 (C, J, K, Q, QN, SD, SE, SN);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input SD;
  input SE;
  input SN;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  MUX_UDP (JK_buf, JK, SD, SE);
  DFF_UDP (Q_buf, JK_buf, C, SN, 1, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (SN => Q) = (1,1);
    (SN => QN) = (1,1);
    $setup(posedge J, posedge C &&& (~SE), 0, notifier);
    $setup(negedge J, posedge C &&& (~SE), 0, notifier);
    $setup(posedge K, posedge C &&& (~SE), 0, notifier);
    $setup(negedge K, posedge C &&& (~SE), 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $recovery(posedge SN, posedge C, 0, notifier);
    $hold(posedge C, negedge J &&& (~SE), 0, notifier);
    $hold(posedge C, posedge J &&& (~SE), 0, notifier);
    $hold(posedge C, negedge K &&& (~SE), 0, notifier);
    $hold(posedge C, posedge K &&& (~SE), 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $hold(posedge C, posedge SN, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge SN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JKSA (C, J, K, Q, QN, RN, SD, SE);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input RN;
  input SD;
  input SE;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  MUX_UDP (JK_buf, JK, SD, SE);
  DFF_UDP (Q_buf, JK_buf, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge J, posedge C &&& (~SE), 0, notifier);
    $setup(negedge J, posedge C &&& (~SE), 0, notifier);
    $setup(posedge K, posedge C &&& (~SE), 0, notifier);
    $setup(negedge K, posedge C &&& (~SE), 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $hold(posedge C, negedge J &&& (~SE), 0, notifier);
    $hold(posedge C, posedge J &&& (~SE), 0, notifier);
    $hold(posedge C, negedge K &&& (~SE), 0, notifier);
    $hold(posedge C, posedge K &&& (~SE), 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JKSA2 (C, J, K, Q, QN, RN, SD, SE);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input RN;
  input SD;
  input SE;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  MUX_UDP (JK_buf, JK, SD, SE);
  DFF_UDP (Q_buf, JK_buf, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge J, posedge C &&& (~SE), 0, notifier);
    $setup(negedge J, posedge C &&& (~SE), 0, notifier);
    $setup(posedge K, posedge C &&& (~SE), 0, notifier);
    $setup(negedge K, posedge C &&& (~SE), 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $hold(posedge C, negedge J &&& (~SE), 0, notifier);
    $hold(posedge C, posedge J &&& (~SE), 0, notifier);
    $hold(posedge C, negedge K &&& (~SE), 0, notifier);
    $hold(posedge C, posedge K &&& (~SE), 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module JKSA4 (C, J, K, Q, QN, RN, SD, SE);
  input C;
  input J;
  input K;
  output Q;
  output QN;
  input RN;
  input SD;
  input SE;

  reg notifier;
  buf (Q, Q_buf);
  not (QN, Q_buf);
  JK_UDP  (JK, J, K, Q_buf);
  MUX_UDP (JK_buf, JK, SD, SE);
  DFF_UDP (Q_buf, JK_buf, C, 1, RN, notifier);

`ifdef functional
`else
  specify
    (C => Q) = (1,1);
    (C => QN) = (1,1);
    (RN => Q) = (1,1);
    (RN => QN) = (1,1);
    $setup(posedge J, posedge C &&& (~SE), 0, notifier);
    $setup(negedge J, posedge C &&& (~SE), 0, notifier);
    $setup(posedge K, posedge C &&& (~SE), 0, notifier);
    $setup(negedge K, posedge C &&& (~SE), 0, notifier);
    $recovery(posedge RN, posedge C, 0, notifier);
    $setup(posedge SD, posedge C &&& (SE), 0, notifier);
    $setup(negedge SD, posedge C &&& (SE), 0, notifier);
    $setup(posedge SE, posedge C, 0, notifier);
    $setup(negedge SE, posedge C, 0, notifier);
    $hold(posedge C, negedge J &&& (~SE), 0, notifier);
    $hold(posedge C, posedge J &&& (~SE), 0, notifier);
    $hold(posedge C, negedge K &&& (~SE), 0, notifier);
    $hold(posedge C, posedge K &&& (~SE), 0, notifier);
    $hold(posedge C, posedge RN, 0, notifier);
    $hold(posedge C, negedge SD &&& (SE), 0, notifier);
    $hold(posedge C, posedge SD &&& (SE), 0, notifier);
    $hold(posedge C, negedge SE, 0, notifier);
    $hold(posedge C, posedge SE, 0, notifier);
    $width(posedge C, 1, 0, notifier);
    $width(negedge C, 1, 0, notifier);
    $width(negedge RN, 1, 0, notifier);
  endspecify
`endif

endmodule

module LOGIC0 (Q);
  output Q;

  buf (Q,0);
 
endmodule

module LOGIC1 (Q);
  output Q;

  buf (Q,1);
 
endmodule

module MU2 (I0, I1, Q, S);
  input I0;
  input I1;
  output Q;
  input S;

  MUX_UDP (Q, I0, I1, S);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (S => Q) = (1,1);
  endspecify
`endif

endmodule

module MU22 (I0, I1, Q, S);
  input I0;
  input I1;
  output Q;
  input S;

  MUX_UDP (Q, I0, I1, S);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (S => Q) = (1,1);
  endspecify
`endif

endmodule

module MU24 (I0, I1, Q, S);
  input I0;
  input I1;
  output Q;
  input S;

  MUX_UDP (Q, I0, I1, S);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (S => Q) = (1,1);
  endspecify
`endif

endmodule

module MU4 (I0, I1, I2, I3, Q, S0, S1);
  input I0;
  input I1;
  input I2;
  input I3;
  output Q;
  input S0;
  input S1;

  MUX_UDP (net_1, I0, I1, S0);
  MUX_UDP (net_2, I2, I3, S0);
  MUX_UDP (Q, net_1, net_2, S1);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
  endspecify
`endif

endmodule

module MU42 (I0, I1, I2, I3, Q, S0, S1);
  input I0;
  input I1;
  input I2;
  input I3;
  output Q;
  input S0;
  input S1;

  MUX_UDP (net_1, I0, I1, S0);
  MUX_UDP (net_2, I2, I3, S0);
  MUX_UDP (Q, net_1, net_2, S1);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
  endspecify
`endif

endmodule

module MU44 (I0, I1, I2, I3, Q, S0, S1);
  input I0;
  input I1;
  input I2;
  input I3;
  output Q;
  input S0;
  input S1;

  MUX_UDP (net_1, I0, I1, S0);
  MUX_UDP (net_2, I2, I3, S0);
  MUX_UDP (Q, net_1, net_2, S1);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
  endspecify
`endif

endmodule

module MU8 (I0, I1, I2, I3, I4, I5, I6, I7, Q, S0, S1, S2);
  input I0;
  input I1;
  input I2;
  input I3;
  input I4;
  input I5;
  input I6;
  input I7;
  output Q;
  input S0;
  input S1;
  input S2;

  MUX_UDP (net_2, I0, I1, S0);
  MUX_UDP (net_3, I2, I3, S0);
  MUX_UDP (net_1, net_2, net_3, S1);
  MUX_UDP (net_5, I4, I5, S0);
  MUX_UDP (net_6, I6, I7, S0);
  MUX_UDP (net_4, net_5, net_6, S1);
  MUX_UDP (Q, net_1, net_4, S2);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (I4 => Q) = (1,1);
    (I5 => Q) = (1,1);
    (I6 => Q) = (1,1);
    (I7 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
    (S2 => Q) = (1,1);
  endspecify
`endif

endmodule

module MU82 (I0, I1, I2, I3, I4, I5, I6, I7, Q, S0, S1, S2);
  input I0;
  input I1;
  input I2;
  input I3;
  input I4;
  input I5;
  input I6;
  input I7;
  output Q;
  input S0;
  input S1;
  input S2;

  MUX_UDP (net_2, I0, I1, S0);
  MUX_UDP (net_3, I2, I3, S0);
  MUX_UDP (net_1, net_2, net_3, S1);
  MUX_UDP (net_5, I4, I5, S0);
  MUX_UDP (net_6, I6, I7, S0);
  MUX_UDP (net_4, net_5, net_6, S1);
  MUX_UDP (Q, net_1, net_4, S2);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (I4 => Q) = (1,1);
    (I5 => Q) = (1,1);
    (I6 => Q) = (1,1);
    (I7 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
    (S2 => Q) = (1,1);
  endspecify
`endif

endmodule

module MU84 (I0, I1, I2, I3, I4, I5, I6, I7, Q, S0, S1, S2);
  input I0;
  input I1;
  input I2;
  input I3;
  input I4;
  input I5;
  input I6;
  input I7;
  output Q;
  input S0;
  input S1;
  input S2;

  MUX_UDP (net_2, I0, I1, S0);
  MUX_UDP (net_3, I2, I3, S0);
  MUX_UDP (net_1, net_2, net_3, S1);
  MUX_UDP (net_5, I4, I5, S0);
  MUX_UDP (net_6, I6, I7, S0);
  MUX_UDP (net_4, net_5, net_6, S1);
  MUX_UDP (Q, net_1, net_4, S2);

`ifdef functional
`else
  specify
    (I0 => Q) = (1,1);
    (I1 => Q) = (1,1);
    (I2 => Q) = (1,1);
    (I3 => Q) = (1,1);
    (I4 => Q) = (1,1);
    (I5 => Q) = (1,1);
    (I6 => Q) = (1,1);
    (I7 => Q) = (1,1);
    (S0 => Q) = (1,1);
    (S1 => Q) = (1,1);
    (S2 => Q) = (1,1);
  endspecify
`endif

endmodule

module NA2 (A, B, Q);
  input A;
  input B;
  output Q;

  nand (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module NA22 (A, B, Q);
  input A;
  input B;
  output Q;

  nand (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module NA23 (A, B, Q);
  input A;
  input B;
  output Q;

  nand (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module NA24 (A, B, Q);
  input A;
  input B;
  output Q;

  nand (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module NA3 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  nand (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module NA32 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  nand (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module NA33 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  nand (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module NA34 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  nand (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module NA4 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  nand (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module NA42 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  nand (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module NA43 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  nand (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module NA44 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  nand (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module NA5 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  nand (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module NA52 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  nand (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module NA53 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  nand (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module NA54 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  nand (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module NA6 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  nand (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module NA62 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  nand (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module NA63 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  nand (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module NA64 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  nand (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module NA7 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  nand (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module NA72 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  nand (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module NA73 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  nand (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module NA74 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  nand (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module NA8 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  nand (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module NA82 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  nand (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module NA83 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  nand (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module NA84 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  nand (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module NO2 (A, B, Q);
  input A;
  input B;
  output Q;

  nor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module NO22 (A, B, Q);
  input A;
  input B;
  output Q;

  nor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module NO23 (A, B, Q);
  input A;
  input B;
  output Q;

  nor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module NO24 (A, B, Q);
  input A;
  input B;
  output Q;

  nor (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module NO3 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  nor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module NO32 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  nor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module NO33 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  nor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module NO34 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  nor (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module NO4 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  nor (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module NO42 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  nor (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module NO43 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  nor (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module NO44 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  nor (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module NO5 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  nor (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module NO52 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  nor (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module NO53 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  nor (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module NO54 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  nor (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module NO6 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  nor (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module NO62 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  nor (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module NO63 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  nor (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module NO64 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  nor (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module NO7 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  nor (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module NO72 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  nor (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module NO73 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  nor (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module NO74 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  nor (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module NO8 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  nor (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module NO82 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  nor (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module NO83 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  nor (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module NO84 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  nor (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module OA21 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  or (net_1, A, B);
  and (Q, C, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module OA211 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  or (net_2, B, A);
  and (Q, D, C, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module OA22 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  or (net_0, D, C);
  or (net_1, B, A);
  and (Q, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module OA221 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  or (net_1, B, A);
  or (net_2, C, D);
  and (Q, E, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module OA222 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  or (net_0, F, E);
  or (net_1, B, A);
  or (net_2, D, C);
  and (Q, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module OA31 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  or (net_1, B, A, C);
  and (Q, D, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module OA311 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  or (net_2, A, C, B);
  and (Q, D, E, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module OA32 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  or (net_0, D, E);
  or (net_1, A, C, B);
  and (Q, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module OA321 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  or (net_1, C, B, A);
  or (net_2, E, D);
  and (Q, F, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module OA322 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  or (net_0, D, E);
  or (net_1, G, F);
  or (net_2, B, A, C);
  and (Q, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module OA33 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  or (net_0, F, E, D);
  or (net_1, C, B, A);
  and (Q, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module OA331 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  or (net_1, C, B, A);
  or (net_2, E, D, F);
  and (Q, G, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module OA332 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  or (net_0, H, G);
  or (net_1, C, B, A);
  or (net_2, D, F, E);
  and (Q, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module OA333 (A, B, C, D, E, F, G, H, I, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  input I;
  output Q;

  or (net_0, I, H, G);
  or (net_1, C, B, A);
  or (net_2, F, E, D);
  and (Q, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
    (I => Q) = (1,1);
  endspecify
`endif

endmodule

module ON21 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  not (Q,Q_I);
  or (net_1, A, B);
  and (Q_I, C, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module ON211 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  not (Q,Q_I);
  or (net_2, B, A);
  and (Q_I, D, C, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module ON22 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  not (Q,Q_I);
  or (net_0, D, C);
  or (net_1, B, A);
  and (Q_I, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module ON221 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  not (Q,Q_I);
  or (net_1, B, A);
  or (net_2, C, D);
  and (Q_I, E, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module ON222 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  not (Q,Q_I);
  or (net_0, F, E);
  or (net_1, B, A);
  or (net_2, D, C);
  and (Q_I, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module ON31 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  not (Q,Q_I);
  or (net_1, B, A, C);
  and (Q_I, D, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module ON311 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  not (Q,Q_I);
  or (net_2, A, C, B);
  and (Q_I, D, E, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module ON32 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  not (Q,Q_I);
  or (net_0, D, E);
  or (net_1, A, C, B);
  and (Q_I, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module ON321 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  not (Q,Q_I);
  or (net_1, C, B, A);
  or (net_2, E, D);
  and (Q_I, F, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module ON322 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  not (Q,Q_I);
  or (net_0, D, E);
  or (net_1, G, F);
  or (net_2, B, A, C);
  and (Q_I, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module ON33 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  not (Q,Q_I);
  or (net_0, F, E, D);
  or (net_1, C, B, A);
  and (Q_I, net_0, net_1);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module ON331 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  not (Q,Q_I);
  or (net_1, C, B, A);
  or (net_2, E, D, F);
  and (Q_I, G, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module ON332 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  not (Q,Q_I);
  or (net_0, H, G);
  or (net_1, C, B, A);
  or (net_2, D, F, E);
  and (Q_I, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module ON333 (A, B, C, D, E, F, G, H, I, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  input I;
  output Q;

  not (Q,Q_I);
  or (net_0, I, H, G);
  or (net_1, C, B, A);
  or (net_2, F, E, D);
  and (Q_I, net_0, net_1, net_2);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
    (I => Q) = (1,1);
  endspecify
`endif

endmodule

module OR2 (A, B, Q);
  input A;
  input B;
  output Q;

  or (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module OR22 (A, B, Q);
  input A;
  input B;
  output Q;

  or (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module OR23 (A, B, Q);
  input A;
  input B;
  output Q;

  or (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module OR24 (A, B, Q);
  input A;
  input B;
  output Q;

  or (Q, A, B);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
  endspecify
`endif

endmodule

module OR3 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  or (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module OR32 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  or (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module OR33 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  or (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module OR34 (A, B, C, Q);
  input A;
  input B;
  input C;
  output Q;

  or (Q, A, B, C);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
  endspecify
`endif

endmodule

module OR4 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  or (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module OR42 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  or (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module OR43 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  or (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module OR44 (A, B, C, D, Q);
  input A;
  input B;
  input C;
  input D;
  output Q;

  or (Q, A, B, C, D);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
  endspecify
`endif

endmodule

module OR5 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  or (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module OR52 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  or (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module OR53 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  or (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module OR54 (A, B, C, D, E, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  output Q;

  or (Q, A, B, C, D, E);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
  endspecify
`endif

endmodule

module OR6 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  or (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module OR62 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  or (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module OR63 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  or (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module OR64 (A, B, C, D, E, F, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  output Q;

  or (Q, A, B, C, D, E, F);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
  endspecify
`endif

endmodule

module OR7 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  or (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module OR72 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  or (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module OR73 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  or (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module OR74 (A, B, C, D, E, F, G, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  output Q;

  or (Q, A, B, C, D, E, F, G);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
  endspecify
`endif

endmodule

module OR8 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  or (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module OR82 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  or (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module OR83 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  or (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module OR84 (A, B, C, D, E, F, G, H, Q);
  input A;
  input B;
  input C;
  input D;
  input E;
  input F;
  input G;
  input H;
  output Q;

  or (Q, A, B, C, D, E, F, G, H);

`ifdef functional
`else
  specify
    (A => Q) = (1,1);
    (B => Q) = (1,1);
    (C => Q) = (1,1);
    (D => Q) = (1,1);
    (E => Q) = (1,1);
    (F => Q) = (1,1);
    (G => Q) = (1,1);
    (H => Q) = (1,1);
  endspecify
`endif

endmodule

module SIGNALHOLD (SIG);
   inout SIG;

   buf (SIG_buf, SIG);
//   buf (pull1, pull0)(SIG, SIG_buf);
 
endmodule

`endcelldefine
