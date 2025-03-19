dig [0,9]
alpha [a-zA-Z]
ws [ \t]
name ({alpha}|{dig}|\$)({alpha}|{dig}|\_|\.|\-|\/|\$)*
int [-+]?{dig}+\.?([eE][-+]?{dig}+)?
float [-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number {int}|{float}
