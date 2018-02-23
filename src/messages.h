#ifndef _MESSAGES_H_
#define _MESSAGES_H_

extern void Error(const char *format, ...);
extern void Warning(const char *format, ...);
extern void Message(const char *format, ...);
extern void Progress(const char *format, ...);
extern void Info(const char *format, ...);

#endif
