#include    "./lib/libEuler.h"
#include    "./src/head_gen.h"
#include    "./src/euler.h"
#define     P_HEADER "./src/problems.h"
#include    P_HEADER
#include    <stdio.h>

#define N_PROBLEMS  100
#define USE_MSG     "Usage: ./_euler [problem number]"
#define INPUT_MSG   "Your input is shit."
#define PROB_MSG    "The problem is not yet solved."

typedef void (* fptr)(void);

static const fptr call_table[N_PROBLEMS] =
{
    NULL,
    p_1,
    p_2,
    p_3,
    p_4,
    p_5,
    p_6,
    p_7,
    p_8,
    p_9,
    p_10,
    p_11,
    p_12,
    p_13,
    p_14,
    p_15,
    p_16,
    NULL,
    p_18,
    NULL,
    p_20,
    p_21,
};

static inline int _error(const byte * msg)
{
    return printf("%s\n", msg);
}

static inline int _test()
{
    Bigu x = Bigu_factorial(100);
    Bigu_dbg(x);
    Bigu_del(& x);

    return 0;
}

static inline void _run(fptr f)
{
    f();
    nl;
}

//header gen
//code align
//regex
//c flags
// fold ? filter ?

int main(int argc, char * argv[])
{
    u64     n;
    fptr    function;

    if (argc == 1) return _test();
    if (argc != 2) return _error(USE_MSG);

    n = u64_parse_cstr(argv[1]);
    if (n == 0 || n > N_PROBLEMS) return _error(INPUT_MSG);
    if (! (function = call_table[n])) return _error(PROB_MSG);

    _run(function);
}