rm -f adder_4bit_stat.txt
verimap \
-r ams.rls \
-a ams.asn \
-p ams.prm \
-g ams_dr-gen.v \
-i ams.v,ams_dr-cl.v,ams_sr-misc.v,ams_sr-c.v \
-o adder_4bit_dr.v \
adder_4bit_sr.v \
-ol2 -tl2 -cd1 \
-gd gate_delay \
-sl3 -s adder_4bit_stat.txt \
-clk *.clk -rst *.reset
