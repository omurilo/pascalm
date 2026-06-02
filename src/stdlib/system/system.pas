unit System;
interface

  { Math Intrinsics }
  function Sqrt(n: real): real;
  
  { Execution Control }
  procedure Halt(code: integer);
  procedure RuntimeInit;

  { Memory Management }
  function AllocMem(size: integer): integer;
  procedure FreeMem(ptr: integer; size: integer);

implementation

  { The compiler links these natively to the Rust implementation }
  function Sqrt(n: real): real; external name 'pascal_sqrt';
  procedure Halt(code: integer); external name 'pascal_halt';
  procedure RuntimeInit; external name 'pascal_runtime_init';

  function AllocMem(size: integer): integer; external name 'sys_alloc_mem';
  procedure FreeMem(ptr: integer; size: integer); external name 'sys_free_mem';

end.
