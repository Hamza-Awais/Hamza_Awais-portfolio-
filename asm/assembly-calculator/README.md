# Calculator

| **Course** | Computer Organization and Assembly Language (COAL) |
| **Language** | x86 Assembly (MASM, 8086, DOS) |
| **Type** | Console application |

A menu-driven calculator written entirely in 8086 assembly for DOS. It adds, subtracts, multiplies and divides signed whole numbers typed at the keyboard, validates the input, detects results that do not fit in 16 bits, and guards division by zero. Everything lives in a single `.asm` file with no libraries.

## Features
- **Menu driven:** a clear-screen menu offers Add, Subtract, Multiply, Divide and Exit, and repeats after every calculation
- **Signed multi-digit input:** numbers are typed normally (with an optional `+` or `-` sign) and parsed digit by digit into a 16-bit value
- **Input validation:** anything that is not a number is rejected with a message and re-asked, so the program never crashes on bad typing
- **Overflow detection:** results too large for a signed 16-bit word are reported instead of wrapping around silently
- **Safe division:** dividing by zero is caught before `idiv` runs, and the answer is shown as quotient plus remainder
- **Signed output:** negative results are printed with a minus sign using repeated division by 10

## How it works
- **`readNumber`** reads a line with `INT 21h` service `0Ah`, strips an optional sign, then builds the value with `acc = acc * 10 + digit` using `mul`, rejecting any non-digit.
- **`printNumber`** prints the sign if the value is negative, negates it, then pushes the remainders of repeated `div 10` on the stack and pops them back as ASCII digits.
- **Main loop:** clear the screen with `INT 10h` service `06h`, draw the menu, read one key, branch to the operation, read the two operands, compute with `add` / `sub` / `imul` / `idiv`, print the result and wait for a key before repeating.
- **Overflow checks:** `add` and `sub` are followed by `jo`; for `imul` the high word in `DX` is compared against the sign extension of `AX` to confirm the product still fits in 16 bits.

## Files
- `calculator.asm`: the complete calculator source (MASM / 8086 / DOS)
- `Calculator_Documentation.docx`: full project documentation

