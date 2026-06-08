unit Strings;

interface

uses Collections;
function Length(str: string): integer;
function IntToStr(int: integer): string;
function StrToInt(str: string): integer;
function UpperCase(str: string): string;
function LowerCase(str: string): string;
function Trim(str: string): string;
function Substring(str: string; start: integer; len: integer): string;
function IndexOf(str: string; sub: string): integer;
function Contains(str: string; sub: string): boolean;
function Replace(str: string; search: string; replace: string): string;
function Split(str: string; sep: string): integer;
function Join(list: integer; sep: string): string;

implementation

function Length(str: string): integer; external name 'str_len';

function IntToStr(int: integer): string; external name 'str_int_to_str';

function StrToInt(str: string): integer; external name 'str_str_to_int';

function UpperCase(str: string): string; external name 'str_upper_case';

function LowerCase(str: string): string; external name 'str_lower_case';

function Trim(str: string): string; external name 'str_trim';

function Substring(str: string; start: integer; len: integer): string; external name 'str_substring';

function IndexOf(str: string; sub: string): integer; external name 'str_index_of';

function Contains(str: string; sub: string): boolean; external name 'str_contains';

function Replace(str: string; search: string; replace: string): string; external name 'str_replace';

function Split(str: string; sep: string): integer; external name 'str_split';

function Join(list: integer; sep: string): string; external name 'str_join';

end.
