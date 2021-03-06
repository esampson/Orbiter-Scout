// ==============================================================
//                ORBITER MODULE: Scout
//                  Part of the ORBITER SDK
//          Copyright (C) 2001-2008 Martin Schweiger
//                   All rights reserved
//
// UndockBtn.cpp
// "Dock release" button interface
// ==============================================================

#define STRICT 1
#include "UndockBtn.h"
#include "Scout.h"

// constants for texture coordinates
static const float texw = (float)PANEL2D_TEXW; // texture width
static const float texh = (float)PANEL2D_TEXH; // texture height
static const float tx_x0 = 1102.5f;     // left edge of texture block
static const float tx_y0 = texh-614.5f; // top edge of texture block
static const float tx_dx = 31.0f;       // texture block width
static const float tx_dy = 39.0f;       // texture block height
// constants for panel coordinates
static const float bb_x0 = 1140.5f;     // left edge of button block
static const float bb_y0 =  471.5f;     // top edge of button block

// ==============================================================

UndockButton::UndockButton (VESSEL3 *v): PanelElement (v)
{
	Reset2D();
}

// ==============================================================

void UndockButton::AddMeshData2D (MESHHANDLE hMesh, DWORD grpidx)
{
	static const DWORD NVTX = 4;
	static const DWORD NIDX = 6;
	static const NTVERTEX VTX[NVTX] = {
		{bb_x0,      bb_y0,      0,  0,0,0,  tx_x0/texw,        tx_y0/texh},
		{bb_x0+tx_dx,bb_y0,      0,  0,0,0,  (tx_x0+tx_dx)/texw,tx_y0/texh},
		{bb_x0,      bb_y0+tx_dy,0,  0,0,0,  tx_x0/texw,        (tx_y0+tx_dy)/texh},
		{bb_x0+tx_dx,bb_y0+tx_dy,0,  0,0,0,  (tx_x0+tx_dx)/texw,(tx_y0+tx_dy)/texh}
	};
	static const WORD IDX[NIDX] = {
		0,1,2, 3,2,1
	};

	AddGeometry (hMesh, grpidx, VTX, NVTX, IDX, NIDX);
}

// ==============================================================

void UndockButton::Reset2D ()
{
	btndown = false;
}

// ==============================================================

bool UndockButton::Redraw2D (SURFHANDLE surf)
{
	float y = (btndown ? bb_y0+tx_dy : bb_y0);
	float tv = (btndown ? tx_y0+tx_dy : tx_y0)/texh;
	grp->Vtx[vtxofs+2].y = grp->Vtx[vtxofs+3].y = y;
	grp->Vtx[vtxofs+2].tv = grp->Vtx[vtxofs+3].tv = tv;
	return false;
}

// ==============================================================

bool UndockButton::ProcessMouse2D (int event, int mx, int my)
{
	if (event == PANEL_MOUSE_LBDOWN) vessel->Undock (0);
	btndown = (event == PANEL_MOUSE_LBDOWN);
	return true;
}
