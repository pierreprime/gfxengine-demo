#ifndef WORKFLOW_H
#define WORKFLOW_H

#define WORKFLOW_INIT 0
#define WORKFLOW_TITLE_SCREEN 1
#define WORKFLOW_INGAME 2
#define WORKFLOW_LOOSELIFE 3
#define WORKFLOW_GAMEOVER 4
#define WORKFLOW_NEXTLEVEL 5

void w_set(int value);
int w_get();
void title_screen();
void next_level();

#endif // WORKFLOW_H
