#ifndef TGEOTET_VMCDEMO_MCAPPLICATION_H
#define TGEOTET_VMCDEMO_MCAPPLICATION_H

#include <TVirtualMCApplication.h>

class TVirtualMCStack;

class MCApplication : public TVirtualMCApplication
{
  public:
    MCApplication();
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
    TVirtualMCStack* fStack;

    ClassDefOverride(MCApplication, 1)
};

#endif // TGEOTET_VMCDEMO_MCAPPLICATION_H
