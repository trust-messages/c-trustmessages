# Trust messages in C

## Introduction

TODO

## Profiling

1. Compile: `make -j`
2. Run the program, e.g. `./time_decode a.ber`
3. Optionally, rename the gmon.out to something more descriptive, like a.ber.out
4. Run the gprof2dot: `gprof ../c-trustmessages/time_decode ../c-trustmessages/a.ber.out | gprof2dot | dot -Tpdf -o a.ber.pdf`

