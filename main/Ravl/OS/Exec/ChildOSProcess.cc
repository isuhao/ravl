// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlOS
//! file="Ravl/OS/Exec/ChildOSProcess.cc"

#include "Ravl/OS/ChildOSProcess.hh"

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 3
#endif

#ifdef __linux__
extern "C" {
  int kill(pid_t pid, int sig);
};
#endif

#include <sys/types.h>
#ifndef VISUAL_CPP
#include <sys/wait.h>
#include <unistd.h>
#else
#include <direct.h>
#endif
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif


namespace RavlN {
  
  ///////////////////////////////////////////////////////
  //: Start a child process.

  ChildOSProcessC::ChildOSProcessC(StringC cmd,bool useStdOut,bool useStdErr,bool useStdIn)
    : OSProcessC(*new ChildOSProcessBodyC(cmd,useStdOut,useStdErr,useStdIn))
    {}
  
  //: Start a child process.
  
  ChildOSProcessC::ChildOSProcessC(StringC cmd,FilenameC out,bool redirectStderr,bool useStdIn)
    : OSProcessC(*new ChildOSProcessBodyC(cmd,out,redirectStderr,useStdIn))
    {}
  
  ///////////////////////////////////////////////////////
  //: Default constructor.
  
  ChildOSProcessBodyC::ChildOSProcessBodyC()
    : OSProcessBodyC(-1),
    running(false),
    exitok(false)
    {}

  //: Start a child process.
  
  ChildOSProcessBodyC::ChildOSProcessBodyC(StringC cmd,FilenameC out,bool redirectStderr,bool useStdIn)
    : OSProcessBodyC(-1),
    running(false),
    exitok(false)
  {
    StringListC strlst(cmd);
    Run(strlst,out,redirectStderr,useStdIn);
  }
  
  //: Start a child process.
  
  ChildOSProcessBodyC::ChildOSProcessBodyC(StringC cmd,bool useStdOut,bool useStdErr,bool useStdIn)
    : OSProcessBodyC(-1),
    running(false),
    exitok(false)
  {
    StringListC strlst(cmd);
    Run(strlst,useStdOut,useStdErr,useStdIn);
  }
  
  //: Start a child process.
  // where the first arg is the name of the program to run.
  
  ChildOSProcessBodyC::ChildOSProcessBodyC(StringListC args)
    : OSProcessBodyC(-1),
    running(false),
    exitok(false)
  {
    Run(args);
  }


  // Use the most appropriate fork for the architecture
  // for doing an exec.
  
#define EXECFORK fork

  //: Run child process.
  // Will return false if failed, or if child is already
  // running.
  
  bool ChildOSProcessBodyC::Run(StringListC args,bool useStdOut,bool useStdErr,bool useStdIn) {
    if(args.IsEmpty())
      return false; // No program to run.
    
    // Setup stdio stuff.
    int stdoutfd = -1,stderrfd = -1,stdinfd = -1;
    
    if(useStdOut) 
      stdoutfd = SetupPipe(pstdout);
    
    if(useStdErr) 
      stderrfd = SetupPipe(pstderr);
    
    if(useStdIn) 
      stdinfd = SetupPipe(pstdin);
    
    // And run it.
    return Exec(args,stdinfd,stdoutfd,stderrfd);
  }
  
  //////////////////////////////////
  //: Run, sending output to a file.
  
