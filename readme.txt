File: readme.txt
Author: Miles Zoltak
----------------------

ATM
---
1a)

Defect description:
       The withdraw function subtracts (unsigned int)amount from (signed int)cust->balance which
       casts the whole operation to be unsigned int subtraction.  This means that it overflows to
       2^32 or whatever when you should get a negative number.  Then when they check to see if the
       resulting withdraw gives a balance of less than MIN_BALANCE ($50), they get back false becuase
       the resulting balance appears to be like 4 billion-ish or so.
-------------------

Test case explanation (put test case in custom_tests!):
     Didn't wanna go for anything too crazy, just demonstrate that having the logical balance be less
     than zero causes the error.  Of course you can't subtract 300 or more becuase that is the
     MAX_WITHDRAW number.  So 108 does it quite nicely and modestly I think.
-------------------------------------------------------

Recommended fix:
            I think if you just change <withdraw>'s function signature to type "amount" as a regular
            signed int instead of an "unsigned int" that should alleviate the problem.
----------------

1b)

Defect description:
       When running the find_account() function, there is no return statement reached when we pass in
       an invalid username.  This means that we just get back whatever value was put into %rax
       throughout the calculations because %rax is callee-owned and will not be set back to any
       specific value.  This means that various inputs lead to various bogus return values and
       although most inputs lead to negative return values, the input can be manipulated to give a
       positive output.
-------------------

Test case explanation (put test case in custom_tests!):
     When I noticed that there was no return value and that various assembly calls were moving values
     all around between %rdi, $rsi, %rax, and other registers, it dawned on me that the return value
     for a bogus username could be affected by the input parameters.  I started testing the output of
     find_account() under different inputs and saw that the username was the trick.  I did some
     analytical trial and error and found that going one letter at a time and pushing the limits of
     overflow and underflow so that the %rax value would overflow back to 1 when casted from an
     unsigned into to a signed int as account_num.
-------------------------------------------------------

Recommended fix:
            Change find_account() to have an EXIPLICIT negative return value instead of just letting
            whatever ends up in %rax be the return value.
----------------

1c)

Defect description:
       The sprintf() function allows the user two overwrite the buffer provided for the path which
       lets them overwrite adjacent memory.  This can be manipulated to trick the atm into thinking
       they have submitted the right password to the vault and they may withdraw from the vault.
-------------------

Test case explanation (put test case in custom_tests!):
     If you put in a name that is long enough, you can overwrite the buffer used to store that
     name and overwrite adjacent memory.  If you overwrite the four bits that coorespond to the
     password and then submit a password that is equal to the numeric representation of the bits
     that have overwritten the password location, you can make the system think you entered a valid
     passcode.
-------------------------------------------------------

Recommended fix:
            If they used strlen(filename) instead of sizeof(filename) they would be able to size the
            buffer accordingly and not let them overwrite space.
----------------

Bomb
----
2a)
    I looked through the assembly code to find the explode_bomb() function.  I set a breakpoint at
    the first instruction and then made it execute a signal SIGKILL to stop the program from
    deducting points.  It failed once, a few minutes ago, and I have no idea why... maybe a
    connectivity issue, but I'm not sure... weird.
2b)
    That hex number is the numeric encoding of a string.  It is placed into %edi so that it can be
    the first argument of strcmp(), where the second argument is our input.  The two are compared
    against each other and if they match, you defuse the first level.
2c)
    It doesn't reaaaally matter if a branch is preceded by a test or a cmp instruction at all.  All
    the branch commands do is check for certain flag values.  This jle branch is taken if the result
    of the xor instruction turns on the zero flag OR if it results in nonequal sign flag and overflow
    flag values.  The first can only be true if the two operands are the same, so it really came down
    to the second one about SF != OF.
2d)
    winky is exited if strcmp returns 0.  However, you don't want it to work right away because you
    need to build up the value in %r12d and that is done by choosing a good input according to the
    64 words read from the wordlist.
2e)
    The size of the variable is 8 bytes and it is a ptr to a char* (aka char **).  I can figure
    this out because it is used as the second argument when strtoul is called, and that argument
    maps to a char ** in the documentation.  It doesn't have to be set in the code though, because
    strtoul will do that on it's own.  On return endptr ($rsi) will either be NULL or set to the
    first invalid character (which is used as the delimiter to break up our array) which is a space
    here.
2f)
    My cmp is used to check if the array you passed is in order, this is necessary because find1 and
    find2 will be calling bsearch which requires that the array be in sorted order.  This is
    necessary becuase the same comparison function will be used to help the pointer navigate through
    the array in the way a binary search pointer does.  If it were out of order the navigation would
    be improperly "calibrated", if you will.  The data being compared are integers.  The value of
    each integer being compared is bit shifted right 4 times until the number is less than 16 (fits
    in 4 bits).  Overall it's checking if the numbers are in ascending order AFTER that alteration
    is applied.

Secret Level:
       The CS107 TAs rock for making this level, I think it really shows just how fun this assignment is
       supposed to be both for the students and the staff.  That being said, I was excited to get going
       on it.  Then I saw how much harder it was supposed to be, and I considered the physical toll  this
       assignment took on my body, and I said no thank you.  So I'm glad you guys had funt.
       But now that I finished the mandatory part it's Summertime... and the living is easy, so I'll pass.
