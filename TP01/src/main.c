#include "../headers/core/control.h"

int main(int argc, char const *argv[])
{
    scheduler_policy type_escalation_policy;

    if (!argv[1])
    {
        type_escalation_policy = MULTIPLE_QUEUES;
    }
    else
    {
        int user_type_escalation_policy = atoi(argv[1]);

        if (user_type_escalation_policy != 0 && user_type_escalation_policy != 1)
        {
            type_escalation_policy = MULTIPLE_QUEUES;
        }
        else
        {
            type_escalation_policy = user_type_escalation_policy;
        }
    }

    control(type_escalation_policy);

    return 0;
}