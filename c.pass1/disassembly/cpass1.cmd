+ z S=defines.lbl S=cpass1.lbl
* Redefine Y and U references for "C"

> Y D; U &; #D &

A 0d-13;S &
A 0123-013b

> X D 2d
> U D 3f-79; U D (+&2) 7d; U D (+&1) 85; U D a7-e8
> #1 ^ 89-d5

* End of cstart

" D 03 'End DPInit - Begin NonDp Init'
" D 76 ' Begin of non-dp data'
" D 284 ' End of Non-DP Init Data'
" D 53 'Defined in stats.c'

* Define ALL chcode values for D005f here

> #D R 03de; #D R 042A; #D R 0440; #D R 0508-0510; #D R 078E
> #X R 07FC-0857; #D R 093E; #X R 098F-09A4; #D R 09AF
> #X R 09E4-09E9; #D R 0A05; #D R 0A40; #D R 0A6F; #D R 0AA7
> #D R 0AB1; #D R 0ACC-0AE6; #X R 0AF4-0B16
> #D R 1031-1045; #D R 105A; #X R 1095-10AF
> #D R 1118; #X R 1133-113A; #D R 1152-116F; #D R 11A5-11B3; #D R 1200
> #D R 1261-126B; #X R 1224-124E; #X R 12ca-12CF; #X R 1308-1316
> #D R 27DA; #D R 28C0
> #X R 28E7-28F3; #X R 2901; #D R 290B; #D R 293B; #D R 298A; #D R 299D
> #D R 2A1E; #D R 2CFE; #D R 2DBC; #D R 2EA0; #D R 2FAB; #D R 3244-324C
> #D R 32FE-3306; #D R 339B; #D R 34B6; #D R 35FD-3614; #D R 3754
> #D R 3789; #D R 385A; #D R 3926; #D R 3B17; #D R 3B6E-3B78
> #D R 3BD2-3BDA; #D R 3C00; #D R 3C50; #D R 3C6B; #D R 3C8E
> #D R 3CE3; #D R 3D20; #D R 3D5F; #D R 3D8D; #D R 3DB5; #D R 3EC6-3EDA
> #D R 3F53; #D R 3FAD-3FB5; #D R 3FC7; #D R 4001; #D R 4069
> #D R 409F; #D R 44CC; #D R 458F; #D R 460B-4616; #D R 4669-4674
> #D R 46DF-46EC; #X R 49A7-49AC; #D R 55A0-55B2; #D R 55BF
> #D R 5635-5659; #D R 5698; #D R 56A5; #D R 56C5; #D R 56D7
> #D R 56E4; #D R 5709; #D R 573A; #D R 574F; #D R 575A; #D R 5779
> #D R 578E; #D R 5799; #D R 57B8; #D R 57C2; #D R 57E0; #D R 57EA
> #D R 57F4; #X R 5816-586a

* end D005f defines

" L 017d '
Begin of part 1
'

> #X & 044a-046d
A 0520-57f

" L 0580 '
Begin of part 2
'

*> #X ^ 07fc-0858; #X ^ 098f-09a5
*> #X ^ 0af4-0b17
*> #X ^ 0c9a-0d3c
*> #X ^ 0803-0850
*> #x ^ 0c71-0d3b
*> #X ^ 0e7c-0e8b

> X C 0a1b-0A22; U C 0a6d-0a75
> #X R 0c93-0d3e; #X & 0c71-0c7b
> U C 0de1-0E62

A 0e97-0f17

" L 0f18 '
Begin of part 3
'

> U W 0f2a-0FE3; X W 0F73-0FE7
> U W 101a-1272
> X W 10D2-10EF; X W 1114-112C
> #X R 133a-1362; #X R 1E49-1F61

* L2027()
* Set U to be LBLDEF ptr for entire L2027() function
> U W 2027-2339
* These are the 'case' values in L2027()
> #X F 2072-2088; #X F 2137-214A; #X F 2174-218B
> #X F 220b-2225; #X F 2253-226d; #X F 22d6-22f9
> #X R 2475-2483

> #X F 263E-2651

A 2675-27cf

