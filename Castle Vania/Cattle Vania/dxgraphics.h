#ifndef		_DXGRAPHICS_H
#define		_DXGRAPHICS_H
#include <d3d9.h>
#include <d3dx9.h>

int Init_Direct3D(HWND, int, int, int);

extern LPDIRECT3D9			d3d;
extern LPDIRECT3DDEVICE9	d3ddev;
extern LPDIRECT3DSURFACE9	backbuffer;
extern LPDIRECT3DSURFACE9	surface;
#endif //     _DXGRAPHICS_H
