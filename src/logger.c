#include "logger.h"
#include "commons.h"
#include "parser/types.h"

extern YYLTYPE yylloc;

SourceLocation from_yylloc(YYLTYPE loc) {
    return (SourceLocation) {
        .first_line = loc.first_line,
        .first_column = loc.first_column,
        .last_line = loc.last_line,
        .last_column = loc.last_column,
        .file_name = loc.file_name
    };
}

void yyerror_internal(const char *msg, SourceLocation loc) {
    LOG_ERROR("%s:%d.%d-%d.%d: error: %s\n",
              loc.file_name ? loc.file_name : "input",
              loc.first_line, loc.first_column,
              loc.last_line, loc.last_column,
              msg);
}

void yyerror_internal_format(SourceLocation loc, const char *fmt, ...) {
    char buffer[1024];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    yyerror_internal(buffer, loc);
}

void yyerror(const char *msg) {
    yyerror_internal(msg, from_yylloc(yylloc));
}
