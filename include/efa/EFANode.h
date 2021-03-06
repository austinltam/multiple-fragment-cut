//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include <string>

class EFANode
{
public:
  enum N_CATEGORY
  {
    N_CATEGORY_PERMANENT,
    N_CATEGORY_TEMP,
    N_CATEGORY_EMBEDDED,
    N_CATEGORY_EMBEDDED_PERMANENT,
    N_CATEGORY_LOCAL_INDEX
  };

  EFANode(unsigned int nid, N_CATEGORY ncat, EFANode * nparent = NULL);

private:
  N_CATEGORY _category;
  unsigned int _id;
  EFANode * _parent;
  std::vector <unsigned int> _cut_plane_id;
  std::vector <unsigned int> _past_cut_plane_id;

public:
  std::string idCatString();
  unsigned int id() const;
  N_CATEGORY category() const;
  void setCategory(EFANode::N_CATEGORY category);
  EFANode * parent() const;
  void removeParent();
  std::vector <unsigned int> getCutPlaneIDs();
  void addCutPlaneID(unsigned int cutPlaneID);
  bool hasCutPlaneID(unsigned int CutPlaneID);
  void moveCutPlaneIDtoPast(unsigned int cutPlaneID);
  unsigned int getLastCutPlaneID();
  bool hasCut();
  bool hasSameCut(EFANode otherNode);
};
