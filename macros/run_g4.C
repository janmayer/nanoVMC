// clang-format off
R__LOAD_LIBRARY(../build/libTGeoTet_VMCDemo.so)
// clang-format on

void run_g4(std::string geo = "geo.root", std::string out = "out.root")
{
    gROOT->ProcessLine(".x load_g4.C");

    auto appl = new MCApplication(geo, out);
    appl->InitMC("g4Config.C");
    appl->RunMC(1e6);
    delete appl;
}
