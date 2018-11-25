/*
 * UserInitLBM.cpp
 *
 *  Created on: 12 Jun 2015
 *      Author: Thomas Burel
 *
 *  This file is used to initialise the domain for all models (2D, 3D and single or multiphases).
 *  For single phase, Rho is the density, U[0] is Ux, U[1] is Uy and U[2] is Uz
 *  For Multiphase, Rho is the mass fraction (0 <= Rho <= 1), U[0] is Ux, U[1] is Uy and U[2] is Uz
 *  	The mass Fraction (Alpha) is defined as Rho= Rho_1 * Alpha +Rho_2 * (1-Alpha)
 *
 *  Notes: element number is not used at this time and set to 0.
 */

#include "UserInit.h"

UserInit::UserInit() {
	Block_=0;

}

UserInit::~UserInit() {
	// TODO Auto-generated destructor stub
}

void UserInit::UserBc(Parameters& PtrParameters, int elem, int nodenumber, double* pos,double& Rho, double* U, double& alpha){

	double Umax,H,L,Pmax,Pmin;
	double teta,sigma,Diameter,densityratio,Ca;
	PtrParameters.Get_UserParameters(Umax,H,L,Pmax,Pmin);
	PtrParameters.Get_UserDroplets(teta,sigma,Diameter,densityratio,Ca);

	U[0]=0.0;
	U[1]=0.0;
	Rho=2.0;
	alpha=0.0;
	if(pow(pos[0]-(L)/2.0,2.0)+pow(pos[1]-H/2,2.0)<=Diameter*Diameter/4.0+1e-08)
	{
		alpha=1.0;
		Rho*=densityratio;
		Rho+=sigma*2.0/Diameter;
	}

}

void UserInit::UserIc (Parameters& PtrParameters, int elem, int nodenumber, double* pos ,double& Rho, double* U, double& alpha){
	double Umax,H,L,Pmax,Pmin;
	double teta,sigma,Diameter,densityratio,Ca;
	PtrParameters.Get_UserParameters(Umax,H,L,Pmax,Pmin);
	PtrParameters.Get_UserDroplets(teta,sigma,Diameter,densityratio,Ca);


	U[0]=0.0;
	U[1]=0.0;
	Rho=2.0;
	alpha=0.0;
	if(pow(pos[0]-(L)/2.0,2.0)+pow(pos[1]-H/2,2.0)<=Diameter*Diameter/4.0+1e-08)
	{
		alpha=1.0;
		Rho*=densityratio;
		Rho+=sigma*2.0/Diameter;
	}

}

