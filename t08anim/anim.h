 /* file name: anim.h
 *progremmer: sa2
 *date: 11.06.2016
 */
#ifndef  __ANIM_H_
#define  __ANIM_H_
#include "def.h"

#define MAX_UNITS 1000

typedef struct tagsa2UNIT sa2UNIT;

 
typedef struct tagsa2ANIM
{
  HWND hWnd; 
  HDC hDC; 
  HGLRC hGLRC;

  INT W, H;
  HBITMAP hFrame; 
  sa2UNIT *Units[MAX_UNITS]; 
  INT NumOfUnits;
  DBL
    GlobalTime, GlobalDeltaTime, Time, DeltaTime, FPS;
  BOOL IsPause;
  INT 
    Mx, My, Mz, Mdx, Mdy, Mdz;
  BYTE 
    Keys[256],
    OldKeys[256],
    KeysClick[256];
  BYTE
    JBut[32];
  INT JPov;
  DBL
     JX, JY, JZ, JR;

  
} sa2ANIM;
struct tagsa2UNIT
{
  VOID (* Init)(sa2UNIT *Uni, sa2ANIM *Ani);
  VOID (* Close)(sa2UNIT *Uni, sa2ANIM *Ani);
  VOID (* Response)(sa2UNIT *Uni, sa2ANIM *Ani);
  VOID (* Render)(sa2UNIT *Uni, sa2ANIM *Ani);
} ;
__inline DBL Rnd0( VOID )
{
  return (DBL)rand() / RAND_MAX;
} 
__inline DBL Rnd1( VOID )
{
  return 2.0 * rand() / RAND_MAX - 1;
}
extern INT SA2_MouseWheel;


extern sa2ANIM SA2_Anim;
VOID  SA2_AnimInit( HWND hWnd );
VOID  SA2_AnimClose( VOID );
VOID  SA2_AnimResize( INT W, INT H );
VOID  SA2_AnimCopyFrame( VOID );
VOID  SA2_AnimRender( VOID );
VOID  SA2_AnimAddUnit( sa2UNIT *Uni );
VOID SA2_AnimDoExit( VOID );
VOID SA2_AnimFlipFullScren( VOID );
sa2UNIT * SA2_AnimUnitCreate( INT Size );

extern MATR 
      SA2_RndMatrWorld,
      SA2_RndMatrView,
      SA2_RndMatrProj;
extern DBL
  SA2_RndProjDist, /* Near clip plane */
  SA2_RndFarClip,  /* Far clip plane */
  SA2_RndProjSize; /* Project plane size */
typedef struct
{
  VEC  P;   /*Vertex position*/
  VEC2 T;   /*Vertex texture coordinates*/            
  VEC  N;   /*Normal at vertex*/ 
  sa2COLOR C;   /*Vertex color*/
} sa2VERTEX;

typedef struct
{
  sa2VERTEX *V;     /* Primitive vertex array */
  INT NumOfV;       /* Point array size */
  INT *I;           /* Facets index array */
  INT NumOfI;       /* Facets index array size */
} sa2PRIM;




extern MATR SA2_RndMatrWorld, SA2_RndMatrView, SA2_RndMatrProj;
extern DBL SA2_RndProjSize, SA2_RndProjDist, SA2_RndFarClip;
VOID SA2_RndSetProj( VOID );


VOID SA2_RndPrimDraw( sa2PRIM *Pr );


VOID SA2_RndPrimFree( sa2PRIM *Pr );


BOOL SA2_RndPrimLoad( sa2PRIM *Pr, CHAR *FileName );

VOID SA2_RndSetProj( VOID );


VOID SA2_RndPrimDraw( sa2PRIM *Pr );

extern INT S2_Anim;


#endif
    
