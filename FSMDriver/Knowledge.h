#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <vector>

class Knowledge
{
public:
    float targetSpeed, landmark;
    
    Knowledge();
    Knowledge(float,float);

    static bool aux_sort(const Knowledge& l, const Knowledge& r);
    
    ~Knowledge();
};

extern std::vector<Knowledge> memory;


#endif // KNOWLEDGE_H
