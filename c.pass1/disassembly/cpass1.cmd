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

> #X & 0c93-0d3e; #X & 0c71-0c7b

A 0e97-0f17

" L 0f18 '
Begin of part 3
'

A 2675-27cf

" L 27d0 '
Begin of part 4
'

A 316a-3226

" L 3227 '
Begin of part 5
'
> U & 3976-39E3; #X & 3996-39a7; #X & 39cc-39d8

" L 4432 '
Begin of part 6
'

A 49be-4a1f

" L 4a20 '
Begin of part 7
'

> #D ^ 4a3a; #D ^ 4a50; #D ^ 4a80; #D ^ 4ac9;#D ^ 4acc;#D ^ 4b09
> #D ^ 4b42;#D ^ 4b6d
> #D ^ 4b7d-4b8d; #D ^ 4ba9-4bae; #X ^ 4bc5-4be5; #D ^ 4bf4
> #D ^ 4c74

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

> #D ^ 66F3-6703; #D ^ 6745; #D ^ 679E; #D ^ 67D8
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
L & /20; A /8

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

