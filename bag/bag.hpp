#pragma once
#pragma warning(disable:4290)

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

namespace bag{
//==================================ContentBag==================================
//バッグを表現するテンプレートクラス
/*テンプレート引数のContentは持っているオブジェクトを表すAbstructHavingObjectを継承したクラスを想定
自前で実装する場合は
・Contentの暗黙のインターフェース
		void addContent();
		bool reduceContent();
*/
template<class Content>
class ContentBag{
	public:
		
		//バッグにアイテムを追加
		void appendContent(const std::string& ContentName);
		//バッグからアイテムを取り出す
		typename std::shared_ptr<Content> removeContent(const std::string& ContentName)throw(std::out_of_range);
		//イテレータ関係
		typename std::map<std::string,std::shared_ptr<Content> >::iterator begin();
		typename std::map<std::string,std::shared_ptr<Content> >::iterator end();

		//入っているアイテムの種類の数を返す
		const int getContentNum()const;
		
	private:
		std::map<std::string,std::shared_ptr<Content> > ContentList;
};

//=============================AbstructHavingObject=============================
//バッグの中身の抽象クラス
template<typename BodyObject,int MaximumAbleHave,class SubClass>
class AbstructHavingObject{
	public:
		friend class bag::ContentBag<SubClass>;

		AbstructHavingObject(const BodyObject& Self_);
		virtual ~AbstructHavingObject(){}

		//持っている総数を返す
		const unsigned int getHavingNumber() const;
		
	protected:
		BodyObject Self;

	private:
		void addContent();
		const bool reduceContent();

		unsigned int HavingNumber;
		
};

}


//===============================ContentBag Methods===============================

template<class Content>
const int bag::ContentBag<Content>::getContentNum() const{
	return ContentList.size();
}
		

template<class Content>
void bag::ContentBag<Content>::appendContent(const std::string& ContentName){
	if (ContentList.count(ContentName)==0){
		ContentList.insert(std::map<std::string,std::shared_ptr<typename Content> >::value_type(ContentName,new Content(ContentName)));
	}else{
		ContentList[ContentName]->addContent();
	}
}

template<class Content>
typename std::shared_ptr<Content> bag::ContentBag<Content>::removeContent(const std::string& ContentName){
	
	auto TargetContent=ContentList.find(ContentName);
	if (TargetContent==ContentList.end()) throw(std::out_of_range("見つからない"));

	auto ReturnContent=TargetContent->second;
	if (TargetContent->second->reduceContent()==false){
		ContentList.erase(TargetContent);
	}

	return ReturnContent;


}

template<class Content>
typename std::map<std::string,std::shared_ptr<Content> >::iterator bag::ContentBag<Content>::begin(){return ContentList.begin();}

template<class Content>
typename std::map<std::string,std::shared_ptr<Content> >::iterator bag::ContentBag<Content>::end(){return ContentList.end();}

//=========================AbstructHavingObject Methods=========================

template<typename BodyObject,int MaximumAbleHave,class SubClass>
bag::AbstructHavingObject<BodyObject,MaximumAbleHave,SubClass>::AbstructHavingObject(const BodyObject& Self_):
	Self(Self_),
	HavingNumber(1)
	{}


template<typename BodyObject,int MaximumAbleHave,class SubClass>
const unsigned int bag::AbstructHavingObject<BodyObject,MaximumAbleHave,SubClass>::getHavingNumber() const{
	return HavingNumber;
}


template<typename BodyObject,int MaximumAbleHave,class SubClass>
void bag::AbstructHavingObject<BodyObject,MaximumAbleHave,SubClass>::addContent(){
	HavingNumber++;
	if (HavingNumber>MaximumAbleHave) HavingNumber=MaximumAbleHave;
}

template<typename BodyObject,int MaximumAbleHave,class SubClass>
const bool bag::AbstructHavingObject<BodyObject,MaximumAbleHave,SubClass>::reduceContent(){
	HavingNumber--;
	if (HavingNumber<=0){
		return false;
	}
	return true;

}

