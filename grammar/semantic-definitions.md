# Definições Semânticas para BNF Pascal

Este documento fornece definições semânticas complementares para a BNF fornecida, visando eliminar ambiguidades e auxiliar na implementação de um compilador Pascal consistente. Cada seção aborda um aspecto específico que requer clareza semântica.

## 1. Tipos de Dados e Sistema de Tipos

### 1.1 Tipo String
- O tipo `string` é implementado como um array de caracteres de comprimento variável.
- Uma string possui um campo de comprimento oculto que armazena o número atual de caracteres (0 a MAX_STRING_LENGTH).
- O comprimento máximo padrão (MAX_STRING_LENGTH) é 255 caracteres.
- Strings são armazenadas com terminação nula para compatibilidade com funções de sistema.

```pascal
type
  String = record
    length: 0..MAX_STRING_LENGTH;
    data: array[1..MAX_STRING_LENGTH] of char;
  end;
```

### 1.2 Conversões de Tipos
- Conversões numéricas implícitas ocorrem apenas de tipos menores para maiores (integer → real).
- Conversões de string para numérico ou vice-versa requerem funções explícitas (StrToInt, IntToStr, etc.).
- Caracteres podem ser concatenados a strings implicitamente.

### 1.3 Compatibilidade de Tipos
- Dois tipos são considerados compatíveis para atribuição se:
  - São o mesmo tipo base.
  - Ambos são subranges do mesmo tipo base.
  - Um é subrange e o outro é seu tipo base.
  - Ambos são ponteiros para tipos compatíveis ou para o mesmo tipo.
  - São strings com qualquer tamanho máximo.

## 2. Estruturas de Controle

### 2.1 Instrução Case
- Se um valor não corresponder a nenhum caso e não houver cláusula `else`, o programa continua após o fim da instrução `case` sem executar nenhum bloco.
- Se casos sobrepostos existirem (em ranges), o primeiro caso correspondente é executado.
- A cláusula `else` é executada apenas se nenhum outro caso corresponder ao valor.

```pascal
// Comportamento definido para casos sobrepostos
case x of
  1..10: writeln('Small');  // Se x=5, apenas 'Small' é impresso
  5..15: writeln('Medium'); // Nunca executado para x=5
  else writeln('Other');    // Executado apenas se x < 1 ou x > 15
end;
```

### 2.2 Instruções If-Then-Else
- A cláusula `else` sempre se associa ao `if` mais próximo que não tem um `else`.
- Expressões booleanas são avaliadas completamente (não há avaliação de curto-circuito).

## 3. Registros Variantes

### 3.1 Alocação e Acesso
- Registros variantes alocam espaço suficiente para a maior variante.
- O campo tag é sempre inicializado antes de acessar quaisquer campos da variante.
- Acessar um campo de uma variante não ativa resulta em comportamento indefinido (erro em tempo de execução se a verificação estiver ativada).

### 3.2 Verificação de Segurança
- Em modo de verificação (opcional), o compilador gera código que verifica se o campo tag corresponde à variante sendo acessada.
- Em modo de otimização, estas verificações podem ser desativadas por motivos de desempenho.

```pascal
// Exemplo de verificação em tempo de execução
if record_variable.tag <> expected_tag then
  RuntimeError('Variante incorreta acessada');
```

## 4. Escopo e Tempo de Vida

### 4.1 Regras de Escopo
- O escopo de uma variável começa após sua declaração e termina no final do bloco em que foi declarada.
- Variáveis com o mesmo nome em blocos aninhados ocultam as variáveis de escopo mais externo.
- Parâmetros de procedimentos e funções têm escopo limitado ao corpo do procedimento ou função.

### 4.2 Declarações em Blocos Aninhados
- Declarações de variáveis em blocos anônimos criam novas variáveis distintas das de escopo superior.
- Ao sair de um bloco, todas as variáveis declaradas nesse bloco são desalocadas.

```pascal
procedure Example;
var
  x: integer; // x de escopo externo
begin
  x := 10;
  begin
    var x: integer; // Nova variável com escopo limitado a este bloco
    x := 20;        // Modifica apenas o x local
    writeln(x);     // Imprime 20
  end;
  writeln(x);       // Imprime 10 (valor do x de escopo externo não foi alterado)
end;
```

## 5. Gestão de Memória

### 5.1 Alocação de Variáveis
- Variáveis globais são alocadas em área de dados estáticos.
- Variáveis locais são alocadas na pilha.
- Variáveis dinâmicas (ponteiros) são alocadas no heap.

### 5.2 Ponteiros e Memória Dinâmica
- A operação `new(p)` aloca memória para o tipo apontado por `p` e atribui seu endereço a `p`.
- A operação `dispose(p)` libera a memória apontada por `p` e atribui `nil` a `p`.
- Acessar um ponteiro após `dispose` ou antes de `new` resulta em erro de tempo de execução.
- O valor `nil` é representado internamente como o endereço 0, que é uma área de memória inválida.

## 6. Entrada e Saída

### 6.1 Procedimentos de E/S Padrão
- `read` e `readln` leem da entrada padrão (stdin).
- `write` e `writeln` escrevem na saída padrão (stdout).
- `readln` consome todos os caracteres até o fim da linha, incluindo o caractere de nova linha.
- `writeln` acrescenta um caractere de nova linha após a saída.

