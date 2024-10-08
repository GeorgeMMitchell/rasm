
RASM -- RISC-V Assembler

RASM is a customizable assembler targeting the RISC-V architecture with the
goal of providing the same extendability seen in the RISC-V ISA specification.
RASM does not specifically target CPUs that implement RISC-V; instead, RASM
supports specific RISC-V bases and extensions and expects the end-user to
enable the extensions one wishes to utilize for particular hardware.


RASM is still in early development. This is a personal project that I would
like to see grow into a useful tool some day. For now, it is a tool I'm using
to better understand software development practices.

Building RASM requires CMake 3.11+. Support for more build systems is planned.
No dependencies are currently required other than a compiler supporting C90.
