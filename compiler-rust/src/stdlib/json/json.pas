unit json;
interface
  function JsonParse(json_str: string): integer;
  function JsonStringify(handle: integer): string;
  procedure JsonFree(handle: integer);
implementation
  function JsonParse(json_str: string): integer; external;
  function JsonStringify(handle: integer): string; external;
  procedure JsonFree(handle: integer); external;
end.
