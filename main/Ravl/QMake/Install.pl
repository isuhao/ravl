$NEWHOME = $ARGV[0];
$PROJOUT = $ARGV[1];
open(infile,$ARGV[2]);
open(outfile,">$ARGV[3]");
while(<infile>) {
  if(/[ ]*MAKEHOME[ ]*=[ ]*[^ ]*/) {
    print outfile " MAKEHOME\=$NEWHOME\n" ;
  } else {
    if(/\A[ ]*setenv[ ]+QMAKE_INSTALL[ ]*[^ ]*/) {
      print outfile "setenv QMAKE_INSTALL $NEWHOME\n" ;
    } elsif(/\A[ ]*setenv[ ]+RAVL_INSTALL[ ]*[^ ]*/) {
      print outfile "setenv RAVL_INSTALL $PROJOUT\n" ;
    } elsif(/\A[ ]*\$QMAKE_INSTALL_DIR[ ]+\=[ ]*[^ ]*/) {
      print outfile "\$QMAKE_INSTALL_DIR = \"$NEWHOME\" ;\n" ;
    } elsif(/\A[ ]*QMAKE_INSTALL[ ]*\=[ ]*[^ ]*/) {
      print outfile "QMAKE_INSTALL=$NEWHOME ;\n" ;
    } elsif(/\A[ ]*RAVL_INSTALL[ ]*\=[ ]*[^ ]*/) {
      print outfile "RAVL_INSTALL=$PROJOUT\n" ;
    }else {
      print outfile "$_" ;
    }
  }
}
($a1,$a2,$mode,$nlink,$uid,$gid,$rdev,$size,$atime,$mtime,$ctime,$blksize,$blocks)= stat($ARGV[1]);
chmod $mode,$ARGV[2] ;
