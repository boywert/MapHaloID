#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct halostruct {
  long long unsigned host;
  float pos[3];
  float vel[3];
  long long nextid;
};

struct AHFhalo {
  uint64_t ID;
  uint64_t hostHalo;
  int  numSubStruct;
  float   Mvir;
  int  npart;
  float   Xc;
  float   Yc;
  float   Zc;
  float   VXc;
  float   VYc;
  float   VZc;
  float   Rvir;
  float   Rmax;
  float   r2;
  float   mbp_offset;
  float   com_offset;
  float   Vmax;
  float   v_esc;
  float   sigV;
  float   lambda;
  float   lambdaE;
  float   Lx;
  float   Ly;
  float   Lz;
  float   b;
  float   c;
  float   Eax;
  float   Eay;
  float   Eaz;
  float   Ebx;
  float   Eby;
  float   Ebz;
  float   Ecx;
  float   Ecy;
  float   Ecz;
  float   ovdens;
  uint32_t nbins;
  float   fMhires;
  float   Ekin;
  float   Epot;
  float   SurfP;
  float   Phi0;
  float   cNFW;
};

void read_clueAHFhalos()
{
  char strbuffer[2048];
  struct AHFhalo ahfhalo;
  char filename[2048];
  int currentHalo;
  FILE *fp;
  sprintf(filename,"/scratch/01937/cs390/B64_2048_snap_077_halos");
  fp = fopen(filename, "r");
  fgets(strbuffer,2048,fp);
  while(fgets(strbuffer,2048,fp))
    {
      //printf("iHalo = %llu\n",iHalo);
      sscanf(strbuffer,"%llu %llu %d %g %d %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
	     &(HaloTable[currentHalo].ID),
	     &(ahfhalo.hostHalo),
	     &(ahfhalo.numSubStruct),
	     &(ahfhalo.Mvir),
	     &(ahfhalo.npart),
	     &(ahfhalo.Xc),
	     &(ahfhalo.Yc),
	     &(ahfhalo.Zc),
	     &(ahfhalo.VXc),
	     &(ahfhalo.VYc),
	     &(ahfhalo.VZc),
	     &(ahfhalo.Rvir), 
	     &(ahfhalo.Rmax),
	     &(ahfhalo.r2),
	     &(ahfhalo.mbp_offset),
	     &(ahfhalo.com_offset),
	     &(ahfhalo.Vmax),
	     &(ahfhalo.v_esc),
	     &(ahfhalo.sigV),
	     &(ahfhalo.lambda),
	     &(ahfhalo.lambdaE),
	     &(ahfhalo.Lx),
	     &(ahfhalo.Ly),
	     &(ahfhalo.Lz),
	     &(ahfhalo.b),
	     &(ahfhalo.c),
	     &(ahfhalo.Eax),
	     &(ahfhalo.Eay),
	     &(ahfhalo.Eaz),
	     &(ahfhalo.Ebx), 
	     &(ahfhalo.Eby),
	     &(ahfhalo.Ebz),
	     &(ahfhalo.Ecx), 
	     &(ahfhalo.Ecy), 
	     &(ahfhalo.Ecz),
	     &(ahfhalo.ovdens),
	     &(ahfhalo.nbins),
	     &(ahfhalo.fMhires),
	     &(ahfhalo.Ekin),
	     &(ahfhalo.Epot),
	     &(ahfhalo.SurfP),
	     &(ahfhalo.Phi0),
	     &(ahfhalo.cNFW) 
	     );
      
      currentHalo++;
    }
  fclose(fp);
      
}




void readmfofsnap(int filenr)
{
  char folder[1024];
  //int filenr=138;
  char massfname[1024],structfname[1024];
  double pos[3],vel[3];
  FILE *fp;
  int ihalo,jhalo,ifile;
  int skip,nhalos,ipart,nparts;
  float mass;
  long long id;
  int nfiles = 4096;
  int firstfile,lastfile;
  sprintf(folder,"/scratch/00916/tg459470/clues/4096/reduced/output_%05d/fofres/halos",filenr);

  for(ifile=1;ifile<=nfiles;ifile++)
    {
      printf("READING %d\n",ifile);
      sprintf(structfname,"%s/halos_strct_%05d",folder,ifile);
      fp = fopen(structfname,"rb");
  
  
      /* read nHalos */

      fseek(fp, sizeof(int), SEEK_CUR);
      fread (&nhalos,1,sizeof(int),fp);
      fseek(fp, sizeof(int), SEEK_CUR);


      for(ihalo=0;ihalo<nhalos;ihalo++)
	{
	  fseek(fp, sizeof(int), SEEK_CUR);
	  fread (&nparts,1,sizeof(int),fp);
	  fseek(fp, sizeof(int), SEEK_CUR);


	  fseek(fp, sizeof(int), SEEK_CUR);
	  for(ipart=0;ipart<nparts;ipart++)
	    {
	      fread (&(pos[0]), 3, sizeof(float),fp);
	    }
	  fseek(fp, sizeof(int), SEEK_CUR);


	  fseek(fp, sizeof(int), SEEK_CUR);
	  for(ipart=0;ipart<nparts;ipart++)
	    {
	      fread (&(vel[0]), 3, sizeof(float),fp);
	    }
	  fseek(fp, sizeof(int), SEEK_CUR);



	  fseek(fp, sizeof(int), SEEK_CUR);
	  // skip ids
	  fseek(fp, ipart*sizeof(long long), SEEK_CUR);
	  /* for(ipart=0;ipart<nparts;ipart++)  */
	  /* 	{ */
	  /* 	  fread (&id, 1, sizeof(long long),fp); */
	  /* 	} */
	  fseek(fp, sizeof(int), SEEK_CUR);

	}
      fclose(fp);
    }
}

int main ()
{
  int filenr=138;

  //readmfofsnap(filenr);
  read_clueAHFhalos();

  return 0;
}
