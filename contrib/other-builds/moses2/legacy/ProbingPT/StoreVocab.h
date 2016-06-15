/*
 * StoreVocab.h
 *
 *  Created on: 15 Jun 2016
 *      Author: hieu
 */
#pragma once
#include <string>
#include <boost/unordered_map.hpp>
#include "../OutputFileStream.h"

namespace Moses2
{

template<typename VOCABID>
class StoreVocab
{
protected:
  std::string m_path;

  typedef boost::unordered_map<std::string, VOCABID> Coll;
  Coll m_vocab;

public:
  StoreVocab(const std::string &path)
  :m_path(path)
  {}

  virtual ~StoreVocab() {}

  VOCABID GetVocabId(const std::string &word)
  {
    typename Coll::iterator iter = m_vocab.find(word);
    if (iter == m_vocab.end()) {
      uint32_t ind = m_vocab.size() + 1;
      m_vocab[word] = ind;
      return ind;
    }
    else {
      return iter->second;
    }
  }

  void Save()
  {
    OutputFileStream strme(m_path);

    typename Coll::const_iterator iter;
    for (iter = m_vocab.begin(); iter != m_vocab.end(); ++iter) {
      strme << iter->first << "\t" << iter->second << std::endl;
    }

    strme.Close();
  }
};

} /* namespace Moses2 */

