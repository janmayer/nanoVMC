#include "SensitiveDetector.h"
#include <TVirtualMC.h>
#include <iostream>

SensitiveDetector::SensitiveDetector(std::string absorberVolName)
    : fEdep(0.)
    , fAbsorberVolName(std::move(absorberVolName))
    , fAbsorberVolId(0)
{
}

SensitiveDetector::SensitiveDetector()
    : SensitiveDetector("")
{
}


void SensitiveDetector::Initialize() { fAbsorberVolId = gMC->VolId(fAbsorberVolName.c_str()); }

Bool_t SensitiveDetector::ProcessHits()
{
    Int_t copyNo; // Useless
    const Int_t id = gMC->CurrentVolID(copyNo);
    if (id != fAbsorberVolId)
    {
        return false;
    }

    fEdep += gMC->Edep();

    return true;
}

void SensitiveDetector::EndOfEvent() { fEdep = 0.; }
