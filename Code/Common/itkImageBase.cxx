/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkImageBase.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#include "itkImageBase.h"

ITK_NAMESPACE_BEGIN
  
/**
 *
 */
ImageBase
::ImageBase()
{
}


/**
 *
 */
ImageBase
::~ImageBase()
{
  this->Initialize();
}


/**
 *
 */
void 
ImageBase
::Initialize()
{
  this->DataObject::Initialize();
}


/**
 *
 */
void 
ImageBase
::PrintSelf(std::ostream& os, Indent indent)
{
  DataObject::PrintSelf(os,indent);
}

ITK_NAMESPACE_END
