/*
 * Parameters.h
 *
 *  Created on: 5 May 2015
 *      Author: thomas
 */

#ifndef CORE_PARAMETERS_H_
#define CORE_PARAMETERS_H_

#include "../User/UserParameters.h"
#include "../Mesh/SingleBlock/Node2D.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>

//#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
// include this header to serialize vectors
#include <boost/serialization/vector.hpp>
// include this header to serialize string
#include <boost/serialization/string.hpp>

/*
 *
 */


using namespace std;

//General enumeration
enum parralleltype {Serial,Mpi,Openmp,Hybrid};
enum OutputFormat {CGNSFormat,TecplotFormat};
enum DensityExport{Density,NormalDensity,BothDensity};

//Solver enumeration
namespace SolverEnum
{
	enum dimension {D2,D3};
	enum schemetype {Q9,Q16};
	enum modeltype {SinglePhase, ColourFluid};
	enum fluidmodel {Compressible, Incompressible,DensityRatio};
	enum variablesSolver{Density,VelocityX,VelocityY,VelocityZ,RhoN};
	enum PatchType {Wall, Periodic, Velocity, Symmetry, Pressure};
}
//model enumeration
namespace ModelEnum
{
	enum FluidType{Newtonian};
	enum UserForceType{None,LocalForce,BodyForce};
	enum GradientType{FD,LBMStencil};
	enum ExtrapolationType{NoExtrapol,TailorExtrapol,WeightDistanceExtrapol};
	enum InterpolationType{NoInterpol,LinearInterpol,LinearLeastSquareInterpol};
}
//Boundary conditions enumeration

enum WallType {BounceBack, HalfWayBounceBack, Diffuse, Specular,HeZouWall,HeZouWallVel};
enum PressureModel{HeZouP};
enum PressureType{FixP,zeroPGrad1st};
enum VelocityModel{HeZouV,Ladd};
enum VelocityType{FixV,zeroVGrad1st};
enum CornerModel{HoChan};
enum CornerPressureType{FixCP,ExtrapolCP,LocalCP};
enum PeriodicType{Simple,PressureForce};

//Two phases enumeration
namespace ContactAngleEnum{
	enum TetaType{NoTeta, UniformTeta, UserTeta};
	enum TetaModel{Standard,Interpol};
	enum ExtrapolNormal{yes,no};
	enum SwitchSelect{Binary,Linear};
	enum ExtrapolationType{NoExtrapol,TailorExtrapol,WeightDistanceExtrapol};
	enum InterpolationType{NoInterpol,LinearInterpol,LinearLeastSquareInterpol};
}
enum ViscosityType{ConstViscosity,LinearViscosity,HarmonicViscosity};
//Colour fluid enumeration
namespace ColourFluidEnum{
	enum ColourGradType{Gunstensen,DensityGrad,DensityNormalGrad};
	enum RecolouringType{LatvaKokkoRothman,LatvaKokkoRothmanEstimator};
	enum ColourOperatorType {Grunau,Reis,SurfaceForce};
}
namespace PorousMediaEnum{
	enum HeleShawBodyForce{no,SinglePhase,TwoPhases};
}
class PorousMediaParameters{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(porousmediacase)
		& BOOST_SERIALIZATION_NVP(calculatePorosity)
		& BOOST_SERIALIZATION_NVP(calculateProductionRate)
		& BOOST_SERIALIZATION_NVP(calculatePermeability)
		& BOOST_SERIALIZATION_NVP(calculateDarcyPermeability)
		& BOOST_SERIALIZATION_NVP(LenghtMedia)
		& BOOST_SERIALIZATION_NVP(SectionMedia)
		& BOOST_SERIALIZATION_NVP(MinX)
		& BOOST_SERIALIZATION_NVP(MaxX)
		& BOOST_SERIALIZATION_NVP(MinY)
		& BOOST_SERIALIZATION_NVP(MaxY)
		& BOOST_SERIALIZATION_NVP(MinZ)
		& BOOST_SERIALIZATION_NVP(MaxZ)
		& BOOST_SERIALIZATION_NVP(HeleShaw)
		& BOOST_SERIALIZATION_NVP(depth);
	}
