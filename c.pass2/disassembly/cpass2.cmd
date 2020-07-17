+ a z ll=11 S=cpass2.lbl S=../../c.pass1/disassembly/defines.lbl

* Redefine Y and U references for "C"

> Y D; U C; #D & ; #X &

" D 0212 'End of init data
'

* Program name - Adjust the end address
* The version byte follows, it needs no adjustment
A 0d-13; S &
*> U D 003f-0079; U D (+&2) 007d; U D (+&1) 0085
*> U D (+&1) 00a7-00c9; U D 00e1-00e7
*
*> #1 ^ 008d-00d2
*> #1 E 013f
A 0123-013b

> X D 2d
> U D 3f-79; U D (+&2) 7d; U D (+&1) 85; U D a7-e8
> #1 ^ 8d-d5

" L 017d '
End of cstart
Begin of part 1
p1_01.a
'
> U & 0195-06B2
> #1 ^ 0197; #1 ^ 01c7
> #X ^ 0214 - 0229
> #X & 03cd; #X & 0471
> Y D (+&1d) 068E; #1 ^ 06AA
> #X & 06D3 - 0766
*> U C 07B8 - 0924
> X N 0825; X N 0865
> #X F 086a - 087d; #X R 08f4 - 0902
> #X ^ 0940 - 094F; U & 098b-09CF
> #D R 0A4A-0A59; #X F 0a92-0ab7; #X F 0c58-0c62
> #X R 0CE0-0ce7; X R 0cf6 - 0CFB; #X R 0E5E - 0EED

A 0b04/9; B; A - 0b1d; B/2; A -0b33; B/2; A -0b43; B
A; B; A -0b53; B/3; A -0b69; B /2; A -0b8e; B/2
A -0ba3; B/2; A; B; A -0bb4; B /2; A -0bc0; B/2

" L 0bc3 '
Begin of part 2
p2_02.a
'

> X C 0f09 - 0f0d; #D F 0f13
> #X R 0F2E - 0F38; #D R 0f45-0F4F; X C 0f4d
> #X R 0f67-0f6c; X C 0f8e; X C 0fa1; X C 101D
> #D R 1043; #D R 107B; X C 1079 - 1085
> #D F 108F; #D R 10E1 - 10f7; X C 10F5 - 1110
> #D R 1114 - 111a
> #X R 1167 - 11AD; #X R 11D7 -11E5; #X R 11F3; #X R 1201; X C 121a
> U & 122e; #U & 1243
> X C 137B; #D R 1387; #D F 13aa-13b2; #X R 13E7-13EC; #D F 137F
> X C 1403-1418; #D R 1421; X C 143b
> X C 1456; #X R 1469-1493; X C 14AE-14BD; #D R 14BF
> #X R 14CC-14D1; X C 14E4; #D F 14E7-14ED
> X C 1502; #D R 1504; #X R 1511-1522
> X C 1573-15AD; #X R 15f1-15f6; #D F 1608; X C 1637; #D F 164B
> X C 16B6-16DD; #D F 16EF; #X R 170A-1714; X C 1731-1749
> #D R 1733-1751; #D R 1771-1777; X C 1798-179E; #X R 17CA-17E4
> #D F 1807; #X R 183F-184B; #D R 189E-18A2; #X R 18BE-18DA
> X C 18FF; #D R 1912-1929; X C 196C-1985; #X R 19AF
> X C 19FC; X C 1A08-1A35; #D R 1A3A
> #X R 1A53-1A5A; #X R 1A7D; #X R 1A8B

> X C 1AA6-1AB1; #X R 1AEC-1AF1; #D R 1b06; X C 1b2d; #D R 1b49-1b5b
> #X R 1b70-1b75; #D R 1BA7; #D R 1bb1; X C 1bc5; #X R 1bc9-1bce
> X C 1bdb; X C 1C29-1C38; #D R 1c83-1ca9; X C 1c8b-1cbc; #D R 1cd3-1cd9
> #D R 1cfb; X C 1d06-1d25; #D R 1d47-1d51; X C 1d4f; #D R 1dd9-1df0
> X C 1dd7-1de1; #D R 1e2a; X C 1e3e; #X R 1e4f-1EA0; X C 1EAD

