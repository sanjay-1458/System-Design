#ifndef LADDER_H
#define LADDER_H

class Ladder {

    int start, end;

public:

    Ladder(int start, int end);

    int getStart() const;
    int getEnd() const;
};

#endif