/**
 * @file RecommStrategy.h
 * @brief Abstract Strategy interface for recommendation algorithms
 */
#ifndef RECOMMSTRATEGY_H
#define RECOMMSTRATEGY_H

class RecommStrategy {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~RecommStrategy() {}
    /**
     * @brief Recommends plants based on the implemented strategy
     */
    virtual void recommend() = 0;
};
#endif