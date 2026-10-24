# bfx

## things to add:

### 1. Project foundation
- [x] Set up project structure and CMake
- [x] Set up GTest and CTest
- [x] Read Brainfuck source file
- [x] Handle file errors and invalid input

### 2. Frontend
- [ ] Tokenize Brainfuck instructions
- [ ] Ignore non-instruction characters
- [ ] Validate matching `[` and `]`
- [ ] Add source location information for errors (optional)

### 3. Intermediate Representation (IR)
- [ ] Define the IR instruction format
- [ ] Generate IR from tokens
- [ ] Print IR on demand (debug mode)
- [ ] Add IR validation
- [ ] Optimize IR
  - [ ] Combine consecutive identical operations
  - [ ] Combine consecutive pointer movements
  - [ ] Detect simple loop patterns (later)

### 4. Interpreter / Runtime
- [ ] Implement tape (memory cells)
- [ ] Implement data pointer
- [ ] Implement instruction execution
- [ ] Implement input (`,`) and output (`.`)
- [ ] Define tape boundary and cell overflow behavior
- [ ] Add interpreter tests

### 5. JIT compiler
- [ ] Choose code generation strategy
- [ ] Generate native machine code from IR
- [ ] Allocate executable memory safely
- [ ] Handle instruction cache requirements
- [ ] Execute generated code
- [ ] Add JIT tests
- [ ] Compare JIT output against interpreter output

### 6. CLI and polish
- [ ] Add command-line argument parsing
- [ ] Add interpreter/JIT execution modes
- [ ] Add optional IR output
- [ ] Add clear error messages
- [ ] Test with known Brainfuck programs
- [ ] Add a benchmark comparing interpreter and JIT

## installation
WIP

## usage 
WIP

## License
Copyright (C) 2026 Semino

This project is licensed under the GNU General Public License v3.0 or later (GPL-3.0-or-later). See [LICENSE](./LICENSE) for the full license text.