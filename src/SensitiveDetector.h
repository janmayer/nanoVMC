#ifndef TGEOTET_VMCDEMO_SENSITIVEDETECTOR_H
#define TGEOTET_VMCDEMO_SENSITIVEDETECTOR_H

#include "TObject.h"
#include <string>

class SensitiveDetector : public TObject
{
  public:
    explicit SensitiveDetector(std::string absorberVolName);
    SensitiveDetector()           = default;
    ~SensitiveDetector() override = default;

    void Initialize();
    Bool_t ProcessHits();
    void EndOfEvent();
    void Print(Option_t* option = "") const override;

    inline void SetVerboseLevel(Int_t level) { fVerboseLevel = level; }

    inline Double_t GetEdep() const { return fEdep; }

  private:
    Double_t fEdep;
    std::string fAbsorberVolName;
    Int_t fAbsorberVolId;
    Int_t fVerboseLevel;

    ClassDefOverride(SensitiveDetector, 1)
};

#endif // TGEOTET_VMCDEMO_SENSITIVEDETECTOR_H
