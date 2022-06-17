#ifndef INSTRUCTIONS_h
#define INSTRUCTIONS_h

typedef struct
{
    char command;

    union
    {
        int value;
    } N;

    union
    {
        int memory_reference;
    } D;

    union
    {
        int value;
    } F;

    union
    {
        char *file;
    } R;

    union
    {
        struct
        {
            int memory_reference;
            int value;
        } values;
    } operation;

} instructions;

#endif