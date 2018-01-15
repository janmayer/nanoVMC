R__LOAD_LIBRARY(../build/libTGeoTet_VMCDemo.so)

void run_g4(const TString& configMacro = "g4Config.C")
{
    gROOT->ProcessLine(".x load_g4.C");

    auto appl = new MCApplication();
    appl->InitMC(configMacro);
    appl->RunMC(1);
    delete appl;
}