" L 27d0 '
Begin of part 4
'

> #X F 2B16-2B27

A 316a-3226

" L 3227 '
Begin of part 5
'
> U W 331a-3482
> #X F 3406-3417
> U W 35AB-35B9; #X F 35E5-35EF
> U W 36c4-383D; #X F 3776-3780
> U W 3976-39E3; #X & 3996-39a7; #X & 39cc-39d8
> U W 3aa2-3aca; X W 3aa0-3aad
> U W 3b80-3BC3; X W 3BB9
> U W 4212-42B4

A 42f4-4431

" L 4432 '
Begin of part 6
'

> U C 479F-48E0

A 49be-4a1f

" L 4a20 '
Begin of part 7
'

> #D ^ 4a3a; #D ^ 4a50; #D ^ 4a80; #D ^ 4ac9;#D ^ 4acc;#D ^ 4b09
> #D ^ 4b42;#D ^ 4b6d
> #D ^ 4b7d-4b8d; #D ^ 4ba9-4bae; #X ^ 4bc5-4be5; #D ^ 4bf4
> #D ^ 4c74
> U C 4E4D-4FD2; #D R 4EE6; #D R 4F51

*???following correct???
> #X R 4d7e-4de7

> #D ^ 4e55-4e6c; #D ^ 4f10; #D ^ 5026; #D ^ 5047; #D ^ 5070
W 4f5f /4; W 4f9b /8
A 50be-50cd

" L 50ce '
Begin of printf
This seems to be a substitute "printf" routine
'

> #1 ^ 5137-51C7; #X ^ 5273-5288
> #D ^ 5373-5378
" L 549c 'Comes from atof library'

A 5495-549b

" L 549c '
Begin of part 8
'

> #X F 563d-5647; #X F 5C7D
*> #X F 5873-5888
> #1 ^ 5cb4-5cbc; #1 ^ 5d4a-5D50; #1 ^ 5DA5-5DBB; #1 ^ 5DFB-5E1C
> #1 ^ 5eac-5eb2; #1 ^ 5f07-5f1c; #D ^ 6012-601c

* These are switch cases..  Perhaps they aren't ascii

> #D ^ 5f84; #1 & 5fd0-5fed
> #X ^ 6091-60b6; # U ^ 60bb
> #D ^ 60db; #U ^ 6117; #1 ^ 61AD-61B3; #D ^ 61d4; #1 ^ 61dc

A 61e9-6331

" L 6332 '
Begin of part 9
'

> #1 ^ 63a7

A 6631-66b5

" L 66b6 '
Begin of part 10
'

> #D ^ 66F3-6703; #D W 6729; #D ^ 6745; #D ^ 679E; #D ^ 67D8
> #D ^ 6817-6823
> Y D (+&2) 6867

A 691a-6958
" L 6959 '
Begin of part 11 ( contains main())
'

" L 6a70 '
main() - Entry point for the program
'

> #X ^ 6b37-6B54; #1 ^ 6ae4
A 6c15-6c96

W 5c69-5c70; W 5cab-5cae

* ------------------------

" L 6c97 '
Begin of Library routines
'

> Y D (+&2) 746D
> Y D (+&2) 7482
> Y D (+&2) 7826

A 6eb4/3

>Y & 74de

" L 794c '
End of Program code - Begin of data
'

' L 794C Init DP data size
' L 7951 Init Non-DP data size

L & 794c; B ; L D;L &

'L 7953 .   to D0076 (dpsiz)
A /11

' L 795e . to D0081
L & /8

' L 7966 . to D0089
B /128

' L 79e6 . to D0109
B /128

' L 7a66 . to D0189
L D (+ $ ff)

' L 7a68 . to D018b
S & /28

' L 7a84 . to D01a7
L D ( + & 14)

' L 7a86 . to D01a9

' L 7a90 . to D01a9
A /11

" L 7a91 '_iob's (16) for stdin, stdout, stderr, etc'
16 W /10; B; W

* --------------- End of init data
' L 7b61 Data-text ref count
'L 7b63 Data-Data ref count
L & 7b61; L& 7b63; L D /6; A -7b72