A 1ed4 - 1ede; B; A/2; B/2; A - 1eed; B; A -1ef9; B
A -1f05; B; A -1f11; B

" L 1f13 '
Begin of part 3
p2_03.a
'

> #D F 1FEE; #D F 200e-2016; #D R 2055-205E
> #X R 206f-20df
> X C 20F9-20FF; #D F 2125-213E; X C 217e-219e; #X R 21fd
> #X R 2207-220E; #D R 222a
> X C 2247; X C 2281; X C 22D4; #X R 22E8-22F4; #D R 2308
> X C 233d-2373; #D R 233F; #X R 2388-23F7
> #D R 2419; #X R 244D-245B; #D R 2472-247E; #X R 2490-2495
> #X R 24BC-24db; #D R 24F2; #D R 2580; #D R 25ae; #D R 25CD
> X C 2680; #D R 2682-269C; X C 269A-26ff; #D F 26BE; #D R 26d6
> #D F 26dd; #D R 26e5-2701; X C 27B6; #D R 27E4
> #X R 281B-28ED; X C 2905; #X R 2938; #D R 296D; #D R 2994
> #D R 29ae; #D R 2b2c-2b31; X C 2BB5; #D R 2BCD; X C 2BFB
> #D R 2C0C; #D R 2C44; #X R 2C7B-2D2A

A 29F6-29FA; B;

" L 29fc '
Begin of part 4
p2_04.c
'
> #X ^ 2ee6-2efb

A 2d38-2d3d; B


" L 2d3f '
Begin of part 5 (printf)
printf.a
'

> #1 ^ 2DA8-2DB8; #1 ^ 2DCD-2DD6; #1 ^ 2E09; #D ^ 2f32; #D ^ 2FA1
> #D ^ 2FBA; U & 2FC1; #D ^ (-&0a) 2FE6; #D ^ 2FEB;
> U & 300e; U & 3004e; U & 304E-307f
A 3108-310d; B

" L 310f '
Begin of part 6
p2_06.a
'

> #D R 32ff; #D R 3318
> X C 3418-3423; #D R 341a; #D ^ 3486; X C 34f0
> X C 3516; #X R 3564-3579; #X R 3587-3595
> #X R 35AA-35B8; #X R 35D4-35E2
> #X R 35FE-3605; #X R 3670-3677; #D F 3686; #D R 3696-369c
> #X R 3748-374f; #X R 375b-3760; #D R 3770
> #D R 3700; #D R 370a; #D R 3723; #D R 3737; #D R 3794
> #D R 37C3-37C9
> #D R 3819; #D ^ 384c; #D F 3858; X C 3860; #X F 388b-3897
> #D ^ 3906; #X R 3931; #X R 395b-3969
> #D ^ 398d-39a1; #X R 39b0-39b5
> #X R 3B0E-3BB6; #U F 3bec-3C6A; #D ^ 3BF2-3BF7
> #X R 3cd5; #X R 3cf1-3d84; #D ^ 3e12-3e33
> #D F 3EB9-3EBF; X C 3ECA-3ED0; #X R 3EEC-3EF6; #U R 3F04
> #D ^ 3F39; #D R 3f5b; #U R 3F79-3F8D; #D R 3FB1
> #D ^ 3FB6; #U R 3FD6-3FEC; #D R 4011; #D ^4016
> #X R 405b; #X R 4077; #D ^ 4090-40db; #D ^ 40f8; #D ^ 4125; X C 4167
> #D ^ 418A-41BA; #D F 41EE-4202; #X F 4232-425C; #D ^ 427C-4298
> #X R 42E9; #X R 42F7; #D ^ 4325; #X R 4381-43ae
> #D ^ 43BE; #D ^ 4421; #D ^ 447F; #D ^ 44B3

