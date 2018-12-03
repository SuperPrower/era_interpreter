## ERA Interpreter Test Binaries

### v0Test.bin - test for v0 file loading. 16 byte long file:
00 00 00 00 00 02 ff f2 ff f4 ad dc 56 69 f7 b1
Version (0), Padding(0), 4 bytes Length(2) static data(fff2fff4) code(ad dc 56 69 f7 b1)

### v0_simple_ops.bin - tests of mathematical operators

```
00 00 # v0 heading + padding
00 00 00 00 # 0 bytes of static data

C8 A0 # LDC 5 0
C8 41 # LDC 2 1

14 20 # ADD_8 1 0

```
