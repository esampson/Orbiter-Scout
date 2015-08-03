// ==============================================================
//                ORBITER MODULE: Scout
//                  Part of the ORBITER SDK
//          Copyright (C) 2001-2008 Martin Schweiger
//                   All rights reserved
//
// ThrottleHover.h
// Hover throttle sliders
// ==============================================================

#ifndef __THROTTLEHOVER_H
#define __THROTTLEHOVER_H

#include "Instrument.h"

class Scout;

class ThrottleHover: public PanelElement {
public:
	ThrottleHover (VESSEL3 *v);
	void AddMeshData2D (MESHHANDLE hMesh, DWORD grpidx);
	void Reset2D ();
	bool Redraw2D (SURFHANDLE surf);
	bool ProcessMouse2D (int event, int mx, int my);

private:
	Scout *dg;
	float ppos;
};

#endif // !__THROTTLEHOVER_H