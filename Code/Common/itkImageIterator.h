/*==========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkImageIterator.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.
  
==========================================================================*/
#ifndef __itkImageIterator_h
#define __itkImageIterator_h

#include "itkIndex.h"
#include "itkImage.h"
#include <memory.h>

ITK_NAMESPACE_BEGIN

/**
 * \class ImageIterator
 * \brief Multi-dimensional image iterator.
 * 
 * ImageIterator is a templated class to represent a multi-dimensional
 * iterator. ImageIterator is templated over the dimension of the image
 * and the data type of the image.
 *
 * ImageIterator is a base class for all the image iterators. It provides
 * the basic construction and comparison operations.  However, it does not
 * provide mechanisms for moving the iterator.  A subclass of ImageIterator
 * must be used to move the iterator.
 * 
 * ImageIterator is a multi-dimensional iterator, requiring more information
 * be specified before the iterator can be used than conventional iterators.
 * Whereas the std::vector::iterator from the STL only needs to be passed
 * a pointer to establish the iterator, the multi-dimensional image iterator
 * needs a pointer, the size of the buffer, the size of the region, the
 * start index of the buffer, and the start index of the region. To gain
 * access to this information, ImageIterator holds a reference to the image
 * over which it is traversing.
 *
 * ImageIterator assumes a particular layout of the image data. In particular,
 * the data is arranged in a 1D array as if it were [][][][slice][row][col]
 * with Index[0] = col, Index[1] = row, Index[2] = slice, etc.
 *
 * 
 */
template<typename TPixel, unsigned int VImageDimension=2>
class ImageIterator {
public:
  /**
   * Standard "Self" typedef.
   */
  typedef ImageIterator Self;
  
  /** 
   * Index typedef support.
   */
  typedef Index<VImageDimension> Index;

  /**
   * Image typedef support.
   */
  typedef Image<TPixel, VImageDimension> Image;

  /**
   * Default Constructor. Need to provide a default constructor since we
   * provide a copy constructor.
   */
  ImageIterator()
  {
    m_Buffer = 0;
    m_Offset = 0;
    m_BeginOffset = 0;
    m_EndOffset = 0;
    memset( m_Size, 0, VImageDimension*sizeof(unsigned long) );
  }

  /**
   * Copy Constructor. The copy constructor is provided to make sure the
   * handle to the image is properly reference counted.
   */
  ImageIterator(const Self& it)
  {
    m_Image = it.m_Image;     // copy the smart pointer

    m_StartIndex = it.m_StartIndex;
    memcpy(m_Size, it.m_Size, VImageDimension*sizeof(unsigned long));
    
    m_Buffer = it.m_Buffer;
    m_Offset = it.m_Offset;
    m_BeginOffset = it.m_BeginOffset;
    m_EndOffset = it.m_EndOffset;
  }

  /**
   * Constructor establishes an iterator to walk a particular image and a
   * particular region of that image.
   */
  ImageIterator(const SmartPointer<Image> &ptr,
                const Index &start,
                const unsigned long size[VImageDimension])
  {
    m_Image = ptr;
    m_Buffer = m_Image->GetBufferPointer();
    m_StartIndex = start;
    memcpy(m_Size, size, VImageDimension*sizeof(unsigned long));

    // Compute the start offset
    m_Offset = m_Image->ComputeOffset( m_StartIndex );
    m_BeginOffset = m_Offset;
    
    // Compute the end offset
    Index ind(m_StartIndex);
    for (unsigned int i=0; i < VImageDimension; ++i)
      {
      ind[i] += (m_Size[i] - 1);
      }
    m_EndOffset = m_Image->ComputeOffset( ind );
    m_EndOffset++;
  }
  
  /**
   * operator= is provided to make sure the handle to the image is properly
   * reference counted.
   */
  Self &operator=(const Self& it)
  {
    m_Image = it.m_Image;     // copy the smart pointer

    m_StartIndex = it.m_StartIndex;
    memcpy(m_Size, it.m_Size, VImageDimension*sizeof(unsigned long));
    
    m_Buffer = it.m_Buffer;
    m_Offset = it.m_Offset;
    m_BeginOffset = it.m_BeginOffset;
    m_EndOffset = it.m_EndOffset;

    return *this;
  }
  
