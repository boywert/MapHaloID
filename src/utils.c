#include "all.h"

struct halostruct {
  long long unsigned host;
  float pos[3];
  float vel[3];
  long long nextid=-1;
};
struct halostruct *haloA, *haloB;
long long *headofchainA, *headofchainB;

void read_clueAHFhalos(char *filename)
{

      fp = fopen(strcat(filename,".AHF_halos"), "r");
      fgets(buffer,MAXSTRING,fp);
      for(iHalo=0;iHalo<SnapNhalos[iFile];iHalo++)
	{
	  //printf("iHalo = %llu\n",iHalo);
	  fscanf(fp,"%llu %llu %llu %g %llu %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
		 &(HaloTable[currentHalo].ID),
		 &(HaloTable[currentHalo].hostHalo),
		 &(HaloTable[currentHalo].numSubStruct),
		 &(HaloTable[currentHalo].Mvir),
		 &(HaloTable[currentHalo].npart),
		 &(HaloTable[currentHalo].Xc),
		 &(HaloTable[currentHalo].Yc),
		 &(HaloTable[currentHalo].Zc),
		 &(HaloTable[currentHalo].VXc),
		 &(HaloTable[currentHalo].VYc),
		 &(HaloTable[currentHalo].VZc),
		 &(HaloTable[currentHalo].Rvir), 
		 &(HaloTable[currentHalo].Rmax),
		 &(HaloTable[currentHalo].r2),
		 &(HaloTable[currentHalo].mbp_offset),
		 &(HaloTable[currentHalo].com_offset),
		 &(HaloTable[currentHalo].Vmax),
		 &(HaloTable[currentHalo].v_esc),
		 &(HaloTable[currentHalo].sigV),
		 &(HaloTable[currentHalo].lambda),
		 &(HaloTable[currentHalo].lambdaE),
		 &(HaloTable[currentHalo].Lx),
		 &(HaloTable[currentHalo].Ly),
		 &(HaloTable[currentHalo].Lz),
		 &(HaloTable[currentHalo].b),
		 &(HaloTable[currentHalo].c),
		 &(HaloTable[currentHalo].Eax),
		 &(HaloTable[currentHalo].Eay),
		 &(HaloTable[currentHalo].Eaz),
		 &(HaloTable[currentHalo].Ebx), 
		 &(HaloTable[currentHalo].Eby),
		 &(HaloTable[currentHalo].Ebz),
		 &(HaloTable[currentHalo].Ecx), 
		 &(HaloTable[currentHalo].Ecy), 
		 &(HaloTable[currentHalo].Ecz),
		 &(HaloTable[currentHalo].ovdens),
		 &(HaloTable[currentHalo].nbins),
		 &(HaloTable[currentHalo].fMhires),
		 &(HaloTable[currentHalo].Ekin),
		 &(HaloTable[currentHalo].Epot),
		 &(HaloTable[currentHalo].SurfP),
		 &(HaloTable[currentHalo].Phi0),
		 &(HaloTable[currentHalo].cNFW) 
		 );
	  currentHalo++;
	}
      fclose(fp);
      
    }

}


int main(void)
{
  long long i;
  long long max_halo = 10000000;
  long long nhalosA = 0, nhalosB = 0;
  // read haloA : AHF
  
}
