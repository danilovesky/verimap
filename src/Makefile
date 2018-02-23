CC = g++
CFLAGS = -m32
LDFLAGS = -static -s
LIBS =
YACC = bison
YFLAGS= -d
YACC_DEBUG = NO_DEBUG_YACC
LEX = flex
LEX_VERSION = FLEX_2_5_33
LEX_DEBUG = NO_DEBUG_LEX
PLATFORM=LINUX #WIN32
LFLAGS =
RM = rm
RFLAGS = -f
CP = cp
PREFIX = /usr/local/verimap
BIN_PATH = /usr/local/bin

SVERILOG_PARSER = sverilog
RULES_PARSER = rules
PARAMETERS_PARSER = parameters
ASSIGNMENTS_PARSER = assignments
OBJECTS_PARSER = objects

CMN_OBJS = str_utils.o param.o messages.o
SV_OBJS = sv_object.o sv_delay.o sv_range.o sv_trans.o sv_parameter.o sv_port.o sv_net.o sv_connection.o sv_instance.o sv_module.o sv_circuit.o sv_rule.o sv_assignment.o sv_lib.o
CD_OBJS = cd_engine.o
VERIMAP_OBJS = $(CMN_OBJS) $(SV_OBJS) $(CD_OBJS) verimap_main.o verimap_params.o verimap_msgs.o $(SVERILOG_PARSER)_l.o $(SVERILOG_PARSER)_y.o $(RULES_PARSER)_l.o $(RULES_PARSER)_y.o $(PARAMETERS_PARSER)_l.o $(PARAMETERS_PARSER)_y.o hash.o $(ASSIGNMENTS_PARSER)_l.o $(ASSIGNMENTS_PARSER)_y.o $(OBJECTS_PARSER)_l.o $(OBJECTS_PARSER)_y.o
VERIMAP = verimap
VERIMAP_BINS = $(VERIMAP)
BINS = $(VERIMAP_BINS)
OBJS = $(VERIMAP_OBJS)
README = index.htm verimap.gif
DOCS = $(README)

define EXEC_DEPENDENCER
$(SHELL) -ec '$(CC) -M $(CFLAGS) -D $(LEX_VERSION) -D $(LEX_DEBUG) -D $(YACC_DEBUG) -D $(PLATFORM) $< | sed '\''s/$*.o/& $@/g'\'' > $@'
endef

define EXEC_COMPILER
$(CC) -c $(CFLAGS) -D $(LEX_VERSION) -D $(LEX_DEBUG) -D $(YACC_DEBUG) -D $(PLATFORM) $< -o $@
endef

define EXEC_LINKER
$(CC) ${CFLAGS} $(LDFLAGS) $(LIBS) $^ -o $@
endef

.PHONY = all install clean

all: $(BINS)

install:
	if [ ! -e $(PREFIX) ] ; then mkdir $(PREFIX); fi
	$(CP) $(BINS) $(DOCS) $(PREFIX)
	if [ ! -e $(BIN_PATH)/$(VERIMAP) ]; then ln -s $(PREFIX)/$(VERIMAP) $(BIN_PATH)/$(VERIMAP); fi

uninstall:
	rm $(BIN_PATH)/$(VERIMAP)
	rm -rf $(PREFIX)

$(VERIMAP_BINS): $(VERIMAP_OBJS)
	$(EXEC_LINKER)

$(SVERILOG_PARSER)_l.l: $(SVERILOG_PARSER)_y.c $(SVERILOG_PARSER)_y.h
	

$(SVERILOG_PARSER)_l.c: $(SVERILOG_PARSER)_l.l
	$(LEX) $(LFLAGS) -P$(SVERILOG_PARSER)_ -o$@ $^

$(SVERILOG_PARSER)_y.c $(SVERILOG_PARSER)_y.h: $(SVERILOG_PARSER)_y.y
	$(YACC) $(YFLAGS) -p $(SVERILOG_PARSER)_ -o$(SVERILOG_PARSER)_y.c $^


