: abs
    dup 0 < if
        -1 *
    else endif
;

: powernn
    dup 0 > if
        swap -1 * swap
        over -1 * swap 1 -

        begin
            dup 0 >
        while
            over swap 1 -
        repeat

        drop

        begin
            over 0 >
        while
            *
        repeat

        swap drop
    else
        drop drop 1
    endif
;

: powerzn
    over 0 < if
        over abs over
        dup 2 mod 0 = if
            powernn
        else
            powernn -1 *
        endif
        swap drop swap drop
    else
        powernn
    endif
;

(*
( TEST : abs )

-5 .s
abs .s
drop

( TEST : powernn )

2 3 .s
powernn .s
drop

3 3 .s
powernn .s
drop

10 3 .s
powernn .s
drop

12 0 .s
powernn .s
drop

( TEST : powerzn )

-3 3 .s
powerzn .s
drop*)