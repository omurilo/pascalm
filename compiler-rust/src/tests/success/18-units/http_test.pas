program http_test;
uses Net, Json;
var
  resp: HttpResponse;
  json_data: string;
begin
  resp := HttpGet('https://httpbin.org/ip');
  
  json_data := resp.ToJson();
  writeln('JSON: ', json_data.JsonParse());
end.
