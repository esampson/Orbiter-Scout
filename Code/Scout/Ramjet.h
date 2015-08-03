// ==============================================================
//                ORBITER MODULE: Scout
//                  Part of the ORBITER SDK
//          Copyright (C) 2001-2008 Martin Schweiger
//                   All rights reserved
//
// Ramjet.h
// Interface for the delta glider ramjet engine
//
// Notes:
// This class only requires a generic VESSEL reference, so it can
// be ported to other vessel classes.
// It is designed to manage all ramjet/scramjet engines of a
// vessel, so only a single instance should be created. Individual
// engines can then be defined by the AddThrusterDefinition method.
// ==============================================================

#ifndef __RAMJET_H
#define __RAMJET_H

#include "Orbitersdk.h"

class Ramjet {
public:
	Ramjet (VESSEL *_vessel);
	// constructor

	~Ramjet ();
	// destructor

	void AddThrusterDefinition (THRUSTER_HANDLE th,
		double Qr, double Ai, double Tb_max, double dmf_max);
	// Add a new thruster definition to the list of engines managed by
	// the Ramjet object. Engine design parameters:
	// Qr: Fuel heating value (FHV) [J/kg]. Value for typical jet fuel
	//     is about 4.5e7. Qr influences the rate at which fuel must be
	//     burned to obtain a given amount of thrust.
	// Ai: Inlet cross section [m^2]. Ai basically scales the size of
	//     the engine, i.e. determines how much thrust it generates and
	//     how much fuel it burns.
	// Tb_max: Maximum burner temperature [K] (due to material limits).
	//     Determines how much thrust can be generated without melting
	//     the engine, and up to what velocity the engine can be
	//     operated. A typical value may be around 2400K.

	void Thrust (double *F) const;
	// calculates the thrust generated by each thruster
	// and returns the force value in the supplied list F
	// On input, F must point to an array of at least the same
	// length as the number of thruster definitions (nthdef)

	inline double DMF (UINT idx) const { return thdef[idx]->dmf; }
	// returns current fuel mass flow of thruster idx

	inline double Temp (UINT idx, UINT which) const { return thdef[idx]->T[which]; }
	// returns diffuser, combustion or exhaust temperature [K] of thruster idx

	double TSFC (UINT idx) const;
	// returns thrust-specific fuel consumption of thruster idx
	// based on last thrust calculation

private:
	VESSEL *vessel;            // vessel pointer
	
	struct THDEF {             // list of ramjet thrusters
		THRUSTER_HANDLE th;    //   thruster handle                -+
		double Qr;             //   fuel heating parameter [J/kg]   | static
		double Ai;             //   air intake cross section [m^2]  | parameters
		double Tb_max;         //   max. burner temperature [K]     |
		double dmf_max;        //   max. fuel flow rate [kg/s]     -+

		double dmf;            //   current fuel mass rate [kg/s]  -+ dynamic
		double F;              //   current thrust [N]              | parameters
		double T[3];           //   temperatures                   -+
	} **thdef;
	UINT nthdef;               // number of ramjet thrusters
};

#endif // !__RAMJET_H