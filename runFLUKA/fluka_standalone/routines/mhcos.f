      subroutine mhcosn(tx,ty,tz)
c======================================================================
c     mhcosn                                       MH 14.11.96 CERN/PPE
c
c     routine to normalize direction cosines
c     garanteed not to generate an invalid operation.
c======================================================================      
      include '(DBLPRC)'
      if (tx.lt.-1.0d0) then
        tx=-1.0d0
	ty=0.0d0      
	tz=0.0d0
      else if (tx.gt.1.0d0) then	
        tx=1.0d0
	ty=0.0d0      
	tz=0.0d0		
      else if (ty.lt.-1.0d0) then
        tx=0.0d0	
        ty=-1.0d0	
        tz=0.0d0	
      else if (ty.gt.1.0d0) then
        tx=0.0d0	
        ty=1.0d0	
        tz=0.0d0	
      else
        t2=tx*tx+ty*ty
	if (t2.gt.1.d0) then	
	  tz=0.d0
	  txt=sqrt(1.0d0-ty**2)
	  if (tx.lt.0.0d0) then 
            tx=-txt
          else
	    tx=txt
          endif	    	    
        else
	  tzt=sqrt(1.0d0-t2)	  
	  if (tz.lt.0.0d0) then
            tz=-tzt
          else
	    tz=tzt
          endif	    	    
        endif	  
      endif	
      end
