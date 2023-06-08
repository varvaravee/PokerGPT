#ifndef ISROYALFLUSH_H
#define ISROYALFLUSH_H

#include "cards2.h"

int isRoyalFlush(PlayerDECK P, HouseDECK H);

int isRoyalFlush(PlayerDECK P, HouseDECK H)
{
    // check if there is a flush
    if (!isFlush(P, H))
        return 0; // Not a royal flush
    
    // check if the highest cards are A, K, Q, J, 10 of the same suit
    int suit = -1;
    int values[4] = {1, 10, 11, 12, 13}; // A, 10, J, Q, K
    
    // check player's hand
    for (int i = 0; i < 2; i++)
    {
        if (P[i]->Value == values[4] && (suit == -1 || P[i]->CC == suit))
            suit = P[i]->CC;
    }
    
    // check house cards
    for (int i = 0; i < 5; i++)
    {
        if (H[i] != NULL && H[i]->Value == values[4] && (suit == -1 || H[i]->CC == suit))
            suit = H[i]->CC;
    }
    
    // check if all the required cards are present in the same suit
    for (int i = 1; i < 5; i++)
    {
        int found = 0;
        for (int j = 0; j < 2; j++)
        {
            if (P[j]->Value == values[i] && P[j]->CC == suit)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            for (int j = 0; j < 5; j++)
            {
                if (H[j] != NULL && H[j]->Value == values[i] && H[j]->CC == suit)
                {
                    found = 1;
                    break;
                }
            }
        }
        if (!found)
            return 0; // Not a royal flush
    }
    
    return 1; // Royal flush
}

#endif 
