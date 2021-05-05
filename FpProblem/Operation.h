#ifndef Operation_h
#define Operation_h

class Operation{
    int PerformedTime;
    int TerminationTime;
    int StartTime;

    public:

    Operation(){
        PerformedTime=0;
        TerminationTime=0;
        StartTime=0;
    }

    void AddValue(char IDValue, int Value);
    int ReturnValue(char IDValue);
};

#endif