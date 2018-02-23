rm -f comparator_stat.txt
verimap \
-r ams.rls \
-a ams.asn \
-p ams.prm \
-g ams_dr-gen.v \
-i ams.v,ams_dr-cl.v,ams_sr-misc.v \
-o comparator_dr.v \
comparator_sr.v \
-ol2 -tl2 \
-gd gate_delay \
-sl3 -s comparator_stat.txt \
-clk *.clk -rst *.reset
