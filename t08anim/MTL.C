/* FILE NAME: MTL.C
 * PROGRAMMER: SA2
 * DATE: 18.06.2016
 * PURPOSE: Materials handle functions.
 */

#include <stdio.h>
#include <string.h>

#include "anim.h"

/* Materials array */
sa2MTL SA2_RndMaterials[SA2_MAX_MATERIALS] =
{
  {
    "default material",
    {0.1, 0.1, 0.1}, {1, 1, 1}, {0, 0, 0}, 30, 1, 0, 0, 0
  }
};
INT SA2_RndNumOfMaterials = 1;

/* Material find by name function.
 * ARGUMENTS:
 *   - material name:
 *       CHAR *Name;
 * RETURNS:
 *   (INT) number of found material or -1 if no result.
 */
INT SA2_RndFindMaterial( CHAR *Name )
{
  INT i;

  for (i = 0; i < SA2_RndNumOfMaterials; i++)
    if (strcmp(Name, SA2_RndMaterials[i].Name) == 0)  /* #include <string.h> */
      return i;
  return -1;
} /* End of 'VG4_RndFindMaterial' function */

/* Material load function.
 * ARGUMENTS:
 *   - material file name:
 *       CHAR *FileName;
 * RETURNS: None.
*/
VOID SA2_RndLoadMaterials( CHAR *FileName )
{
  INT i, NumOfMaterials /* , x, y */;
  UINT t;
  DWORD Sign;
  FILE *F;
  sa2MTL M;
  BYTE *Image;

  if ((F = fopen(FileName, "rb")) == NULL)
    return;
  /* Read and check file signature */
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"GMT")
  {
    fclose(F);
    return;
  }

  /* Read all materials */
  fread(&NumOfMaterials, 4, 1, F);
  for (i = 0; i < NumOfMaterials; i++)
  {
    if (SA2_RndNumOfMaterials >= SA2_MAX_MATERIALS)
      break;

    /* Read illumination coefficients and texture parameters */
    fread(&M, sizeof(sa2MTL), 1, F);
    
    /* Read image */
    if (M.TexW != 0 && M.TexH != 0 && M.TexNo != 0)
    {
      /* Allocate memory for texture image */
      if ((Image = malloc(M.TexW * M.TexH * M.TexNo)) == NULL)
      {
        fclose(F);
        return;
      }
      fread(Image, M.TexNo, M.TexW * M.TexH, F);
      /* Flip image */
      /*
      for (y = 0; y < M.TexH / 2; y++)
        for (x = 0; x < M.TexW * M.TexNo; x++)
        {
          INT
            first = y * M.TexW * M.TexNo + x,
            last = (M.TexH - 1 - y) * M.TexW * M.TexNo + x;
          BYTE tmp = Image[first];

          Image[first] = Image[last];
          Image[last] = tmp;
        }
      */
      glGenTextures(1, &t);
      glBindTexture(GL_TEXTURE_2D, t);
      gluBuild2DMipmaps(GL_TEXTURE_2D, M.TexNo, M.TexW, M.TexH,
        M.TexNo == 3 ? GL_BGR_EXT : GL_BGRA, GL_UNSIGNED_BYTE, Image);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);
      M.TexNo = t;
    }
    else
      M.TexNo = 0;
    /* Add material to animation and OpenGL */
    SA2_RndMaterials[SA2_RndNumOfMaterials++] = M;
  }
  fclose(F);
} /* End of 'SA2_RndLoadMaterials' function */

/* END OF 'MTL.C' FILE */
