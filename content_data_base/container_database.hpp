
#pragma once

#include<memory>
#include <stdexcept>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace content_data_base{
//=================================ContentDataBase=================================
//Flyweightなデータベースを作るためのテンプレートクラス
/*Implementationの暗黙のインターフェース
typedef Content;//データの中身の方をtypedefする
typename Content* getContent(boost::property_tree::ptree Tree);//部分木から中身を生成してポインタを返す
static const std::string getRootName();//ファイルのRootの名前
static const std::string getFileName();//書かれているファイル(XML)

Contentの暗黙のインターフェース
const std::string getName();

*/
template<class Implementation>
class ContentDataBase: private boost::noncopyable{
	
	typedef typename Implementation::Content Content;

	public:

		//データベースに存在しなかったら例外送出
		static std::shared_ptr<typename Content>& get(const std::string& ContentName_) throw(std::invalid_argument);

	private:
		ContentDataBase();
		std::map<std::string,std::shared_ptr<typename Content> > ContentList;


};
}

//=============================ContentDataBase Methods=============================

template<class Implementation>
content_data_base::ContentDataBase<Implementation>::ContentDataBase(){
	
	boost::property_tree::ptree ReadData;
	boost::property_tree::read_xml(Implementation::getFileName() , ReadData );
	BOOST_FOREACH(const auto& child, ReadData.get_child(Implementation::getRootName())) {
		auto AppendContent=Implementation::getContent(child);
		ContentList.insert(std::map<std::string,std::shared_ptr<typename Content> >::value_type(AppendContent->getName(),std::shared_ptr<typename Content>(AppendContent) ) );
	}

}


template<class Implementation>
std::shared_ptr<typename content_data_base::ContentDataBase<Implementation>::Content>& content_data_base::ContentDataBase<Implementation>::get(const std::string& ItemName_)throw(std::invalid_argument){
	static ContentDataBase instance;

	auto it = instance.ContentList.find(ItemName_);
	if (it!= instance.ContentList.end() ){
		return it->second;
	}else{
		throw std::invalid_argument("不正なアイテム名");
	}

}