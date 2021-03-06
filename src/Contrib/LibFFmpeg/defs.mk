# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003-14, University of Surrey
# This code may be redistributed under the terms of the GNU
# General Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here

REQUIRES = libffmpeg

ORGANISATION=Omniperception Ltd.

PACKAGE = Ravl/Image

HEADERS = ImgIOFFmpeg.hh LibFFmpegFormat.hh FFmpegPacket.hh \
 FFmpegPacketStream.hh FFmpegVideoDecoder.hh FFmpegVideoEncoder.hh \
 FFmpegEncodePacketStream.hh ImgDPOFFmpeg.hh

SOURCES = ImgIOFFmpeg.cc LibFFmpegFormat.cc FFmpegPacket.cc \
 FFmpegPacketStream.cc FFmpegVideoDecoder.cc FFmpegVideoEncoder.cc \
 FFmpegEncodePacketStream.cc ImgDPOFFmpeg.cc

PLIB = RavlLibFFmpeg

SUMMARY_LIB=Ravl

MUSTLINK = MustLinkLibFFmpeg.cc

EXTERNALLIBS=LibFFmpeg.def

USESLIBS = RavlImage RavlIO LibFFmpeg

PROGLIBS = RavlGUI.opt RavlDPDisplay.opt RavlRawVidIO.opt RavlVideoIO

EXAMPLES = exFFmpeg.cc exFFmpegSeek.cc exFFmpegOutPut.cc

EHT = LibFFmpeg.html
