#ifndef _STR_UTILS_H_
#define _STR_UTILS_H_

#define SYMBOL_ESCAPE          '\\'
#define SYMBOL_UNDERSCORE      '_'
#define INDENT_SYMBOL          ' '
#define INDENT_DELTA           2
#define SYMBOL_NAME_SEP        ','
#define SYMBOL_NAME_SPACE_SEP  '.'
#define SYMBOL_ASSIGNMENT      '='
#define SYMBOL_WIRE_META       '?'
#define NAME_STDIO             "-"

extern "C" char* namecopy(char* name);
extern "C" char* nameresize(char*& name, int size);
extern "C" char* name2pattern(const char* pattern, ...);
extern "C" char* name2name_(char* name);
extern "C" int indent(char*& str, int dir, int delta = INDENT_DELTA, char symbol = INDENT_SYMBOL);
extern "C" int namesnum(const char* names);
extern "C" char* names2name(const char* names, int index);
extern "C" int namesnamenum(const char* names, char* name);

#endif


