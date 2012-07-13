
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
//Flyweight�ȃf�[�^�x�[�X����邽�߂̃e���v���[�g�N���X
/*Implementation�̈Öق̃C���^�[�t�F�[�X
typedef Content;//�f�[�^�̒��g�̕���typedef����
typename Content* getContent(boost::property_tree::ptree Tree);//�����؂��璆�g�𐶐����ă|�C���^��Ԃ�
static const std::string getRootName();//�t�@�C����Root�̖��O
static const std::string getFileName();//������Ă���t�@�C��(XML)

Content�̈Öق̃C���^�[�t�F�[�X
const std::string getName();

*/
template<class Implementation>
class ContentDataBase: private boost::noncopyable{
	
	typedef typename Implementation::Content Content;

	public:

		//�f�[�^�x�[�X�ɑ��݂��Ȃ��������O���o
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
		throw std::invalid_argument("�s���ȃA�C�e����");
	}

}