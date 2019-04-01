void getCut(TString *namelist,int n){
  for(int i=0;i<n;i++){
    TString name=namelist[i];
    TCutG *cut = (TCutG*)gPad->WaitPrimitive("CUTG","CutG");
    cut->SetName(name);
    cut->Print();
    int n = cut->GetN();
    double *x = cut->GetX();
    double *y = cut->GetY();
    //open file for output of bananas
    ofstream outfile;
    char ofn[32];
    sprintf(ofn,"%s.cut",name.Data());
    outfile.open(ofn);
    outfile << n << endl;
    for (int i=0;i<n;i++){
      outfile << *x++ << " " << *y++ <<  endl;
    }
    outfile.close();
    delete cut;
  }
}
