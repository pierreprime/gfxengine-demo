#include "../gfxengine_shared/bfg_gfxEngine.h"
#include "../gfxengine_shared/bfg_spriteEngine.h"
#include "player.h"
#include "playerShoot.h"
#include "myDefines.h"

s_player player;

void playerInit(){
    player.sprno = spr_reserveFreeSprite();
    player.coolDown = 0;

    spr_changeSpriteImage(player.sprno, IB_PLAYER_F0);
    spr_moveSprite(player.sprno, 280, 400);
}

void playerControl(){

    int verif;
    if(player.coolDown > 0){
        player.coolDown--;
    }

    checkController();
    if(getKeyRight() == 1)
        spr_moveSpriteRelative(player.sprno, 3, 0);
    else if(getKeyLeft() == 1)
        spr_moveSpriteRelative(player.sprno, -3, 0);

    if((getKeyA() == 1) && (player.coolDown == 0)){
        verif = ps_create((int)spr_getSpriteX(player.sprno)+42, (int)spr_getSpriteY(player.sprno));
        if(verif != -1){
            player.coolDown = PL_COOLDOWN;
        }
    }
}

int getPlayerCoolDown(void){
    return player.coolDown;
}

void setPlayerCoolDown(int cd){
    player.coolDown = cd;
}

int getPlayerSpriteNumber(void){
    return player.sprno;
}

int getPlayerNbLive(void){
    return player.nbLive;
}

void setPlayerNbLive(int nbLive){
    player.nbLive = nbLive;
}
