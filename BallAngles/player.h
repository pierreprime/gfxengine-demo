#ifndef PLAYER_H
#define PLAYER_H

typedef struct{

    int sprno;
    int nbLive;
    int coolDown;

}s_player;

void playerInit();
void playerControl();
int getPlayerCoolDown(void);
void setPlayerCoolDown(int cd);
int getPlayerSpriteNumber(void);
int getPlayerNbLive(void);
void setPlayerNbLive(int nbLive);

#endif // PLAYER_H
