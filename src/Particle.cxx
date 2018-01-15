#include "Particle.h"
#include "TObjArray.h"
#include "TParticle.h"

Particle::Particle(Int_t id, TParticle* particle)
    : fID(id)
    , fParticle(particle)
    , fMother(nullptr)
    , fDaughters(nullptr)
{
}

Particle::Particle(Int_t id, TParticle* particle, Particle* mother)
    : fID(id)
    , fParticle(particle)
    , fMother(mother)
    , fDaughters(nullptr)
{
}

Particle::Particle()
    : fID(0)
    , fParticle(nullptr)
    , fMother(nullptr)
    , fDaughters(nullptr)
{
}

Particle::~Particle() { delete fDaughters; }


void Particle::AddDaughter(Particle* particle)
{
    if (!fDaughters)
        fDaughters = new TObjArray();
    fDaughters->Add(particle);
}

void Particle::SetMother(Particle* particle) { fMother = particle; }

Int_t Particle::GetID() const { return fID; }

TParticle* Particle::GetParticle() const { return fParticle; }

Particle* Particle::GetMother() const { return fMother; }

Int_t Particle::GetNofDaughters() const
{
    if (!fDaughters)
        return 0;
    return fDaughters->GetEntriesFast();
}

Particle* Particle::GetDaughter(Int_t i) const { return (Particle*)fDaughters->At(i); }
