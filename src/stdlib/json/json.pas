unit json;
interface
  function JsonParse(json_str: string): integer;
  function JsonStringify(handle: integer): string;
  function JsonGetString(handle: integer; key: string): string;
  procedure JsonFree(handle: integer);
implementation
  function JsonParse(json_str: string): integer; external;
  function JsonStringify(handle: integer): string; external;
  function JsonGetString(handle: integer; key: string): string; external;
  procedure JsonFree(handle: integer); external;
end.