public:
	void PorousMediaCase(bool porousmediacase_) { porousmediacase=porousmediacase_;};
	void CalculatePorosity(bool calculatePorosity_)  { calculatePorosity=calculatePorosity_;};
	void CalculateProductionRate(bool calculateProductionRate_)  { calculateProductionRate=calculateProductionRate_;};
	void CalculatePermeability(bool calculatePermeability_ )  { calculatePermeability=calculatePermeability_;};
	void CalculateDarcyPermeability(bool calculateDarcyPermeability_ )  { calculateDarcyPermeability=calculateDarcyPermeability_;};
	bool IsPorousMediaCase() const {return porousmediacase;};
	bool IsCalculatePorosity() const {return calculatePorosity;};
	bool IsCalculateProductionRate() const {return calculateProductionRate;};
	bool IsCalculatePermeability() const {return calculatePermeability;};
	bool IsCalculateDarcyPermeability() const {return calculateDarcyPermeability;};
	void Set_LenghtMedia(double lenghtIn){LenghtMedia=lenghtIn;};
	double Get_LenghtMedia()const {return LenghtMedia;};
	void Set_SectionMedia(double sectionIn){SectionMedia=sectionIn;};
	double Get_SectionMedia()const {return SectionMedia;};
	void Set_PositionMedia(unsigned int minX,unsigned int maxX,unsigned int minY,unsigned int maxY,unsigned int minZ=0,unsigned int maxZ=0);
	void Get_PositionMedia(unsigned int &minX,unsigned int &maxX,unsigned int &minY,unsigned int &maxY,unsigned int &minZ,unsigned int &maxZ);
	void Set_HeleShawBodyForce(PorousMediaEnum::HeleShawBodyForce HeleShawIn){HeleShaw=HeleShawIn; if(HeleShaw!=PorousMediaEnum::no) porousmediacase=true;};
	PorousMediaEnum::HeleShawBodyForce Get_HeleShawBodyForce()const {return HeleShaw;};
	void Set_Depth(double depthIn){depth=depthIn;};
	double Get_Depth()const {return depth;};
protected:
	bool porousmediacase;
	bool calculatePorosity;
	bool calculateProductionRate;
	bool calculatePermeability,calculateDarcyPermeability;
	double LenghtMedia,SectionMedia;
	int MinX,MaxX,MinY,MaxY,MinZ,MaxZ;
	PorousMediaEnum::HeleShawBodyForce HeleShaw;
	double depth;
};
class ColourFluid{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(beta)
		& BOOST_SERIALIZATION_NVP(RhoLimiter)
		& BOOST_SERIALIZATION_NVP(GNormLimiter)
		 & BOOST_SERIALIZATION_NVP(A1)
		 & BOOST_SERIALIZATION_NVP(A2)
		 & BOOST_SERIALIZATION_NVP(Atau)
		 & BOOST_SERIALIZATION_NVP(ColourGrad)
		 & BOOST_SERIALIZATION_NVP(Recolouring)
		 & BOOST_SERIALIZATION_NVP(ColourOperator)
		 & BOOST_SERIALIZATION_NVP(ColourExtrapolNoramlDensity)
		 & BOOST_SERIALIZATION_NVP(ColourExtrapolNoramlInterface)
		 & BOOST_SERIALIZATION_NVP(RedDensityOutput)
		 & BOOST_SERIALIZATION_NVP(BlueDensityOutput)
		 & BOOST_SERIALIZATION_NVP(SurfaceForceOutput)
		 & BOOST_SERIALIZATION_NVP(CurvatureOutput)
		 & BOOST_SERIALIZATION_NVP(ColourGradientOutput)
		 & BOOST_SERIALIZATION_NVP(NormColourGradientOutput);
	}
