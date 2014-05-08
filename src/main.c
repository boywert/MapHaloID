#include <stdio.h>
#include <stdlib.h>

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
  
  sprintf(folder,"/scratch/00916/tg459470/clues/4096/reduced/output_%05d/fofres/halos",filenr);

  for(ifile=1;ifile<=nfiles;ifile++)
    {
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

  readmfof(filenr);

  return 0;
}
