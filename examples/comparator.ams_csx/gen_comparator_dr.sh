rm -f ams_dr-gen.v comparator_dr.v
#valgrind --tool=memcheck -v --leak-check=yes --show-reachable=yes --leak-resolution=low --num-callers=8 --suppressions=valgrind.supp \
../../src/verimap \
-a ams.asn -r ams.rls -p ams.prm,ams.rti -g ams_dr-gen.v \
-i ams.v,ams_sr-misc.v,ams_sr-c.v,ams_dr-cl.v,ams_adr-cnv.v,ams_adr-df_ta_clk2.v \
-o comparator_dr.v comparator_sr.v \
-ol3 -tl2 -as -op area,transistor_number \
-clk *.clk -rst *.rst -ra1