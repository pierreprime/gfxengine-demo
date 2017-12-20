#ifndef GESTIONROOM_H
#define GESTIONROOM_H

void gr_initLevelRooms(int level);
void gr_changeRoom(int level,int roomX,int roomY);
void gr_showRoom(void);
void gr_removeObj(int level,int roomX,int roomY,int typeObjet,int objet,int idObject);
int gr_getStartPlayerX(void);
int gr_getStartPlayerY(void);

void gr_move2RoomRight();
void gr_move2RoomLeft();
void gr_move2RoomUp();
void gr_move2RoomDown();
int gr_isLastRoom(void);
int gr_getHalo(void);

#endif
