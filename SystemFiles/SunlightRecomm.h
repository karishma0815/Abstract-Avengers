#ifndef SUNLIGHTRECOMM_H
#define SUNLIGHTRECOMM_H

#include"RecommStrategy.h"

class SunlightRecomm: public RecommStrategy{
    public:
    SunlightRecomm();
    virtual void recommend() override;
    ~SunlightRecomm();
};
#endif