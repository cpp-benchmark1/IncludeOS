// This file is a part of the IncludeOS unikernel - www.includeos.org
//
// Copyright 2015 Oslo and Akershus University College of Applied Sciences
// and Alfred Bratterud
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <fs/dirent.hpp>

namespace fs
{

  Dirent::Dirent(const Dirent& other) noexcept
  {
    this->fs_     = other.fs_;
    this->ftype   = other.ftype;
    this->fname_  = other.fname_;
    this->block_  = other.block_;
    this->parent_ = other.parent_;
    this->size_   = other.size_;
    this->attrib_ = other.attrib_;
    this->modif   = other.modif;
  }


  Dirent& Dirent::operator=(const Dirent& other) noexcept
  {
    this->fs_     = other.fs_;
    this->ftype   = other.ftype;
    this->fname_  = other.fname_;
    this->block_  = other.block_;
    this->parent_ = other.parent_;
    this->size_   = other.size_;
    this->attrib_ = other.attrib_;
    this->modif   = other.modif;

    return *this;
  }

}
