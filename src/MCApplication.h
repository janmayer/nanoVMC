#ifndef TGEOTET_VMCDEMO_MCAPPLICATION_H
#define TGEOTET_VMCDEMO_MCAPPLICATION_H

#include "MCStack.h"
#include "SensitiveDetector.h"
#include "TH1D.h"
#include "TLorentzVector.h"
#include "TVirtualMCApplication.h"
#include <functional>
#include <string>
#include <vector>

class MCApplication : public TVirtualMCApplication
{
  public:
    explicit MCApplication(std::string geoFileName = "geo.root",
                           std::string outFileName = "out.root",
                           std::function<void(MCStack*)> generator =
                               [](MCStack* stack) {
                                   stack->PushBasicPrimary(22, TLorentzVector(5.e-3, 0., 0., 5.e-3));
                               },
                           const std::vector<std::string>& sensitiveVolumeNames = {"SV"});
    ~MCApplication() override;

    static inline MCApplication* Instance()
    {
        return dynamic_cast<MCApplication*>(TVirtualMCApplication::Instance());
    }

    void InitMC(const char* setup);
    void RunMC(Int_t nofEvents);
    void FinishRun();

    TVirtualMCApplication* CloneForWorker() const override;
    void InitForWorker() const override;
    void ConstructGeometry() override;
    void InitGeometry() override;

    void GeneratePrimaries() override;
    void BeginEvent() override;
    void BeginPrimary() override;
    void PreTrack() override;
    void Stepping() override;
    void PostTrack() override;
    void FinishPrimary() override;
    void FinishEvent() override;

  private:
    MCStack* fStack;
    const std::string fGeoFileName;
    const std::string fOutFileName;
    const std::function<void(MCStack*)> fGenerator;
    std::vector<SensitiveDetector> fSensitiveDetectors;
    std::vector<TH1D> fHistograms;

    ClassDefOverride(MCApplication, 1)
};

#endif // TGEOTET_VMCDEMO_MCAPPLICATION_H
