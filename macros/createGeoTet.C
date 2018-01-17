void createGeoTet()
{
    auto geom   = new TGeoManager("World", "IES");
    auto matVac = new TGeoMaterial("Vacuum", 0, 0, 0);
    auto medVac = new TGeoMedium("Vacuum", 0, matVac);

    auto matAl = new TGeoMaterial("Al", 26.98, 13, 2.7);
    auto medAl = new TGeoMedium("Al", 1, matAl);

    auto matPb = new TGeoMaterial("Pb", 208, 82, 11.34);
    auto medPb = new TGeoMedium("Pb", 2, matPb);

    auto world = geom->MakeBox("World", medVac, 200., 200., 200.);
    world->SetLineColor(kMagenta);
    geom->SetTopVolume(world);

    auto Sha1   = new TGeoBBox("BOX", 10, 5, 5);
    auto Vol1   = new TGeoVolume("SV", Sha1, medAl);
    auto trans1 = new TGeoTranslation(30, 0, 0);
    Vol1->SetLineColor(kBlue);
    world->AddNode(Vol1, 0, trans1);

    auto Sha3   = new TGeoTet({0, 0, -5}, {-10, 0, -5}, {0, -10, -5}, {0, 0, +5});
    auto Vol3   = new TGeoVolume("tet", Sha3, medPb);
    auto trans3 = new TGeoTranslation(15, 2, 3);
    Vol3->SetLineColor(kRed);
    world->AddNode(Vol3, 0, trans3);

    geom->CloseGeometry();
    geom->SetVisLevel(4);

    gStyle->SetCanvasPreferGL(kTRUE);
    world->Draw("ogl");
    auto v = (TGLViewer*)gPad->GetViewer3D();
    v->CurrentCamera().RotateRad(0, 0.1);
    v->SetStyle(TGLRnrCtx::kOutline);
    v->RequestDraw();
    v->SavePicture("geo-tet.png");

    geom->Export("geo-tet.root");
}