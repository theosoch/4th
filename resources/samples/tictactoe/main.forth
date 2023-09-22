include ./math.forth

( 1 000 000 000 )
-10
1000000000

( ------ )

: printcasechar
    dup 10 mod 0 = if ." &n "
    else
        dup 10 mod 1 = if ." &b&nO"
        else
            dup 10 mod 2 = if ." &c&nX"
            else
                ." &6&n■"
            endif
        endif
    endif
;

( ------ )

: showgrid
    swap
        dup

        ."    (&na&r;&nb&r;&nc&r)" cr
        0
        begin
            dup 3 <
        while
            dup ." (" 1 + char 0 + emit ." )"
            swap
                0
                begin
                    dup 3 <
                while
                    swap
                        ." &8|"
                        printcasechar
                        10 /
                    swap
                    1 +
                repeat
                drop
                ." &8|" cr
            swap
            1 +
        repeat
        drop

        drop
    swap
;

( ------ )

: playask
    over swap

    swap
    over
    
    ." &8&l╔╾&r " ." &9Play&r "    ." &8&l->&r " ." &e`1a`&r to &e`3c`&r" cr
    ." &8&l╠╾&r " ." &9Restart&r " ." &8&l->&r " ." &e`r`&r" cr
    ." &8&l╚╾&r " ." &9Quit&r "    ." &8&l->&r " ." &e`q`&r" cr
    ." &lEnter your choice : &r"
    key
    dup 10 = if
        drop drop
    else
        dup char r = if
            key drop
            drop drop drop -2
        else
            dup char q = if
                key drop
                drop drop drop -1
            else
                char 0 - 1 -
                key char a -
                key drop

                10 swap powerzn
                swap 1000 swap powerzn
                *
                
                swap 1 + * +

                swap 1 + 2 mod
            endif
        endif
    endif
;

( ------ )

: main
    0

    begin
        dup 1 +
    while
        cr
        showgrid
        cr
        
        ." Turn to player "
        dup 0 = if ." &bO"
        else
            dup 1 = if ." &cX"
            else endif
        endif
        ." ." cr
        
        playask
        
        dup -1 = not if
            cr ." --------------------" cr
        else endif

        dup -2 = if
            begin
                dup -10 = not
            while
                drop
            repeat

            1000000000
            0

            ." [&6!&r] &aGame restarted !" cr
        else endif
    repeat
;

( ------ )

main