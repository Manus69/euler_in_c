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
};

static inline int _error(const byte * msg)
{
    return printf("%s\n", msg);
}

static inline void _run(fptr f)
{
    f();
    nl;
}

//word trim
//header gen
//code align
//regex
//c flags
// fold ? filter ?
//test.h -> something else.h ?

int main(int argc, char * argv[])
{
    u64     n;
    fptr    function;

    if (argc != 2) return _error(USE_MSG);

    n = u64_parse_cstr(argv[1]);
    if (n == 0 || n > N_PROBLEMS) return _error(INPUT_MSG);
    if (! (function = call_table[n])) return _error(PROB_MSG);

    _run(function);
}