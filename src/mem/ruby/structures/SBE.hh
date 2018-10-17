#ifndef __MEM_RUBY_STRUCTURES_SBE_HH__
#define __MEM_RUBY_STRUCTURES_SBE_HH__

#include "mem/ruby/common/Address.hh"
#include "mem/protocol/DataBlock.hh"

class SBE
{
  public:
    SBE() {}

    Addr m_Address;
    DataBlock m_DataBlk;
};

#endif // __MEM_RUBY_STRUCTURES_SBETABLE_HH__
