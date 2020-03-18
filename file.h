#ifndef _FILE_H_
#define _FILE_H_

#include "a234.h"
#define MAX_FILE_SIZE 32

typedef struct
{
    int tete;
    int queue;
    int nb;
    pnoeud234 Tab[MAX_FILE_SIZE];
} file_t, *pfile_t;

pfile_t creer_file();

int detruire_file(pfile_t f);

int file_vide(pfile_t f);

int file_pleine(pfile_t f);

pnoeud234 defiler(pfile_t f);

int enfiler(pfile_t f, pnoeud234 p);

#endif