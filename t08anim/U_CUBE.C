/* file name: U_CUBE.C
 *progremmer: sa2
 *date: 15.06.2016
 */
#include <time.h>                   



#include "anim.h"

/* Ball unit representation type */
typedef struct
{
  sa2UNIT;         /* Base unit fields */
  VEC Pos;         /* Cube position */
  DBL TimerShift;  /* Timer shift phase value*/
  DBL TimerSpeed; 
  sa2OBJ Obj;  /* Timer speed value*/
} sa2UNIT_CUBE;

/* Cube primitive */

/* Unit cube initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       sa2UNIT_CUBE *Uni;                                       
 *   - animation context:
 *       sa2ANIM *Ani;
 * RETURNS: None.
 */
static VOID SA2_UnitInit( sa2UNIT_CUBE *Uni, sa2ANIM *Ani )
{
  Uni->Pos = VecSet(/*Rnd0() * 5, Rnd0() * 5, Rnd0() * 5*/0, 0, -5);
  Uni->TimerShift = Rnd1() * 59;
  Uni->TimerSpeed = Rnd1() * 8;
  SA2_RndObjLoad(&Uni->Obj, "modela\\dodge.g3d");
 
} /* End of 'SA2_UnitInit' function */                        

/* Unit cube deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       sa2UNIT_CUBE *Uni;
 *   - animation context:
 *       sa2ANIM *Ani;
 * RETURNS: None.
 */
static VOID SA2_UnitClose( sa2UNIT_CUBE *Uni, sa2ANIM *Ani )
{
  SA2_RndObjFree(&Uni->Obj);
} /* End of 'SA2_UnitClose' function */

/* Unit cube inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       sa2UNIT_CUBE *Uni;
 *   - animation context:
 *       sa2ANIM *Ani;
 * RETURNS: None.
 */
static VOID SA2_UnitResponse( sa2UNIT_CUBE *Uni, sa2ANIM *Ani )
{
 
} /* End of 'SA2_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       sa2UNIT_CUBE *Uni;
 *   - animation context:
 *       sa2ANIM *Ani;
 * RETURNS: None.
 */
static VOID SA2_UnitRender( sa2UNIT_CUBE *Uni, sa2ANIM *Ani )
{
 

  SA2_RndMatrWorld = MatrMulMatr(SA2_RndMatrWorld, MatrScale(VecSet(0.8F, 0.8F, 0.8F)),
                MatrTranslate(VecAddVec(Uni->Pos, VecMulNum(VecSet(Ani->JX, Ani->JY, Ani->JZ),3)))); 

 /* SA2_RndMatrWorld = MatrMulMatr(MatrScale(VecSet(0.8F, 0.8F, 0.8F)),
                     MatrMulMatr(MatrRotateY((Uni->TimerSpeed * Ani->Time) * 30 + Uni->TimerShift),
                                 MatrTranslate(VecAddVec(Uni->Pos,
                                                         VecMulNum(VecSet(Ani->JX, Ani->JY, Ani->JZ), 3))))); */
  

  SA2_RndObjDraw(&Uni->Obj);
} /* End of 'SA2_UnitRender' function */

/* Unit cube creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (sa2UNIT *) pointer to created unit.
 */
sa2UNIT * SA2_UnitCreateCube( VOID )
{
  sa2UNIT_CUBE *Uni;

  if ((Uni = (sa2UNIT_CUBE *)SA2_AnimUnitCreate(sizeof(sa2UNIT_CUBE))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)SA2_UnitInit;
  Uni->Close = (VOID *)SA2_UnitClose;
  Uni->Response = (VOID *)SA2_UnitResponse;
  Uni->Render = (VOID *)SA2_UnitRender;
  return (sa2UNIT *)Uni;
} /* End of 'SA2_UnitCreateCube' function */

/* END OF 'U_CUBE.C' FILE */
 