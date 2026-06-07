unit Collections;

interface

{ Handle-based containers. Each `*New` returns an opaque integer handle that
  must eventually be released with the matching `*Free`. Values are integers,
  which is enough to also carry booleans, enum ordinals or other handles. }

{ Dynamic list (0-based indexing). }
function ListNew: integer;
procedure ListPush(list: integer; value: integer);
function ListGet(list: integer; index: integer): integer;
procedure ListSet(list: integer; index: integer; value: integer);
function ListLen(list: integer): integer;
function ListPop(list: integer): integer;
procedure ListFree(list: integer);

{ Hash map from string keys to integer values. }
function MapNew: integer;
procedure MapPut(map: integer; key: string; value: integer);
function MapGet(map: integer; key: string): integer;
function MapHas(map: integer; key: string): boolean;
procedure MapDelete(map: integer; key: string);
function MapLen(map: integer): integer;
procedure MapFree(map: integer);

implementation

function ListNew: integer; external name 'coll_list_new';

procedure ListPush(list: integer; value: integer); external name 'coll_list_push';

function ListGet(list: integer; index: integer): integer; external name 'coll_list_get';

procedure ListSet(list: integer; index: integer; value: integer); external name 'coll_list_set';

function ListLen(list: integer): integer; external name 'coll_list_len';

function ListPop(list: integer): integer; external name 'coll_list_pop';

procedure ListFree(list: integer); external name 'coll_list_free';

function MapNew: integer; external name 'coll_map_new';

procedure MapPut(map: integer; key: string; value: integer); external name 'coll_map_put';

function MapGet(map: integer; key: string): integer; external name 'coll_map_get';

function MapHas(map: integer; key: string): boolean; external name 'coll_map_has';

procedure MapDelete(map: integer; key: string); external name 'coll_map_delete';

function MapLen(map: integer): integer; external name 'coll_map_len';

procedure MapFree(map: integer); external name 'coll_map_free';

end.
