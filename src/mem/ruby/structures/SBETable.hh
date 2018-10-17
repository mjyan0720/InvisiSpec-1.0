#ifndef __MEM_RUBY_STRUCTURES_SBETABLE_HH__
#define __MEM_RUBY_STRUCTURES_SBETABLE_HH__

#include <iostream>
#include <unordered_map>

#include "mem/ruby/common/Address.hh"
#include "mem/protocol/DataBlock.hh"

class SBE
{
  public:
    SBE() {}

    Addr m_addr;
    DataBlock m_DataBlk;
};

class SBETable
{
  public:
    SBETable() {}

    // bool isPresent(Addr address) const;
    void allocate(Addr address);
    // void deallocate(Addr address);

  private:
    std::unordered_map<Addr, SBE> m_map;
};

inline void
SBETable::allocate(Addr address)
{
    // assert(!isPresent(address));
    m_map[address] = SBE();
    m_map[address].m_addr = address;
}

#endif // __MEM_RUBY_STRUCTURES_SBETABLE_HH__