public:
	void Set_Beta(double beta_=0.7){beta=beta_;};
	double Get_Beta() const{return beta;};
	void Set_RhoLimiter(double RhoLimiter_=1e-07){RhoLimiter=RhoLimiter_;};
	double Get_RhoLimiter(){return RhoLimiter;};
	void Set_ColourGradLimiter(double GNormLimiter_=0.01){GNormLimiter=GNormLimiter_;};
	double Get_ColourGradLimiter(){return GNormLimiter;};
	void Set_ATau(double ATau_=0){Atau=ATau_;};
	double Get_ATau() const{return Atau;};
	double Convert_SigmaToATau(double Sigma=0, double latticeSpeed=1){return 9.0*Sigma/(4.0*latticeSpeed*latticeSpeed);};
	void Set_A1(double A_=0){A2=A_;};
	double Get_A1() const{return A2;};
	void Set_A2(double A_=0){A1=A_;};
	double Get_A2() const{return A1;};
	void Set_AlphaB(double Alphab_=0.2) {Alphab=Alphab_;};
	double Get_AlphaB() const{return Alphab;};
	void Set_DensityRatio(double DensityRatio_=1.0) {DensityRatio=DensityRatio_;};
	double Get_DensityRatio() const{return DensityRatio;};	
	void Set_ColourGradType(ColourFluidEnum::ColourGradType type){ColourGrad=type;};
	ColourFluidEnum::ColourGradType Get_ColourGradType(){return ColourGrad;};
	void Set_RecolouringType(ColourFluidEnum::RecolouringType type){Recolouring=type;};
	ColourFluidEnum::RecolouringType Get_RecolouringType(){return Recolouring;};
	void Set_ColourOperatorType(ColourFluidEnum::ColourOperatorType type){ColourOperator=type;};
	ColourFluidEnum::ColourOperatorType Get_ColourOperatorType(){return ColourOperator;};
	void Set_ColourExtrapolNoramlDensity(bool extrapol){if(extrapol==true) ColourExtrapolNoramlDensity=true; else ColourExtrapolNoramlDensity=false;};
	bool Get_ColourExtrapolNoramlDensity(){return ColourExtrapolNoramlDensity;};
	void Set_ColourExtrapolNoramlInterface(bool extrapol){if(extrapol==true) ColourExtrapolNoramlInterface=true; else ColourExtrapolNoramlInterface=false;};
	bool Get_ColourExtrapolNoramlInterface(){return ColourExtrapolNoramlInterface;};
	void Set_RedDensityOutput(bool RedDensityOutput_=false){RedDensityOutput=RedDensityOutput_;};
	bool Get_RedDensityOutput() const{return RedDensityOutput;};
	void Set_BlueDensityOutput(bool BlueDensityOutput_=false){BlueDensityOutput=BlueDensityOutput_;};
	bool Get_BlueDensityOutput() const{return BlueDensityOutput;};
	void Set_SurfaceForceOutput(bool SurfaceForceOutput_=false){SurfaceForceOutput=SurfaceForceOutput_;};
	bool Get_SurfaceForceOutput() const{return SurfaceForceOutput;};
	void Set_CurvatureOutput(bool CurvatureOutput_=false){CurvatureOutput=CurvatureOutput_;};
	bool Get_CurvatureOutput() const{return CurvatureOutput;};
	void Set_ColourGradientOutput(bool ColourGradientOutput_=false){ColourGradientOutput=ColourGradientOutput_;};
	bool Get_ColourGradientOutput() const{return ColourGradientOutput;};
	void Set_NormColourGradientOutput(bool NormColourGradientOutput_=false){NormColourGradientOutput=NormColourGradientOutput_;};
	bool Get_NormColourGradientOutput() const{return NormColourGradientOutput;};


protected:
	double beta,RhoLimiter,GNormLimiter;
	double A1,A2,Atau,Alphab,DensityRatio;
	ColourFluidEnum::ColourGradType ColourGrad;
	ColourFluidEnum::RecolouringType Recolouring;
	ColourFluidEnum::ColourOperatorType ColourOperator;
	bool ColourExtrapolNoramlDensity,ColourExtrapolNoramlInterface;
	bool RedDensityOutput,BlueDensityOutput,SurfaceForceOutput,CurvatureOutput,ColourGradientOutput,NormColourGradientOutput;
};

class MultiphaseModels: public ColourFluid{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(tension)
		 & BOOST_SERIALIZATION_NVP(NormalDensityOutput)
		 & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ColourFluid);
	}
