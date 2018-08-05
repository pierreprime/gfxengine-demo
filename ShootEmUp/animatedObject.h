#ifndef ANIMATED_OBJECT_H
#define ANIMATED_OBJECT_H

#define MAX_ANIMATED 10
#define ANIMATED_INACTIVE 0
#define ANIMATED_BIG_EXPLOSION 1
#define ANIMATED_SMALL_EXPLOSION 2

typedef struct
{
    int type;
    int sprno;
} s_animated_object;

void ao_init(void);
void ao_create(int type, int x, int y);
void ao_destroy(int aono);
void ao_updateAll();

#endif // ANIMATEDOBJECT_H
