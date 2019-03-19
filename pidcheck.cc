#include "pidcut0.cc"
#include "pidcut1.cc"
TTree *tree;
TFile *ipf;
TCanvas *c1;
TH1F *h1,*h2;
void pidcheck(int run){
    char name[32];
    sprintf(name,"cali%04d.root",run);
    ipf=new TFile(name);
    tree=(TTree*)ipf->Get("tree");
    c1=new TCanvas(name,"pid",1800,800);
    c1->Divide(2,1);
    c1->cd(1);
    gStyle->SetPalette(kRainBow);
    tree->Draw("de[0]:tof>>pid0(1000,0,500,1000,0,500)");
    h1=(TH1F*)gROOT->FindObject("pid0");
    h1->Draw("colz");
    gPad->SetLogz();
    pidcut0();
    c1->cd(2);
    tree->Draw("de[1]:tof>>pid1(1000,0,500,1000,0,500)");
    h2=(TH1F*)gROOT->FindObject("pid1");
    h2->Draw("colz");
    gPad->SetLogz();
    pidcut1();
    //ipf.Close();
    sprintf(name,"check%04d.png",run);
    c1->SaveAs(name);
}
void clear(){
    delete h1;
    delete h2;
    delete c1;
    delete tree;
    ipf->Close();
    delete ipf;
    pidcut0clear();
    pidcut1clear();
}

void pidcheck(){
    for(int i=151;i<=366;i++){
        pidcheck(i);
        clear();
    }
}
void pidcheck(int begin,int end){
    for(int i=begin;i<=end;i++){
        pidcheck(i);
        clear();
    }
}