  bool ChildOSProcessBodyC::Run(StringListC args,FilenameC out,bool redirectStderr,bool useStdIn) {
#ifndef VISUAL_CPP
    if(args.IsEmpty())
      return false; // No program to run.
    
    // Setup stdio stuff.
    
    int stdoutfd = -1,stderrfd = -1,stdinfd = -1;
    if((stdoutfd = open(out.chars(),O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
      cerr << "Failed to open file '" << out << "'\n";
      return false;
    }
    fcntl(stdoutfd,F_SETFD,1); // Close this descriptor on exec.
    ONDEBUG(cerr << "Text file output fd:" << stdoutfd << "\n");
    if(redirectStderr)
      stderrfd = stdoutfd;
    
    if(useStdIn)
      stdinfd = SetupPipe(pstdin);
    
    // And run it.
    bool ret = Exec(args,stdinfd,stdoutfd,stderrfd);  
    close(stdoutfd); // Don't need it anymore.
    return ret;
#else
    throw ExceptionC("ChildOSProcessBodyC::Run() Not implemented. \n");
#endif
  }
  
  //////////////////////////////////
  //: Execute a program.
  // if infd,outfd or errfd are negative there not changed.
  
  bool ChildOSProcessBodyC::Exec(StringListC args,int infd,int outfd,int errfd) {  
#ifndef VISUAL_CPP
    if(args.IsEmpty()) {
      cerr << "ChildOSProcessBodyC::Exec(), No program to run. \n";
      return false; // No program to run.
    }
    if(running) {
      cerr << "ChildOSProcessBodyC::Exec(), Failed. Program already running. \n";
      return false;
    }
    // Make arg list, do it before vfork to avoid
    // problems that may be caused by multithreading.
    char **arglst = new char *[args.Size()+1];
    char **place = arglst;
    for(DLIterC<StringC> it(args);it.IsElm();it.Next(),place++)
      *place = const_cast<char *>(it.Data().chars());
    *place = 0; // Zero terminate list.
    
    // Fork off new process.
    if((pid = EXECFORK()) == 0) {
      // In child, setup a stdin and stdout.
      bool err = false;
      if(infd >= 0) {
	if(dup2(infd,STDIN_FILENO) >= 0)
	  fcntl(STDIN_FILENO,F_SETFD,0); // Make sure file is kept open across exec.
	else
	  err = true;
      }
      if(outfd >= 0 && !err) {
	if(dup2(outfd,STDOUT_FILENO) >= 0)
	  fcntl(STDOUT_FILENO,F_SETFD,0); // Make sure file is kept open across exec.
	else
	  err = true;
      }
      if(errfd >= 0 && !err) {
	if(dup2(errfd,STDERR_FILENO) >= 0)
	  fcntl(STDERR_FILENO,F_SETFD,0); // Make sure file is kept open across exec.
	else
	  err = true;
      }
      if(err) {
	perror("ChildOSProcessBodyC::Run(): Error setup execp ");
	_exit(-1);
      }
      execvp(*arglst,arglst); 
      // If no error this won't return.
      perror("ChildOSProcessBodyC::Run(): execvp failed ");
      _exit(-1);
    }
    delete arglst; // Clean up.
    if(pid < 0) { // Did fork fail ?
      cerr << "ChildOSProcessBodyC::Exec(), Failed to fork. \n";
      running = false;
      return false;
    }
    running = true;
    //cerr << "Started:" << pid << "\n";
    return true;
#else
    throw ExceptionC("ChildOSProcessBodyC::Exec() Not implemented. ");
#endif
  }
  
  //: Setup input stream.
  // Connect strm to one end, and return a file descriptor
  // for the other. 
  // If failed returns -1.
  
  int ChildOSProcessBodyC::SetupPipe(IStreamC &strm) {
#ifndef VISUAL_CPP
    int fds[2];
    if(pipe(fds) != 0) { // 0-Read 1-Write
      cerr << "ChildOSProcessBodyC::SetupIPipe(), Failed to create pipe. \n";
      return -1;
    }
    strm = IStreamC(fds[0]);
    fcntl(fds[0],F_SETFD,1); // Close this descriptor on exec.
    fcntl(fds[1],F_SETFD,1); // Close this descriptor on exec.
    return fds[1];
#else
    throw ExceptionC("ChildOSProcessBodyC::SetupPipe(), Not implemented. ");
#endif
  }
  
  //: Setup output stream.
  // Connect strm to one end, and return a file descriptor
  // for the other. 
  // If failed returns -1.
  
  int ChildOSProcessBodyC::SetupPipe(OStreamC &strm) {
#ifndef VISUAL_CPP
    int fds[2];
    if(pipe(fds) != 0) { // 0-Read 1-Write
      cerr << "ChildOSProcessBodyC::SetupOPipe(), Failed to create pipe. \n";
      return -1;
    }
    strm = OStreamC(fds[1]);
    fcntl(fds[0],F_SETFD,1); // Close this descriptor on exec.
    fcntl(fds[1],F_SETFD,1); // Close this descriptor on exec.
    return fds[0];
#else
    throw ExceptionC("ChildOSProcessBodyC::SetupPipe(), Not implemented. ");
#endif
  }
  
  //////////////////////////////////
  //: Call if you get the exit code from OSProcessC::WaitForChild()
  
  bool ChildOSProcessBodyC::GotExitCode(int code) {
#ifndef VISUAL_CPP
    if(WIFEXITED(code)) { // Exited normaly ?
      exitcode = WEXITSTATUS(code);
      exitok = true;
    }
    if(WIFSIGNALED(code)) { // Exited on signal ?
      exitcode = WTERMSIG(code);
      exitok = false;
    }
    running = false;
    return exitok;
#else
    throw ExceptionC("ChildOSProcessBodyC::GotExitCode(), Not implemented. ");
#endif
  }
  
  //////////////////////////////////
  //: Check exit status of child.

  bool ChildOSProcessBodyC::CheckExit(bool block) {
#ifndef VISUAL_CPP
    int stat,id;
    if((id = waitpid(pid,&stat,WNOHANG)) == 0) {
      if(errno == ECHILD) { // No such child ??
	exitok = false;
	exitcode = 0;
	return true;
      }
      return false; // OSProcess is still running.
    }
    if(id < 0) {
      cerr << "ChildOSProcessBodyC::IsRunning(), waitpid failed. \n";
      exitok = false;
      exitcode = 0;
      return true;
    }
    GotExitCode(stat);
    return true;
#else
    throw ExceptionC("ChildOSProcessBodyC::CheckExit(), Not implemented. ");
#endif
  }
  
  //////////////////////////////////
  //: Wait for program to exit.
  
  bool ChildOSProcessBodyC::Wait() {
#ifndef VISUAL_CPP
    int stat,id;
    id = waitpid(pid,&stat,0);
    if(id < 0) {
      perror("ChildOSProcessBodyC::Wait(), waitpid failed. ");
      return false;
    }
    running = false;
    GotExitCode(stat);
    return true;
#else
    throw ExceptionC("ChildOSProcessBodyC::Wait(), Not implemented. ");
#endif
  }
  
  //////////////////////////////////
  //: Test if child is still running.
  
  bool ChildOSProcessBodyC::IsRunning() {
    if(!running)
      return false;
    if(pid < 0)
      return false; // OSProcess never started.
    return !CheckExit();
  }
}
