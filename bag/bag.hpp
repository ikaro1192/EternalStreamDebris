#pragma once
#pragma warning(disable:4290)

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

namespace bag{
//==================================ContentBag==================================
//�o�b�O��\������e���v���[�g�N���X
/*�e���v���[�g������Content�͎����Ă���I�u�W�F�N�g��\��AbstructHavingObject���p�������N���X��z��
���O�Ŏ�������ꍇ��
�EContent�̈Öق̃C���^�[�t�F�[�X
		void addContent();
		bool reduceContent();
*/
template<class Content>
class ContentBag{
	public:
		
		//�o�b�O�ɃA�C�e����ǉ�
		void appendContent(const std::string& ContentName);
		//�o�b�O����A�C�e�������o��
		typename std::shared_ptr<Content> removeContent(const std::string& ContentName)throw(std::out_of_range);
		//�C�e���[�^�֌W
		typename std::map<std::string,std::shared_ptr<Content> >::iterator begin();
		typename std::map<std::string,std::shared_ptr<Content> >::iterator end();

		//�����Ă���A�C�e���̎�ނ̐���Ԃ�
		const int getContentNum()const;
		
	private:
		std::map<std::string,std::shared_ptr<Content> > ContentList;
};

//=============================AbstructHavingObject=============================
//�o�b�O�̒��g�̒��ۃN���X
template<typename BodyObject,int MaximumAbleHave,class SubClass>
class AbstructHavingObject{
	public:
		friend class bag::ContentBag<SubClass>;

		AbstructHavingObject(const BodyObject& Self_);
		virtual ~AbstructHavingObject(){}

		//�����Ă��鑍����Ԃ�
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
	if (TargetContent==ContentList.end()) throw(std::out_of_range("������Ȃ�"));

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

