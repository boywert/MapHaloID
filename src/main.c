#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mpi.h>

#define  MIN(x,y)  ((x)<(y) ?(x):(y))

int rank, size;

const float boxsize = 64000.; 
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
struct halostruct *AHFhalo,*FOFhalo;

int64_t read_clueAHFhalos()
{
  char strbuffer[2048];
  struct AHFhalo ahfhalo;
  char filename[2048];
  int currentHalo ;
  FILE *fp;
  int stepmaxhalo = 1000000;
  int maxhalo;

  if(rank == 0)
    {
      maxhalo = stepmaxhalo;

      AHFhalo = realloc(AHFhalo,maxhalo*sizeof(struct halostruct));
      sprintf(filename,"/scratch/01937/cs390/B64_2048_snap_077_halos");
      fp = fopen(filename, "r");
      fgets(strbuffer,2048,fp);
      currentHalo = 0;
      while(fgets(strbuffer,2048,fp)!=NULL)
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
	  AHFhalo[currentHalo].host = ahfhalo.hostHalo;
	  AHFhalo[currentHalo].nparts = ahfhalo.npart;
	  AHFhalo[currentHalo].pos[0] = ahfhalo.Xc;
	  AHFhalo[currentHalo].pos[1] = ahfhalo.Yc;
	  AHFhalo[currentHalo].pos[2] = ahfhalo.Zc;
	  AHFhalo[currentHalo].vel[0] = ahfhalo.VXc;
	  AHFhalo[currentHalo].vel[1] = ahfhalo.VYc;
	  AHFhalo[currentHalo].vel[2] = ahfhalo.VZc;
	  AHFhalo[currentHalo].nextid = -1;
	  // printf("%d %f %f %f\n",currentHalo,halo[currentHalo].pos[0],halo[currentHalo].pos[1],halo[currentHalo].pos[2]);
	  if(currentHalo == maxhalo-1)
	    {
	      maxhalo+=stepmaxhalo;
	      AHFhalo = realloc(AHFhalo,sizeof(struct halostruct)*maxhalo);
	    }
	  currentHalo++;
	}
  
      fclose(fp);

      AHFhalo = realloc(AHFhalo,sizeof(struct halostruct)*currentHalo);
    }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Bcast(&currentHalo, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if(rank != 0)
    {
      AHFhalo = realloc(AHFhalo,sizeof(struct halostruct)*currentHalo);
    }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Bcast(AHFhalo, sizeof(struct halostruct)*currentHalo, MPI_BYTE, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  return (int64_t)currentHalo;
}




int64_t readmfofsnap(int filenr)
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
  int firstfile,lastfile;
  int i;
  int  totalhalos = 0;
  // struct halostruct *halo;
  int  currentHalo = 0;
  int blockA;
  
  blockA = nfiles/size;
  
  firstfile = blockA*rank;
  lastfile = MIN(blockA*(rank+1)-1,nfiles-1);

  FOFhalo = realloc(FOFhalo,0);
  sprintf(folder,"/scratch/00916/tg459470/clues/4096/reduced/output_%05d/fofres/halos",filenr);
  
  
  for(ifile=firstfile;ifile<=lastfile;ifile++)
    {
      
      sprintf(structfname,"%s/halos_strct_%05d",folder,ifile);
      printf("READING %d  %s\n",ifile,structfname);
      fp = fopen(structfname,"rb");
  
  
      /* read nhalos */

      fseek(fp, sizeof(int), SEEK_CUR);
      fread (&nhalos,1,sizeof(int),fp);
      fseek(fp, sizeof(int), SEEK_CUR);

      totalhalos += nhalos;
      printf("nhalos:%d  total:%d\n",nhalos,totalhalos);
      FOFhalo = realloc(FOFhalo,totalhalos*sizeof(struct halostruct));

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
	  bpos = malloc(3*nparts*sizeof(float));
	  bvel = malloc(3*nparts*sizeof(float));



	  fseek(fp, sizeof(int), SEEK_CUR);
	  fread (&(bpos[0]), 3*nparts, sizeof(float),fp);
	  for(ipart=0;ipart<nparts;ipart++)
	    {
	      // fread (&(pos[0]), 3, sizeof(float),fp);
	      for(i=0;i<3;i++)
		{
		  cmpos[i] += bpos[ipart*3+i];
		  // cmpos[i] += pos[i];
		}
	    }
	  fseek(fp, sizeof(int), SEEK_CUR);


	  fseek(fp, sizeof(int), SEEK_CUR);
	  fread (&(bvel[0]), 3*nparts, sizeof(float),fp);
	  for(ipart=0;ipart<nparts;ipart++)
	    {
	      // fread (&(vel[0]), 3, sizeof(float),fp);
	      for(i=0;i<3;i++)
		{
		  cmvel[i] += bvel[ipart*3+i];
		  // cmvel[i] += vel[i];
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
	  FOFhalo[currentHalo].host = 0;
	  FOFhalo[currentHalo].nparts = nparts;
	  FOFhalo[currentHalo].pos[0] = cmpos[0]*boxsize;
	  FOFhalo[currentHalo].pos[1] = cmpos[1]*boxsize;
	  FOFhalo[currentHalo].pos[2] = cmpos[2]*boxsize;
	  FOFhalo[currentHalo].vel[0] = cmvel[0];
	  FOFhalo[currentHalo].vel[1] = cmvel[1];
	  FOFhalo[currentHalo].vel[2] = cmvel[2];
	  FOFhalo[currentHalo].nextid = -1;
	  

	  free(bpos);
	  free(bvel);
	  currentHalo++;
	}
      fclose(fp);
      printf("closing file\n");
    }
  printf("%d  %d \n",(int)currentHalo,(int)totalhalos);
  return (int64_t) totalhalos;
}

int main (int argc, char** argv)
{
  int filenr=88;
  int64_t ihalo,nhaloFOF,nhaloAHF;
  int *hocFOF,*hocAHF;
  int block,xb,yb,zb;
  int i;
  int nsubperdim = 128;
  int totalsub;
  //   struct halostruct *FOFhalo,*AHFhalo;
  float subsize;


  MPI_Init (&argc, &argv);	/* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);	/* get number of processes */

  totalsub = nsubperdim*nsubperdim*nsubperdim;
  subsize = boxsize/nsubperdim;

  hocFOF = malloc(sizeof(int)*totalsub);
  hocAHF = malloc(sizeof(int)*totalsub);

  for(i=0;i<totalsub;i++)
    {
      hocFOF[i] = -1;
      hocAHF[i] = -1;
    }

  FOFhalo = malloc(0);

  nhaloFOF = readmfofsnap(filenr);

  for(ihalo=0;ihalo<nhaloFOF;ihalo++)
    {
      xb = FOFhalo[ihalo].pos[0]/subsize;
      yb = FOFhalo[ihalo].pos[1]/subsize;
      zb = FOFhalo[ihalo].pos[2]/subsize;
      
      block = xb*nsubperdim*nsubperdim + yb*nsubperdim + zb;
      FOFhalo[ihalo].nextid = hocFOF[block];
      hocFOF[block] = ihalo;
    }

  AHFhalo = malloc(0);

  /* nhaloAHF = read_clueAHFhalos(); */

  /* for(ihalo=0;ihalo<nhaloAHF;ihalo++) */
  /*   { */
  /*     // printf("%llu %f %f %f %f %f %f\n",ihalo,AHFhalo[ihalo].pos[0],AHFhalo[ihalo].pos[1],AHFhalo[ihalo].pos[2],AHFhalo[ihalo].vel[0],AHFhalo[ihalo].vel[1],AHFhalo[ihalo].vel[2]); */
  /*     xb = AHFhalo[ihalo].pos[0]/subsize; */
  /*     yb = AHFhalo[ihalo].pos[1]/subsize; */
  /*     zb = AHFhalo[ihalo].pos[2]/subsize; */
      
  /*     block = xb*nsubperdim*nsubperdim + yb*nsubperdim + zb; */

  /*     // printf("%llu/%llu  %d: %d %d %d \n",ihalo,nhaloAHF,block,xb,yb,zb); */
  /*     AHFhalo[ihalo].nextid = hocAHF[block]; */
  /*     hocAHF[block] = ihalo;       */
  /*   } */


  free(hocFOF);
  free(hocAHF);
  free(AHFhalo);
  free(FOFhalo);
  MPI_Finalize();
  return 0;
}
