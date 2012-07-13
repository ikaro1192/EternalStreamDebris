#pragma once
#pragma warning(disable:4290)

#include <string>
#include <map>
#include <list>
#include <deque>
#include <vector>
#include <memory>
#include <string>
#include <bitset>
#include <iostream>
#include <stdexcept>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "container_database.hpp"
#include "basic_data_helper_functions.h"

namespace magic{

//つくり中
class Magic{
	public:
	
		Magic(std::string Name_,std::string ScriptName_,std::string Explain_,int Type_);

		const std::string getName();

	private:
		const std::string Name;
		std::string ScriptName;
		const std::string Explain;
		const int Type;

};


//=================================MagicDataBaseImplementation=================================

//現在作成中
//魔法のデータベースの実装
class MagicDataBaseImplementation: private boost::noncopyable{
	public:
		typedef Magic Content;
		static  Content* getContent(const boost::property_tree::ptree::value_type& child);

	static const std::string magic::MagicDataBaseImplementation::getRootName();
	static const std::string magic::MagicDataBaseImplementation::getFileName();
};

//簡単に扱えるようにするtypedef
typedef content_data_base::ContentDataBase<magic::MagicDataBaseImplementation> MagicDataBase;
}



/*
*/