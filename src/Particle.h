#ifndef TGEOTET_VMCDEMO_PARTICLE_H
#define TGEOTET_VMCDEMO_PARTICLE_H

#include "TObject.h"

class TParticle;

class Particle : public TObject
{
  public:
    Particle(Int_t id, TParticle* particle);
    Particle(Int_t id, TParticle* particle, Particle* mother);
    Particle();
    ~Particle() override;

    void SetMother(Particle* particle);
    void AddDaughter(Particle* particle);

    Int_t GetID() const;
    TParticle* GetParticle() const;
    Particle* GetMother() const;
    Int_t GetNofDaughters() const;
    Particle* GetDaughter(Int_t i) const;

  private:
    Int_t fID;
    TParticle* fParticle;
    Particle* fMother;
    TObjArray* fDaughters;

    ClassDefOverride(Particle, 1)
};

#endif // TGEOTET_VMCDEMO_PARTICLE_H
