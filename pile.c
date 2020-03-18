#include <stdlib.h>

#include "a234.h"
#include "pile.h"

ppile_t creer_pile()
{
    ppile_t pile = (ppile_t)malloc(sizeof(pile_t));
    for (int i = 0; i != MAX_PILE_SIZE; i++)
        pile->Tab[i] = NULL;
    pile->sommet = -1;
    return pile;
}

int detruire_pile(ppile_t p)
{
    if (p == NULL)
        return 1;
    free(p);
    return 0;
}

int pile_vide(ppile_t p)
{
    if (p == NULL)
        return 2;
    return (p->sommet == -1);
}

int pile_pleine(ppile_t p)
{
    if (p == NULL)
        return 2;
    return (p->sommet == MAX_PILE_SIZE - 1);
}

pnoeud234 depiler(ppile_t p)
{
    if (p == NULL)
        return NULL;
    pnoeud234 n = p->Tab[p->sommet];
    p->sommet--;
    return n;
}

int empiler(ppile_t p, pnoeud234 pn)
{
    if (p == NULL)
        return 1;
    p->sommet++;
    p->Tab[p->sommet] = pn;
    return 0;
}