public:
	void Set_SurfaceTension(double tension_=0){tension=tension_;};
	double Get_SurfaceTension() const{return tension;};
	void Set_NormalDensityOutput(bool NormalDensityOutput_=false){NormalDensityOutput=NormalDensityOutput_;};
	bool Get_NormalDensityOutput() const{return NormalDensityOutput;};
	void Set_NormalOutput(bool NormalOutput_=false){NormalOutput=NormalOutput_;};
	bool Get_NormalOutput() const{return NormalOutput;};
protected:
	bool NormalDensityOutput,NormalOutput;
	double tension;
};
class MeshParameters {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(nx)
		   & BOOST_SERIALIZATION_NVP(ny)
		   & BOOST_SERIALIZATION_NVP(nz)
		   & BOOST_SERIALIZATION_NVP(dimension_)
		   & BOOST_SERIALIZATION_NVP(MeshFile)
		   & BOOST_SERIALIZATION_NVP(NbNodes);
	}
public:
	void Set_Dimension(SolverEnum::dimension dim_);
	SolverEnum::dimension Get_Dimension() const;
	void set_MeshParameters();
	void Set_Domain_Size(int nx_=1,int ny_=1,int nz_=1);
	int Get_Nx() const;
	int Get_Ny() const;
	int Get_Nz() const;
	int Get_NbNodes() const;
	void Set_MeshFile(std::string MeshFile_);
	std::string Get_MeshFile() const;
protected:
	int nx,ny,nz;
	SolverEnum::dimension dimension_; //2D or 3D
	std::string MeshFile;
	int NbNodes;
};

class ModelsParameters:public MultiphaseModels {
public:
//Single phase
	void Set_Rho(double Rho_=1){Rho_1=Rho_;};
	double Get_Rho() const{return Rho_1;};
	void Set_Tau(double Tau_=1){Tau_1=Tau_;};
	double Get_Tau() const{return Tau_1;};
//multiphase
	void Set_Rho_1(double Rho){Rho_1=Rho;};
	double Get_Rho_1() const {return Rho_1;};
	void Set_Rho_2(double Rho){Rho_2=Rho;};
	double Get_Rho_2() const {return Rho_2;};
	void Set_Tau_1(double Tau){Tau_1=Tau;};
	double Get_Tau_1() const {return Tau_1;};
	void Set_Tau_2(double Tau){Tau_2=Tau;};
	double Get_Tau_2() const {return Tau_2;};

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(Rho_1)
		   & BOOST_SERIALIZATION_NVP(Rho_2)
		   & BOOST_SERIALIZATION_NVP(Tau_1)
		   & BOOST_SERIALIZATION_NVP(Tau_2)
		   & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MultiphaseModels);
	}

protected:
	double Rho_1, Rho_2;
	double Tau_1, Tau_2;
};

class PhysicalParameters {
public:
	void Set_deltax(double dx_);
	double Get_deltax() const ;
	void Set_deltat(double dt_){dt=dt_;};
	double Get_deltat() const {return dt;};
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(nu0)
		   & BOOST_SERIALIZATION_NVP(l0)
		   & BOOST_SERIALIZATION_NVP(t0)
		   & BOOST_SERIALIZATION_NVP(Re)
		   & BOOST_SERIALIZATION_NVP(l)
		   & BOOST_SERIALIZATION_NVP(t)
		   & BOOST_SERIALIZATION_NVP(dx)
		   & BOOST_SERIALIZATION_NVP(dt);
	}

protected:
	double nu0, l0,t0;//physical reference values
	double Re,l,t;// non dimension reference values
	double dx,dt; // convert from lattice unit to non dimension value

};

class IniParameters {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(U_ini)
		   & BOOST_SERIALIZATION_NVP(V_ini)
		   & BOOST_SERIALIZATION_NVP(W_ini);
	}

protected:
	double U_ini,V_ini,W_ini;

};

