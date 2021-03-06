void run_g4(std::string geo = "geo.root", std::string out = "out.root")
{
    auto generator = [](MCStack* stack) {
        stack->PushBasicPrimary(22, TLorentzVector(5.e-3, 0., 0., 5.e-3));
    };

    MCApplication app(geo, out, generator);
    app.InitMC("g4Config.C");
    app.RunMC(1e6);
}
