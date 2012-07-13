#include "effect_obj.h"

//=============================RunnableEffectTuple=============================
effect_obj::RunnableEffectTuple::RunnableEffectTuple(EffectInterface* Effect_,std::string TargetName_,EffectHandlerInterface* Handler_):
			EffectObject(Effect_),
			TargetName(TargetName_),
			Handler(Handler_)
			{}

bool effect_obj::RunnableEffectTuple::run(std::string RunFunctionName){return Handler->run(EffectObject,TargetName,RunFunctionName);}


//================================EffectManager================================

//�f�X�g���N�^
effect_obj::EffectManager::~EffectManager(){
	std::vector<EffectHandlerInterface*>::iterator it=EffectSpecies.begin();
	while( it != EffectSpecies.end() ){
		delete (*it);
		it++;
	}
}

//createEffectSelector
//�b��
boost::optional<std::shared_ptr<effect_obj::EffectManager::Selector> > effect_obj::EffectManager::createEffectSelector(EffectInterface* Effect)throw(std::invalid_argument){
	std::vector<std::string> TargetList;
	
	//�A�C�e���������ł���Handler��T��(Chain of Responsibility)
	auto it=EffectSpecies.begin();
	while( it != EffectSpecies.end() ){
		//vector����̏ꍇ�����ł��Ȃ����Ƃ�\��
		if (!((*it)->getTargetList(Effect->getType())).empty()){
			TargetList=(*it)->getTargetList(Effect->getType());
			if (TargetList[0]=="NULL"){
				std::shared_ptr<effect_obj::EffectManager::Selector> Tmp(new effect_obj::EffectManager::Selector(TargetList,Effect,*it,this));
				this->set(Tmp.get(),Effect,"NULL");
				return boost::optional<std::shared_ptr<effect_obj::EffectManager::Selector> >(std::shared_ptr<Selector>());
			}else{
				return boost::optional<std::shared_ptr<effect_obj::EffectManager::Selector> >(std::shared_ptr<Selector>(new effect_obj::EffectManager::Selector(TargetList,Effect,*it,this)));
			}
		}
		it++;
	}
	
	return boost::none;
	
	
}


//set
//Selector����Ă΂�邽�߃v���O���}����͌����Ȃ�
void effect_obj::EffectManager::set(Selector* ThisSelector,EffectInterface* SetEffect,std::string TargetName){
	EffectManager::Selector::GetHandler(ThisSelector) ->run(SetEffect,TargetName,RunFunctionName);
	return;
}

//append
void effect_obj::EffectManager::appendHandler(effect_obj::EffectHandlerInterface* EffectHandler){
	EffectSpecies.push_back(EffectHandler);
}


//===========================EffectManager::Selector===========================
//�v���O���}����͌����Ȃ�
effect_obj::EffectManager::Selector::Selector(std::vector<std::string>& TargetList_,EffectInterface* Effect_,EffectHandlerInterface* Handler_,EffectManager* Manager_):
	TargetName(""),
	Manager(Manager_),
	Effect(Effect_),
	Handler(Handler_),
	TargetList(TargetList_)
	{}
//selectTarget
void effect_obj::EffectManager::Selector::run(int Target){
	Manager->set(this,Effect,TargetList.at(Target));
}

void effect_obj::EffectManager::Selector::run(std::string Target){
	TargetName=Target;
	Manager->set(this,Effect,TargetName);

}

void effect_obj::EffectManager::Selector::run(effect_obj::EffectManager::Selector::iterator Target){
	Manager->set(this,Effect,*Target);
}


//�n���h����Ԃ�
effect_obj::EffectHandlerInterface* effect_obj::EffectManager::Selector::GetHandler(EffectManager::Selector* Self){
	return Self->Handler;
}
