/* FILE NAME: LOADPRIM.C
 * PROGRAMMER: VG4
 * DATE: 13.06.2016
 * PURPOSE: Render handle functions.
 */

#include <stdio.h>
#include <string.h>

#include "anim.h"

/* Load primitive from '*.g3d' file function.
 * ARGUMENTS:
 *   - primitive structure pointer:
 *       vg4PRIM *Pr;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL VG4_RndPrimLoad( vg4PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  DWORD Sign;
  INT NumOfPrimitives;
  CHAR MtlFile[300];
  INT NumOfV;
  INT NumOfI;
  CHAR Mtl[300];
  INT p;
  vg4VERTEX *V;
  INT *I;

  memset(Pr, 0, sizeof(vg4PRIM));

  F = fopen(FileName, "rb");
  if (F == NULL)
    return FALSE;

  /* File structure:
   *   4b Signature: "G3D\0"    CHAR Sign[4];
   *   4b NumOfPrimitives       INT NumOfPrimitives;
   *   300b material file name: CHAR MtlFile[300];
   *   repeated NumOfPrimitives times:
   *     4b INT NumOfV; - vertex count
   *     4b INT NumOfI; - index (triangles * 3) count
   *     300b material name: CHAR Mtl[300];
   *     repeat NumOfV times - vertices:
   *         !!! float point -> FLT
   *       typedef struct
   *       {
   *         VEC  P;  - Vertex position
   *         VEC2 T;  - Vertex texture coordinates
   *         VEC  N;  - Normal at vertex
   *         VEC4 C;  - Vertex color
   *       } VERTEX;
   *     repeat (NumOfF / 3) times - facets (triangles):
   *       INT N0, N1, N2; - for every triangle (N* - vertex number)
   */
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3D")
  {
    fclose(F);
    return FALSE;
  }
  fread(&NumOfPrimitives, 4, 1, F);
  fread(MtlFile, 1, 300, F);
  for (p = 0; p < NumOfPrimitives; p++)
  {
    /* Read primitive info */
    fread(&NumOfV, 4, 1, F);
    fread(&NumOfI, 4, 1, F);
    fread(Mtl, 1, 300, F);

    /* Allocate memory for primitive */
    if ((V = malloc(sizeof(vg4VERTEX) * NumOfV)) == NULL)
    {
      fclose(F);
      return FALSE;
    }
    if ((I = malloc(sizeof(INT) * NumOfI)) == NULL)
    {
      free(V);
      V = NULL;
      fclose(F);
      return FALSE;
    }
    Pr->NumOfI = NumOfI;
    fread(V, sizeof(vg4VERTEX), NumOfV, F);
    fread(I, sizeof(INT), NumOfI, F);

    /* Create OpenGL buffers */
    glGenVertexArrays(1, &Pr->VA);
    glGenBuffers(1, &Pr->VBuf);
    glGenBuffers(1, &Pr->IBuf);

    /* Activate vertex array */
    glBindVertexArray(Pr->VA);
    /* Activate vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    /* Store vertex data */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vg4VERTEX) * NumOfV, V, GL_STATIC_DRAW);

    /* Setup data order */
    /*                    layout,
     *                      components count,
     *                          type
     *                                    should be normalize,
     *                                           vertex structure size in bytes (stride),
     *                                               offset in bytes to field start */
    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                          (VOID *)0); /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                          (VOID *)sizeof(VEC)); /* texture coordinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */

    /* Enable used attributes */
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    /* Indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);

    /* Disable vertex array */
    glBindVertexArray(0);

    free(V);
    free(I);
    break;
  }
  fclose(F);
  return TRUE;
} /* End of 'VG4_RndPrimLoad' function */

/* END OF 'LOADPRIM.C' FILE */
