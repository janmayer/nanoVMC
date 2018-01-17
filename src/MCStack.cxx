#include "MCStack.h"
#include "TClonesArray.h"
#include "TParticle.h"

MCStack::MCStack(Int_t size)
    : fParticles(new TClonesArray("TParticle", size))
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

    TClonesArray& particlesRef = *fParticles;
    Int_t trackId              = GetNtrack();
    auto particle              = new (particlesRef[trackId])
        TParticle(pdg, is, parent, trackId, kFirstDaughter, kLastDaughter, px, py, pz, e, vx, vy, vz, tof);

    particle->SetPolarisation(polx, poly, polz);
    particle->SetWeight(static_cast<Float_t>(weight));
    particle->SetUniqueID(mech);

    if (parent < 0)
        fNPrimary++;

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

    TParticle* particle = fStack.top();
    fStack.pop();

    if (!particle)
        return nullptr;

    fCurrentTrack = particle->GetSecondMother();
    itrack        = fCurrentTrack;

    return particle;
}

TParticle* MCStack::PopPrimaryForTracking(Int_t i)
{
    /// Return \em i -th particle in fParticles.
    /// \return   The popped primary particle object
    /// \param i  The index of primary particle to be popped

    if (i < 0 || i >= fNPrimary)
        Fatal("GetPrimaryForTracking", "Index out of range");

    return (TParticle*)fParticles->At(i);
}

void MCStack::SetCurrentTrack(Int_t itrack) { fCurrentTrack = itrack; }

Int_t MCStack::GetNtrack() const { return fParticles->GetEntriesFast(); }

Int_t MCStack::GetNprimary() const { return fNPrimary; }

TParticle* MCStack::GetCurrentTrack() const
{
    TParticle* current = GetParticle(fCurrentTrack);

    if (!current)
        Warning("GetCurrentTrack", "Current track not found in the stack");

    return current;
}

Int_t MCStack::GetCurrentTrackNumber() const { return fCurrentTrack; }

Int_t MCStack::GetCurrentParentTrackNumber() const
{
    TParticle* current = GetCurrentTrack();

    if (current)
        return current->GetFirstMother();
    else
        return -1;
}

TParticle* MCStack::GetParticle(Int_t id) const
{
    if (id < 0 || id >= fParticles->GetEntriesFast())
        Fatal("GetParticle", "Index out of range");

    return (TParticle*)fParticles->At(id);
}

void MCStack::Reset()
{
    fCurrentTrack = -1;
    fNPrimary     = 0;
    fParticles->Clear();
}

void MCStack::PushBasicPrimary(Int_t pdg, const TLorentzVector& mom)
{
    // Track ID (filled by stack) (Nobody cares!)
    Int_t ntr;

    // Option: to be tracked
    const Int_t toBeDone = 1;

    // Polarization
    const Double_t polx = 0.;
    const Double_t poly = 0.;
    const Double_t polz = 0.;

    // Position
    const Double_t vx  = 0.;
    const Double_t vy  = 0.;
    const Double_t vz  = 0.;
    const Double_t tof = 0.;

    // Add particle to stack
    PushTrack(toBeDone, -1, pdg, mom.Px(), mom.Py(), mom.Pz(), mom.E(), vx, vy, vz, tof, polx, poly, polz, kPPrimary, ntr, 1., 0);
}
