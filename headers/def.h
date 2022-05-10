#ifndef _H_DEF_
#define _H_DEF_

typedef enum Bool
{
    False,
    True
} Bool;

#define LEN_RESPONSE 10

// colors
#define ESC "\x01b"
#define INIT ESC "[0m"  //reset
#define RED ESC "[31m"
#define GREEN ESC "[32m"
#define YELLOW ESC "[33m"
#define BLUE ESC "[34m"
#define MAGENTA ESC "[35m"

#define BOLD ESC "[1m"
#define ITALIC ESC "[3m"
#define UNDERLINE ESC "[4m"
#define BLINK ESC "[5m"
#define BACKGROUND ESC "[47m"       //white
#define REVERSED ESC "[7m"

#endif
