// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here


namespace RavlAudioN
{
  extern void InitLibFFmpegAudioFormat();
  
  void MustLinkLibFFmpegAudio()
  { 
    InitLibFFmpegAudioFormat();
  }
}
