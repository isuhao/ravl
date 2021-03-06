// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBINARYTREEDOWNITER_HEADER
#define RAVLBINARYTREEDOWNITER_HEADER 1
/////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.API.Core.Trees"
//! author="Charles Galambos"
//! example=exBinaryTree.cc
//! lib=RavlCore
//! file="Ravl/Core/Container/Trees/BinaryTreeDownIter.hh"

#include "Ravl/BinaryTree.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Iterate down through a binary tree.
  // This iterate from the largest value to the smallest value
  // in a binary tree.
  
  template<class KeyT,class DataT>
  class BinaryTreeDownIterC {
  public:
    BinaryTreeDownIterC(const BinaryTreeC<KeyT,DataT> &ntree)
      : tree(ntree)
    { First(); }
    //: Constructor

    BinaryTreeDownIterC()
    {}
    //: Default constructor.

    const BinaryTreeC<KeyT,DataT> &operator=(const BinaryTreeC<KeyT,DataT> &ntree);
    //: Assignment from another binary tree.
    
    bool First();
    //: Goto smallest element in the tree.
    
    bool Next();
    //: Goto next smallest key in the tree.

    void operator++(int)
    { Next(); }
    //: Goto next smallest key in the tree
    
    DataT &Data()
    { return stk.Top()->Data(); }
    //: Access data.
    
    const DataT &Data() const
    { return stk.Top()->Data(); }
    //: Access data.
    
    const KeyT &Key() const
    { return stk.Top()->Key(); }
    //: Access data.
    
    bool IsElm() const
    { return !stk.IsEmpty(); }
    //: Test if we're at a valid element.

    operator bool() const
    { return !stk.IsEmpty(); }
    //: Test if we're at a valid element.

    DataT &operator *() 
    { return Data(); }
    //: Access data.
    
    DataT *operator->() 
    { return &Data(); }
    //: Access data.
    
#if 0
    void Remove();
    //: Delete this node.
    // NB. This uses lazy deletion, it only flags the
    // node as removed, it does not free any memory.
    //
    // FIXME:- This may cause MaxNode and MinNode to fail.
#endif    
  protected:
    BinaryTreeC<KeyT,DataT> tree;
    BlkStackC<BinaryTreeNodeC<KeyT,DataT> *> stk;
  };


  template<class KeyT,class DataT>
  const BinaryTreeC<KeyT,DataT> &BinaryTreeDownIterC<KeyT,DataT>::operator=(const BinaryTreeC<KeyT,DataT> &ntree) {
    tree = ntree;
    First();
    return ntree;
  }
  
  template<class KeyT,class DataT>
  bool BinaryTreeDownIterC<KeyT,DataT>::First() {
    stk.Empty();
    if(!tree.IsValid())
      return false;
    BinaryTreeNodeC<KeyT,DataT> *place = tree.Body().root;
    while(place != 0) {
      stk.Push(place);
      place = place->Child1();
    }
    if(stk.IsEmpty())
      return false;
    if(stk.Top()->IsDeleted()) { // Skip deleted nodes.
      return Next();
    }
    return true;
  }
  
  //: Goto smallest element in the tree.
  
  template<class KeyT,class DataT>
  bool BinaryTreeDownIterC<KeyT,DataT>::Next() {
    BinaryTreeNodeC<KeyT,DataT> *place;
    do {
      if(stk.Top()->Child0() == 0) {
	do {
	  place = stk.Top();
	  stk.DelTop();
	  if(stk.IsEmpty())
	    return false;
	  // If we're coming back from Child1(),
	  // pop again as we've done this node.
	} while(stk.Top()->Child0() == place) ;
	if(stk.Top()->IsDeleted())
	  continue; // Skip deleted nodes.
	return true;
      }
      stk.Push(stk.Top()->Child0());
      place = stk.Top()->Child1();
      while(place != 0) {
	stk.Push(place);
	place = place->Child1();
      }
    } while(stk.Top()->IsDeleted()) ; // Skip deleted nodes.
    return true;
  }
#if 0
  template<class KeyT,class DataT>
  void BinaryTreeDownIterC<KeyT,DataT>::Remove() {
    RavlAssert(!stk.IsEmpty());
    stk.Top().SetDeleted(true);
  }
#endif

}

#endif
