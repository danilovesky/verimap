module cmp_1bit (a, b, gt, eq, lt);
  input a, b;
  output gt, eq, lt;
  wire not_a, not_b;
  
  // gt = a' b
  // eq = a b + a' b' = (a xor b)'
  // lt = a b'
  
  IN1 inst_not_a (.A(a), .Q(not_a));
  IN1 inst_not_b (.A(b), .Q(not_b));
  AND2 inst_gt (.A(a), .B(not_b), .Q(gt));
  AO22 inst_eq (.A(a), .B(b), .C(not_a), .D(not_b), .Q(eq));
  AND2 inst_lt (.A(b), .B(not_a), .Q(lt));
endmodule


module cmp_combiner (gt1, eq1, lt1, gt0, eq0, lt0, gt, eq, lt);
  input  gt1, eq1, lt1;
  input  gt0, eq0, lt0;
  output gt, eq, lt;
  
  // gt = (a[1] > b[1]) + ( (a[1] == b[1]) (a[0] > b[0]) ) = gt1 + eq1 gt0
  // eq = (a[1] == b[1]) (a[0] == b[0])                    = eq1 eq0
  // lt = (a[1] < b[1]) + ( (a[1] == b[1]) (a[0] < b[0]) ) = lt1 + eq1 lt0
  
  AO21 inst_gt (.A(gt0), .B(eq1), .C(gt1), .Q(gt));
  AND2 inst_eq (.A(eq0), .B(eq1), .Q(eq));
  AO21 inst_lt (.A(lt0), .B(eq1), .C(lt1), .Q(lt));
endmodule


module cmp_4bit (a, b, gt, eq, lt);
  input [3:0] a, b;
  output gt, eq, lt;
  wire [3:0] cmp_gt, cmp_eq, cmp_lt;
  wire cmp_gt_32, cmp_eq_32, cmp_lt_32;
  wire cmp_gt_321, cmp_eq_321, cmp_lt_321;
  
  cmp_1bit inst_cmp_0 (.a(a[0]), .b(b[0]), .gt(cmp_gt[0]), .eq(cmp_eq[0]), .lt(cmp_lt[0]));
  cmp_1bit inst_cmp_1 (.a(a[1]), .b(b[1]), .gt(cmp_gt[1]), .eq(cmp_eq[1]), .lt(cmp_lt[1]));
  cmp_1bit inst_cmp_2 (.a(a[2]), .b(b[2]), .gt(cmp_gt[2]), .eq(cmp_eq[2]), .lt(cmp_lt[2]));
  cmp_1bit inst_cmp_3 (.a(a[3]), .b(b[3]), .gt(cmp_gt[3]), .eq(cmp_eq[3]), .lt(cmp_lt[3]));
  
  cmp_combiner inst_32 (.gt1(cmp_gt[3]), .eq1(cmp_eq[3]), .lt1(cmp_lt[3]), .gt0(cmp_gt[2]), .eq0(cmp_eq[2]), .lt0(cmp_lt[2]), .gt(cmp_gt_32), .eq(cmp_eq_32), .lt(cmp_lt_32));
  cmp_combiner inst_321 (.gt1(cmp_gt_32), .eq1(cmp_eq_32), .lt1(cmp_lt_32), .gt0(cmp_gt[1]), .eq0(cmp_eq[1]), .lt0(cmp_lt[1]), .gt(cmp_gt_321), .eq(cmp_eq_321), .lt(cmp_lt_321));
  cmp_combiner inst_3210 (.gt1(cmp_gt_321), .eq1(cmp_eq_321), .lt1(cmp_lt_321), .gt0(cmp_gt[0]), .eq0(cmp_eq[0]), .lt0(cmp_lt[0]), .gt(gt), .eq(eq), .lt(lt));
endmodule
