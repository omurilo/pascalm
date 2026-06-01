program test_features;
type
  colors = (red, green, blue);
  id_record = record
    id: integer;
    case kind: boolean of
      true: (name: string);
      false: (code: integer);
  end;
var
  i: integer;
  s: set of 1..10;
  r: id_record;
  c: char;
begin
  i := $FF; { Hex literal }
  c := #65; { Char code 'A' }
  s := [1..5, 8]; { Set range }
  
  if 3 in s then
    writeln('3 is in set');
    
  case i of
    0..100: writeln('small');
    255: writeln('large ($FF)');
  end;
  
  r.id := 1;
  r.kind := true;
  r.name := 'variant';
  writeln(r.name);
end.
