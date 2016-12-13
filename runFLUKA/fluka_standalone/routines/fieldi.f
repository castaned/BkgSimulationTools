      subroutine fieldi
c===========================================================================
c     fieldi                                            MH 4.10.96 CERN/PPE
c
c     subroutine to read in the CMS magnetic field map for 00080 maps
c     from Dick Loveless
c===========================================================================
      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
      parameter (nrmap=180,nzmap=320)
      common /cmsmap/ drmap,dzmap,rminma,zminma,
     & rmaxma,zmaxma,br(nrmap,nzmap),bz(nrmap,nzmap),btot(nrmap,nzmap)
      dimension bchk(3,46,31)
      drmap=5.d0
      dzmap=5.d0
      rminma=0.d0
      zminma=0.d0     
      rmaxma=900.d0
      zmaxma=1600.d0
      CALL OAUXFI('../cmssw501.fieldmap',99,'OLD',IERR)      
      do 3 i=1, nrmap
         do 4 j=1,nzmap
            read(99,*) z,r,br(i,j),bz(i,j)
 4       continue
 3    continue
      do 1 i=1,nrmap
        do 2 j=1,nzmap
          btot(i,j)=sqrt(br(i,j)**2+bz(i,j)**2)
    2   continue
    1 continue
      write(*,*) 'Full field map read and converted to Tesla'
      write(*,*) 'Testing map now...'          
      do 10 ir=1,46   
        phi=FLRNDM(vdum*ir)*3.1415926d0*2.d0
        rr=(ir-0.5)*drmap*2
        y=rr*sin(phi)
        x=rr*cos(phi)
        do 11 iz=1,31
          z=(iz-0.5)*dzmap*4
          call magfld(x,y,z,btx,bty,btz,b,nreg,idisc)
          bchk(1,ir,iz)=b
          bchk(2,ir,iz)=sqrt(btx**2+bty**2)
          bchk(3,ir,iz)=btz                   
          btest=sqrt(btx**2+bty**2+btz**2)
          if (abs(btest-1.d0).gt.1d-10) then
            write(*,*) 'B-field not normalized',btest,b,ir,iz,
     &                 btx,bty,btz,x,y,z
            stop
          endif
   11   continue
   10 continue
c     don't check the map any more...   
      goto 30
      write(97,*) 'Total B in Tesla'
      do 20 ir=1,46
        write(97,1001) (bchk(1,ir,iz),iz=1,31)
   20 continue
      write(97,*) 'Total BR components in Tesla'
      do 21 ir=1,46
        write(97,1001) (bchk(2,ir,iz),iz=1,31)
   21 continue                  
      write(97,*) 'Total BZ components in Tesla'
      do 22 ir=1,46
        write(97,1001) (bchk(3,ir,iz),iz=1,31)
   22 continue	 
   30 continue
c     read in lbq field map
      write (*,*) 'calling lbqfin'
      call lbqfin
 1000 format(8f10.5)                         
 1001 format(31(1p,1x,e9.2))                         
      end
