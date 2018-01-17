# nanoVMC: The minimalist Virtual Monte Carlo example


## Purpose
Provide a minimal, yet flexible example for a VMC Simulation application:

- Geometries are defined outside in a ROOT macro and loaded via TGeoManager
- Multiple sensitive detectors are supported
- Energy depositions are recorded in histograms for each sensitive detector
- The primary generator can be changed in the macro, no recompilation necessary


## Constituents
Compiled Code:
- `MCApplication`: The main application, handles all setup and execution tasks, derived from `TVirtualMCApplication`.
- `MCStack`: The list of particles in the event, derived from `TVirtualMCStack`. For unknown and incomprehensible reasons, each VMC app has to implement (read: copy & paste) this for oneself.
- `Sensitive Detector`: Keeps track of the energy depositions in each sensitive volume.

Macros:
- `createGeo*.C`: Creates a root geometry to be loaded in the VMC app. Note that each sensitive volume should be defined here by name.
- `run_g4.C`: Runs the VMC Simulation using Geant4. All libraries should be auto-loaded if their location is in the environment variable `LD_LIBRARY_PATH`.
- `g4Config.C`: Basic configuration for Geant4.
- `do.sh`: Demonstrates example usage.  


## Installation:

Prerequisites:

`Geant4_VMC` needs to be correctly installed with all dependencies. I recommend simply installing all of [FairSoft](https://github.com/FairRootGroup/FairSoft).
All of ROOT, Geant4, VMC, etc. are **extremely** sensitive to environment variables. You need to make sure everything is set up properly. Use `export LD_LIBRARY_PATH=...` liberally and edit the `CMakeFile.txt` if necessary.

Clone and build:

```bash
(set environment variables first!)
git clone https://github.com/janmayer/nanoVMC.git
cd nanoVMC
mkdir build
cd build
cmake ..
make
```

Run `./do.sh` in `macros`.


## Acknowledgements:
Very loosely based on the examples provided with `geant4_VMC` by I. Hrivnacova (IPN, Orsay). Copy & Pasted the MCStack. Inheriting GPL. 