class BoundaryParameters {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(WallTypeParam)
		   & BOOST_SERIALIZATION_NVP(NbGlobalBcType);
		if (NbGlobalBcType==4)
		{
			ar & boost::serialization::make_nvp("GlobalBcType_0",GlobalBcType[0] );
			ar & boost::serialization::make_nvp("GlobalBcType_1",GlobalBcType[1] );
			ar & boost::serialization::make_nvp("GlobalBcType_2",GlobalBcType[2] );
			ar & boost::serialization::make_nvp("GlobalBcType_3",GlobalBcType[3] );
		}
		else
		{
			ar & boost::serialization::make_nvp("GlobalBcType_0",GlobalBcType[0] );
			ar & boost::serialization::make_nvp("GlobalBcType_1",GlobalBcType[1] );
			ar & boost::serialization::make_nvp("GlobalBcType_2",GlobalBcType[2] );
			ar & boost::serialization::make_nvp("GlobalBcType_3",GlobalBcType[3] );
			ar & boost::serialization::make_nvp("GlobalBcType_4",GlobalBcType[4] );
			ar & boost::serialization::make_nvp("GlobalBcType_5",GlobalBcType[5] );
		}
		ar & BOOST_SERIALIZATION_NVP(SymmetryTypeParam)
		   & BOOST_SERIALIZATION_NVP(PressureModelParam)
		   & BOOST_SERIALIZATION_NVP(PressureTypeParam)
		   & BOOST_SERIALIZATION_NVP(VelocityModelParam)
		   & BOOST_SERIALIZATION_NVP(VelocityTypeParam)
		   & BOOST_SERIALIZATION_NVP(CornerModelParam)
		   & BOOST_SERIALIZATION_NVP(CornerPressureTypeParam)
		   & BOOST_SERIALIZATION_NVP(PeriodicTypeParam)
		   & BOOST_SERIALIZATION_NVP(PressureDropParam);
	}
public:
	NodeType Get_GlobalBcType(int side) const;
	void Set_WallType(WallType WallType_);
	WallType Get_WallType() const;
	void Set_SymmetryType(SymmetryType SymmetryType_);
	SymmetryType Get_SymmetryType() const;
	void Set_PressureModel(PressureModel PressureModelParam_){PressureModelParam=PressureModelParam_;};
	PressureModel Get_PressureModel() const {return PressureModelParam;};
	void Set_PressureType(PressureType PressureType_){PressureTypeParam=PressureType_;};
	PressureType Get_PressureType() const {return PressureTypeParam;};
	void Set_VelocityModel(VelocityModel VelocityModel_){VelocityModelParam=VelocityModel_;};
	VelocityModel Get_VelocityModel() const {return VelocityModelParam;};
	void Set_VelocityType(VelocityType VelocityType_){VelocityTypeParam=VelocityType_;};
	VelocityType Get_VelocityType() const {return VelocityTypeParam;};
	void Set_CornerModel(CornerModel CornerModel_){CornerModelParam=CornerModel_;};
	CornerModel Get_CornerModel() const {return CornerModelParam;};
	void Set_CornerPressureType(CornerPressureType CornerPressureType_){CornerPressureTypeParam=CornerPressureType_;};
	CornerPressureType Get_CornerPressureType() const {return CornerPressureTypeParam;};
	void Set_PressureDrop(double PressureDropIn){PressureDropParam=PressureDropIn;};
	double Get_PressureDrop() const {return PressureDropParam;};
	void Set_PeriodicType(PeriodicType Type){PeriodicTypeParam=Type;};
	PeriodicType Get_PeriodicType() const {return PeriodicTypeParam;};
	void Set_CollisionOnWalls(bool collOnWalls){CollisionOnWalls=collOnWalls;};
	bool Get_CollisionOnWalls() const {return CollisionOnWalls;};
protected:
	WallType WallTypeParam;
	SymmetryType SymmetryTypeParam;
	int NbGlobalBcType;
	NodeType * GlobalBcType;
	PressureModel PressureModelParam;
	PressureType PressureTypeParam;
	VelocityModel VelocityModelParam;
	VelocityType VelocityTypeParam;
	CornerModel CornerModelParam;
	CornerPressureType CornerPressureTypeParam;
	PeriodicType PeriodicTypeParam;
	double PressureDropParam;
	bool CollisionOnWalls;
};

