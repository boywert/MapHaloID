#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mpi.h>
#include <math.h>
#include <sqlite3.h> 

#define  MIN(x,y)  ((x)<(y) ?(x):(y))

int rank, size;
const float FOFpmass = 287905.756504;
const float AHFpmass = 2303246.05203;
const float boxsize = 64000.; 
struct halostruct {
  uint64_t host;
  float mass;
  int nparts;
  float pos[3];
  float vel[3];
  int64_t nextid;
  int AHF2FOF;
  int FOF2AHF;
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
	  AHFhalo[currentHalo].mass = AHFpmass*(float)ahfhalo.npart;
	  AHFhalo[currentHalo].pos[0] = ahfhalo.Xc;
	  AHFhalo[currentHalo].pos[1] = ahfhalo.Yc;
	  AHFhalo[currentHalo].pos[2] = ahfhalo.Zc;
	  AHFhalo[currentHalo].vel[0] = ahfhalo.VXc;
	  AHFhalo[currentHalo].vel[1] = ahfhalo.VYc;
	  AHFhalo[currentHalo].vel[2] = ahfhalo.VZc;
	  AHFhalo[currentHalo].AHF2FOF = 100000000;
	  AHFhalo[currentHalo].FOF2AHF = 100000000;
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
  char buf[2048],ident[2048],equal[2048],value[2048];
  //int filenr=138;
  char massfname[1024],structfname[1024],infofile[1024];
  float  pos[3],vel[3];
  float *bpos,*bvel;
  double cmpos[3],cmvel[3];
  FILE *fp;
  int ihalo,jhalo,ifile;
  int skip,nhalos,ipart,nparts;
  float mass;
  int count;
  // long long id;
  int nfiles = 4096;
  int firstfile,lastfile;
  int i;
  int  totalhalos = 0;
  // struct halostruct *halo;
  int  currentHalo = 0;
  int totalallhalos;
  int blockA,tag;
  int *nhalosRank;
  struct halostruct *aFOFhalo;
  MPI_Status status;
  char *pch;
  float unit_t,unit_l;
  blockA = nfiles/size;
  nhalosRank = malloc(size*sizeof(int));

  firstfile = blockA*rank;
  lastfile = MIN(blockA*(rank+1)-1,nfiles-1);

  aFOFhalo = malloc(0);
  sprintf(folder,"/scratch/00916/tg459470/clues/4096/reduced/output_%05d/fofres/halos",filenr);
  sprintf(infofile,"/scratch/00916/tg459470/clues/4096/reduced/output_%05d/cutouts/1/info_%05d.txt",filenr,filenr);

  fp = fopen(infofile,"r");
  while(fgets(buf,2048,fp))
    {      
      pch = strtok (buf," \t\n");
      count = 0;
      while (pch != NULL)
	{
	  count++;
	  if(count == 1) sprintf(ident,"%s",pch);
	  if(count == 2) sprintf(equal, "%s", pch);
	  if(count == 3) sprintf(value, "%s", pch);
	  pch = strtok (NULL, " \t\n");
	}
      
      if(strcmp("unit_l",ident)==0)
	{
	  sscanf(value,"%g",&unit_l);
	  unit_l /= 100000.;
	}
      if(strcmp("unit_t",ident)==0)
	{
	  sscanf(value,"%g",&unit_t);
	}
    }
  fclose(fp);

