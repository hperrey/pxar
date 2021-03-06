#ifndef CONFIGPARAMETERS
#define CONFIGPARAMETERS

#include "pxardllexport.h"

/** Cannot use stdint.h when running rootcint on WIN32 */
#if ((defined WIN32) && (defined __CINT__))
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
#undef __GNUC__
typedef char int8_t; 
#else

#ifdef __CINT__
#undef __GNUC__
typedef char __signed;
typedef char int8_t; 
#endif

#include <stdint.h>
#endif

#include <string>
#include <sstream>
#include <vector>

#include "api.h"

struct gainPedestalParameters {
  double p0, p1, p2, p3; 
};


class DLLEXPORT ConfigParameters {
public:
  ConfigParameters();
  ConfigParameters(std::string filename);

  void initialize();
  bool readConfigParameterFile(std::string filename);
  void readAllConfigParameterFiles();
  void readRocPixelConfig();
  void readTbParameters();
  void readRocDacs();
  void readTbmDacs();

  
  void writeAllFiles();
  bool writeConfigParameterFile();
  // NB: if you add a variable name after the second argument, the dictionary will not compile anymore??!?!
  bool writeDacParameterFile(int iroc, std::vector<std::pair<std::string, uint8_t> > );
  bool writeTrimFile(int iroc, std::vector<pxar::pixelConfig> );
  bool writeTbmParameterFile(int itbm, std::vector<std::pair<std::string, uint8_t> > );
  bool writeTbParameterFile();
  bool writeTestParameterFile(std::string test="all");

  template <typename T1, typename T2> std::string dumpParameters(std::vector<std::pair<T1, T2> > v);
  static ConfigParameters* Singleton();

  std::string getTBParameterFileName()    {return fTBParametersFileName;}
  std::string getDACParameterFileName()   {return fDACParametersFileName;}
  std::string getTbmParameterFileName()   {return fTbmParametersFileName;}
  std::string getTrimParameterFileName()  {return fTrimParametersFileName;}
  std::string getTestParameterFileName()  {return fTestParametersFileName;}
  std::string getGainPedestalParameterFileName()  {return fGainPedestalParameterFileName;}
  std::string getRootFileName()           {return fRootFileName;}
  std::string getLogFileName()            {return fLogFileName;}
  std::string getMaskFileName()           {return fMaskFileName;}
  std::string getDebugFileName()          {return fDebugFileName;}
  std::string getDirectory()              {return fDirectory;}
  std::string getRocType()                {return fRocType;}
  std::string getTbmType()                {return fTbmType;}

  std::vector<std::pair<std::string,uint8_t> >  getTbParameters();
  std::vector<std::pair<std::string,double> >  getTbPowerSettings();
  std::vector<std::pair<std::string,uint8_t> >  getTbSigDelays();
  std::vector<std::pair<uint16_t,uint8_t> >  getTbPgSettings();
  std::vector<std::vector<std::pair<std::string, uint8_t> > > getTbmDacs();
  std::vector<std::vector<std::pair<std::string, uint8_t> > > getRocDacs();
  std::vector<std::string> getDacs();
  std::vector<std::pair<std::string, uint8_t> > readDacFile(std::string fname);
  void readTrimFile(std::string fname, std::vector<pxar::pixelConfig>&);
  std::vector<std::vector<std::pair<int, int> > > readMaskFile(std::string fname);
  std::vector<std::vector<pxar::pixelConfig> > getRocPixelConfig();
  std::vector<pxar::pixelConfig> getRocPixelConfig(int i);

  bool setTbParameter(std::string, uint8_t);
  bool setTbPowerSettings(std::string, double);
  bool setTbmDac(std::string var, uint8_t val, int itbm = -1);
  bool setRocDac(std::string var, uint8_t val, int iroc = -1);
  bool setTrimBits(int trim); 

  void setTBParameterFileName(std::string filename) {fTBParametersFileName = filename;}
  void setDACParameterFileName(std::string filename) {fDACParametersFileName = filename;}
  void setTbmParameterFileName(std::string filename) {fTbmParametersFileName = filename;}
  void setTrimParameterFileName(std::string filename) {fTrimParametersFileName = filename;}
  void setTestParameterFileName(std::string filename) {fTestParametersFileName = filename;}
  void setRootFileName(std::string filename) {fRootFileName = filename;}
  void setLogFileName(std::string filename) {fLogFileName = filename;}
  void setDebugFileName(std::string filename) {fMaskFileName = filename;}
  void setMaskFileName(std::string filename) {fDebugFileName = filename;}
  void setDirectory(std::string dirname) {fDirectory = dirname;}

  void setGuiMode(bool a) {fGuiMode = a;}

  unsigned int getNrocs() {return fnRocs;}
  unsigned int getNtbms() {return fnTbms;}
  std::vector<int> getSelectedRocs() {return fSelectedRocs;}
  std::vector<int> getSelectedTbms() {return fSelectedTbms;}
  void setSelectedRocs(std::vector<int> v) {fSelectedRocs = v;}
  void setSelectedTbms(std::vector<int> v) {fSelectedTbms = v;}

  void readGainPedestalParameters(); 
  void writeGainPedestalParameters(); 
  void setGainPedestalParameters(std::vector<std::vector<gainPedestalParameters> >); 
  std::vector<std::vector<gainPedestalParameters> > getGainPedestalParameters(); 

  double getIa() {return ia;}
  double getId() {return id;}
  double getVa() {return va;}
  double getVd() {return vd;}
  bool   getHvOn() {return fHvOn;}

  uint8_t getHubId() {return fHubId;}

private:

  bool fReadTbParameters, fReadTbmParameters, fReadDacParameters, fReadRocPixelConfig;
  std::vector<std::pair<std::string, uint8_t> > fTbParameters;
  std::vector<std::pair<std::string, double> > fTbPowerSettings;
  std::vector<std::pair<uint16_t, uint8_t> > fTbPgSettings;
  std::vector<std::vector<std::pair<std::string, uint8_t> > > fTbmParameters, fDacParameters; 
  std::vector<std::vector<pxar::pixelConfig> > fRocPixelConfigs; 
  std::vector<int> fSelectedRocs, fSelectedTbms;

  std::vector<std::vector<gainPedestalParameters> > fGainPedestalParameters;

  unsigned int fnCol, fnRow, fnRocs, fnTbms, fnModules, fHubId;
  int fCustomModule, fHalfModule;
  int fEmptyReadoutLength, fEmptyReadoutLengthADC, fEmptyReadoutLengthADCDual, fTbmChannel;
  float ia, id, va, vd;
  float rocZeroAnalogCurrent;
  std::string fRocType, fTbmType;
  std::string fDirectory;
  std::string fTBName;
  bool fHvOn, fTbmEnable, fTbmEmulator, fKeithleyRemote, fGuiMode;

  std::string fTBParametersFileName;
  std::string fDACParametersFileName;
  std::string fTbmParametersFileName;
  std::string fTrimParametersFileName;
  std::string fTestParametersFileName;
  std::string fRootFileName;
  std::string fLogFileName;
  std::string fMaskFileName;
  std::string fDebugFileName;
  std::string fGainPedestalParameterFileName; 

  static ConfigParameters* fInstance;

};

// ----------------------------------------------------------------------
template <typename T1, typename T2> std::string ConfigParameters::dumpParameters(std::vector<std::pair<T1, T2> > v) {
  std::stringstream line;
  for(typename std::vector<std::pair<T1, T2> >::iterator it = v.begin(); it != v.end(); ++it) {
    line << " " << it->first << ": " << static_cast<int>(it->second); 
  }
  return line.str();
}


#endif
