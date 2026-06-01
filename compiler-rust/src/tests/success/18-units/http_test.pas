program http_test;
uses net;
var
  resp: HttpResponse;
  json_data: string;
begin
  resp := HttpGet('https://httpbin.org/ip');
  
  { Look at this beauty: UFCS in action! }
  json_data := resp.HttpJson();
  writeln('JSON: ', json_data);
end.
