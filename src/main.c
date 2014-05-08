#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct halostruct {
  uint64_t host;
  float mass;
  int nparts;
  float pos[3];
  float vel[3];
  int64_t nextid;
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
  int currentHalo = 0;
  FILE *fp;
  int stepmaxhalo = 1000000;
  int maxhalo;
  maxhalo = stepmaxhalo;
  struct halostruct *halo;

  halo = malloc(maxhalo*sizeof(struct AHFhalo));
  sprintf(filename,"/scratch/01937/cs390/B64_2048_snap_077_halos");
  fp = fopen(filename, "r");
  fgets(strbuffer,2048,fp);
  
  while(fgets(strbuffer,2048,fp))
    {
      //printf("iHalo = %llu\n",iHalo);
      sscanf(strbuffer,"%llu %llu %d %g %d %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %d %g %g %g %g %g %g",
	     &(ahfhalo.ID),
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
      halo[currentHalo].host = ahfhalo.hostHalo;
      halo[currentHalo].nparts = ahfhalo.npart;
      halo[currentHalo].pos[0] = ahfhalo.Xc;
      halo[currentHalo].pos[1] = ahfhalo.Yc;
      halo[currentHalo].pos[2] = ahfhalo.Zc;
      halo[currentHalo].vel[0] = ahfhalo.VXc;
      halo[currentHalo].vel[1] = ahfhalo.VYc;
      halo[currentHalo].vel[2] = ahfhalo.VZc;
      halo[currentHalo].nextid = -1;
      if(currentHalo == maxhalo-1)
	{
	  maxhalo+=stepmaxhalo;
	  halo = realloc(halo,sizeof(struct halostruct)*maxhalo);
	}
      currentHalo++;
    }
  
  fclose(fp);
  halo = realloc(halo,sizeof(struct halostruct)*currentHalo);
  free(halo);
      
}




void readmfofsnap(int filenr)
{
  char folder[1024];
  //int filenr=138;
  char massfname[1024],structfname[1024];
  float  pos[3],vel[3];
  float *bpos,*bvel;
  double cmpos[3],cmvel[3];
  FILE *fp;
  int ihalo,jhalo,ifile;
  int skip,nhalos,ipart,nparts;
  float mass;
  // long long id;
  int nfiles = 4096;
  // int firstfile,lastfile;
  int i;
  uint64_t totalhalos = 0;
  struct halostruct *halo;
  long long currentHalo = 0;
  
  halo = malloc(0);
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

      totalhalos += nhalos;
      halo = realloc(halo,totalhalos*sizeof(struct halostruct));

      for(ihalo=0;ihalo<nhalos;ihalo++)
	{
	  fseek(fp, sizeof(int), SEEK_CUR);
	  fread (&nparts,1,sizeof(int),fp);
	  fseek(fp, sizeof(int), SEEK_CUR);

	  for(i=0;i<3;i++)
	    {
	      cmvel[i] = 0.;
	      cmpos[i] = 0.;
	    }
	  // bpos = malloc(3*nparts*sizeof(float));
	  // bvel = malloc(3*nparts*sizeof(float));



	  fseek(fp, sizeof(int), SEEK_CUR);
	  // fread (&(bpos[0]), 3*nparts, sizeof(float),fp);
	  for(ipart=0;ipart<nparts;ipart++)
	    {
	      fread (&(pos[0]), 3, sizeof(float),fp);
	      for(i=0;i<3;i++)
		{
		  // cmpos[i] += bpos[ipart*3+i];
		  cmpos[i] += pos[i];
		}
	    }
	  fseek(fp, sizeof(int), SEEK_CUR);


	  fseek(fp, sizeof(int), SEEK_CUR);
	  // fread (&(bvel[0]), 3*nparts, sizeof(float),fp);
	  for(ipart=0;ipart<nparts;ipart++)
	    {
	      fread (&(vel[0]), 3, sizeof(float),fp);
	      for(i=0;i<3;i++)
		{
		  // cmvel[i] += bvel[ipart*3+i];
		  cmvel[i] += vel[i];
		}
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
	  for(i=0;i<3;i++)
	    {
	      cmvel[i] /= (double)nparts;
	      cmpos[i] /= (double)nparts;
	      
	    }
	  halo[currentHalo].host = 0;
	  halo[currentHalo].nparts = nparts;
	  halo[currentHalo].pos[0] = cmpos[0];
	  halo[currentHalo].pos[1] = cmpos[1];
	  halo[currentHalo].pos[2] = cmpos[2];
	  halo[currentHalo].vel[0] = cmvel[0];
	  halo[currentHalo].vel[1] = cmvel[1];
	  halo[currentHalo].vel[2] = cmvel[2];
	  halo[currentHalo].nextid = -1;
	  

	  //free(bpos);
	  //free(bvel);
	  currentHalo++;
	}
      fclose(fp);
    }
}

int main ()
{
  int filenr=138;

  readmfofsnap(filenr);
  //read_clueAHFhalos();

  return 0;
}
