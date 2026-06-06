program server_test;
uses Net;

var
  listener: HttpListener;
  router: HttpRouter;

function MyHandler(): string;
begin
  MyHandler := '{"status": "ok", "message": "Hello from Pascal Server via Rust Axum!"}';
end;

begin
  writeln('Iniciando o servidor na porta 8080...');
  listener := HttpListen(8080);
  router := NewHttpRouter;
  router := HttpRoute(router, '/pascal', 'GET', MyHandler);
  writeln('Servidor pronto! Acesse http://localhost:8080/pascal');
  HttpServe(listener, router);
end.
