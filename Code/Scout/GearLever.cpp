// ==============================================================
//                ORBITER MODULE: Scout
//                  Part of the ORBITER SDK
//          Copyright (C) 2001-2008 Martin Schweiger
//                   All rights reserved
//
// GearLever.cpp
// Gear up/down lever interface
// ==============================================================

#define STRICT 1
#include "GearLever.h"
#include "Scout.h"

// constants for texture coordinates
static const float texw = (float)PANEL2D_TEXW; // texture width
static const float texh = (float)PANEL2D_TEXH; // texture height
static const float tx_x0 = 1104.0f;
static const float tx_y0 = texh-689.5f;
static const float tx_dx =  176.0f;
static const float tx_dy =   33.0f;
// constants for panel coordinates
static const float bb_x0 = 1228.5f;
static const float bb_y0 =  326.0f;

// ==============================================================

GearLever::GearLever (VESSEL3 *v): PanelElement (v)
{
}

// ==============================================================

void GearLever::AddMeshData2D (MESHHANDLE hMesh, DWORD grpidx)
{
	static const DWORD NVTX = 4;
	static const DWORD NIDX = 6;
	static const NTVERTEX VTX[NVTX] = {
		{bb_x0,      bb_y0,      0,  0,0,0,  tx_x0/texw,(tx_y0+tx_dy)/texh},
		{bb_x0+tx_dy,bb_y0,      0,  0,0,0,  tx_x0/texw,tx_y0/texh},
		{bb_x0,      bb_y0+tx_dx,0,  0,0,0,  (tx_x0+tx_dx)/texw,(tx_y0+tx_dy)/texh},
		{bb_x0+tx_dy,bb_y0+tx_dx,0,  0,0,0,  (tx_x0+tx_dx)/texw,tx_y0/texh}
	};
	static const WORD IDX[NIDX] = {
		0,1,2, 3,2,1
	};
	AddGeometry (hMesh, grpidx, VTX, NVTX, IDX, NIDX);
}

// ==============================================================

bool GearLever::Redraw2D (SURFHANDLE surf)
{
	Scout *dg = (Scout*)vessel;
	Scout::DoorStatus action = dg->gear_status;
	bool leverdown = (action == Scout::DOOR_OPENING || action == Scout::DOOR_OPEN);
	float y = (leverdown ? bb_y0+tx_dx : bb_y0);
	grp->Vtx[vtxofs+2].y = grp->Vtx[vtxofs+3].y = y;
	return false;
}

// ==============================================================

bool GearLever::ProcessMouse2D (int event, int mx, int my)
{
	Scout *dg = (Scout*)vessel;
	Scout::DoorStatus action = dg->gear_status;
	if (action == Scout::DOOR_CLOSED || action == Scout::DOOR_CLOSING) {
		if (my < 151) dg->ActivateLandingGear (Scout::DOOR_OPENING);
	} else {
		if (my >  46) dg->ActivateLandingGear (Scout::DOOR_CLOSING);
	}
	return false;
}

// ==============================================================
// ==============================================================

GearIndicator::GearIndicator (VESSEL3 *v): PanelElement (v)
{
	tofs = (double)rand()/(double)RAND_MAX;
}

// ==============================================================

void GearIndicator::AddMeshData2D (MESHHANDLE hMesh, DWORD grpidx)
{
	static const DWORD NVTX = 3*4;
	static const DWORD NIDX = 3*6;
	static const NTVERTEX VTX[NVTX] = {
		{1240,   293,   0,  0,0,0,  1018/texw, (texh-597)/texh},
		{1240+10,293,   0,  0,0,0,  1028/texw, (texh-597)/texh},
		{1240,   293+10,0,  0,0,0,  1018/texw, (texh-587)/texh},
		{1240+10,293+10,0,  0,0,0,  1028/texw, (texh-587)/texh},
		{1232,   309,   0,  0,0,0,  1018/texw, (texh-597)/texh},
		{1232+10,309,   0,  0,0,0,  1028/texw, (texh-597)/texh},
		{1232,   309+10,0,  0,0,0,  1018/texw, (texh-587)/texh},
		{1232+10,309+10,0,  0,0,0,  1028/texw, (texh-587)/texh},
		{1248,   309,   0,  0,0,0,  1018/texw, (texh-597)/texh},
		{1248+10,309,   0,  0,0,0,  1028/texw, (texh-597)/texh},
		{1248,   309+10,0,  0,0,0,  1018/texw, (texh-587)/texh},
		{1248+10,309+10,0,  0,0,0,  1028/texw, (texh-587)/texh}
	};
	static const WORD IDX[NIDX] = {
		0,1,2, 3,2,1,
		4,5,6, 7,6,5,
		8,9,10, 11,10,9
	};
	AddGeometry (hMesh, grpidx, VTX, NVTX, IDX, NIDX);
}

// ==============================================================

bool GearIndicator::Redraw2D (SURFHANDLE surf)
{
	int i, j, xofs;
	double d;
	Scout::DoorStatus action = ((Scout*)vessel)->gear_status;
	switch (action) {
		case Scout::DOOR_CLOSED: xofs = 1018; break;
		case Scout::DOOR_OPEN:   xofs = 1030; break;
		default: xofs = (modf (oapiGetSimTime()+tofs, &d) < 0.5 ? 1042 : 1020); break;
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++)
			grp->Vtx[vtxofs+i*4+j].tu = (xofs + (j%2)*10)/texw;
	}
	return false;
}