  for(ifile=firstfile;ifile<=lastfile;ifile++)
    {
      
      sprintf(structfname,"%s/halos_strct_%05d",folder,ifile);
      // printf("READING %d  %s\n",ifile,structfname);
      fp = fopen(structfname,"rb");
  
  
      /* read nhalos */

      fseek(fp, sizeof(int), SEEK_CUR);
      fread (&nhalos,1,sizeof(int),fp);
      fseek(fp, sizeof(int), SEEK_CUR);

      totalhalos += nhalos;
      // printf("nhalos:%d  total:%d\n",nhalos,totalhalos);
      aFOFhalo = realloc(aFOFhalo,totalhalos*sizeof(struct halostruct));

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
		  cmvel[i] += bvel[ipart*3+i]*unit_l/unit_t;
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
	  aFOFhalo[currentHalo].host = 0;
	  aFOFhalo[currentHalo].nparts = nparts;
	  aFOFhalo[currentHalo].mass = FOFpmass * (float)nparts;
	  aFOFhalo[currentHalo].pos[0] = cmpos[0]*boxsize;
	  aFOFhalo[currentHalo].pos[1] = cmpos[1]*boxsize;
	  aFOFhalo[currentHalo].pos[2] = cmpos[2]*boxsize;
	  aFOFhalo[currentHalo].vel[0] = cmvel[0];
	  aFOFhalo[currentHalo].vel[1] = cmvel[1];
	  aFOFhalo[currentHalo].vel[2] = cmvel[2];
	  aFOFhalo[currentHalo].AHF2FOF = -1;
	  aFOFhalo[currentHalo].FOF2AHF = 100000000;
	  aFOFhalo[currentHalo].nextid = 100000000;
	  
	  // printf("%f %f %f\n",aFOFhalo[currentHalo].vel[0],aFOFhalo[currentHalo].vel[1],aFOFhalo[currentHalo].vel[2]);
	  free(bpos);
	  free(bvel);
	  currentHalo++;
	}
      fclose(fp);
      // printf("closing file\n");
    }

  MPI_Barrier(MPI_COMM_WORLD); 
  MPI_Allreduce(&totalhalos, &totalallhalos, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  MPI_Allgather(&totalhalos,1,MPI_INT,nhalosRank,1,MPI_INT,MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);
  FOFhalo = realloc(FOFhalo,sizeof(struct halostruct)*totalallhalos);
  if(rank == 0)
    {
      currentHalo = nhalosRank[0];
      memcpy (&(FOFhalo[0]), &(aFOFhalo[0]), nhalosRank[0]*sizeof(struct halostruct));
    }
  MPI_Barrier(MPI_COMM_WORLD);
  for(i=1;i<size;i++)
    {
      tag = i;
      if(rank == 0)
	{
	  // printf("Transfering from %d\n",i);
	  MPI_Recv(&(FOFhalo[currentHalo]), sizeof(struct halostruct)*nhalosRank[i], MPI_BYTE, i, tag, MPI_COMM_WORLD, &status);
	  currentHalo+=nhalosRank[i];
	}
      if(rank == i)
	{
	  MPI_Send(&(aFOFhalo[0]), sizeof(struct halostruct)*nhalosRank[i], MPI_BYTE, 0, tag, MPI_COMM_WORLD);
	}
      MPI_Barrier(MPI_COMM_WORLD);
    }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Bcast(FOFhalo, sizeof(struct halostruct)*totalallhalos, MPI_BYTE, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  free(nhalosRank);
  free(aFOFhalo);
  return (int64_t) totalallhalos;
}

int main (int argc, char** argv)
{
  int filenr=88;
  int64_t ihalo,nhaloFOF,nhaloAHF;
  int *hocFOF,*hocAHF;
  int block,xb,yb,zb;
  int i,j,ib,jb,kb,target_b;
  int nsubperdim = 64;
  int totalsub;
  //   struct halostruct *FOFhalo,*AHFhalo;
  float subsize;
  int blockA;
  int firstsub,lastsub;
  int curhalo_src,curhalo_tar;
  float merit,maxmerit;
  int maxmeritid;
  double sigma_pos,sigma_vel,sigma_mass;
  int ahf2fof, fof2ahf;
  int tag;
  MPI_Status status;

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
  MPI_Barrier(MPI_COMM_WORLD);
  nhaloFOF = readmfofsnap(filenr);
  MPI_Barrier(MPI_COMM_WORLD);
  for(ihalo=0;ihalo<nhaloFOF;ihalo++)
    {
      
      // if(rank==0) printf("%d/%d: %d %f %f %f %f\n",(int)ihalo,(int)nhaloFOF, (int)FOFhalo[ihalo].host, FOFhalo[ihalo].mass,FOFhalo[ihalo].pos[0],FOFhalo[ihalo].pos[1],FOFhalo[ihalo].pos[2]);
      xb = FOFhalo[ihalo].pos[0]/subsize;
      yb = FOFhalo[ihalo].pos[1]/subsize;
      zb = FOFhalo[ihalo].pos[2]/subsize;
      
      block = xb*nsubperdim*nsubperdim + yb*nsubperdim + zb;
      FOFhalo[ihalo].nextid = hocFOF[block];
      hocFOF[block] = ihalo;
  
    }
  MPI_Barrier(MPI_COMM_WORLD);

  AHFhalo = malloc(0);

  nhaloAHF = read_clueAHFhalos();

  for(ihalo=0;ihalo<nhaloAHF;ihalo++)
    {
      if(AHFhalo[ihalo].host == 0 && AHFhalo[ihalo].nparts >= 50)
	{
	  xb = AHFhalo[ihalo].pos[0]/subsize;
	  yb = AHFhalo[ihalo].pos[1]/subsize;
	  zb = AHFhalo[ihalo].pos[2]/subsize;
      
	  block = xb*nsubperdim*nsubperdim + yb*nsubperdim + zb;
	  AHFhalo[ihalo].nextid = hocAHF[block];
	  hocAHF[block] = ihalo;
	}
    }
  

  blockA = totalsub/size;
  firstsub = rank*blockA;
  lastsub = MIN(blockA*(rank+1)-1,totalsub-1);


  /* FOF -> AHF */ 
  for(i=firstsub;i<=lastsub;i++)
    {

      xb = i/(nsubperdim*nsubperdim);
      yb = (i - xb*(nsubperdim*nsubperdim))/nsubperdim;
      zb = i - xb*(nsubperdim*nsubperdim) - yb*nsubperdim;
      
      curhalo_src = hocFOF[i];
      while(curhalo_src > -1)
  	{
  	  sigma_pos = 100.0;
  	  sigma_vel = 50.0;
  	  sigma_mass = FOFhalo[curhalo_src].mass*0.2;
	  maxmerit = -1.;
  	  for(target_b=0;target_b<27;target_b++)
  	    {
  	      ib = target_b/9 - 1;
  	      jb = (target_b - (ib+1)*9)/3 -1;
  	      kb = target_b - (ib+1)*9 - (jb+1)*3 -1;

  	      block = ((xb+ib+nsubperdim)%nsubperdim)*nsubperdim*nsubperdim
  		+ ((yb+jb+nsubperdim)%nsubperdim)*nsubperdim
  		+ ((zb+kb+nsubperdim)%nsubperdim);
	      
  	   
  	      curhalo_tar = hocAHF[block];
  	      while(curhalo_tar > -1)
  		{
  		  merit = ((FOFhalo[curhalo_src].pos[0] - AHFhalo[curhalo_tar].pos[0])/sigma_pos)*((FOFhalo[curhalo_src].pos[0] - AHFhalo[curhalo_tar].pos[0])/sigma_pos)
  		    + ((FOFhalo[curhalo_src].pos[1] - AHFhalo[curhalo_tar].pos[1])/sigma_pos)*((FOFhalo[curhalo_src].pos[1] - AHFhalo[curhalo_tar].pos[1])/sigma_pos)
  		    + ((FOFhalo[curhalo_src].pos[2] - AHFhalo[curhalo_tar].pos[2])/sigma_pos)*((FOFhalo[curhalo_src].pos[2] - AHFhalo[curhalo_tar].pos[2])/sigma_pos)
  		    + ((FOFhalo[curhalo_src].vel[0] - AHFhalo[curhalo_tar].vel[0])/sigma_vel)*((FOFhalo[curhalo_src].vel[0] - AHFhalo[curhalo_tar].vel[0])/sigma_vel)
  		    + ((FOFhalo[curhalo_src].vel[1] - AHFhalo[curhalo_tar].vel[1])/sigma_vel)*((FOFhalo[curhalo_src].vel[1] - AHFhalo[curhalo_tar].vel[1])/sigma_vel)
  		    + ((FOFhalo[curhalo_src].vel[2] - AHFhalo[curhalo_tar].vel[2])/sigma_vel)*((FOFhalo[curhalo_src].vel[2] - AHFhalo[curhalo_tar].vel[2])/sigma_vel)
  		    + ((FOFhalo[curhalo_src].mass - AHFhalo[curhalo_tar].mass)/sigma_mass)*((FOFhalo[curhalo_src].mass - AHFhalo[curhalo_tar].mass)/sigma_mass);
		  
  		  merit = exp(-1.*merit);
  		  if(merit > maxmerit)
  		    {
  		      maxmeritid = curhalo_tar;
  		      maxmerit = merit;
  		    }
  		  curhalo_tar = AHFhalo[curhalo_tar].nextid;
  		}
  	    }
	  if(maxmerit > 0.005)
	    {
	      FOFhalo[curhalo_src].FOF2AHF = maxmeritid;
	    }
	  else
	    {
	      FOFhalo[curhalo_src].FOF2AHF = -1;
	    }
  	  curhalo_src = FOFhalo[curhalo_src].nextid;
  	}
    }

  /* AHF -> FOF */
  for(i=firstsub;i<=lastsub;i++)
    {
      xb = i/(nsubperdim*nsubperdim);
      yb = (i - xb*(nsubperdim*nsubperdim))/nsubperdim;
      zb = i - xb*(nsubperdim*nsubperdim) - yb*nsubperdim;
      
      curhalo_src = hocAHF[i];
      while(curhalo_src > -1)
	{
	  sigma_pos = 100.0;
	  sigma_vel = 50.0;
	  sigma_mass = AHFhalo[curhalo_src].mass * 0.2;
	  maxmerit = -1.;
	  for(target_b=0;target_b<27;target_b++)
	    {
	      ib = target_b/9 - 1;
	      jb = (target_b - (ib+1)*9)/3 -1;
	      kb = target_b - (ib+1)*9 - (jb+1)*3 -1;

	      block = ((xb+ib+nsubperdim)%nsubperdim)*nsubperdim*nsubperdim 
		+ ((yb+jb+nsubperdim)%nsubperdim)*nsubperdim
		+ ((zb+kb+nsubperdim)%nsubperdim);

	      curhalo_tar = hocFOF[block];
	      while(curhalo_tar > -1)
		{
		  merit = ((FOFhalo[curhalo_tar].pos[0] - AHFhalo[curhalo_src].pos[0])/sigma_pos)*((FOFhalo[curhalo_tar].pos[0] - AHFhalo[curhalo_src].pos[0])/sigma_pos)
		    + ((FOFhalo[curhalo_tar].pos[1] - AHFhalo[curhalo_src].pos[1])/sigma_pos)*((FOFhalo[curhalo_tar].pos[1] - AHFhalo[curhalo_src].pos[1])/sigma_pos)
		    + ((FOFhalo[curhalo_tar].pos[2] - AHFhalo[curhalo_src].pos[2])/sigma_pos)*((FOFhalo[curhalo_tar].pos[2] - AHFhalo[curhalo_src].pos[2])/sigma_pos)
		    + ((FOFhalo[curhalo_tar].vel[0] - AHFhalo[curhalo_src].vel[0])/sigma_vel)*((FOFhalo[curhalo_tar].vel[0] - AHFhalo[curhalo_src].vel[0])/sigma_vel)
		    + ((FOFhalo[curhalo_tar].vel[1] - AHFhalo[curhalo_src].vel[1])/sigma_vel)*((FOFhalo[curhalo_tar].vel[1] - AHFhalo[curhalo_src].vel[1])/sigma_vel)
		    + ((FOFhalo[curhalo_tar].vel[2] - AHFhalo[curhalo_src].vel[2])/sigma_vel)*((FOFhalo[curhalo_tar].vel[2] - AHFhalo[curhalo_src].vel[2])/sigma_vel)
		    + ((FOFhalo[curhalo_tar].mass - AHFhalo[curhalo_src].mass)/sigma_mass)*((FOFhalo[curhalo_tar].mass - AHFhalo[curhalo_src].mass)/sigma_mass);
		  
		  merit = exp(-1.*merit);
		  if(merit > maxmerit)
		    {
		      maxmeritid = curhalo_tar;
		      maxmerit = merit;
		    }
		  curhalo_tar = FOFhalo[curhalo_tar].nextid;
		}
	    }
	  if(maxmerit > 0.005)
	    {
	      AHFhalo[curhalo_src].AHF2FOF = maxmeritid;	  
	    }
	  else
	    {
	      AHFhalo[curhalo_src].AHF2FOF = -1;
	    }
	  curhalo_src = AHFhalo[curhalo_src].nextid;
	}
    }
  MPI_Barrier(MPI_COMM_WORLD);
  for(j=1;j<size;j++)
    {
      tag = j;
      blockA = totalsub/size;
      firstsub = j*blockA;
      lastsub = MIN(blockA*(j+1)-1,totalsub-1);
      for(i=firstsub;i<=lastsub;i++)
	{    
	  curhalo_src = hocAHF[i];
	  while(curhalo_src > -1)
	    {
	      if(rank == 0)
		{
		  MPI_Recv(&(FOFhalo[curhalo_src]), sizeof(struct halostruct), MPI_BYTE, j, tag, MPI_COMM_WORLD, &status);
		}
	      if(rank == j)
		{
		  MPI_Send(&(FOFhalo[curhalo_src]), sizeof(struct halostruct), MPI_BYTE, 0, tag, MPI_COMM_WORLD);
		}
	      MPI_Barrier(MPI_COMM_WORLD);
	      if(rank == 0)
		{
		  MPI_Recv(&(AHFhalo[curhalo_src]), sizeof(struct halostruct), MPI_BYTE, j, tag, MPI_COMM_WORLD, &status);
		}
	      if(rank == j)
		{
		  MPI_Send(&(AHFhalo[curhalo_src]), sizeof(struct halostruct), MPI_BYTE, 0, tag, MPI_COMM_WORLD);
		}
	      MPI_Barrier(MPI_COMM_WORLD);
	      curhalo_src = AHFhalo[curhalo_src].nextid;
	    }
	  MPI_Barrier(MPI_COMM_WORLD);
	}
    }
  MPI_Barrier(MPI_COMM_WORLD);
  if(rank == 0)
    {
      for(i=0;i<totalsub;i++)
	{
	  curhalo_src = hocAHF[i];
	  while(curhalo_src > -1)
	    {
	      ahf2fof = AHFhalo[curhalo_src].AHF2FOF;
	      if(ahf2fof > -1)
		{
		  fof2ahf = FOFhalo[ahf2fof].FOF2AHF;
		  if(curhalo_src != fof2ahf)
		    {
		      if(rank==0)printf("%d %d %d\n",curhalo_src,ahf2fof,fof2ahf);
		    }
		}
	      curhalo_src = AHFhalo[curhalo_src].nextid;
	    }
	}
    }

  MPI_Barrier(MPI_COMM_WORLD);
  free(hocFOF);
  free(hocAHF);
  free(AHFhalo);
  free(FOFhalo);
  MPI_Finalize();
  return 0;
}
