// ==============================================================
//                ORBITER MODULE: Scout
//                  Part of the ORBITER SDK
//          Copyright (C) 2001-2008 Martin Schweiger
//                   All rights reserved
//
// ThrottleScram.h
// Scram throttle sliders
// ==============================================================

#ifndef __THROTTLESCRAM_H
#define __THROTTLESCRAM_H

#include "Instrument.h"

class Scout;

class ThrottleScram: public PanelElement {
public:
	ThrottleScram (VESSEL3 *v);
	void AddMeshData2D (MESHHANDLE hMesh, DWORD grpidx);
	void Reset2D ();
	bool Redraw2D (SURFHANDLE surf);
	bool ProcessMouse2D (int event, int mx, int my);

private:
	Scout *dg;
	float ppos[2];
};

#endif // !__THROTTLESCRAM_H