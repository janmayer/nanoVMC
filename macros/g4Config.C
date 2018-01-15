void Config()
{
    // geomRootToGeant4 <-
    // geomVMCtoGeant4
    // geomRoot <-
    // geomVMCtoRoot
    auto runConfiguration = new TG4RunConfiguration("geomRoot", "QGSP_INCLXX");

    auto geant4 = new TGeant4("TGeant4", "The Geant4 Monte Carlo", runConfiguration);
    geant4->ProcessGeantCommand("/mcVerbose/all 0");

    cout << "Geant4 has been created." << endl;
}
