void rebin()
{
    auto gaus1 = new TF1("gaus1", "gaus", -10300, -10200);
    gaus1->SetParameters(10, -10250, 10);
    auto gaus2 = new TF1("gaus2", "gaus", -100, 100);
    gaus2->SetParameters(10, 0, 10);
    auto gaus3 = new TF1("gaus3", "gaus", 10200, 10300);
    gaus3->SetParameters(10, 10250, 10);

    TH1D *h1 = new TH1D("h1", "h1", 100, -10300, -10200);
    TH1D *h2 = new TH1D("h2", "h2", 200, -100, 100);
    TH1D *h3 = new TH1D("h3", "h3", 100, 10200, 10300);

    for (int i = 0; i < 10000; i++)
    {
        h1->FillRandom("gaus1", 1);
        h2->FillRandom("gaus2", 4);
        h3->FillRandom("gaus3", 2);
    }
    const int x1n = h1->GetNbinsX();
    const int x2n = h2->GetNbinsX();
    const int x3n = h3->GetNbinsX();
    const int xn = x1n + x2n + x3n + 3;
    const int x1w = h1->GetXaxis()->GetBinWidth(0);
    const int x2w = h2->GetXaxis()->GetBinWidth(0);
    const int x3w = h3->GetXaxis()->GetBinWidth(0);
    double nbinsx[xn];
    const int x1min = h1->GetXaxis()->GetXmin();
    const int x2min = h2->GetXaxis()->GetXmin();
    const int x3min = h3->GetXaxis()->GetXmin();

    for (int i = 0; i <= x1n; i++)
    {
        nbinsx[i] = x1min + i * x1w; // + i * x1w;
    }
    for (int i = 0; i <= x2n; i++)
    {
        nbinsx[i + x1n + 1] = x2min + i * x2w;
    }
    for (int i = 0; i <= x3n; i++)
    {
        nbinsx[i + x1n + x2n + 2] = x3min + i * x3w;
    }

    TCanvas *c1 = new TCanvas();
    c1->Divide(2, 2);
    c1->cd(1);
    h1->Draw();
    c1->cd(2);
    h2->Draw();
    c1->cd(3);
    h3->Draw();
    c1->cd(4);

    TH1F *hnew = new TH1F("hnew", "rebinned", xn - 1, nbinsx);
    for (int i = 0; i < x1n; i++)
        hnew->Fill(h1->GetBinCenter(i), h1->GetBinContent(i));
    for (int i = 0; i < x2n; i++)
        hnew->Fill(h2->GetBinCenter(i), h2->GetBinContent(i));
    for (int i = 0; i < x3n; i++)
        hnew->Fill(h3->GetBinCenter(i), h3->GetBinContent(i));
    hnew->Draw();

    // for (int i = 0; i < hnew->GetNbinsX(); i++)
    // {
    //     cout << i << '\t' << hnew->GetBinContent(i) << endl;
    // }
}