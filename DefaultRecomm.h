#ifndef DEFAULTRECOMM_H
#define DEFAULTRECOMM_H

#include"RecommStrategy.h"

class DefaultRecomm: public RecommStrategy{
    public:
    DefaultRecomm();
    virtual void recommend() override;
    ~DefaultRecomm();
};
#endif