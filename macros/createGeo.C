void createGeo()
{
    auto geom   = new TGeoManager("World", "IES");
    auto matVac = new TGeoMaterial("Vacuum", 0, 0, 0);
    auto medVac = new TGeoMedium("Vacuum", 0, matVac);

    auto matAl = new TGeoMaterial("Al", 26.98, 13, 2.7);
    auto medAl = new TGeoMedium("Al", 1, matAl);

    auto world = geom->MakeBox("World", medVac, 200., 200., 200.);
    world->SetLineColor(kMagenta);
    geom->SetTopVolume(world);

    // auto Sha1 = new TGeoTet({0, 0, 0}, {1, 0, 0}, {0, 2, 0}, {0, 0, 3});
    auto Sha1 = new TGeoBBox("BOX", 10, 5, 5);
    auto Vol1 = new TGeoVolume("SV", Sha1, medAl);
    auto trans = new TGeoTranslation(30, 0, 0);
    Vol1->SetLineColor(kBlue);
    world->AddNode(Vol1, 0, trans);

    /*auto Sha2 = new TGeoTet({0, 0, 0}, {-1, 0, 0}, {0, -1, 0}, {0, 0, -1});
    auto Vol2 = new TGeoVolume("tetrahedron2", Sha2, medVac);
    Vol2->SetLineColor(kGreen);
    world->AddNode(Vol2, 0);*/

    geom->CloseGeometry();
    geom->SetVisLevel(4);

    gStyle->SetCanvasPreferGL(kTRUE);
    world->Draw("ogl");
    auto v = (TGLViewer*)gPad->GetViewer3D();
    v->CurrentCamera().RotateRad(0, 0.1);
    v->SetStyle(TGLRnrCtx::kOutline);
    v->RequestDraw();
    v->SavePicture("geo.png");

    geom->Export("geo.root");
}