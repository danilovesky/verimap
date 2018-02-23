module adder_4bit (a, b, s);
  input [3:0] a;
  input [3:0] b;
  output [4:0] s;
  wire [2:0] c;

  // bit 0
  EO1 inst_s[0] (.A(a[0]), .B(b[0]), .Q(s[0]));
  AND2 inst_c[0] (.A(a[0]), .B(b[0]), .Q(c[0]));

  //bit 1
  EO3 inst_s[1] (.A(a[1]), .B(b[1]), .C(c[0]), .Q(s[1]));
  AO222 inst_c[1] (.A(a[1]), .B(b[1]), .C(a[1]), .D(c[0]), .E(b[1]), .F(c[0]), .Q(c[1]));

  //bit 2
  EO3 inst_s[2] (.A(a[2]), .B(b[2]), .C(c[1]), .Q(s[2]));
  AO222 inst_c[2] (.A(a[2]), .B(b[2]), .C(a[2]), .D(c[1]), .E(b[2]), .F(c[1]), .Q(c[2]));

  //bit 3
  EO3 inst_s[3] (.A(a[3]), .B(b[3]), .C(c[2]), .Q(s[3]));
  AO222 inst_c[3] (.A(a[3]), .B(b[3]), .C(a[3]), .D(c[2]), .E(b[3]), .F(c[2]), .Q(s[4]));
endmodule

