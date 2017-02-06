#ifndef TRGEMANALYSIS_HH
#define TRGEMANALYSIS_HH 1

#include "globals.hh"
#include <vector>

class G4Run;
class G4Event;
class G4ParticleDefinition;
class TFile;
class TH1D;
class TNtuple;
class TTree;

class TrGEMAnalysis {

   public:

      static TrGEMAnalysis* GetInstance();
      ~TrGEMAnalysis();

      void PrepareNewEvent(const G4Event* anEvent);
      void PDGHisto(std::vector<G4double> PDGvector) ;
      void EndOfEvent(const G4Event* anEvent);
      void PrepareNewRun(const G4Run* aRun);
      void EndOfRun(const G4Run* aRun);
      void AddSecondary(const G4ParticleDefinition* part);
      void AddGapSecondary(const G4ParticleDefinition* part, G4int gapNum);
      void AddEDep(G4double edep, G4double z);
      void AddEDepSD(G4double z, G4int copyno);
      //void SetEcalZposition(G4double val) { eCalZposition = val; };
      void SetBeam(const G4ParticleDefinition* part, G4double energy);
      //void CreateBranch(G4String name, G4int evtNo, G4String type) ;
      void AddParticlesPerEvent(G4int PDGCode) ;
      void SetDriftSensitivity(G4double someDriftEdep) ;
      void SetTransferSensitivity(G4double someTransferEdep) ;
      void SetNeutronSensitivity(G4bool someBool) ;
      void SaveStepProcess(int process, std::string volume) ;
      void SaveGarfieldQuantities(
	    G4double aGlobalTime,
	    G4int aPdgCode,
	    G4double aKineticEnergy,
	    G4double aPositionX, 
	    G4double aPositionY, 
	    G4double aPositionZ,
	    G4double aMomentumX, 
	    G4double aMomentumY, 
	    G4double aMomentumZ,
	    G4double aMomentumDirectionX, 
	    G4double aMomentumDirectionY, 
	    G4double aMomentumDirectionZ) ;



   private:

	 TrGEMAnalysis();
	 static TrGEMAnalysis* singleton;

	 bool isNewEvent ;
	 G4int eventCounter ;

	 // beam and calorimeter geometry
	 const G4ParticleDefinition* beamParticle;
	 G4double beamEnergy;
	 //G4double eCalZposition;

	 // simple analysis parameters
	 G4double thisEventTotEM;
	 G4double thisEventCentralEM;
	 G4double thisRunTotEM;
	 G4double thisRunTotEM2;
	 G4double thisRunCentralEM;
	 G4double thisRunCentralEM2;

	 // counters
	 G4int thisEventSecondaries;
	 G4int n_gamma;
	 G4int n_electron;
	 G4int n_positron;
	 G4int n_gapGamma[4];
	 G4int n_gapElectron[4];
	 G4int n_gapPositron[4];

	 //const G4int kMaxTrack ;
	 G4int elexevt ;
	 G4int posxevt ;
	 G4int gammaxevt ;
	 G4int secoxevt ;
	 G4bool driftSensitivity ;
	 G4bool transferSensitivity ;
	 G4double driftEdep ;
	 G4double transferEdep ;
	 std::vector<std::string> vecProcess ;
	 std::vector<std::string>* pVecProcess ;
	 std::vector<std::string> vecVolume ;
	 std::vector<std::string>* pVecVolume ;
	 G4int vecProcNo ;
	 G4bool neutronSensitivity ;

	 // GARFIELD quantities
	 G4double globalTime ;
	 G4int pdgCode ;
	 G4double kineticEnergy ;
	 G4double positionX ;
	 G4double positionY ;
	 G4double positionZ ;
	 G4double momentumX ;
	 G4double momentumY ;
	 G4double momentumZ ;
	 G4double momentumDirectionX ;
	 G4double momentumDirectionY ;
	 G4double momentumDirectionZ ;

	 // ROOT objects
	 TFile*    m_ROOT_file;
	 TH1D*     m_ROOT_histo0;
	 //TH1D*     m_ROOT_histo1;
	 TH1D*     m_ROOT_histo2;
	 TH1D*     m_ROOT_histo3;
	 //TNtuple*  ntuple;
	 TTree     *t ;
	 TTree     *g ;

};

#endif /* TRGEMANALYSIS_HH */
