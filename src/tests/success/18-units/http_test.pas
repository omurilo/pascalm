program http_test;
uses Net, Json;

var
  resp: HttpResponse;
  json_data: string;

begin
  resp := HttpGet('https://httpbin.org/ip');
  json_data := ToJson(resp);
  writeln('JSON: ', JsonParse(json_data));
end.
