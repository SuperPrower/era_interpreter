## ERA Interpreter Test Binaries

### v0Test.bin - test for v0 file loading. 16 bytes long file:
00 00 00 00 00 02 ff f2 ff f4 ad dc 56 69 f7 b1
1 byte Version (00), 1 byte Padding(00), 4 bytes Data length(00000002),
4 bytes Static data(fff2fff4), 6 bytes Code(ad dc 56 69 f7 b1)

### v1Test.bin - test for v1 file loading. 36 bytes long file:
01 00 00 00 00 20 00 00 00 02 00 00 00 18 00 00 00 03 13 37 10 01 de ad ad dc 56 69 f7 b1 00 00 ff f2 ff f4
1 byte Version(01), 1 byte Padding(00), 4 bytes Data start(00000020), 4 bytes Data length(00000002),
4 bytes Code start(00000018), 4 bytes Code length(00000003), 6 bytes Ignored junk(13371001dead),
6 bytes Code(addc5669f7b1), 2 bytes Ignored junk(00), 4 bytes Static data(fff2fff4)

### v0_simple_ops.bin - tests of mathematical operators

```
00 00 # v0 heading + padding
00 00 00 00 # 0 bytes of static data

C8 A0 # LDC 5 0
C8 41 # LDC 2 1

14 20 # ADD_8 1 0

CC 1D # ST 0 SP

```