W 4926-4929; W 49a6-49a9

> #X R 4AB0 - 4ABA

A 44c9/2; B; A/2; B
2 A/5; B
A /4; B
A -44f2; B; A -44fb; B/2; A/2; B; A -4509; B/2
2 A/6; B
4 A/5; B
A /6; B; A/5; B; A /4; B; A /5; B; A -4551; B; A/4; B
3 A/5; B
A /2; B /2; A /4; B; A /3; B; A/2; B
*A 44c9-4822; A 04b2e-4b87
* at "aslb"
3 A/4; B; A /5; B
2 A/4; B
2 A/5; B
B; A /4; B/2; A/3; B
2 A/7; B
A/5; B/2; A/4; B; A/5; B; A/2; B
*  at st%c -2,s
A -45ea; B/2; A /3; B; A /2; B
3 A/3; B
A -4609; B /2; A /2; B; A -4615; B; A -4620; B /2
A -4629; B
3 A/8; B
A -464b; B
6 A/5; B
A /4; B
3 A /5; B
A /6; B; A /5; B; A /7; B
2 A /6; B
2 A /5; B
A -46c4; B; A -46cc; B; A -46d6; B /2
2 A /6; B
4 A /5; B
A /6; B
12 A /5; B
A -475c; B; A /4; B; A -4768; B; A /2; B; A /3; B; A /2; B
A /3; B
3 A/4; B
2 A /8; B
B; A -47a9; B; A /6; B; A /4; B; A -47c3; B; A /2; B
A -47d2; B; A -47d9; B
10 A /3; B
A /2; B; A /4; B; A /5; B; A /7; B; A -4820; B/2

" L 4823 '
Begin of part 7
p2_07.a
'
> #D ^ 4a14

A 4b2e - 4b3a; B; A -4b4c; B; A /4; B; A -4b5b; B; A -4b6a; B /2
A; B; A /23; B /2

" L 4b88 '
Begin of part 8
p2_08.a
'

> #X R 4EDC; #X R 4EE8
*A 4d06-4daf
A 4d06/4; B; A -4d13; B /2; A /6; B; A -4d25; B; A -4d35; B /2
A /5; B; A /4; B; A /7; B; A /6; B; A /4; B; A -4d5d; B
A -4d69; B; A -4d73; B /2; A -4d7f; B/3; A -4d8a; B; A /5; B
A -4d98; B; A -4d9f; B; A; B; A -4daa; B /2; A; B/2

" L 4db0 '
End split
Begin of Library routines
'

> U & 4DB6 - 5D8A
L & 5033/4; W 50c8 /4; W 5104/4
" L 5559 'End of setbase routine'
W 5c77/8
> Y D (+&2) 5CBB; Y D (+&4) 5CC1; Y D (+&2) 5D99; Y D (+&2) 5DAE
> Y & 5E2A - 5E2E
> Y D (+&2) 6176
' L 6235 Init DP data size
L & 6235; S &; L D

' L 623a Init Non-DP size
L & 623a
" L 623C 'Following 14 words go to D0027'
W /28

' L 6258 .        to D0043
L & -625f

' L 6260 .        to D004b
L $ 6260

' L 6262 .        to D004d
L L 6262

' L 6264 .        to D004f
L L

' L 6266 .        to D0051
L L

' L 6268 .        to D0053
L L

' L 626a .        to D0055
L L

' L 626c to D0057
L L

" L 626e 'atoftbl (from scale.c)'
B /104

" L 62d6 '_iob's (16) for stdin, stdout, stderr, etc'
16 W /10; B; W

' L 63a6  .    To D0191
B

' L 63a7 .    to D0192
S & /128

' L 6427 Data-text references
L & 6427;L D /12

' L 6435 Data-data references
L & 6435; L D 6437
A 6439-643f; B


* Initialized data
' D 0 .    = 0
' D 1 .    = 0
' D 2 .    = 75
" D 27 '
Begin of non-DP data
'