class SolverParameters {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(scheme)
		   & BOOST_SERIALIZATION_NVP(model)
		   & BOOST_SERIALIZATION_NVP(FluidModel)
		   & BOOST_SERIALIZATION_NVP(variableError)
		   & BOOST_SERIALIZATION_NVP(fluid)
		   & BOOST_SERIALIZATION_NVP(Gradient)
		   & BOOST_SERIALIZATION_NVP(Extrapol)
		   & BOOST_SERIALIZATION_NVP(UserForce)
		   & BOOST_SERIALIZATION_NVP(NbVelocities)
		   & BOOST_SERIALIZATION_NVP(cs)
		   & BOOST_SERIALIZATION_NVP(cs2)
		   & BOOST_SERIALIZATION_NVP(deltaT)
		   & BOOST_SERIALIZATION_NVP(deltaX)
		   & BOOST_SERIALIZATION_NVP(ErrorMax)
		   & BOOST_SERIALIZATION_NVP(refDensity)
		   & BOOST_SERIALIZATION_NVP(tetaType)
		   & BOOST_SERIALIZATION_NVP(tetaModel)
		   & BOOST_SERIALIZATION_NVP(NormalExtrapol)
		   & BOOST_SERIALIZATION_NVP(NormalInterpol)
		   & BOOST_SERIALIZATION_NVP(Switchteta)
		   & BOOST_SERIALIZATION_NVP(teta)
		   & BOOST_SERIALIZATION_NVP(nNodesInterpolInSolid)
		   & BOOST_SERIALIZATION_NVP(nNodesInterpolInFluid)
		   & BOOST_SERIALIZATION_NVP(viscosityType)
		   & BOOST_SERIALIZATION_NVP(LpErrorCase)
		   & BOOST_SERIALIZATION_NVP(L1ErrorCase);
	}

