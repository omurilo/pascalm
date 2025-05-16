package main

import (
    "bufio"
    "fmt"
    "math"
    "os"
    "strconv"
    "strings"
)

type InstrKind int

const (
    IBinOp InstrKind = iota
    IUnOp
    IAssign      // x = y      or  x = "some literal..."
    IIfFalse     // ifFalse x goto L
    IGoto        // goto L
    IRead        // read x
    IPrint       // print x
)

type Instruction struct {
    Kind     InstrKind
    Result   string   // destination variable
    Op1      string   // first operand or literal text
    Operator string   // "+", "-", "*", "/", "&&", "||", "==", "!=", "<", "<=", ">", ">=", "^", or "!"
    Op2      string   // second operand (for binary ops)
    Label    string   // label name (for jumps)
}

// parseCode does a two-pass parse:
// 1) record labels → map[label]index
// 2) build []Instruction
func parseCode(lines []string) ([]Instruction, map[string]int) {
    labels := make(map[string]int)
    instrCount := 0
    // pass 1: note label positions
    for _, line := range lines {
        fld := strings.Fields(line)
        if len(fld) == 0 {
            continue
        }
        if strings.HasSuffix(fld[0], ":") {
            lbl := strings.TrimSuffix(fld[0], ":")
            labels[lbl] = instrCount
        } else {
            instrCount++
        }
    }

    // pass 2: build instructions
    instrs := make([]Instruction, 0, instrCount)
    for _, line := range lines {
        fld := strings.Fields(line)
        if len(fld) == 0 || strings.HasSuffix(fld[0], ":") {
            continue
        }
        inst := Instruction{}
        switch fld[0] {
        case "goto":
            inst.Kind = IGoto
            inst.Label = fld[1]
        case "ifFalse":
            inst.Kind = IIfFalse
            inst.Op1 = fld[1]
            inst.Label = fld[3]
        case "read":
            inst.Kind = IRead
            inst.Result = fld[1]
        case "print":
            inst.Kind = IPrint
            inst.Op1 = fld[1]
        default:
            dest := fld[0]
            rhs := fld[2:]
            if len(rhs) == 3 && isOperator(rhs[1]) {
                // x = y op z
                inst.Kind = IBinOp
                inst.Result, inst.Op1, inst.Operator, inst.Op2 = dest, rhs[0], rhs[1], rhs[2]
            } else if len(rhs) == 2 && isOperator(rhs[0]) {
                // x = op y
                inst.Kind = IUnOp
                inst.Result, inst.Operator, inst.Op1 = dest, rhs[0], rhs[1]
            } else {
                // x = y  (copy) or literal
                inst.Kind = IAssign
                inst.Result = dest
                inst.Op1 = strings.Join(rhs, " ")
            }
        }
        instrs = append(instrs, inst)
    }
    return instrs, labels
}

func isOperator(op string) bool {
    switch op {
    case "+", "-", "*", "/", "&&", "||", "==", "!=", "<", "<=", ">", ">=", "^", "!":
        return true
    }
    return false
}

// getVal tries to parse a float, or fetch a variable's value.
// Returns (value, true) if numeric or known var; (0,false) otherwise.
func getVal(sym map[string]interface{}, name string) (float64, bool) {
    if v, err := strconv.ParseFloat(name, 64); err == nil {
        return v, true
    }
    if val, ok := sym[name]; ok {
        switch x := val.(type) {
        case float64:
            return x, true
        }
    }
    return 0, false
}

func main() {
    if len(os.Args) < 2 {
        fmt.Fprintf(os.Stderr, "Usage: %s <program.tac>\n", os.Args[0])
        os.Exit(1)
    }

    data, err := os.ReadFile(os.Args[1])
    if err != nil {
        panic(err)
    }
    lines := strings.Split(string(data), "\n")
    instrs, labels := parseCode(lines)

    sym := make(map[string]interface{})
    reader := bufio.NewReader(os.Stdin)
    pc := 0
    for pc < len(instrs) {
        inst := instrs[pc]
        switch inst.Kind {

        case IGoto:
            pc = labels[inst.Label]
            continue

        case IIfFalse:
            if v, ok := getVal(sym, inst.Op1); !ok || v == 0 {
                pc = labels[inst.Label]
                continue
            }

        case IRead:
            fmt.Printf("Enter %s: ", inst.Result)
            line, _ := reader.ReadString('\n')
            line = strings.TrimSpace(line)
            if num, err := strconv.ParseFloat(line, 64); err == nil {
                sym[inst.Result] = num
            } else {
                sym[inst.Result] = line
            }

        case IPrint:
            if v, ok := sym[inst.Op1]; ok {
                switch x := v.(type) {
                case float64:
                    fmt.Println(x)
                case string:
                    fmt.Println(x)
                default:
                    fmt.Printf("%v\n", x)
                }
            } else {
                // unknown var → print literal
                fmt.Println(inst.Op1)
            }

        case IAssign:
            // copy or literal
            if num, ok := strconv.ParseFloat(inst.Op1, 64); ok == nil {
                sym[inst.Result] = num
            } else if v, exists := sym[inst.Op1]; exists {
                sym[inst.Result] = v
            } else {
                sym[inst.Result] = inst.Op1
            }

        case IUnOp:
            if v, ok := getVal(sym, inst.Op1); ok {
                switch inst.Operator {
                case "-":
                    sym[inst.Result] = -v
                case "!":
                    if v == 0 {
                        sym[inst.Result] = float64(1)
                    } else {
                        sym[inst.Result] = float64(0)
                    }
                }
            }

        case IBinOp:
            a, _ := getVal(sym, inst.Op1)
            b, _ := getVal(sym, inst.Op2)
            var r float64
            switch inst.Operator {
            case "+": r = a + b
            case "-": r = a - b
            case "*": r = a * b
            case "/":
                if b != 0 {
                    r = a / b
                } else {
                    r = math.Inf(1)
                }
            case "^": r = math.Pow(a, b)
            case "&&":
                if a != 0 && b != 0 {
                    r = 1
                }
            case "||":
                if a != 0 || b != 0 {
                    r = 1
                }
            case "==":
                if a == b {
                    r = 1
                }
            case "!=":
                if a != b {
                    r = 1
                }
            case "<":
                if a < b {
                    r = 1
                }
            case "<=":
                if a <= b {
                    r = 1
                }
            case ">":
                if a > b {
                    r = 1
                }
            case ">=":
                if a >= b {
                    r = 1
                }
            }
            sym[inst.Result] = r
        }

        pc++
    }

    fmt.Println("Final state:", sym)
}

