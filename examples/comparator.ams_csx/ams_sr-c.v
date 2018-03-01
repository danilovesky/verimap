
//  C Elements

module cn02d1 (a1, a2, q, qn);
  input a1, a2;
  output q, qn;

  AN222 inst_qn (.A(a1), .B(a2), .C(a1), .D(q), .E(a2), .F(q), .Q(qn));
  IN1 inst_q (.A(qn), .Q(q));
endmodule


//  C Elements with Clear

module cc02d1 (a1, a2, q, qn, cdn);
  input cdn;
  input a1, a2;
  output q, qn;
  wire w1, w2;

  AND2 inst_w1 (.A(cdn), .B(a1), .Q(w1));
  AND2 inst_w2 (.A(cdn), .B(a2), .Q(w2));
  cn02d1 inst_q (.a1(w1), .a2(w2), .q(q), .qn(qn));
endmodule


//  C Elements with Set

module cp02d1 (a1, a2, q, qn, sdn);
  input sdn;
  input a1, a2;
  output q, qn;
  wire w1, w2;

  INA2 inst_w1 (.A(a1), .B(sdn), .Q(w1));
  INA2 inst_w2 (.A(a2), .B(sdn), .Q(w2));
  cn02d1 inst_q (.a1(w1), .a2(w2), .q(q), .qn(qn));
endmodule


//  C Elements with Clear and Set

module cb02d1 (a1, a2, q, qn, cdn, sdn);
  input cdn, sdn;
  input a1, a2;
  output q, qn;
  wire v1, v2;
  wire w1, w2;

  NA2 inst_v1 (.A(a1), .B(cdn), .Q(v1));
  NA2 inst_w1 (.A(v1), .B(sdn), .Q(w1));
  NA2 inst_v2 (.A(a2), .B(cdn), .Q(v2));
  NA2 inst_w2 (.A(v2), .B(sdn), .Q(w2));
  cn02d1 inst_q (.a1(w1), .a2(w2), .q(q), .qn(qn));
endmodule
