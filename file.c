#include <stdlib.h>

#include "a234.h"
#include "file.h"

pfile_t creer_file()
{
    pfile_t f = malloc(sizeof(file_t));
    for (int i = 0; i != MAX_FILE_SIZE; i++)
        f->Tab[i] = NULL;
    f->tete = 0;
    f->queue = 0;
    f->nb = 0;
    return f;
}

int detruire_file(pfile_t f)
{
    if (f == NULL)
        return 0;
    free(f);
    return 0;
}

int file_vide(pfile_t f)
{
    if (f == NULL)
        return 0;
    if (f->nb == 0)
        return 1;
    return 0;
}

int file_pleine(pfile_t f)
{
    if (f == NULL)
        return 0;
    if (f->nb == 32)
        return 1;
    return 0;
}

pnoeud234 defiler(pfile_t f)
{
    if (f == NULL)
        return NULL;
    if (file_vide(f) == 1)
        return NULL;
    pnoeud234 n = f->Tab[f->tete];
    f->tete++;
    f->nb--;
    if (f->tete >= 32)
        f->tete = 0;
    return n;
}

int enfiler(pfile_t f, pnoeud234 p)
{
    if (f == NULL)
        return 0;
    if (file_pleine(f) == 1)
        return 0;
    f->Tab[f->queue] = p;
    f->queue++;
    f->nb++;
    if (f->queue >= 32)
        f->queue = 0;
    return 1;
}