### 6.2 Arquivos
- Arquivos são abertos explicitamente com `reset` (leitura) ou `rewrite` (escrita).
- Arquivos são fechados com `close`.
- O arquivo está no EOF após tentar ler além do último item.

## 7. Expressões e Avaliação

### 7.1 Ordem de Avaliação
- Operandos são avaliados da esquerda para a direita.
- Subexpressões são avaliadas de acordo com a precedência dos operadores.
- Os parâmetros de funções e procedimentos são avaliados da esquerda para a direita antes da chamada.

### 7.2 Operadores Lógicos
- Operadores lógicos (`and`, `or`, `not`) não implementam avaliação de curto-circuito.
- Todos os operandos são avaliados, mesmo que o resultado possa ser determinado pelo primeiro operando.

```pascal
// Ambas as expressões são avaliadas, mesmo que a primeira seja falsa
if (x > 0) and (ComputeValue() > 10) then
  DoSomething;
```

### 7.3. Operador `in` para Conjuntos
- O operador `in` verifica se um elemento está contido em um conjunto.
- O tipo do elemento deve ser compatível com o tipo base do conjunto.
- Conjuntos só podem conter elementos de tipos ordenados e enumerados com no máximo 256 valores.

```pascal
type
  Colors = (Red, Green, Blue, Yellow, Purple);
  ColorSet = set of Colors;
var
  PrimaryColors: ColorSet;
  c: Colors;
begin
  PrimaryColors := [Red, Green, Blue];
  // Verifica se uma cor está no conjunto de cores primárias
  if c in PrimaryColors then
    writeln('Cor primária');
end;
```

## 8. Procedimentos e Funções

### 8.1 Declarações Forward
- Declarações `forward` permitem referências recursivas mútuas entre procedimentos e funções.
- Uma declaração `forward` deve ser seguida por uma declaração completa posterior com o mesmo cabeçalho (exceto a palavra-chave `forward`).
- Os parâmetros não precisam ser nomeados novamente na declaração completa.

```pascal
procedure A(x: integer); forward;

procedure B(y: integer);
begin
  if y > 0 then
    A(y - 1);
end;

procedure A(x: integer); // Implementação da declaração forward
begin
  if x > 0 then
    B(x - 1);
end;
```

### 8.2 Passagem de Parâmetros
- Parâmetros por valor são copiados para o procedimento/função.
- Parâmetros `var` são passados por referência (o procedimento/função acessa diretamente a variável original).
- Parâmetros de procedimento/função permitem passar procedimentos ou funções como parâmetros.

### 8.3 Resultado de Funções
- Funções devem atribuir um valor à variável com o mesmo nome da função.
- Se uma função terminar sem atribuir um valor de retorno, o resultado é indefinido.

## 9. Tratamento de Erros e Limites

### 9.1 Verificação de Limites
- Arrays têm verificação de limites em tempo de execução para garantir que os índices estejam dentro dos limites declarados.
- Subranges têm verificação para garantir que os valores atribuídos estejam dentro do intervalo declarado.

### 9.2 Operações Aritméticas
- Operações que resultam em overflow levantam um erro em tempo de execução.
- Divisão por zero levanta um erro em tempo de execução.

### 9.3 Ponteiros
- Desreferenciar um ponteiro nulo (`nil`) resulta em erro em tempo de execução.
- Ponteiros não inicializados contêm valores aleatórios e não devem ser desreferenciados.

## 10. Otimizações do Compilador

### 10.1 Eliminação de Código Morto
- O compilador pode eliminar código que nunca é executado.
- Constantes são avaliadas em tempo de compilação quando possível.

### 10.2 Propagação de Constantes
- Expressões constantes são avaliadas em tempo de compilação.
- Variáveis com valores constantes podem ser substituídas por seus valores.

### 10.3 Inline de Funções
- Funções pequenas podem ser expandidas inline para melhorar o desempenho.
- A palavra-chave `packed` sugere ao compilador otimizar o uso de memória, possivelmente às custas de velocidade de acesso.

## 11. Implementação de `packed`

- Estruturas declaradas como `packed` usam o mínimo de bits necessários para representar os dados.
- Em um `packed array` ou `packed record`, os campos são armazenados de forma contígua sem preenchimento para alinhamento.
- O acesso a elementos de estruturas `packed` pode ser mais lento devido à necessidade de operações de deslocamento e máscara.

```pascal
type
  // Sem packed: Pode usar 8 bytes (com padding para alinhamento)
  RegularRecord = record
    b: boolean;  // 1 byte (possivelmente alinhado em 4 bytes)
    i: integer;  // 4 bytes
  end;

  // Com packed: Usa 5 bytes (sem padding)
  PackedRecord = packed record
    b: boolean;  // 1 byte exato
    i: integer;  // 4 bytes exatos, possivelmente com acesso mais lento
  end;
```

Estas definições semânticas complementam a BNF fornecida, fornecendo diretrizes claras para implementação de um compilador e eliminando ambiguidades que poderiam levar a comportamentos inconsistentes.

<sub>Gerado com auxílo do agente de IA claude</sub>