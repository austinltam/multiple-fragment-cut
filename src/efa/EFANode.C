//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EFANode.h"

#include <sstream>

EFANode::EFANode(unsigned int nid, N_CATEGORY ncat, EFANode * nparent)
  : _category(ncat), _id(nid), _parent(nparent)
{
}

std::string
EFANode::idCatString()
{
  std::ostringstream s;
  s << _id;
  if (_category == N_CATEGORY_EMBEDDED)
    s << "e";
  else if (_category == N_CATEGORY_TEMP)
    s << "t";
  else if (_category == N_CATEGORY_EMBEDDED_PERMANENT)
    s << "ep";
  else
    s << " ";
  return s.str();
}

unsigned int
EFANode::id() const
{
  return _id;
}

EFANode::N_CATEGORY
EFANode::category() const
{
  return _category;
}

EFANode *
EFANode::parent() const
{
  return _parent;
}

void
EFANode::removeParent()
{
  _parent = NULL;
}

void
EFANode::setCategory(EFANode::N_CATEGORY category)
{
  _category = category;
}

std::vector<unsigned int>
EFANode::getCutPlaneIDs()
{
	return _cut_plane_id;
}

void
EFANode::addCutPlaneID(unsigned int cutPlaneID)
{
	_cut_plane_id.push_back(cutPlaneID);
}

bool
EFANode::hasCutPlaneID(unsigned int cutPlaneID)
{
	bool has_Cut = false;
    for (unsigned int i = 0; i < _cut_plane_id.size(); ++i)
	{
	  if (cutPlaneID == _cut_plane_id[i])
	  {
	    has_Cut = true;
	    break;
	  }
	}
    return has_Cut;
}

void
EFANode::moveCutPlaneIDtoPast(unsigned int cutPlaneID)
{
  for(unsigned int i = 0; i < _cut_plane_id.size(); ++i)
  {
    if(_cut_plane_id[i] == cutPlaneID)
    {
      _past_cut_plane_id.push_back(_cut_plane_id[i]);
      _cut_plane_id.erase(_cut_plane_id.begin()+i);
      return;
    }
  }
}

unsigned int
EFANode::getLastCutPlaneID()
{
  return _cut_plane_id.back();
}

bool
EFANode::hasCut()
{
  return (_cut_plane_id.size()>0) ? (true) : (false);
}

bool
EFANode::hasSameCut(EFANode otherNode)
{
  for (unsigned int i = 0; i < _cut_plane_id.size(); ++i)
  {
    if (otherNode.hasCutPlaneID(_cut_plane_id[i]))
    {
      return true;
    }
  }
  return false;
}
