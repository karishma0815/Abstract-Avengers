#ifndef WATERRECOMM_H
#define WATERRECOMM_H

#include"RecommStrategy.h"

class WaterRecomm: public RecommStrategy{
    public:
    WaterRecomm();
    virtual void recommend() override;
    ~WaterRecomm();
};
#endif