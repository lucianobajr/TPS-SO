void instruction_n(int number_of_variable_to_declare, int **memory)
{
    *memory = (int *)malloc(number_of_variable_to_declare * sizeof(int));

    for (int i = 0; i < number_of_variable_to_declare; i++)
    {
        (*memory)[i] = __INT_MAX__;
    }
}

void instruction_d(int index_of_variable_declared, int** memory)
{
    (*memory)[index_of_variable_declared] = 0;
}

void instruction_v(int index, int value, int** memory)
{
    (*memory)[index] = value;
}

void instruction_a(int index, int value, int** memory)
{
    (*memory)[index] = (*memory)[index] + value;
}

void instruction_s(int index, int value, int** memory)
{
    (*memory)[index] = (*memory)[index] - value;
}