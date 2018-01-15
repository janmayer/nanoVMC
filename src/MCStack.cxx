#include "MCStack.h"
#include "TObjArray.h"
#include "TParticle.h"

MCStack::MCStack(Int_t size)
    : fParticles(new TObjArray(size))
    , fCurrentTrack(-1)
    , fNPrimary(0)
{
}

MCStack::MCStack()
    : fParticles(nullptr)
    , fCurrentTrack(-1)
    , fNPrimary(0)
{
}

MCStack::~MCStack()
{
    if (fParticles)
        fParticles->Delete();
    delete fParticles;
}

void MCStack::PushTrack(Int_t toBeDone,
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
                        Int_t is)
{
    /// Create a new particle and push into stack;
    /// adds it to the particles array (fParticles) and if not done to the
    /// stack (fStack).
    /// \param toBeDone  1 if particles should go to tracking, 0 otherwise
    /// \param parent    number of the parent track, -1 if track is primary
    /// \param pdg       PDG encoding
    /// \param px        particle momentum - x component [GeV/c]
    /// \param py        particle momentum - y component [GeV/c]
    /// \param pz        particle momentum - z component [GeV/c]
    /// \param e         total energy [GeV]
    /// \param vx        position - x component [cm]
    /// \param vy        position - y component  [cm]
    /// \param vz        position - z component  [cm]
    /// \param tof       time of flight [s]
    /// \param polx      polarization - x component
    /// \param poly      polarization - y component
    /// \param polz      polarization - z component
    /// \param mech      creator process VMC code
    /// \param ntr       track number (is filled by the stack
    /// \param weight    particle weight
    /// \param is        generation status code

    const Int_t kFirstDaughter = -1;
    const Int_t kLastDaughter  = -1;

    auto particleDef =
        new TParticle(pdg, is, parent, -1, kFirstDaughter, kLastDaughter, px, py, pz, e, vx, vy, vz, tof);

    particleDef->SetPolarisation(polx, poly, polz);
    particleDef->SetWeight(static_cast<Float_t>(weight));
    particleDef->SetUniqueID(mech);

    Particle* mother = nullptr;
    if (parent >= 0)
        mother = GetParticle(parent);
    else
        fNPrimary++;

    auto particle = new Particle(GetNtrack(), particleDef, mother);

    fParticles->Add(particle);

    if (toBeDone)
        fStack.push(particle);

    ntr = GetNtrack() - 1;
}

TParticle* MCStack::PopNextTrack(Int_t& itrack)
{
    /// Get next particle for tracking from the stack.
    /// \return        The popped particle object
    /// \param itrack  The index of the popped track

    itrack = -1;
    if (fStack.empty())
        return nullptr;

    Particle* particle = fStack.top();
    fStack.pop();

    if (!particle)
        return nullptr;

    itrack        = particle->GetID();
    fCurrentTrack = itrack;

    return particle->GetParticle();
}

TParticle* MCStack::PopPrimaryForTracking(Int_t i)
{
    /// Return \em i -th particle in fParticles.
    /// \return   The popped primary particle object
    /// \param i  The index of primary particle to be popped

    if (i < 0 || i >= fNPrimary)
    {
        Fatal("GetPrimaryForTracking", "Index out of range");
    }

    return ((Particle*)fParticles->At(i))->GetParticle();
}

void MCStack::SetCurrentTrack(Int_t itrack) { fCurrentTrack = itrack; }

Int_t MCStack::GetNtrack() const { return fParticles->GetEntriesFast(); }

Int_t MCStack::GetNprimary() const { return fNPrimary; }

TParticle* MCStack::GetCurrentTrack() const
{
    Particle* current = GetParticle(fCurrentTrack);

    if (current)
    {
        return current->GetParticle();
    }
    else
    {
        return nullptr;
    }
}

Int_t MCStack::GetCurrentTrackNumber() const { return fCurrentTrack; }

Int_t MCStack::GetCurrentParentTrackNumber() const
{
    Particle* current = GetParticle(fCurrentTrack);

    if (!current)
    {
        return -1;
    }
    Particle* mother = current->GetMother();

    if (!mother)
    {
        return -1;
    }
    return mother->GetID();
}

Particle* MCStack::GetParticle(Int_t id) const
{
    if (id < 0 || id >= fParticles->GetEntriesFast())
    {
        Fatal("GetParticle", "Index out of range");
    }
    return (Particle*)fParticles->At(id);
}