public:
	void set_SolverParameters();
	void Set_Scheme(SolverEnum::schemetype scheme_);
	SolverEnum::schemetype Get_Scheme() const;
	void Set_Model(SolverEnum::modeltype model_);
	SolverEnum::modeltype Get_Model() const;
	void Set_ModelOfFluid(SolverEnum::fluidmodel FluidModel_){FluidModel=FluidModel_;};
	SolverEnum::fluidmodel Get_ModelOfFluid() const {return FluidModel;};
	void Set_FluidType(ModelEnum::FluidType fluidtype_){fluid=fluidtype_;};
	ModelEnum::FluidType Get_FluidType() const{return fluid;};
	void Set_UserForceType(ModelEnum::UserForceType UserForceType_){UserForce=UserForceType_;};
	ModelEnum::UserForceType Get_UserForceType() const{return UserForce;};
	void Set_ErrorMax(double ErrorMax_){ErrorMax=ErrorMax_;};
	double Get_ErrorMax(){return ErrorMax;};
	void Set_ErrorVariable(SolverEnum::variablesSolver variableError_){variableError=variableError_;};
	SolverEnum::variablesSolver Get_ErrorVariable(){return variableError;};
	void Set_GradientType(ModelEnum::GradientType GradientType_){Gradient=GradientType_;};
	ModelEnum::GradientType Get_GradientType() const{return Gradient;};
	void Set_ExtrapolationType(ModelEnum::ExtrapolationType ExtrapolationType_){Extrapol=ExtrapolationType_;};
	ModelEnum::ExtrapolationType Get_ExtrapolationType() const{return Extrapol;};
	void Set_ContactAngle(double teta_){teta=teta_;};
	double Get_ContactAngle(){return teta;};
	void Set_ContactAngleType(ContactAngleEnum::TetaType tetaType_){tetaType=tetaType_;};
	ContactAngleEnum::TetaType Get_ContactAngleType(){return tetaType;};
	void Set_ContactAngleModel(ContactAngleEnum::TetaModel tetaModel_){tetaModel=tetaModel_;};
	ContactAngleEnum::TetaModel Get_ContactAngleModel(){return tetaModel;};
	void Set_NormalExtrapolType(ContactAngleEnum::ExtrapolationType NormalExtrapol_){NormalExtrapol=NormalExtrapol_;};
	ContactAngleEnum::ExtrapolationType Get_NormalExtrapolType(){return NormalExtrapol;};
	void Set_NormalInterpolType(ContactAngleEnum::InterpolationType NormalInterpol_){NormalInterpol=NormalInterpol_;};
	ContactAngleEnum::InterpolationType Get_NormalInterpolType(){return NormalInterpol;};
	void Set_NumberOfInterpolNode(int nNodes);
	void Set_NumberOfInterpolNodeInSolid(int nNodes);
	void Set_NumberOfInterpolNodeInFluid(int nNodes);
	int Get_NumberOfInterpolNode(){return nNodesInterpolInSolid+nNodesInterpolInFluid;};
	int Get_NumberOfInterpolNodeInSolid(){return nNodesInterpolInSolid;};
	int Get_NumberOfInterpolNodeInFluid(){return nNodesInterpolInFluid;};
	void Set_SwitchSelectTeta(ContactAngleEnum::SwitchSelect Switchteta_){Switchteta=Switchteta_;};
	ContactAngleEnum::SwitchSelect Get_SwitchSelectTeta(){return Switchteta;};
	void Set_ViscosityType(ViscosityType viscosityType_){viscosityType=viscosityType_;};
	ViscosityType Get_ViscosityType(){return viscosityType;};
	void Set_ReferenceDensity(double refDens){refDensity=refDens;};
	double Get_ReferenceDensity(){return refDensity;};
	int Get_NbVelocities() const;
	double Convert_TauToNu(double Tau_){return (Tau_-0.5)*cs2*deltaT;};
	double Convert_MutoNu(double mu_,double rho){return mu_/rho;};
	double Convert_NutoMu(double nu_,double rho){return nu_*rho;};
	double Convert_NuToTau(double nu_){return nu_/(cs2*deltaT)+0.5;};

	double Get_cs() const {return cs;};
	double Get_cs2() const {return cs2;};
	double Get_deltaT() const {return deltaT;};
	double Get_deltaX() const {return deltaX;};
	double Get_LatticeSpeed() const {return deltaX/deltaT;};
	void Set_deltaX(double deltaX_) { deltaX=deltaX_;};
	void Set_deltaT(double deltaT_) { deltaT=deltaT_;};

	void SetErrorLpCase(bool Is){LpErrorCase=Is;};
	bool IsLpErrorCase(){return LpErrorCase;};
	void SetErrorL1Case(bool Is){L1ErrorCase=Is;};
	bool IsL1ErrorCase(){return L1ErrorCase;};

protected:
	SolverEnum::schemetype scheme;
	SolverEnum::modeltype model;
	SolverEnum::fluidmodel FluidModel;
	SolverEnum::variablesSolver variableError;
	ModelEnum::FluidType fluid;
	ModelEnum::GradientType Gradient;
	ModelEnum::ExtrapolationType Extrapol;
	ModelEnum::UserForceType UserForce;
	int NbVelocities;
	double cs,cs2;
	double deltaT,deltaX;
	double ErrorMax;
	double refDensity;

	ContactAngleEnum::TetaType tetaType;
	ContactAngleEnum::TetaModel tetaModel;
	ContactAngleEnum::ExtrapolationType NormalExtrapol;
	ContactAngleEnum::InterpolationType NormalInterpol;
	ContactAngleEnum::SwitchSelect Switchteta;
	double teta;
	int nNodesInterpolInSolid,nNodesInterpolInFluid;
	ViscosityType viscosityType;

	bool LpErrorCase;
	bool L1ErrorCase;



};

class CalculationParameters {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(parrallel)
		& BOOST_SERIALIZATION_NVP(Format)
		   & BOOST_SERIALIZATION_NVP(NbSteps)
		   & BOOST_SERIALIZATION_NVP(IntervalOutput)
		   & BOOST_SERIALIZATION_NVP(IntervalListing)
		   & BOOST_SERIALIZATION_NVP(NbVariablesOutput)
		   & BOOST_SERIALIZATION_NVP(OutputFileName)
		   & BOOST_SERIALIZATION_NVP(density)
		   & BOOST_SERIALIZATION_NVP(pressure)
		   & BOOST_SERIALIZATION_NVP(velocity);
		/*  ar & BOOST_SERIALIZATION_NVP(argc)
		   & BOOST_SERIALIZATION_NVP(argv);*/
	}
