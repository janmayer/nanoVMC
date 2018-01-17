#ifndef NANOVMC_SENSITIVEDETECTOR_H
#define NANOVMC_SENSITIVEDETECTOR_H

#include "TObject.h"
#include <string>

class SensitiveDetector : public TObject
{
  public:
    explicit SensitiveDetector(std::string absorberVolName);
    SensitiveDetector();
    ~SensitiveDetector() override = default;

    void Initialize();
    Bool_t ProcessHits();
    void EndOfEvent();

    inline Double_t GetEdep() const { return fEdep; }

  private:
    Double_t fEdep;
    std::string fAbsorberVolName;
    Int_t fAbsorberVolId;

    ClassDefOverride(SensitiveDetector, 1)
};

#endif // NANOVMC_SENSITIVEDETECTOR_H