  /**
   * Get the dimension (size) of the index.
   */
  static unsigned int GetImageIteratorDimension() 
    {return VImageDimension;}

  /**
   * Comparison operator. Two iterators are the same if they "point to" the
   * same memory location
   */
  bool
  operator!=(const Self &it) const
    {
    // two iterators are the same if they "point to" the same memory location
    return (m_Buffer + m_Offset) != (it.m_Buffer + it.m_Offset);
    };

  /**
   * Comparison operator. Two iterators are the same if they "point to" the
   * same memory location
   */
  bool
  operator==(const Self &it) const
    {
    // two iterators are the same if they "point to" the same memory location
    return (m_Buffer + m_Offset) == (it.m_Buffer + it.m_Offset);
    };
  
  /**
   * Comparison operator. An iterator is "less than" another if it "points to"
   * a lower memory location.
   */
  bool
  operator<=(const Self &it) const
    {
    // an iterator is "less than" another if it "points to" a lower
    // memory location
    return (m_Buffer + m_Offset) <= (it.m_Buffer + it.m_Offset);
    };

  /**
   * Comparison operator. An iterator is "less than" another if it "points to"
   * a lower memory location.
   */
  bool
  operator<(const Self &it) const
    {
    // an iterator is "less than" another if it "points to" a lower
    // memory location
    return (m_Buffer + m_Offset) < (it.m_Buffer + it.m_Offset);
    };

  /**
   * Comparison operator. An iterator is "greater than" another if it
   * "points to" a higher location.
   */
  bool
  operator>=(const Self &it) const
    {
    // an iterator is "greater than" another if it "points to" a higher
    // memory location
    return (m_Buffer + m_Offset) >= (it.m_Buffer + it.m_Offset);
    };

  /**
   * Comparison operator. An iterator is "greater than" another if it
   * "points to" a higher location.
   */
  bool
  operator>(const Self &it) const
    {
    // an iterator is "greater than" another if it "points to" a higher
    // memory location
    return (m_Buffer + m_Offset) > (it.m_Buffer + it.m_Offset);
    };

  /**
   * Get the index. This provides a read only reference to the index.
   * This causes the index to be calculated from pointer arithmetic and is
   * therefore an expensive operation.
   * \sa SetIndex
   */
  const Index GetIndex()
    { return m_Image->ComputeIndex( m_Offset );  }

  /**
   * Set the index. No bounds checking is performed.
   * \sa GetIndex
   */
  void SetIndex(const Index &ind)
    { m_Offset = m_Image->ComputeOffset( ind ); }

  /**
   * Get the size of the image.
   */
  const unsigned long *GetImageSize() const
  { return m_Image->GetImageSize(); };

  /**
   * Get the size of the buffer.
   */
  const unsigned long *GetBufferSize() const
  { return m_Image->GetBufferSize(); };

  /**
   * Get the "array index" of the first pixel to iterate over.
   * ImageIterators know the beginning and end of the region of the image
   * to iterate over.
   */
  const Index &GetStartIndex() const  {return m_StartIndex;} ;

  /**
   * Get the size of the region to iterator over.
   */
  const unsigned long *GetSize() const
    { return m_Size; };

  /**
   * Dereference the iterator, returns a reference to the pixel. Used to set
   * or get the value referenced by the index.
   */
  TPixel& operator*() const  
    { return *( m_Buffer + m_Offset ); }

  /**
   * Return an iterator for the beginning of the region.
   */
  Self Begin();

  /**
   * Return an iterator for the end of the region.
   */
  Self End();

  /**
   * Is the iterator at the beginning of the region?
   */
  bool IsAtBegin()
    {
    return (m_Offset == m_BeginOffset);
    }

  /**
   * Is the iterator at the end of the region?
   */
  bool IsAtEnd()
    {
    return (m_Offset == m_EndOffset);
    }
  
protected: //made protected so other iterators can access 
  SmartPointer<Image> m_Image;
  Index          m_StartIndex;                // Index to start iterating over
  unsigned long  m_Size[VImageDimension];     // How large of a region to iter
  
  unsigned long  m_Offset;
  unsigned long  m_BeginOffset;
  unsigned long  m_EndOffset;

  TPixel        *m_Buffer;
};

ITK_NAMESPACE_END

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkImageIterator.txx"
#endif

#endif 