public:
	void Set_OutputFormat(OutputFormat OutputFormat_) {Format=OutputFormat_;};
	OutputFormat Get_OutputFormat(){return Format;};
	std::string Get_OutputFileName() const;
	void Set_OutputFileName(std::string string_);
	void Set_Parallel(parralleltype parrallel_);
	parralleltype Get_Parallel() const;
	std::string* Get_PtrVariablesOutput() const;
	int Get_NbVariablesOutput() const;
	void Set_NbStep(int NbStep_);
	int Get_NbStep() const;
	void Set_OutPutNSteps(int NbStep_);
	int Get_OutPutNSteps() const;
	void Set_listing(int IntervalListning);
	int Get_listing() const;
	bool Get_output_density() const {return density;};
	bool Get_output_pressure() const {return pressure;};
	bool Get_output_velocity() const {return velocity;};
protected:
	void Set_VariablesOutput(int nbvar, std::string * strinput);
protected:
	parralleltype parrallel;
	int *argc;
	char ***argv;
	OutputFormat Format;
	int NbSteps, IntervalOutput,IntervalListing;
	std::string *VariablesOutput;
	int NbVariablesOutput;
	std::string OutputFileName;
	bool density,velocity,pressure;
};
class RestartParameters {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(restart);
		ar & BOOST_SERIALIZATION_NVP(RestartFile);
		ar & BOOST_SERIALIZATION_NVP(InitFromFile);
		ar & BOOST_SERIALIZATION_NVP(NbVariablesInitFromFile);
		ar & BOOST_SERIALIZATION_NVP(NameInitFromFile);
		ar & BOOST_SERIALIZATION_NVP(VariableInitFromFile);
	}
public:
	void set_RestartParameters();
	bool IsInitFromFile() const {return InitFromFile;};
	int Get_NumberVariableToInit() const {return NbVariablesInitFromFile;};
	std::string Get_FileNameToInit(int IdVariable) const {return NameInitFromFile[IdVariable];};
	std::string Get_VariableNameToInit(int IdVariable) const {return VariableInitFromFile[IdVariable];};


protected:
	bool restart;
	std::string RestartFile;
	bool InitFromFile;
	int NbVariablesInitFromFile;
	std::vector<std::string> NameInitFromFile;
	std::vector<std::string> VariableInitFromFile;
};
class Parameters :
		public UserParameters,
		public MeshParameters,
		public ModelsParameters,
		public PhysicalParameters,
		public IniParameters,
		public BoundaryParameters,
		public SolverParameters,
		public CalculationParameters,
		public RestartParameters,
		public PorousMediaParameters
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(UserParameters);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MeshParameters);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ModelsParameters);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PhysicalParameters);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(IniParameters);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BoundaryParameters);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(SolverParameters);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CalculationParameters);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(RestartParameters);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PorousMediaParameters);
		ar & BOOST_SERIALIZATION_NVP(verbous);
	}
public:
	Parameters();
	virtual ~Parameters();

	void Change_Dimension(SolverEnum::dimension dim_);
	void Set_BcType(NodeType Bc0,NodeType Bc1,NodeType Bc2,NodeType Bc3,NodeType Bc4=Wall,NodeType Bc5=Wall);
	void Add_VariableToInit(std::string filename,SolverEnum::variablesSolver variablesSolvertype);

	void Set_Arguments(int *argc_,char ***argv_,bool verbous=false);

	int* Get_Argc() const;
	char*** Get_Argv() const;
	bool Get_Verbous() const;

	void Set_VariablesOutput(bool Rho, bool U, bool P){density=Rho;velocity=U;pressure=P;};

	double Convert_SigmaToATau(){return ColourFluid::Convert_SigmaToATau(Get_SurfaceTension(),Get_LatticeSpeed());};
	//void Save_Parameters();
	//void Load_Parameters();

	void CheckParameters();

private:
	bool verbous;

};

#endif /* CORE_PARAMETERS_H_ */
