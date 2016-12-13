#PBS script to run FLUKA jobs
#Can be implemented with other scheduler (slurm, condor, etc..) 

#Requirements: 
- local installation of FLUKA package (32bit or 64) that is accessible to other nodes (in case of running in a cluster) 
- Fortran compiler: gfortran (64bits) g77 (32bits), installed in all the cluster nodes

#Steps: 


- produce a tarball with the content of fluka_standalone directory:

   tar -zcvf fluka_standalone.tgz fluka_standalone/

- replace the directory name for your simulation:

   (e.g.  export work_folder=<name_of_project>

- change the FLUPRO and FLUFOR variables: 
       FLUPRO=location of your installed FLUKA version
       FLUFOR=fortran compiler used (e.g.  g77 or gfortran)

- change geometry file according to you simulation
   (e.g. templates/CMSpp_v3.0.0.0.inp CMSpp_template.inp)

- Every simulation job will produce an event (primary), depending on your detector region or scoring you will need of the order of 1k to 10k simulated primaries





