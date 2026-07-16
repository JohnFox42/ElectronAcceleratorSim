# ElectronAcceleratorSim

## Introduction
Hello! Welcome, to my research project that started in the Summer of 2026. 
The purpose of this project was to simulate a 100keV-1MeV electron accelerator. 
This accelerator is to quantify the losses to bremsstrahlung radiation within Si detectors for low energy electrons,
specifically for the NAB experiment at the spallation neutron source at Oak Ridge National Laboratory. 
This simulation relies on Geant4, an API designed for the passage of particles and radiation through matter. 
The Geant4 website is found here: https://geant4.web.cern.ch/
I also have published an installation guide for Geant4 on windows should that interest you, also found on my github. 

## Simulation Specifics
This simulation uses the low energy EM transport model Penelope as we are working with electrons less that 1GeV. 
This simulation also outputs data within the root framework. 
