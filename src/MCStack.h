#ifndef NANOVMC_MCSTACK_H
#define NANOVMC_MCSTACK_H

#include "TLorentzVector.h"
#include "TVirtualMCStack.h"
#include <stack>

class TParticle;
class TClonesArray;


class MCStack : public TVirtualMCStack
{
  public:
    explicit MCStack(Int_t size);
    MCStack();
    ~MCStack() override;

    void PushBasicPrimary(Int_t pdg, const TLorentzVector& mom);

    void PushTrack(Int_t toBeDone,
                   Int_t parent,
                   Int_t pdg,
                   Double_t px,
                   Double_t py,
                   Double_t pz,
                   Double_t e,
                   Double_t vx,
                   Double_t vy,
                   Double_t vz,
                   Double_t tof,
                   Double_t polx,
                   Double_t poly,
                   Double_t polz,
                   TMCProcess mech,
                   Int_t& ntr,
                   Double_t weight,
                   Int_t is) override;

    TParticle* PopNextTrack(Int_t& itrack) override;
    TParticle* PopPrimaryForTracking(Int_t i) override;
    void Reset();
    void SetCurrentTrack(Int_t itrack) override;
    Int_t GetNtrack() const override;
    Int_t GetNprimary() const override;
    TParticle* GetCurrentTrack() const override;
    Int_t GetCurrentTrackNumber() const override;
    Int_t GetCurrentParentTrackNumber() const override;
    TParticle* GetParticle(Int_t id) const;

  private:
    std::stack<TParticle*> fStack; // The stack of particles (transient)
    TClonesArray* fParticles;      // The array of particle (persistent)
    Int_t fCurrentTrack;           // The current track number
    Int_t fNPrimary;               // The number of primaries

    ClassDefOverride(MCStack, 1)
};

#endif // NANOVMC_MCSTACK_H
