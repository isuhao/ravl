// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////
//! rcsid="$Id$" 
//! lib=RavlGUI

#include "Ravl/GUI/CList.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/SArr1Iter2.hh"
#include <gtk/gtk.h>

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  CListBodyC::CListBodyC(const DListC<StringC> &ntitles)
    : selMode(GTK_SELECTION_SINGLE),
      titles(ntitles)
  {
    cols = titles.Size();
    ONDEBUG(cerr << "CListBodyC::CListBodyC(), Cols : " << cols << "\n");
  }
  
  //: Default constructor
  
  CListBodyC::CListBodyC(const char *ntitles[])  {
    int i = 0;
    if(ntitles != 0) {
      for(;ntitles[i] != 0;i++)
	titles.InsLast(StringC(ntitles[i]));
    } else {
      titles.InsLast("Unknown");
      i++;
    }

    cols = i;
    ONDEBUG(cerr << "CListBodyC::CListBodyC(), Cols : " << cols << "\n");
  }
  
  //: Called when row is unselected.
  
  bool CListBodyC::GUIRowUnselected(CListEventC &cle) {
    ONDEBUG(cerr << "CListBodyC::GUIRowUnselected. " << cle.RowID() << "\n");
    RWLockHoldC hold(access,false);
    selection -= cle.RowID();
    return true;
  }

  //: Called when row is unselected.
  
  bool CListBodyC::GUIRowSelected(CListEventC &cle) {
    ONDEBUG(cerr << "CListBodyC::GUIRowSelected. " << cle.RowID() << "\n");
    RWLockHoldC hold(access,false);
    selection += cle.RowID();
    return true;
  }
  
  //: Access current selection.
  
  DListC<IntT> CListBodyC::Selection() {
    DListC<IntT> ret;
    RWLockHoldC hold(access,true);
    for(HSetIterC<IntT> it(selection);it;it++)
      ret += *it;
    return ret;
  }
  
  
  //: Create the widget.
  
  bool CListBodyC::Create() {
    if(widget != 0)
      return true; // Done already!
    
    cols = titles.Size();
    char **tlist = new char *[cols];
    int i = 0;
    for(DLIterC<StringC> it(titles);it;it++,i++) 
      tlist[i] = (char *) it->chars();
    widget = gtk_clist_new_with_titles(cols,tlist);  
    delete tlist; // Hope I don't need this now.
    gtk_clist_set_selection_mode(GTK_CLIST(widget),selMode);
    // Append lines that we've stored up.
    for(DLIterC<Tuple2C<IntT,SArray1dC<CListCellC> > > it(data);it;it++)
      GUIAppendCLine(it->Data1(),it->Data2());
    
    ConnectRef(Signal("select_row"),*this,&CListBodyC::GUIRowSelected);
    ConnectRef(Signal("unselect_row"),*this,&CListBodyC::GUIRowUnselected);
    ConnectSignals();
    return true;
  }
  
  //: Append a line entry.  
  // GUI thread only.
  
  bool CListBodyC::GUIAppendCLine(int &id,SArray1dC<CListCellC> &line) {
    if(widget == 0) {
      data.InsLast(Tuple2C<IntT,SArray1dC<CListCellC> >(id,line));
      return true;
    }
    // This doesn't to any fancy stuff yet...
    char **tlist = new char *[cols];
    for(int i = 0;i < cols;i++)
      tlist[i] = (char *) line[i].text.chars();  
    int rowNo = gtk_clist_append(GTK_CLIST(widget),tlist);
    gtk_clist_set_row_data (GTK_CLIST(widget),rowNo,(void *) id);
    delete tlist;
    return true;
  }
  
  //: Append a line entry.  
  // GUI thread only.
  
  bool CListBodyC::GUIAppendLine(int &id,SArray1dC<StringC> &line) {
    if(widget == 0) {
      SArray1dC<CListCellC> newLine(cols);
      for(SArray1dIter2C<CListCellC,StringC> it(newLine,line);it;it++)
	it.Data1().text = it.Data2();
      data.InsLast(Tuple2C<IntT,SArray1dC<CListCellC> >(id,newLine));
      return true;
    }
    RavlAssert(((int) line.Size()) >= cols); // Do something friendlier ?
    int rowNo = gtk_clist_find_row_from_data (GTK_CLIST(widget),(void *) id);
    if(rowNo >= 0) { // Got row already ?
      for(int i = 0;i< ((int) line.Size());i++)
	gtk_clist_set_text(GTK_CLIST(widget),rowNo,i,line[i]);
    } else {
      char **tlist = new char *[cols];
      for(int i = 0;i < cols;i++)
	tlist[i] = (char *) line[i].chars();  
      rowNo = gtk_clist_append(GTK_CLIST(widget),tlist);
      gtk_clist_set_row_data (GTK_CLIST(widget),rowNo,(void *) id);
      delete tlist;
    }
    return true;
  }
  
  //: Remove a line entry.  
// GUI thread only.
  
  bool CListBodyC::GUIRemoveLine(int &id) {
    int rowNo = gtk_clist_find_row_from_data (GTK_CLIST(widget),(void *) id);
    ONDEBUG(cerr << "CListBodyC::GUIRemoveLine(), ID:" << id << "  Row:" << rowNo << "\n");
    if(rowNo < 0)
      return true; // Not found.
    gtk_clist_remove (GTK_CLIST(widget),rowNo);
    return true;
  }
  
  //: Remove a line entry.  
  
  void CListBodyC::RemoveLine(int &id) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIRemoveLine,id));
  }
  
  
  //: Append a line entry.  
  // GUI thread only.
  
  void CListBodyC::AppendLine(int &id,SArray1dC<CListCellC> &line) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIAppendCLine,id,line));
  }
  
  //: Append a line entry.  
  // GUI thread only.
  
  void CListBodyC::AppendLine(int &id,SArray1dC<StringC> &line) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIAppendLine,id,line));
  }

  //: Force an item to be selected.
  
  bool CListBodyC::GUISelect(int &id) {
    if(widget == 0) {
      // FIXME:- This should be handled properly....
      cerr << "WARNING: CListBodyC::GUISelect() called before widget created. \n";
      return true;
    }
    int rowNo = gtk_clist_find_row_from_data (GTK_CLIST(widget),(void *) id);
    if(rowNo < 0)
      return true; // Not found.
    gtk_clist_select_row (GTK_CLIST(widget),rowNo,0);
    return true;    
  }
  
  //: Force an item to be unselected.
  
  bool CListBodyC::GUIUnselect(int &id) {
    if(widget == 0) {
      // FIXME:- This should be handled properly.
      cerr << "WARNING: CListBodyC::GUIUnselect() called before widget created. \n";
      return true;
    }
    int rowNo = gtk_clist_find_row_from_data (GTK_CLIST(widget),(void *) id);
    if(rowNo < 0)
      return true; // Not found.
    gtk_clist_unselect_row (GTK_CLIST(widget),rowNo,0);
    return true;
  }
  
  //: Force an item to be selected.
  
  bool CListBodyC::Select(int &id) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUISelect,id));
    return true;
  }
  
  //: Force an item to be unselected.
  
  bool CListBodyC::Unselect(int &id) {
    Manager.Queue(Trigger(CListC(*this),&CListC::GUIUnselect,id));
    return true;
  }
  
  //: Undo all refrences.
  
  void CListBodyC::Destroy() {
    WidgetBodyC::Destroy(); 
  }
}