$(RULES_PARSER)_l.l: $(RULES_PARSER)_y.c $(RULES_PARSER)_y.h
	

$(RULES_PARSER)_l.c: $(RULES_PARSER)_l.l
	$(LEX) $(LFLAGS) -P$(RULES_PARSER)_ -o$@ $^

$(RULES_PARSER)_y.c $(RULES_PARSER)_y.h: $(RULES_PARSER)_y.y
	$(YACC) $(YFLAGS) -p $(RULES_PARSER)_ -o$(RULES_PARSER)_y.c $^


$(PARAMETERS_PARSER)_l.l: $(PARAMETERS_PARSER)_y.c $(PARAMETERS_PARSER)_y.h
	

$(PARAMETERS_PARSER)_l.c: $(PARAMETERS_PARSER)_l.l
	$(LEX) $(LFLAGS) -P$(PARAMETERS_PARSER)_ -o$@ $^

$(PARAMETERS_PARSER)_y.c $(PARAMETERS_PARSER)_y.h: $(PARAMETERS_PARSER)_y.y
	$(YACC) $(YFLAGS) -p $(PARAMETERS_PARSER)_ -o$(PARAMETERS_PARSER)_y.c $^


$(ASSIGNMENTS_PARSER)_l.l: $(ASSIGNMENTS_PARSER)_y.c $(ASSIGNMENTS_PARSER)_y.h
	

$(ASSIGNMENTS_PARSER)_l.c: $(ASSIGNMENTS_PARSER)_l.l
	$(LEX) $(LFLAGS) -P$(ASSIGNMENTS_PARSER)_ -o$@ $^

$(ASSIGNMENTS_PARSER)_y.c $(ASSIGNMENTS_PARSER)_y.h: $(ASSIGNMENTS_PARSER)_y.y
	$(YACC) $(YFLAGS) -p $(ASSIGNMENTS_PARSER)_ -o$(ASSIGNMENTS_PARSER)_y.c $^


$(OBJECTS_PARSER)_l.l: $(OBJECTS_PARSER)_y.c $(OBJECTS_PARSER)_y.h
	

$(OBJECTS_PARSER)_l.c: $(OBJECTS_PARSER)_l.l
	$(LEX) $(LFLAGS) -P$(OBJECTS_PARSER)_ -o$@ $^

$(OBJECTS_PARSER)_y.c $(OBJECTS_PARSER)_y.h: $(OBJECTS_PARSER)_y.y
	$(YACC) $(YFLAGS) -p $(OBJECTS_PARSER)_ -o$(OBJECTS_PARSER)_y.c $^

%.o: %.c
	$(EXEC_COMPILER)

%.d: %.c
	$(EXEC_DEPENDENCER)

clean:
	$(RM) $(RFLAGS) $(BINS)
	$(RM) $(RFLAGS) $(SVERILOG_PARSER)_y.c $(SVERILOG_PARSER)_y.h $(SVERILOG_PARSER)_l.c
	$(RM) $(RFLAGS) $(RULES_PARSER)_y.c $(RULES_PARSER)_y.h $(RULES_PARSER)_l.c
	$(RM) $(RFLAGS) $(PARAMETERS_PARSER)_y.c $(PARAMETERS_PARSER)_y.h $(PARAMETERS_PARSER)_l.c
	$(RM) $(RFLAGS) $(ASSIGNMENTS_PARSER)_y.c $(ASSIGNMENTS_PARSER)_y.h $(ASSIGNMENTS_PARSER)_l.c
	$(RM) $(RFLAGS) $(OBJECTS_PARSER)_y.c $(OBJECTS_PARSER)_y.h $(OBJECTS_PARSER)_l.c
	$(RM) $(RFLAGS) *.d
	$(RM) $(RFLAGS) *.o
	$(RM) $(RFLAGS) *.~*
	$(RM) $(RFLAGS) core

include $(OBJS:.o=.d)
