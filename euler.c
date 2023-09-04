#include    "./lib/libEuler.h"
#include    "./src/head_gen.h"
#include    "./src/test.h"
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
};

static int _error(const byte * msg)
{
    return printf("%s\n", msg);
}

//word trim
//header gen
//code align
//regex

int main(int argc, char * argv[])
{
    u64     n;
    fptr    function;

    // if (argc != 2) return _error(USE_MSG);

    // n = u64_parse_cstr(argv[1]);
    // if (n == 0 || n > N_PROBLEMS) return _error(INPUT_MSG);
    // if (! (function = call_table[n])) return _error(PROB_MSG);

    // function();

    _Bfd_test();

}