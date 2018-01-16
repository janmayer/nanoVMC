#include "SensitiveDetector.h"
#include <TVirtualMC.h>
#include <iostream>

SensitiveDetector::SensitiveDetector(std::string absorberVolName)
    : fEdep(0.)
    , fAbsorberVolName(std::move(absorberVolName))
    , fAbsorberVolId(0)
    , fVerboseLevel(1)
{
}

void SensitiveDetector::Initialize() { fAbsorberVolId = gMC->VolId(fAbsorberVolName.c_str()); }

Bool_t SensitiveDetector::ProcessHits()
{
    Int_t copyNo;
    const Int_t id = gMC->CurrentVolID(copyNo);

    if (id != fAbsorberVolId)
    {
        return false;
    }

    fEdep += gMC->Edep();

    return true;
}

void SensitiveDetector::EndOfEvent()
{
    if (fVerboseLevel > 1)
        Print();
    // Reset the accumulated values.
    fEdep = 0.;
}

void SensitiveDetector::Print(Option_t*) const
{
    std::cout << "Edep in this event [MeV]: " << fEdep * 1e+03 << std::endl;
}
