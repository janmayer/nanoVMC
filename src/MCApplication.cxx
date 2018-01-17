#include "MCApplication.h"
#include "MCStack.h"
#include "TFile.h"
#include "TGeoManager.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TVirtualMC.h"
#include <iostream>


MCApplication::MCApplication(std::string geoFileName, std::string outFileName, std::function<void(MCStack*)> generator)
    : fStack(new MCStack(100))
    , fSensitiveDetector("SV")
    , fGeoFileName(std::move(geoFileName))
    , fOutFileName(std::move(outFileName))
    , fGenerator(std::move(generator))
    , fHist("hist", "hist", 10000, 0, 10000)
{
}

MCApplication::~MCApplication() { delete fStack; }

void MCApplication::InitMC(const char* setup)
{
    std::cout << "MCApplication::InitMC" << std::endl;
    /// Initialize MC.
    /// The selection of the concrete MC is done in the macro.
    /// \param setup The name of the configuration macro

    if (TString(setup) != "")
    {
        gROOT->LoadMacro(setup);
        gInterpreter->ProcessLine("Config()");
        if (!gMC)
        {
            Fatal("InitMC", "Processing Config() has failed. (No MC is instantiated.)");
        }
    }

    gMC->SetStack(fStack);
    gMC->Init();
    gMC->BuildPhysics();
}

void MCApplication::RunMC(Int_t nofEvents)
{
    std::cout << "MCApplication::RunMC" << std::endl;
    gMC->ProcessRun(nofEvents);
    FinishRun();
}

void MCApplication::FinishRun()
{
    std::cout << "MCApplication::FinishRun" << std::endl;
    TFile tfile(fOutFileName.c_str(), "RECREATE");
    // fHist->SetD
    fHist.Write();
    tfile.Write();
    tfile.Close();
}

TVirtualMCApplication* MCApplication::CloneForWorker() const
{
    std::cout << "MCApplication::CloneForWorker" << std::endl;
    return new MCApplication();
}

void MCApplication::InitForWorker() const
{
    std::cout << "MCApplication::InitForWorker" << std::endl;
    gMC->SetStack(fStack);
}

void MCApplication::ConstructGeometry()
{
    std::cout << "MCApplication::ConstructGeometry" << std::endl;
    TGeoManager::Import(fGeoFileName.c_str());
    gMC->SetRootGeometry();
}

void MCApplication::InitGeometry()
{
    std::cout << "MCApplication::InitGeometry" << std::endl;
    fSensitiveDetector.Initialize();
}

void MCApplication::GeneratePrimaries()
{
    // std::cout << "MCApplication::GeneratePrimaries" << std::endl;
    fGenerator(fStack);
}

void MCApplication::BeginEvent()
{
    // std::cout << "MCApplication::BeginEvent" << std::endl;
}

void MCApplication::BeginPrimary()
{
    // std::cout << "MCApplication::BeginPrimary" << std::endl;
}

void MCApplication::PreTrack()
{
    // std::cout << "MCApplication::PreTrack" << std::endl;
}

void MCApplication::Stepping() { fSensitiveDetector.ProcessHits(); }

void MCApplication::PostTrack()
{
    // std::cout << "MCApplication::PostTrack" << std::endl;
}

void MCApplication::FinishPrimary()
{
    // std::cout << "MCApplication::FinishPrimary" << std::endl;
}

void MCApplication::FinishEvent()
{
    // std::cout << "MCApplication::FinishEvent" << std::endl;
    fHist.Fill(fSensitiveDetector.GetEdep() * 1e+06); // GeV -> keV
    // fSensitiveDetector.Print();
    fSensitiveDetector.EndOfEvent();
    fStack->Reset();
}
