#!/usr/bin/perl

use DynaLoader;

sub PrintHelp {
  print "BinDep 2\n Some help: \n";
  print "  bindep [options] objectfiles \n";
  print "Options: \n";
  print "  -T(library name)  Specify a library that will be created soon. \n";
  print "  -L(directory)     Directory to seach for libraries. \n";
  print "  -l(library stem)  Stem of library name use in executable. \n";
  print "  -P(string)        Pass on string to stdout. \n";
  print "  -v                Verbose mode. \n";
  print " -I... -o... -O...  Are ingored. \n";
  exit ;
}

  my @LibPath, @Output, @Find, $found;
  my $verbose=0;
  my $returnCode=0;
  
  # First check for verbose or help flags
  foreach (@ARGV) {
    if(/\A-v/) { # Verbose
      $verbose=1;
      next ;
    }
    if(/\A-h/) {  # Reqest for help.
      PrintHelp;
    }
  }

  foreach (@ARGV) {
    if(/\A-L([^ ]*)/) { # Library search dir - record it
      push @LibPath, "-L".$1 ;
      next ;
    }
#   if(/\A-R([^ ]*)/) {
#     push @LibPath, "-L".$1." " ;
#     next ;
#   }
    if(/\A-n32/) {  # Irix new 32 bit mode ?
      push @LibPath, "-L/usr/lib32" ;
      next ;
    }
    if(/\A-64/) {  # Irix 64 bit mode ?
      push @LibPath, "-L/usr/lib64" ;
      next ;
    }
    if(/\A-P(.*)/) { # Just pass on string.
      push @Output, $1 . " ";
      next ;
    }
    if(/\A-l([^ ]*)/) { # Library - find its path
      if(exists $targLibs{$1}) { # We know library may not exist yet
        push @Output, $1 ; # Use its path as specified
      }
      else
      { if($verbose) {
          print stderr "Searching for  '-l$1' \n";
          print stderr "Using system path '@DynaLoader::dl_library_path' \n";
          print stderr "and '@LibPath' \n";
        }
        @Find = @LibPath ;
        push @Find, "-l" . $1 ;
        $found = DynaLoader::dl_findfile( @Find );
        if($verbose) { print stderr "Found '$found' \n"; }
        if ($found) { # Located library - use full path
          push @Output, $found . " " ;
        }
        else { # Library not found - keep -l form
          $returnCode=-1;
          push @Output, @Find[$#Find] . " " ;
          print stderr "Error - could not locate library @Find[$#Find].\n";
        }
      }
      next ;
    }
    if(/\A-T([^ ]*)/) { # Library we know may not exist yet - record the fact
      $targLibs{$1} = 1;
      next ;
    }
    if(/\A-[WRLuIOvVgrpB][^ ]*/ )  { # Ignore these.
      next ;
    }
    if(/\A[^-][^ ]*/) { # Ingore direct dependancy on object files
      next ;
    }
    print stderr "Unknown argument $_\n ";
  }

  print @Output;
  print "\n";
  exit $returnCode;
