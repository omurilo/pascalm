unit Net;
interface
  type 
    HttpResponse = record
      inner_ptr: integer;
    end;

    HttpListener = record
      inner_ptr: integer;
    end;

    HttpRouter = record
      inner_ptr: integer;
    end;

    { Função callback para o handler }
    PascalHandler = function: string;

  function HttpGet(url: string): HttpResponse;
  function HttpPost(url: string; body: string): HttpResponse;
  function ToJson(resp: HttpResponse): string;
  
  function HttpListen(port: integer): HttpListener;
  function NewHttpRouter: HttpRouter;
  function HttpRoute(router: HttpRouter; path: string; method: string; handler: PascalHandler): HttpRouter;
  procedure HttpServe(listener: HttpListener; router: HttpRouter);

implementation
  function HttpGet(url: string): HttpResponse; external;
  function HttpPost(url: string; body: string): HttpResponse; external;
  function ToJson(resp: HttpResponse): string; external;
  
  function HttpListen(port: integer): HttpListener; external;
  function NewHttpRouter: HttpRouter; external;
  function HttpRoute(router: HttpRouter; path: string; method: string; handler: PascalHandler): HttpRouter; external;
  procedure HttpServe(listener: HttpListener; router: HttpRouter); external;
end.
