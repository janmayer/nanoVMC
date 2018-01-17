void createGeoArb8()
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

    auto Sha2 = new TGeoArb8(5); // 10/2
    Sha2->SetVertex(0, 0, 0);
    Sha2->SetVertex(1, 0, -10);
    Sha2->SetVertex(2, 0, -10);
    Sha2->SetVertex(3, -10, 0);
    Sha2->SetVertex(4, 0, 0);
    Sha2->SetVertex(5, 0, 0);
    Sha2->SetVertex(6, 0, 0);
    Sha2->SetVertex(7, 0, 0);
    auto Vol2   = new TGeoVolume("arb8", Sha2, medPb);
    auto trans2 = new TGeoTranslation(15, 2, 3);
    Vol2->SetLineColor(kGreen);
    Sha2->InspectShape();
    world->AddNode(Vol2, 0, trans2);

    geom->CloseGeometry();
    geom->SetVisLevel(4);

    gStyle->SetCanvasPreferGL(kTRUE);
    world->Draw("ogl");
    auto v = (TGLViewer*)gPad->GetViewer3D();
    v->CurrentCamera().RotateRad(0, 0.1);
    v->SetStyle(TGLRnrCtx::kOutline);
    v->RequestDraw();
    v->SavePicture("geo-arb8.png");

    geom->Export("geo-arb8.root");
}