#ifndef IDXFILE_H
#define IDXFILE_H

/*	Indexed file for fast random access on big files for e.g. hdd images
	Copyright (c) 2015 by Till Harbaum

	Contributed to the Minimig project, which is free software;
	you can redistribute it and/or modify it under the terms of
	the GNU General Public License as published by the Free Software Foundation;
	either version 3 of the License, or (at your option) any later version.

	Minimig is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "fat_compat.h"

#define SZ_TBL 1024
#define HDD_IMAGES 2

typedef struct
{
	char valid;
	FIL file;
	DWORD clmt[SZ_TBL];
} IDXFile;

extern IDXFile hdd_image[HDD_IMAGES];

static inline unsigned char IDXRead(IDXFile *file, unsigned char *pBuffer) {
  UINT br;
  return f_read(&(file->file), pBuffer, 512, &br);
}

static inline unsigned char IDXWrite(IDXFile *file, unsigned char *pBuffer) {
  UINT bw;
  return f_write(&(file->file), pBuffer, 512, &bw);
}

unsigned char IDXOpen(IDXFile *file, const char *name, char mode);
void IDXClose(IDXFile *file);
unsigned char IDXSeek(IDXFile *file, unsigned long lba);
void IDXIndex(IDXFile *pIDXF);

#endif
