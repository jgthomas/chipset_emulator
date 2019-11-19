# Emulator for 4-bit and 8-bit chips [![Build Status](https://travis-ci.com/jgthomas/chipset_emulator.svg?branch=master)](https://travis-ci.com/jgthomas/chipset_emulator)

## Features

* **Interactive shell**

> Enter a program in machine code directly into the emulator.

* **Run program from a file**

> Run a machine code program from a file.

* **Simple debugger**

> Debug mode available with the contents of memory and registers displayed at each step in execution.

* **Custom assembly langauge**

> Set of mnemonic symbols to simplify writing programs for the system.

* **Simple assembler**

> Converts a program written in the system's assembly language into machine code.

## Details

![chipset_emulator](images/instructions.png)

![chipset_emulator](images/memory.png)

## Assembly language ➔ instruction code

* HALT ➔ 00

* ADD ➔ 01

* SUB ➔ 02

* INC0 ➔ 03

* INC1 ➔ 04

* DEC0 ➔ 05

* DEC1 ➔ 06

* SWP ➔ 07

* PRNT ➔ 08

* LD0 ➔ 09

* LD1 ➔ 0A

* ST0 ➔ 0B

* ST1 ➔ 0C

* JMP ➔ 0D

* JMPZ ➔ 0E

* JMPNZ ➔ 0F

* ASCCHAR ➔ 10
